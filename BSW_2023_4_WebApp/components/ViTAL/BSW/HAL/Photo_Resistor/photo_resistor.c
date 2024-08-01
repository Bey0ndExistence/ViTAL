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
#include "BSW/HAL/Photo_Resistor/photo_resistor.h"

static const char* TAG = "PHOTO RESISTOR SENSOR";

uint16_t PHRES_u16Read(void)
{
    return ADC_u16Read();
}


