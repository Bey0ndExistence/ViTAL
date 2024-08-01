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
#include "BSW/HAL/DC_Motor/dc_motor.h"

static const char *TAG = "DC_MOTOR";

void DCMOT_vChangeSpeed(uint32_t u32DCMotorSpeed, bool dir)
{
        ESP_LOGI(TAG,"SPEED DC MOTOR: %d", u32DCMotorSpeed);
    if(u32DCMotorSpeed <= DC_MOTOR_FULL_SPEED)
    {
        if(dir == LEFT)
        {
            PWM_vSetDutyCycle(DC_MOTOR_PWM_CHANNEL, u32DCMotorSpeed);
        }
        else
        {
            PWM_vSetDutyCycle(DC_MOTOR_PWM_REVERSE_CHANNEL, u32DCMotorSpeed);
        }
    }
}