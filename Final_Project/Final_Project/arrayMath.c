/*
* arrayMath.c
*
* Created: 10/24/2017 2:55:31 PM
*  Author: Brendan
*/
#include "arrayMath.h"
#include <limits.h>


void mult_arr(unsigned short w[], unsigned short u[],
unsigned short v[], int m, int n) {//w = output

	unsigned int k, t;
	int i, j;

	for (i = 0; i < m; i++)
	w[i] = 0;

	for (j = 0; j < n; j++) {
		k = 0;
		for (i = 0; i < m; i++) {
			t = u[i]*v[j] + w[i + j] + k;
			w[i + j] = t;          // (I.e., t & 0xFFFF).
			k = t >> 16;
		}
		w[j + m] = k;
	}
	return;
}

//void mult_arr(unsigned long x[], unsigned long y, unsigned long z,	long m, long n){
	//unsigned long a,b;
	//long i,j;
	//for(i = 0; i < m; i++){
		//z[i] = 0;
//
	//}
//}

void add_arr(unsigned long* x, unsigned long* y, unsigned long* z, long m, long n){//m corresponds to x's length, n is y's
	long min;
	long i;
	unsigned long a,b;
	char carry = 0;
	char temp_carry = 0;
	long num_max = max(n,m);
	
	//#asm("cli")
	//SREG = (SREG&0xFE);//TODO: Note to self, figure out byte storage
	
	for(i = 0; i < num_max;i++){
		if(i > m-1){
			a = 0;
		a = x[i];		}
		else{

		}
		if(i > n-1){
			b = 0;
		}
		else{
			b = y[i];
		}
		//if(()))
		
		if((z[i]>0)&&(carry>ULONG_MAX-z[i])){
			temp_carry = 1;
		}
		else{
			temp_carry = 0;
		}
		z[i] += carry;
		carry = temp_carry;
		//if(!carry){
			//carry = SREG;
			//carry = carry&0x01;
		//}
		if((z[i] > 0)&&(a>ULONG_MAX-z[i])){
			carry = 1;
		}
		z[i] += a;
		if(z[i])
		//if(!carry){
			//carry = SREG;
			//carry = carry&0x01;
		//}
		if((z[i] > 0)&&(b>ULONG_MAX-z[i])){
			carry = 1;
		}
		z[i] += b;
		//if(!carry){
			//carry = SREG;
			//carry = carry&0x01;
		//}
	}
	z[num_max] = carry;
	//#asm("sti")
}

//void mult_arr(unsigned int x[], unsigned int y[], unsigned int z[], long m, long n){
//
//}