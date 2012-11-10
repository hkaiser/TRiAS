// Anzeigen von Objekten nach GI-Vergleich in einer Ansicht -----------------------------
// File: CLASSGI.CXX


#include "statistp.hxx"
#include "geostat.h"
#include <igeometr.hxx>

#include "dirmath.h"

#include "idkey.hxx"
#include "objkey.hxx"
#include "classkey.hxx"
#include "dbinfo.hxx"
#include "classgi.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32


// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

ObjectClassification :: ObjectClassification (pWindow pW, uint res, ResourceFile &RF, IDMTree *pIDM, OBJTree *pOBJ, GICLATree *pGICLA)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _ObjClassList (this,IDC_LISTOBJCLASS),
	       _MassEinhList (this,IDC_LISTMASSEINH),
	       _ElementeTyp (this,IDT_TEXTELEMENTS),
	       _ElementeZahl (this,IDT_NUMBERELEMENTS),
	       _EinzelButton (this,IDC_BUTTONEINZEL),
	       _IntervallButton (this,IDC_BUTTONINTERVALL),
	       _VerglWertMin (this,IDT_VERGLWERTMIN),
	       _VerglWertMax (this,IDT_VERGLWERTMAX),
	       _MathOpListOne (this,IDC_LISTMATHOPONE),
	       _MathOpListTwo (this,IDC_LISTMATHOPTWO),
	       _IntervallWert (this,IDT_INTERVALLWERT),
	       _IntervallText (this,IDT_INTERVALLTEXT),
	       _ObjektKlasse (this,IDT_OBJEKTKLASSE),
	       _RF (RF),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_pW = pW;
//	pW->Disable();
	_pHelpText = NULL;

	_pHelpText = CHelpTextX :: CreateInstance (this, IDT_HILFETEXT);
	if (_pHelpText == NULL)
		return;

	_Einheit = -1L;
	_Operat1 = -1;
	_Operat2 = -1;
//	_ObjKlasse = -1L;
	_ObjKlasse = 0L;	// Korr. 6.4.95
	_isObjectFound = FALSE;

	_iOklGiTyp = 0;		// GI-Typ : OTFlaeche oder OTLinie
	_iMETyp = 0;		// MassEinheit-Typ : OTFlaeche oder OTLinie

	_pGICLA = pGICLA;		// GI-Intervall
	_pClaObj = NULL;	// Objektklasse im Intervall

//	analog IDC_BUTTONEINZEL
	_EinzelButton.SetState ( TRUE );
	_VerglWertMin.SetFocus();
	_IntervallButton.SetState ( FALSE ); 
	_IntervallWert.Disable();
	_IntervallText.Disable();
//	Voreinstellungen
	_IntervallWert.SetNumEditMode ( NumEditX :: NEM_NoTest);
	_VerglWertMin.SetNumEditMode ( NumEditX :: NEM_NoTest);
	_VerglWertMax.SetNumEditMode ( NumEditX :: NEM_NoTest);

	_pIDM = pIDM;
	_pOBJ = pOBJ;
	FillObjKlassenList ();

	_ObjKlasse = GetFirstObjClass ();	// iIndex = 0 holen + Typ
						// iOkl-.. bestimmen
	ShowPBDText ( _ObjKlasse, 'i');

	if ( isLinie() )
		LinienMassEinhListe();

	if ( isFlaeche() )
		FlaechenMassEinhListe();

	SetStandardMathOp ( TRUE );

	_WERT[0] = '\0';
	_Wert = 0.0;
	_IntervallWert.SetText(NULL);
	_MinVglWert = _MinWert;
	_MaxVglWert = _MaxWert;

}

#pragma warning (default: 4355)


ObjectClassification :: ~ObjectClassification (void)
{
	DELETE_OBJ (_pHelpText);
//	_pW->Enable();
}

//
void ObjectClassification :: FillObjKlassenList ( void )
{

long Ident, lIDCount= 0L;

	CTable t(*_pIDM );

	for (t.First(); t.Valid() ; t.Next()  ) {
	
		IDMLock l(t);

		Ident = ( l->Ident());
		short Typ = ( l->IdentGiTyp());
		StoreObjKlassList ( &_RF, Ident ,&_ObjClassList , Typ);
		lIDCount++;
	} 
}
//---------------------------------------------------------------

//
void ObjectClassification :: FillMathOpList ( int iIndex, void *pData)
{

	((ListBox *)pData) -> AddString ( ResString (ResID (IDS_KLEINER, &_RF), 30));
	((ListBox *)pData) -> AddString ( ResString (ResID (IDS_KLEINERGLEICH, &_RF), 30));
	((ListBox *)pData) -> AddString ( ResString (ResID (IDS_GLEICH, &_RF), 30));
	((ListBox *)pData) -> AddString ( ResString (ResID (IDS_UNGLEICH, &_RF), 30));
	((ListBox *)pData) -> AddString ( ResString (ResID (IDS_GROESSER, &_RF), 30));
	((ListBox *)pData) -> AddString ( ResString (ResID (IDS_GROESSERGLEICH, &_RF), 30));
	((ListBox *)pData) -> ChangeCurrentIndex ( iIndex );	//DEFAULT

	return; 
}
//---------------------------------------------------------------

//
void ObjectClassification :: SetStandardMathOp ( Bool Flag )
{
//	TRUE : EinzelButton

	_MathOpListOne.Clear();
	_MathOpListTwo.Clear();
	if ( Flag ) {
		FillMathOpList( GOGroesserGleich, &_MathOpListOne);
		FillMathOpList( GOKleinerGleich , &_MathOpListTwo);
		_MathOpListOne.Enable();
		_MathOpListTwo.Enable();
		_VerglWertMin.Enable();
		_VerglWertMax.Enable();
		_Operat1 = (long) GOGroesserGleich;
		_Operat2 = (long) GOKleinerGleich;
		_Wert = 0.0;
	} else {
		FillMathOpList( GOGroesserGleich, &_MathOpListOne);
		FillMathOpList( GOKleiner, &_MathOpListTwo);
		_MathOpListOne.Disable();
		_MathOpListTwo.Disable();
		_VerglWertMin.Disable();
		_VerglWertMax.Disable();
		_Operat1 = (long) GOGroesserGleich;
		_Operat2 = (long) GOKleiner;
	}

	return; 
}
//---------------------------------------------------------------

void ObjectClassification :: FlaechenMassEinhListe ( void )
{
int iIndex;
	if ( _iMETyp != OTFlaeche ) {
		if ( _iMETyp == OTLinie ) {
			_MassEinhList.Clear();
			_Einheit = 0L;
		}
		_MassEinhList.AddString ( ResString (ResID (IDT_UNITQM, &_RF), 10));
		_MassEinhList.AddString ( ResString (ResID (IDT_UNITHA, &_RF), 10));
		_MassEinhList.AddString ( ResString (ResID (IDT_UNITQKM, &_RF), 10));
		_iMETyp = OTFlaeche;
	}
	iIndex = DefineMinMaxZeile();
	_MassEinhList.ChangeCurrentIndex ( iIndex);
	return;
}
//---------------------------------------------------------
void ObjectClassification :: LinienMassEinhListe ( void )
{
int iIndex;
	if ( _iMETyp != OTLinie ) {
		if ( _iMETyp == OTFlaeche ) {
			_MassEinhList.Clear();
			_Einheit = 0L;
		}
		_iMETyp = OTLinie;
		_MassEinhList.AddString ( ResString (ResID (IDT_UNITM, &_RF), 10));
		_MassEinhList.AddString ( ResString (ResID (IDT_UNITKM, &_RF), 10));
	}
	iIndex = DefineMinMaxZeile();
	_MassEinhList.ChangeCurrentIndex ( iIndex);
	return;
}
//---------------------------------------------------------
Bool ObjectClassification :: isLinie ( void ) 
{
	if ( _iOklGiTyp == OTLinie )
		return TRUE;
	else
		return FALSE;
}
//---------------------------------------------------------
Bool ObjectClassification :: isFlaeche ( void ) 
{
	if ( _iOklGiTyp == OTFlaeche )
		return TRUE;
	else
		return FALSE;
}
//---------------------------------------------------------

void _XTENSN_EXPORT ObjectClassification :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

	case IDC_LISTOBJCLASS:
		{
		_ObjKlasse = GetObjClass();	// Ident
		if ( isLinie() )
			LinienMassEinhListe();
		if ( isFlaeche() )
			FlaechenMassEinhListe();
		}
		if ( _EinzelButton.GetState() ) {
			SetStandardMathOp (TRUE);
		} else {
			SetStandardMathOp (FALSE);
		}

		_WERT[0] = '\0';
		_Wert = 0.0;
		_IntervallWert.SetText(NULL);
		ShowPBDText ( _ObjKlasse, 'i' );

		break;

	case IDC_LISTMASSEINH:
		{
		TestVergleichsWert();
		SaveIntervallWert();
		_Einheit = GetMassEinheit();
		if ( _ObjKlasse != 0 ) {
			DefineObjClass ( );
		}
		_pHelpText -> SetHelpText (ResID(IDH_HELPMASSEINHEIT,&_RF));

		}
		break;


	case IDC_LISTMATHOPONE:
		{
		TestVergleichsWert();
		_Operat1 = GetMathOp(&_MathOpListOne);

		if ( _EinzelButton.GetState() ) {
			PruefeEinzelAbfrage ();
		}
		}
		break;

	case IDC_LISTMATHOPTWO:
		{
		TestVergleichsWert();
		_Operat2 = GetMathOp(&_MathOpListTwo);
		
		if ( _EinzelButton.GetState() ) {
			PruefeEinzelAbfrage();
		}
		}
		break;


	}
}

//--------------------------------------------------------------------
long ObjectClassification :: GetExtrema ( double *pMin, double *pMax )
{
long Count = 0;
	//	Maximum-Minimum besorgen und eintragen

	if ( _pIDM == NULL )
		return FALSE;

	CTable t(*_pIDM);

	if ( t.Find (&_ObjKlasse) ) {
	
		IDMLock l(t);
		if ( isFlaeche() ) {
			*pMin = l->rAreaMin();
			*pMax = l->rAreaMax();
			Count = l->Flaeche();
		}
		if ( isLinie() ) {
			*pMin = l->rPolyLenMin();
			*pMax = l->rPolyLenMax();
			Count = l->Linie();
		}
	}
	_MinWert = *pMin;
	_MaxWert = *pMax;

	return Count;
}

//--------------------------------------------------------------------
void ObjectClassification :: DefineObjClass ( void )
{
double Wert;
	//	Maximum-Minimum besorgen und eintragen


	char * pNum = new char [_MAX_PATH];
//	char * pNum = new char [20];
	if ( pNum == NULL ) {
		DELETE_OBJ ( pNum );
		return;
	}


	CTable t(*_pIDM);

	if ( t.Find (&_ObjKlasse) ) {
	
		IDMLock l(t);
	
		if ( isFlaeche() ) {
		   if ( _MinVglWert != -1.0 ) {
			if ( _EinzelButton.GetState() ) 
				Wert = _MinVglWert / (double) _Einheit;
			else
				Wert = l->rAreaMin() / (double) _Einheit;
			ST_DtoA ( pNum, "%8.3f", Wert);
			_VerglWertMin.SetText( pNum );
		   }

		   if ( _MaxVglWert != -1.0 ) {
			if ( _EinzelButton.GetState() ) 
				Wert = _MaxVglWert / (double) _Einheit;
			else
				Wert = l->rAreaMax() / (double) _Einheit;
			ST_DtoA ( pNum, "%8.3f", Wert);
			_VerglWertMax.SetText( pNum );
		   }
		} else {
		   if ( _MinVglWert != -1.0 ) {
			if ( _EinzelButton.GetState() ) 
				Wert = _MinVglWert / (double) _Einheit;
			else
				Wert = l->rPolyLenMin() / (double) _Einheit;
			ST_DtoA ( pNum, "%8.3f", Wert );
			_VerglWertMin.SetText( pNum );
		   }

		   if ( _MaxVglWert != -1.0 ) {
			if ( _EinzelButton.GetState() ) 
				Wert = _MaxVglWert / (double) _Einheit;
			else
				Wert = l->rPolyLenMax() / (double) _Einheit;
			ST_DtoA ( pNum, "%8.3f", Wert);
			_VerglWertMax.SetText( pNum );
		   }
		}

		if ( _Wert > 0.0 ) {
			Wert = _Wert/ ( double ) _Einheit;
			ST_DtoA ( pNum, "%8.3f",Wert);
			_IntervallWert.SetText( pNum );
		}

		// ID _Key in OBJKLASSEN-Feld anzeigen


		DELETE_OBJ ( pNum );

	// ID _Key in OBJKLASSEN-Feld anzeigen


PBDDATA pbdData;
char KText[MAXFCTNAME+1];
		KText[0] = '\0';
		memset (&pbdData, '\0', sizeof(PBDDATA));
	
		pbdData.dwSize = sizeof(PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = _ObjKlasse;
		pbdData.pbdKText = KText;
		pbdData.pbdKTextLen = sizeof(KText) -1;
		pbdData.pbdLTextLen = 0;
		if ( DEX_GetPBDData (pbdData) == EC_OKAY ) {

			if ( KText[0] == '\0' )
				strcpy ( KText, ResString(ResID(IDS_NODEFOBJCLASS,&_RF ),70));
			KText[MAXFCTNAME] = '\0';
		} else {
			strcpy ( KText, ResString(ResID(IDS_NODEFOBJCLASS,&_RF ),70));
			KText[MAXFCTNAME] = '\0';
		}

		_ObjektKlasse.SetText( KText );

	}

	return;
}
//--------------------------------------------------------------------
long ObjectClassification :: GetFirstObjClass ( void )
{
long Ident = 0L;
int iIndex = 0;		// 1.Okl

char *pBuffer = new char [_MAX_PATH];
	_iOklGiTyp = 0;			// Typ unbekannt
	if ( pBuffer == NULL )
		return Ident;
	_ObjClassList.ChangeCurrentIndex ( iIndex);
	_ObjClassList.GetCurrentString (pBuffer);

	char *ptr = strchr (pBuffer, ':');
	if ( ptr == NULL ) {
		DELETE_OBJ ( pBuffer );
		return Ident;
	} else {
		if ( *(ptr+1) == 'L' )
			_iOklGiTyp = OTLinie;
		if ( *(ptr+1) == 'F' )
			_iOklGiTyp = OTFlaeche;
		*ptr = '\0';
	}


	ulong uIdent = (ulong)Ident;

//	IdentFromClassX (pBuffer,&uIdent);

#if _MSC_VER < 1200

	HRESULT hr = IdentFromClassX (pBuffer, &uIdent);
	if (FAILED(hr)) {
		DELETE_OBJ(pBuffer);
		return 0;
	}
#else
	uIdent = _ObjClassList.GetItemData (iIndex);		// Ident ist am Item gespeichert
	TX_ASSERT(0 != uIdent);
#endif // _MSC_VER < 1200


	Ident = (long) uIdent;

	DELETE_OBJ ( pBuffer );
	return Ident;


}
//--------------------------------------------------------------------------
void ObjectClassification :: SetObjClass ( double * pMin, double * pMax )
{
double Wert;


//	char * pNum = new char [20];
	char * pNum = new char [_MAX_PATH];

	if ( pNum == NULL ) {
		DELETE_OBJ ( pNum );
		return;
	}

	if ( isFlaeche() ) {
		Wert = *pMin / double ( _Einheit );
		ST_DtoA ( pNum, "%8.3f", Wert);
		_VerglWertMin.SetText( pNum );

		Wert = *pMax / double ( _Einheit );
		ST_DtoA ( pNum, "%8.3f", Wert);
		_VerglWertMax.SetText( pNum );
	} else {
		Wert = *pMin / double ( _Einheit );
		ST_DtoA ( pNum, "%8.3f", Wert);
		_VerglWertMin.SetText( pNum );

		Wert = *pMax / double ( _Einheit );
		ST_DtoA ( pNum, "%8.3f", Wert);
		_VerglWertMax.SetText( pNum );
	}

	DELETE_OBJ ( pNum );

	// ID _Key in OBJKLASSEN-Feld anzeigen


PBDDATA pbdData;
char KText[MAXFCTNAME+1];

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = _ObjKlasse;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	if ( DEX_GetPBDData (pbdData) == EC_OKAY ) {

		if ( KText[0] == '\0' )
			strcpy ( KText, ResString(ResID(IDS_NODEFOBJCLASS,&_RF ),70));
		KText[MAXFCTNAME] = '\0';
	} else {
		strcpy ( KText, ResString(ResID(IDS_NODEFOBJCLASS,&_RF ),70));
		KText[MAXFCTNAME] = '\0';
	}

	_ObjektKlasse.SetText( KText );

	if ( _EinzelButton.GetState() ) {
		SetStandardMathOp (TRUE);
	} else {
		SetStandardMathOp (FALSE);
	}

	return;
}
//--------------------------------------------------------------------
int ObjectClassification :: DefineMinMaxZeile ( void )
{
int iIndex = -1;
	_isObjectFound = FALSE;

double Min,Max;
long FVglWert[3];
long LVglWert[2];

	FVglWert[2] = (long) QuadratKiloMeter;
	FVglWert[1] = (long) Hektar;
	FVglWert[0] = (long) QuadratMeter;
	LVglWert[1] = (long) KiloMeter;
	LVglWert[0] = (long) Meter;
	long Count = GetExtrema (&Min, &Max);
	if ( Count > 0L ) {
		if ( isFlaeche()) {
			_Einheit = FVglWert[0];
			iIndex = 0;
			for ( long i = 1; i < 3; i++ ) {
			   if ( Min / (double)FVglWert[i] >= 1.0 ) {
				_Einheit = FVglWert[i];		
				iIndex = (int)i;
			   }
			}
		}
		if ( isLinie()) {
			_Einheit = LVglWert[0];
			iIndex = 0;
			 if ( Min / (double)LVglWert[1] >= 1.0 ) {
				_Einheit = LVglWert[1];		
				iIndex = 1;
			 }
		}

//		char * pNum = new char [20];
		char * pNum = new char [_MAX_PATH];
		if ( pNum == NULL ) {
			DELETE_OBJ ( pNum );
			return iIndex;
		}

		_ElementeZahl.SetText( ltoa ((long)Count,pNum,10) );
		DELETE_OBJ ( pNum );
		if ( isFlaeche() )
			_ElementeTyp.SetText ( ResString (ResID (IDS_FLAECHEN, &_RF), 35));
		else
			_ElementeTyp.SetText ( ResString (ResID (IDS_LINIEN, &_RF), 35) );

		SetObjClass ( &Min, &Max );	// Zeile ausfüllen
		_MassEinhList.ChangeCurrentIndex ( iIndex);
		SaveVergleichsWert();
		OKButton.Enable();
		

	}
	return iIndex;
}
//---------------------------------------------

long ObjectClassification :: GetObjClass ( void )
{
long Ident = 0L;

char *pBuffer = new char [_MAX_PATH];
	_iOklGiTyp = 0;			// Typ unbekannt
	if ( pBuffer == NULL )
		return Ident;
	int iIndex = _ObjClassList.GetCurrentIndex();
	if (iIndex != -1) {
		_ObjClassList.GetCurrentString (pBuffer);
		char *ptr = strchr (pBuffer, ':');
		if ( ptr == NULL ) {
			DELETE_OBJ ( pBuffer );
			return Ident;
		} else {
			if ( *(ptr+1) == 'L' )
				_iOklGiTyp = OTLinie;
			if ( *(ptr+1) == 'F' )
				_iOklGiTyp = OTFlaeche;
			*ptr = '\0';
		}

// Korr 22.1.97
/*--------
		if ( DEX_GetIdBase() == 16 )
			Ident = strtoul ( pBuffer, NULL, 16 );
		else
			Ident = atol(pBuffer);
----------*/
		ulong uIdent = (ulong)Ident;

#if _MSC_VER < 1200

		HRESULT hr = IdentFromClassX (pBuffer, &uIdent);
		if (FAILED(hr)) {
			DELETE_OBJ(pBuffer);
			return 0;
		}
#else
		uIdent = _ObjClassList.GetItemData (iIndex);		// Ident ist am Item gespeichert
		TX_ASSERT(0 != uIdent);
#endif // _MSC_VER < 1200

		Ident = (long)uIdent;

	}

	DELETE_OBJ ( pBuffer );
	return Ident;
}
//---------------------------------------------
long ObjectClassification :: GetMassEinheit ( void )
{
long Einheit = -1L;
	int iIndex = _MassEinhList.GetCurrentIndex();
	if (iIndex != -1) {
		if ( _iMETyp == OTFlaeche ) {
			if ( iIndex == 0 ) Einheit = (long) QuadratMeter;
			if ( iIndex == 1 ) Einheit = (long) Hektar;
			if ( iIndex == 2 ) Einheit = (long) QuadratKiloMeter;
		}
		if ( _iMETyp == OTLinie ) {
			if ( iIndex == 0 ) Einheit = (long) Meter;
			if ( iIndex == 1 ) Einheit = (long) KiloMeter;
		}
	}
	return Einheit;
}
//---------------------------------------------
long ObjectClassification :: GetMathOp ( void *pData )
{
long Operate = -1L;

	int iIndex = ((ListBox *)pData) -> GetCurrentIndex();
	Operate = (long) iIndex;

	return Operate;
}

//---------------------------------------------
void _XTENSN_EXPORT ObjectClassification :: ListBoxClk (ControlEvt e)
{
/*------------------------------------------------------------------
	switch ((unsigned int)e.GetControlID()) {

	case IDC_LISTOBJCLASS:
		{
		_ObjKlasse = GetObjClass();
		}
		break;

	case IDC_LISTMATHOP:
		{
		_Operat = GetMathOp();
		}
		break;

	case IDC_LISTMASSEINH:
		{
		_Einheit = GetMassEinheit();
		}
		break;
	}
------------------------------------------------------------------*/
}


void _XTENSN_EXPORT ObjectClassification :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDOK: 
		{

		_IntervallWert.GetText ( _WERT , sizeof ( _WERT ) );
		_Wert = atof ( _WERT );

		_VerglWertMin.GetText ( _WERT , sizeof ( _WERT ) );
		if ( !isWertDeleted( &_WERT[0] ))
			_MinVglWert = atof ( _WERT ) - 0.0005;
		else
			_MinVglWert = -1.0;

		_VerglWertMax.GetText ( _WERT , sizeof ( _WERT ) );
		if ( !isWertDeleted(&_WERT[0]) )
			_MaxVglWert = atof ( _WERT ) + 0.0005;
		else
			_MaxVglWert = -1.0;

		if ( BuildIntervall () ) {
			EndDlg (1);
		} else {
			if ( isObjectFound() == GKlKeineObjekte) {
				
				MessageBox ( (HWND ) this->Handle() , ResString ( ResID( IDS_GICLASSNOOBJECTS,&_RF),50) ,
					 ResString ( ResID( IDS_GICLASSIFICATION,&_RF),50),
					 MB_OK|MB_ICONEXCLAMATION);
			}
			if ( isObjectFound() == GKlKriteriumFalsch ) {
				MessageBox ( (HWND )this->Handle() , ResString ( ResID( IDS_GICLASSNORECH,&_RF),50) ,
					 ResString ( ResID( IDS_GICLASSIFICATION,&_RF),50),
					 MB_OK|MB_ICONEXCLAMATION);
			}

			if ( isObjectFound() == GKlAbgebrochen ) {
				MessageBox ( (HWND )this->Handle() , ResString ( ResID( IDS_GICLASSSTOPWORK,&_RF),50) ,
					 ResString ( ResID( IDS_GICLASSIFICATION,&_RF),50),
					 MB_OK|MB_ICONEXCLAMATION);
			}

			DELETE_OBJ ( _pClaObj );
			if ( _pGICLA != NULL ) {
				DeleteClassification();
			}
			_WERT[0] = '\0';
			_Wert = 0.0;
			_IntervallWert.SetText(NULL);
			DefineMinMaxZeile();
		}

		}
		break;

	case IDCANCEL:
		if ( _pClaObj != NULL )
			DELETE_OBJ ( _pClaObj);
		if ( _pGICLA != NULL ) {
			DeleteClassification();
		}
		EndDlg (0);
		break;

	case IDC_BUTTONEINZEL :
		_EinzelButton.SetState(TRUE);
		_IntervallButton.SetState ( FALSE );
		_IntervallWert.Disable();
		_IntervallText.Disable();  
		_VerglWertMin.SetFocus();
		DefineMinMaxZeile();
		TestVergleichsWert();
		SetStandardMathOp ( TRUE );

		_WERT[0] = '\0';
		_Wert = 0.0;
		_IntervallWert.SetText(NULL);
		PruefeEinzelAbfrage();

		break;

	case IDC_BUTTONINTERVALL :
		_EinzelButton.SetState(FALSE);
		_IntervallButton.SetState ( TRUE );
		_IntervallWert.Enable();
		_IntervallWert.SetFocus();
		_IntervallText.Enable();   
		DefineMinMaxZeile();
		TestVergleichsWert();
		SetStandardMathOp ( FALSE );
		_pHelpText -> SetHelpText (ResID(IDH_HELPINTERVALLANGABE,&_RF));
		break;

	}

}


Bool ObjectClassification :: BuildIntervall ( void)
{
CEierUhr Wait ( _pW );
double FirstWert = 0.0, SecondWert = 0.0,Wert;
	_isObjectFound = GKlIgnore;		// IGNORE
	if ( _pGICLA == NULL )
		return FALSE;


	CTable t(*_pGICLA);

GICLASS GI;
long Group = 0L;
long Count = 0L;
double SWert = 0.0;

	if ( _EinzelButton.GetState() ) {
		if ( _ObjKlasse != 0L && _Einheit > 0L ) {

			SetGIKlassZero (&GI);
			GI.lGroupNr = -1;
			GI.IDNr = _ObjKlasse;
			GI.MCode = 0L;
			GI.iGiTyp = _iOklGiTyp;
			GI.lEinheit = _Einheit;
			if ( _MinVglWert == _MaxVglWert ) {
				if ( _MinVglWert == 0.0 || _MinVglWert == -1.0 )
					return FALSE;
			}
		double W1 = _MinVglWert;
		double W2 = _MaxVglWert;
			if ( W1 != -1.0 )
				W1 = W1 / (double)_Einheit;
			if ( W2 != -1.0 )
				W2 = W2 / (double)_Einheit;
			char *pBuf = ShowSearchScript ( W1,_Operat1,_Operat2,W2);
			if ( pBuf == NULL ) {
				_pHelpText -> SetHelpText (ResID(IDH_HELPWIDERSPRUCH,&_RF));
				return FALSE;
			}
			DELETE_OBJ ( pBuf );
			GI.lOperate1 = _Operat1;
			GI.lOperate2 = _Operat2;
			GI.rVglWert1 = _MinVglWert;
			GI.rVglWert2 = _MaxVglWert;
			GI.rKumul = 0.0;
			GI.rKumulMin = MaxDouble;
			GI.rKumulMax = 0.0;
			GI.lCount = 0;

//		ObjektVektor zusammenstellen
			OBJTree *pIdOBJ;
			CTable t(*_pIDM);
			if ( t.Find ( &_ObjKlasse ) ) {
				IDMLock l(t); 
				pIdOBJ = l->pObjects();

				if ( isLinie() )
					Count = (long)l->Linie();
				else
					Count = (long) l->Flaeche(); 
			} else
				return FALSE;

			_pClaObj = new long [ Count + 1];
			if (_pClaObj == NULL )
				return FALSE;

			CTable d( *pIdOBJ );
			Count = 0L;			
			OBJTree *pObj = new OBJTree;
			if ( pObj == NULL ) 
				return FALSE;

			for (d.First(); d.Valid() ; d.Next()  ) {
	
				OBJLock m(d);
				if ( !m) continue;
				if ( m->Ident() == _ObjKlasse ) {
					if ( isLinie() )
						Wert = m->LinLaenge();
					else
						Wert = m->FlInhalt();
					Wert = Wert / ( double) _Einheit;

					if ( Operate ( _MinVglWert,_Operat1, Wert )) {
					   if ( Operate (_MaxVglWert,_Operat2,Wert)) {
						Count++;
						SWert = SWert + Wert;
						if ( GI.rKumulMin == MaxDouble )
							GI.rKumulMin = Wert;
						else {
							if ( GI.rKumulMin > Wert )
								GI.rKumulMin = Wert;
						}
						if ( GI.rKumulMax == 0.0 )
							GI.rKumulMax = Wert;
						else {
							if ( GI.rKumulMax < Wert )
								GI.rKumulMax = Wert;
						}

						DuplicateObject( m->Object(),pIdOBJ, pObj);
						m->Intervall() = GI.lGroupNr;
						*(_pClaObj+Count) = m->Object();

	//----------------------------------------CONTAINER----------------------------
						if ( GI.lYmin > m->RuHoch() ) 
							GI.lYmin = m->RuHoch();
						if ( GI.lXmin > m->LoRechts() ) 
							GI.lXmin = m->LoRechts();
						if ( GI.lYmax < m->LoHoch() )
							 GI.lYmax = m->LoHoch();
						if ( GI.lXmax < m->RuRechts() )
							 GI.lXmax = m->RuRechts();

	//-----------------------------------------------------------------------------
					   }
					}
				}
			}

			GI.rKumul = SWert;
			GI.lCount = Count;
			if ( Count > 0L )
				GI.pObj = pObj;
			GICLACreator GICLACr ( *_pGICLA );
		  	ContCreate ( GICLACr, GICLA ) ( Group, &GI );

			*_pClaObj = Count;
			if ( Count > 0L ) {
				return TRUE;
			} else {
				_isObjectFound = GKlKeineObjekte;
				DELETE_OBJ ( pObj);			
				return FALSE;
			}
		}	// falls nicht Objklasse ...
		return FALSE;
	} else {
//-------------------Intervall------------------------------

		if ( _ObjKlasse != 0L && _Operat1 >= 0L && _Operat2 >= 0L && _Einheit > 0L ) {
			if ( _Wert <= 0.0 ) {
				_isObjectFound = GKlKriteriumFalsch;
				_pHelpText -> SetHelpText (ResID(IDT_KEININTERVALLWERT,&_RF));
				return FALSE;
			}
//	Objektanzahl bestimmen
			OBJTree * pIdOBJ;
			CTable t(*_pIDM);
			if ( t.Find ( &_ObjKlasse ) ) {
				IDMLock l(t);
 			    	pIdOBJ = l->pObjects();
				if ( isLinie() )
					Count = (long) l->Linie();
				else
					Count = (long) l->Flaeche(); 
			} else
				return FALSE;
	
			long lRange = Count;

//		ObjektVektor zusammenstellen
			long ICount = (long) ((_MaxWert/(double) _Einheit)/_Wert );
			if ( ICount > (long) MaxIntervall + 1 ) {
				char *pBuf = new char [_MAX_PATH];
				if ( pBuf == NULL )
					return FALSE;
				*pBuf = '\0';
				wsprintf ( pBuf , ResString ( ResID( IDS_GICLASSCOUNTINTERVALL,&_RF),90),ICount );
				HWND hwnd = this->Handle();

				int flag = MessageBox ( hwnd , pBuf ,
					 ResString ( ResID( IDS_GICLASSIFICATION,&_RF),50),
					 MB_YESNO|MB_ICONEXCLAMATION);
				DELETE_OBJ ( pBuf );
				if ( flag == IDNO )
					return FALSE;
			
			}
			char * pBuf = new char [ _MAX_PATH];
			if ( pBuf == NULL ) 
				return FALSE;
			*pBuf = '\0';
			strcat ( pBuf , ResString (ResID(IDS_GICLASSCREATEINTERVALL,&_RF),50));

			IdentInformation GCI ( this, SHOWIDENTIFIKATOR, _RF, _pIDM, pBuf ,lRange);
			GCI.Show();
			DELETE_OBJ ( pBuf);

			_pClaObj = new long [ Count + 1];
			if (_pClaObj == NULL )
				return FALSE;

			Count = 0L;

			while ( SecondWert < _MaxWert / (double) _Einheit) {
				OBJTree * pObj = new OBJTree;
				if ( pObj == NULL )
					return FALSE;
				SetGIKlassZero (&GI);
				FirstWert = SecondWert;
				SecondWert = SecondWert + _Wert;
				Group++;
				GI.lGroupNr = Group;
				GI.IDNr = _ObjKlasse;
				GI.MCode = 0L;
				GI.iGiTyp = _iOklGiTyp;
				GI.lEinheit = _Einheit;
				GI.lOperate1 = _Operat1;
				GI.lOperate2 = _Operat2;
				GI.rVglWert1 = FirstWert;
				GI.rVglWert2 = SecondWert;
				GI.rKumul = 0.0;
				GI.rKumulMin = MaxDouble;
				GI.rKumulMax = 0.0;
				GI.lCount = 0;

				long LCount = 0;

				short GITyp = 0;
				if ( isLinie() )
					GITyp = OTLinie;
				else
					GITyp = OTFlaeche;

				CTable d( *pIdOBJ );
				
				for (d.First(); d.Valid() ; d.Next()  ) {
	
					OBJLock m(d);
					if ( !m) continue;
					if ( m->Ident() == _ObjKlasse && GITyp == m->ObjectTyp()) {

						if ( isLinie() )
							Wert = m->LinLaenge();
						else
							Wert = m->FlInhalt();
						Wert = Wert / ( double) _Einheit;

						if ( Operate ( FirstWert,_Operat1, Wert )) {
						   if ( Operate (SecondWert,_Operat2,Wert)) {
							Count++;
							LCount++;
							SWert = SWert + Wert;
							if ( GI.rKumulMin == MaxDouble )
								GI.rKumulMin = Wert;
							else {
								if ( GI.rKumulMin > Wert )
									GI.rKumulMin = Wert;
							}
							if ( GI.rKumulMax == 0.0 )
								GI.rKumulMax = Wert;
							else {
								if ( GI.rKumulMax < Wert )
									GI.rKumulMax = Wert;
							}

							DuplicateObject( m->Object(),pIdOBJ,pObj);
							m->Intervall() = Group;
							*(_pClaObj+Count) = m->Object();

	//----------------------------------------CONTAINER----------------------------
							if ( GI.lYmin > m->RuHoch() ) 
								GI.lYmin = m->RuHoch();
							if ( GI.lXmin > m->LoRechts() ) 
								GI.lXmin = m->LoRechts();
							if ( GI.lYmax < m->LoHoch() )
								 GI.lYmax = m->LoHoch();
							if ( GI.lXmax < m->RuRechts() )
								 GI.lXmax = m->RuRechts();

	//-----------------------------------------------------------------------------
						   }
						}
					}
				}

				GI.rKumul = SWert;
				GI.lCount = LCount;
				if ( LCount > 0 )
					GI.pObj = pObj;
				else
					DELETE_OBJ ( pObj);

				GICLACreator GICLACr ( *_pGICLA );
			  	ContCreate ( GICLACr, GICLA ) ( Group, &GI );

				GCI.ModifyGIWindow( Group, FirstWert, SecondWert);

				long lCount = Count;
				GCI.SetPosition( (short)lCount);
				SWert = 0.0;
				LCount = 0;
				if ( GCI.Break() ) {
				    _isObjectFound = GKlAbgebrochen;		// IGNORE
				    DELETE_OBJ ( pObj );
				    DELETE_OBJ ( _pClaObj);
				    return FALSE;
				}
			}	//WHILE

			*_pClaObj = Count;

			if ( Count > 0 ) {
				return TRUE;
			} else {
				_isObjectFound = GKlKeineObjekte;
				return FALSE;
			}

		} else
			return FALSE;

	}
	return FALSE;
}
//-----------------------------------------------------------
void ObjectClassification :: DuplicateObject ( long ON,OBJTree *pIdOBJ, OBJTree * pObj)
{
	if ( pObj == NULL || pIdOBJ == NULL)
		return;

	CTable t(*pIdOBJ); 
	if ( !t.Find( &ON) )
		return;
	OBJLock l(t);
	CTable d(*pObj); 
	OBJECTTYP ObjStr;
	SetObjZero ( &ObjStr );
	long ONr = l->Object();
	ObjStr.lIdent = l->Ident();
	ObjStr.iGITyp = l->ObjectTyp();
	ObjStr.lXmin = l->LoRechts();
	ObjStr.lXmax = l->RuRechts();
	ObjStr.lYmin = l->RuHoch();
	ObjStr.lYmax = l->LoHoch();
	ObjStr.rPolyLen = l->LinLaenge();
	ObjStr.rArea = l->FlInhalt();
	
	OBJCreator OBJCr ( *pObj );
	ContCreate ( OBJCr, OBJ ) ( ONr, &ObjStr );
	return;	
}
//------------------------------------------------------------
void ObjectClassification :: SaveIntervallWert ( void)
{
	_IntervallWert.GetText ( _WERT , sizeof ( _WERT ) );
	_Wert = atof ( _WERT );
	_Wert = _Wert * (double)_Einheit;
	return;
}

//------------------------------------------------------------
void ObjectClassification :: TestVergleichsWert ( void)
{
//	nichts passiert
	if ( !_VerglWertMin.GetEditControl()->isModified() &&
		!_VerglWertMax.GetEditControl()->isModified() )
		return;
//	Erster Wert gel”scht
	if ( _VerglWertMin.GetEditControl()->isModified() ) {

		_VerglWertMin.GetText ( _WERT , sizeof ( _WERT ) );
		if ( isWertDeleted(&_WERT[0]) ) {
			_MinVglWert = -1.0;
			_MathOpListOne.Clear();
			_MathOpListOne.Disable();
		} else {
			_MinVglWert = atof ( _WERT );
			if ( _MinVglWert >= 0.0 ) {
				if ( (long)_MinVglWert == (long)(_MinWert / (double) _Einheit) )
					_MinVglWert = _MinWert;
				else
					_MinVglWert = _MinVglWert * (double)_Einheit;
			}
		}
	}
//	Zweiter Wert gel”scht
	if ( _VerglWertMax.GetEditControl()->isModified() ) {

		_VerglWertMax.GetText ( _WERT , sizeof ( _WERT ) );
		if ( isWertDeleted(&_WERT[0]) ) {
			_MaxVglWert = -1.0;
			_MathOpListTwo.Clear();
			_MathOpListTwo.Disable();
		} else {
			_MaxVglWert = atof ( _WERT );
			if ( _MaxVglWert >= 0.0 ) {
				if ( (long)_MaxVglWert == (long)(_MaxWert / (double) _Einheit) )
					_MaxVglWert = _MaxWert;
				else
					_MaxVglWert = _MaxVglWert * (double)_Einheit;
			}

		}
	}
}

//------------------------------------------------------------
void ObjectClassification :: SaveVergleichsWert ( void)
{
	_VerglWertMin.GetText ( _WERT , sizeof ( _WERT ) );
	if ( isWertDeleted(&_WERT[0]) )
		_MinVglWert = -1.0;
	else
		_MinVglWert = atof ( _WERT );
	if ( _MinVglWert >= 0.0 ) {
		if ( (long)_MinVglWert == (long)(_MinWert / (double) _Einheit) )
			_MinVglWert = _MinWert;
		else
			_MinVglWert = _MinVglWert * (double)_Einheit;
	}

	_VerglWertMax.GetText ( _WERT , sizeof ( _WERT ) );
	if ( isWertDeleted(&_WERT[0]) )
		_MaxVglWert = -1.0;
	else
		_MaxVglWert = atof ( _WERT );
	if ( _MaxVglWert >= 0.0 ) {
		if ( (long) _MaxVglWert == (long) (_MaxWert / (double) _Einheit ))
			_MaxVglWert = _MaxWert;
		else
			_MaxVglWert = _MaxVglWert * (double)_Einheit;
	}
	return;
}
//------------------------------------------------------------
void ObjectClassification :: DeleteClassification ( void )
{
	if ( _pGICLA == NULL )
		return;

	CTable t(*_pGICLA );

	for (t.First(); t.Valid() ; t.Next()  ) {
		t.Delete();
	}
	return;
}
//------------------------------------------------------------
Bool ObjectClassification :: isWertDeleted ( char *pWert )
{
	if ( *pWert == '\0' )
		return TRUE;
char *eptr;
	eptr = strchr ( pWert, '\0');
	long i = eptr - pWert;

	for ( long j = 0; j < i ;j++)
		if ( *(pWert+j)  != ' ' ) return FALSE;
	return TRUE;
}
//------------------------------------------------------------
Bool ObjectClassification :: isClassification ( void )
{
	if ( _EinzelButton.GetState() )
		return FALSE;
	else
		return TRUE;
	
}


//---------------------------------------------------------------------
void ObjectClassification :: ShowPBDText ( long Key, short TCode )
{
PBDDATA pbdData;
char *pLText = new char [1000];
	if ( pLText == NULL ) return;
	*pLText = NULL;
	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = TCode;
	pbdData.pbdCode = Key;
	pbdData.pbdLText = pLText;
	pbdData.pbdKTextLen = 0;
	pbdData.pbdLTextLen = 999;
	DEX_GetPBDData (pbdData);

	if ( SucheLeerZeichen ( pLText ))
			*pLText = NULL;

	if (pLText != NULL && *pLText != NULL ) {
		if ( pbdData.pbdTemp )
			_pHelpText -> SetHelpText (ResID(IDH_HELPTEMPOKL,&_RF));
		else 
			_pHelpText -> SetHelpTextV ( ResID(IDH_HELPOKLBESCHREIBUNG,&_RF),pLText);

	} else  {
		_pHelpText -> SetHelpText (ResID(IDT_KEINIDLANGTEXT,&_RF));
	}

	DELETE_OBJ (pLText);

}
//----------------------------------------------------------------
void ObjectClassification :: PruefeEinzelAbfrage ( void )
{
	double W1 = _MinVglWert;
	double W2 = _MaxVglWert;
	if ( W1 != -1.0 )
		W1 = W1 / (double)_Einheit;
	if ( W2 != -1.0 )
		W2 = W2 / (double)_Einheit;
	char *pBuf = ShowSearchScript ( W1,_Operat1,_Operat2,W2);
	if ( pBuf != NULL ) {
		OKButton.Enable();
		_pHelpText -> SetHelpTextV ( ResID(IDH_HELPEINZELKRITERIUM,&_RF),pBuf);
	} else {
		OKButton.Disable();
		_pHelpText -> SetHelpText (ResID(IDH_HELPWIDERSPRUCH,&_RF));
	}
	DELETE_OBJ ( pBuf );
	return;
}
//--------------------- keine Member -----------------------------
//
//------------------------------------------------------------
Bool Operate ( double Min, long Operation, double Wert)
{
	if ( Min == -1.0 )
		return TRUE;
	if ( Operation == (long) GOKleiner ) {
		if ( ( Min - Wert ) * Genauigkeit > 1.0 ) 
			return TRUE;
		else
			return FALSE;
	}
	if ( Operation == (long) GOKleinerGleich ) {
		if ( ( Min - Wert ) * Genauigkeit >= -1.0 )
			return TRUE;
		else
			return FALSE;
	}
	if ( Operation == (long) GOUnGleich ) {
		if ( fabs ( Wert - Min ) < 1.0 )
			return FALSE;
		else
			return TRUE;
	}
	if ( Operation == (long) GOGleich ) {
		if (  fabs ( Wert - Min ) < 1.0 )
			return TRUE;
		else
			return FALSE;
	}
	if ( Operation == (long) GOGroesser ) {
		if ( ( Wert - Min ) * Genauigkeit > 1.0 ) 
			return TRUE;
		else
			return FALSE;
	}
	if ( Operation == (long) GOGroesserGleich ) {
		if ( ( Wert - Min ) * Genauigkeit >= -1.0 )
			return TRUE;
		else
			return FALSE;
	}

	return TRUE;
}
//------------------------------------------------------------
char *ShowSearchScript ( double Min, long Op1, long Op2, double Max)
{
	//	Sondierungen
	if ( Min == Max ) {
		if ( Min == -1.0 )
			return NULL;
		if ( TestW1GleichW2 ( Op1, Op2 ) )
			return NULL;
	}

	if ( Min < Max && Min >= 0.0 ) {
		if ( TestW1KleinerW2 ( Op1,Op2) )
			return NULL;
	}

	if ( Min > Max && Max >= 0.0 ) {
		if ( TestW1GroesserW2 ( Op1, Op2 ))
			return NULL; 
	}

char *pBuffer1 = new char [ _MAX_PATH];
char *pBuffer2 = new char [ _MAX_PATH];

	if ( pBuffer1 == NULL || pBuffer2 == NULL )
		return NULL;

	*pBuffer1 = '\0';
	*pBuffer2 = '\0';

	if ( Min != -1.0 ) {
		ST_DtoA ( pBuffer1, "%8.3f", Min);

		if ( Op1 == (long) GOKleiner ) 
			strcat ( pBuffer1, " > ");

		if ( Op1 == (long) GOKleinerGleich ) 
			strcat ( pBuffer1, " >= ");

		if ( Op1 == (long) GOUnGleich ) 
			strcat ( pBuffer1, " != ");

		if ( Op1 == (long) GOGleich ) 
			strcat ( pBuffer1, " = ");

		if ( Op1 == (long) GOGroesser ) 
			strcat ( pBuffer1, " < ");

		if ( Op1 == (long) GOGroesserGleich ) 
			strcat ( pBuffer1, " <= ");

//		strcat ( pBuffer1, ResString(ResID(IDS_GICLASSOBJEKT,&_RF),20));
		strcat ( pBuffer1, " Objekt ");
	}

	if ( Max != -1.0 ) {
		if ( *pBuffer1 == '\0')
//			strcat ( pBuffer1, ResString(ResID(IDS_GICLASSOBJEKT,&_RF),20));
			strcat ( pBuffer1, " Objekt ");
		if ( Op2 == (long) GOKleiner ) 
			strcat ( pBuffer1, " < ");

		if ( Op2 == (long) GOKleinerGleich ) 
			strcat ( pBuffer1, " <= ");

		if ( Op2 == (long) GOUnGleich ) 
			strcat ( pBuffer1, " != ");

		if ( Op2 == (long) GOGleich ) 
			strcat ( pBuffer1, " = ");

		if ( Op2 == (long) GOGroesser ) 
			strcat ( pBuffer1, " > ");

		if ( Op2 == (long) GOGroesserGleich ) 
			strcat ( pBuffer1, " >= ");

		ST_DtoA ( pBuffer2, "%8.3f", Max);
	}

	strcat ( pBuffer1,pBuffer2);

	DELETE_OBJ ( pBuffer2);
	if ( *pBuffer1 != '\0' )
		return pBuffer1;
	DELETE_OBJ ( pBuffer1 );
	return NULL;
	
}
//------------------------------------------------------------
BOOL TestW1GleichW2 ( long Op1, long Op2)
{
//
	if ( Op1 == (long)GOUnGleich && Op2 == (long) GOGleich )
		return TRUE; 

//	OP1 = Gleich
	if ( Op1 == (long) GOGleich ) {
		if( Op2 == (long) GOKleiner )
			return TRUE; 
		if( Op2 == (long) GOGroesser )
			return TRUE; 
		if ( Op2 == (long)GOUnGleich )
			return TRUE; 
		return FALSE;	
	}
//	OP2 = Gleich
	if ( Op2 == (long) GOGleich ) {
		if( Op1 == (long) GOKleiner )
			return TRUE; 
		if( Op1 == (long) GOGroesser )
			return TRUE; 
		if ( Op1 == (long)GOUnGleich )
			return TRUE; 
		return FALSE;	
	}
//	OP1 = kleiner
	if ( Op1 == (long)GOKleiner ) {
		if( Op2 == (long) GOGroesser )
			return TRUE; 
		if ( Op2 == (long) GOGroesserGleich )
			return TRUE; 
		if ( Op2 == (long) GOGleich )
			return TRUE; 
		return FALSE;
	}
//
//	OP1 = kleinergleich
	if ( Op1 == (long)GOKleinerGleich ) {
		if( Op2 == (long) GOGroesser )
			return TRUE; 
		return FALSE;
	}
//
//	OP1 = Groesser
	if ( Op1 == (long)GOGroesser ) {
		if( Op2 == (long) GOKleiner )
			return TRUE; 
		if( Op2 == (long) GOKleinerGleich )
			return TRUE; 
		if ( Op2 == (long) GOGleich )
			return TRUE; 
		return FALSE;
	}
//	OP1 = GroesserGleich
	if ( Op1 == (long)GOGroesserGleich ) {
		if( Op2 == (long) GOKleiner )
			return TRUE; 
	}
	return FALSE;
}

//-----------------------------------------------------
BOOL TestW1KleinerW2 ( long Op1, long Op2 )
{

	if ( Op1 == (long)GOGleich ) {
		if ( Op2 == (long) GOGleich )
			return TRUE; 
		if ( Op2 == (long) GOGroesser )
			return TRUE; 
		if ( Op2 == (long) GOGroesserGleich )
			return TRUE; 
	}
	if ( Op1 == (long) GOKleiner ) {
		if( Op2 == (long) GOGleich )
			return TRUE;
		if ( Op2 == (long) GOGroesser )
			return TRUE;
		if( Op2 == (long) GOGroesserGleich )
			return TRUE;
	}

	if ( Op1 == (long) GOKleinerGleich ) {
		if( Op2 == (long) GOGleich )
			return TRUE;
		if ( Op2 == (long) GOGroesser )
			return TRUE;
		if( Op2 == (long) GOGroesserGleich )
			return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------
BOOL TestW1GroesserW2 ( long Op1, long Op2 )
{

	if ( Op1 == (long)GOGleich ) {
		if ( Op2 == (long) GOGleich )
			return TRUE; 
		if ( Op2 == (long) GOKleiner )
			return TRUE; 
		if ( Op2 == (long) GOKleinerGleich )
			return TRUE; 
	}
	if ( Op1 == (long) GOGroesser ) {
		if( Op2 == (long) GOGleich )
			return TRUE;
		if ( Op2 == (long) GOKleiner )
			return TRUE;
		if( Op2 == (long) GOKleinerGleich )
			return TRUE;
	}

	if ( Op1 == (long) GOGroesserGleich ) {
		if( Op2 == (long) GOGleich )
			return TRUE;
		if ( Op2 == (long) GOKleiner )
			return TRUE;
		if( Op2 == (long) GOKleinerGleich )
			return TRUE;
	}

	return FALSE;
}
