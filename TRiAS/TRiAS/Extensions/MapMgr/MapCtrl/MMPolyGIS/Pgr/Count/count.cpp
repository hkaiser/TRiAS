// count.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

inline 
unsigned char readnext(FILE *fp)
{
unsigned char c = 0;

	if (1 != fread(&c, sizeof(unsigned char), 1, fp))
		throw false;
	return c;
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
			unsigned long curr = ftell(fp)-4;

				if (0 == lCnt) 
					printf ("Bild %02d: Offset 0x%08x, ", lCnt, curr);
				else
					printf ("Größe 0x%08x (%d)\nBild %02d: Offset 0x%08x, ", curr-last, curr-last, lCnt, curr);
				
				last = ftell(fp)-4;
				++lCnt;
			}
		}
	} catch (...) {
		printf ("Größe 0x%08x (%d)\n", ftell(fp)-last, ftell(fp)-last);
	}
	fclose (fp);
	printf("Anzahl der Bilder: %d\n", lCnt);
	return 0;
}

