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
#include "RTE/rte.h"

static const char *TAG = "RTE";

void RTE_vSetAmbientalLightsState(bool bState)
{
	/*The function will render the R-G-B color sequence.
	  bState will be the button status from WebApp */

	static uint8_t s_u8ColorState = STATE_RED;

	if (bState == ON)
	{
		RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
		switch (s_u8ColorState)
		{
		case STATE_RED:
			RTE_vSetShiftRegisterOutput(RED, HIGH);
			s_u8ColorState = STATE_RED_GREEN;
			break;
		case STATE_GREEN:
			RTE_vSetShiftRegisterOutput(GREEN, HIGH);
			s_u8ColorState = STATE_GREEN_BLUE;
			break;
		case STATE_BLUE:
			RTE_vSetShiftRegisterOutput(BLUE, HIGH);
			s_u8ColorState = STATE_RED_BLUE;
			break;
		case STATE_RED_GREEN:
			RTE_vSetShiftRegisterOutput(RED_GREEN, HIGH);
			s_u8ColorState = STATE_GREEN;
			break;
		case STATE_RED_BLUE:
			RTE_vSetShiftRegisterOutput(RED_BLUE, HIGH);
			s_u8ColorState = STATE_ALL_COLORS;
			break;
		case STATE_GREEN_BLUE:
			RTE_vSetShiftRegisterOutput(GREEN_BLUE, HIGH);
			s_u8ColorState = STATE_BLUE;
			break;
		case STATE_ALL_COLORS:
			RTE_vSetShiftRegisterOutput(ALL_COLORS, HIGH);
			s_u8ColorState = STATE_RED;
			break;
		default:
			ESP_LOGI(TAG, "RGB ERROR");
			break;
		}
	}
	else if (bState == OFF)
	{
		RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
		s_u8ColorState = STATE_RED;
	}
	else
	{
		ESP_LOGI(TAG, "AMBIENTAL LIGHTS ERROR");
	}
}

void RTE_vSetRGBLedState() 
{
	/* this function will control the RGB led through the shift register depending on the combination of pressed buttons 
	   (R, G or B button or a combination of these)*/
	int rgbState = (int)COM_bGet_ButtonRLedStatus() + 2 * (int)COM_bGet_ButtonGLedStatus() + 4 * (int)COM_bGet_ButtonBLedStatus();
	
	RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
	switch(rgbState)
	{
	case 0: // off
		break;
	case 1: // red
		RTE_vSetShiftRegisterOutput(RED, HIGH);		
		break;
	case 2: // green
		RTE_vSetShiftRegisterOutput(GREEN, HIGH);
		break; 
	case 3: // red-green
		RTE_vSetShiftRegisterOutput(RED_GREEN, HIGH);
		break;
	case 4: // blue
		RTE_vSetShiftRegisterOutput(BLUE, HIGH);
		break;
	case 5: //red-blue
		RTE_vSetShiftRegisterOutput(RED_BLUE, HIGH);
		break;
	case 6: //green-blue
		RTE_vSetShiftRegisterOutput(GREEN_BLUE, HIGH);
		break;
	case 7: //red-green-blue
		RTE_vSetShiftRegisterOutput(ALL_COLORS, HIGH);	
		break;
	default:
		ESP_LOGI(TAG, "AMBIENTAL LIGHTS ERROR");
		break;
	} 
}
void RTE_vSetShiftRegisterOutput(shift_register_positions_t u8ComponentMask, bool bLevel)
{
	/* this function will send to the shift register to reproduce the color sequence */
	static uint8_t s_u8CurrentData = 0;

	switch(bLevel)
	{
		case LOW:
			s_u8CurrentData &= ~(u8ComponentMask);
			break;
		case HIGH:
			s_u8CurrentData |= u8ComponentMask;
			break;
		default:
			ESP_LOGI(TAG, "Invalid level for shift register");
			break;
	}
	SHIFTREG_vOutput8Bits(s_u8CurrentData);
}

void RTE_vSetDCMotorSpeed(uint32_t speed)
{	
	DCMOT_vChangeSpeed(speed, LEFT);
}

void RTE_vIsOcupied()
{
    bool oc = PROX_v16Read() <= 50;
    COM_vSetIsOccupied(oc);
}

void RTE_vPhotoResCalculate(void)
{
    uint16_t ptRes = PHRES_u16Read(); 
    COM_vSetPhotoRes(ptRes);
}
void RTE_vSetRGBLedByLuminosity(uint16_t thr)
{
    uint16_t ptRes = PHRES_u16Read();
    if(ptRes > thr)
    {
        RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
		//RTE_vSetShiftRegisterOutput(GREEN_BLUE, HIGH);
    }
    else
    {
        //RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
		RTE_vSetShiftRegisterOutput(BLUE, HIGH);
        //RTE_vSetShiftRegisterOutput(ALL_COLORS, HIGH);   
    }
    ESP_LOGI(TAG, "Luminozitate: %d", ptRes);
}

void RTE_vTempAndHumCalculate()
{
	DHT11_vTaskTempAndHumCalculate();
}

void RTE_vSetBuzzerState(bool on)
{
	uint16_t u32BuzzerDutyCycle = on ? BUZZER_START : BUZZER_STOP;
	BUZZER_vChangeDutyCycle(u32BuzzerDutyCycle);
}
void RTE_vSetServoState(bool open)
{
	SERVO_trunk_pos pos = open ? OPEN : CLOSE;
	SERVO_vChangeAngle(pos);
}
void RTE_vMotorTest()
{
	static bool lastState = false;
    bool bState = COM_bGet_ButtonFanStatus();
    if(lastState == bState)
		return;

	RTE_vSetDCMotorSpeed(bState ? DC_MOTOR_LOW_SPEED : DC_MOTOR_STOP);
	lastState = bState;

	ESP_LOGI(TAG,"MOTOR IS %s", bState ? "ON" : "OFF");
}
