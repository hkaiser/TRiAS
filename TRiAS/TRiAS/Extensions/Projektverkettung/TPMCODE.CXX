// Anzeigen von Merkmalskodes -----------------------------
// File: TPMCODE.CXX

#include "tprojp.hxx"
#include "tproject.h"
#include "defproj.h"

#include "txtedit.hxx"
#include "tpmcode.hxx"



// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

TPMCodeDef :: TPMCodeDef (pWindow pW, uint res, ResourceFile &RF )
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _ShowTPMCode ( this, IDS_TPMCODE),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL),
	       _RF(RF),
	       TPMCodeList (this, IDLB_TPMKLIST)

{
	_pW = pW;
//	pW->Disable();
	OKButton.Disable();
	_ShowTPMCode.SetButton ( &OKButton);

	_pMCode = new char [MaxKey ];
	if ( _pMCode == NULL ) return;
// ListBox fllen

ENUMLONGKEY ENK;
	ENK.eKey = 'm';
	ENK.eFcn = (ENUMNOKEYLONGPROC) FillTPMCListBox;
	ENK.ePtr = &TPMCodeList;
	
	DEX_EnumPBDData(ENK);

}

#pragma warning (default: 4355)

// Destruktor
TPMCodeDef :: ~TPMCodeDef (void) 
{
	DELETE_OBJ ( _pMCode );
//	_pW->Enable();
}

void _XTENSN_EXPORT TPMCodeDef :: ButtonClick (ControlEvt e)
{

	switch ((unsigned int)e.GetControlID()) {

	case IDOK:
		_ShowTPMCode.GetText (_pMCode,MaxKey);
		EndDlg(1);

	break;

	case IDCANCEL:
		EndDlg (0);
	break;

	}

}


void _XTENSN_EXPORT TPMCodeDef :: ListBoxSel (ControlEvt)
{
	if (!_pMCode)
		return;
int jIndex = TPMCodeList.GetCurrentIndex();

	if (jIndex != -1) {

		TPMCodeList.GetCurrentString ( _pMCode );
		*strchr (_pMCode, ':') = '\0';
		_ShowTPMCode.SetText (_pMCode); 
		OKButton.Enable();
	}
}

//-------------------------------------------------------------------

void _XTENSN_EXPORT TPMCodeDef :: ListBoxClk (ControlEvt)
{

	if (!_pMCode)
		return;
	_ShowTPMCode.GetText (_pMCode,MaxKey);
	*strchr(_pMCode, ':') = '\0';
	EndDlg (1);

}

//--------------------------------------------------------------------------

extern "C" {

BOOL PASCAL _XTENSN_EXPORT FillTPMCListBox (long Mkode, Bool , void *pData)
{
PBDDATA pbdData;
char KText[33];

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = Mkode;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);

char outBuff[TEXTLEN+20];
	if ( DEX_GetMkBase() == 16 )
		wsprintf (outBuff, "%lx:%s", Mkode, pbdData.pbdKText);
	else
		wsprintf (outBuff, "%ld:%s", Mkode, pbdData.pbdKText);

	((ListBox *)pData) -> AddString (outBuff);

	return TRUE;

}

} // extern "C"
