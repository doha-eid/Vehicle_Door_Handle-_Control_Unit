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


	// active low

//	unlock
	uint8 push_button_handle_unlock = 0;
//	lock
	uint8 push_button_handle_lock = 1;

//	unlock
	uint8 push_button_door_unlock = 1;
//	lock
	uint8 push_button_door_lock = 0;

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
	Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, LOW);
	Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
	Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, LOW);

//	active low
	Gpio_WritePin(VEHICLE_PORT, pin_button_handle, push_button_handle_lock);
	Gpio_WritePin(VEHICLE_PORT, pin_button_door, push_button_door_lock);


while(1){

	uint8 handle_state = Gpio_ReadPin(VEHICLE_PORT,pin_button_handle);
	if (handle_state == 1){
		//	unlock
			push_button_handle_unlock = 1;
		//	lock
			push_button_handle_lock = 0;
	}
	else{
		//	unlock
			push_button_handle_unlock = 0;
		//	lock
			push_button_handle_unlock = 1;
	}

	uint8 door_state = Gpio_ReadPin(VEHICLE_PORT,pin_button_door);
	if (door_state == 1){
		//	unlock
			push_button_door_unlock = 1;
		//	lock
			push_button_door_lock = 0;
	}
	else{
		//	unlock
			push_button_door_lock = 0;
		//	lock
			push_button_door_unlock = 1;
	}

	uint8 unlock= door_unlock();
	uint8 open= door_open();
	uint8 anti= door_anti_theft();
	uint8 close= door_close();
	uint8 lock= door_lock();



		if(unlock){
			Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, HIGH);
			for(uint8 i=0; i<1; i++){
				Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, HIGH);
				Delay_us(500000);
				Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
		}
			Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, HIGH);
			Delay_us(2000000);
			Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, LOW);
		}

		else if(open){

			Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, LOW);
			Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
			Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, HIGH);
		}

		else if(anti){
			Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, LOW);
			for(uint8 i=0; i<2; i++){
				Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, HIGH);
				Delay_us(500000);
				Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
				Delay_us(500000);
		}
			Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, LOW);


		}

		else if(close){
			Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, LOW);
			Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
			Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, HIGH);
			Delay_us(1000000);
			Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, LOW);

		}

		else if(lock){
			Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, LOW);
			for(uint8 i=0; i<2; i++){
				Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, HIGH);
				Delay_us(500000);
				Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
				Delay_us(500000);
		}
			Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, LOW);
		}

		else {
			Gpio_WritePin(VEHICLE_PORT, pin_led_vehicle, LOW);
			Gpio_WritePin(VEHICLE_PORT, pin_led_hazard, LOW);
			Gpio_WritePin(VEHICLE_PORT, pin_led_Ambient, LOW);
		}
}
		return 0;
}

void Delay_us(uint32 us){
	for(uint32 i=0;i<us;i++);
}


uint8 door_unlock(){

	if(door_lock() && push_button_handle_unlock){
		return 1;
	}
	else{
		return 0;
	}

}

uint8 door_open(){

	if(door_unlock() && door_close() && push_button_door_unlock){
		return 1;
	}
	else{
		return 0;
	}

}

uint8 door_anti_theft(){

	if(door_unlock() && door_close()){

		for(uint32 i=0;i<10000000;i++){

			if(push_button_handle_lock && push_button_door_lock){

				return 1;
			}
			else{

				return 0;
			}
		}

	}
	else{
		return 0;
	}

}

uint8 door_close(){

	if(door_unlock() && door_open() && push_button_door_lock){
		return 1;
	}
	else{
		return 0;
	}

}

uint8 door_lock(){

	if(door_unlock() && door_open() && push_button_door_lock){
		return 1;
	}
	else{
		return 0;
	}

}

