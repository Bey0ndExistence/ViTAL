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
#ifndef COMPONENTS_VITAL_RTE_H
#define COMPONENTS_VITAL_RTE_H

#include "global.h"

#include "BSW/HAL/Com/com.h" 
#include "BSW/HAL/Shift_Register/shift_register.h"
#include "BSW/HAL/Proximity_Sensor/proximity_sensor.h"
#include "BSW/HAL/Photo_Resistor/photo_resistor.h"
#include "BSW/HAL/Temp_Sensor/temp_sensor.h"
#include "BSW/HAL/DC_Motor/dc_motor.h"
#include "BSW/HAL/Buzzer/buzzer.h"
#include "BSW/HAL/Servo_Motor/servo_motor.h"

#define OFF false
#define ON true

#define LOW false
#define HIGH true

typedef enum
{
	LOCK_GREEN = (uint8_t)(1 << 1),
	LOCK_RED = (uint8_t)(1 << 2),
	RGB_RED_POS = (uint8_t)(1 << 4),
	RGB_GREEN_POS = (uint8_t)(1 << 5),
	RGB_BLUE_POS = (uint8_t)(1 << 3),
	HEAD_LIGHTS_POS = (uint8_t)((1 << 6) | (1 << 7))
} shift_register_positions_t;

typedef enum
{
	RED = RGB_RED_POS,
	GREEN = RGB_GREEN_POS,
	BLUE = RGB_BLUE_POS,
	RED_GREEN = RGB_RED_POS | RGB_GREEN_POS,
	RED_BLUE = RGB_RED_POS | RGB_BLUE_POS,
	GREEN_BLUE = RGB_GREEN_POS | RGB_BLUE_POS,
	ALL_COLORS = RGB_RED_POS | RGB_GREEN_POS | RGB_BLUE_POS
} rgb_states_masks_t;

typedef enum
{
	STATE_RED = 0,
	STATE_GREEN,
	STATE_BLUE,
	STATE_RED_GREEN,
	STATE_RED_BLUE,
	STATE_GREEN_BLUE,
	STATE_ALL_COLORS
} rgb_states_t;

void RTE_vSetRGBLedState();

void RTE_vSetAmbientalLightsState(bool bState);

void RTE_vSetShiftRegisterOutput(shift_register_positions_t u8ComponentMask, bool bLevel);

void RTE_vSetDCMotorSpeed(uint32_t speed);

void RTE_vIsOcupied();

void RTE_vPhotoResCalculate(void);

void RTE_vSetRGBLedByLuminosity(uint16_t thr);

void RTE_vTempAndHumCalculate();

void RTE_vSetBuzzerState(bool on);

void RTE_vSetServoState(bool open);

void RTE_vMotorTest();

#endif
