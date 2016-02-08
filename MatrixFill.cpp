#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MatrixFill.h"


extern unsigned char **Matrix;
extern FILE *fp;
void Fill(unsigned int n, // the power of 2

	// Note that for quarters without the hole, new hole will always be at the corner that are adjacent to the other
	//  quarters. Three holes of these no-hole quarters will need a simple base fill pattern at appropriate rotation.
			unsigned int hi, 	// vertical coordinates of the hole. < pow(2, n-1)
			unsigned int hj,	// horizontal coordinates of the hole    < pow(2, n-1)
	
			//The start filling position need to be updated as we go unsigned into each sub-quarters
			unsigned int si,  // vertical start position of that fill
			unsigned int sj  // horizontal start position of that fill
			)
{
	if (n==0)
	{
		exit(0);
	}
	else if (n==1)
	{
		if (hi == 0)
		{
			if (hj == 0) //0, 0
			{
	//			Matrix[0+si][0+sj] += 1;
				Matrix[0+si][1+sj] += 1;
				Matrix[1+si][0+sj] += 1;
				Matrix[1+si][1+sj] += 1;
				fprintf(fp, "%8d%8d%8d%8d\n", si, sj,hi, hj);

				// actual filling happens here. OX
				//								XX
			}
			else		//0, 1
			{
				Matrix[0+si][0+sj] += 1;
	//			Matrix[0+si][1+sj] += 1;
				Matrix[1+si][0+sj] += 1;
				Matrix[1+si][1+sj] += 1;
				fprintf(fp, "%8d%8d%8d%8d\n", si, sj,hi, hj);
				// actual filling happens here. XO
				//								XX
			}
		}
		else	//1,0
		{
			if (hj == 0)
			{
				Matrix[0+si][0+sj] += 1;
				Matrix[0+si][1+sj] += 1;
	//			Matrix[1+si][0+sj] += 1;
				Matrix[1+si][1+sj] += 1;
				fprintf(fp, "%8d%8d%8d%8d\n", si, sj,hi, hj);
				// actual filling happens here. XX
				//								OX
			}
			else // 1,1
			{
				Matrix[0+si][0+sj] += 1;
				Matrix[0+si][1+sj] += 1;
				Matrix[1+si][0+sj] += 1;
	//			Matrix[1+si][1+sj] += 1;
				fprintf(fp, "%8d%8d%8d%8d\n", si, sj,hi, hj);
				// actual filling happens here. XX
				//								XO
			}
		}		
		return;
	}
	else
	{
		if (hi>=1<<n || hj>=1<<n)
		{
			printf("hole position error. exit!\n");
			exit(0);
		}

		n=n-1;
		// Determine which quarter the hole locates. Note that the hole can be located at any position in that quarter.
		if (hj<1<<n) // hole is at left quarters
		{
			if (hi<1<<n) // hole is upper left quarter, case 1
			{	
				Fill(n, hi,       hj,       si,        sj       ); //upper left
				Fill(n, (1<<n)-1, 0,        si,        sj+(1<<n)); //upper right
				Fill(n, 0,        0,        si+(1<<n), sj+(1<<n)); //lower right
				Fill(n, 0,        (1<<n)-1, si+(1<<n), sj       ); //lower left
				
				//three new holes
				Fill(1, 0, 0, si+(1<<n)-1, sj+(1<<n)-1); 
				// actual filling happens here. OX
				//								XX
			}
			else // hole is lower left quarter, case 4
			{
				Fill(n, (1<<n)-1, (1<<n)-1, si,        sj       );//upper left
				Fill(n, (1<<n)-1, 0,        si,        sj+(1<<n));//upper right
				Fill(n, 0,        0,        si+(1<<n), sj+(1<<n));//lower right
				Fill(n, hi-(1<<n),hj,       si+(1<<n), sj       );//lower left
				
				//three new holes
				Fill(1, 1, 0, si+(1<<n)-1, sj+(1<<n)-1); 
				// actual filling happens here. XX
				//								OX
			}
		}
		else
		{
			if (hi<1<<n) // hole is upper right quarter, case 2
			{
				Fill(n, (1<<n)-1, (1<<n)-1, si,        sj       );//upper left
				Fill(n, hi,       hj-(1<<n),si,        sj+(1<<n));//upper right
				Fill(n, 0,        0,        si+(1<<n), sj+(1<<n));//lower right
				Fill(n, 0,        (1<<n)-1, si+(1<<n), sj       );//lower left
				
				//three new holes
				Fill(1, 0, 1, si+(1<<n)-1, sj+(1<<n)-1); 
				// actual filling happens here. XO
				//								XX
			}
			else // hole is lower right quarter, case 3
			{
				Fill(n, (1<<n)-1, (1<<n)-1, si,        sj       );//upper left
				Fill(n, (1<<n)-1, 0,        si,        sj+(1<<n));//upper right
				Fill(n, hi-(1<<n),hj-(1<<n),si+(1<<n), sj+(1<<n));//lower right
				Fill(n, 0,        (1<<n)-1, si+(1<<n), sj       );//lower left
				
				//three new holes
				Fill(1, 1, 1, si+(1<<n)-1, sj+(1<<n)-1); 
				// actual filling happens here. XX
				//								XO
			}
		}
	}
}

void MatirxFillingTesting(unsigned int n, unsigned int hi, unsigned int hj)
{
	unsigned int si, sj, M;
	char Filename[80], str[80];
	
	M = 1<<n;

	Matrix = (unsigned char **)malloc(M*sizeof(unsigned char *));
	if (NULL == Matrix)
	{
		printf("Memory allocation failed!\n");
		exit(-1);
	}
	for (unsigned int i=0; i<M; i++)
	{
		Matrix[i] = (unsigned char *)malloc(M*sizeof(unsigned char));
		if (NULL == Matrix[i])
		{
			printf("Memory allocation failed!\n");
			exit(-1);
		}
	}

	si = 0;
	sj = 0;

	strcpy(Filename,"FillLocation");
	sprintf(str, "%d", n);
	strcat(Filename,"_");
	strcat(Filename,str);
	sprintf(str, "%d", hi);
	strcat(Filename,"_");
	strcat(Filename,str);
	sprintf(str, "%d", hj);
	strcat(Filename,"_");
	strcat(Filename,str);
	strcat(Filename,".txt");

	fp=fopen(Filename,"w");

	if (!fp)
	{
		printf("File can't be open. exit!\n");
		exit(-1);
	}

	fprintf(fp, "Fill Template Location:\n");
	fprintf(fp, "    pos_v    pos_h    hole_v   hole_h \n");
	for (unsigned int i=0; i<M; i++)
		for (unsigned int j=0; j<M; j++)
			Matrix[i][j]=0;

	Fill(n,hi, hj, 0, 0);

	fprintf(fp, "\n\nFill Result:\n");
	for (unsigned int i=0; i<M; i++)
	{
		for (unsigned int j=0; j<M; j++)
		{
			fprintf(fp, "%2d", Matrix[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	for (unsigned int i=0; i<M; i++)
	{
		free(Matrix[i]);
	}
	free(Matrix); 
}

void MatrixFillingCheck(unsigned int n, bool cont, bool split, bool pattern, unsigned int si, unsigned int sj)
{
	if (n==1)
	{
		if (split)
		{
			if (pattern)
			{
				Matrix[0+si][0+sj] = 0;
				Matrix[0+si][1+sj] = 1;
				Matrix[1+si][0+sj] = 1;
				Matrix[1+si][1+sj] = 0;
			}
			else
			{
				Matrix[0+si][0+sj] = 1;
				Matrix[0+si][1+sj] = 0;
				Matrix[1+si][0+sj] = 0;
				Matrix[1+si][1+sj] = 1;
			}
		}
		else
		{
			if (pattern)
			{
				Matrix[0+si][0+sj] = 0;
				Matrix[0+si][1+sj] = 0;
				Matrix[1+si][0+sj] = 0;
				Matrix[1+si][1+sj] = 0;
			}
			else
			{
				Matrix[0+si][0+sj] = 1;
				Matrix[0+si][1+sj] = 1;
				Matrix[1+si][0+sj] = 1;
				Matrix[1+si][1+sj] = 1;
			}
		}
		return;
	}
	else
	{

		if (cont)
		{
			n--;
			MatrixFillingCheck(n, false, false, pattern, si, sj); // top left
			MatrixFillingCheck(n, false, true, (!pattern), si, sj+(1<<n)); // top right
			MatrixFillingCheck(n, false, true, (!pattern), si+(1<<n), sj); // bottom left
			MatrixFillingCheck(n, true, true, (!pattern), si+(1<<n), sj+(1<<n)); // bottom left
		}
		else
		{
			if (split)
			{
				if (pattern)
				{
					for (int i=0; i<1<<(n-1); i++)
					{
						for (int j=0; j<1<<(n-1); j++)
						{
							Matrix[i+si][j+sj] = 0;
						}
						for (int j=1<<(n-1); j<1<<n; j++)
						{
							Matrix[i+si][j+sj] = 1;
						}
					}
					for (int i=1<<(n-1); i<1<<(n); i++)
					{
						for (int j=0; j<1<<(n-1); j++)
						{
							Matrix[i+si][j+sj] = 1;
						}
						for (int j=1<<(n-1); j<1<<n; j++)
						{
							Matrix[i+si][j+sj] = 0;
						}
					}
				}
				else
				{
					for (int i=0; i<1<<(n-1); i++)
					{
						for (int j=0; j<1<<(n-1); j++)
						{
							Matrix[i+si][j+sj] = 1;
						}
						for (int j=1<<(n-1); j<1<<n; j++)
						{
							Matrix[i+si][j+sj] = 0;
						}
					}
					for (int i=1<<(n-1); i<1<<(n); i++)
					{
						for (int j=0; j<1<<(n-1); j++)
						{
							Matrix[i+si][j+sj] = 0;
						}
						for (int j=1<<(n-1); j<1<<n; j++)
						{
							Matrix[i+si][j+sj] = 1;
						}
					}
				}
			}
			else
			{
				if (pattern)
				{
					for (int i=0; i<(1<<n); i++)
					{
						for (int j=0; j<(1<<n); j++)
						{
							Matrix[i+si][j+sj] = 0;
						}
					}
				}
				else
				{
					for (int i=0; i<(1<<n); i++)
					{
						for (int j=0; j<(1<<n); j++)
						{
							Matrix[i+si][j+sj] = 1;
						}
					}
				}
			}
		}
	}
}
