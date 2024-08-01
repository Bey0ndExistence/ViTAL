#include "BSW/HAL/Temp_Sensor/temp_sensor.h"

static const char *TAG = "HAL TEMP SENSOR";

static uint8_t u8Counter = 0;

float C[] = 
{
    -8.78469475556,
    1.61139411,
    2.33854883889,
    -0.14611605,
    -0.012308094,
    -0.0164248277778 ,
    0.002211732,
    0.00072546 ,
    -0.000003582 
};

/*******************************************************************************
 *  Function name    : DHT11_vRequest
 *
 *  Description      : Send pulse to activate the sensor
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void DHT11_vRequest(void)
{
	/* Set the direction to output for a new communication */
	GPIO_vSetDirection(DHT11_PIN, DIR_OUTPUT);

	/* H-L-H of at least 18ms */
	GPIO_vSetLevel(DHT11_PIN, HIGH_LEVEL);
	GPIO_vSetLevel(DHT11_PIN, LOW_LEVEL);
	ets_delay_us(20000);
	/* Set as input so 10k pull-up from circuit drives pin High */
	GPIO_vSetDirection(DHT11_PIN, DIR_INPUT);
}

/*******************************************************************************
 *  Function name    : DHT11_i8Response
 *
 *  Description      : See if the sensor got the pulse
 *
 *  List of arguments: -
 *
 *  Return value     : int8_t -> 0 - OK; -1 for TIMEOUT
 *
 *******************************************************************************/
int8_t DHT11_i8Response(void)
{
	u8Counter = 0;
	while (GPIO_iGetLevel(DHT11_PIN))
	{
		if (u8Counter >= DHT11_RESPONSE_START_US)
		{
			return DHT11_TIMEOUT;
		}
		u8Counter++;
		ets_delay_us(1);
	}

	u8Counter = 0;
	while (GPIO_iGetLevel(DHT11_PIN) == 0)
	{
		if (u8Counter >= DHT11_RESPONSE_LOW_US)
		{
			return DHT11_TIMEOUT;
		}
		u8Counter++;
		ets_delay_us(1);
	}

	u8Counter = 0;
	while (GPIO_iGetLevel(DHT11_PIN))
	{
		if (u8Counter >= DHT11_RESPONSE_HIGH_US)
		{
			return DHT11_TIMEOUT;
		}
		u8Counter++;
		ets_delay_us(1);
	}

	return DHT11_OK;
}

/*******************************************************************************
 *  Function name    : DHT11_i8Receive
 *
 *  Description      : Get 8 bits of data from the sensor
 *
 *  List of arguments: -
 *
 *  Return value     : int8_t -> Data received; -1 for TIMEOUT
 *
 *******************************************************************************/
int8_t DHT11_i8Receive(void)
{
	uint8_t u8Index = 0;
	/* Sensor measures data in the range of 0-50 degrees and 0-100(max) humidity
	 * so it is safe to type cast uint to int or int to uint */
	uint8_t u8Data = 0;

	for (; u8Index < 8; u8Index++)
	{
		/* Get the common 0 level for both 0 and 1 bits */
		u8Counter = 0;
		while (GPIO_iGetLevel(DHT11_PIN) == 0)
		{
			if (u8Counter >= DHT11_BIT_START_US)
			{
				return DHT11_TIMEOUT;
			}
			u8Counter++;
			ets_delay_us(1);
		}

		/* Measure the bit value */
		u8Counter = 0;
		while (GPIO_iGetLevel(DHT11_PIN))
		{
			/* Max time of bit */
			if (u8Counter >= DHT11_BIT_1_US)
			{
				{
					return DHT11_TIMEOUT;
				}
			}
			u8Counter++;
			ets_delay_us(1);
		}

		/* Time is greater than a 0 so it must be a one */
		if (u8Counter > DHT11_BIT_0_US)
		{
			u8Data = (u8Data << 1) | (0x01);
		}
		else
		{
			u8Data = (u8Data << 1);
		}
	}

	return (int8_t) u8Data;
}


/*******************************************************************************
 *  Function name    : DHT11_dht11Read
 *
 *  Description      : Makes a complete read operation from the sensor
 *
 *  List of arguments: -
 *
 *  Return value     : DHT11_struct
 *
 *******************************************************************************/
DHT11_struct DHT11_dht11Read()
{
	DHT11_struct info;

	DHT11_vRequest();
	if(DHT11_i8Response() != DHT11_TIMEOUT)
	{
		info.u8IntegralHum = DHT11_i8Receive();
		info.u8DecimalHum = DHT11_i8Receive(); 
		info.u8IntegralTemp = DHT11_i8Receive();
		info.u8DecimalTemp = DHT11_i8Receive();
		info.u8CheckSum = DHT11_i8Receive();
	}
	else
	{
		ESP_LOGI(TAG,"Timeout");
	}
	return info;
}

/*******************************************************************************
 *  Function name    : DHT11_vTaskTempAndHumCalculate()
 *
 *  Description      : Updates the COM_GET_struct structure with the temp and humidity values
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void DHT11_vTaskTempAndHumCalculate()
{
	DHT11_struct info = DHT11_dht11Read();
	if((info.u8IntegralHum + info.u8DecimalHum + info.u8IntegralTemp + info.u8DecimalTemp) != info.u8CheckSum)
	{
		ESP_LOGI(TAG,"Checksum gresit!");
	}
	else
	{
		COM_vSetTemperature(info.u8IntegralTemp);
		COM_vSetHumidity(info.u8IntegralHum);
		double T = info.u8IntegralTemp;
		double R = info.u8IntegralHum;
		double T2 = T * T;
		double R2 = R * R;
		double HI = C[0] + C[1]*T + C[2]*R + C[3]*T*R + C[4]*T2 + C[5]*R2 + C[6]*T2*R + C[7]*T*R2 + C[8]*T2*R2;
		COM_vSetComfort((uint8_t)(HI));
		ESP_LOGI(TAG,"Umiditatea este: %d %d",info.u8IntegralHum,info.u8DecimalHum);
		ESP_LOGI(TAG,"Temperatura este: %d %d",info.u8IntegralTemp,info.u8DecimalTemp);	
	}
}
