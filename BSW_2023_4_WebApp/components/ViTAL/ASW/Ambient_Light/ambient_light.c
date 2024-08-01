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

#include "ASW/Ambient_Light/ambient_light.h"

static const char *TAG = "ASW AL";

void ASW_vTaskShiftRegControlTest(void)
{
	//if the button is pressed
	if (COM_bGet_ButtonShiftRegStatus())
	{
		int8_t i8Index = 1;
		uint8_t lastdata = 0;
		for (; i8Index <= 8; i8Index++)
		{
			lastdata = lastdata + (1 << i8Index);
			SHIFTREG_vOutput8Bits(lastdata); 
			vTaskDelay(100);
		}
	}
	else if(!COM_bGet_ButtonRLedStatus() && !COM_bGet_ButtonGLedStatus() && !COM_bGet_ButtonBLedStatus() && !COM_bGet_ButtonAmbientalLightsStatus())
	{
		RTE_vSetShiftRegisterOutput(ALL_COLORS, LOW);
	}
}

void ASW_vTaskRGBLedControlTest(void) // Interface command RGB buttons
{
	//if one of the buttons is pressed
	if(COM_bGet_ButtonAmbientalLightsStatus() || COM_bGet_ButtonShiftRegStatus())
	{
		RTE_vSetRGBLedState();
	}
}

void ASW_vAmbientLightCtrl(void)
{
	bool lightsOn = COM_bGet_ButtonAmbientalLightsStatus() && !COM_bGetIsLocked();
	RTE_vSetAmbientalLightsState(lightsOn);
	//ESP_LOGI(TAG,"Led status: %d", COM_bGet_ButtonAmbientalLightsStatus());
}