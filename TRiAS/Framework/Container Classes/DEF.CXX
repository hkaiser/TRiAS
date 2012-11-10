//	Implementation of Glockenspiel Container release 2.0,
//
//	Glockenspiel's Framework for managing objects
//
//	Copyright 1990 Glockenspiel Limited
//
//	Version 2.0		July 27th 1990
//
//	Tab stops in this file are at	4 * n + 1
//
//  def.cxx - Contains source for default compare and hashing functions
//-------------------------------------------------------------------------

// #include <afx.h>

#include "contpre.hxx"
#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

int _DLLENTRY StrCmp (void * str1, void * str2)
{
	TX_ASSERT (TIsValidString((const char *)str1));
	TX_ASSERT (TIsValidString((const char *)str2));
	
return strcmp ((const char *)str1, (const char *)str2);
}

unsigned int _DLLENTRY StrHash (void * keystr)
{
	TX_ASSERT (TIsValidString((const char *)keystr));

unsigned int y = 0;
char * str = (char *) keystr;

	while (*str)
		y = y << 1 ^ *str++;

	return y;
}

int _DLLENTRY IntCmp (void * pint1, void * pint2)
{
	TX_ASSERT (TIsValidAddress(pint1, sizeof(int), false));
	TX_ASSERT (TIsValidAddress(pint2, sizeof(int), false));

int i1 = *(int *)pint1;
int i2 = *(int *)pint2;

	if (i1 > i2)
		return 1;
	else if (i1 < i2)
		return -1;
	else
		return 0;
}

unsigned int _DLLENTRY IntHash (void *pKeyint)
{
	TX_ASSERT (TIsValidAddress(pKeyint, sizeof(unsigned int), false));
	
	return *(unsigned int *)pKeyint;
}
