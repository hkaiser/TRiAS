// DialogFenster zur Anzeige und Auswertung klassifizierter Merkmale 
// File: CLASSDLG.CXX

#include "featurep.hxx"
#include "feature.h"

#include <clipbrd.hxx>

#include "classdlg.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CClassifiedDlg *CClassifiedDlg :: CreateInstance (pWindow pW, ResID uiRes, 
			CUIdentObjects &rAllObjs, CUIdentObjects &rDupObjs,
			ULONG ulMCode)
{
CClassifiedDlg *pDlg = new CClassifiedDlg (pW, uiRes, rAllObjs, rDupObjs, ulMCode);

	if (NULL == pDlg || !pDlg -> FInit()) {
		DELETE(pDlg);
		return NULL;
	}

return pDlg;
}

#pragma warning (disable: 4355)

CClassifiedDlg :: CClassifiedDlg (pWindow pW, ResID uiRes, 
			CUIdentObjects &rAllObjs, CUIdentObjects &rDupObjs, 
			ULONG ulMCode)
		: DialogWindow (pW, uiRes),
		  m_pbShow (this, ID_SHOWOBJECTS),
		  m_mslFeatures (this, IDC_FEATURES),
		  m_rAllObjs (rAllObjs), m_rDupObjs (rDupObjs), m_ulMCode(ulMCode)
{
	m_pbShow.Disable();
}

#pragma warning (default: 4355)

CClassifiedDlg :: ~CClassifiedDlg (void)
{
}

bool CClassifiedDlg :: FInit (void)
{
CTable t(m_rAllObjs);
char cbBuffer[_MAX_PATH];

	for (t.First(); t.Valid(); t.Next()) {
	CObjUIdentLock l(t);

		TX_ASSERT(NULL != (CObjUIdent *)l);
		wsprintf (cbBuffer, "%04ld:%s", l -> Count(), l -> Text());
		m_mslFeatures.AddString (cbBuffer);
	}

return true;
}

void CClassifiedDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg(1);
		break;

	case IDCANCEL:
		EndDlg(0);
		break;

	case ID_SELECTALL:
		m_mslFeatures.ChangeSelected (Range (0, m_mslFeatures.GetCount() -1));
		AdjustButtons();
		break;

	case ID_SHOWOBJECTS:
		ShowObjects();
		break;

	case ID_COPYCLIP:
		CopyToClipBoard();
		break;
	}
}

void CClassifiedDlg :: ListBoxSel (ControlEvt)
{
	AdjustButtons();
}

bool CClassifiedDlg :: AdjustButtons (void)
{
	if (m_mslFeatures.GetNoSelected()) {
		m_pbShow.Enable();
		return true;
	} else {
		m_pbShow.Disable();
		return false;
	}
}

// Anzeigen der Objekte ausgewählter MerkmalsKlassen --------------------------
typedef struct tagFILLOBJS {
	LONG *pObjs;
	LONG lMaxIndex;
	LONG lIndex;
	LONG lCurrCnt;
} FILLOBJS;

bool FillObjs (CObjUIdent &rObj, void *pData)
{
FILLOBJS *pFO = (FILLOBJS *)pData;


	TX_ASSERT(ExtIsValidAddress(pData, sizeof(FILLOBJS), true));
	TX_ASSERT(pFO -> lIndex < pFO -> lMaxIndex);

	(pFO -> pObjs)[(pFO -> lIndex)++] = rObj.ObjNr();
	(pFO -> lCurrCnt)++;

return true;
}

bool CClassifiedDlg :: ShowObjects (void)
{
CEierUhr Wait (this);		// SandUhr anzeigen
char cbBuffer[_MAX_PATH+1];

// Anzahl der Objekte zählen
int iIndex = m_mslFeatures.GetFirstSelected();
LONG lObjCnt = 0;

	while (iIndex >= 0) {
	// einlesen des selektierten Eintrages
		m_mslFeatures.GetString (cbBuffer, iIndex, _MAX_PATH);

	char *pColon = strchr (cbBuffer, ':');

		TX_ASSERT(NULL != pColon);

		lObjCnt += m_rAllObjs.GetCount (pColon+1);
		iIndex = m_mslFeatures.GetNextSelected();	// nächster
	}
	TX_ASSERT(lObjCnt > 0);		// wirklich was gefunden

// Objektfeld zusammenstellen
FILLOBJS FO;

	FO.pObjs = new long [lObjCnt];
	FO.lMaxIndex = lObjCnt;
	FO.lIndex = 0;

	if (FO.pObjs == NULL) return false;

	iIndex = m_mslFeatures.GetFirstSelected();
	while (iIndex >= 0) {
	// einlesen des selektierten Eintrages
		m_mslFeatures.GetString (cbBuffer, iIndex, _MAX_PATH);
		
	char *pColon = strchr (cbBuffer, ':');

		TX_ASSERT(NULL != pColon);

		FO.lCurrCnt = 0;	// Zähler für dieses Merkmal

		m_rDupObjs.FEnumItems (pColon+1, FillObjs, &FO);
		if (FO.lCurrCnt == 0) 		// nicht im doppelten Baum
			m_rAllObjs.FEnumItems (pColon+1, FillObjs, &FO);
		
		TX_ASSERT(FO.lCurrCnt > 0);	// wiedergefunden ?
				
		iIndex = m_mslFeatures.GetNextSelected();	// nächster
	}
	TX_ASSERT(FO.lIndex <= lObjCnt);

// ORFenster mit Result aufbauen
// anstelle des IdentKurztextes soll das Merkmal angezeigt werden
	((CFeatureExtension *)g_pTE) -> GenerateObjWnd (
		(LONG)m_ulMCode, FO.pObjs, FO.lIndex, IDS_OBJCLUSTER);

	DELETE (FO.pObjs);

return true;
}

bool CClassifiedDlg :: CopyToClipBoard (void)
{
CEierUhr Wait (this);
string strCopy;
CTable t(m_rAllObjs);
char cbBuffer[_MAX_PATH];

	for (t.First(); t.Valid(); t.Next()) {
	CObjUIdentLock l(t);

		TX_ASSERT(NULL != (CObjUIdent *)l);
		wsprintf (cbBuffer, "%04ld\t%s\r\n", l -> Count(), l -> Text());
		strCopy += cbBuffer;
	}

// Ins Clipboard kopieren
	{
	CClipboard cbClip;

		cbClip.Insert (strCopy.c_str());
	}

return true;
}
