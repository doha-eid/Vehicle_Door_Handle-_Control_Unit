/******************************************************************************
 * File Name: Gpio.c
 * Description: Source file of Gpio driver
 * Author: - Doha Eid
 *   	   - Amira Mohamed
 *   	   - Mayar Ehab
 *   	   - Mariam Ezzat
 ******************************************************************************/
/*******************************************************************************************
 * 											Includes										*
 ******************************************************************************************/
#include "Gpio.h"
#include "Gpio_Private.h"
#include "../Lib/Utils.h"

/******************************************************************************************************
 *                                Functions Definitions                                               *
 ******************************************************************************************************/
/*
 * Service Name     : Gpio_ConfigPin
 * Parameters (in)  : - uint8 PortName
 * 					  - uint8 PinNum
 * 					  - uint8 PinMode
 * 					  - uint8 DefaultState
 * 					  - uint8 PUPD
 * Parameters (Out) : void
 * Description      :A function to initialize the GPIO registers with the needed initial values to support the
 * connected hardware actions
 */
void Gpio_ConfigPin(uint8 PortName, uint8 PinNum, uint8 PinMode,uint8 DefaultState,uint8 PUPD) {
	 switch (PortName) {
	    case GPIO_A:
	      GPIOA_MODER &= ~(0x03 << (PinNum * 2));
	      GPIOA_MODER |= (PinMode << (PinNum * 2));

	      if(PinMode == GPIO_OUTPUT){
	      GPIOA_OTYPER &= ~(0x01 << PinNum);
	      GPIOA_OTYPER |= (DefaultState << PinNum);
	      }
	      GPIOA_PUPDR &=~(0x03<<(PinNum*2));
		  GPIOA_PUPDR |=(PUPD<<PinNum);


	      break;
	    case GPIO_B:
	      GPIOB_MODER &= ~(0x03 << (PinNum * 2));
	      GPIOB_MODER |= (PinMode << (PinNum * 2));

	      if(PinMode == GPIO_OUTPUT){
	      GPIOB_OTYPER &= ~(0x01 << PinNum);
	      GPIOB_OTYPER |= (DefaultState << PinNum);
	      }
	      GPIOB_PUPDR &=~(0x03<<(PinNum*2));
		  GPIOB_PUPDR |=(PUPD<<PinNum);


	      break;
	    case GPIO_C:

		  GPIOC_MODER &= ~(0x03 << (PinNum * 2));
		  GPIOC_MODER |= (PinMode << (PinNum * 2));

	      if(PinMode == GPIO_OUTPUT){
	      GPIOC_OTYPER &= ~(0x01 << PinNum);
	      GPIOC_OTYPER |= (DefaultState << PinNum);}
	      GPIOC_PUPDR &=~(0x03<<(PinNum*2));
		  GPIOC_PUPDR |=(PUPD<<PinNum);


	      break;

	    case GPIO_D:

	  	  GPIOD_MODER &= ~(0x03 << (PinNum * 2));
	  	  GPIOD_MODER |= (PinMode << (PinNum * 2));

	      if(PinMode ==GPIO_OUTPUT){
	      GPIOD_OTYPER &= ~(0x01 << PinNum);
	      GPIOD_OTYPER |= (DefaultState << PinNum);}

	      GPIOD_PUPDR &=~(0x03<<(PinNum*2));
		  GPIOD_PUPDR |=(PUPD<<PinNum);
	      break;
	    default:
	      break;
  }
}

/*
 * Service Name     : Gpio_WritePin
 * Parameters (in)  : - uint8 PortName
 * 					  - uint8 PinNum
 * 					  - uint8 Data
 * Parameters (Out) : - uint8 OK
 * 					  - uint8 NOK
 * Description      :A function to set a value (1 or 0) to a specific pin.
 */
uint8  Gpio_WritePin(uint8 PortName, uint8 PinNum, uint8 Data) {

		uint8 pin_mode =0;


		 switch (PortName) {

		    case GPIO_A:
		    	pin_mode = (GPIOA_MODER & (0x03<<PinNum * 2))>> (PinNum * 2);
		      break;
		    case GPIO_B:
		    	pin_mode = (GPIOB_MODER &(0x03<<PinNum * 2))>> (PinNum * 2);

		      break;
		    case GPIO_C:
		    	pin_mode = (GPIOC_MODER &(0x03<<PinNum * 2))>> (PinNum * 2);
		      break;
		    case GPIO_D:
		    	pin_mode = ( GPIOD_MODER & (0x03 << PinNum * 2)) >> (PinNum * 2);
		      break;
		    default:
		      break;
		  }

	  if(pin_mode == GPIO_OUTPUT){

	  switch (PortName) {
	    case GPIO_A:
	      GPIOA_ODR &= ~(0x1 << PinNum);
	      GPIOA_ODR |= (Data << PinNum);
	      break;
	    case GPIO_B:
	      GPIOB_ODR &= ~(0x1 << PinNum);
	      GPIOB_ODR |= (Data << PinNum);
	      break;
	    case GPIO_C:
		  GPIOC_ODR &= ~(0x1 << PinNum);
		  GPIOC_ODR |= (Data << PinNum);
	      break;
	    case GPIO_D:
	  	  GPIOD_ODR &= ~(0x1 << PinNum);
	  	  GPIOD_ODR |= (Data << PinNum);
	      break;
	    default:
	      break;
	  }
	  return OK;}
	  else{
	return NOK;
	}

}
/*
 * Service Name     : Gpio_ReadPin
 * Parameters (in)  : - uint8 PortName
 * 					  - uint8 PinNum
 * Parameters (Out) : uint8 data
 * Description      :A function to return (1) if a falling edge is detected on the pin and (0) otherwise.
 */
uint8 Gpio_ReadPin(uint8 PortName , uint8 PinNum){
	uint8 Data=0;
	 switch (PortName) {
	    case GPIO_A:
	    	Data=(GPIOA_IDR &(0x1 << PinNum))>> PinNum;
	      break;
	    case GPIO_B:
	    	Data=(GPIOB_IDR &(0x1 << PinNum))>> PinNum;

	      break;
	    case GPIO_C:
	    	Data=(GPIOC_IDR &(0x1 << PinNum))>> PinNum;

	      break;
	    case GPIO_D:
	    	Data=(GPIOD_IDR &(0x1 << PinNum))>> PinNum;
	      break;
	    default:
	      break;
}
	 return Data;
}
