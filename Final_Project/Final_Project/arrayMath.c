/*
* arrayMath.c
*
* Created: 10/24/2017 2:55:31 PM
*  Author: Brendan
*/
#include "arrayMath.h"
#include <limits.h>

struct IOUS arrCopy(struct IOUS origin){
	struct IOUS retval;
	long i = 0;
	retval.size = origin.size;
	retval.arr = malloc(sizeof(unsigned long)*SIZE);
	for(i = 0; i < retval.size;i++){
		retval.arr[i] = origin.arr[i];
	}
	return retval;
}

void zeroArr(struct IOUS X){
	int i;
	for(i = 0; i < X.size;i++){
		X.arr[i]=0;
	}
}

void freeArr(struct IOUS X){
	free(X.arr);
}

struct IOUS createArr(){
	struct IOUS X;
	X.arr = malloc(SIZE*sizeof(unsigned long));
	X.size = SIZE;
	return X;
}

void bitShiftLeft(struct IOUS X){//assuming pre-pro done for making sure that x has or doesn't need an extra long added to the top
	unsigned long* x = X.arr;
	long m = X.size;
	int i;
	unsigned long temp1;//grabs msb
	unsigned long temp2;//previous msb
	for(i = m-1; i >= 0; i--){
		temp1 = x[i]&MSB;
		x[i] = x[i]<<1;
		temp2 = temp2>>31;
		x[i] = x[i]|temp2;
		temp2 = temp1;	
	}
}

void bitShiftRight(struct IOUS X){
	unsigned long* x = X.arr;
	long m = X.size;
	int i;
	unsigned long temp1;
	unsigned long temp2=0;
	//static long m = 2;
	//unsigned long x[m] = {0xFFFFFFFF,0x00};

	for(i = 0; i < m;i++){
		temp1 = x[i]&LSB;
		x[i] = x[i]>>1;
		temp2 = temp2<<31;
		x[i] = temp2|x[i];
		temp2 = temp1;
	}
}

/*
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
*/

void sub_arr(struct IOUS X, struct IOUS Y, struct IOUS Z){
	//x is larger number, x-y never negative;
	unsigned long* x = X.arr;
	unsigned long* y = Y.arr;
	unsigned long* z = Z.arr;
	long m = X.size;
	long n = Y.size;
	long o = Z.size;
	int i = 0;
	unsigned char borrow = 0;
	unsigned char borrowed = 0;
	unsigned long ALF = 0xFFFFFFFF;
	unsigned long temp;
	int xindex;
	int yindex;
	int zindex;
	for(i = 1; i < m;i++){
		xindex = n-i;
		yindex = m-i;
		zindex = o-i;
		z[zindex] = x[xindex];
		if(borrowed){
			if(z[zindex]==0){
				borrow = 1;
				z[zindex] = ALF;
			}
			else{
				z[zindex]-= 1;
			}
		}
		if(z[zindex] < y[yindex]){
			borrow = 1;
			temp = ALF - y[yindex];
			temp = temp + 1;
			temp = temp + z[zindex];
			z[zindex] = temp;
		}
		else{
			z[zindex]-= y[yindex];
		}
		borrowed = borrow;

	}
}

void add_arr(struct IOUS X, struct IOUS Y, struct IOUS Z){//m corresponds to x's length, n is y's
	
	unsigned long* x = X.arr;
	unsigned long* y = Y.arr;
	unsigned long* z = Z.arr;
	long m = X.size;
	long n = Y.size;
	long o = Z.size;
	long min;
	long i;
	unsigned long a,b;
	char carry = 0;
	char temp_carry = 0;
	long num_max = max(n,m);

	

	int xindex;
	int yindex;
	int zindex;
	//#asm("cli")
	//SREG = (SREG&0xFE);//TODO: Note to self, figure out byte storage
	
	for(i = 1; i <= num_max;i++){
		xindex = m-i;
		yindex = n-i;
		zindex = o-i;

		if(xindex < 0){
			a = 0;
		}
		else{
			a = x[xindex];
		}
		if(yindex < 0){
			b = 0;
		}
		else{
			b = y[yindex];
		}
		//if(()))
		
		if((z[zindex]>0)&&(carry>ULONG_MAX-z[zindex])){
			temp_carry = 1;
		}
		else{
			temp_carry = 0;
		}
		z[zindex] += carry;
		carry = temp_carry;
		//if(!carry){
		//carry = SREG;
		//carry = carry&0x01;
		//}
		if((z[zindex] > 0)&&(a>ULONG_MAX-z[zindex])){
			carry = 1;
		}
		z[zindex] += a;
		if(z[zindex])
		//if(!carry){
		//carry = SREG;
		//carry = carry&0x01;
		//}
		if((z[zindex] > 0)&&(b>ULONG_MAX-z[zindex])){
			carry = 1;
		}
		z[zindex] += b;
		//if(!carry){
		//carry = SREG;
		//carry = carry&0x01;
		//}
	}
	z[0] = carry;
	//#asm("sti")
}

char greaterThanEqual(struct IOUS X, struct IOUS Y){
	unsigned long* x = X.arr;
	unsigned long* y = Y.arr;

	int i = 0;
	char retval = 1;
	for(i = 0; i<X.size;i++){
		if(x[i] > y[i]){
			break;
		}
		else if(x[i]<y[i]){
			retval = 0;
			break;
		}
	}
	return retval



}
void bitwiseAnd(struct IOUS X, struct IOUS Y, struct IOUS Z){
	int i;
	for(i = 0; i < X.size;i++){
		Z.arr[i] = X.arr[i]&Y.arr[i];
	}
}
//void bitwiseAndOneLong(struct IOUS X, unsigned long y, )

char arrToBool(struct IOUS X){
	int i;
	for(i = 0; i < X.size;i++){
		if(X.arr[i]){
		return 1;
	}
	return 0;
}