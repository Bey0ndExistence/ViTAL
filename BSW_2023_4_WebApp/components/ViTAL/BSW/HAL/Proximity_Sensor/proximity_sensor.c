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
#include "BSW/HAL/Proximity_Sensor/proximity_sensor.h"

static const char* TAG = "HAL PROXIMITY SENSOR";


//The sensor has a trigger pin (HC_SR04_TRIGGER_PIN) that,
// when set high for a short period (at least 10 microseconds), initiates the measurement process.
void PROX_vRequest()
{
    //This line sets the direction of the trigger pin to output,
    // allowing the microcontroller to control the pin’s voltage level.
    GPIO_vSetDirection(HC_SR04_TRIGGER_PIN, DIR_OUTPUT);

    //Sets the pin to a low state to ensure it starts from a known state.
	GPIO_vSetLevel(HC_SR04_TRIGGER_PIN, LOW_LEVEL);
    ets_delay_us(1);
    //sets the pin high.
	GPIO_vSetLevel(HC_SR04_TRIGGER_PIN, HIGH_LEVEL);
    // waits for 10 microseconds.
	ets_delay_us(10);
    //sets the pin low again.
    GPIO_vSetLevel(HC_SR04_TRIGGER_PIN, LOW_LEVEL);
}

uint16_t PROX_v16Read()
{   
    uint16_t distance = 0;
    
    //Upon receiving the trigger signal, the sensor emits an ultrasonic pulse at a frequency of 40 kHz.
    PROX_vRequest();

    // In this mode, the pin is used to read signals.
    GPIO_vSetDirection(HC_SR04_ECHO_PIN, DIR_INPUT);

    //The sensor then listens for the echo of this pulse, which reflects back from an object. 
    //The time it takes for the echo to return is proportional to the distance of the object.
    int time = 0;

    // Wait for the echo pin to go high (start of echo signal)
    while(GPIO_iGetLevel(HC_SR04_ECHO_PIN) == LOW_LEVEL);

    time = esp_timer_get_time(); // Record the start time

     // Wait for the echo pin to go low (end of echo signal)
    while(GPIO_iGetLevel(HC_SR04_ECHO_PIN) == HIGH_LEVEL);

      // Calculate the distance based on the time difference
    distance = (uint16_t)(esp_timer_get_time() - time) * 0.0343; //  converted from us to s (*10^-6), and from m to cm (*10^2)
    distance /= 2; // we only want the distance from the sensor to the object so we divide by 2
    ESP_LOGI(TAG, "Distanta: %d cm", distance);

    return distance;
}
