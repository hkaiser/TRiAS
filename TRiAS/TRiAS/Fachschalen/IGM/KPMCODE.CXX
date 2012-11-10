// Anzeigen von Merkmalskodes -----------------------------
// File: KPMCODE.CXX

#include "kompp.hxx"
#include "kompaktr.h"

#include <igeometr.hxx>

#include "triasdef.h"
#include "kompdef.h"

#include "txtedit.hxx"
#include "kpmcode.hxx"



// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

KPMCodeDef :: KPMCodeDef (pWindow pW, uint res, ResourceFile &RF, char *pText )
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _ShowKPMCode ( this, IDS_KPMCODE),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL),
	       _RF(RF),
	       KPMCodeList (this, IDLB_KPMKLIST)

{
	_pW = pW;
//	pW->Disable();
	OKButton.Disable();
	_ShowKPMCode.SetButton ( &OKButton);
	_pMText = NULL;
	if (pText)
		_pMText = pText;
	_pMCode = new char [_MAX_PATH ];
	if ( _pMCode == NULL ) return;
// ListBox füllen

ENUMLONGKEY ENK;
	ENK.eKey = 'm';
	ENK.eFcn = (ENUMNOKEYLONGPROC) FillKPMCListBox;
	ENK.ePtr = &KPMCodeList;
	
	DEX_EnumPBDData(ENK);

}

#pragma warning (default: 4355)

// Destruktor
KPMCodeDef :: ~KPMCodeDef (void) 
{
	DELETE_OBJ ( _pMCode );
//	_pW->Enable();
}

void _XTENSN_EXPORT KPMCodeDef :: ButtonClick (ControlEvt e)
{

	switch ((unsigned int)e.GetControlID()) {

	case IDOK:
		_ShowKPMCode.GetText (_pMCode,_MAX_PATH);
		StoreKPMCode ( _pMCode, _pMText );
		EndDlg(1);

	break;

	case IDCANCEL:
		EndDlg (0);
	break;

	}

}


void _XTENSN_EXPORT KPMCodeDef :: ListBoxSel (ControlEvt)
{
	if (!_pMCode)
		return;
int jIndex = KPMCodeList.GetCurrentIndex();

	if (jIndex != -1) {

		KPMCodeList.GetCurrentString ( _pMCode );
		*strchr (_pMCode, ':') = '\0';
		_ShowKPMCode.SetText (_pMCode); 
		OKButton.Enable();
	}
}

//-------------------------------------------------------------------

void _XTENSN_EXPORT KPMCodeDef :: ListBoxClk (ControlEvt)
{

	if (!_pMCode)
		return;
	_ShowKPMCode.GetText (_pMCode,_MAX_PATH);
	*strchr(_pMCode, ':') = '\0';
	EndDlg (1);

}


void KPMCodeDef :: StoreKPMCode ( char *pMCode, char *pText)
{

	if (!pMCode || *pMCode == '\0')
		return;
	if ( !pText)
		return;

	long lMCode;

	if ( DEX_GetMkBase() == 16 )
		lMCode = strtoul(pMCode,NULL,16);
	else
		lMCode = atol ( pMCode);


PBDMERKMAL pbdData;
char KText[33];

	memset (&pbdData, '\0', sizeof(PBDMERKMAL));
	
	pbdData.dwSize = sizeof(PBDMERKMAL);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	strncpy ( KText,  pText , sizeof(KText)-1);
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.ipbdMTyp = 'a' | PBDMERKMAL_SYSTEMFLAG;	// so tun, als ob's nur für Objekte wär
	pbdData.ipbdMLen = 256;
	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDData (pbdData) != EC_OKAY)
			return;
		else
			DEXN_PBDMCodeChanged (lMCode);
	}

}

//--------------------------------------------------------------------------

extern "C" {

BOOL PASCAL _XTENSN_EXPORT FillKPMCListBox (long Mkode, Bool , void *pData)
{
PBDDATA pbdData;
char KText[TEXTLEN];

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
