/*
 * arrayMath.h
 *
 * Created: 10/24/2017 2:55:45 PM
 *  Author: Brendan
 */ 
#ifndef ARRAYMATH_H_
#define ARRAYMATH_H_

#include <math.h>
#include <io.h>

#define MSB 0x80000000
#define LSB 0x1
//#define ALF 0xFFFFFFFF

void add_arr(unsigned long* x, unsigned long* y, unsigned long* z, long m, long n,long o);
void mult_arr(unsigned short w[], unsigned short u[],unsigned short v[], int m, int n);

void bitShiftRight(unsigned long* x, long m);
void bitShiftLeft(unsigned long* x, long m);

void sub_arr(unsigned long* x, unsigned long* y, unsigned long* z, long m, long n, long o);
#endif /* ARRAYMATH_H_ */