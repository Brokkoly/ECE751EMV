/*
* Final_Project.c
*
* Created: 10/24/2017 2:52:48 PM
*  Author: Brendan
*/

#include <io.h>
#include <arrayMath.h>
#include <math.h>
#include "testMain.h"
const long m = 3;
const long n = 3;
const long o = 4;
unsigned long x[m] = {0x01,0x00,0x80000000};
unsigned long y[n] = {0x00,0xFFFFFFFF,0x7FFFFFFF};


long z[o]= {0,0,0,0};
void test(void)
{
	const long m = 3;
	const long n = 3;
	const long o = 4;
	unsigned long x[m] = {0x01,0x00,0x80000000};
	unsigned long y[n] = {0x00,0xFFFFFFFF,0x7FFFFFFF};
	int i;
	add_arr(x,y,z,m,n,o);
	for(i = 0; i < o;i++){
		z[i] = 0;
	}
	sub_arr(x,y,z,m,n,o);
	for(i = 0; i < o;i++){
		z[i] = 0;
	}
	bitShiftRight(x,m);
	for(i = 0; i < o;i++){
		z[i] = 0;
	}
	bitShiftLeft(x,m);
	//mult_arr(z_mult,x_mult,y_mult,(int)m,(int)n);
	return;

	//while(1)
	//{
	//// Please write your application code here
	//
	//}
}