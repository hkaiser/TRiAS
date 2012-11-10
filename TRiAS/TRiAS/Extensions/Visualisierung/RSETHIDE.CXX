// VisInfo rücksetzen ---------------------------------------------------------
// File: RSETHIDE.CXX

#include "visobjp.hxx"

#include <viserror.hxx>
#include <eieruhr.hxx>

#include "visobj.h"
#include "resetvis.h"
#include "visobj.hxx"		// Klasse für diese Erweiterung
#include "rsethide.hxx"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// externe Funktionen
DWORD BitsFromType (char *pType)
{
	if (NULL == pType)
		return 0;

// pType zeigt hier auf einen ':'
	TX_ASSERT(':' == *pType);
	switch (*(pType+1)) {
	case 'P': 
		return OTPunkt;
	case 'L': 
		return OTLinie;
	case 'F': 
		return OTFlaeche;
	case 'T': 
		return OTText;
	default:
		break;
	}
	return 0;
}

// Anzeigen des Dialogfensters ------------------------------------------------
bool CVisObjExtension::RemoveShowInfo (void)
{
CResetShowInfoDlg RSIDlg (MWind(), &RF(), GetIdentMCode (false, m_pActSight));

	if (RSIDlg.Init ()) {
		RSIDlg.Show (Centre);
		return RSIDlg.Result();
	}
	return false;
}

typedef struct tagHIDEDATA {
	long m_lMCode;
	short m_iIdBase;
	MultiSelListBox *m_lbIdents;
	char *m_pMWert;
} HIDEDATA;

inline
bool AddEntry (HIDEDATA *pRD, char cChar, LPCSTR pcOKS, LPCSTR pcKText, long lIdent)
{
char cbBuffer[_MAX_PATH];

	wsprintf (cbBuffer, "%s:%c:%s", pcOKS, cChar, pcKText);

// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen 
// in Klammern hintendran hängen
	if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
	char cbConnName[_MAX_PATH];
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);

		TX_ASSERT(NULL != hPr);
		if (NULL != DEX_GetDataSourceShortName (hPr, cbConnName)) {
			strcat (cbBuffer, " (");
			strcat (cbBuffer, cbConnName);
			strcat (cbBuffer, ")");
		}
	}
	
int iIndex = pRD -> m_lbIdents -> AddString (cbBuffer);

	pRD -> m_lbIdents -> SetItemData (iIndex, lIdent);		// Ident wird diesem LB-Eintrag zugeordnet
	return true;	// weitermachen
}

extern "C"
BOOL PASCAL _XTENSN_EXPORT ResetShowInfoIdentEx (long lIdent, DWORD dwType, void *pPtr)
{
// Identifikator überprüfen, ob Objekte anders Visualisiert sind
HIDEDATA *pHD = (HIDEDATA *)pPtr;
CVisObjExtension *pE = (CVisObjExtension *)g_pTE;

	if (!ReadTextMerkmal (TT_Identifikator, lIdent, pHD -> m_lMCode, pHD -> m_pMWert))
		return true;	// Ident ist nicht visualisiert

// auf zu behandelnde Objekttypen beschränken
	dwType &= GetObjectTypeBits(CVisObjExtension::StringToIdMode(pHD -> m_pMWert), OVModShow);

	if (0 != dwType) {
	// für diesen Identifikator KurzText besorgen
	PBDDATA pbdData;
	char KText[33];

		INITSTRUCT(pbdData, PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = lIdent;
		pbdData.pbdKText = KText;
		pbdData.pbdKTextLen = sizeof(KText) -1;
		pbdData.pbdLTextLen = 0;
		DEX_GetPBDData (pbdData);
		KText[32] = '\0';

	char outBuff[_MAX_PATH];

		ClassFromIdentX (lIdent, outBuff);
		if (dwType & OTPunkt) AddEntry (pHD, 'P', outBuff, pbdData.pbdKText, lIdent);
		if (dwType & OTLinie) AddEntry (pHD, 'L', outBuff, pbdData.pbdKText, lIdent);
		if (dwType & OTFlaeche) AddEntry (pHD, 'F', outBuff, pbdData.pbdKText, lIdent);
		if (dwType & OTText) AddEntry (pHD, 'T', outBuff, pbdData.pbdKText, lIdent);
	}
	return true;	// weitermachen
}

// Konstruktor/Destruktor -----------------------------------------------------
#pragma warning (disable: 4355)

CResetShowInfoDlg::CResetShowInfoDlg (pWindow pW, ResourceFile *pRF, long lMCode)
		   : DialogWindow (pW, ResID (RESETVISINFO, pRF)),
		     m_pbOKButton (this, IDOK),
		     m_lbIdents (this, IDL_RESETIDENTS),
		     m_ftToDo (this, IDT_LISTBOXTEXT),
		     m_lMCode (lMCode)
{
	SetCaption (ResString (ResID (IDS_RESETSHOWCAPTION, pRF), 50));
	m_ftToDo.SetText (ResString (ResID (IDS_RESETSHOWTEXT, pRF), 50));	

	m_pInBuff = NULL;
}

#pragma warning (default: 4355)

CResetShowInfoDlg::~CResetShowInfoDlg (void)
{
	DELETE_OBJ (m_pInBuff);
}


bool CResetShowInfoDlg::Init (void)
{
	if (m_lMCode == -1) return false;
	
	TX_TRY(m_pInBuff = new char [_MAX_PATH]);
	if (m_pInBuff == NULL) return false;
	
// ListBox füllen, dazu Identifikatoren dieser Sicht enumerieren lassen
ENUMTEXTKEYEX ETK;
HIDEDATA HD;
	
	HD.m_lMCode = m_lMCode;
	HD.m_iIdBase = DEX_GetIdBase();
	HD.m_lbIdents = &m_lbIdents;
	HD.m_pMWert = m_pInBuff;
	
	ETK.eKey = DEX_GetActiveSight (m_pInBuff);
	ETK.eFcn = (ENUMTEXTKEYEXPROC)ResetShowInfoIdentEx;
	ETK.ePtr = &HD;
	ETK.eData = (OTPunkt|OTLinie|OTFlaeche|OTText);
	DEX_EnumSightIdentsEx (ETK);	
	return true;
}

void _XTENSN_EXPORT CResetShowInfoDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (RemoveIdentShowInfo());
		break;
		
	case IDCANCEL:
		EndDlg (0);
		break;
		
	case IDB_RESETHELP:
		break;
	}
}

BOOL _XTENSN_EXPORT PASCAL ObjHideVisInfoEx (long lONr, DWORD, void *pData)
{
short Status = DEX_GetObjectStatus (lONr);

	if (Status != OSNormal && Status != OSModified) 
	// Objekt existiert nicht oder ist temporär
		return true;	// weitermachen

bool fFirst = false;

	return ((CVisObjExtension *)g_pTE) -> HandleHiddenFlag (lONr, true, fFirst);
}

// Abschließendes bearbeiten der Eingaben -------------------------------------
bool CResetShowInfoDlg::RemoveIdentShowInfo (void)
{
CEierUhr Wait (GetParent());
short iIndex = m_lbIdents.GetFirstSelected();
bool fOne = false;

	while (iIndex != -1) {
	// Merkmale an Objekten löschen
	long lIdent = m_lbIdents.GetItemData (iIndex);

		m_lbIdents.GetString (m_pInBuff, iIndex, _MAX_PATH);
		
	ENUMLONGKEYEX ELK;
	
		ELK.eKey = lIdent;
		ELK.eFcn = (ENUMLONGKEYEXPROC)ObjHideVisInfoEx;
		ELK.ePtr = NULL;
		ELK.eData = BitsFromType (strchr (m_pInBuff, ':'));

		if (!DEX_EnumIdentObjectsEx(ELK))
			break;		// Fehler o.ä.

	// Merkmal am Ident löschen/modifizieren
	CVisObjExtension *pE = (CVisObjExtension *)g_pTE;

		if (!pE -> AdjustIdentifier (lIdent, OVModShow, ELK.eData, false))
			return false;

	// nächster aktiver Eintrag
		iIndex = m_lbIdents.GetNextSelected();
		fOne = true;		// wenigstens einer
	}
	
return fOne;
}





