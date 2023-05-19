/***************************************************************
 * File Name :delay.c
 * Description: source file of delay driver
 * Author: Doha Eid Ali
 * Sec:1
 * BN:49
 *********************************************************/
#include"delay.h"

void Delay_us(uint32 us){
	for(uint32 i=0;i<us;i++);
}

