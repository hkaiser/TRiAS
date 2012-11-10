// ----------------Auswahl der FlaechenKlassen -----------------------------
// File: KOMPCLS.CXX

#include "kompp.hxx"   

#include "kompaktr.h"

#include "igeometr.hxx"
#include "triasdec.h"
#include "triasdef.h"
#include "kompdef.h"
#include "kpstatus.hxx"
#include <igeometr.hxx>
#include "cobjtree.hxx"
#include "gewbaum.hxx"
#include "kompcls.hxx"
#include "komphead.hxx"

#include "kompdll.hxx"
// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include "kompias.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32

//--------------------------------------------------------------------------
//-------------------------FlaechenKlasse---------------------------------------
//--------------------------------------------------------------------------


// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

TriasFlaechen :: TriasFlaechen (pWindow pW, uint res, ResourceFile &RF, long lIdent )
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _ObjClass ( this, IDLB_FLAECHENCLSAUSWAHL),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_isValid = false;
	_pW = pW;
	_pObj = NULL;
	_lClassIdent = NULL;
	FillObjClassList(lIdent);
	return;
}

#pragma warning (default: 4355)


TriasFlaechen :: ~TriasFlaechen (void)
{
//	_pW->Enable();
	DELETE_OBJ  ( _pObj);
	DELETE_OBJ  ( _lClassIdent);
}

void _XTENSN_EXPORT TriasFlaechen :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

		case IDLB_FLAECHENCLSAUSWAHL:
		{
		int iIndex = _ObjClass.GetFirstSelected();
		if ( iIndex == -1)
			return;
		int Count = _ObjClass.GetCount();
		DELETE_OBJ  ( _lClassIdent);

		_lClassIdent = new long [ Count + 1];
		*_lClassIdent = 0L;
		ErfasseObjKlasse ( iIndex );

		iIndex=_ObjClass.GetNextSelected ();

		while ( iIndex != -1 ) {
			ErfasseObjKlasse ( iIndex );
			iIndex=_ObjClass.GetNextSelected ();
		}
		}
		break;

	}
	return;
}
//----------------------------------------------------------------------

void _XTENSN_EXPORT TriasFlaechen :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		_isValid = true;
		if ( 0L == *_lClassIdent ) {
			DELETE_OBJ  ( _lClassIdent);
			EndDlg(0);
			return;
		}
		EndDlg (1);
		}
		break;

		case IDCANCEL:
		{
		_isValid = false;
		DELETE_OBJ  ( _lClassIdent);
		EndDlg (0);
		}
		break;
	}
	return;
}
//Member
//------------------------------------------------------------------
//-------------------------------------------------------------------
Bool TriasFlaechen :: FillObjClassList ( long lIdent )
{
//	Alle O'Klassen formal durchz‰hlen 
	short Typ = OTFlaeche;
OBJCLSRECHERCHE OR;
	OR.lIdent = lIdent;
	OR.pListBox = &_ObjClass;

	ENUMTEXTKEYEX ENTex;
	ENTex.eKey = NULL;		// NULL = aktuelle Sicht
	ENTex.eFcn = ( ENUMTEXTKEYEXPROC) SucheFlaechen;
	ENTex.ePtr = &OR;
	ENTex.eData = ( DWORD ) Typ;	
	DEX_EnumSightIdentsEx(ENTex);

    return true;
}
//-------------------------------------------------------------------
void TriasFlaechen :: ErfasseObjKlasse ( int iIndex) 
{

	char * pClassName = new char [_MAX_PATH];
	if ( !pClassName ) 
		return;
	_ObjClass.GetString (pClassName,iIndex,_MAX_PATH);

	char *ptr = strchr (pClassName, ':');
	if ( ptr ) {
		long Num = *_lClassIdent;
		*ptr = '\0';
		long Ident;
		ulong uIdent;
//
#if _MSC_VER < 1100
		IdentFromClassX(pClassName,&uIdent);
#else
		uIdent = _ObjClass.GetItemData (iIndex);		// Ident ist am Item gespeichert
#endif

		Ident = (long) uIdent;

		Num++;
		*_lClassIdent = Num;
		*(_lClassIdent + Num) = Ident;
	}
	DELETE_OBJ  ( pClassName);
	return;
}
//--------------------------------------------------------------------
long *TriasFlaechen :: FlaechenCls ( void) 
{

	if ( !_lClassIdent || 0L == *_lClassIdent )
		return NULL;

	long lDim = *_lClassIdent;
	if ( !_pObj)
		_pObj = new CTop_ObjTree;

	CEierUhr Wait (g_pTE->MVWind());

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) SucheFlaechenObjekte;

#if defined (WIN32)
	ResourceFile RF (g_pDLLName);
	ResString resCaption (ResID(IDS_FLAECHENKLASSEN, &RF), 128);
	ResString resObjekt (ResID(IDS_FLAECHENOBJEKTE, &RF), 128);

	
//	CStatus *pStatus = new CStatus ( _pW, &_RF,lDim, "Fl‰chenklassen");
	CStatus *pStatus = new CStatus ( _pW, &_RF,lDim, resCaption);
	pStatus->Show();
#endif

	long lCount = 0L;

	for ( long i = 0L; i < lDim; i++ ) {
		long lIdent = *(_lClassIdent + i + 1);

		ELK.eKey = lIdent;
		ELK.ePtr = _pObj;
		DEX_EnumIdentObjects(ELK);
		lCount ++;
#if defined (WIN32)
		if ( pStatus) {
			pStatus->SetValue( lCount, lIdent);
		}
#endif
	}
#if defined (WIN32)
	if ( pStatus)
		DELETE_OBJ  ( pStatus);
#endif

	lCount = (long) _pObj->Count();
	long * plONR = new long [lCount + 1];
	if ( !plONR) {
		DELETE_OBJ  ( _pObj);
		return NULL;
	}


#if defined (WIN32)
//	pStatus = new CStatus ( _pW, &_RF,lCount, "Fl‰chenobjekte");
	pStatus = new CStatus ( _pW, &_RF,lCount, resObjekt);
	pStatus->Show();
#endif

	lCount = 0L;
	CTable t (*_pObj);

	for ( t.First(); t.Valid(); t.Next()) {
		CTop_ObjLock l(t);
		if ( !l)
			continue;
		lCount++;
		*(plONR + lCount) = l->PObject();
#if defined (WIN32)
		if ( pStatus) {
			pStatus->SetValue( lCount, l->PObject());
		}
#endif
	}
	if ( 0L == lCount) {
		DELETE_OBJ  (_pObj);
		DELETE_OBJ  ( plONR);
		return NULL;
	}
	*plONR = lCount;

#if defined (WIN32)
	if ( pStatus)
		DELETE_OBJ  ( pStatus);
#endif
	return plONR;
}
//////////////////////////////////////////////////////////////////////
//-------------------------TRiASKlasse---------------------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

AlleTRiASKlassen :: AlleTRiASKlassen (pWindow pW, uint res, ResourceFile &RF, long lIdent, TR_OCLTree *pObj )
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _ObjClass ( this, IDLB_TRIASCLSAUSWAHL),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_isValid = false;
	_pW = pW;
	_lClassIdent = NULL;
	OKButton.Disable();
	FillObjClassList(lIdent,pObj);	// lIdent = ObjektNummer
	return;
}

#pragma warning (default: 4355)


AlleTRiASKlassen :: ~AlleTRiASKlassen (void)
{
	DELETE_OBJ  ( _lClassIdent);
}

void _XTENSN_EXPORT AlleTRiASKlassen :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

		case IDLB_TRIASCLSAUSWAHL:
		{
		int iIndex = _ObjClass.GetFirstSelected();
		if ( iIndex == -1)
			return;
		int Count = _ObjClass.GetCount();
		DELETE_OBJ  ( _lClassIdent);
		OKButton.Enable();

		_lClassIdent = new long [ 2 * Count + 1];

		*_lClassIdent = 0L;

		ErfasseObjKlasse ( iIndex );

		iIndex=_ObjClass.GetNextSelected ();

		while ( iIndex != -1 ) {
			ErfasseObjKlasse ( iIndex );
			iIndex=_ObjClass.GetNextSelected ();
		}
		}
		break;

	}
	return;
}
//----------------------------------------------------------------------

void _XTENSN_EXPORT AlleTRiASKlassen :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{

		_isValid = true;

		if ( NULL == _lClassIdent || 0L == * _lClassIdent) {

			DELETE_OBJ  ( _lClassIdent);

			return;
		}

		EndDlg (1);
		}
		break;

		case IDCANCEL:
		{
		_isValid = false;
		DELETE_OBJ  ( _lClassIdent);
		EndDlg (0);
		}
		break;
	}
	return;
}
//Member
//------------------------------------------------------------------
//-------------------------------------------------------------------
Bool AlleTRiASKlassen :: FillObjClassList ( long lONr , TR_OCLTree * pObj)
{
// KK020618 - Korrektur, um Gew‰sser und Bauwerke zu holen !
//	short Typ = OTFlaeche | OTLinie | OTPunkt;
	short Typ = OTLinie | OTPunkt;

	long lIdent = DEX_GetObjIdent(lONr);

	OBJCLSRECHERCHE OR;
	OR.lIdent = lIdent;
	OR.pListBox = &_ObjClass;

	CTable t (*pObj);

	for ( t.First(); t.Valid(); t.Next()){

		TR_OCLLock l(t);
		if (!l)
			continue;

		long lIdent = l->Ident();
		if ( l->Define () )
			SucheTRiASKlassen (lIdent,Typ, &OR);

	}

	return true;
}
//-------------------------------------------------------------------
void AlleTRiASKlassen :: ErfasseObjKlasse ( int iIndex) 
{

	char * pClassName = new char [_MAX_PATH];
	if ( !pClassName ) 
		return;
	_ObjClass.GetString (pClassName,iIndex,_MAX_PATH);

	char *ptr = strchr (pClassName, ':');
	if ( ptr ) {
		long Num = *_lClassIdent;
		*ptr = '\0';
		ptr++;
		if ( *ptr != 'F' && *ptr != 'L' && *ptr != 'P')
			return;
		long Ident;

		ulong uIdent;

#if _MSC_VER < 1100
		IdentFromClassX(pClassName,&uIdent);
#else
		uIdent = _ObjClass.GetItemData (iIndex);		// Ident ist am Item gespeichert
#endif

		Ident = (long) uIdent;

		Num++;
		*_lClassIdent = Num;
		*(_lClassIdent + Num) = Ident;
		Num++;
		*_lClassIdent = Num;
		if (*ptr == 'F' ) 
			*(_lClassIdent + Num) = (long)OTFlaeche;

		if (*ptr == 'L' ) 
			*(_lClassIdent + Num) = (long)OTLinie;

		if (*ptr == 'P' ) 
			*(_lClassIdent + Num) = (long)OTPunkt;
		
	}

	DELETE_OBJ  ( pClassName);
	return;
}
//--------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//-------------------------TRiASRechercheKlasse---------------------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

TRiASRechercheKlassen :: TRiASRechercheKlassen (pWindow pW, uint res, ResourceFile &RF, long lIdent , TR_IDMTree *pIDM)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _ObjClass ( this, IDC_FLSTOKLASSEN),
	       _InClass ( this, IDC_FLSTINNEN),
	       _InAusClass ( this, IDC_FLSTINAUS),
		_InText ( this,IDC_FLSTINNENTEXT),
		_InAusText ( this,IDC_FLSTINAUSTEXT),
		_NewButton (this,IDC_BUTTONNEW),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_isValid = false;
	_pW = pW;
	_lClassIdent = NULL;
	_lObjIn = NULL;
	_lObjInAus = NULL;
	_pIDM = NULL;
	if ( pIDM)
		_pIDM = pIDM;
	char *pText = new char [_MAX_PATH];

	if ( pText) {

		long lIIdent = DEX_GetObjIdent ( lIdent);
		ulong lSMCode = DEX_GetObjNameMCode(lIIdent);
		char *pBuffer = new char [_MAX_PATH];
		if ( pBuffer ) {
			*pBuffer = '\0';
			if ( lSMCode != 0L) {
			
		// MerkmalsWert holen
				TARGETMERKMAL tm;
				tm.dwSize = sizeof(TARGETMERKMAL);
				tm.lTarget = lIdent;		// ObjektNummer
				tm.lMCode = (long)lSMCode;		// MerkmalsCode ObjektName
				tm.imaxLen = _MAX_PATH - 1;
				tm.pMText =pBuffer;		// Puffer
				tm.iTTyp = TT_Objekt;

				if( !DEX_GetTextMerkmal ( tm ) ) {

					tm.lMCode = DEX_GetUniqueIdentMCodeEx (DEX_GetObjectProject(lIdent));

					if( !DEX_GetTextMerkmal ( tm ) ) 
						strcpy ( pBuffer , ResString(ResID(IDS_KEINOBJEKTNAME,&g_pTE->RF()),70).Addr() );
//						strcpy ( pBuffer ,"Kein Objektname ");
				}
			}


//		wsprintf ( pText, "Rechercheergebnis %ld",lIdent);
			wsprintf ( pText, ResString(ResID(IDS_RECHERCHEERGEBNISEX,&g_pTE->RF()),70).Addr(),pBuffer);
			DELETE_OBJ(pBuffer);
		}

		SetCaption(pText);
		DELETE_OBJ  ( pText);
	}

	_lONNew = -1L;

	_InText.Disable();
	_InAusText.Disable();
	OKButton.Disable();
	_NewButton.Disable();

	FillObjClassList();

	m_InClass.clear();
	m_InAusClass.clear();

	return;
}

#pragma warning (default: 4355)


TRiASRechercheKlassen :: ~TRiASRechercheKlassen (void)
{
	DELETE_OBJ  ( _lClassIdent);
	DELETE_OBJ  ( _lObjIn);
	DELETE_OBJ  ( _lObjInAus);
}

void _XTENSN_EXPORT TRiASRechercheKlassen :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

		case IDC_FLSTOKLASSEN:
		{
		_InClass.Clear();
		_InAusClass.Clear();
		OKButton.Disable();
		_NewButton.Disable();
		int iIndex = _ObjClass.GetFirstSelected();
		if ( iIndex == -1)
			return;
		int Count = _ObjClass.GetCount();
		DELETE_OBJ  ( _lClassIdent);

		_lClassIdent = new long [ 2 * Count + 1];
		*_lClassIdent = 0L;

		ErfasseObjKlasse ( iIndex );

		iIndex=_ObjClass.GetNextSelected ();

		while ( iIndex != -1 ) {
			ErfasseObjKlasse ( iIndex );
			iIndex=_ObjClass.GetNextSelected ();
		}
		FillRechercheList();
	
		}
		break;

		case IDC_FLSTINNEN:
		{
		int iIndex = _InClass.GetFirstSelected();
		if ( iIndex == -1)
			return;
		int Count = _InClass.GetCount();
		OKButton.Enable();
		_NewButton.Disable();
		_lONNew = -1L;
	
		DELETE_OBJ  ( _lObjIn);

		_lObjIn = new long [ Count + 1];
		*_lObjIn = 0L;
		ErfasseInKlasse ( iIndex ,&m_InClass);

		iIndex=_InClass.GetNextSelected ();

		while ( iIndex != -1 ) {
			ErfasseInKlasse ( iIndex ,&m_InClass);
			iIndex=_InClass.GetNextSelected ();
		}

		}
		break;

		case IDC_FLSTINAUS:
		{

		int iIndex = _InAusClass.GetFirstSelected();
		if ( iIndex == -1)
			return;
		int Count = _InAusClass.GetCount();
		OKButton.Enable();
		_NewButton.Disable();
		_lONNew = -1L;
		DELETE_OBJ  ( _lObjIn);

		_lObjInAus = new long [ Count + 1];
		*_lObjInAus = 0L;

		ErfasseInAusKlasse ( iIndex ,&m_InAusClass);

		iIndex=_InAusClass.GetNextSelected ();

		while ( iIndex != -1 ) {
			ErfasseInAusKlasse ( iIndex ,&m_InAusClass);
			iIndex=_InAusClass.GetNextSelected ();
		}

		}
		break;

	}
	return;
}
//----------------------------------------------------------------------

void _XTENSN_EXPORT TRiASRechercheKlassen :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
		_isValid = true;

		EndDlg (1);
		}
		break;

		case IDCANCEL:
		{
		_isValid = false;
		EndDlg (0);
		}
		break;

		case IDC_BUTTONNEW:
		{
		_isValid = true;
		EndDlg (-1);
		}
		break;

	}
	return;
}
//Member
//------------------------------------------------------------------
//-------------------------------------------------------------------
bool TRiASRechercheKlassen :: FillObjClassList ( void )
{
//	Alle O'Klassen formal durchz‰hlen 

	if ( !_pIDM)
		return false;
	OKButton.Disable();
	_NewButton.Disable();

	char *outBuff = new char [_MAX_PATH];
	if ( !outBuff)
			return false;

	char NewIdent [MAX_OKS_LENX + 1];
	char CTyp = ' ';


	PBDDATA pbdData;
	char KText[TEXTLEN+1];
	KText[0] = '\0';
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';


	CTable t (*_pIDM);
	for ( t.First(); t.Valid(); t.Next()){
		TR_IDMLock l(t);
		if (!l)
			continue;

		if ( !l->OBJP() && !l->OBJLI() && !l->OBJLIA() && !l->OBJFI() && !l->OBJFIA())
			continue;

		pbdData.pbdCode = l->Ident();
		pbdData.pbdKText = KText;
		pbdData.pbdKTextLen = sizeof(KText) -1;
		pbdData.pbdLTextLen = 0;

		DEX_GetPBDData (pbdData);

		if ( KText[0] == NULL )
			strcat ( KText, ResString(ResID(IDS_KOMPNODEFIDENT,&g_pTE->RF()),70));
		KText[TEXTLEN] = '\0';

		ulong ulIdent = (ulong) l->Ident();

	#if _MSC_VER < 1100
		ClassFromIdentX ( ulIdent, NewIdent);
	#else
		HPROJECT hPr = DEX_GetObjectsProject(ulIdent);
		ClassFromIdentX ( hPr,ulIdent, NewIdent);
	#endif

		short iTyp = l->Typ();
		if ( (iTyp & OTPunkt) != 0 ) {
			if ( l->OBJP()) {
				CTyp ='P';
				wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);


		#if _MSC_VER < 1200
				_ObjClass.AddString (outBuff);
		#else
			// wenn mehr als eine Datenquelle geˆffnet ist, dann den Namen der zugehˆrigen in
			// Klammern hinten anh‰ngen
				if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
					char cbBuffer[_MAX_PATH];

					TX_ASSERT(NULL != hPr);
					if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
						strcat (outBuff, " (");
						strcat (outBuff, cbBuffer);
						strcat (outBuff, ")");
					}
				}

		// Ident am jeweiligen Item speichern
				int iIndex = _ObjClass.AddString (outBuff);

				_ObjClass.SetItemData (iIndex, ulIdent);

		#endif // _MSC_VER < 1200

			}
		}
		if ( (iTyp & OTLinie) != 0 ) {
			if ( l->OBJLI() || l->OBJLIA()) {
				CTyp ='L';
				wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);

		#if _MSC_VER < 1200
				_ObjClass.AddString (outBuff);
		#else
			// wenn mehr als eine Datenquelle geˆffnet ist, dann den Namen der zugehˆrigen in
			// Klammern hinten anh‰ngen
				if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
					char cbBuffer[_MAX_PATH];

					TX_ASSERT(NULL != hPr);
					if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
						strcat (outBuff, " (");
						strcat (outBuff, cbBuffer);
						strcat (outBuff, ")");
					}
				}

		// Ident am jeweiligen Item speichern
				int iIndex = _ObjClass.AddString (outBuff);

				_ObjClass.SetItemData (iIndex, ulIdent);

		#endif // _MSC_VER < 1200

			}
		}
		if ( (iTyp & OTFlaeche) != 0 ) {
			if ( l->OBJFI() || l->OBJFIA()) {
				CTyp ='F';
				wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);

		#if _MSC_VER < 1200
				_ObjClass.AddString (outBuff);
		#else
			// wenn mehr als eine Datenquelle geˆffnet ist, dann den Namen der zugehˆrigen in
			// Klammern hinten anh‰ngen
				if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
					char cbBuffer[_MAX_PATH];

					TX_ASSERT(NULL != hPr);
					if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
						strcat (outBuff, " (");
						strcat (outBuff, cbBuffer);
						strcat (outBuff, ")");
					}
				}

		// Ident am jeweiligen Item speichern
				int iIndex = _ObjClass.AddString (outBuff);

				_ObjClass.SetItemData (iIndex, ulIdent);

		#endif // _MSC_VER < 1200

			}
		}
	}
	DELETE_OBJ  ( outBuff);
    return true;
}
//-------------------------------------------------------------------
void TRiASRechercheKlassen :: ErfasseObjKlasse ( int iIndex) 
{

	char * pClassName = new char [_MAX_PATH];
	if ( !pClassName ) 
		return;
	_ObjClass.GetString (pClassName,iIndex,_MAX_PATH);

	char *ptr = strchr (pClassName, ':');
	if ( ptr ) {
		long Num = *_lClassIdent;
		*ptr = '\0';
		ptr++;
		if ( *ptr != 'F' && *ptr != 'L' && *ptr != 'P')
			return;
		long Ident;
		ulong uIdent;

#if _MSC_VER < 1100
		IdentFromClassX(pClassName,&uIdent);
#else
		uIdent = _ObjClass.GetItemData (iIndex);		// Ident ist am Item gespeichert
#endif


		Ident = (long) uIdent;

		Num++;
		*_lClassIdent = Num;
		*(_lClassIdent + Num) = Ident;
		Num++;
		*_lClassIdent = Num;
		if (*ptr == 'F' ) 
			*(_lClassIdent + Num) = (long)OTFlaeche;

		if (*ptr == 'L' ) 
			*(_lClassIdent + Num) = (long)OTLinie;

		if (*ptr == 'P' ) 
			*(_lClassIdent + Num) = (long)OTPunkt;
		
	}

	DELETE_OBJ  ( pClassName);
	return;
}
//-------------------------------------------------------------------
void TRiASRechercheKlassen :: ErfasseInKlasse ( int iIndex, CObjectMap *pOM) 
{

	char * pClassName = new char [_MAX_PATH];
	if ( !pClassName ) 
		return;
	if ( !_lObjIn)
		return;

	_InClass.GetString (pClassName,iIndex,_MAX_PATH);

	_NewButton.Disable();

	CObjectMap::iterator it = pOM->find(pClassName);

	if (it == pOM->end())
		return;

	long lONr = (*it).second;	// Objektnummer

	if ( lONr != 0 && lONr != -1 ) {
		long Num = *_lObjIn;
		Num++;
		*_lObjIn = Num;
		*(_lObjIn + Num) = lONr;
	}


	DELETE_OBJ  ( pClassName);
	return;
}
//-------------------------------------------------------------------
void TRiASRechercheKlassen :: ErfasseInAusKlasse ( int iIndex ,  CObjectMap *pOM) 
{

	char * pClassName = new char [_MAX_PATH];
	if ( !pClassName ) 
		return;
	_InAusClass.GetString (pClassName,iIndex,_MAX_PATH);
	_NewButton.Disable();

	CObjectMap::iterator it = pOM->find(pClassName);

	if (it == pOM->end())
		return;

	long lONr = (*it).second;	// Objektnummer

	if (  lONr != 0 && lONr != -1  ) {
		long Num = *_lObjInAus;
		Num++;
		*_lObjInAus = Num;
		*(_lObjInAus + Num) = lONr;
	}

	DELETE_OBJ  ( pClassName);
	return;
}
//--------------------------------------------------------------------
//-------------------------------------------------------------------
bool TRiASRechercheKlassen :: FillRechercheList ( void )
{

	if ( !_pIDM)
		return false;

	if ( !_lClassIdent || *_lClassIdent == 0L)
		return false;

	CTable t (*_pIDM);

	long lICount = 0L;
	long lIACount = 0L;
	long lDim = *_lClassIdent;

	for ( long i = 0L; i < lDim; i++ ) {
		long j = i*2;
		long lIdent = *(_lClassIdent + j + 1);
		short iGITyp = (short)*(_lClassIdent + j + 2);

		if ( t.Find ( &lIdent)) {
			TR_IDMLock l(t);
			TR_IDOTree *pObjI = NULL;
			TR_IDOTree *pObjIA = NULL;

			if ( iGITyp == OTPunkt) {
				pObjI =l->OBJP();
			}

			if ( iGITyp == OTLinie) {
				pObjI =l->OBJLI();
				pObjIA =l->OBJLIA();
			}

			if ( iGITyp == OTFlaeche) {
				pObjI =l->OBJFI();
				pObjIA =l->OBJFIA();
			}

			if ( pObjI ) {
				lICount = lICount + pObjI->Count();
				FillErgebnisListe(pObjI,&_InClass,&m_InClass);
			}

			if ( pObjIA ) {
				lIACount = lIACount + pObjIA->Count();
				FillErgebnisListe(pObjIA, &_InAusClass, &m_InAusClass);
			}

		}

	}
	_InText.Enable();
	_InAusText.Enable();
	char *pText = new char [_MAX_PATH];
	if ( pText) {
		wsprintf ( pText,"innen : %ld ",lICount);
		_InText.SetText(pText);
		wsprintf ( pText,"innen/auﬂen : %ld ",lIACount);
		_InAusText.SetText(pText);
		DELETE_OBJ  ( pText);
	}

	return true;
}


//typedef map<CString, pair<DWORD, HPROJECT>, CCompareNoCase> CComboEntryMap; 


//////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------
bool TRiASRechercheKlassen :: FillErgebnisListe ( TR_IDOTree *pObj , MultiSelListBox *p, CObjectMap *pOM)
{

	if (!pObj)
		return false;

	if (!p)
		return false;

	char *pBuffer = new char [_MAX_PATH];
	char *outBuff = new char [_MAX_PATH];

	if ( !pBuffer || !outBuff ) {
		DELETE_OBJ  ( outBuff);
		DELETE_OBJ  ( pBuffer);
		return false;
	}

	*pBuffer = '\0';

	CTable t (*pObj);
	for ( t.First(); t.Valid(); t.Next()){
		TR_IDOLock l(t);
		if (!l)
			continue;

		long lONr = l->Object();
		long lIdent = DEX_GetObjIdent ( lONr);


		ulong lSMCode = DEX_GetObjNameMCode(lIdent);

		if ( ((CKompiasExtension *)g_pTE)->ObjektIstGewaesser(lONr) )
			lSMCode = ((CKompiasExtension *)g_pTE)->KPHeader()->CodeGewNr();

		if ( ((CKompiasExtension *)g_pTE)->ObjektIstBauwerk(lONr) )
			lSMCode = ((CKompiasExtension *)g_pTE)->KPHeader()->CodeBauwNr();

		*pBuffer = '\0';
		if ( lSMCode != 0L) {
			
		// MerkmalsWert holen
			TARGETMERKMAL tm;
			tm.dwSize = sizeof(TARGETMERKMAL);
			tm.lTarget = lONr;		// ObjektNummer
			tm.lMCode = (long)lSMCode;		// MerkmalsCode ObjektName
			tm.imaxLen = _MAX_PATH - 1;
			tm.pMText =pBuffer;		// Puffer
			tm.iTTyp = TT_Objekt;

			if( !DEX_GetTextMerkmal ( tm ) ) {

				tm.lMCode = DEX_GetUniqueIdentMCodeEx (DEX_GetObjectProject(lONr));

				if( !DEX_GetTextMerkmal ( tm ) ) 
					strcpy ( pBuffer , ResString(ResID(IDS_KEINOBJEKTNAME,&g_pTE->RF()),70).Addr() );
//						strcpy ( pBuffer ,"Kein Objektname ");
			}



		}

//		wsprintf (outBuff, "%ld:%s", lONr,pBuffer);
		wsprintf (outBuff, "%s", pBuffer);
		p->AddString (outBuff);

		CObjectMap::iterator it = pOM->find(pBuffer);

		if (it == pOM->end())
//			pOM->insert(CObjectMap::value_type( os_string(pBuffer)),lONr);
			pOM->insert(CObjectMap::value_type( pBuffer,lONr));

	}

	DELETE_OBJ  ( pBuffer);
	DELETE_OBJ  ( outBuff);
	return true;
}

//----------------------------------------------------------------------
//----------------------KOMPCLS.CXX-------------------------------------
