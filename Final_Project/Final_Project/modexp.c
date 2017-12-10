#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int const k = 16; //number bits of M (k needs to be even?)
int const n = 8; //k/2
int const R2 = 256; //2^n
int const R1 = 256;
int const word = 32; //number of bits in a int variable
int const full = 0xFFFFFFFF; //used to mask the bits of a 32 bit variable
int const L = 16;	//number of bits of e
int const EMASK = 0x8000; //100 so the 1 is in the most significant bit of e
int const BMASK = 0x8000; //1 bit in the MSB of M so if k=8 BMASK = 128

int Inter(int b, int d, int M)
{
	int Z = 0;
	int i = 0;
	int I = 0;
	int bi = 0;
	int mask = BMASK;
	for(i = k-1; i >= 0; i--){	//i >= k/2
		Z = 2*Z;
		bi = mask & b;
		bi = bi>>i;

		I = bi * d;
		//printf("I: %d\n",I);
		Z = Z + I;
		if(Z >= M){
			Z = Z - M;
		}
		if(Z >= M){
			Z = Z - M;
		}
		//printf("Z: %d\nbi: %d\n",Z,bi);
		mask = mask>>1;
	}
	return Z;
}

int Mont(int xhat, int yhat, int M)
{
	int Z = 0;
	int i = 0;
	int I = 0;
	int yi = 0;
	int qm = 0;
	int mask = 1;
	//printf("Xhat: %d\nYhat: %d\n",xhat,yhat);
	for(i=0; i < n; i++){ //i < k/2
		yi = mask & yhat;
		I = yi * xhat;
		//printf("I: %d\n",I);
		Z = Z + I;
		qm = mask & Z;
		Z = Z + qm*M;
		Z = Z/2;
		if(Z >= M){
			Z = Z - M;
		}
		//printf("Z: %d\nyi: %d\n",Z,yi);
		yhat = yhat>>1;
	}

	return Z;
}

int BMM(int M, int T, int U, int sel, int RmM)
{
	int Z = 0;
	int Xhat = Inter(T,R2,M);
	unsigned int Yhat;
	if(!sel){
		Yhat = Inter(U,R2,M);
	}else{
		Yhat = U;
	}
	int maskH = full;
	maskH = maskH<<n;
	int YH = maskH & Yhat;
	YH = YH>>n;
	unsigned int shftAmnt = word - n; //32 - 4 + 2 will leave only the bottom bits for YL
	unsigned int YL = Yhat;
	YL = YL<<shftAmnt;
	YL = YL>>shftAmnt;

	int Ii = Inter(Xhat,YH,M);
	int Im = Mont(Xhat,YL,M);
	//printf("Ii: %d\nIm: %d\n",Ii,Im);
	Z = Ii + Im;
	Z = Inter(Z,1,M);

	return Z;
}

int expmod(int A, int e, int M)
{
	int C = 1;
	int l = L;
	//printf("l %d\n", l);
	int i = 0;
	int Z = 0;
	int RmM = Inter(R2,R2,M);			//R^2modM
	int Ahat = Inter(A,R2,M);		//(A*R)modM
	//printf("RmM: %d\nAhat: %d\n",RmM,Ahat);
	int mask = EMASK;
	int ei;
	for(i = l-1; i >= 0; i--){//should it be i>=n?
		Z = BMM(M,C,C,0,RmM);
		//printf("Zmid: %d\n", Z);
		C = Mont(Z,1,M);
		//printf("Cmid: %d\n",C);
		ei = mask & e;
		ei = ei>>i;
		//printf("ei: %d\n",ei);
		if(ei){ //if ei == 1
			Z = BMM(M,C,Ahat,1,RmM);
			C = Mont(Z,1,M);
		}
		//C = Z;
		//printf("C: %d\n", C);
		mask = mask >> 1;
	}

	return C;
}

int main(int argc, char* argv[]) 
{
	if(argc != 5){
		printf("Wrong Arguments!: ./modexp A e M C_check\n");
		return 1;
	}
	/*if(sizeof(int) !=4 ){
		printf("size of int != 4: size: %ld\n",sizeof(int));
		return 1;
	}*/
	int A = atoi(argv[1]);
	int e = atoi(argv[2]);
	int M = atoi(argv[3]);
	int C_check = atoi(argv[4]);
	printf("A = %d, e = %d M = %d\n",A,e,M);
	printf("A = %x, e = %x M = %x\n",A,e,M);
	int C = expmod(A,e,M);
	//int C_check;
	//C_check = pow(A,e);
	//C_check = C_check%M;
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