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
#include "ASW/Headlights/headlights.h"
#include "RTE/rte.h"

static const char *TAG = "HEADLIGHTS";

bool HLT_vIsBrighterThan(uint16_t lumens)
{
    return lumens < PHRES_u16Read();
}

void HLT_vOpenHeadlights()
{
    static bool lastState = false;
    bool state = !HLT_vIsBrighterThan(X) && COM_bGet_ButtonHeadlightsStatus();
    if(lastState == state)
        return;

    RTE_vSetShiftRegisterOutput(HEAD_LIGHTS_POS, state);    
    lastState = state;
}