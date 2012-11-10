// Dialogfenster 'Import aus anderen Formaten' --------------------------------
// File: IMPORT.CXX

#include "triaspre.hxx"

#include "import.h"
#include "import.hxx"


// Funktion, die Import ausführt ----------------------------------------------
ErrCode GeoDB :: doImport (pWindow pW)
{
// Festellen, ob bereits eine Koordinatentransformation gegeben ist
HeaderEntry HE (*this, IDS_CTFHEADER);

// Fenster aufmachen
CImportParamDlg IPDlg (pW, *this);

	if (!IPDlg.Init (HE.EntryText())) 
		return WC_RETURN;	// InitialisierungsFehler
		
	IPDlg.Show();
	if (IPDlg.Result()) {
	char *pFormatDesc = IPDlg.GetFormatDesc();
	
		IPDlg.GenerateCoordSysEntries (HE);
		return EC_OKAY;	
	}

return EC_OKAY;
}


// KoordinatenSystemEinträge in GeoDBHeader generieren ------------------------
void CImportParamDlg :: GenerateCoordSysEntries (HeaderEntry &rHE)
{
// KoordinatenTransformations-DLL und weitere Parameter eintragen
char *pCTF = strtok (GetCoordSysDesc(), ",\n");
char *pKey = strtok (NULL, ":\n");

	rHE.SetEntryText (pCTF);
	rHE.WriteBack();			// CTF setzen
	
	while (pKey != NULL) {
	char *pHVal = strtok (NULL, ",\n");
	
		if (pHVal) {
		HeaderEntry HE (m_rDB, pKey, pHVal);

			HE.WriteBack();
		}
		pKey = strtok (NULL, ":\n");
	}
}


// Konstruktor/Destruktor -----------------------------------------------------
#pragma warning (disable:4355)

CImportParamDlg :: CImportParamDlg (pWindow pW, GeoDB &rDB)
		 : DialogWindow (pW, IMPORTDLG),
		   m_pbHelp (this, IDB_IMPORTHELP),
		   m_cbFormats (this, IDC_IMPORTFORMAT),
		   m_cbCoords (this, IDC_IMPORTCOORDSYS),
		   m_rDB (rDB)
{
	m_pbHelp.Disable();
	
	m_pFormat = NULL;
	m_pCoordSys = NULL;
}

#pragma warning (default:4355)

CImportParamDlg :: ~CImportParamDlg (void)
{
	DELETE (m_pFormat);
	DELETE (m_pCoordSys);
} 


BOOL CImportParamDlg :: Init (char *pInitCTF)
{
short iIndex;

	FillCBox (IDS_IMPORTFORMATS, m_cbFormats);
	if ((iIndex = FillCBox (IDS_COORDSYSTEMS, m_cbCoords, pInitCTF)) != -1) 
	{
		m_cbCoords.ChangeCurrentIndex (iIndex);
		m_cbCoords.Disable();
	}
	
return TRUE;
}


// EventHandler ---------------------------------------------------------------
void CImportParamDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		m_pFormat = ReadDesc (IDS_IMPORTFORMATS, m_cbFormats);
		m_pCoordSys = ReadDesc (IDS_COORDSYSTEMS, m_cbCoords);
		EndDlg (m_pFormat != NULL && m_pCoordSys != NULL);
		break;
			
	case IDCANCEL:
		EndDlg (0);
		break;	
		
	case IDB_IMPORTHELP:
		break;
	}
}



// sonstige Memberfunktionen --------------------------------------------------
short CImportParamDlg :: FillCBox (unsigned int uiRes, ComboBox &rCB, char *pInit)
{
ResString Ini (IDS_PROFILE, 15);
ResString Params (IDS_IRISPARS, 15);
ResString Topic (uiRes, 20);
char numTopic[30];

	strcpy (numTopic, ResString (IDS_NUMPREFIX, 5));
	strcat (numTopic, Topic.Addr());

// evtl. Erweiterungen laden
short iNums = GetPrivateProfileInt (Params, numTopic, 0, Ini);
short iIndex = -1;

	if (iNums > 0) {
	// wenn Einträge gegeben sind
	char *pNamesStr = new char [iNums*80+1];
	char **ppNames = new char *[iNums];

		if (pNamesStr == NULL || ppNames == NULL) {
			DELETE (pNamesStr);
			return (ErrCode)db_error (EC_NOMEMORY, RC_ImportDlgFillCBox);
		}
		GetPrivateProfileString (Topic, NULL, "", pNamesStr, iNums*80+1, Ini);
		ppNames[0] = pNamesStr;

	short len = 0;

		for (short i = 1; i < iNums; i++)
			ppNames[i] = &pNamesStr[len += strlen(ppNames[i-1])+1];

	// Füllen der entsprechenden ComboBox
	char *pInBuff = new char [80];

		if (pInit) strlwr (pInit);
		for (i = 0; i < iNums; i++) {
			rCB.AddString (ppNames[i]);
			if (pInit) {	// Voreinstellung
				if (!pInBuff) continue;

				GetPrivateProfileString (Topic, pInBuff, "", 
							 ppNames[i], 80, Ini);
				strlwr (pInBuff);
				if (!strncmp (pInBuff, pInit, strlen(pInit)))
					iIndex = i;
			}
		}
			
	// Speicher wieder freigeben             
		DELETE (pInBuff);
		DELETE (ppNames);
		DELETE (pNamesStr);
	}

return iIndex;
}


// Einlesen der BeschreibungsZeile für ein vorgebenes Topic -------------------
char *CImportParamDlg :: ReadDesc (unsigned int uiRes, ComboBox &rCB)
{
short iIndex = rCB.GetCurrentIndex();

	if (iIndex == -1) return NULL;	// nichts selektiert

char *pResult = new char [_MAX_PATH];

	if (pResult == NULL) {
		db_error (EC_NOMEMORY, RC_ImportDlgReadDesc);
		return NULL;
	}
	
ResString Ini (IDS_PROFILE, 15);
ResString Topic (uiRes, 20);
char inBuff[80];

	rCB.GetString (inBuff, iIndex, sizeof(inBuff));	
	GetPrivateProfileString (Topic, inBuff, "", pResult, _MAX_PATH, Ini);

return pResult;	
}
