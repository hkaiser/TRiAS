// VisInfo rücksetzen ---------------------------------------------------------
// File: RESETVIS.CXX

#include "visobjp.hxx"

#include <viserror.hxx>
#include <eieruhr.hxx>

#include "visobj.h"
#include "resetvis.h"
#include "visobj.hxx"		// Klasse für diese Erweiterung
#include "resetvis.hxx"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Anzeigen des Dialogfensters 
bool CVisObjExtension :: RemoveVisInfo (void)
{
CResetVisInfoDlg RVIDlg (MWind(), &RF(), m_lObjVisMCode);

	if (RVIDlg.Init ()) {
		RVIDlg.Show (Centre);
		return RVIDlg.Result();
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Einträge einfügen
typedef struct tagRESETDATA {
	long m_lMCode;
	short m_iIdBase;
	MultiSelListBox *m_lbIdents;
} RESETDATA;

inline
bool AddEntry (RESETDATA *pRD, char cChar, LPCSTR pcOKS, LPCSTR pcKText)
{
char cbBuffer[_MAX_PATH];

	wsprintf (cbBuffer, "%s:%c:%s", pcOKS, cChar, pcKText);
	pRD -> m_lbIdents -> AddString (cbBuffer);
	return true;	// weitermachen
}

extern "C"
BOOL PASCAL _XTENSN_EXPORT ResetVisInfoIdentEx (long lIdent, DWORD dwType, void *pPtr)
{
// Identifikator überprüfen, ob Objekte anders Visualisiert sind
RESETDATA *pRD = (RESETDATA *)pPtr;
char cbBuffer[_MAX_PATH];

	if (!ReadTextMerkmal (TT_Identifikator, lIdent, pRD -> m_lMCode, cbBuffer))
		return true;	// Ident ist nicht visualisiert

// auf zu behandelnde Objekttypen beschränken
	dwType &= GetObjectTypeBits(CVisObjExtension::StringToIdMode(cbBuffer), OVModVisInfo);

	if (0 != dwType) {
	// für diesen Identifikator KurzText besorgen
	PBDDATA pbdData;
	char KText[33];

		KText[0] = '\0';		// für alle Fälle
			
		INITSTRUCT(pbdData, PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = lIdent;
		pbdData.pbdKText = KText;
		pbdData.pbdKTextLen = sizeof(KText) -1;
		pbdData.pbdLTextLen = 0;
		DEX_GetPBDData (pbdData);
		KText[32] = '\0';

	char outBuff[64];

		ClassFromIdentX (lIdent, outBuff);
		if (dwType & OTPunkt) AddEntry (pRD, 'P', outBuff, pbdData.pbdKText);
		if (dwType & OTLinie) AddEntry (pRD, 'L', outBuff, pbdData.pbdKText);
		if (dwType & OTFlaeche) AddEntry (pRD, 'F', outBuff, pbdData.pbdKText);
		if (dwType & OTText) AddEntry (pRD, 'T', outBuff, pbdData.pbdKText);
	}
	return true;
}

// Konstruktor/Destruktor -----------------------------------------------------
#pragma warning (disable: 4355)

CResetVisInfoDlg :: CResetVisInfoDlg (pWindow pW, ResourceFile *pRF, long lMCode)
		  : DialogWindow (pW, ResID (RESETVISINFO, pRF)),
		    m_pbOKButton (this, IDOK),
		    m_lbIdents (this, IDL_RESETIDENTS),
		    m_ftToDo (this, IDT_LISTBOXTEXT),
		    m_lMCode (lMCode)
{
	SetCaption (ResString (ResID (IDS_RESETVISCAPTION, pRF), 50));
	m_ftToDo.SetText (ResString (ResID (IDS_RESETVISTEXT, pRF), 50));	
	
	m_pInBuff = NULL;
}

#pragma warning (default: 4355)

CResetVisInfoDlg :: ~CResetVisInfoDlg (void)
{
	DELETE_OBJ (m_pInBuff);
}


bool CResetVisInfoDlg :: Init (void)
{
	if (m_lMCode == -1) return false;
	
	m_pInBuff = new char [_MAX_PATH];
	if (m_pInBuff == NULL) return false;
	
// ListBox füllen, dazu Identifikatoren dieser Sicht enumerieren lassen
ENUMTEXTKEYEX ETK;
RESETDATA RD;
	
	RD.m_lMCode = m_lMCode;
	RD.m_iIdBase = DEX_GetIdBase();
	RD.m_lbIdents = &m_lbIdents;
	
	ETK.eKey = DEX_GetActiveSight (m_pInBuff);
	ETK.eFcn = (ENUMTEXTKEYEXPROC)ResetVisInfoIdentEx;
	ETK.ePtr = &RD;
	ETK.eData = (OTPunkt|OTLinie|OTFlaeche|OTText);
	DEX_EnumSightIdentsEx (ETK);	
	return true;
}

void _XTENSN_EXPORT CResetVisInfoDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (RemoveIdentVisInfo());
		break;
		
	case IDCANCEL:
		EndDlg (0);
		break;
		
	case IDB_RESETHELP:
		break;
	}
}

// Abschließendes bearbeiten der Eingaben -------------------------------------

BOOL PASCAL _XTENSN_EXPORT ObjResetVisInfoEx (long lONr, DWORD, void *pData)
{
short Status = DEX_GetObjectStatus (lONr);

	if (Status == OSNormal || Status == OSModified) 
	{
	// Objekt existiert und ist nicht temporär: VisInfoMerkmal löschen	
		((CVisObjExtension *)g_pTE) -> ResetObjectVisInfo (lONr);
	}
	return true;
}

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

bool CResetVisInfoDlg :: RemoveIdentVisInfo (void)
{
CEierUhr Wait (GetParent());
short iIndex = m_lbIdents.GetFirstSelected();
bool fOne = false;

	while (iIndex != -1) {
		fOne = true;		// wenigstens einer

		m_lbIdents.GetString (m_pInBuff, iIndex, _MAX_PATH);
		
	// Merkmale an Objekten löschen
	long lIdent = 0L;
	
		if (FAILED(IdentFromClassX (m_pInBuff, (ULONG *)&lIdent)))
			continue;

	ENUMLONGKEYEX ELK;
	
		ELK.eKey = lIdent;
		ELK.eFcn = (ENUMLONGKEYEXPROC)ObjResetVisInfoEx;
		ELK.ePtr = &m_lMCode;
		ELK.eData = BitsFromType (strchr (m_pInBuff, ':'));
		if (!DEX_EnumIdentObjectsEx (ELK))
			break;		// Fehler o.ä.

	// Merkmal am Ident löschen/modifizieren
	CVisObjExtension *pE = (CVisObjExtension *)g_pTE;

		if (!pE -> AdjustIdentifier (lIdent, OVModVisInfo, ELK.eData, false))
			return false;

	// nächster aktiver Eintrag
		iIndex = m_lbIdents.GetNextSelected();
	}
	return fOne;
}





