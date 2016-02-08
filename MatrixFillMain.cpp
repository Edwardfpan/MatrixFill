// Edward Pan, edwardfpan@yahoo.com
// For XXX Inc.

//1. Prove that any square of 2^n x 2^n, can be filled by patterns of the shape ## , ## ,  # , #   , with only one hole.
//                                                                              #     #   ##   ##   
// eg. when n=2, ####     n=3  ########
//               ####          # ######
//               # ##          ########
//               ####          ########
//                             ########
//                             ########
//                             ########
//                             ########
//
//2. Write a program, by giving 'n', and the location of the hole, 'Hole_h', 'Hole_v', to list the position of the filling patterns,
// and their orientation, such that the square 2^n x 2^n can be fully filled with the only hole at (Hole_h, Hole_v).

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "MatrixFill.h"

unsigned char **Matrix;
FILE *fp;

void main(int argc, char *argv[])
{
	int TwoSPower, Hole_h, Hole_v;
	switch (argc) {
		case 4:
			TwoSPower = atoi(argv[1]);
			Hole_h = atoi(argv[2]);
			Hole_v = atoi(argv[3]);
			break;
		default:
			printf("MatirxFillingTesting.exe TwoSPower Hole_h Hole_v\n");
			exit(1);
	}
	int M = (1<<TwoSPower) -1;

	if (TwoSPower<1)
	{
		printf("Square must be at least 2x2 !\n");
		exit(-1);
	}
	else if (Hole_v<0 || Hole_h<0 || Hole_v>M || Hole_h>M)
	{
		printf("Hole must be within the Square !\n");
		exit(-1);
	}
	else
	{
		MatirxFillingTesting(TwoSPower, Hole_v, Hole_h);
	}

}