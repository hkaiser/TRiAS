// Eine ListViewCtrl, das alle Identifikatoren der Beschreibungs-Datenbasis enthält 
// File: SELIDPBD.CXX

#include "featurep.hxx"
#include "feature.h"		// ResourceKonstanten

#include "selidpbd.hxx"

#define KTEXT_COLUMN	1
#define IDENT_COLUMN	0

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CSelPBDIdentList :: CSelPBDIdentList (pDialogWindow pW, ResID uiRes, ResourceFile &rRF)
		  : CListViewCtrl (pW, uiRes), m_rRF(rRF)
{
	m_pBuff = NULL;
	m_iIdBase = DEX_GetIdBase();
}

CSelPBDIdentList :: ~CSelPBDIdentList (void)
{
	DELETE (m_pBuff);
}

typedef struct tagFILLPBDDATA {
	CListViewCtrl *m_pLV;
	char *m_pOutBuff;
	int m_iCnt;
	int m_iIdBase;
} FILLPBDDATA;

static void AddTypeString (FILLPBDDATA *pFR, long lIdent, char *pKText)
{
	wsprintf (pFR -> m_pOutBuff, 
		  (10 == pFR -> m_iIdBase) ? "%08ld" : "%08lx", lIdent);

int iItem = pFR -> m_pLV -> InsertItem (pFR -> m_iCnt++, pFR -> m_pOutBuff);

	if (-1 == iItem) return;

LV_ITEM lvi;

	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.pszText = pKText;
	lvi.iItem = iItem;
	lvi.iSubItem = KTEXT_COLUMN;
	pFR -> m_pLV -> SetItem (&lvi);
}


extern "C" 
bool _XTENSN_EXPORT PASCAL FillPBDIdentsLV (long lIdent, bool, void *pData)
{
PBDRELATION pbdData;
char cbKText[34];
FILLPBDDATA *pFR = (FILLPBDDATA *)pData;

	memset (cbKText, '\0', sizeof(cbKText));

	INITSTRUCT(pbdData, PBDRELATION);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof(cbKText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);
	cbKText[32] = '\0';
	
	AddTypeString (pFR, lIdent, pbdData.pbdKText);

return true;	// weitermachen
}

// Initialisierung des Controls -----------------------------------------------
bool CSelPBDIdentList :: InitControl (void)
{
	if (!Control::FInit()) return false;		// Initialisieren

	SetStyle (LVS_SHOWSELALWAYS);

// HeaderBezeicher eintragen
ResString resIdent (ResID (IDS_HEADERIDENT, &m_rRF), 16);	// "Identifikator"
ResString resDesc (ResID (IDS_HEADERDESC, &m_rRF), 16);		// "Beschreibung"

	InsertColumn (IDENT_COLUMN, resIdent, LVCFMT_LEFT, -1, 0);
	InsertColumn (KTEXT_COLUMN, resDesc, LVCFMT_LEFT, -1, 0);

// ZeichenKette anlegen
	m_pBuff = new char [_MAX_PATH];
	if (m_pBuff == NULL) return false;

FILLPBDDATA FRD;

	FRD.m_pLV = this;
	FRD.m_pOutBuff = m_pBuff;
	FRD.m_iCnt = 0;
	FRD.m_iIdBase = m_iIdBase;

ENUMLONGKEY ELK;

	ELK.eKey = 'i';
	ELK.eFcn = (ENUMLONGKEYPROC)FillPBDIdentsLV;
	ELK.ePtr = &FRD;
	if (!DEX_EnumPBDData (ELK))	// alle Idents der PBD enumerieren
		return false;

// Spalten entsprechend richten
	FitColumn (KTEXT_COLUMN);
	FitColumn (IDENT_COLUMN);

return true;
}

// Liefert Selektion ----------------------------------------------------------
bool CSelPBDIdentList :: GetSelectedIdent (long &rlIdent)
{
	return DecodeEntry (GetNextItem (-1, LVNI_ALL|LVNI_SELECTED), rlIdent);
}

///////////////////////////////////////////////////////////////////////////////
// HilfsFunktionen ------------------------------------------------------------
bool CSelPBDIdentList :: DecodeEntry (int iIndex, long &rlIdent)
{
	if (iIndex == -1) return false;
	
	rlIdent = 0;

	if (0 == GetItemText (iIndex, IDENT_COLUMN, m_pBuff, _MAX_PATH))
		return false;
	rlIdent = strtoul (m_pBuff, NULL, m_iIdBase);

return true;
}

void CSelPBDIdentList :: FitColumn (int iCol)
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
