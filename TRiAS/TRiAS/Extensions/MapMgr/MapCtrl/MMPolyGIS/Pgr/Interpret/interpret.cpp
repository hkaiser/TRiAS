// interpret.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
FILE *fp = fopen("maps.pgr", "rb");

	fseek (fp, 0, SEEK_END);

long lSize = ftell(fp);

	fseek (fp, 0, SEEK_SET);

char *pBuffer = new char [lSize];

	fread (pBuffer, 1, lSize, fp);
	fclose (fp);
	return 0;
}

