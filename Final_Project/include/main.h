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
#define pin_led_vehicle    0
#define pin_led_hazard     1
#define pin_led_Ambient    2

#define pin_button_handle  4
#define pin_button_door    5

/********************Functions Prototypes*******************/
uint8 is_door_opened();
uint8 is_door_locked();


void door_is_open();
void door_unlock();
void locking_the_door();
void closing_the_door();
void anti_theft_vehicle_lock();
void default_state();


void Delay_us(uint32 us);
#endif /* MAIN_H_ */
