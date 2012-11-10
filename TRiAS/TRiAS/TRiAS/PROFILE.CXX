// Memberfunktionen für Projekt- ProfileDatei ---------------------------------
// File: PROFILE.CXX

#include "triaspre.hxx"

#include <TRiASDB.h>

#include "Strings.h"
#include "profile.hxx"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if defined(_FORCE_LEGACY_CODE)

///////////////////////////////////////////////////////////////////////////////
// Verwaltung der Ansichten (Sight's) 
// Standard-Ansicht aus Profile-Datei holen
char *ProFile::GetStandardSight (void) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return NULL;

ResString RSight (IDS_SIGHTS, 13);
ResString Standard (IDS_STANDARD, SIGHTMENUITEM+1);
static char inString[SIGHTMENUITEM+3];

// ProfileString einlesen
	GetPrivateProfileString (RSight, Standard, "", inString, 
				 SIGHTMENUITEM+3, _FullName);

// In Windows Zeichensatz konvertieren
	OemToAnsi (inString, inString);
	return inString;
}

///////////////////////////////////////////////////////////////////////////////
// Standard-Ansicht in ProFile-Datei schreiben 
void ProFile::SetStandardSight (char *SightName) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return;

ResString RSight (IDS_SIGHTS, 13);
ResString Standard (IDS_STANDARD, SIGHTMENUITEM+1);
char OutString[SIGHTMENUITEM+3];

// in normalen Zeichensatz konvertieren
	if (SightName) {
	// wenn neue Ansicht gegeben ist
		strcpy (OutString, "\"");			// in '"' einpacken
		AnsiToOem (SightName, OutString+1);
		strcat (OutString, "\"");

	// ProFileString wegschreiben
		WritePrivateProfileString (RSight, Standard, OutString, _FullName);
	} else
	// Standard löschen
		WritePrivateProfileString (RSight, Standard, NULL, _FullName);
}

///////////////////////////////////////////////////////////////////////////////
// MerkmalsKodes, die Objektnamen enthalten 
long ProFile::GetObjNameCode (char *pOKS, bool *pfForceMCode) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return 0L;

ResString ObjName (IDS_OBJNAME, 13);
char IdKey[64];
char PString[64];

// für bestimmten Id liefern
	if (NULL != pfForceMCode) *pfForceMCode = false;
	if (pOKS != NULL) {
		strcpy (IdKey, ResString (IDS_PROFID, 3));
		strcat (IdKey, pOKS);
		if (0 == GetPrivateProfileString (ObjName, IdKey, "", PString, sizeof(PString)-1, _FullName)) {
		// soll ein MCode erzwungen werden
			strcpy (IdKey, g_cbIdForce);
			strcat (IdKey, pOKS);
			if (0 != GetPrivateProfileString (ObjName, IdKey, "", PString, sizeof(PString)-1, _FullName))
			{
				if (NULL != pfForceMCode) *pfForceMCode = true;
			}
		}
	} else
		PString[0] = '\0';

// wenn nichts da, dann Standard liefern
ResString Standard(IDS_STANDARD, 20);

	if (!strcmp (PString, ""))
		GetPrivateProfileString (ObjName, Standard, "", PString, sizeof(PString)-1, _FullName);

// wenn immer noch nichts da, dann 5100000 setzen und liefern
	if (!strcmp (PString, "")) {
		ltoa (51100000L, PString, 10);
		WritePrivateProfileString (ObjName, Standard, PString, _FullName);
	}
	return atol (PString);
}
#endif // defined(_FORCE_LEGACY_CODE)

///////////////////////////////////////////////////////////////////////////////
// Verwalten des letzten verwendeten Identifikators 
long ProFile::GetLastIdent (void)
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return 0L;

char cbBuffer[_MAX_PATH];

	GetPrivateProfileString (TEXT("Parameters"), TEXT("LastIdent"), TEXT(""), cbBuffer, sizeof(cbBuffer), _FullName);
	if (cbBuffer[0] == '\0') {
	// evtl. schon neuer Eintrag
		GetPrivateProfileString (TEXT("Parameters"), TEXT("LastOKS"), TEXT(""), cbBuffer, sizeof(cbBuffer), _FullName);
		if ('\0' == cbBuffer[0])
			return -1L;

	// Eintrag besteht aus 2 Teilen: LastOKS=Connection,OKS
	char *pT = strtok (cbBuffer, ",;");
	HPROJECT hPr = NULL;

		if (NULL != pT)		// connection wiederfinden
			hPr = FindConnection (pT);

		pT = strtok (NULL, ",;");
		if (NULL != pT && HACTCONNECTION != hPr) {
		IDENTFROMCLASS IFC;

			INITSTRUCT(IFC, IDENTFROMCLASS);
			IFC.pcClass = pT;
			IFC.fCreateNew = false;

		HRESULT hr = DEX_GetIdentFromClassEx(hPr, IFC);

			if (S_OK == hr)			// nur, wenn OKS wirklich existiert (S_FALSE: not exists)
				return IFC.ulIdent;
		}
		return -1L;		// nothing found
	}	
	return atol (cbBuffer);
}

DefineSmartInterface(TRiASProject);
DefineSmartInterface(TRiASConnections);
DefineSmartInterface(TRiASConnection);
DefineSmartInterface(TRiASDatabase);

HPROJECT ProFile::FindConnection (LPCSTR pcConnection)
{
// Anzahl der Connections feststellen
CComBSTR bstrActName;
HPROJECT hPr = NULL;

	USES_CONVERSION;
	COM_TRY {
	// alle Connections durchgehen und die gesuchte finden
	WTRiASProject Prj;

		if (!DEX_GetActiveProjectPtr (*Prj.ppi())) 
			_com_issue_error(E_UNEXPECTED);		// snh

	WTRiASConnections Conns;
	long lCnt = 0;

		THROW_FAILED_HRESULT(Prj -> get_Connections (Conns.ppi()));
		THROW_FAILED_HRESULT(Conns -> get_Count(&lCnt));

		for (long i = 1; i <= lCnt; i++) {
		CComVariant vIndex (i);
		WTRiASConnection Conn;

			THROW_FAILED_HRESULT(Conns -> Item (vIndex, Conn.ppi()));

		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened == rgStatus) {
			// geöffnet 
			CComBSTR bstrName;

				THROW_FAILED_HRESULT(Conn -> get_Name (CLEARED(&bstrName)));
				if (!strcmp (pcConnection, OLE2A(bstrName))) {
				// wenns die aktuelle ist, dann den Index speichern
				WTRiASDatabase DBase;
				INT_PTR lHandle = 0; 

					THROW_FAILED_HRESULT(Conn -> get_Database(DBase.ppi()));
					THROW_FAILED_HRESULT(DBase -> get_Handle (&lHandle));
					return reinterpret_cast<HPROJECT>(lHandle);
				}
			}
		}
	} COM_CATCH_RETURN(NULL);
	return NULL;
}

void ProFile::SetLastIdent (long lIdent)
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL) return;

// alten Eintrag erbarmungslos löschen
	WritePrivateProfileString (TEXT("Parameters"), TEXT("LastIdent"), NULL, _FullName);

// neuen Eintrag schreiben
HPROJECT hPr = DEX_GetObjectsProject (lIdent);
char cbBuffer[_MAX_PATH];

	if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
	char cbOKS[64];
	CLASSFROMIDENT CFI;

		INITSTRUCT(CFI, CLASSFROMIDENT);
		CFI.ulIdent = lIdent;
		CFI.pClass = cbOKS;
		CFI.iBuffLen = sizeof(cbOKS);
		cbOKS[0] = '\0';

		if (SUCCEEDED(DEX_GetClassFromIdentEx(hPr, CFI))) {
			strcat (cbBuffer, ",");
			strcat (cbBuffer, cbOKS);
			WritePrivateProfileString (TEXT("Parameters"), TEXT("LastOKS"), cbBuffer, _FullName);
		}
	}
}
 
 
