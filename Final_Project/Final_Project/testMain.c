/*
* Final_Project.c
*
* Created: 10/24/2017 2:52:48 PM
*  Author: Brendan
*/

//#include <io.h>

#include <math.h>
#include "testMain.h"
#include <arrayMath.h>
// const long m = 3;
// const long n = 3;
// const long o = 4;
// unsigned long x[m] = {0x01,0x00,0x80000000};
// unsigned long y[n] = {0x00,0xFFFFFFFF,0x7FFFFFFF};


//long z[o]= {0,0,0,0};

void test(void)
{
	int i;
	struct IOUS X;
	struct IOUS Y;
	struct IOUS Z;
	X = createArr();
	X.arr[0] = 0x0F0F0F0F;
	X.arr[1] = 0x0F0F0F0F;
	Y = createArr();
	Y.arr[0] = 0xF0F0F0F0;
	Y.arr[1] = 0xF0F0F0F0;
	Z = createArr();
	add_arr(X,Y,Z);
	printf("Addition Result: Should be all F's: ");
	printArr(Z,"Z");
	
	freeArr(Y);
	printf("Copy Result: Should be all F's");
	Y = arrCopy(Z);
	Z.arr[0] = 0;
	printArr(Y,"Y copied Z");
	zeroArr(Z);
	printf("Zeroes Result: Should be all 0's: ");
	printArr(Z,"Z");
	X.arr[0] = 0x1;
	X.arr[1] = 0x0;
	Y.arr[0] = 0x0;
	Y.arr[1] = 0xFFFFFFFF;
	sub_arr(X,Y,Z);
	printf("subtraction Result: Should be 1: ");
	printArr(Z,"Z");

	printf("greaterThanorEqual Result: Should be 1: ");
	//printf("%c\n",greaterThanEqual(X,Y));
	if(greaterThanEqual(X,Y)){
		printf("%d\n",1);	
	}
	else{
		printf("%d\n",0);		
	}
	printf("greaterThanorEqual Result: Should be 0: ");
	if(greaterThanEqual(Y,X)){
		printf("%d\n",1);	
	}
	else{
		printf("%d\n",0);		
	}
	printf("Equal Result: Should be 0: ");
	if(equal(X,Y)){
		printf("%d\n",1);	
	}
	else{
		printf("%d\n",0);		
	}
	Y.arr[0] = 0x1;
	Y.arr[1] = 0x0;
	printf("Equal Result: Should be 1: ");
	if(equal(X,Y)){
		printf("%d\n",1);	
	}
	else{
		printf("%d\n",0);		
	}

	X.arr[0] = 0x55555555;
	X.arr[1] = 0x55555555;
	Y.arr[0] = ~0x55555555;
	Y.arr[1] = ~0x55555555;
	printf("bitwiseAnd Result: Should be 0: ");
	bitwiseAnd(X,Y,Z);
	printArr(Z,"Z");
	Y.arr[0] = 0x55555555;
	Y.arr[1] = 0x55555555;
	printf("bitwiseAnd Result: Should be all 5's: ");
	bitwiseAnd(X,Y,Z);
	printArr(Z,"Z");
	printf("arrToBool Result: Should be 1: ");
	if(arrToBool(X)){
		printf("%d\n",1);	
	}
	else{
		printf("%d\n",0);		
	}
	X.arr[0] = 0;
	X.arr[1] = 0;
	printf("arrToBool Result: Should be 0: ");
	if(arrToBool(X)){
		printf("%d\n",1);	
	}
	else{
		printf("%d\n",0);		
	}
	Z.arr[0] = 0x1;
	Z.arr[1] = 0;

	printf("bitShiftRight result should be 0 80000000: ");
	bitShiftRight(Z);
	printArr(Z,"Z");
	printf("bitShiftLeft result should be 1 0: ");
	bitShiftLeft(Z);
	printArr(Z,"Z");
	freeArr(Z);

	printf("no seg fault? Z.arr = %d\n",*Z.arr);
	printf("Null: %d\n",NULL);

	Z.arr[0] = 0;
	Z.arr[1] = 1;
	printf("bitShiftLeft result should be 1 0: ");
	bitShiftLeft(Z);
	printArr(Z,"Z");

	/*
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
	*/
	return;
	
	//while(1)
	//{
	//// Please write your application code here
	//
	//}
}