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
#include "ASW/Locking_System/locking_system.h"

static const char *TAG = "LOCKING SYSTEM";

void LockSystem(void)
{
    bool lock = COM_bGet_ButtonDoorLockStatus();
    COM_vSetIsLocked(lock);
}

