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
#include "BSW/MCAL/PWM/pwm.h"

typedef enum
{
    CLOSE = 0,
    SUSPENDED = 90,
    OPEN = 180
} SERVO_trunk_pos;

void SERVO_vChangeAngle(uint32_t u32ServoAngle); 