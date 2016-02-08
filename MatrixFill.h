#ifndef __MATRIXFILL_H
#define __MATRIXFILL_H
//#define N	5
//#define M	32 // M=(1<<n)

void Fill(unsigned int n, // the power of 2
			// Note that for quarters without the hole, new hole will always be at the corner that are adjacent to the other
			//  quarters. Three holes of these no-hole quarters will need a simple base fill pattern at appropriate rotation.
			unsigned int hi, 	// vertical coordinates of the hole.
			unsigned int hj,	// horizontal coordinates of the hole
	
			//The start filling position need to be updated as we go unsigned into each sub-quarters
			unsigned int si,  // vertical start position of that fill
			unsigned int sj  // horizontal start position of that fill
			);

void MatirxFillingTesting(
		unsigned int n, // the power of 2
		unsigned int hi,// vertical coordinates of the hole. 
		unsigned int hj // horizontal coordinates of the hole
		);

void MatrixFillingCheck(unsigned int n, bool cont, bool split, bool pattern, unsigned int si, unsigned int sj);


#endif