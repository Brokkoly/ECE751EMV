

.DEFAULT_GOAL := all


all : finalProject testMath modexp



finalProject: main.c inputs.c inputs.h arrayMath.c arrayMath.h consts.c consts.h
	gcc -o finalProject main.c inputs.c arrayMath.c consts.c -I.
testMath: testMainFile.c arrayMath.c arrayMath.h testMain.c testMain.h
	gcc -o testMath testMainFile.c arrayMath.c testMain.c -I.
modexp: modexp.c
	gcc -o modexp modexp.c -I. -lm



# TODO: add targets for building executables

.PHONY: clean
clean:
	rm -f finalProject testMath
