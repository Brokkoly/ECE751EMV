#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <exampleNums.h>
#include "arrayMath.h"
#include "inputs.h"

//int const SIZE = 512;
int const k = 16;//64; //number bits of M (k needs to be even?)
int const n = 8;//32; //k/2
//unsigned int const R2 = 4294967296; //2^n
struct IOUS R2;
int const R1 = 256;
int const word = SIZE*32; //number of bits in a IOUS variable

//unsigned int const full = 0xFFFFFFFF; //used to mask the bits of a 32 bit variable
struct IOUS full;
int const L = 16;	//number of bits of e
//int const EMASK = 4; //100 so the 1 is in the most significant bit of e
struct IOUS EMASK;
struct IOUS BMASK;
struct IOUS one;
//int const BMASK = 128; //1 bit in the MSB of M so if k=8 BMASK = 128


// void printArr(struct IOUS toPrint,char* name){
// 	int i;
// 	printf("Array %s: ",name);
// 	for(i=0;i<toPrint.size;i++){

// 		printf("%x ",toPrint.arr[i]);
// 	}
// 	printf("\n");

// }


void setup(){
	
	int i;
	full = createArr();
	//printf("Made it to line 32\n");
	for(i = 0; i < full.size;i++){
		full.arr[i] = 0xFFFFFFFF;
	}
	//printf("Made it to line 36\n");
	printArr(full,"full");
	EMASK = createArr();
	//EMASK.arr[EMASK.size-1] = 4;
	EMASK.arr[1]=0x8000;
	//printf("made it to line 39\n");
	printArr(EMASK,"EMASK");
	BMASK= createArr();
	//BMASK.arr[BMASK.size-1] = 128;
	BMASK.arr[1] = 0x8000;
	printArr(BMASK,"BMASK");
	R2 = createArr();
	R2.arr[1] = 256;//4294967295;
	R2.arr[0] = 0;
	//printf("made it to line 46\n");
	one = createArr();
	one.arr[1]=1;
	printArr(one,"one");
	//printf("setup fine\n");
	//printf("sizeof(unsigned int): %d\n",sizeof(unsigned int));
}



struct IOUS Inter(struct IOUS b, struct IOUS d, struct IOUS M)//
{
	struct IOUS Z;
	int i = 0;
	struct IOUS I;
	struct IOUS bi;
	struct IOUS mask;
	static char first = 1;
	int j = 0;
	struct IOUS temp;
	Z = createArr();
	I = createArr();
	bi = createArr();
	mask = arrCopy(BMASK);
	//printf("\n\nNEW ITERATION\n\n");
	//zeroArr(Z);
	//
	//printArr(mask,"mask");

	for(i = k-1; i >= 0; i--){	//i >= k/2
		//confirm i>=n
		//Z = 2*Z;
		bitShiftLeft(Z);

		if((first>16)&&(first<32)){
			printf("i = %d: ",i);
			printArr(Z,"Z@94");
		}
		
		//bi = mask & b;
		bitwiseAnd(mask,b,bi);
		//bi = bi>>i;
		for(j = 0; j < i;j++){
			bitShiftRight(bi);
		}
		//I = bi * d; solution:
		if(arrToBool(bi)){
			//Z = Z+d;
			temp = arrCopy(Z);
			zeroArr(Z);
			add_arr(temp,d,Z);
			freeArr(temp);
		}
		//printf("I: %d\n",I);
		//Z = Z + I;:
		/*
		temp = arrCopy(Z);
		zeroArr(Z);
		add_arr(temp,d,Z);
		freeArr(temp);
		*/
		/*if(Z >= M){
		Z = Z - M;
		}
		if(Z >= M){
		Z = Z - M;
		}*/

		

		if(greaterThanEqual(Z,M)){
			//printf("first greaterThanEqual\n");
			if((first>16)&&(first<32)){
				printArr(Z,"Z");
				printArr(M,"M");
			}
			temp = arrCopy(Z);
			zeroArr(Z);
			sub_arr(temp,M,Z);
			freeArr(temp);
			if((first>16)&&(first<32)){
				//first++;
				printArr(Z,"Z-M");
			}
		}
		if(greaterThanEqual(Z,M)){
			if((first>16)&&(first<32)){
				//printf("second greaterThanEqual\n");	
			}
			

			//printArr(Z,"Z");
			//printArr(M,"M");
			temp = arrCopy(Z);
			zeroArr(Z);
			sub_arr(temp,M,Z);
			freeArr(temp);
			//printArr(Z,"Z-M");
		}
		//printf("Z: %d\nbi: %d\n",Z,bi);
		//mask = mask>>1;
		bitShiftRight(mask);
		//first++;
	}
	freeArr(I);
	freeArr(bi);
	freeArr(mask);
	return Z;
}

struct IOUS Mont(struct IOUS xhat, struct IOUS yhat, struct IOUS M)
{

	//int Z = 0;//IOUS
	struct IOUS Z;
	int i = 0;
	//int I = 0;//IOUS
	struct IOUS I;
	//int yi = 0;//IOUS
	struct IOUS yi;
	//int qm = 0;//IOUS
	struct IOUS qm;
	//int mask = 1;
	struct IOUS mask;
	struct IOUS temp;
	//printf("Xhat: %d\nYhat: %d\n",xhat,yhat);
	printArr(xhat,"Xhat");
	printArr(yhat,"Yhat");
	Z = createArr();
	I = createArr();
	yi = createArr();
	qm = createArr();
	mask = createArr();
	mask.arr[mask.size-1] = 1;
	for(i=0; i < n; i++){ //i < k/2
		printf("\nMonti: %d\n\n",i);	
		//yi = mask & yhat;
		bitwiseAnd(mask,yhat,yi);
		
		//I = yi * xhat;//
		if(arrToBool(yi)){
			printArr(xhat,"Xhat");
			temp = arrCopy(Z);
			zeroArr(Z);
			add_arr(temp,xhat,Z);
			freeArr(temp);
		}
		//printf("I: %d\n",I);

		//Z = Z + I;//
		
		//qm = mask & Z;
		bitwiseAnd(mask,Z,qm);

		//Z = Z + qm*M;//same as other multiplication
		if(arrToBool(qm)){
			temp = arrCopy(Z);
			zeroArr(Z);
			add_arr(temp,M,Z);
			freeArr(temp);
		}
		//Z = Z/2;
		bitShiftRight(Z);

		//if(Z >= M){
		//Z = Z - M;
		//}
		if(greaterThanEqual(Z,M)){
			temp = arrCopy(Z);
			zeroArr(Z);
			sub_arr(temp,M,Z);
			freeArr(temp);
		}
		//printf("Z: %d\nyi: %d\n",Z,yi);
		//yhat = yhat>>1;
		bitShiftRight(yhat);
	}


	freeArr(I);
	freeArr(yi);
	freeArr(qm);
	freeArr(mask);
	return Z;
}

struct IOUS BMM(struct IOUS M,struct IOUS T,struct IOUS U, int sel, struct IOUS RmM)
{
	int i;
	struct IOUS Yhat;
	struct IOUS Z;
	struct IOUS Xhat;
	struct IOUS YL;
	struct IOUS YH;
	struct IOUS Ii;
	struct IOUS Im;
	struct IOUS maskH;
	struct IOUS localOne;
	unsigned int shftAmnt;
	//int Z = 0;
	Z = createArr();
	//int Xhat = Inter(T,R2,M);
	Xhat = Inter(T,R2,M);
	//printArr(Xhat,"Xhat");
	// printf("past BMMINTER\n");
	//unsigned int Yhat;
	//Yhat = createArr();
	if(!sel){
		Yhat = Inter(U,R2,M);
	}
	else{
		Yhat = arrCopy(U);
	}
	
	maskH = arrCopy(full);
	//maskH = maskH<<n;
	//printArr(maskH,"maskHbefore");
	for(i = 0; i < n;i++){
		bitShiftLeft(maskH);

	}
	//printArr(maskH,"maskHAfter");
	//printf("past BSL\n");
	//int YH = maskH & Yhat;
	YH = createArr();
	bitwiseAnd(maskH,Yhat,YH);
	//printArr(maskH,"maskH");
	//printArr(Yhat,"yhat");
	//printArr(YH,"YH");
	//YH = YH>>n;
	//printf("bastBand\n");
	for(i = 0; i < n;i++){
		bitShiftRight(YH);
	}
	
	//printf("past BSR\n");
	shftAmnt = word - n; //32 - 4 + 2 will leave only the bottom bits for YL
	//unsigned int YL = Yhat;
	YL = arrCopy(Yhat);
	
	
	//YL = YL<<shftAmnt;
	//YL = YL>>shftAmnt;
	//printArr(YL,"YLB");
	for(i = 0; i < shftAmnt;i++){
		bitShiftLeft(YL);
	}
	for(i = 0; i < shftAmnt;i++){
		bitShiftRight(YL);
	}
	//printArr(YL,"YLA");

	Ii = Inter(Xhat,YH,M);
	printf("past Ii\n");
	Im = Mont(Xhat,YL,M);
	//printf("past Ii/Im\n");
	//printf("Ii: %d\nIm: %d\n",Ii,Im);
	printArr(Ii,"Ii");
	printArr(Im,"Im");

	//Z = Ii + Im;
	add_arr(Ii,Im,Z);
	localOne = arrCopy(one);
	Z = Inter(Z,localOne,M);

	freeArr(Ii);
	freeArr(Im);
	freeArr(YL);
	freeArr(Yhat);
	freeArr(YH);
	freeArr(Xhat);
	freeArr(maskH);
	freeArr(localOne);
	return Z;
	
}

struct IOUS expmod(struct IOUS A, struct IOUS e, struct IOUS M)
{
	//int C = 1;
	int l = L;
	int i = 0;
	int j = 0;
	char freed = 0;
	struct IOUS cinput;
	struct IOUS C;
	struct IOUS mask;
	struct IOUS ei;
	struct IOUS Z;
	struct IOUS RmM;
	struct IOUS Ahat;
	//struct IOUS Zeroes;
	C = createArr();
	C.arr[C.size-1] = 1;
	
	printf("l: %d\n", l);
	printf("expmod init\n");
	cinput = arrCopy(one);
	//int Z = 0;
	
	RmM = Inter(R2,R2,M);			//R^2modM
	printArr(RmM,"RmM");
	//printf("finished Inter 1\n");
	Ahat = Inter(A,R2,M);		//(A*R)modM
	printArr(Ahat,"Ahat");
	//printf("finished inter 2\n");
	//printf("RmM: %d\nAhat: %d\n",RmM,Ahat);
	mask = arrCopy(EMASK);
	//printf("copied EMASK\n");
	//int ei;
	// = createArr();
	//Zeroes = createArr();
	ei = createArr();
	Z = createArr();
	for(i = l-1; i >=0; i--){
		//printf("In For Loop\n");
		//zeroArr(Zeroes);
		//printf("Zeroes\n");
		printf("\ni: %d\n\n",i);
		if(!freed){
			freeArr(Z);	
		}
		

		//printArr(M,"M");
		//printArr(C,"C");

		Z = BMM(M,C,C,0,RmM);
		freed = 0;
		//printf("past BMM1\n");
		//printf("Zmid: %d\n", Z);
		printArr(Z,"Zmid");
		freeArr(C);
		zeroArr(cinput);
		cinput.arr[cinput.size-1] = 1;
		C = Mont(Z,cinput,M);//
		//printf("past Mont1\n");
		zeroArr(cinput);
		cinput.arr[cinput.size-1] = 1;
		//printf("Cmid: %d\n",C);
		printArr(C,"Cmid");
		//ei = mask & e;
		zeroArr(ei);
		bitwiseAnd(mask,e,ei);
		//ei = ei>>i;
		for(j = 0; j < i;j++){
			bitShiftRight(ei);
		}
		//printf("past BSRei\n");
		//printf("ei: %d\n",ei);
		printArr(ei,"ei");
		/*if(ei){ //if ei == 1
		Z = BMM(M,C,Ahat,1,RmM);
		C = Mont(Z,1,M);
		}*/
		if(arrToBool(ei)){
			//printf("past arrToBool\n");
			freed = 1;
			freeArr(Z);
			freed = 0;
			//printf("past freeArr\n");
			Z = BMM(M,C,Ahat,1,RmM);
			//printf("past BMM\n");
			printArr(Z,"Z");
			zeroArr(cinput);
			cinput.arr[cinput.size-1] = 1;
			freeArr(C);
			C = Mont(Z,cinput,M);
		}
		//printf("past arrToBool\n");
		//C = Z;
		//printf("C: %d\n", C);
		printArr(C,"C");

		//mask = mask >> 1;
		//printArr(mask,"m");

		bitShiftRight(mask);
		//printf("past Bsr\n");
		if(!freed){
			freeArr(Z);
			freed = 1;
		}
		//printf("past free\n");
	}

	return C;
}






void main(int argc, char* argv[])
{
	
	struct IOUS A;
	struct IOUS e;
	int i;
	struct IOUS M;
	struct IOUS C;
	struct IOUS C_check;
	char breakpoint;
	/*
	if(argc != 4){
		printf("Wrong Arguments!: ./modexp A e M\n");
		return;
	}
	*/
	printf("Made it to line 353\n");
	setup();
	printf("finished Setup\n");
	/*if(sizeof(int) !=4 ){
	printf("size of int != 4: size: %ld\n",sizeof(int));
	return 1;
	}*/





	//int A = atoi(argv[1]);
	A = createArr();
	for(i = 0; i < A.size;i++){
		A.arr[i] = A_arr[i];
	}
	e = createArr();
	for(i = 0; i < e.size;i++){
		e.arr[i] = E_arr[i];
	}
	//int e = atoi(argv[2]);
	//int M = atoi(argv[3]);
	M = createArr();
	for(i = 0; i < M.size;i++){
		M.arr[i] = M_arr[i];
	}
	printf("Made A,E,M\n");
	C = expmod(A,e,M);
	printf("Finished C\n");
	C_check = createArr();
	for(i = 0; i < C_check.size;i++){
		C_check.arr[i] = C_arr[i];
	}
	
	printArr(A,"A");
	printArr(e,"e");
	printArr(M,"M");
	printArr(C,"C");
	printArr(C_check,"c");
	//C_check = pow(A,e);
	//C_check = C_check%M;
	if(!equal(C_check,C)){
		printf("Wrong Output:\nGot: %x,%x\nExpected: %x,%x\n",C.arr[0],C.arr[1],C_check.arr[0],C_check.arr[1]);
		printf("Are you sure M is an odd prime number?\nAre you sure the constants of bit sizes are set correctly?\n");
		breakpoint = 0;
	}
	else{
		printf("Correct: C=C_check\n");
		breakpoint = 1;
	}
	freeArr(A);
	freeArr(e);
	freeArr(M);
	freeArr(C);
	freeArr(C_check);
	/*int In;
	int Mt;
	In = Inter(A,e,M);
	Mt = Mont((A*R1)%M,(e*R1)%M,M);
	printf("Ahat: %d\n",(A*R2)%M);
	printf("ehat: %d\n",(e*R2)%M);
	printf("MontMid: %d\n", Mt);
	Mt = Mont(1,Mt,M);

	printf("Inter: %d\nMont: %d\n",In,Mt);*/
	return;

}