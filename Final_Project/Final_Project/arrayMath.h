/*
 * arrayMath.h
 *
 * Created: 10/24/2017 2:55:45 PM
 *  Author: Brendan
 */ 
#ifndef ARRAYMATH_H_
#define ARRAYMATH_H_
//#include <math.h>
#include <stdlib.h>
#include "consts8.h"
#include <stdio.h>
//#include <io.h>

#define MSB 0x80000000
#define LSB 0x1
//#define SIZE 2
//#define SIZE 2
//#define ALF 0xFFFFFFFF
struct IOUS {//Integers of Unusual Size
	unsigned int* arr;
	int size;
};
void add_arr(struct IOUS x, struct IOUS y, struct IOUS z);
//void mult_arr(unsigned short w[], unsigned short u[],unsigned short v[], int m, int n);

void bitShiftRight(struct IOUS X);//rewrite to not be destructive
void bitShiftLeft(struct IOUS X);
char greaterThanEqual(struct IOUS X, struct IOUS Y);
void bitwiseAnd(struct IOUS X, struct IOUS Y,struct IOUS Z);

void sub_arr(struct IOUS x, struct IOUS y, struct IOUS z);
struct IOUS createArr();
void freeArr(struct IOUS X);
void zeroArr(struct IOUS X);
char arrToBool(struct IOUS X);
struct IOUS arrCopy(struct IOUS origin);
char equal(struct IOUS X, struct IOUS Y);
void printArr(struct IOUS toPrint,char* name);
//struct IOUS Inter(struct IOUS b, struct IOUS d, struct IOUS M);
#endif /* ARRAYMATH_H_ */