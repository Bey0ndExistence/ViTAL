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

#include "SRVL/SCHEDULER/scheduler.h"

#include "BSW/MCAL/ADC/adc.h"
#include "BSW/MCAL/GPIO/gpio.h"
#include "BSW/MCAL/PWM/pwm.h"
#include "BSW/MCAL/WIFI/wifi.h"

#include "RTE/rte.h"

#include "BSW/HAL/Com/com.h"
#include "ASW/Ambient_Light/ambient_light.h"
#include "ASW/Headlights/headlights.h"
#include "ASW/Security/security.h"
#include "ASW/Climate_Control_System/climate_control_system.h"
#include "ASW/Locking_System/locking_system.h"
#include "ASW/Trunk/trunk.h"
#include "ASW/Horn/horn.h"

#include "nvs_flash.h"


static const char *TAG = "SRVL SCHEDULER";
static httpd_handle_t server = NULL;

void SYSTEM_vInit(void)
{
    /* Call these functions only when specific HW parts are connected */
    
	//Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	/* Initialize All periferials */
	ADC_vInit();

	GPIO_vInit();

	PWM_vInit();
	
	WIFI_vInit(&server);
}

void vTask100ms(void)
{	
	/* Send and receive data to the HTML interface -- get and post functions*/
	COM_vTaskProcessServer();

	/* Call Shift register functionalty */
	//ASW_vTaskShiftRegControlTest();
}
 
void vTask200ms(void)
{
	SetAlarm();
}

void vTask500ms(void)
{
	//PORTBAGAJ
	OpenTrunk();

	LockSystem(); //USI

	Horn(); // CLAXON
	
	ControlAmbientTemperature();
	// Find my car
	FindMyCar();
}

void vTask800ms(void)
{
	ASW_vAmbientLightCtrl();
} 

void vTask1000ms(void)
{
	RTE_vPhotoResCalculate(); 
	HLT_vOpenHeadlights();

} 

void vTask2000ms(void)
{
	RTE_vIsOcupied();
} 

void vTask5000ms(void)
{
	RTE_vTempAndHumCalculate();
} 

void SYSTEM_vTaskScheduler(void)
{
	uint16_t u16TickCount = 0;

	while (1)
	{
		if (u16TickCount % TASK_100MS == 0)
		{
			vTask100ms();
			//ESP_LOGI(TAG," %d TICK 100ms", u16TickCount);
		}

		if (u16TickCount % TASK_200MS == 0)
		{
			vTask200ms();	
		}

		if (u16TickCount % TASK_500MS == 0)
		{
			vTask500ms();	
		}
		
		if (u16TickCount % TASK_800MS == 0)
		{
			vTask800ms();	
		}
		
		if (u16TickCount % TASK_1000MS == 0)
		{
			vTask1000ms();	
			//ESP_LOGI(TAG," %d TICK 1s", u16TickCount);
		}

		if (u16TickCount % TASK_2000MS == 0)
		{
			vTask2000ms();	
		}
		
		if (u16TickCount % TASK_5000MS == 0)
		{
			vTask5000ms();	
		}

		if (u16TickCount >= TASK_40000MS)
		{
			u16TickCount = 0;
		}
		u16TickCount++;
		vTaskDelay(TASK_LOOP_FREQ / 10/*/ 30*/); // 100 ms aprox
		// ESP_LOGI(TAG," %d TICK", u16TickCount);
	}
}
