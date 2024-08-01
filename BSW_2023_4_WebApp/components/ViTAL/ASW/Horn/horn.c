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
#include "ASW/Horn/horn.h"

static const char *TAG = "ASW HONK";

void  Horn()
{
    static bool lastState = false;
    bool state = COM_bGet_ButtonHonkStatus();

    if(state)
    {
        COM_vResetHonkButton();
    }
    if(lastState == state)
        return;

    RTE_vSetBuzzerState(state);
    lastState = state;
    
    ESP_LOGI(TAG, "HONK PWM: %d", state);   
}