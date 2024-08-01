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

#ifndef COMPONENTS_VITAL_BSW_HAL_COM_H
#define COMPONENTS_VITAL_BSW_HAL_COM_H

#include "global.h"

typedef struct
{
	uint8_t u8Temperature;
	uint8_t u8Humidity;
	uint8_t u8Comfort;
	uint16_t u16PhotoRes;
	bool bIsLocked;
	bool bIsOccupied;
} COM_GET_struct;

typedef struct
{
	bool bButtonFan;
	bool bButtonTrunk;
	bool bButtonHeadlights;
	bool bButtonAmbientalLights;
	bool bButtonFindMyCar;
	bool bButtonHonk;
	bool bButtonSecurity;
	bool bButtonDoorLock;
	uint8_t u8UserTemperature;
	bool bButtonShiftReg;
	bool bButtonRLed;
	bool bButtonGLed;
	bool bButtonBLed;
} COM_POST_struct;

/*******************************************************************************
 *  Function name    : COM_vProcessGetRequest
 *
 *  Description      : Update the GET buffer
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void COM_vProcessGetRequest(void);

/*******************************************************************************
 *  Function name    : COM_vProcessPostRequest
 *
 *  Description      : Process the POST buffer
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void COM_vProcessPostRequest(void);

/*******************************************************************************
 *  Function name    : COM_vTaskProcessServer
 *
 *  Description      : Process POST/GET requests
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void COM_vTaskProcessServer(void);

// Getters
bool COM_bGet_ButtonFanStatus(void);

bool COM_bGet_ButtonTrunkStatus(void);

bool COM_bGet_ButtonHeadlightsStatus(void);

bool COM_bGet_ButtonFindMyCarStatus(void);

bool COM_bGet_ButtonHonkStatus(void);

bool COM_bGet_ButtonSecurityStatus(void);

bool COM_bGet_ButtonDoorLockStatus(void);

uint8_t COM_bGet_UserTemperatureStatus(void);

bool COM_bGet_ButtonAmbientalLightsStatus(void);
bool COM_bGet_ButtonShiftRegStatus(void);

bool COM_bGet_ButtonRLedStatus(void);
bool COM_bGet_ButtonGLedStatus(void);
bool COM_bGet_ButtonBLedStatus(void);

uint8_t COM_u8GetComfort();

uint8_t COM_vGetTemperature();

uint8_t COM_bGetHumidity();

uint16_t COM_vGetPhotoRes();

bool COM_bGetIsOcupied();

bool COM_bGetIsLocked();


// Setters
void COM_vSetTemperature(uint8_t temp);

void COM_vSetHumidity(uint8_t humidity);

void COM_vSetComfort(uint8_t comfTemp);

void COM_vSetIsLocked(bool bState);

void COM_vSetIsOccupied(bool bState);

void COM_vSetPhotoRes(uint16_t phr);

void COM_vResetFindMyCarButton();

void COM_vResetHonkButton();

#endif
