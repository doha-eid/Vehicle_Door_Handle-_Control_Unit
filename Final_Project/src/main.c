/******************************************************************************
 * File Name: main.c
 * Description: Source file of main function
 * Author: - Doha Eid
 *   	   - Amira Mohamed
 *   	   - Mayar Ehab
 *   	   - Mariam Ezzat
 ******************************************************************************/

/*******************************************************************************************
 * 											Includes										*
 ******************************************************************************************/
#include"main.h"
#include"Rcc.h"
#include "Gpio.h"
#include"Std_Types.h"

// variables

uint8 door_locked=1;
uint8 door_opened=0;
//uint8 push_button_handle;
//uint8 push_button_handle_unlock;
//uint8 push_button_door;
//uint8 push_button_door_lock;
	// active low

//	unlock

//	lock
//	uint8 push_button_handle_lock = 1;

//	unlock
//	uint8 push_button_door_unlock = 1;
//	lock


/*****************************Main Function*************************************/
int main (){
	Rcc_Init(); //Initialization of RCC
	Rcc_Enable(RCC_GPIOA); //Enable clock of port A


//	PIN CONFIGURATION

	Gpio_ConfigPin(VEHICLE_PORT, pin_led_vehicle, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_NO_PULL_UP_PULL_DOWN);
	Gpio_ConfigPin(VEHICLE_PORT, pin_led_hazard, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_NO_PULL_UP_PULL_DOWN);
	Gpio_ConfigPin(VEHICLE_PORT, pin_led_Ambient, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_NO_PULL_UP_PULL_DOWN);

	Gpio_ConfigPin(VEHICLE_PORT, pin_button_handle, GPIO_INPUT, GPIO_PUSH_PULL, GPIO_PULL_DOWN);
	Gpio_ConfigPin(VEHICLE_PORT, pin_button_door, GPIO_INPUT, GPIO_PUSH_PULL, GPIO_PULL_DOWN);

//pin default state

//	active high
//	Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, LOW);
//	Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
//	Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, LOW);

	uint8 push_button_handle_state = 0;
	uint8 push_button_handle_prev_state = 0;
	uint8 push_button_handle_is_pressed = 0;

	uint8 push_button_door_state = 0;
	uint8 push_button_door_prev_state = 0;
	uint8 push_button_door_is_pressed = 0;


while(1){
	//reading btn state
	push_button_handle_state = Gpio_ReadPin(VEHICLE_PORT,pin_button_handle);
	//check for falling edge
	if(push_button_handle_state == 0 && push_button_handle_prev_state == 1) {
		push_button_handle_is_pressed = 1;}
	//waiting for de-bouncing
	Delay_us(100000);
	//updating button previous state
	push_button_handle_prev_state = push_button_handle_state;
	//reading btn state
	push_button_door_state = Gpio_ReadPin(VEHICLE_PORT,pin_button_door);
	//check for falling edge
	if(push_button_door_state == 0 && push_button_door_prev_state == 1) {
		push_button_door_is_pressed = 1;}
	//waiting for de-bouncing
	Delay_us(100000);
	//updating button previous state
	push_button_door_prev_state = push_button_door_state;

	if(push_button_handle_is_pressed){
		if(is_door_opened()){
			door_is_open();
			push_button_handle_is_pressed=0;
		}
		else if(is_door_locked()){
			door_unlock();
			push_button_handle_is_pressed=0;
		}
		else{
			locking_the_door();
			push_button_handle_is_pressed=0;
		}
	}

	else if (push_button_door_is_pressed){
		if(is_door_locked()){
			default_state();
			push_button_door_is_pressed=0;
		}
		else if(!is_door_opened()){
			door_is_open();
			push_button_door_is_pressed=0;
		}
		else{
			closing_the_door();
			push_button_door_is_pressed=0;
		}
	}
//	else{
//		if(!is_door_locked() && !is_door_opened() ){
//			anti_theft_vehicle_lock();
//		}
//		else{ default_state();
//		}
//	}
}
return 0;
}


void Delay_us(uint32 us){
	for(uint32 i=0;i<us;i++);
}

uint8 is_door_opened(){
	if (door_opened){
		return 1;
	}
	else {
		return 0;
	}
}

uint8 is_door_locked(){
	if (door_locked){
		return 1;
	}
	else {
		return 0;
	}
}

void default_state(){
	door_locked=1;
	door_opened=0;
	Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, LOW);
	Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
	Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, LOW);


}

void door_unlock(){
	door_locked=0;
	door_opened=0;
	Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, HIGH);
	for(uint8 i=0; i<1; i++){
		Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, HIGH);
		Delay_us(500000);
		Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
		Delay_us(500000);
	}
	Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, HIGH);
	Delay_us(2000000);
	Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, LOW);
}

void door_is_open(){
	door_locked=0;
	door_opened=1;
	Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, LOW);
	Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
	Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, HIGH);
}

void anti_theft_vehicle_lock(){
	door_locked=1;
	door_opened=0;
	Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, LOW);
	for(uint8 i=0; i<2; i++){
		Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, HIGH);
		Delay_us(500000);
		Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
		Delay_us(500000);
	}
	Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, LOW);

}

void closing_the_door(){
	door_locked=0;
	door_opened=0;
	Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, LOW);
	Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
	Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, HIGH);
	Delay_us(1000000);
	Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, LOW);

}

void locking_the_door(){
	door_locked=1;
	door_opened=0;
	Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, LOW);
	for(uint8 i=0; i<2; i++){
		Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, HIGH);
		Delay_us(500000);
		Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
		Delay_us(500000);
	}
	Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, LOW);
}







