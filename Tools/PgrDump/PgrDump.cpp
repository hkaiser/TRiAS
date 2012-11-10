// PgrDump.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <pgr.h>

#define min(x,y) (x) < (y) ? (x) : (y)
#define max(x,y) (x) > (y) ? (x) : (y)

int main(int argc, char* argv[])
{
	if (argc != 3)
		exit(0);

long lLevel = atol(argv[2]);

FILE *fp = fopen(argv[1], "rb");

	if (NULL == fp) {
		fprintf (stderr, "Could not open '%s' !", argv[1]);
		exit(0);
	}

long dwMagic = 0;

	fread (&dwMagic, sizeof(long), 1, fp);
	if (MAGIC_OLD_PGR == dwMagic) {
	PGRHEADEROLD hdr;

		fread(&hdr, sizeof(PGRHEADEROLD), 1, fp); 
		printf ("PGRHEADEROLD\n");
		printf ("Magic: %ld\n", hdr.iMagic1);
		printf ("Kacheln (X): %ld\n", hdr.iCountX);
		printf ("Kacheln (Y): %ld\n", hdr.iCountY);
		printf ("Gesamtcontainer (XMin, YMin, XMax, YMax): %lf, %lf, %lf, %lf\n", 
			hdr.dXMin, hdr.dYMin, hdr.dXMax, hdr.dYMax); 

		printf ("Berechnete Werte:\n");
		printf ("Gesamtgröße (X): %ld\n", hdr.iCountX * TILE_SIZE_X);
		printf ("Gesamtgröße (Y): %ld\n", hdr.iCountY * TILE_SIZE_Y);
	}
	else if (MAGIC_PGR == dwMagic) {
	PGRHEADER hdr;

		fread(&hdr, sizeof(PGRHEADER), 1, fp); 
		printf ("PGRHEADER\n");
		printf ("Magic: %ld\n", dwMagic);
		printf ("Gesamtgröße (X, Y): %ld, %ld\n", hdr.lSizeX, hdr.lSizeY);
		printf ("Gesamtcontainer (XMin, YMin, XMax, YMax): \n%lf, %lf, %lf, %lf\n", 
			hdr.dXMin, hdr.dYMin, hdr.dXMax, hdr.dYMax); 

	// erste Kachel lesen
	long lCount = 1;
	CMPKACHEL Tile;
	double dXMinT, dXMaxT, dYMinT, dYMaxT;

		fread (&Tile, sizeof(CMPKACHEL), 1, fp);
		dXMinT = Tile.dXMin;
		dYMinT = Tile.dYMin;
		dXMaxT = Tile.dXMax;
		dYMaxT = Tile.dYMax;

		printf ("\nBerechnete Werte:\n");
		printf ("Kachelgröße (X, Y): %f, %f\n", Tile.dXMax-Tile.dXMin, Tile.dYMax-Tile.dYMin);

	// alle anderen kacheln auch noch lesen
		do {
			if (1 != fread (&Tile, sizeof(CMPKACHEL), 1, fp))
				break;

			lCount++;
			dXMinT = min(dXMinT, Tile.dXMin);
			dYMinT = min(dYMinT, Tile.dYMin);
			dXMaxT = max(dXMaxT, Tile.dXMax);
			dYMaxT = max(dYMaxT, Tile.dYMax);
			 
		} while (true);

	long lSizeX = (long)((dXMaxT-dXMinT)/(Tile.dXMax-Tile.dXMin) * TILE_SIZE_X);
	long lSizeY = (long)((dYMaxT-dYMinT)/(Tile.dYMax-Tile.dYMin) * TILE_SIZE_Y);

		printf ("Gesamtgröße (X, Y): %ld, %ld\n", lSizeX, lSizeY);

		if (lLevel > 1) 
			printf ("Gesamtgröße Level 1 (X, Y): %ld, %ld\n", lSizeX << (lLevel-1), lSizeY << (lLevel-1));

		printf ("Gesamtcontainer (XMin, YMin, XMax, YMax): \n%lf, %lf, %lf, %lf\n", 
			dXMinT, dYMinT, dXMaxT, dYMaxT); 

	long lCountX = (long)((dXMaxT-dXMinT)/(Tile.dXMax-Tile.dXMin));
	long lCountY = (long)((dYMaxT-dYMinT)/(Tile.dYMax-Tile.dYMin));

		printf ("Kacheln (X, Y): %ld, %ld\n", lCountX, lCountY);
		printf ("Kachelanzahl: %ld, (%ld)\n", lCount, lCountX*lCountY);
	}

	printf("\n\n");
	fclose (fp);
	return 0;
}
