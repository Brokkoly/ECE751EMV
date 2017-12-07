#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <exampleNums.h>
#include "arrayMath.h"


//long const SIZE = 512;
long const k = 8; //number bits of M (k needs to be even?)
long const n = 4; //k/2
long const R2 = 16; //2^n
long const R1 = 256;
long const word = SIZE*32; //number of bits in a long variable

//unsigned long const full = 0xFFFFFFFF; //used to mask the bits of a 32 bit variable
struct IOUS full;
int const L = 3;	//number of bits of e
//int const EMASK = 4; //100 so the 1 is in the most significant bit of e
struct IOUS EMASK;
struct IOUS BMASK;
//int const BMASK = 128; //1 bit in the MSB of M so if k=8 BMASK = 128




void setup(){
	
	int i;
	full = createArr();
	for(i = 0; i < full.size;i++){
		full.arr[i] = 0xFFFFFFFF;
	}
	EMASK = createArr();
	EMASK.arr[EMASK.size-1] = 4;
	
	BMASK= createArr();
	BMASK.arr[BMASK.size-1] = 128;
}



struct IOUS Inter(struct IOUS b, struct IOUS d, struct IOUS M)//
{
	
	struct IOUS Z = createArr();
	long i = 0;
	struct IOUS I = createArr();
	struct IOUS bi = createArr();
	struct IOUS mask = arrCopy(BMASK);
	long j = 0;
	struct IOUS temp;
	
	//
	for(i = k-1; i >= 0; i--){	//i >= k/2
		//Z = 2*Z;
		bitShiftLeft(Z);

		
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
		temp = arrCopy(Z);
		zeroArr(Z);
		add_arr(temp,d,Z);
		freeArr(temp);
		/*if(Z >= M){
		Z = Z - M;
		}
		if(Z >= M){
		Z = Z - M;
		}*/
		if(greaterThanEqual(Z,M)){
			temp = arrCopy(Z);
			zeroArr(Z);
			sub_arr(temp,M,Z);
			freeArr(temp);
		}
		if(greaterThanEqual(Z,M)){
			temp = arrCopy(Z);
			zeroArr(Z);
			sub_arr(temp,M,Z);
			freeArr(temp);
		}
		//printf("Z: %d\nbi: %d\n",Z,bi);
		//mask = mask>>1;
		bitShiftRight(mask);
	}
	freeArr(I);
	freeArr(bi);
	freeArr(mask);
	return Z;
}

struct IOUS Mont(struct IOUS xhat, struct IOUS yhat, struct IOUS M)
{
	//int Z = 0;//IOUS
	struct IOUS Z = createArr();
	int i = 0;
	//int I = 0;//IOUS
	struct IOUS I = createArr();
	//int yi = 0;//IOUS
	struct IOUS yi = createArr();
	//int qm = 0;//IOUS
	struct IOUS qm = createArr();
	//int mask = 1;
	struct IOUS mask = createArr();
	mask.arr[mask.size-1] = 1;
	struct IOUS temp;
	//printf("Xhat: %d\nYhat: %d\n",xhat,yhat);
	for(i=0; i < n; i++){ //i < k/2
		
		//yi = mask & yhat;
		bitwiseAnd(mask,yhat,yi);
		
		//I = yi * xhat;//
		if(arrToBool(yi)){
			freeArr(I);
			I = arrCopy(xhat);
		}
		//printf("I: %d\n",I);

		//Z = Z + I;//
		temp = arrCopy(Z);
		zeroArr(Z);
		add_arr(temp,I,Z);
		freeArr(temp);
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

int BMM(struct IOUS M,struct IOUS T,struct IOUS U, int sel, int RmM)
{
	int i;
	//int Z = 0;
	IOUS Z = createArr();
	//int Xhat = Inter(T,R2,M);
	IOUS Xhat = Inter(T,R2,M);
	//unsigned int Yhat;
	IOUS Yhat = createArr;
	if(!sel){
		Yhat = Inter(U,R2,M);
	}
	else{
		Yhat = U;
	}
	struct IOUS maskH = arrCopy(full);
	//maskH = maskH<<n;

	for(i = 0; i < n;i++){
		bitShiftLeft(maskH);
	}
	struct IOUS YH;
	//int YH = maskH & Yhat;
	bitwiseAnd(maskH,Yhat,YH);
	//YH = YH>>n;
	for(i = 0; i < n;i++){
		bitShiftRight(YH);
	}
	
	unsigned int shftAmnt = word - n; //32 - 4 + 2 will leave only the bottom bits for YL
	//unsigned int YL = Yhat;
	struct IOUS YL = arrCopy(Yhat);
	
	
	//YL = YL<<shftAmnt;
	//YL = YL>>shftAmnt;
	for(i = 0; i < shftAmnt;i++){
		bitShiftLeft(YL);
	}
	for(i = 0; i < shftAmnt;i++){
		bitShiftRight(YL);
	}

	struct IOUS Ii = Inter(Xhat,YH,M);
	struct IOUS Im = Mont(Xhat,YL,M);
	//printf("Ii: %d\nIm: %d\n",Ii,Im);
	//Z = Ii + Im;
	add_arr(Ii,Im,Z);
	Z = Inter(Z,1,M);

	return Z;
	freeArr(Ii);
	freeArr(Im);
	freeArr(YL);
	freeArr(Yhat);
	freeArr(YH);
	freeArr(Xhat);
	freeArr(maskH);
}

struct IOUS expmod(struct IOUS A, struct IOUS e, struct IOUS M)
{
	//int C = 1;
	struct IOUS C = createArr();
	C.arr[C.size-1]= 1;
	int l = L;
	//printf("l %d\n", l);
	int i = 0;
	int j = 0;
	struct IOUS cinput = createArr();
	cinput.arr[cinput.size=1]= 1;
	//int Z = 0;
	struct IOUS Z;
	struct IOUS RmM = Inter(R2,R2,M);			//R^2modM
	struct IOUS Ahat = Inter(A,R2,M);		//(A*R)modM
	//printf("RmM: %d\nAhat: %d\n",RmM,Ahat);
	struct IOUS mask = arrCopy(EMASK);
	//int ei;
	struct IOUS ei;// = createArr();
	for(i = l-1; i >= 0; i--){
		
		Z = BMM(M,C,C,0,RmM);
		//printf("Zmid: %d\n", Z);
		freeArr(C);
		C = Mont(Z,cinput,M);//
		zeroArr(cinput);
		cinput.arr[cinput.size-1] = 1;
		//printf("Cmid: %d\n",C);
		//ei = mask & e;
		ei = bitwiseAnd(mask,e);
		//ei = ei>>i;
		for(j = 0; j < i;j++){
			bitShiftRight(ei);
		}
		
		//printf("ei: %d\n",ei);
		/*if(ei){ //if ei == 1
			Z = BMM(M,C,Ahat,1,RmM);
			C = Mont(Z,1,M);
		}*/
		if(arrToBool(ei)){
			freeArr(Z);
			Z = BMM(M,C,Ahat,cinput,RmM);
			zeroArr(cinput);
			cinput.arr[cinput.size-1] = 1;
			zeroArr(C);
			C = Mont(Z,cinput,M);
		}
		//C = Z;
		//printf("C: %d\n", C);

		//mask = mask >> 1;
		bitShiftRight(mask);
		freeArr(Z);
	}

	return C;
}






int main(int argc, char* argv[])
{
	if(argc != 4){
		printf("Wrong Arguments!: ./modexp A e M\n");
		return 1;
	}


	setup();
	/*if(sizeof(int) !=4 ){
	printf("size of int != 4: size: %ld\n",sizeof(int));
	return 1;
	}*/





	int A = atoi(argv[1]);
	int e = atoi(argv[2]);
	int M = atoi(argv[3]);

	int C = expmod(A,e,M);
	int C_check;
	C_check = pow(A,e);
	C_check = C_check%M;
	if(C_check != C){
		printf("Wrong Output:\nGot: %d\nExpected: %d\n",C,C_check);
		printf("Are you sure M is an odd prime number?\nAre you sure the constants of bit sizes are set correctly?\n");
		}else{
		printf("Correct: C=%d\n",C);
	}
	/*int In;
	int Mt;
	In = Inter(A,e,M);
	Mt = Mont((A*R1)%M,(e*R1)%M,M);
	printf("Ahat: %d\n",(A*R2)%M);
	printf("ehat: %d\n",(e*R2)%M);
	printf("MontMid: %d\n", Mt);
	Mt = Mont(1,Mt,M);

	printf("Inter: %d\nMont: %d\n",In,Mt);*/

}