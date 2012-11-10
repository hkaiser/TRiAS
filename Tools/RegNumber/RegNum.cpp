#include <stdio.h>
#include <stdlib.h>

int iInit = 100;
int iSeed = 230459;

void main (int argc, char *argv[])
{
	if (argc < 2) {
		printf ("Verwendung: RegNum Startnummer [evtl. '> Ausgabedatei']\n");
		exit (1);
	}

	iInit = atol (argv[1]);
	if (iInit < 500 || iInit >= 1000) {
		printf ("RegNum: Die vorzugebenede Startnummer muﬂ im Bereich zwischen 500 und 1000 liegen!\n");
		exit (2);
	}

	srand (iSeed);
	for (int i = 0; i < iInit-2; i++) 
		rand();

int iStep = iInit / ((rand() % 93) + 7);	// teilen durch mind 7 und max 92
int iGroup = rand() % 1000;

	printf ("Reg.Nr\tKunde\tDatum\n");
	printf ("100-0000-16670989\tTRiAS GmbH Intern\t\n\n");

	for (int j = 0; j < 10000; j += iStep) 
		printf ("%03ld-%04ld-%08ld\t\t\n", iInit, j, rand()*iGroup+rand());
}

