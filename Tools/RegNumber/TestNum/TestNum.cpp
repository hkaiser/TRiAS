// TestNum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool IsInternalRegNumber (const char *pcRegEntry) 
{
char *pNext = NULL;
long lInit = strtol (pcRegEntry, &pNext, 10);
long l2nd = strtol (pNext+1, &pNext, 10);
long lNumber = strtol (pNext+1, &pNext, 10);

	return (100 == lInit && 0 == l2nd && 16670989L == lNumber);
}

bool IsDemoRegNumber (const char * pcRegEntry) 
{
char *pNext = NULL;
long lInit = strtol (pcRegEntry, &pNext, 10);
long l2nd = strtol (pNext+1, &pNext, 10);
long lNumber = strtol (pNext+1, &pNext, 10);

	return (1 == lInit && 0 == l2nd && 7621669L == lNumber);
}

bool IsLegalRegNumber (const char * pcRegEntry) 
{
char *pNext = NULL;
long lInit = strtol (pcRegEntry, &pNext, 10);

#if _MSC_VER >= 1200
	if (300 > lInit && !IsInternalRegNumber(pcRegEntry) && !IsDemoRegNumber(pcRegEntry))
		return false;
#endif // _MSC_VER >= 1200

long l2nd = strtol (pNext+1, &pNext, 10);
long lNumber = strtol (pNext+1, &pNext, 10);

	srand (230459L);
	for (long i = 0; i < lInit-2; i++) 
		rand();

long lStep = lInit / ((rand() % 93) + 7);	// teilen durch mind 7 und max 92
long lGroup = rand() % 1000;
long lResult = 0;

	if (lInit >= 500) {
	// für Werte über 500
		for (int j = 0; j <= l2nd; j += lStep)
			lResult = rand()*lGroup+rand();
		if (j != l2nd + lStep)
			return false;		// lStep muß auch stimmen
	} else {
	// für Werte zwischen 300 und 499
		for (int j = 0; j <= l2nd; j++)
			lResult = rand()*lGroup+rand();
	}
	return lResult == lNumber;
}

int main(int argc, char* argv[])
{
char cbBuffer[1024];

	while (NULL != fgets (cbBuffer, sizeof(cbBuffer), stdin)) {
		if (!isdigit (cbBuffer[0]))
			continue;

	int iLen = strlen(cbBuffer);

		if ('\n' == cbBuffer[iLen-1])
			cbBuffer[iLen-1] = '\0';

		if (IsLegalRegNumber (cbBuffer))
			printf ("%s: valid\n", cbBuffer);
		else
			printf ("%s: not valid\n", cbBuffer);
	}
	return 0;
}

