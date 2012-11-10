// decodeini.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
FILE *fp = fopen ("pgrview.prv", "r");
FILE *fpOut = fopen ("pgrview.prv.txt.out", "w+");
char cbBuffer[200];

	while (NULL != fgets(cbBuffer, sizeof(cbBuffer), fp)) {
		for (char *pT = cbBuffer; '\n' != *pT && '\0' != *pT; ++pT) {
			if (0x20 == (*pT & 0xf0))
				*pT ^= (pT-cbBuffer) % 2 ? 0x70 : 0x5f;
			else if (0x30 == (*pT & 0xf0))
				*pT ^= (pT-cbBuffer) % 2 ? 0x50 : 0x5f;
			else if (0x40 == (*pT & 0xf0))
				*pT ^= (pT-cbBuffer) % 2 ? 0x30 : 0x1f;
			else if (0x50 == (*pT & 0xf0))
				*pT ^= (pT-cbBuffer) % 2 ? 0x70 : 0x1f;
			else if (0x60 == (*pT & 0xf0))
				*pT ^= (pT-cbBuffer) % 2 ? 0x50 : 0x5f;
			else if (0x70 == (*pT & 0xf0))
				*pT ^= (pT-cbBuffer) % 2 ? 0x30 : 0x5f;
		}
		fwrite(cbBuffer, (char *)pT-cbBuffer+1, sizeof(char), fpOut);
	}
	fclose (fp);
	fclose (fpOut);
	return 0;
}

