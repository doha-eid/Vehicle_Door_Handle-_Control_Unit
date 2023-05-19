/******************************************************************************
 * File Name: main.h
 * Description: Header file of main function
 * Author: - Doha Eid
 *   	   - Amira Mohamed
 *   	   - Mayar Ehab
 *   	   - Mariam Ezzat
 ******************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

/*******************************************************************************************
 * 											Includes										*
 ******************************************************************************************/
#include"Functions.h"

/************************Definitions************************/
#define VEHICLE_PORT	GPIO_A
#define pin_led_vehicle    1
#define pin_led_hazard     2
#define pin_led_Ambient    3

#define pin_button_handle  4
#define pin_button_door    5

/********************Functions Prototypes*******************/
uint8 default_state();
uint8 door_unlock();
uint8 door_lock();
uint8 door_open();
uint8 door_close();
uint8 door_anti_theft();
void Delay_us(uint32 us);
#endif /* MAIN_H_ */
