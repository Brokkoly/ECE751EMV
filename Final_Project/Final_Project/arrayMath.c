/*
* arrayMath.c
*
* Created: 10/24/2017 2:55:31 PM
*  Author: Brendan
*/
#include "arrayMath.h"
#include <io.h>


void add_arr(unsigned int* x, unsigned int* y, unsigned int* z, long m, long n){//m corresponds to x's length, n is y's
	long min;
	long i;
	if(m>n){
		min = n;
	}
	else {
		min = m;
	}
	//#asm("cli")
	SREG = (SREG&0xFE);//TODO: Note to self, figure out byte storage
	for(i = 0; i < min;i++){
		z[i] = (SREG&0x01)+x[i]+y[i];
	}
	z[min] = SREG&0x01;
	//#asm("sti")
}

void mult_arr(unsigned int x[], unsigned int y[], unsigned int z[], long m, long n){

}