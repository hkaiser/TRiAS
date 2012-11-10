// readpgr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pgr.h"

int main(int argc, char* argv[])
{
FILE *fp = fopen("maps.pgr", "rb");
long dwMagic = ~0;
PGRHEADER hdr1;
PGRHEADEROLD hdr2;
int i = 0;

	fread(&dwMagic, 1, sizeof(long), fp);
	if (MAGIC_OLD_PGR == dwMagic) {
	CMPKACHELOLD cmp[50];

		fread(&hdr2, 1, sizeof(PGRHEADEROLD), fp);
		while (sizeof(CMPKACHELOLD) == fread(&cmp[i++], 1, sizeof(CMPKACHELOLD), fp) && i < 50)
				;
		fclose(fp);
	} else {
	CMPKACHEL cmp[50];
	
		fread(&hdr1, 1, sizeof(PGRHEADER), fp);
		while (sizeof(CMPKACHEL) == fread(&cmp[i++], 1, sizeof(CMPKACHEL), fp) && i < 50)
				;
		fclose(fp);
	}
	return 0;
}

