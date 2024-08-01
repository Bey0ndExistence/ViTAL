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

#include "BSW/HAL/Com/com.h"

#include "BSW/MCAL/WIFI/wifi.h"

static const char *TAG = "HAL COM";

extern char g_cGETBuffer[100];
extern char g_cPOSTBuffer[100];

extern bool g_bGETRequestInProcess;
extern bool g_bPOSTRequestInProcess;

/* Assign some default values to GET buffer */
COM_GET_struct g_GET_DataStructure =
{ .u8Temperature = 27, .u8Humidity = 50, .u8Comfort = 24, .bIsLocked = true,
		.bIsOccupied = false };

/* Assign some default values to POST buffer */
COM_POST_struct g_POST_DataStructure =
{ .bButtonFan = false, .bButtonTrunk = false, .bButtonHeadlights = false,
		.bButtonAmbientalLights = false, .bButtonFindMyCar = false,
		.bButtonHonk = false, .bButtonSecurity = false, .bButtonDoorLock = false,
		.u8UserTemperature = 27, .bButtonShiftReg = false, .bButtonRLed = false, .bButtonGLed = false, .bButtonBLed = false};

void COM_vProcessGetRequest(void)
{
	if (g_bGETRequestInProcess)
	{
		char dataBuffer[6];

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u8Temperature);
		/* First string to be copied to buffer */
		strcpy(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u8Humidity);
		strcat(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u8Comfort);
		strcat(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u16PhotoRes);
		strcat(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		if (g_GET_DataStructure.bIsLocked)
		{
			strcat(g_cGETBuffer, "locked\n");
		}
		else
		{
			strcat(g_cGETBuffer, "unlocked\n");
		}

		if (g_GET_DataStructure.bIsOccupied)
		{
			strcat(g_cGETBuffer, "occupied\n");
		}
		else
		{
			strcat(g_cGETBuffer, "unoccupied\n");
		}

		g_bGETRequestInProcess = false;
	}
}

void COM_vProcessPostRequest(void)
{
	if (g_bPOSTRequestInProcess)
	{
		if (strcmp(g_cPOSTBuffer, "button=Fan+On") == 0)
		{
			g_POST_DataStructure.bButtonFan = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=Fan+Off") == 0)
		{
			g_POST_DataStructure.bButtonFan = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Open+Trunk") == 0)
		{
			g_POST_DataStructure.bButtonTrunk = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=Close+Trunk") == 0)
		{
			g_POST_DataStructure.bButtonTrunk = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Head+Lights+On") == 0)
		{
			g_POST_DataStructure.bButtonHeadlights = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=Head+Lights+Off") == 0)
		{
			g_POST_DataStructure.bButtonHeadlights = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Ambiental+Lights+On") == 0)
		{
			g_POST_DataStructure.bButtonAmbientalLights = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=Ambiental+Lights+Off") == 0)
		{
			g_POST_DataStructure.bButtonAmbientalLights = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Find+My+Car") == 0)
		{
			g_POST_DataStructure.bButtonFindMyCar = true;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Honk") == 0)
		{
			g_POST_DataStructure.bButtonHonk = true;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Security+On") == 0)
		{
			g_POST_DataStructure.bButtonSecurity = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=Security+Off") == 0)
		{
			g_POST_DataStructure.bButtonSecurity = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=Unlock+Door") == 0)
		{
			g_POST_DataStructure.bButtonDoorLock = false;
		}
		else if (strcmp(g_cPOSTBuffer, "button=Lock+Door") == 0)
		{
			g_POST_DataStructure.bButtonDoorLock = true;
		}

		else if (strstr(g_cPOSTBuffer, "user-temp=") != NULL)
		{
			g_POST_DataStructure.u8UserTemperature = (g_cPOSTBuffer[10] - '0') * 10;
			g_POST_DataStructure.u8UserTemperature += g_cPOSTBuffer[11] - '0';
		}

		else if (strcmp(g_cPOSTBuffer, "button=Shift+Register+On") == 0)
		{
			g_POST_DataStructure.bButtonShiftReg = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=Shift+Register+Off") == 0)
		{
			g_POST_DataStructure.bButtonShiftReg = false;
		}

		else if (strcmp(g_cPOSTBuffer, "button=R+Led+On") == 0)
		{
			g_POST_DataStructure.bButtonRLed = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=R+Led+Off") == 0)
		{
			g_POST_DataStructure.bButtonRLed = false;
		}
		else if (strcmp(g_cPOSTBuffer, "button=G+Led+On") == 0)
		{
			g_POST_DataStructure.bButtonGLed = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=G+Led+Off") == 0)
		{
			g_POST_DataStructure.bButtonGLed = false;
		}
		else if (strcmp(g_cPOSTBuffer, "button=B+Led+On") == 0)
		{
			g_POST_DataStructure.bButtonBLed = true;
		}
		else if (strcmp(g_cPOSTBuffer, "button=B+Led+Off") == 0)
		{
			g_POST_DataStructure.bButtonBLed = false;
		}
		else
		{
			ESP_LOGI(TAG, "Not known");
		}

		g_bPOSTRequestInProcess = false;
	}
}

void COM_vTaskProcessServer(void)
{
	COM_vProcessGetRequest();
	COM_vProcessPostRequest();
}

bool COM_bGet_ButtonAmbientalLightsStatus(void)
{
	return g_POST_DataStructure.bButtonAmbientalLights;
}

bool COM_bGet_ButtonShiftRegStatus(void)
{
	return g_POST_DataStructure.bButtonShiftReg;
}

bool COM_bGet_ButtonRLedStatus(void)
{
	return g_POST_DataStructure.bButtonRLed;
}

bool COM_bGet_ButtonGLedStatus(void)
{
	return g_POST_DataStructure.bButtonGLed;
}

bool COM_bGet_ButtonBLedStatus(void)
{
	return g_POST_DataStructure.bButtonBLed;
}

bool COM_bGet_ButtonFanStatus(void)
{
	return g_POST_DataStructure.bButtonFan;
}
bool COM_bGet_ButtonTrunkStatus(void)
{
	return g_POST_DataStructure.bButtonTrunk;
}
bool COM_bGet_ButtonHeadlightsStatus(void)
{
	return g_POST_DataStructure.bButtonHeadlights;
}
bool COM_bGet_ButtonFindMyCarStatus(void)
{
	return g_POST_DataStructure.bButtonFindMyCar;
}
bool COM_bGet_ButtonHonkStatus(void)
{
	return g_POST_DataStructure.bButtonHonk;
}
bool COM_bGet_ButtonSecurityStatus(void)
{
	return g_POST_DataStructure.bButtonSecurity;
}
bool COM_bGet_ButtonDoorLockStatus(void)
{
	return g_POST_DataStructure.bButtonDoorLock;
}
uint8_t COM_bGet_UserTemperatureStatus(void)
{
	return g_POST_DataStructure.u8UserTemperature;
}

uint8_t COM_u8GetComfort(void)
{
	return g_GET_DataStructure.u8Comfort;
} 

uint8_t COM_vGetTemperature()
{
	return g_GET_DataStructure.u8Temperature;
} 

uint8_t COM_bGetHumidity()
{
	return g_GET_DataStructure.u8Humidity;
} 

bool COM_bGetIsOcupied()
{
	return g_GET_DataStructure.bIsOccupied;
} 

bool COM_bGetIsLocked()
{
	return g_GET_DataStructure.bIsLocked;
} 

uint16_t COM_vGetPhotoRes()
{
	return g_GET_DataStructure.u16PhotoRes;
} 


void COM_vSetTemperature(uint8_t temp)
{
	g_GET_DataStructure.u8Temperature = temp;
}
void COM_vSetHumidity(uint8_t humidity)
{
	g_GET_DataStructure.u8Humidity = humidity;
}
void COM_vSetComfort(uint8_t comfTemp)
{
	g_GET_DataStructure.u8Comfort = comfTemp;
}
void COM_vSetIsLocked(bool bState)
{
	g_GET_DataStructure.bIsLocked = bState;
}
void COM_vSetIsOccupied(bool bState)
{
	g_GET_DataStructure.bIsOccupied = bState;
}
void COM_vSetPhotoRes(uint16_t phr)
{
	g_GET_DataStructure.u16PhotoRes = phr;
}
void COM_vResetFindMyCarButton()
{
	g_POST_DataStructure.bButtonFindMyCar = false;
}
void COM_vResetHonkButton()
{
	g_POST_DataStructure.bButtonHonk = false;
}
