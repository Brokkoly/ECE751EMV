/*
 * Final_Project.c
 *
 * Created: 10/24/2017 2:52:48 PM
 *  Author: Brendan
 */ 

#include <io.h>
#include <arrayMath.h>
#include <math.h>
static long m = 5;
static long n = 6;
int x[m] = {1,2,3,4,5};
int y[n] = {1,2,3,4,5,6};

int z[max(m,n)+1]= {0,0,0,0,0,0,0};
void main(void)
{
	add_arr(x,y,z,m,n);

	return;

    //while(1)
    //{
        //// Please write your application code here
		//
    //}
}