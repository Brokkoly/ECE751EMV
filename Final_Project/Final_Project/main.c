/*
 * Final_Project.c
 *
 * Created: 10/24/2017 2:52:48 PM
 *  Author: Brendan
 */ 

#include <io.h>
#include <arrayMath.h>
#include <math.h>
static long m = 2;
static long n = 1;
long x[m] = {0xFFFFFFFF,0xFFFFFFFF};
long y[n] = {0x1};


short x_mult[m] = {0xFFFF,0xFFFF};
short y_mult[n] = {0x10};
short z_mult[m+n] = {0,0,0};


long z[max(m,n)+1]= {0,0,0};
void main(void)
{
	add_arr(x,y,z,m,n);
	mult_arr(z_mult,x_mult,y_mult,(int)m,(int)n);
	return;

    //while(1)
    //{
        //// Please write your application code here
		//
    //}
}