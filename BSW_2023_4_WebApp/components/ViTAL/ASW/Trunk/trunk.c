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
#include "ASW/Trunk/trunk.h"

static const char *TAG = "ASW TRUNK";

void OpenTrunk()
{
   
    static bool lastPos = false;
    bool pos = COM_bGet_ButtonTrunkStatus() && !COM_bGet_ButtonDoorLockStatus();
    if(lastPos == pos)
        return;

    if(pos){
        RTE_vSetServoState(pos);
        ets_delay_us(2000000);
        RTE_vSetServoState(!pos);
    }
        
    lastPos = pos;

    ESP_LOGI(TAG, "TRUNK %s", pos? "OPEN" : "CLOSE");
}