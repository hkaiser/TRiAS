// split.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

inline
long min(long x, long y)
{
	return (x < y) ? x : y;
}

inline 
unsigned char readnext(FILE *fp)
{
unsigned char c = 0;

	if (1 != fread(&c, sizeof(unsigned char), 1, fp))
		throw false;
	return c;
}

void copy_out (FILE *pIn, FILE *pOut, unsigned long lCount)
{
char cbBuffer[10000];
long lRead = 0;
unsigned long lCumulate = 0;

	do {
	long lToRead = min(lCount, sizeof(cbBuffer));

		lRead = fread (cbBuffer, 1, lToRead, pIn);
		lCount -= lRead;
		if (0 == lRead)
			break;

		fwrite (cbBuffer, 1, lRead, pOut);
		if (0 == lCount)
			break;

	} while (true);
}

void write_out (long iNum, FILE *fp, unsigned long lLast, int iOffset = 0)
{
unsigned long lCurr = ftell(fp)+iOffset;
char cbBuffer[255];

	sprintf(cbBuffer, "bild_%02d.cmp", iNum);

FILE *fpOut = fopen(cbBuffer, "wb+");

	fseek (fp, lLast, SEEK_SET);
	copy_out (fp, fpOut, lCurr-lLast-4);
	fclose (fpOut);
	fseek (fp, lCurr, SEEK_SET);	// wieder richtig positionieren
}

int main(int argc, char* argv[])
{
FILE *fp = fopen("maps.dat", "rb");
unsigned long lCnt = 0;
unsigned long last = 0;

	try {
	unsigned char c = 0;

		while (true) {
			if ('L' == readnext(fp) && 
				'E' == readnext(fp) &&
				'A' == readnext(fp) && 
				'D' == readnext(fp)) 
			{
				if (0 != lCnt) 
					write_out (lCnt, fp, last);
				
				last = ftell(fp)-4;
				++lCnt;
			}
		}
	} catch (...) {
		write_out (lCnt, fp, last, 4);
	}
	fclose (fp);
	printf("Anzahl der Bilder: %d\n", lCnt);
	return 0;
}

