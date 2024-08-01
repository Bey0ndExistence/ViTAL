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
#include "ASW/Climate_Control_System/climate_control_system.h"

static bool fanWasOn = true;
static uint8_t power = 0;


static const char *TAG = "Climate Control System";

void ControlAmbientTemperature()
{
    bool isfanon= COM_bGet_ButtonFanStatus();
    ESP_LOGI(TAG,"iS FAN ON?: %d", isfanon);
   if(COM_bGet_ButtonFanStatus())
    {
        fanWasOn = true;
        power = abs(COM_u8GetComfort() - COM_bGet_UserTemperatureStatus());
           ESP_LOGI(TAG,"POWER?: %d", power);

        switch(power)
        {
            case 0:
                RTE_vSetDCMotorSpeed(DC_MOTOR_LOW_SPEED);
            break;
            case 1:
                RTE_vSetDCMotorSpeed(DC_MOTOR_20);
            break;
            case 2:
                RTE_vSetDCMotorSpeed(DC_MOTOR_30);
            break;
            case 3:
                RTE_vSetDCMotorSpeed(DC_MOTOR_40);
            break;
            case 4:
                RTE_vSetDCMotorSpeed(DC_MOTOR_60);
            break;
            case 5:
                RTE_vSetDCMotorSpeed(DC_MOTOR_80);
            break;
            case 6:
                RTE_vSetDCMotorSpeed(DC_MOTOR_FULL_SPEED);
            break;
        }
    }
    else if(fanWasOn)
    {
        RTE_vSetDCMotorSpeed(DC_MOTOR_STOP);
        fanWasOn = false;
    }
}