// StringEnumeratoren innerhalb von TRIAS -------------------------------------
// File ENUMFNAM.CXX

#include "triaspre.hxx"

#include <tchar.h>

#if defined(WIN32)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include "ienumstr.hxx"
#include "tenums.h"
#include "enumfnam.hxx"

extern ExtDirisWindow *CurrActDirisW;	// Hauptfenster

// Funktion, welche einen gewünschten Enumerator generiert und einen Pointer
// auf sein Interface liefert
extern "C" 
bool EXPORTTRIAS WINAPI CreateStringEnumerator (
		IEnumString **ppEnum, ENUMSTRINGTYPE eST, DWORD dwData) 
{
	if (ppEnum == NULL) return false;
	*ppEnum = NULL;

// Erzeugen der Klasse, die gewünschtes Interface implementiert hat
	switch (eST) {
	case ENUMSTRINGTYPE_FNAMES:	// alle DateiNamen einer OpenBox
		{
		CEnumFileNames *pEnum = CEnumFileNames :: CreateInstance ((char *)dwData, 0);
		
			if (pEnum != NULL) {
				pEnum -> QueryInterface (IID_IEnumString, (LPVOID *)ppEnum);
				pEnum -> Release();
			}
		}
		break;
		
	default:
		return false;	// sorry, not implemented
	}

return *ppEnum != NULL;
}


// Konkrete Enumeratoren ------------------------------------------------------
// Alle DateiNamen einer OpenFileBox ------------------------------------------
CEnumFileNames :: CEnumFileNames (void)
{
	// nothing else to do
}

CEnumFileNames :: ~CEnumFileNames (void)
{
	// nothing else to do
}

CEnumFileNames *CEnumFileNames :: CreateInstance (char *pDesc, DWORD dwFlags)
{
CEnumFileNames *pEnum = new CEnumFileNames();

	if (pEnum == NULL || !pEnum -> Init (pDesc, dwFlags)) {
		DELETE(pEnum);
		return NULL;
	}
	pEnum -> AddRef();

return pEnum;
}

bool CEnumFileNames :: Init (char *pDesc, DWORD dwFlags)
{
	if (!CImpIEnumStrings :: Init ()) 	// BasisKlasse initialisieren
		return false;

// MultiSelectOpenBox anzeigen
COpenDialog ODlg (CurrActDirisW, pDesc);

	ODlg.AddFlags (OFN_ALLOWMULTISELECT);
#if defined(WIN32)
	if (IsWin40())
	{
		ODlg.AddFlags (OFN_EXPLORER|OFN_LONGNAMES);
	} else 
#endif // WIN32
	{
	// SonderWünsche einstellen
		if (IsWinNT()) ODlg.AddFlags (OFN_LONGNAMES);
	}
	ODlg.Show();
	if (!ODlg.Result()) return false;

// DateiNamen in Array ablegen
short iLen = ODlg.GetFileNameLen();
char *pPath = new char [iLen +1];
char *pFName = new char [_MAX_PATH];
char *pRelName = new char [_MAX_PATH];

	if (pPath == NULL || pFName == NULL || pRelName == NULL) {
		DELETE (pPath);
		DELETE (pRelName);
		DELETE (pFName);
		return false;
	}
	ODlg.GetFileName (pPath, iLen);		// Eingabe abholen
	
char *pFPath = strtok (pPath, " ");
char *pFile = strtok (NULL, " ");

	while (pFile != NULL) {
		strcpy (pRelName, pFPath);
		strcat (pRelName, pFile);
		AddString (_fullpath (pFName, pRelName, _MAX_PATH));

		pFile = strtok (NULL, " ");	// nächster DateiName
	}
	DELETE (pPath);
	DELETE (pRelName);
	DELETE (pFName);
	
return true;
}


