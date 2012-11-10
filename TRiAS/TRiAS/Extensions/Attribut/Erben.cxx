
// ----------------Vererben von Attributen -----------------------------
// File: ERBEN.CXX

#include "attribp.hxx"


#include <triastlb_i.c>
#include <triastlb.h>

#include <oleguid.h>
#include <dirisole.h>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include <shellapi.h>
#include <igeometr.hxx>

#include <xtsnaux.hxx>
#include <initguid.h>
#include <istatus.h>

#include <igeometr.hxx>

#include "attribut.h" 
#include "about.h"
#include "define.h"


#include "about.hxx"
#include "idkey.hxx"
#include "objkey.hxx"
#include "clstree.hxx"
#include "stohwnd.hxx"
#include "attribut.hxx"
#include "erben.hxx"

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

DefineObjClassErbe :: DefineObjClassErbe (pWindow pW, uint res, ResourceFile &RF, IDMTree *pIDM, long *lMCode)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _ObjClass1 ( this, IDLB_ATTOBJCLASS1),
	       _ObjClass2 ( this, IDLB_ATTOBJCLASS2),
	       _MClass1 ( this, IDLB_ATTMCLASS1),
	       _MClass2 ( this, IDLB_ATTMCLASS2),
	       _MIdent ( this, IDCB_ATTMCODEIDENT),
	       _IDCont ( this, IDB_ATTIDENTCONT),
	       _IDMCode ( this, IDB_ATTIDENTMCODE),
	       _ZuOrdn ( this, IDCB_ATTZUORDNUNG),
	       _Zuordnen ( this, IDB_ATTZUORDNEN),
	       _Loeschen ( this, IDB_ATTLOESCHEN),
	       _ContText ( this, IDS_ATTCONTTEXT),
	       _MerkmalText ( this, IDS_ATTMERKMALTEXT),
	       _IntervallWert (this,IDT_ATTINTERVALLWERT),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_pW = pW;
	pW->Disable();
	_pMCode = NULL;
	_lMCode = lMCode;
	_pIDM = pIDM;

	CEierUhr Wait(_pW);

	// Start mit Containertest
	_IDMCode.SetState(FALSE);
	_IDCont.SetState(TRUE);   

	if ( !FillObjClassList1())
		return;

	SetzeStandard();
	return;
}

#pragma warning (default: 4355)


DefineObjClassErbe :: ~DefineObjClassErbe (void)
{
	_pW->Enable();
}

void _XTENSN_EXPORT DefineObjClassErbe :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_ATTOBJCLASS1:
		{
		int iIndex = _ObjClass1.GetFirstSelected();
		if ( iIndex == -1 ) {
			_iIdSel = false;
			return;
		}

		CTable t ( *_pIDM);
		for ( t.First(); t.Valid();t.Next()) {
			IDMLock l(t);
			l->SetTypZero();
		}

		short Typ;
		long Key = GetIdent ( iIndex , &Typ);
		if ( t.Find ( &Key)) {
			IDMLock l(t);
			l->SetTyp ( Typ);
			_iIdSel = true;
		}

		iIndex=_ObjClass1.GetNextSelected ();

		while ( iIndex != -1 ) {
			Key = GetIdent ( iIndex , &Typ);

			if ( t.Find ( &Key)) {
				IDMLock l(t);
				l->SetTyp ( Typ);
				_iIdSel = true;
			}

			iIndex=_ObjClass1.GetNextSelected ();

		}
		KonsistenzTest();
		}
		break;

	case IDLB_ATTOBJCLASS2:
		{
		int iIndex = _ObjClass2.GetCurrentIndex();
		_Ident2 = 0L;
		if ( iIndex == -1)
			return;
		char * pBuffer = new char [_MAX_PATH];
		if ( !pBuffer ) 
			return;
		_ObjClass2.GetCurrentString (pBuffer);

		char *ptr = strchr (pBuffer, ':');
		if ( ptr == NULL ) {
			DELETE ( pBuffer);
			return;
		} else
			*ptr = '\0';

		ulong uIdent2 = (ulong) _Ident2;
		IdentFromClassX ( pBuffer, &uIdent2);
		_Ident2 = (long)uIdent2;

/*---------23.1.97
		if ( DEX_GetIdBase() == 16 )
			_Ident2 = strtoul ( pBuffer, NULL, 16 );
		else
			_Ident2 = atol(pBuffer);
---------------*/

		if ( *(ptr+1) == 'F' )
			_iGiTyp = OTFlaeche;
		if ( *(ptr+1) == 'L' )
			_iGiTyp = OTLinie;
		if ( *(ptr+1) == 'P' )
			_iGiTyp = OTPunkt;
		if ( *(ptr+1) == 'T' )
			_iGiTyp = OTText;
		
		DELETE ( pBuffer);

		KonsistenzTest();

		}
		break;

	case IDLB_ATTMCLASS1:
		{
		int iIndex = _MClass1.GetCurrentIndex();
		if ( iIndex == -1 ) 
			return;
		_MZiel = GetMCode ( iIndex ,&_MClass1);

		if ( _MZiel != 0L && _MQuelle != 0L)
			_Zuordnen.Enable();
		else
			_Zuordnen.Disable();
		}
		break;

	case IDLB_ATTMCLASS2:
		{
		int iIndex = _MClass2.GetCurrentIndex();
		if ( iIndex == -1 ) 
			return;
		_MQuelle = GetMCode ( iIndex ,&_MClass2);
		if ( _MZiel != 0L && _MQuelle != 0L)
			_Zuordnen.Enable();
		else
			_Zuordnen.Disable();
		}
		break;

	case IDCB_ATTMCODEIDENT:
		{
		int iIndex = _MIdent.GetCurrentIndex();
		if ( iIndex == -1 ) 
			return;
		_MkIdent = GetMCode ( iIndex ,&_MIdent);
		KonsistenzTest();
		}
		break;
	}
}

void _XTENSN_EXPORT DefineObjClassErbe :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		_IntervallWert.GetText ( _WERT , sizeof ( _WERT ) );
		_lWert = atol ( _WERT );
		LeseMCodeTupel();
		EndDlg (1);
		}
		break;

		case IDCANCEL:
		{
		EndDlg (0);
		}
		break;

		case IDB_ATTZUORDNEN:
		{
		BildeMCodeTupel();
		KonsistenzTest();
		_MZiel = _MQuelle = 0L;
		_Zuordnen.Disable();
		}
		break;

		case IDB_ATTLOESCHEN:
		{
		_ZuOrdn.Clear();
		_MClass1.Clear();
		_MClass2.Clear();
		_MZiel = _MQuelle = 0L;
		if ( !FillMClassList1())
			return;
		if ( !FillMClassList2())
			return;
		OKButton.Disable();
		_Zuordnen.Disable();
		}
		break;

		case IDB_ATTIDENTCONT :
		{
		_IDMCode.SetState(FALSE);
		_IDCont.SetState(TRUE);   
		SetzeStandard();
		}
		break;

		case IDB_ATTIDENTMCODE :
		{
		_IDMCode.SetState(TRUE);
		_IDCont.SetState(FALSE);   
		SetzeStandard();
		}
		break;

	}
	return;
}
//Member

//-------------------------------------------------------------------
void DefineObjClassErbe :: KonsistenzTest ( void )
{
	if ( _isCont ) {	//Container
		if ( _iIdSel && _Ident2 != 0L && _iMkSel )
			OKButton.Enable();
	} else {	//Merkmal
		if ( _iIdSel && _MkIdent != 0L && _Ident2 != 0L && _iMkSel )
			OKButton.Enable();
	}
}
//------------------------------------------------------------------------
void DefineObjClassErbe :: LeseMCodeTupel ( void )
{

	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return;

	int Count = _ZuOrdn.GetCount();
	short Number = 1;
	if (_pMCode)
		DELETE ( _pMCode);

	_pMCode = new long [ 2 * Count +1];
	if ( !_pMCode )
		return;
	for ( int i = 0 ; i < Count; i++ ) {
		_ZuOrdn.GetString(pBuffer,i);
		char *ptr = strchr ( pBuffer,':');
		if ( !ptr)
			return;
		*ptr = '\0'; 
		long M1;
		long M2;
		if ( DEX_GetMkBase() == 16 )
			M1 = strtoul ( pBuffer, NULL, 16 );
		else
			M1 = atol(pBuffer);
		*ptr = ':';
		ptr = strrchr ( pBuffer,':');
		if ( !ptr)
			return;
		*ptr = '\0';
		ptr--;
		while (*ptr != ' ')
			ptr--;
		ptr++;
		if ( DEX_GetMkBase() == 16 )
			M2 = strtoul ( ptr, NULL, 16 );
		else
			M2 = atol(ptr);

		*(_pMCode+Number) = M1;
		*(_pMCode+Number+1) = M2;	
		Number = Number + 2;
	}
	*_pMCode = Count;
	DELETE ( pBuffer);
	return;
}
//------------------------------------------------------------------------
void DefineObjClassErbe :: BildeMCodeTupel ( void )
{

	char * pBuffer = new char [_MAX_PATH];
	if ( !pBuffer )
		return;

	PBDDATA pbdData;
	char KText1[MAXFCTNAME+1];
	char KText2[MAXFCTNAME+1];
	KText1[0] = '\0';
	KText2[0] = '\0';

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = _MZiel;
	pbdData.pbdKText = KText1;
	pbdData.pbdKTextLen = sizeof(KText1) -1;
	pbdData.pbdLTextLen = 0;

	DEX_GetPBDData (pbdData);

	pbdData.pbdCode = _MQuelle;
	pbdData.pbdKText = KText2;
	pbdData.pbdKTextLen = sizeof(KText2) -1;

	DEX_GetPBDData (pbdData);

	if ( KText1[0] == NULL )
		strcat ( KText1 , ResString(ResID(IDS_ATTNODEFOBJCLASS,&g_pTE->RF()),70));
	KText1[MAXFCTNAME] = '\0';

	if ( KText2[0] == NULL )
		strcat ( KText2 , ResString(ResID(IDS_ATTNODEFOBJCLASS,&g_pTE->RF()),70));
	KText2[MAXFCTNAME] = '\0';

	if ( DEX_GetMkBase() == 16 )
		wsprintf (pBuffer, "%08lx:%-20s   <==    %08lx:%s", _MZiel,KText1,_MQuelle,KText2);
	else
		wsprintf (pBuffer, "%08ld:%-20s   <==    %08ld:%s", _MZiel,KText1,_MQuelle,KText2);
	

	_ZuOrdn.AddString ( pBuffer);

	_ZuOrdn.ChangeCurrentIndex ( 0 );

	DELETE ( pBuffer);
	_iMkSel = true;

}
//------------------------------------------------------------------------
void DefineObjClassErbe :: SetzeStandard ( void )
{
	_ObjClass1.ClearSelected();
	_ObjClass2.Clear();
	_MClass1.Clear();
	_MClass2.Clear();
	_MIdent.Clear();
	_ZuOrdn.Clear();
	OKButton.Disable();
	_Zuordnen.Disable();
	_MQuelle = _MZiel = 0L;
	_Ident2 = 0L;
	_MkIdent = 0L;
	_iIdSel = false;	// Kein ID selektiert
	_iMkSel = false;	// Kein MK-Paar selektiert

	if ( !FillObjClassList2())
		return;
	if ( !FillMClassList1())
		return;
	if ( !FillMClassList2())
		return;
	if ( !FillMClassIdent())
		return;

	if ( _IDCont.GetState()) {
		_IDMCode.SetState(FALSE);
		_IDCont.SetState(TRUE);   
		_MerkmalText.Disable();
		_ContText.Enable();
		_MIdent.Disable();
		_IntervallWert.Enable();
		_IntervallWert.SetText(NULL);
		_isCont = true;		// Container = Standard
	} else {
		_IDMCode.SetState(TRUE);
		_IDCont.SetState(FALSE);   
		_MerkmalText.Enable();
		_ContText.Disable();
		_MIdent.Enable();
		_IntervallWert.Disable();
		_IntervallWert.SetText(NULL);
		_isCont = false;		// Container = Standard
	}
	return;
}
//-------------------------------------------------------------------
Bool DefineObjClassErbe :: FillObjClassList1 ( void )
{
	if ( !_pIDM ) 
		return false;

	CTable t ( *_pIDM);
	for ( t.First(); t.Valid(); t.Next() ) {
		IDMLock l(t);
		DWORD Type = (DWORD) l->RefTyp();
		GetIdentWithTyp ( l->Ident(), Type, &_ObjClass1);
		l->GiTyp() = l->RefTyp();
		l->SetTypZero();
	}

	return true;
}
//------------------------------------------------------------------------
Bool DefineObjClassErbe :: FillObjClassList2 ( void )
{
	short Typ;
	if ( _IDMCode.GetState()) {
		Typ = OTLinie | OTFlaeche | OTPunkt ;
	} else {
		Typ = OTPunkt ;
	}
	_ObjClass2.Clear();

	ENUMTEXTKEYEX ENTex;
	ENTex.eKey = NULL;		// NULL = aktuelle Sicht

	if ( _IDMCode.GetState()) 
		ENTex.eFcn = ( ENUMTEXTKEYEXPROC) GetIdentWithTyp;
	else
		ENTex.eFcn = ( ENUMTEXTKEYEXPROC) GetIdentWithPoint;

	ENTex.ePtr = &_ObjClass2;
	ENTex.eData = ( DWORD ) Typ;	

	DEX_EnumSightIdentsEx(ENTex);

	return true;
}
//----------------------------------------------------------------------
//
Bool DefineObjClassErbe :: FillMClassList1 ( void )
{
	
// ------------MerkmalListBox füllen

	if ( !_lMCode || *_lMCode == 0 )
		return false;

	long NR = *_lMCode;
	short flag = true;
    
	for ( long i = 0; i < NR; i++ ) {

		long lMCode = *(_lMCode+i+1);
		FillMKListBox ( lMCode, flag, &_MClass1);
	}
	return true;
}
//
Bool DefineObjClassErbe :: FillMClassList2 ( void )
{
	
// ------------MerkmalListBox füllen

ENUMNOKEY ENK;

	ENK.eFcn = ( ENUMNOKEYPROC) FillMKListBox;
	ENK.ePtr = &_MClass2;
	
	DEX_EnumMCodes(ENK);

	return true;
}
//----------------------------------------------------------------
//----------------------------------------------------------------------
//
Bool DefineObjClassErbe :: FillMClassIdent ( void )
{
	
// ------------MerkmalListBox füllen

	if ( !_lMCode || *_lMCode == 0 )
		return false;

	long NR = *_lMCode;
	short flag = true;
    
	for ( long i = 0; i < NR; i++ ) {

		long lMCode = *(_lMCode+i+1);
		FillMKListBox ( lMCode, flag, &_MIdent);
	}
	return true;
}
//----------------------------------------------------------------
long DefineObjClassErbe :: GetIdent ( int iIndex , short *Typ)
{
char * pBuff = new char [_MAX_PATH];
*Typ = 0;
	if ( pBuff == NULL ) 
		return 0;
long Ident;
	_ObjClass1.GetString (pBuff, iIndex, _MAX_PATH);
	char *ptr = strchr (pBuff, ':');
	if ( ptr == NULL ) {
		DELETE ( pBuff);
		return 0;
	} else
		*ptr = '\0';
	ulong uIdent;
	IdentFromClassX (pBuff, &uIdent);
	Ident = (long) uIdent;

/*------------------
	if ( DEX_GetIdBase() == 16 )
		Ident = strtoul ( pBuff, NULL, 16 );
	else
		Ident = atol(pBuff);
-----------*/

	*ptr = ':';
	if ( *(ptr+1) == 'F' )
		*Typ = OTFlaeche;
	if ( *(ptr+1) == 'L' )
		*Typ = OTLinie;
	if ( *(ptr+1) == 'P' )
		*Typ = OTPunkt;
	if ( *(ptr+1) == 'T' )
		*Typ = OTText;

	DELETE ( pBuff);

	return Ident;	

}
//----------------------------------------------------------------
long DefineObjClassErbe :: GetMCode ( int iIndex , ListBox * pL)
{
char * pBuff = new char [_MAX_PATH];
	if ( pBuff == NULL ) 
		return 0;
long Ident;
	pL->GetString (pBuff, iIndex, _MAX_PATH);
	char *ptr = strchr (pBuff, ':');
	if ( ptr == NULL ) {
		DELETE ( pBuff);
		return 0;
	} else
		*ptr = '\0';
	if ( DEX_GetMkBase() == 16 )
		Ident = strtoul ( pBuff, NULL, 16 );
	else
		Ident = atol(pBuff);

	*ptr = ':';
	DELETE ( pBuff);

	return Ident;	

}
//----------------------------------------------------------------
//------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT FillMKListBox (long Mkode, Bool, void *pData)
{
PBDDATA pbdData;
char KText[MAXFCTNAME+1];
	KText[0] = '\0';
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = Mkode;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);

char outBuff[TEXTLEN+20];
	if ( KText[0] == NULL )
		strcat ( KText, ResString(ResID(IDS_ATTNODEFMERKMAL,&g_pTE->RF()),70));
	KText[MAXFCTNAME] = '\0';

	if ( DEX_GetMkBase() == 16 )
		wsprintf (outBuff, "%08lx:%s", Mkode, KText);
	else
		wsprintf (outBuff, "%08ld:%s", Mkode, KText);

	((ListBox *)pData) -> AddString (outBuff);
	return TRUE;

}
//--------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT GetIdentWithTyp (long Ident, DWORD Typ , void *pData)
{

PBDDATA pbdData;
char KText[MAXFCTNAME+1];
	KText[0] = '\0';
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);

char outBuff[TEXTLEN+20];
	if ( KText[0] == NULL )
		strcat ( KText , ResString(ResID(IDS_ATTNODEFOBJCLASS,&g_pTE->RF()),70));
	KText[MAXFCTNAME] = '\0';
	char CTyp = ' ';

	ulong ulIdent = 0L;
	char NewIdent[MAX_OKS_LENX + 1];

	if ( Typ & OTPunkt ) {
		CTyp = 'P';

		ulIdent = (ulong) Ident;

		ClassFromIdentX (ulIdent,NewIdent);

		wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);

/*----------23.1.97
		if ( DEX_GetIdBase() == 16 )
			wsprintf (outBuff, "%08lx:%c:%s", Ident, CTyp, KText);
		else
			wsprintf (outBuff, "%08ld:%c:%s", Ident, CTyp, KText);
-------------*/
	
		((ListBox *)pData) -> AddString (outBuff);
	}
	if ( Typ & OTLinie ) {
		CTyp = 'L';


		ulIdent = (ulong) Ident;

		ClassFromIdentX (ulIdent,NewIdent);

		wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);

/*----------23.1.97
		if ( DEX_GetIdBase() == 16 )
			wsprintf (outBuff, "%08lx:%c:%s", Ident, CTyp, KText);
		else
			wsprintf (outBuff, "%08ld:%c:%s", Ident, CTyp, KText);
------------*/	

		((ListBox *)pData) -> AddString (outBuff);
	}
	if ( Typ & OTFlaeche ) {
		CTyp = 'F';


		ulIdent = (ulong) Ident;

		ClassFromIdentX (ulIdent,NewIdent);

		wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);

/*--------23.1.97
		if ( DEX_GetIdBase() == 16 )
			wsprintf (outBuff, "%08lx:%c:%s", Ident, CTyp, KText);
		else
			wsprintf (outBuff, "%08ld:%c:%s", Ident, CTyp, KText);
-----------------*/
	
		((ListBox *)pData) -> AddString (outBuff);
	}

	if ( Typ & OTText ) {
		CTyp = 'T';


		ulIdent = (ulong) Ident;

		ClassFromIdentX (ulIdent,NewIdent);

		wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);


/*-----------------

		if ( DEX_GetIdBase() == 16 )
			wsprintf (outBuff, "%08lx:%c:%s", Ident, CTyp, KText);
		else
			wsprintf (outBuff, "%08ld:%c:%s", Ident, CTyp, KText);
	
-----------------*/
		((ListBox *)pData) -> AddString (outBuff);

	}

	return TRUE;

}
//--------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT GetIdentWithPoint (long Ident, DWORD Typ , void *pData)
{
	char CTyp = ' ';
	if ( Typ & OTPunkt ) {
		CTyp = 'P';
	} else 
		return true;


PBDDATA pbdData;
char KText[MAXFCTNAME+1];
	KText[0] = '\0';
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);

	char outBuff[TEXTLEN+20];

	if ( KText[0] == NULL )
		strcat ( KText , ResString(ResID(IDS_ATTNODEFOBJCLASS,&g_pTE->RF()),70));
	KText[MAXFCTNAME] = '\0';


	ulong ulIdent = (ulong) Ident;
	char NewIdent[MAX_OKS_LENX+1];

	ClassFromIdentX (ulIdent,NewIdent);

	wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);


/*--------------------
	if ( DEX_GetIdBase() == 16 )
		wsprintf (outBuff, "%08lx:%c:%s", Ident, CTyp, KText);
	else
		wsprintf (outBuff, "%08ld:%c:%s", Ident, CTyp, KText);
------------------*/

	((ListBox *)pData) -> AddString (outBuff);


	return TRUE;

}
//--------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT GetIdents (long Ident, Bool , void *pData)
{

PBDDATA pbdData;
char KText[MAXFCTNAME+1];
	KText[0] = '\0';
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);

char outBuff[TEXTLEN+20];
	if ( KText[0] == NULL )
		strcat ( KText , ResString(ResID(IDS_ATTNODEFOBJCLASS,&g_pTE->RF()),70));
	KText[MAXFCTNAME] = '\0';


	ulong ulIdent = (ulong) Ident;
	char NewIdent[MAX_OKS_LENX+1];

	ClassFromIdentX (ulIdent,NewIdent);

	wsprintf (outBuff, "%s:%s", NewIdent, KText);

/*-------------------
	if ( DEX_GetIdBase() == 16 )
		wsprintf (outBuff, "%08lx:%s", Ident,  KText);
	else
		wsprintf (outBuff, "%08ld:%s", Ident, KText);
---------------------*/	

	((ListBox *)pData) -> AddString (outBuff);
	return TRUE;

}
//--------------------------------------------------------------------
//---------------------------------------------------------------------
// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

DefineCopyInformation :: DefineCopyInformation (pWindow pW, uint res, ResourceFile &RF, long ONr)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _Object( this, IDT_OBJATTROOT),
	       _ObjMerkmal (this, IDT_OBJATTMERKMALSWERT),
	       _MClass ( this, IDLB_OBJATTMCLASS),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_pW = pW;
	pW->Disable();
	OKButton.Disable();
	_Object.SetText(NULL);
	_ObjMerkmal.SetText(NULL);
	_pMCode = NULL;
	_ONr = ONr;
	if (_ONr <= 0L)
		return;
	CEierUhr Wait(_pW);
	if ( !FillMClassList())
		return;
	SetObjectInformation();
	return;
}

#pragma warning (default: 4355)


DefineCopyInformation :: ~DefineCopyInformation (void)
{
	_pW->Enable();
}

void _XTENSN_EXPORT DefineCopyInformation :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_OBJATTMCLASS:
		{
		
		int iIndex = _MClass.GetFirstSelected();

		if ( iIndex == -1 ) 
			return;

		int Count = _MClass.GetCount();
		short Number = 0;
		if (_pMCode)
			DELETE ( _pMCode);

		_pMCode = new long [ Count +1];
		if ( !_pMCode )
			return;
	
		long Key = GetMCode ( iIndex );
		Number++;
		*(_pMCode+Number) = Key;
		OKButton.Enable();
		ShowObjectMerkmal ( Key );

		iIndex=_MClass.GetNextSelected ();

		while ( iIndex != -1 ) {
			Key = GetMCode ( iIndex );
			Number++;
			*(_pMCode+Number) = Key;

			iIndex=_MClass.GetNextSelected ();

		}
		*_pMCode = (long) Number;
		}
		break;

	}
}

void _XTENSN_EXPORT DefineCopyInformation :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		EndDlg (1);
		}
		break;

		case IDCANCEL:
		{
		EndDlg (0);
		}
		break;

	}
	return;
}
//Member

//-------------------------------------------------------------------
//
Bool DefineCopyInformation :: FillMClassList ( void )
{
	
// ------------MerkmalListBox füllen


ENUMLONGKEY ELK;
	ELK.eKey = _ONr;
	ELK.eFcn = ( ENUMLONGKEYPROC) FillMKListBox;
	ELK.ePtr = &_MClass;
	
	DEX_EnumObjektMerkmale(ELK);

	return true;
}
//----------------------------------------------------------------
void DefineCopyInformation :: SetObjectInformation ( void )
{
	long Ident = DEX_GetObjIdent( _ONr);

	PBDDATA pbdData;
	char KText[MAXFCTNAME+1];
	KText[0] = '\0';
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);

	char outBuff[TEXTLEN+20];
	if ( KText[0] == NULL )
		strcat ( KText , ResString(ResID(IDS_ATTNODEFOBJCLASS,&g_pTE->RF()),70));
	KText[MAXFCTNAME] = '\0';


	ulong ulIdent = (ulong) Ident;
	char NewIdent[MAX_OKS_LENX+1];

	ClassFromIdentX (ulIdent,NewIdent);

	wsprintf (outBuff, "%ld:%s:%s", _ONr,NewIdent, KText);

/*---------------23.1.97---
	if ( DEX_GetIdBase() == 16 )
		wsprintf (outBuff, "%08ld:%08lx:%s", _ONr,Ident,  KText);
	else
		wsprintf (outBuff, "%08ld:%08ld:%s", _ONr,Ident, KText);
---------------*/


	_Object.SetText(outBuff);
	return;
}
//----------------------------------------------------------------
void DefineCopyInformation :: ShowObjectMerkmal ( long MKode )
{
	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return;

	// MerkmalsWert holen
	TARGETMERKMAL tm;

	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = _ONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = MKode;		// MerkmalsCode

	if( !DEX_GetTextMerkmal ( tm )) {
		DELETE ( pBuffer);
		return;
	}
	_ObjMerkmal.SetText(pBuffer);
	DELETE ( pBuffer);

	return;
}
//----------------------------------------------------------------
long DefineCopyInformation :: GetMCode ( int iIndex )
{
char * pBuff = new char [_MAX_PATH];
	if ( pBuff == NULL ) 
		return 0;
long Ident;
	_MClass.GetString (pBuff, iIndex, _MAX_PATH);
	char *ptr = strchr (pBuff, ':');
	if ( ptr == NULL ) {
		DELETE ( pBuff);
		return 0;
	} else
		*ptr = '\0';
	if ( DEX_GetMkBase() == 16 )
		Ident = strtoul ( pBuff, NULL, 16 );
	else
		Ident = atol(pBuff);

	*ptr = ':';
	DELETE ( pBuff);

	return Ident;	

}

//----------------------ERBEN.CXX-------------------------------------
