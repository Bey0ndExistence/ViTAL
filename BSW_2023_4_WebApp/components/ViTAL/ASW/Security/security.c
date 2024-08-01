/*******************************************************************************
 * COPYRIGHT (C) VITESCO TECHNOLOGIES
 * ALL RIGHTS RESERVED.
 *
 * The reproduction, transmission or use of this document or its
 * contents is not permitted without express written authority.
 * Offenders will be liable for damages. All rights, including rights
 * created by patent grant or registration of a utility model or design,
 * are reserved.
 *******************************************************************************/
#include "ASW/Security/security.h"

static const char *TAG = "ASW SECURIRY";

bool CheckAlarm()
{
    static uint8_t state = 0;

    bool on = false;
    bool SS = COM_bGet_ButtonSecurityStatus();
    bool LS = COM_bGet_ButtonDoorLockStatus();
    bool IO = COM_bGetIsOcupied();  
    
    switch (state)
    {
    case 0:
        if(SS && LS)
            state = 1;
        on = false;
        break;
    case 1:
        if(!SS || !LS)
            state = 0;
        else
        if(IO)  
            state = 2;
        on = false;
        break;
    case 2:
        if(!LS || !SS)
            state = 0;
        on = true;    
        break;

    default:
        on = false;
        break;
    }
   //ESP_LOGI(TAG, "OUT: %d, STATE: %d - %d,%d,%d", on, state, SS, LS, IO);
    return on;
}

void SetAlarm()
{
    static bool on = false;

    if(CheckAlarm())
    {
        on = !on;
        // headlights
        RTE_vSetShiftRegisterOutput(HEAD_LIGHTS_POS, on);  
        // Honk  
        RTE_vSetBuzzerState(on);
        // ESP_LOGI(TAG, "ALARM ON");
    }
    else{
        on = false;
        if(!COM_bGet_ButtonHeadlightsStatus())
            RTE_vSetShiftRegisterOutput(HEAD_LIGHTS_POS, on);
        RTE_vSetBuzzerState(on);
    }
}


void FindMyCar()
{
    static uint8_t ticks = FYND_MY_CAR_TICKS;

    static bool lastStatus = false;
    bool status = COM_bGet_ButtonFindMyCarStatus();

    if(lastStatus == status)
        return;

    if(status && ticks > 0)
    {
        bool isOn = --ticks % 2;
        // headlights
        RTE_vSetShiftRegisterOutput(HEAD_LIGHTS_POS, isOn);  
        // Honk  
        RTE_vSetBuzzerState(isOn);

    }
    else
    {
        ticks = FYND_MY_CAR_TICKS;
        COM_vResetFindMyCarButton();
        lastStatus = status;
    }
   
}

