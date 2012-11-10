//---------------------------------------------------------------------
#include <stdafx.h>
// --------------------------------------------------------------------
char *ConvertFromNL (char *pText)
{
// KK000127
	if (pText == NULL || *pText == '\0') return NULL;

char *pNewText = new char [2 * strlen (pText) +1];

// alle abschließenden \r\n entfernen
char *pTmp = &pText[strlen (pText) -1];

	while ((*pTmp == '\n' || *pTmp == '\r') && pTmp >= pText)
		pTmp--;

	*(pTmp+1) = '\0';	// wegschneiden

// Umkopieren und dabei konvertieren
	pTmp = pNewText;
	if (pNewText) {
		while (*pText) {
			if (*pText == '\n') {
				if (*(pText+1)) {
					*pTmp++ = '\\';
					*pTmp++ = 'n';
				} else {
					pText++;
					continue;
				}
			} else if (*pText == 0x1A) {
				pText++;
				continue;
			} else if (*pText != '\r')
				*pTmp++ = *pText;

			pText++;
		}
		*pTmp = '\0';
	}

return pNewText;
}
//---------------------------------------------------------------------------------
char *ConvertToNL (char *pText)
{
	if (pText == NULL) return NULL;

char *pNewText = new char [strlen (pText) +3];
char *pTmp = pNewText;

	if (pNewText) {
		while (*pText) {
			if (*pText == '\\' && *(pText+1) == 'n') {
				*pTmp++ = '\r';
				*pTmp++ = '\n';
				pText += 2;
			} else
				*pTmp++ = *pText++;
		}
		*pTmp = '\0';
	}

return pNewText;
}
//------------------------------------------------------------------------------------

// --------------------------------------------------------------------
void ConvertKlammer (char *pText)
{

	if (pText == NULL) return;

	char *pBegin = strchr (pText,'"');
	if ( !pBegin) 
		return;
	pBegin ++;
	char *pTmp = &pText[strlen (pText) -1];

	if ( strchr(pBegin,'"') == pTmp)
		return;
	*pText = '\'';
	*pTmp = '\'';
	return;

}
//---------------------------------------------------------------------------------
