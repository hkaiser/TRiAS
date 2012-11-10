// Eine ListViewCtrl, das alle RelationesCodes der Beschreibungs-Datenbasis enthält 
// File: SELRELST.CXX

#include "featurep.hxx"
#include "feature.h"		// ResourceKonstanten

#include "selrelst.hxx"

#define KTEXT_COLUMN	2
#define RTYP_COLUMN	1
#define RCODE_COLUMN	0

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CSelPBDRelationList :: CSelPBDRelationList (pDialogWindow pW, ResID uiRes, ResourceFile &rRF)
		     : CListViewCtrl (pW, uiRes), m_rRF(rRF)
{
	m_pBuff = NULL;
}

CSelPBDRelationList :: ~CSelPBDRelationList (void)
{
	DELETE (m_pBuff);
}

typedef struct tagFILLPBDDATA {
	CListViewCtrl *m_pLV;
	char *m_pOutBuff;
	int m_iCnt;
} FILLPBDDATA;

static void AddTypeString (FILLPBDDATA *pFR, long lRCode, char *pTyp, char *pKText)
{
	wsprintf (pFR -> m_pOutBuff, "%08ld", lRCode);

int iItem = pFR -> m_pLV -> InsertItem (pFR -> m_iCnt++, pFR -> m_pOutBuff);

	if (-1 == iItem) return;

LV_ITEM lvi;

	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.pszText = pTyp;
	lvi.iItem = iItem;
	lvi.iSubItem = RTYP_COLUMN;
	pFR -> m_pLV -> SetItem (&lvi);

	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.pszText = pKText;
	lvi.iItem = iItem;
	lvi.iSubItem = KTEXT_COLUMN;
	pFR -> m_pLV -> SetItem (&lvi);
}


extern "C" 
bool _XTENSN_EXPORT PASCAL FillRCodesLV (long lRCode, bool, void *pData)
{
PBDRELATION pbdData;
char cbKText[34];
FILLPBDDATA *pFR = (FILLPBDDATA *)pData;

	memset (cbKText, '\0', sizeof(cbKText));

	INITSTRUCT(pbdData, PBDRELATION);
	pbdData.pbdTyp = 'r';
	pbdData.pbdCode = lRCode;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof(cbKText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);
	cbKText[32] = '\0';
	
	AddTypeString (pFR, lRCode, 
		'h' == pbdData.ipbdRTyp ? "gleichrangig" : "hierarchisch", 
		pbdData.pbdKText);

return true;	// weitermachen
}

// Initialisierung des Controls -----------------------------------------------
bool CSelPBDRelationList :: InitControl (void)
{
	if (!Control::FInit()) return false;		// Initialisieren

	SetStyle (LVS_SHOWSELALWAYS);

// HeaderBezeicher eintragen
ResString resRCode (ResID (IDS_HEADERRCODE, &m_rRF), 16);	// "Relationscode"
ResString resType (ResID (IDS_HEADERRELTYPE, &m_rRF), 16);	// "Relationstyp"
ResString resDesc (ResID (IDS_HEADERDESC, &m_rRF), 16);		// "Beschreibung"

	InsertColumn (RCODE_COLUMN, resRCode, LVCFMT_LEFT, -1, 0);
	InsertColumn (RTYP_COLUMN, resType, LVCFMT_LEFT, -1, 0);
	InsertColumn (KTEXT_COLUMN, resDesc, LVCFMT_LEFT, -1, 0);

// ZeichenKette anlegen
	m_pBuff = new char [_MAX_PATH];
	if (m_pBuff == NULL) return false;

FILLPBDDATA FRD;

	FRD.m_pLV = this;
	FRD.m_pOutBuff = m_pBuff;
	FRD.m_iCnt = 0;

ENUMLONGKEY ELK;

	ELK.eKey = 'r';
	ELK.eFcn = (ENUMLONGKEYPROC)FillRCodesLV;
	ELK.ePtr = &FRD;
	if (!DEX_EnumPBDData (ELK))	// alle RCodes der PBD enumerieren
		return false;

// Spalten entsprechend richten
	FitColumn (KTEXT_COLUMN);
	FitColumn (RTYP_COLUMN);
	FitColumn (RCODE_COLUMN);

return true;
}

// Liefert Selektion ----------------------------------------------------------
bool CSelPBDRelationList :: GetSelectedRCode (long &rlRCode, short &riRTyp)
{
	return DecodeEntry (GetNextItem (-1, LVNI_ALL|LVNI_SELECTED), rlRCode, riRTyp);
}

///////////////////////////////////////////////////////////////////////////////
// HilfsFunktionen ------------------------------------------------------------
bool CSelPBDRelationList :: DecodeEntry (int iIndex, long &rlRCode, short &riRTyp)
{
	if (iIndex == -1) return false;
	
	rlRCode = 0;
	riRTyp = 0;

	if (0 == GetItemText (iIndex, RCODE_COLUMN, m_pBuff, _MAX_PATH))
		return false;
	rlRCode = strtoul (m_pBuff, NULL, 10);
	
	if (0 == GetItemText (iIndex, RTYP_COLUMN, m_pBuff, _MAX_PATH))
		return false;

	riRTyp = GetRTyp (m_pBuff);

return true;
}

short CSelPBDRelationList :: GetRTyp (LPCSTR pTyp)
{
	switch (*pTyp) {
	case 'h':	return RTKomplexO;	// Komplexrelation
	case 'g':	return RTGleich;	// gleichrangige Relation
	}

return 0;
}


void CSelPBDRelationList :: FitColumn (int iCol)
{
int iCnt = GetItemCount();
int iMax = 0, iWidth = 0;
string str;

	for (int i = 0; i < iCnt; i++) {
		str = GetItemText (i, iCol);

		iWidth = GetStringWidth (str.c_str());
		if (iWidth > iMax) iMax = iWidth;
	}
	if (iMax > 0)
		SetColumnWidth (iCol, iMax+25);
}
