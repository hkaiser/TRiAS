
// File: DBCLASS.CXX

#include "statistp.hxx"
#include "geostat.h"
#include <igeometr.hxx>

#include "dirmath.h"

#include <clipbrd.hxx>
#include "idkey.hxx"
#include "objkey.hxx"
#include "classkey.hxx"
#include "dbinfo.hxx"
#include "trfkoord.hxx"
#include "sclipbrd.hxx"
#include "dbclass.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32


// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

DBClassification :: DBClassification (pWindow pW, uint res, ResourceFile &RF , CoordTransX *pCTF, char *pCaption, void *pData1 , short iOKlTyp, void * pData2) 
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _ObjektKlassen (this, IDT_OCLOBJEKTKLASSEN),
	       _ObjClassList (this,IDLB_OCLOBJCLASSLIST),
	       _MerkmalList (this,IDCB_OCLMERKMALLIST),
	       _ObjektEigenschaften ( this,IDC_OCLOBJEKTEIGENSCH),
	       _MerkmalAnzeige ( this,IDC_OCLMERKMALANZEIGE),
	       _EinschlMerkmal ( this,IDC_OCLONLYMERKMAL),
	       _AusschlMerkmal ( this,IDC_OCLINVERSMERKMAL),
	       _PutClipBoard ( this,IDB_OCLPUTCLIPBOARD),
	       _LoHochWert ( this,IDK_OCLLOHOCH),
	       _LoRechtsWert( this,IDK_OCLLORECHTS),
	       _RuHochWert ( this,IDK_OCLRUHOCH),
	       _RuRechtsWert( this,IDK_OCLRURECHTS),

	       _FlaechenInhalt ( this,IDT_OCLFLINHALT),
	       _FlaechenMass ( this,IDT_OCLFLMASS),
	       _LinienLaenge ( this,IDT_OCLLINLAENGE),
	       _LinienMass ( this,IDT_OCLLINMASS),

	       _Objekte ( this,IDT_OCLOBJEKTE),
	       _Punkte ( this,IDC_OCLPUNKTE),
	       _Linien ( this,IDC_OCLLINIEN),
	       _Flaechen ( this,IDC_OCLFLAECHEN),
	       _Texte ( this,IDC_OCLTEXTE),
	       _Sonstige ( this,IDC_OCLSONSTIGE),
	       _RF (RF),

	       _Schliessen (this, IDOK),
	       _Details (this, IDB_OCLDETAILS),
	       _AlleKlassen (this, IDB_OCLALLEKLASSEN),
	       _Anzeigen (this, IDB_OCLANZEIGEN)

{
//	StartWerte
	_pW = pW;
//	pW -> Disable();
	_pHelpText = NULL;
	_pOCL = NULL;
	_pInfoBox = NULL;
	_pCTF = NULL;
	if ( !pCTF )
		return;
	_pCTF = pCTF;
	_isShowInfoBox = FALSE;	//NOSHOW
	_isBreak = FALSE;	// Kein Abbruch

//	AusgabeVektor in ORWindow
	_pIDC = NULL;

#if !defined (WIN32)
	_pHUGE = NULL;
	_isHuge = false;
#endif
	_isDetails = TRUE;	// Details bearbeitbar
	_pHelpText = CHelpTextX :: CreateInstance (this, IDT_OCLBESCHREIBUNG);
	if (_pHelpText == NULL)
		return;
	_ObjRecherche = TRUE; 	// Alle Informationen des Objektes recherchieren 

//	ObjektKlassenArt erfragen
	_OKlTyp = iOKlTyp;	// ObjektKlassenArten
	_pIDM = ( IDMTree *) pData1;
	_pOBJ = ( OBJTree *) pData2;

//	Allgemein : ID/ON -Kombination
	TX_ASSERT(NULL != _pIDM);

	if ( _pIDM == NULL || _pOBJ == NULL )
		return;
	_pGICLA = NULL;

	TX_ASSERT(0L <= _pIDM->Count());

	if ( isGeometrieTyp(_OKlTyp) ) {	// GeometrieKlasse
		_pGICLA = ( GICLATree * ) pData1;	// GI-Baum(Intervalle)
		_pOBJ = ( OBJTree *) pData2;		// Obj-Baum
		
		if ( _pGICLA == NULL || _pOBJ == NULL )
			return;
		if ( _pGICLA->Count() == 0 || _pOBJ->Count() == 0 )
			return;
	} 

	_MKode = 0L;		// Start Objekteigenschaft

	_ShowObjTyp = 0;	// Anzuzeigende Objekttypen ( 0 = alle )

	short iAnsicht;
	char *pPText = new char [_MAX_PATH];
	if ( pPText == NULL)
		return;
	*pPText = '\0';
	iAnsicht = TRUE;		// Ansicht definiert


	if ( !DEX_GetActiveSight(pPText) || *pPText == '\0') 
		iAnsicht = FALSE;		// keine Ansicht bzw. temp.

	SetCaption ( pCaption);
	
// ------------MerkmalListBox füllen

	FillMerkmalList ();

//-------------ObjektklassenListe füllen------------
	FillObjKlassenList ( iAnsicht, pPText );
	SetStandardInformation ( );

//--------SightContainer sichern
	for ( int l = 0; l < 4 ; l++ )
		 _SightCont[l] = _KooCont[l];

	DELETE_OBJ ( pPText );

}

#pragma warning (default: 4355)


DBClassification :: ~DBClassification (void)
{
	DELETE_OBJ (_pHelpText);
	DELETE_OBJ (_pOCL);
	DELETE_OBJ ( _pInfoBox);
//	_pW -> Enable();
 }


//-----------------------------------------------------------------
void DBClassification :: SetStandardInformation ( void )
{
//char *pNum= new char [20];
char *pNum= new char [_MAX_PATH];

	if ( pNum == NULL ) {
		return;
	}
	_isIDLIST = FALSE;
	_LastIdent = 0L;
	_LastMkode = 0L;
	_IdentBase = DEX_GetIdBase();

//------	Objekteigenschaften
	_EinschlMerkmal.Disable();
	_AusschlMerkmal.Disable();
	_Details.Disable();
        _PutClipBoard.Disable();
	_ObjektEigenschaften.SetChecked(FALSE);
	_MerkmalAnzeige.SetChecked(FALSE);
	_MerkmalAnzeige.Disable();

	ClearObjectInformation();

//------	Objektübersicht
	_Punkte.Disable();
	_Linien.Disable();
	_Flaechen.Disable();
	_Texte.Disable();
	_Sonstige.Disable();

//------	Anzeigen
	_Anzeigen.Disable();

	if ( isAttribut(_OKlTyp)) {
	//------------Sichtcontainer
		DEX_GetActiveSightContainer(_KooCont);
	} else {
		if ( isDataBase ( _OKlTyp ))
			DEX_GetProjectCont ( _KooCont);
		else
			GetObjClassContainer();
	}

	if ( SetKoord ( )) {
		_LoRechtsWert.SetText(ltoa(_KooCont[0],pNum,10));
		_RuRechtsWert.SetText(ltoa(_KooCont[1],pNum,10));
		_LoHochWert.SetText(ltoa(_KooCont[3],pNum,10));
		_RuHochWert.SetText(ltoa(_KooCont[2],pNum,10));
	} else
		SetNoMetric();

	DELETE_OBJ ( pNum );
	return;
}
//-------------------ObjectContainerSumme--------------
void DBClassification :: GetObjClassContainer ( void )
{
	_KooCont[0] = MAXKOORD;
	_KooCont[1] = 0;
	_KooCont[2] = MAXKOORD;
	_KooCont[3] = 0;
	if ( !isGeometrieTyp(_OKlTyp) ) {
		CTable t(*_pIDM );

		for (t.First(); t.Valid() ; t.Next()  ) {
	
			IDMLock l(t);

			if ( _KooCont[2] > l->RuHoch() ) 
				_KooCont[2] = l->RuHoch();
			if ( _KooCont[0] > l->LoRechts() ) 
				_KooCont[0] = l->LoRechts();
//---------------------Maximum-------------------------------------
			if ( _KooCont[3] < l->LoHoch() )
				_KooCont[3] = l->LoHoch();
			if ( _KooCont[1] < l->RuRechts() )
				_KooCont[1] = l->RuRechts();
		}
	} else {
		CTable t(*_pGICLA );

		for (t.First(); t.Valid() ; t.Next()  ) {
	
			GICLALock l(t);

			if ( _KooCont[2] > l->Ymin() ) 
				_KooCont[2] = l->Ymin();
			if ( _KooCont[0] > l->Xmin() ) 
				_KooCont[0] = l->Xmin();
			if ( _KooCont[3] < l->Ymax() )
				_KooCont[3] = l->Ymax();
			if ( _KooCont[1] < l->Xmax() )
				_KooCont[1] = l->Xmax();
		}
	}
return;

}

//-----------------------------------------------------------------
void DBClassification :: FillMerkmalList ( void )
{
	

// ------------MerkmalListBox füllen

ENUMNOKEY ENK;

	ENK.eFcn = ( ENUMNOKEYPROC) FillMKListBox;
	ENK.ePtr = &_MerkmalList;
	
	DEX_EnumMCodes(ENK);

}
//
void DBClassification :: FillObjKlassenList ( short Flag, char *pSightName )
{

char *pPText = new char [_MAX_PATH];
char *pOut = new char [_MAX_PATH];
long Ident, lIDCount= 0L;

	if ( pPText == NULL || pOut == NULL ) {
		DELETE_OBJ ( pPText );
		DELETE_OBJ ( pOut );
		return;
	}

	if ( !isGeometrieTyp (_OKlTyp) ) {
		CTable t(*_pIDM );

		for (t.First(); t.Valid() ; t.Next()  ) {
	
			IDMLock l(t);

			Ident = ( l->Ident());
			short Typ = ( l->IdentGiTyp());
			StoreIDList ( &_RF, Ident ,&_ObjClassList , Typ);
			lIDCount++;
		} 
	}


	if (isGeometrieTyp(_OKlTyp) ) {
		if (_pGICLA == NULL )
			return;
		lIDCount = 0;
		CTable t(*_pGICLA );

		for (t.First(); t.Valid() ; t.Next()  ) {
	
			GICLALock l(t);
	unsigned short resID = 0;
			if ( l->GiTyp() == OTLinie ) {
				resID = IDT_UNITM;
				if ( l->Einheit() == KiloMeter )
					resID = IDT_UNITKM;
			}
			if ( l->GiTyp() == OTFlaeche ) {
				resID = IDT_UNITQM;
				if ( l->Einheit() == QuadratKiloMeter )
					resID = IDT_UNITQKM;
				if ( l->Einheit() == Hektar )
					resID = IDT_UNITHA;
			}
char Einheit[30];

			Einheit[0] = '\0';
			strcat (Einheit, ResString (ResID (resID, &_RF ), 10));

			StoreGIKlassList ( l->Group() ,&_ObjClassList , l->GiTyp(), l->VglWert1(), l->VglWert2(),&Einheit[0],l->Count());
			lIDCount++;
		}
	} 

	_ObjektKlassen.GetText ( pOut , _MAX_PATH - 1);
	wsprintf ( pPText, pOut, lIDCount);
	_ObjektKlassen.SetText( pPText);


	DELETE_OBJ ( pPText );
	DELETE_OBJ ( pOut );

	return;
}
//---------------------------------------------------------------
//----------- AusgabeLISTE ( Container ) ------------------------
//---------------------------------------------------------------
void DBClassification :: LoadObjectClassList ( void )
{

	if ( _pIDM == NULL )
		return;
	if ( _pOCL != NULL )
		DELETE_OBJ ( _pOCL );
	_pOCL = new OBJCLList;	//ListContainer
	if ( _pOCL == NULL )
		return;


char *pBuffer = new char [_MAX_PATH];
char *pBuf = new char [_MAX_PATH];
	if ( pBuffer == NULL || pBuf == NULL) {
		DELETE_OBJ ( pBuffer);
		DELETE_OBJ ( pBuf);
		return;
	}

long lIdent = 0L;

int iIndex = _ObjClassList.GetFirstSelected();
	CTable t( *_pIDM);
	CRing r( *_pOCL);
	if (iIndex != -1) {
		_ObjClassList.GetString (pBuffer,iIndex,_MAX_PATH);

// Identifikator besorgen !

	#if _MSC_VER < 1200

		HRESULT hr = IdentFromClassX (pBuffer, (ULONG *)&lIdent);
		if (FAILED(hr)) {
			lIdent = 0;
		}
	#else
		lIdent = _ObjClassList.GetItemData (iIndex);		// Ident ist am Item gespeichert
		TX_ASSERT(0 != lIdent);
	#endif // _MSC_VER < 1200


		OBJCLCreator OBJCLCr ( *_pOCL );
		char *ptr = strchr ( pBuffer, ':');
		if ( ptr == NULL ) {
			DELETE_OBJ ( pBuffer);
			DELETE_OBJ ( pBuf);
			return;
		}
		if ( *(ptr+2) == 'L' || *(ptr+3) == 'F' ) {
		   *(ptr+1) = '\0';	// Modi
		   *pBuf = '\0';
		   strcat ( pBuf, pBuffer);
		   *(ptr+1) = '_';	// Modi zurück
		   strcat (pBuf,"L");
		   char *qtr = strchr ( ptr+1, ':');
		   if ( qtr == NULL ) {
			DELETE_OBJ ( pBuffer);
			DELETE_OBJ ( pBuf);
			return;
		   }
		   strcat ( pBuf, qtr); 
		   if ( *(ptr+2) == 'L' ) {
			if( isDefinedMCLine( pBuffer)) 
				ContCreate ( OBJCLCr, OBJCL ) ( TRUE, lIdent,pBuf);
			else
				ContCreate ( OBJCLCr, OBJCL ) ( FALSE, lIdent,pBuf);
		   }
		   if ( *(ptr+3) == 'F' ) {
			char *qtr = strchr ( pBuf, ':');
			if ( qtr == NULL ) {
				DELETE_OBJ ( pBuffer);
				DELETE_OBJ ( pBuf);
				return;
			}
			*(qtr+1) = 'F'; 
			if( isDefinedMCArea( pBuffer)) 
				ContCreate ( OBJCLCr, OBJCL ) ( TRUE, lIdent,pBuf);
			else
				ContCreate ( OBJCLCr, OBJCL ) ( FALSE, lIdent, pBuf);
		   }
		}

		iIndex=_ObjClassList.GetNextSelected ();
		while ( iIndex != -1 ) {
			OBJCLCreator OBJCLCr ( *_pOCL );
			_ObjClassList.GetString (pBuffer,iIndex,_MAX_PATH);

		#if _MSC_VER < 1200

			HRESULT hr = IdentFromClassX (pBuffer, (ULONG *)&lIdent);
			if (FAILED(hr)) {
				lIdent = 0;
			}
		#else
			lIdent = _ObjClassList.GetItemData (iIndex);		// Ident ist am Item gespeichert
			TX_ASSERT(0 != lIdent);
		#endif // _MSC_VER < 1200

			char *ptr = strchr ( pBuffer, ':');
			if ( ptr == NULL ) {
				DELETE_OBJ ( pBuffer);
				DELETE_OBJ ( pBuf);
				return;
			}
			if ( *(ptr+2) == 'L' || *(ptr+3) == 'F' ) {
			   *(ptr+1) = '\0';	//Modi
			   *pBuf = '\0';
			   strcat ( pBuf, pBuffer);
			   *(ptr+1) = '_';	// Modi zurück
			   strcat (pBuf,"L");
			   char *qtr = strchr ( ptr+1, ':');
			   if ( qtr == NULL ) {
				DELETE_OBJ ( pBuffer);
				DELETE_OBJ ( pBuf);
				return;
			   }
			   strcat ( pBuf, qtr); 
			   if ( *(ptr+2) == 'L' ) {
				if( isDefinedMCLine( pBuffer)) 
					ContCreate ( OBJCLCr, OBJCL ) ( TRUE, lIdent,pBuf);
				else
					ContCreate ( OBJCLCr, OBJCL ) ( FALSE, lIdent,pBuf);
			   }
			   if ( *(ptr+3) == 'F' ) {
				char *qtr = strchr ( pBuf, ':');
			   	if ( qtr == NULL ) {
					DELETE_OBJ ( pBuffer);
					DELETE_OBJ ( pBuf);
					return;
			   	}
				*(qtr+1) = 'F'; 
				if( isDefinedMCArea( pBuffer)) 
					ContCreate ( OBJCLCr, OBJCL ) ( TRUE, lIdent,pBuf);
				else
					ContCreate ( OBJCLCr, OBJCL ) ( FALSE, lIdent, pBuf);
			   }
			}
			iIndex=_ObjClassList.GetNextSelected ();
		}
	}
	DELETE_OBJ ( pBuffer);
	DELETE_OBJ ( pBuf);
	return;
}
//-----------------------------------------------------------------
Bool DBClassification :: isDefinedMCLine ( char *pBuffer )
{
	short MFlag = TRUE;
	if ( _pIDM == NULL || pBuffer == NULL || *pBuffer == NULL )
		return FALSE;
	if ( _MKode == 0L )
		return TRUE;
	long Mkode = _MKode;
	if ( _AusschlMerkmal.GetState()) {
		Mkode = -_MKode;
		MFlag = FALSE;
	}

long Ident;
HRESULT hr = IdentFromClassX (pBuffer, (ULONG *)&Ident);

	if (FAILED(hr)) false;

	CTable t( *_pIDM);
	if ( t.Find ( &Ident )) {
		IDMLock l(t);
		OBJTree *pObj = l->pObjects();
		if ( pObj == NULL )
			return FALSE;
		CTable d( *pObj );
		for ( d.First(); d.Valid(); d.Next() ) {
			OBJLock m(d);
			long ONr = m->Object();
			if ( m->ObjectTyp() == OTLinie ) {
			   if ( ExistMCodeInObject ( MFlag, Mkode, ONr) )
				return TRUE;
			}
		}
	}
	return FALSE;
}
//-----------------------------------------------------------------
Bool DBClassification :: isDefinedMCArea ( char *pBuffer )
{
	short MFlag = TRUE;
	if ( _pIDM == NULL || pBuffer == NULL || *pBuffer == NULL )
		return FALSE;
	if ( _MKode == 0L )
		return TRUE;
	long Mkode = _MKode;
	if ( _AusschlMerkmal.GetState()) {
		Mkode = -_MKode;
		MFlag = FALSE;
	}

long Ident;
HRESULT hr = IdentFromClassX (pBuffer, (ULONG *)&Ident);

	if (FAILED(hr)) false;

	CTable t( *_pIDM);
	if ( t.Find ( &Ident )) {
		IDMLock l(t);
		OBJTree *pObj = l->pObjects();
		if ( pObj == NULL )
			return FALSE;
		CTable d( *pObj );
		for ( d.First(); d.Valid(); d.Next() ) {
			OBJLock m(d);
			long ONr = m->Object();
			if ( m->ObjectTyp() == OTFlaeche ) {
			   if ( ExistMCodeInObject ( MFlag, Mkode, ONr) )
				return TRUE;
			}
		}
	}
	return FALSE;
}

//-----------------------------------------------------------------
void DBClassification :: LoadObjectVector ( void )
{
	if ( _pIDM == NULL )
		return;

	if ( _pIDC != NULL )
		DELETE_OBJ ( _pIDC);

#if !defined (WIN32)
	_isHuge = false;

	if ( _NumObject > ObjectGrenze ) {
		if ( _pHUGE )
			delete (long __huge *) _pHUGE;
		_pHUGE = new __huge long [ _NumObject +1 ];
		if ( _pHUGE == NULL ) 
			return;
		_isHuge = true;
	} else {
		_pIDC = new long [ _NumObject +1 ];
		if ( _pIDC == NULL)
			return;
		_isHuge = false;
	}
#else
	_pIDC = new long [ _NumObject +1 ];
	if ( _pIDC == NULL)
		return;
#endif
	
long Number = 1L;
int iIndex = _ObjClassList.GetFirstSelected();

	CTable t( *_pIDM);
	short MFlag = TRUE;
	long MKode = _MKode;
	if ( _ObjektEigenschaften.isChecked() ) {	// OE angeklickt,_MKode gilt
		if ( _AusschlMerkmal.GetState()) {
			MKode = -_MKode;	
			MFlag = FALSE;
		}
	} else {
		MKode = 0L;
	}

	if (iIndex != -1) {
		long Key = SetIdent ( iIndex );
		if ( 0 == Key )
			return;
		if ( t.Find(&Key) ){
			IDMLock l(t);
			OBJTree *pObj = l->pObjects();
//------------------Objekte schon bearbeitet-----------------------
			if ( pObj != NULL ) {

				CTable s(*pObj);
				for ( s.First(); s.Valid(); s.Next() ) {
				   OBJLock k(s);
				   short OTyp = k->ObjectTyp();
				   if ( (_ShowObjTyp & OTyp) != 0 ) {
					if ( MKode == 0L ) {

#if !defined (WIN32)
						if ( _isHuge )
							*(_pHUGE + Number ) = k->Object();
						else
							*(_pIDC + Number ) = k->Object();
#else
						*(_pIDC + Number ) = k->Object();
#endif

						Number++;
					} else {
						if ( k->MCode() == MKode) {
#if !defined (WIN32)
							if ( _isHuge)
								*(_pHUGE + Number ) = k->Object();
							else
								*(_pIDC + Number ) = k->Object();
#else
							*(_pIDC + Number ) = k->Object();
#endif

							Number++;
						}
					}
				   } // ObjektTyp
				}
			} else {
//-------------------Informationen wie ON,Typ,MKode besorgen-------------
			long ObjCount = 
					+ l->Punkt() 
					+ l->Linie() 
					+ l->Flaeche() 
					+ l->Text() 
					+ l->Sonstige();
				long * pObjNr = new long [ ObjCount * 2 + 1];
				if ( pObjNr == NULL )
					return;
				*pObjNr = 0L;

				ENUMLONGKEY ELK;

				TYPVECTOR TV;
				TV.pOBJ = pObjNr;
				TV.GiTyp = l->IdentGiTyp();

				memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
				ELK.eFcn = ( ENUMLONGKEYPROC) SearchObjects;
				ELK.eKey = Key;
				ELK.ePtr = &TV;
				DEX_EnumIdentObjects(ELK);

				for ( long j = 0; j < ObjCount; j++ ) {
				   long ONr = *(pObjNr+j*2+1);
				   short OTyp = (short) *(pObjNr+j*2+2);
				   long MCode = MKode;
				   if ( MKode != 0L ) {
					if ( ExistMCodeInObject(MFlag,MCode,ONr) )
						MCode = MKode;
					else
						MCode = 0L;
				   }
				   if ( (_ShowObjTyp & OTyp) != 0 ) {
					if ( MKode == 0L ) {
#if !defined (WIN32)
						if ( _isHuge )
							*(_pHUGE + Number ) = ONr;
						else
							*(_pIDC + Number ) = ONr;
#else
						*(_pIDC + Number ) = ONr;
#endif
						Number++;
					} else {
						if ( MCode == MKode) {
#if !defined (WIN32)
							if ( _isHuge)
								*(_pHUGE + Number ) = ONr;
							else
								*(_pIDC + Number ) = ONr;
#else
							*(_pIDC + Number ) = ONr;
#endif
							Number++;
						}
					}
				   } // ObjektTyp
				}
				DELETE_OBJ ( pObjNr);
			}
		}
		iIndex=_ObjClassList.GetNextSelected ();

		while ( iIndex != -1 ) {
			Key = SetIdent ( iIndex );
			if ( 0 == Key )
				return;
			if ( t.Find(&Key) ){
				IDMLock l(t);
				OBJTree *pObj = l->pObjects();
				if ( pObj != NULL ) {

					CTable s(*pObj);
					for ( s.First(); s.Valid(); s.Next() ) {
					   OBJLock k(s);
					   short OTyp = k->ObjectTyp();
					   if ( (_ShowObjTyp & OTyp) != 0 ) {
						if ( MKode == 0L ) {
#if !defined (WIN32)
							if ( _isHuge)
								*(_pHUGE + Number ) = k->Object();
							else
								*(_pIDC + Number ) = k->Object();
#else
							*(_pIDC + Number ) = k->Object();
#endif
							Number++;
						} else {
							if ( k->MCode() == MKode) {
#if !defined (WIN32)
								if ( _isHuge)
									*(_pHUGE + Number ) = k->Object();
								else
									*(_pIDC + Number ) = k->Object();
#else
								*(_pIDC + Number ) = k->Object();
#endif
								Number++;
							}
						}
					   } // ObjektTyp
					}
				} else {
//-------------------Informationen wie ON,Typ,MKode besorgen-------------
					long ObjCount = 
						+ l->Punkt() 
						+ l->Linie() 
						+ l->Flaeche() 
						+ l->Text() 
						+ l->Sonstige();

					long * pObjNr = new long [ ObjCount * 2 + 1];
					if ( pObjNr == NULL )
						return;
					*pObjNr = 0L;
					ENUMLONGKEY ELK;

					TYPVECTOR TV;
					TV.pOBJ = pObjNr;
					TV.GiTyp = l->IdentGiTyp();

					memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
					ELK.eFcn = ( ENUMLONGKEYPROC) SearchObjects;
					ELK.eKey = Key;
					ELK.ePtr = &TV;
					DEX_EnumIdentObjects(ELK);

					for ( short j = 0; j < ObjCount; j++ ) {
					   long ONr = *(pObjNr+j*2+1);
					   short OTyp = (short) *(pObjNr+j*2+2);
					   long MCode = MKode;
					   if ( MKode != 0L ) {
						if ( ExistMCodeInObject(MFlag,MCode,ONr) )
							MCode = MKode;
						else
							MCode = 0L;
					   }
					   if ( (_ShowObjTyp & OTyp) != 0 ) {
						if ( MKode == 0L ) {
#if !defined(WIN32)
							if ( _isHuge )
								*(_pHUGE + Number ) = ONr;
							else
								*(_pIDC + Number ) = ONr;
#else
							*(_pIDC + Number ) = ONr;
#endif
							Number++;
						} else {
							if ( MCode == MKode) {
#if !defined (WIN32)
								if ( _isHuge)
									*(_pHUGE + Number ) = ONr;
								else
									*(_pIDC + Number ) = ONr;
#else
								*(_pIDC + Number ) = ONr;
#endif
								Number++;
							}
						}
					   } // ObjektTyp
					}
					DELETE_OBJ ( pObjNr);
				}

			}

			iIndex=_ObjClassList.GetNextSelected ();
		}
	}
#if !defined (WIN32)
	if ( Number > 1 ) {
		if ( _isHuge )
			*_pHUGE = Number-1;
		else
			*_pIDC = Number-1;
	} else {
		if ( _isHuge)
			delete (long __huge *)_pHUGE;
		else
			DELETE_OBJ (_pIDC);
	}
#else
	if ( Number > 1 ) {
		*_pIDC = Number-1;
	} else {
		DELETE_OBJ (_pIDC);
	}
#endif

	if ( Number <= _NumObject )
		_NumObject = Number;
		
	return;
}

//-----------------------------------------------------------------
void DBClassification :: LoadGIVector ( long NumGI )
{
	if ( _pGICLA == NULL )
		return;

	if ( _pIDC != NULL )
		DELETE_OBJ ( _pIDC);


#if !defined (WIN32)
	_isHuge = false;

	if ( NumGI > ObjectGrenze ) {
		if ( _pHUGE )
			delete (long __huge *) _pHUGE;
		_pHUGE = new __huge long [ NumGI +1 ];
		if ( _pHUGE == NULL ) 
			return;
		_isHuge = true;
	} else {
		_pIDC = new long [ NumGI +1 ];
		if ( _pIDC == NULL)
			return;
		_isHuge = false;
	}
#else
	_pIDC = new long [ NumGI +1 ];
	if ( _pIDC == NULL)
		return;
#endif
	
long Number = 1L;
int iIndex = _ObjClassList.GetFirstSelected();

	CTable t( *_pGICLA);
	long MKode = _MKode;

	if ( _ObjektEigenschaften.isChecked() ) {	// OE angeklickt,_MKode gilt
		if ( _AusschlMerkmal.GetState())
			MKode = -_MKode;	
	} else {
		MKode = 0L;
	}

	if (iIndex != -1) {
		long Key = SetGIIdent ( iIndex );
		if ( 0 == Key )
			return;

		if ( t.Find(&Key) ){
			GICLALock l(t);
			OBJTree *pObj = l->pObjects();
//------------------Objekte schon bearbeitet-----------------------
			if ( pObj != NULL ) {

				CTable s(*pObj);
				for ( s.First(); s.Valid(); s.Next() ) {
				   OBJLock k(s);
				   if ( MKode == 0L ) {

#if !defined (WIN32)
					if ( _isHuge )
						*(_pHUGE + Number ) = k->Object();
					else
						*(_pIDC + Number ) = k->Object();
#else
					*(_pIDC + Number ) = k->Object();
#endif
					Number++;
				   } else {
					if ( k->MCode() == MKode) {
#if !defined (WIN32)
						if ( _isHuge)
							*(_pHUGE + Number ) = k->Object();
						else
							*(_pIDC + Number ) = k->Object();
#else
						*(_pIDC + Number ) = k->Object();
#endif
						Number++;
				 	}
				   }
				}
			}
		}
		iIndex=_ObjClassList.GetNextSelected ();

		while ( iIndex != -1 ) {
			Key = SetGIIdent ( iIndex );
			if ( 0 == Key )
				return;
			if ( t.Find(&Key) ){
				GICLALock l(t);
				OBJTree *pObj = l->pObjects();
				if ( pObj != NULL ) {

					CTable s(*pObj);
					for ( s.First(); s.Valid(); s.Next() ) {
					   OBJLock k(s);
					   if ( MKode == 0L ) {

#if !defined (WIN32)
						if ( _isHuge )
							*(_pHUGE + Number ) = k->Object();
						else
							*(_pIDC + Number ) = k->Object();
#else
						*(_pIDC + Number ) = k->Object();
#endif
						Number++;
					   } else {
						if ( k->MCode() == MKode) {

#if !defined (WIN32)
							if ( _isHuge)
								*(_pHUGE + Number ) = k->Object();
							else
								*(_pIDC + Number ) = k->Object();
#else
							*(_pIDC + Number ) = k->Object();
#endif
							Number++;
						}
					   }
					}
				}
			}
			iIndex=_ObjClassList.GetNextSelected ();
		}
	}

#if !defined (WIN32)
	if ( Number > 1 ) {
		if ( _isHuge )
			*_pHUGE = Number-1;
		else
			*_pIDC = Number-1;
	} else {
		if ( _isHuge)
			delete (long __huge *)_pHUGE;
		else
			DELETE_OBJ (_pIDC);
	}
#else
	if ( Number > 1 ) {
		*_pIDC = Number-1;
	} else {
		DELETE_OBJ (_pIDC);
	}
#endif
	
	return;
}

//-----------------------------------------------------------------
void _XTENSN_EXPORT DBClassification :: ButtonClick (ControlEvt e)
{

	switch ((unsigned int)e.GetControlID()) {
	case IDOK:
		EndDlg (1);
		break;

	case IDCANCEL:
		EndDlg (0);
		break;

	case IDB_OCLDETAILS:
		{
		CEierUhr Wait(_pW);
		LoadObjectClassList();
		if ( _pOCL != NULL ) {
			Wait.Hide();
			// Start DataBaseObjClass
			{
			long Mkode = _MKode;
			short MFlag = TRUE;
			if ( _AusschlMerkmal.GetState() ) {
				Mkode = -_MKode;
				MFlag = FALSE;
			}
			DataBaseObjClass DBO ( this,SHOWOBJECTCLASS, _RF, MFlag, _pIDM, _pOCL, &Mkode);
			DBO.Show();
			}
			DELETE_OBJ ( _pOCL);
		}	// pOCL != NULL

		}
		break;

	case IDB_OCLALLEKLASSEN:
		{	
		CEierUhr Wait(_pW);
		SetHelpText(FALSE);
		_ObjRecherche = TRUE;
		_isDetails = TRUE;	// Details modifizierbar
		long MKode = SetAllObjClass ();
		AnalysIDListBox ( MKode);
		_ObjRecherche = TRUE;
		}
		break;


	case IDB_OCLANZEIGEN:
		{
		CEierUhr Wait(_pW);
		if ( isGeometrieTyp(_OKlTyp) ) {
			if ( ModifyGIKlassList() )
				EndDlg (-1);
			else
				EndDlg (0); 
		} else {
			LoadObjectVector();
		}
		EndDlg (-1);
		}
		break;

	case IDC_OCLMERKMALANZEIGE:
		{
		SetHelpText(FALSE);
		DefineMwertAnzeige ();	
		}
		break;


	case IDC_OCLOBJEKTEIGENSCH:
		{
		SetHelpText(FALSE);
		long Mkode = AnalysObjProp ( );
		if ( Mkode != 0L) {
			CEierUhr Wait ( _pW );
			if ( Mkode == -1L )
				Mkode = 0L;
			AnalysIDListBox ( Mkode );
		}
		}
		break;

	case IDC_OCLONLYMERKMAL:
		{
		CEierUhr Wait(_pW);
		SetHelpText(FALSE);
		long Mkode = DefineMwertButton ();
		AnalysIDListBox (Mkode);
		}
		break;

	case IDC_OCLINVERSMERKMAL:
		{
		CEierUhr Wait(_pW);
		SetHelpText(FALSE);
		long Mkode = DefineInvMwertButton ();
		AnalysIDListBox (Mkode);
		}
		break;

	case IDB_OCLPUTCLIPBOARD:
		{

		CEierUhr Wait(_pW);
		_pHelpText -> SetHelpText (ResID(IDH_HELPCLIPBOARD,&_RF));

		PutIdentToClipBoard ();

		}
		break;

	case IDC_OCLPUNKTE:
		if ( _Punkte.isChecked() ) {
			_pHelpText -> SetHelpText (ResID(IDH_HELPOBJTYP,&_RF));
			_Punkte.SetChecked ( TRUE );
			SetObjTyp ( OTPunkt);
		} else {
			_Punkte.SetChecked ( FALSE );
			_pHelpText -> SetHelpText (ResID(IDH_HELPNOOBJTYP,&_RF));
			DelObjTyp ( OTPunkt);
		}
		break;

	case IDC_OCLLINIEN:
		if ( _Linien.isChecked() ) {
			_Linien.SetChecked ( TRUE );
			_pHelpText -> SetHelpText (ResID(IDH_HELPOBJTYP,&_RF));
			SetObjTyp ( OTLinie);
		} else {
			DelObjTyp ( OTLinie);
			_Linien.SetChecked ( FALSE );
			_pHelpText -> SetHelpText (ResID(IDH_HELPNOOBJTYP,&_RF));
		}
		break;

	case IDC_OCLFLAECHEN:
		if ( _Flaechen.isChecked() ) {
			_pHelpText -> SetHelpText (ResID(IDH_HELPOBJTYP,&_RF));
			_Flaechen.SetChecked ( TRUE );
			SetObjTyp ( OTFlaeche);
		} else {
			_Flaechen.SetChecked ( FALSE );
			DelObjTyp ( OTFlaeche);
			_pHelpText -> SetHelpText (ResID(IDH_HELPNOOBJTYP,&_RF));
		}
		break;


	case IDC_OCLTEXTE:
		if ( _Texte.isChecked() ) {
			_pHelpText -> SetHelpText (ResID(IDH_HELPOBJTYP,&_RF));
			_Texte.SetChecked ( TRUE );
			SetObjTyp ( OTText);
		} else {
			_Texte.SetChecked ( FALSE );
			DelObjTyp ( OTText);
			_pHelpText -> SetHelpText (ResID(IDH_HELPNOOBJTYP,&_RF));
		}
		break;

	case IDC_OCLSONSTIGE:
		if ( _Sonstige.isChecked() ) {
			_pHelpText -> SetHelpText (ResID(IDH_HELPOBJTYP,&_RF));
			_Sonstige.SetChecked ( TRUE );
			SetObjTyp ( OTKO);
		} else {
			_Sonstige.SetChecked ( FALSE );
			DelObjTyp ( OTKO);
			_pHelpText -> SetHelpText (ResID(IDH_HELPNOOBJTYP,&_RF));
		}
		break;

	}
}
//-----------------------------------------------------------------
long DBClassification :: SetAllObjClass ( void )
{
//------------Help-Text----------------------
	if ( !isHelpText() ) {
		_pHelpText -> SetHelpText (ResID(IDH_HELPALLEKLASSEN,&_RF));
		SetHelpText(TRUE);
	}

//------------Objektklassen markieren-------------
	int iCount = _ObjClassList.GetCount();
	_ObjClassList.ChangeSelected( Range (0,iCount-1),TRUE);
	_isIDLIST = TRUE;
       _PutClipBoard.Enable();
	long Mkode = 0L;	// Keine Objekteigenschaften definiert

	if ( _ObjektEigenschaften.isChecked() ) {	// OE angeklickt,_MKode gilt
		Mkode = _MKode;
		if ( _AusschlMerkmal.GetState() ) {	// inverses Merkmal
			_MerkmalAnzeige.Disable();	// keine MW-Anzeige
			Mkode = -_MKode;
		}
		if ( Mkode == 0L )			// keine OE angeklickt->
			_MerkmalAnzeige.Disable();	// keine MW-Anzeige

	} else {	// keine OE -> damit keine MW-Anzeige
		_MerkmalAnzeige.Disable();
	}

	return Mkode;
}
//---------------------------------------------------------
long DBClassification :: CountObjects ( long *NumNo, long * pKey , short *fgenerate)
{
long Number = 0L;
long NumIdent = 0L;
	*NumNo = 0L;
	*fgenerate = false;	// keine Flaechen und Linien 
	if ( _pIDM == NULL )
		return Number;
	CTable t( *_pIDM);
	if ( pKey == NULL ) {		// Alle Klassen

	  for ( t.First(); t.Valid(); t.Next() ) {
		IDMLock l(t);
		NumIdent ++;
		Number = Number 
			+ l->Punkt() 
			+ l->Linie() 
			+ l->Flaeche() 
			+ l->Text() 
			+ l->Sonstige();
		if ( l->Count() == 0 ) {
			*NumNo = *NumNo 
			+ l->Punkt() 
			+ l->Linie() 
			+ l->Flaeche() 
			+ l->Text() 
			+ l->Sonstige();
			if ( *fgenerate == false ) {
				if ( l->Flaeche() > 0 || l->Linie() > 0 ) 
					*fgenerate = true;
			}
		}
			
	  }

	} else {
	
	   for ( long i = 0; i < *pKey ; i++) {

		long Key = *(pKey+i+1);

		if ( t.Find ( &Key)) {
			IDMLock l(t);

		NumIdent ++;
		Number = Number 
			+ l->Punkt() 
			+ l->Linie() 
			+ l->Flaeche() 
			+ l->Text() 
			+ l->Sonstige();
		if ( l->Count() == 0 )
			*NumNo = *NumNo 
			+ l->Punkt() 
			+ l->Linie() 
			+ l->Flaeche() 
			+ l->Text() 
			+ l->Sonstige();
			if ( *fgenerate == false ) {
				if ( l->Flaeche() > 0 || l->Linie() > 0 ) 
					*fgenerate = true;
			}
	   	}
	    }
	}
	if ( NumIdent > 0 )
		_NumIdent = NumIdent;
	return Number;	
}
//---------------------------------------------------------
void DBClassification :: SetObjTyp ( short Typ )
{
	_ShowObjTyp = _ShowObjTyp | Typ;
	if ( isDataBase(_OKlTyp))
		return;
	if ( _ShowObjTyp ) 
		_Anzeigen.Enable();
	else
		_Anzeigen.Disable();
	return;
}
//-----------------------------------------------------------
void DBClassification :: DelObjTyp ( short Typ )
{	
	_ShowObjTyp = _ShowObjTyp & ~Typ;
	if ( _ShowObjTyp ) 
		_Anzeigen.Enable();
	else
		_Anzeigen.Disable();
}
//---------------------------------------------------------
void DBClassification :: DefineMwertAnzeige ( void )
{
		if ( _MerkmalAnzeige.isChecked() ) {
			_MerkmalAnzeige.SetChecked ( TRUE );
			if (!isHelpText() ) {
				_pHelpText -> SetHelpText (ResID(IDH_HELPMKANZEIGE,&_RF));
				SetHelpText(TRUE);
			}
		} else {
			_MerkmalAnzeige.SetChecked ( FALSE );
			if (!isHelpText() ) {
				_pHelpText -> SetHelpText (ResID(IDH_HELPNOMKANZEIGE,&_RF));
				SetHelpText(TRUE);
			}
		}

}
//---------------------------------------------------------
long DBClassification :: AnalysObjProp ( void ) 
{
	long Mkode = _MKode;
	if ( _ObjektEigenschaften.isChecked() ) {
		_ObjektEigenschaften.SetChecked ( TRUE );
		_EinschlMerkmal.Enable();
		_EinschlMerkmal.SetState(TRUE);
		_AusschlMerkmal.Enable();
		if ( isDataBase(_OKlTyp) ) {
			_MerkmalAnzeige.SetChecked ( FALSE );
			_MerkmalAnzeige.Disable();
		} else 
			_MerkmalAnzeige.Enable();

		if (!isHelpText() ) {
			_pHelpText -> SetHelpText (ResID(IDH_HELPOBJEIGENSCH,&_RF));
			SetHelpText(TRUE);
		}
		if ( Mkode == 0L ) {		//Kein Mwert angegeben
			return Mkode;	
		} 
//--------------Keine O'Klassen angegeben	-----------------------------------
		if ( _isIDLIST  ) {
			return Mkode;
		} else {
			Mkode = SetAllObjClass ();
		}
	} else {
		if (!isHelpText() ) {
			_pHelpText -> SetHelpText (ResID(IDH_HELPNOOBJEIGENSCH,&_RF));
			SetHelpText(TRUE);
		}
		if ( _MKode != 0L )
			Mkode = -1L;
		else
			Mkode = 0L;
		_ObjektEigenschaften.SetChecked ( FALSE );	// OE aus
		_EinschlMerkmal.SetState ( FALSE );
		_AusschlMerkmal.SetState( FALSE );
		_EinschlMerkmal.Disable();
		_AusschlMerkmal.Disable();
		_MerkmalAnzeige.SetChecked ( FALSE );
		_MerkmalAnzeige.Disable();
	}
	return Mkode;
}
//---------------------------------------------------------
long DBClassification :: DefineMwertButton ( void )
{
long Mkode = _MKode;

	if ( !isHelpText() ) {
		_pHelpText -> SetHelpText (ResID(IDH_HELPMKEXISTIERT,&_RF));
		SetHelpText(TRUE);
	}
	_EinschlMerkmal.SetState ( TRUE );
	_AusschlMerkmal.SetState ( FALSE );
	if ( !isDataBase (_OKlTyp) ) {
		if ( Mkode == 0L )
			_MerkmalAnzeige.Disable();
		else
			_MerkmalAnzeige.Enable();
	} else
			_MerkmalAnzeige.Disable();

	return Mkode;
}
//---------------------------------------------------------
long DBClassification :: DefineInvMwertButton ( void )
{
long Mkode = -_MKode;
	if ( !isHelpText() ) {
		_pHelpText -> SetHelpText (ResID(IDH_HELPNOMKEXISTIERT,&_RF));
		SetHelpText(TRUE);
	}

	_AusschlMerkmal.SetState ( TRUE );
	_EinschlMerkmal.SetState ( FALSE );
	_MerkmalAnzeige.Disable();
	return Mkode;
}
//---------------------------------------------------------
void _XTENSN_EXPORT DBClassification :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_OCLOBJCLASSLIST:
		{
		CEierUhr Wait(_pW);
		SetHelpText(FALSE);
		_isDetails = TRUE;
		long Mkode = AnalysObjClass ();
		AnalysIDListBox ( Mkode );
		}
		break;

	case IDCB_OCLMERKMALLIST:
		{
		CEierUhr Wait(_pW);
		SetHelpText(FALSE);
		_isDetails = TRUE;
		long Mkode = AnalysObjEig ( );
		AnalysIDListBox ( Mkode);
		}
		break;
	}

}
//--------------------------------------------------------------
long DBClassification :: AnalysObjClass ( void )
{
long Mkode = _MKode;
	_isIDLIST = TRUE;
       _PutClipBoard.Enable();
	if ( _ObjektEigenschaften.isChecked() ) {	// OE angeklickt
		_ObjektEigenschaften.SetChecked ( TRUE );
		if ( _AusschlMerkmal.GetState() ) {
			_MerkmalAnzeige.Disable();
			Mkode = -_MKode;
		} else {
			if ( Mkode == 0L )
				_MerkmalAnzeige.Disable();
		}
	} else {		// OE ausgeschaltet
		_ObjektEigenschaften.SetChecked ( FALSE );
		_EinschlMerkmal.SetState ( FALSE );
		_AusschlMerkmal.SetState( FALSE );
		_EinschlMerkmal.Disable();
		_AusschlMerkmal.Disable();
		_MerkmalAnzeige.SetChecked ( FALSE );
		_MerkmalAnzeige.Disable();
		Mkode = 0L;		// Nur ID's analysieren
	}
	return Mkode;
}
//--------------------------------------------------------------
long DBClassification :: AnalysObjEig ( void )
{
char *pBuffer = new char [_MAX_PATH];
long Mkode = 0L;
	if ( pBuffer == NULL ) 
		return Mkode;
	int iIndex = _MerkmalList.GetCurrentIndex();
	if (iIndex != -1) {
		_MerkmalList.GetCurrentString (pBuffer);
		char *ptr = strchr (pBuffer, ':');
		if ( ptr == NULL ) {
			DELETE_OBJ ( pBuffer);
			return Mkode;
		} else
			*ptr = '\0';
		if ( DEX_GetMkBase() == 16 )
			_MKode = strtoul ( pBuffer, NULL, 16 );
		else
			_MKode = atol(pBuffer);

		*ptr = ':';
		ShowPBDText ( _MKode , 'm' );
	}
	Mkode = _MKode;
	DELETE_OBJ ( pBuffer );

	if ( _ObjektEigenschaften.isChecked() ) {	// OE angeklickt
		_ObjektEigenschaften.SetChecked ( TRUE );
		if ( _AusschlMerkmal.GetState() ) {
			_MerkmalAnzeige.Disable();
			Mkode = -_MKode;
		} else {
			if ( !isDataBase(_OKlTyp ) ) {
				if ( Mkode == 0L )
					_MerkmalAnzeige.Disable();
				else
					_MerkmalAnzeige.Enable();
			} else
					_MerkmalAnzeige.Disable();
		}
	} else {		// OE ausgeschaltet- alle ID's werden anal.!
		_ObjektEigenschaften.SetChecked ( TRUE );
		_EinschlMerkmal.SetState ( TRUE );
		_AusschlMerkmal.SetState( FALSE );
		_EinschlMerkmal.Enable();
		_AusschlMerkmal.Enable();
		_MerkmalAnzeige.SetChecked ( FALSE );
		_MerkmalAnzeige.Enable();
	}
	if ( _isIDLIST == FALSE )		// keine ID's sind angeklickt
		Mkode = SetAllObjClass ();

	return Mkode;
}	
//--------------------------------------------------------------
//---------------------------------------------------------

void DBClassification :: AnalysIDListBox ( long MKode )
{

int iIndex = _ObjClassList.GetFirstSelected();

	if ( iIndex == -1 ) {	// keine Selektion
		if ( MKode != 0L ) {
			MKode = SetAllObjClass();
			iIndex = _ObjClassList.GetFirstSelected();
		} else
			return;
	}

int Count = _ObjClassList.GetCount();
short Flag = TRUE;
short Number = 0;
	long * pKey = new long [ Count +1];
	if ( pKey == NULL )
		return;

//----------------------------Struktur GI-Typen-----------------------
	
IDGITYP IT;

	SetZero ( &IT );
	IT.lMCode = MKode;

//--------------------------------------------------------
	
	long Key = 0L;
	if ( isGeometrieTyp(_OKlTyp) )
		Key = SetGIIdent ( iIndex );
	else
		Key = SetIdent ( iIndex );

	if ( 0 == Key)
		return;
	Number++;
	*(pKey+Number) = Key;
	iIndex=_ObjClassList.GetNextSelected ();

	while ( iIndex != -1 ) {
		if ( isGeometrieTyp(_OKlTyp) )
			Key = SetGIIdent ( iIndex );
		else
			Key = SetIdent ( iIndex );

		if ( 0 == Key)
			return;

		Number++;
		*(pKey+Number) = Key;

		iIndex=_ObjClassList.GetNextSelected ();
		Flag = FALSE;

	}
//---------------------------------------------------------------------------

	*pKey = (long) Number;
	if ( Number == 1 ) {		// Id schon angeklickt ??
		if ( *(pKey+1) == _LastIdent && MKode == _LastMkode) {
			DELETE_OBJ ( pKey );
			return;
		} else {
			_LastIdent = *(pKey+1);
			_LastMkode = MKode;    
		}	
	} else {
		_LastIdent = 0L;
		_LastMkode = 0L;
	}
	_isShowInfoBox = FALSE;

	if ( isGeometrieTyp(_OKlTyp) )
		FindIntervall ( pKey , &IT);
	else
		AddCountObjTypes ( pKey , &IT);

	_iIdTyp = 0;

	if ( IT.lArea > 0 )
		_iIdTyp = _iIdTyp | OTFlaeche;
	if ( IT.lLine > 0 )
		_iIdTyp = _iIdTyp | OTLinie;
	if ( IT.lPoint > 0 )
		_iIdTyp = _iIdTyp | OTPunkt;
	if ( IT.lText > 0 )
		_iIdTyp = _iIdTyp | OTText;

	DELETE_OBJ ( pKey);
	DELETE_OBJ ( _pInfoBox);
	_isShowInfoBox = FALSE;

	ShowObjects ( &IT );

	if ( Flag ) {
		if ( isGeometrieTyp(_OKlTyp) )
			ShowGIKlassText ( Key );
		else
			ShowPBDText ( Key, 'i' );
	} else {
		if ( !isHelpText()) {
			_pHelpText -> SetHelpText (ResID(IDH_HELPOKLSUMM,&_RF));
			SetHelpText(TRUE);
		}
	}
	
}
//------------------------------------------------------------------------
//--------------------------------------------------------------------
void DBClassification :: AddCountObjTypes ( long *pKey, struct IDGITYP *p )
{
	if ( _pIDM == NULL )
		return;

	DELETE_OBJ ( _pInfoBox);
	long NumNo;
	short flag;
	_NumObject = CountObjects ( &NumNo,pKey,&flag);
	_ObjRecherche = TRUE;
//	flag = true -> es sind Flaechen und/oder Linien vorhanden
	if ( NumNo > (long) MAXOBJECTS && ( isAttribut (_OKlTyp) || isDataBase( _OKlTyp)) && flag ) {
		char *pBuf = new char [_MAX_PATH];
		if ( pBuf == NULL )
			return;
		*pBuf = '\0';
		wsprintf ( pBuf ,ResString ( ResID ( IDS_OCLCOUNTOBJECTS,&_RF),190),NumNo );
		HWND hwnd = this->Handle();
		
		int flag = MessageBox ( hwnd , pBuf ,
			 ResString ( ResID ( IDS_OCLASSRECHERCHE,&_RF),50),
			 MB_YESNO|MB_ICONEXCLAMATION);
		
		DELETE_OBJ ( pBuf );
		if ( flag == IDNO ) {
			_isDetails = FALSE;
			_ObjRecherche = FALSE;
		} else {
			_isDetails = TRUE;
			_ObjRecherche = TRUE;
		}		
	} 

	_lRange = NumNo;
	long Key;	
	for ( long i = 0; i < *pKey ; i++) {
		Key = *(pKey+i+1);
		if ( _pInfoBox != NULL && _pInfoBox ->Break() ) {
			if ( !_isBreak )
				KillIdent();
			LoescheClickInObjList( Key);
		} else
			EnumeriereObjekte ( Key , p);
	}
	_isBreak = false;
	return;
}

//--------------------------------------------------------------------
void DBClassification :: EnumeriereObjekte ( long Key, struct IDGITYP *p )
{
	if ( _pIDM == NULL )
		return;
	CTable t ( *_pIDM);

	if ( !t.Find ( &Key))
		return;
	IDMLock l(t);
	if ( _pInfoBox != NULL ) {
		if ( _pInfoBox ->Break() ) {
			if ( !_isBreak)
				KillIdent();
			LoescheClickInObjList( Key);
			IDGITYP ID;
			SetZero(&ID);
			l->StoreObjParam(&ID);
			l->Count() = 0;
			if ( l->pObjects() != NULL ) {
				l->DeleteObjTree();
			}
			return;
		}
	} else {
		if ( l->pObjects() == NULL ) {
			char *pBuf = new char [_MAX_PATH];
			if ( pBuf == NULL )
				return;
			*pBuf = '\0';
			wsprintf ( pBuf ,ResString ( ResID ( IDS_OCLASSRECHERCHE,&_RF),50));
			_pInfoBox = new IdentInformation ( this, SHOWIDENTIFIKATOR, _RF,_pIDM,pBuf,_lRange);
			_lRange = 0;	// Auf zur Kumulative
			_pInfoBox->Update();
			DELETE_OBJ ( pBuf);
		}
	}

	if ( p->lMCode == 0 ) {
		p->lPoint = p->lPoint + l->Punkt();
		p->lLine = p->lLine + l->Linie();
		p->lArea = p->lArea + l->Flaeche();
		p->lText = p->lText + l->Text();
		p->lNoname = p->lNoname + l->Sonstige();
		if ( _ObjRecherche) {
			if ( l->pObjects() == NULL )
				FindAllObjects (true, Key);
			p->rArea = p->rArea + l->FlInhalt();
			p->rPolyLen = p->rPolyLen + l->LinLaenge(); 
//	Hier könnte noch minimale + maximale FLaeche/Linie bestimmt werden
//----------------Container----------------------------------

			if ( p->lYmin > l->RuHoch() ) 
				p->lYmin = l->RuHoch();
			if ( p->lXmin > l->LoRechts() ) 
				p->lXmin = l->LoRechts();
//--------------------Maximum------------------------------
			if ( p->lYmax < l->LoHoch() )
				p->lYmax = l->LoHoch();
			if ( p->lXmax < l->RuRechts() )
				p->lXmax = l->RuRechts();
		}

	} else {
//-----Recherche nach Merkmal-----------------------------------
		if ( _ObjRecherche ) {
			if ( l->pObjects() == NULL )
				FindAllObjects ( true, Key ); 
		} else {
			if ( l->pObjects() == NULL )
				FindAllObjects ( false, Key ); 
		}
		OBJTree *pObj = l->pObjects();
		short MFlag = TRUE;
		if ( _MKode != p->lMCode )
			MFlag = FALSE;
		short Count = SearchObjectMCode ( MFlag, pObj, p);
		if ( Count > 0 )
			l->StoreMCode( p->lMCode);
		else
			l->StoreMCode(0L);
	}
	return;
}
//---------------------------------------------------------------
void DBClassification :: KillIdent ( void )
{
	HWND hWnd = _pInfoBox->Handle();
	MessageBox ( hWnd ,
	 ResString ( ResID ( IDS_OCLSTOPWORK,&_RF),90),
	 ResString ( ResID ( IDS_OCLASSRECHERCHE,&_RF),50),
	 MB_OK|MB_ICONEXCLAMATION);
	_LastIdent = 0L;
	_LastMkode = 0L;
	_isBreak = true;
}
//---------------------------------------------------------------
void DBClassification :: LoescheClickInObjList ( long Ident )
{
int iCount = _ObjClassList.GetCount();	
int iIndex = _ObjClassList.GetFirstSelected();
	if (iIndex != -1) {
		long Key = SetIdent ( iIndex );
		if ( 0 == Key )
			return;
		if ( Key == Ident ) {
			_ObjClassList.ChangeSelected ( Range(iIndex,iCount-1),FALSE);
			return;
		}
		iIndex=_ObjClassList.GetNextSelected ();
		while ( iIndex != -1 ) {
			Key = SetIdent ( iIndex );
			if ( 0 == Key )
				return;
			if ( Key == Ident ) {
				_ObjClassList.ChangeSelected ( Range(iIndex,iCount-1),FALSE);
				return;
			}
			iIndex=_ObjClassList.GetNextSelected ();
		}
	}
	return;
}
//---------------------------------------------------------------
void DBClassification :: FindAllObjects ( bool iall , long Ident )
{
//-----iall = true : Alle ObjektInformationen
//     iall = false : Nur z„hlen und speichern

	if ( _pIDM == NULL )
		return;
	CTable t ( *_pIDM );
	if(_pInfoBox != NULL) {
		if ( !_isShowInfoBox ) {
			_isShowInfoBox = TRUE;
			_pInfoBox->Show();
			_pInfoBox->Update();
		}
		_pInfoBox->ModifyWindow(Ident);
	}
	if ( t.Find ( &Ident)) {
		long lRange = 0;
		IDMLock l(t);
		if ( isDataBase(_OKlTyp) || isAttribut(_OKlTyp) ) {	// i.a. keine Objekte analysiert
			OBJTree *pObj = l->pObjects();
			if ( pObj ) 
				l->DeleteObjTree();
			pObj = new OBJTree;

			OBJPOINT OTYP;
			OTYP.pOBJ = pObj;
			OTYP.GiTyp = l->IdentGiTyp();
			OTYP.pStatus = _pInfoBox;
			OTYP.lCount = 0;
			OTYP.lRange = _lRange;
			OTYP.pCTF = _pCTF;

			ENUMLONGKEY ENL;
			if ( iall )
				ENL.eFcn = ( ENUMLONGKEYPROC ) EnumObjectsWithTyp;
			else
				ENL.eFcn = ( ENUMLONGKEYPROC ) EnumOnlyObjects;


			ENL.eKey = Ident;

			ENL.ePtr = &OTYP;
			DEX_EnumIdentObjects (ENL);
			if ( OTYP.lCount < 0) {	// Break
				KillIdent();
				LoescheClickInObjList( Ident);
				DELETE_OBJ ( pObj);
				l->Count() = 0;
				return;
			}
			_lRange = OTYP.lRange;

			l->StoreObjTree (pObj);

			CTable s(*pObj);
	
			IDGITYP Kstr;
			IDGITYP Estr;
			SetZero (&Kstr);
			
			for ( s.First(); s.Valid(); s.Next() ) {
				OBJLock k(s);
				SetZero(&Estr);
				if ( iall) {
					Estr.rArea =  k->FlInhalt();
					Estr.rPolyLen =  k->LinLaenge();
					Estr.rAreaMin =  k->FlInhalt();
					Estr.rPolyLenMin =  k->LinLaenge();
					Estr.rAreaMax =  k->FlInhalt();
					Estr.rPolyLenMax =  k->LinLaenge();

					Estr.lYmin = k->RuHoch();
					Estr.lXmin = k->LoRechts();
					Estr.lYmax = k->LoHoch();
					Estr.lXmax = k->RuRechts();
				}
				CumulateObjects( &Kstr,&Estr);
				lRange++;
			}
			l->Count() = lRange;
			l->StoreObjParam(&Kstr);
			pObj->Optimize();
		}
	}
	return;
}
//---------------------------------------------------------------
/*---------------------------------------------------------------
void DBClassification :: FindeNurObjekte ( long Ident )
{
	if ( _pIDM == NULL )
		return;
	CTable t ( *_pIDM );
	if(_pInfoBox != NULL) {
		if ( !_isShowInfoBox ) {
			_isShowInfoBox = TRUE;
			_pInfoBox->Show();
		}
		_pInfoBox->ModifyWindow(Ident);
	}
	if ( t.Find ( &Ident)) {
		short iRange = 0;
		IDMLock l(t);
		if ( isDataBase(_OKlTyp) || isAttribut(_OKlTyp) ) {	// i.a. keine Objekte analysiert
			OBJTree *pObj = new OBJTree;

			OBJPOINT OTYP;
			OTYP.pOBJ = pObj;
			OTYP.GiTyp = l->IdentGiTyp();
			OTYP.pStatus = _pInfoBox;
			OTYP.iCount = 0;
			OTYP.iRange = _iRange;
			OTYP.pCTF = _pCTF;

			ENUMLONGKEY ENL;
			ENL.eFcn = ( ENUMLONGKEYPROC ) EnumOnlyObjects;

			ENL.eKey = Ident;

			ENL.ePtr = &OTYP;
			DEX_EnumIdentObjects (ENL);
			_iRange = OTYP.iRange;
			l->StoreObjTree (pObj);

			CTable s(*pObj);
	
			IDGITYP Kstr;
			IDGITYP Estr;
			SetZero (&Kstr);
			
			for ( s.First(); s.Valid(); s.Next() ) {
				OBJLock k(s);
				SetZero(&Estr);
				CumulateObjects( &Kstr,&Estr);
				iRange++;
			}
			l->Count() = iRange;
			l->StoreObjParam(&Kstr);
			pObj->Optimize();
			
		}
	}
	return;
}
---------------------------------------------------------------*/
//----------------------------------------------------------------
long DBClassification :: SetIdent ( int iIndex )
{
char * pBuff = new char [_MAX_PATH];

	if ( pBuff == NULL ) return 0;

long Ident = 0L;

	
	_ObjClassList.GetString (pBuff, iIndex, _MAX_PATH);

	char *ptr = strchr (pBuff, ':');
	if (ptr)
		*ptr = '\0';

#if _MSC_VER < 1200

	HRESULT hr = IdentFromClassX (pBuff, (ULONG *)&Ident);
	if (FAILED(hr)) {
		DELETE_OBJ(pBuff);
		return 0;
	}
#else
	Ident = _ObjClassList.GetItemData (iIndex);		// Ident ist am Item gespeichert
	TX_ASSERT(0 != Ident);
#endif // _MSC_VER < 1200


	DELETE_OBJ(pBuff);

	return Ident;	

}
//----------------------------------------------------------------
long DBClassification :: SetGIIdent ( int iIndex )
{
char * pBuff = new char [_MAX_PATH];

	if ( pBuff == NULL ) return 0;

	long Ident = 0L;

	
	_ObjClassList.GetString (pBuff, iIndex, _MAX_PATH);

	char *ptr = strchr (pBuff, ':');
	if (ptr)
		*ptr = '\0';

	Ident = atol (pBuff);

	DELETE_OBJ(pBuff);

	return Ident;	

}
//-----------------------------------------------------------------
long DBClassification :: SetMKode ( void )
{
char * pBuff = new char [_MAX_PATH];
	if ( pBuff == NULL ) 
		return 0;

	_MerkmalList.GetCurrentString (pBuff);
	char *ptr = strchr (pBuff, ':');
	if ( ptr == NULL ) {
		DELETE_OBJ (pBuff);
		return 0;
	} else
		*ptr = '\0';

	if ( DEX_GetMkBase() == 16 )
		_MKode = strtoul ( pBuff, NULL, 16 );
	else
		_MKode = atol(pBuff);
	*ptr = ':';
	DELETE_OBJ ( pBuff );
	return _MKode;
}
//------------------------------------------------------------------
Bool DBClassification :: FindIntervall ( long *pKey , struct IDGITYP *p)
{
	if ( _pGICLA == NULL )
		return FALSE;

	CTable t(*_pGICLA);

	for ( long i = 0; i < *pKey ; i++) {

	    long Ident = *(pKey+i+1);

	    if ( t.Find (&Ident) ) {
	
		GICLALock l(t);
		long Count = l->Count();
		if ( Count == 0 ) {	//	Intervall ohne Elemente
			l->MCode() = p->lMCode;
		} else {
		    IDGITYP Estr;
		    SetZero(&Estr);
		    l->MCode() = 0L;
		    if ( p->lMCode == 0L ) {
			if ( l->GiTyp() == OTLinie ) {
				Estr.lLine = l->Count();
				Estr.rPolyLen = l->Kumul()*l->Einheit(); 
			}
			if ( l->GiTyp() == OTFlaeche ){
				Estr.lArea = l->Count();
				Estr.rArea = l->Kumul()*l->Einheit();
			}
	//--------------Container------------------------------
			Estr.lXmin = l->Xmin();
			Estr.lXmax = l->Xmax();
			Estr.lYmin = l->Ymin();
			Estr.lYmax = l->Ymax();
			KumulIdent ( p, &Estr);
			l->CountM() = 0;		// keine Modifikationen
		     } else {
			OBJTree *pOBJ = l->pObjects();
			CTable d( *pOBJ );
			Count = 0;			
			p->iITyp = l->GiTyp();
			IDGITYP Estr;
			for (d.First(); d.Valid() ; d.Next()  ) {
	
				OBJLock m(d); 

				SetZero(&Estr);
				m->MCode() = 0L;
				if ( m->Ident() == l->IDNr() ) {
				    short MFlag = TRUE;
				    if ( _MKode != p->lMCode )
					MFlag = FALSE;
				    if ( ExistMCodeInObject( MFlag, p->lMCode, m->Object())) {
					m->MCode() = p->lMCode;
					Estr.lMCode = p->lMCode;
					Estr.rArea =  m->FlInhalt();
					Estr.rPolyLen =  m->LinLaenge();
				
					if ( l->GiTyp() == OTFlaeche ) {
						Estr.lArea = 1;
					} else {
						Estr.lLine = 1;
					}
					Count ++;
					Estr.lYmin = m->RuHoch();
					Estr.lXmin = m->LoRechts();
					Estr.lYmax = m->LoHoch();
					Estr.lXmax = m->RuRechts();
					KumulIdent ( p, &Estr);
				   }
				}

			}
			l->MCode() = p->lMCode;
			l->CountM() = Count;		// neuer O'Zähler
		   }
		}	// Count != 0
	    }	// Find Ident
	}	//FOR
	return TRUE;
}


//---------------------------------------------------------------------
void DBClassification :: ShowPBDText ( long Key, short TCode )
{
	if ( isHelpText()) 
		return;


PBDDATA pbdData;
char *pLText = new char [1000];
	if ( pLText == NULL )
		 return;
	*pLText = NULL;
	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = TCode;
	pbdData.pbdCode = Key;

	if ( TCode == 'i' ) {
		pbdData.pbdLText = pLText;
		pbdData.pbdKTextLen = 0;
		pbdData.pbdLTextLen = 999;
	} else {
		pbdData.pbdKText = pLText;
		pbdData.pbdLTextLen = 0;
		pbdData.pbdKTextLen = 999;
	}

	DEX_GetPBDData (pbdData);

	if ( SucheLeerZeichen ( pLText ))
			*pLText = NULL;

	if (pLText != NULL && *pLText != NULL ) {
		if ( pbdData.pbdTemp ) {
			_pHelpText -> SetHelpText (ResID(IDH_HELPTEMPOKL,&_RF));
		} else {
//------------------MK bzw ID als Text
			if ( TCode == 'i')
				_pHelpText -> SetHelpTextV ( ResID(IDH_HELPOKLBESCHREIBUNG,&_RF),pLText);
			else
				_pHelpText -> SetHelpTextV ( ResID(IDH_HELPMKBESCHREIBUNG,&_RF),pLText);
		}
		SetHelpText(TRUE);
	} else  {
		if ( TCode == 'i' ) {
			_pHelpText -> SetHelpText (ResID(IDT_KEINIDLANGTEXT,&_RF));
		} else {
			_pHelpText -> SetHelpText (ResID(IDT_KEINMKLANGTEXT,&_RF));
		}
		SetHelpText(TRUE);
	}
	DELETE_OBJ (pLText);

}

//---------------------------------------------------------------------
void DBClassification :: ShowGIKlassText ( long Key )
{

	if ( isHelpText()) 
		return;

	if ( _pGICLA == NULL ) 
		return;
	
	CTable t(*_pGICLA);
	if ( !t.Find (&Key) )
		return;


char * pLText = new char [_MAX_PATH];
char * pBuf = new char [_MAX_PATH];
	if ( pLText == NULL || pBuf == NULL ) {
		DELETE_OBJ (pLText );
		DELETE_OBJ (pBuf);
		return;
	}
	*pLText = '\0';
	*pBuf = '\0';
	
	GICLALock l(t);

	strcat ( pLText, " [ ");
	ST_DtoA ( pBuf, "%8.1f",l->VglWert1());
	strcat ( pLText, pBuf );
	strcat ( pLText , " , ");
	ST_DtoA ( pBuf, "%8.1f",l->VglWert2());
	strcat ( pLText, pBuf );
	strcat ( pLText , " ] ");
	*pBuf = '\0';

	if ( l->GiTyp() == OTLinie ) {
		if ( l->Einheit() == KiloMeter )
			strcat( pBuf , ResString( ResID(IDT_UNITKM,&_RF),MAXSTRING));
		else
			strcat( pBuf , ResString( ResID(IDT_UNITKM,&_RF),MAXSTRING));
		*strrchr ( pBuf, ']') = '\0';
		
		_pHelpText -> SetHelpTextV ( ResID( IDH_LINIENINTERVALL, &_RF) ,pLText, pBuf+1);
		SetHelpText(TRUE);
	}
	if ( l->GiTyp() == OTFlaeche ){
		if ( l->Einheit() == QuadratKiloMeter )
			strcat( pBuf , ResString( ResID(IDT_UNITQKM,&_RF),MAXSTRING));
		if ( l->Einheit() == QuadratMeter )
			strcat( pBuf , ResString( ResID(IDT_UNITQM,&_RF),MAXSTRING));
		if ( l->Einheit() == Hektar )
			strcat( pBuf , ResString( ResID(IDT_UNITHA,&_RF),MAXSTRING));
		
		*strrchr ( pBuf, ']') = '\0';
		_pHelpText -> SetHelpTextV ( ResID( IDH_FLAECHENINTERVALL, &_RF) ,pLText, pBuf+1);
		SetHelpText(TRUE);
	}


	DELETE_OBJ (pLText);
	DELETE_OBJ (pBuf);
	return;
}
//-------------------------------------------------------------------

Bool DBClassification :: ModifyGIKlassList ( void )
{

int iIndex = _ObjClassList.GetFirstSelected();
int max = _ObjClassList.GetCount();
long number = 0L;

	if ( _pGICLA == NULL )
		return FALSE;
	if ( max < 1 )
		return FALSE;

	long * pGroup = new long [max];
	if ( pGroup == NULL)
		return FALSE;

	for ( int i=0; i< max; i++) {
		*(pGroup+i) = i+1;
	}

	CTable t(*_pGICLA);

	if (iIndex != -1) {

//		long Key = SetIdent ( iIndex );
		long Key = SetGIIdent ( iIndex );
		if ( 0 == Key)
			return FALSE;

		*(pGroup+Key-1) = -Key;
		iIndex=_ObjClassList.GetNextSelected ();

		while ( iIndex != -1 ) {
//			long Key = SetIdent ( iIndex );
			long Key = SetGIIdent ( iIndex );
			if ( 0 == Key)
				return FALSE;
			*(pGroup+Key-1) = -Key;
			iIndex=_ObjClassList.GetNextSelected ();
		}

		for ( i=0; i< max;i++  ) {
			Key = *(pGroup+i);
			if ( Key > 0 && t.Find ( &Key ))
				t.Delete();		
		}

		for ( t.First(); t.Valid(); t.Next() ) {
			GICLALock l(t);
			number += l->Count();
		}
		LoadGIVector ( number);
		return TRUE;
	}

	return FALSE;
}

//-------------------------------------------------------------------
void DBClassification :: ShowObjects ( struct IDGITYP *p )
{

char *pBuff = new char[TEXTLEN+20];
//char *pNum = new char[20];
// KK010201
char *pNum = new char[_MAX_PATH];

	if ( pNum == NULL || pBuff == NULL ) {
		DELETE_OBJ ( pBuff );
		DELETE_OBJ ( pNum );
		return;
	}

	*pNum = NULL;
	*pBuff = NULL;

	ResString rsKT ( ResID (IDT_KEINE, &_RF), 35);
	_Details.Disable();
	_NumObject = 0;
	_NumObject = p->lPoint+p->lLine+p->lArea+p->lText+p->lNoname;

	if ( _NumObject > 0 )
	        _PutClipBoard.Enable();
	else
	        _PutClipBoard.Disable();

	if ( !isGeometrieTyp(_OKlTyp) ) {
		if ( ( p->lLine > 0 || p->lArea > 0) && _isDetails == TRUE )
			_Details.Enable();

	}

//------------------Container-------------------------------------
	if ( p->lXmin != MAXKOORD && p->lXmax != 0L) {
		Bool Flag = FALSE;
		if ( _NumObject > 0L && _ObjRecherche == TRUE) {
			_KooCont[0]=p->lXmin;
			_KooCont[1]=p->lXmax;
			_KooCont[2]=p->lYmin;
			_KooCont[3]=p->lYmax;
			Flag = SetKoord ();
		}
		if ( Flag ) {
			_LoRechtsWert.SetText( ltoa ( _KooCont[0],pNum,10));
			_RuRechtsWert.SetText( ltoa ( _KooCont[1],pNum,10));
			_LoHochWert.SetText( ltoa ( _KooCont[3],pNum,10));
			_RuHochWert.SetText( ltoa ( _KooCont[2],pNum,10));
		} else
			SetNoMetric();
	}
//-----------------------------------------------------------------
//-------------Kumulierte Werte------------------------------------

	_FlaechenInhalt.SetText ( NULL);
	_FlaechenMass.SetText ( NULL);
	_LinienLaenge.SetText ( NULL);
	_LinienMass.SetText (NULL);


	if ( p->rArea > 0.0 ) {
	    if ( p->rArea > (double) Hektar ) {
		if ( p->rArea > (double) QuadratKiloMeter ) {
			p->rArea = p->rArea / (double) QuadratKiloMeter;
			_FlaechenMass.SetText (ResString( ResID( IDT_UNITQKM,&_RF),15));	
		} else {
			p->rArea = p->rArea / (double) Hektar;
			_FlaechenMass.SetText ( ResString( ResID ( IDT_UNITHA,&_RF),15));	
		}
	    } else {
		_FlaechenMass.SetText ( ResString( ResID( IDT_UNITQM, &_RF),15));
	    }

	    ST_DtoA ( pNum, "%8.3f", p->rArea);
	    _FlaechenInhalt.SetText( pNum );
	}
//------------------------------------------------------------

	if ( p->rPolyLen > 0.0 ) {
		if ( p->rPolyLen > (double) KiloMeter ) {
			p->rPolyLen = p->rPolyLen / (double) KiloMeter;
			_LinienMass.SetText ( ResString ( ResID(IDT_UNITKM,&_RF),15));
		} else {
			_LinienMass.SetText ( ResString ( ResID (IDT_UNITM,&_RF),15));
		}
		ST_DtoA ( pNum, "%8.3f",p->rPolyLen);
		_LinienLaenge.SetText (pNum);
 
	}

	if ( _NumObject > 0L ) {
		_ShowObjTyp = 0;
		if ( isDataBase(_OKlTyp))
			_Anzeigen.Disable();
		else
			_Anzeigen.Enable();
		wsprintf ( pBuff, ResString( ResID( IDT_OCLOBJEKTE,&_RF),35), ltoa ( _NumObject,pNum,10) );
		if ( _NumObject == 1L ) {
			wsprintf ( pBuff, ResString( ResID( IDT_OCLOBJEKT,&_RF),35), ltoa ( _NumObject,pNum,10) );
		}
		_Objekte.SetText( pBuff );
	} else {
		wsprintf ( pBuff,  ResString( ResID( IDT_OCLOBJEKTE,&_RF),35),  rsKT.Addr());
		_Objekte.SetText( pBuff );
		_Anzeigen.Disable();
		_MerkmalAnzeige.Disable();
	}

	if ( p->lPoint) {
		wsprintf ( pBuff,  ResString( ResID( IDC_OCLPUNKTE,&_RF),15), ltoa ( p->lPoint,pNum,10));
		if ( p->lPoint == 1L ) {
			wsprintf ( pBuff,  ResString( ResID( IDC_OCLPUNKT,&_RF),15), ltoa ( p->lPoint,pNum,10));
		}
		_Punkte.SetText( pBuff);
		_Punkte.SetChecked(TRUE);
		SetObjTyp ( OTPunkt );
		if ( isDataBase(_OKlTyp))
			_Punkte.Disable();
		else
			_Punkte.Enable();
	} else {
		wsprintf ( pBuff,  ResString( ResID( IDC_OCLPUNKTE,&_RF),35),  rsKT.Addr());
		_Punkte.SetText( pBuff);
		_Punkte.SetChecked(FALSE);
		_Punkte.Disable();
	}

	if ( p->lLine ) {
		wsprintf ( pBuff,  ResString( ResID( IDC_OCLLINIEN,&_RF),15), ltoa ( p->lLine,pNum,10));
		if ( p->lLine == 1L ) {
			wsprintf ( pBuff,  ResString( ResID( IDC_OCLLINIE,&_RF),15), ltoa ( p->lLine,pNum,10));
		}
		_Linien.SetText( pBuff );
		_Linien.SetChecked(TRUE);
		SetObjTyp ( OTLinie );
		if ( isDataBase(_OKlTyp))
			_Linien.Disable();
		else
			_Linien.Enable();
	} else {
		wsprintf ( pBuff,  ResString( ResID( IDC_OCLLINIEN,&_RF),15), rsKT.Addr() );
		_Linien.SetText ( pBuff );
		_Linien.SetChecked(FALSE);
		_Linien.Disable();
	}

	if ( p->lArea ) {
		wsprintf ( pBuff,  ResString( ResID( IDC_OCLFLAECHEN,&_RF),15), ltoa ( p->lArea,pNum,10));
		if ( p->lArea == 1L ) {
			wsprintf ( pBuff,  ResString( ResID( IDC_OCLFLAECHE,&_RF),15), ltoa ( p->lArea,pNum,10));
		}
		_Flaechen.SetText( pBuff );
		_Flaechen.SetChecked(TRUE);
		SetObjTyp ( OTFlaeche );
		if ( isDataBase(_OKlTyp))
			_Flaechen.Disable();
		else
			_Flaechen.Enable();
	} else {                                     
		wsprintf ( pBuff,  ResString( ResID( IDC_OCLFLAECHEN,&_RF),15),  rsKT.Addr());
		_Flaechen.SetText ( pBuff );
		_Flaechen.SetChecked(FALSE);
		_Flaechen.Disable();
	}

	if ( p->lText ) {
		wsprintf ( pBuff,  ResString( ResID( IDC_OCLTEXTE,&_RF),15), ltoa ( p->lText,pNum,10));
		if ( p->lText == 1L ) {
			wsprintf ( pBuff,  ResString( ResID( IDC_OCLTEXT,&_RF),15), ltoa ( p->lText,pNum,10));
		}
		_Texte.SetText(  pBuff );
		_Texte.SetChecked(TRUE);
		SetObjTyp ( OTText );
		if ( isDataBase(_OKlTyp))
			_Texte.Disable();
		else
			_Texte.Enable();
	} else {
		wsprintf ( pBuff,  ResString( ResID( IDC_OCLTEXTE,&_RF),15), rsKT.Addr());
		_Texte.SetText ( pBuff );
		_Texte.SetChecked(FALSE);
		_Texte.Disable();
	}

	if ( p->lNoname ) {
		wsprintf ( pBuff,  ResString( ResID( IDC_OCLSONSTIGE,&_RF),15), ltoa ( p->lNoname,pNum,10));
		_Sonstige.SetText( pBuff );
		_Sonstige.SetChecked(TRUE);
		SetObjTyp( OTKO );
		if ( isDataBase(_OKlTyp))
			_Sonstige.Disable();
		else
			_Sonstige.Enable();
		if ( _NumObject == p->lNoname ) {
			_LoRechtsWert.SetText( NULL );
			_RuRechtsWert.SetText( NULL );
			_LoHochWert.SetText( NULL );
			_RuHochWert.SetText( NULL );
		}
	} else {
		wsprintf ( pBuff,  ResString( ResID( IDC_OCLSONSTIG,&_RF),15), rsKT.Addr() );
		_Sonstige.SetText( pBuff);
		_Sonstige.SetChecked(FALSE);
		_Sonstige.Disable();
	}
	DELETE_OBJ ( pBuff);
	DELETE_OBJ ( pNum);
	return;
}
//---------------------------------------------------------------------
Bool DBClassification :: ShowMKWert ( void ) 
{

	if ( _MerkmalAnzeige.isChecked() ) 
		return TRUE;
	else
		return FALSE;

}
//---------------------------------------------------------------------
void DBClassification :: ClearObjectInformation ( void ) 
{
char *pBuff = new char[TEXTLEN+20];
	if ( pBuff == NULL ) 
		return;

//------------------Nullen-------------------------------------
	ResString pKT ( ResID (IDT_KEINE, &_RF), 35);

	wsprintf ( pBuff, ResString( ResID( IDT_OCLOBJEKTE,&_RF),35), pKT.Addr() );
	_Objekte.SetText( pBuff );


	wsprintf ( pBuff,  ResString( ResID( IDC_OCLPUNKTE,&_RF),35),  pKT.Addr());
	_Punkte.SetText( pBuff);
	_Punkte.SetChecked(FALSE);
	_Punkte.Disable();

	wsprintf ( pBuff,  ResString( ResID( IDC_OCLLINIEN,&_RF),15), pKT.Addr() );
	_Linien.SetText ( pBuff );
	_Linien.SetChecked(FALSE);
	_Linien.Disable();

	wsprintf ( pBuff,  ResString( ResID( IDC_OCLFLAECHEN,&_RF),15),  pKT.Addr());
	_Flaechen.SetText ( pBuff );
	_Flaechen.SetChecked(FALSE);
	_Flaechen.Disable();

	wsprintf ( pBuff,  ResString( ResID( IDC_OCLTEXTE,&_RF),15), pKT.Addr());
	_Texte.SetText ( pBuff );
	_Texte.SetChecked(FALSE);
	_Texte.Disable();

	_Sonstige.SetText ( ResString( ResID( IDC_OCLSONSTIG,&_RF),35) );
	_Sonstige.SetChecked(FALSE);
	_Sonstige.Disable();

	_Anzeigen.Disable();

	DELETE_OBJ ( pBuff);
	return;
}
//---------------------------------------------
void _XTENSN_EXPORT DBClassification :: ListBoxClk (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_OCLOBJCLASSLIST:
		{
		CEierUhr Wait(_pW);
		long Mkode = AnalysObjClass ();
		AnalysIDListBox ( Mkode );
		}
		break;

	case IDCB_OCLMERKMALLIST:
		{
		CEierUhr Wait(_pW);
		long Mkode = AnalysObjEig ( );
		AnalysIDListBox ( Mkode);
		}
		break;
	}

}

//	DB-Koordinaten in ASC-Koordinaten umwandeln
Bool DBClassification :: SetKoord ( void ) 
{
	StatistTrfKoord Trf ( _pCTF, _KooCont );
	Trf.FromDBToAsc();
	Trf.Transform ();
	Trf.GetKoord( _KooCont);
	return Trf.isDBMetric();
}

//	ASC-Koordinaten in DB-Koordinaten umwandeln
void DBClassification :: SetNoMetric ( void ) 
{
char *pText;
	StatistTrfKoord Trf ( _pCTF, _KooCont );
	Bool Metric = Trf.isDBMetric();
	if ( !Metric ) {
		pText = Trf.TransToLoR ();
		if ( pText)
			_LoRechtsWert.SetText(pText);
		pText = Trf.TransToRuR ();
		if ( pText)
			_RuRechtsWert.SetText(pText);
		pText = Trf.TransToLoH ();
		if ( pText)
			_LoHochWert.SetText(pText);
		pText = Trf.TransToRuH ();
		if ( pText)
			_RuHochWert.SetText(pText);
	}
	return;
}

//------------------ClipBoard------------------------------------
void DBClassification :: PutIdentToClipBoard ( void )
{

	int max = _ObjClassList.GetCount();

	if ( max <= 0 )
		return;

	unsigned short * pParam = new unsigned short [ MaxParam];
	if ( pParam == NULL )
		return;

	short MFlag = TRUE;

	_isClipUeberschrift = true;
	_isClipKumulativ = true;
	_isClipEintrag = true;
	_isClipEigenschaft = true;

	if ( _isIDLIST)	{
		CEierUhr Wait ( _pW);

		ClipBoardClass CBC ( this, CLIPBOARDVIEW, _RF, _OKlTyp, pParam);
		CBC.Show();
		if ( CBC.Result()== 0 ) {
			DELETE_OBJ ( pParam);
			return;
		} else {
			_isClipUeberschrift = CBC.Ueberschrift_isChecked();
			_isClipKumulativ = CBC.Kumulativ_isChecked();
			_isClipEintrag = CBC.Eintrag_isChecked();
			_isClipEigenschaft = CBC.Eigenschaft_isChecked();
		}
	} else
		DELETE_OBJ ( pParam);

	int MaxBuf = ( max + 10) * (int) MAXRECORD;
	char * pBuf = new char [ MaxBuf ];
	if ( pBuf == NULL )
		return;

	*pBuf = '\0';

	{	//	ClipBoard
	CClipboard CLP;
	CLP.Clear();
	
	long Mkode = 0L;
	if ( _ObjektEigenschaften.isChecked() ) {
		Mkode = _MKode;
		if ( _AusschlMerkmal.GetState()) {
			Mkode = -_MKode;
			MFlag = FALSE;
		}
 	}

//
	{	// GlobalClass
	void * pData; 
	
	if ( isGeometrieTyp(_OKlTyp) ) 
		pData = ( void *) _pGICLA;
	else
		pData = ( void *) _pIDM;  
		
	GlobalObjClass GOC ( &_RF, MFlag, Mkode, pData , _OKlTyp, pParam, _iIdTyp);

	char *pText;

	if ( _isClipUeberschrift ) {
		pText = GOC.GetCaption();
		strcat ( pBuf , pText);
	}

	if ( _isIDLIST ) {	// IDs wurden selektiert

		int iIndex = _ObjClassList.GetFirstSelected();

		if (iIndex != -1) {
			long Ident = SetIdent ( iIndex );
			if ( 0 == Ident)
				return;

			pText = GOC.GetText ( Ident , _isClipEigenschaft);
			if ( _isClipEigenschaft )
				strcat ( pBuf , pText);

			iIndex=_ObjClassList.GetNextSelected ();
			while ( iIndex != -1 ) {
				Ident = SetIdent ( iIndex );
				pText = GOC.GetText ( Ident , _isClipEigenschaft);
				if ( _isClipEigenschaft )
					strcat ( pBuf , pText);
				iIndex=_ObjClassList.GetNextSelected ();
			}
		}
	} else {
	
		if ( isGeometrieTyp(_OKlTyp) ) {
			CTable t(*_pGICLA );
			for (t.First(); t.Valid() ; t.Next()  ) {
	
				GICLALock l(t);
 				long Ident = ( l->Group());
				if ( l->Count() > 0 ) {
					pText = GOC.GetText ( Ident , _isClipEigenschaft);
					if ( _isClipEigenschaft )
						strcat ( pBuf , pText);
				}
			}
		} else {

			CTable t(*_pIDM );

			for (t.First(); t.Valid() ; t.Next()  ) {

				IDMLock l(t);

				long Ident = ( l->Ident());
				pText = GOC.GetText ( Ident , _isClipEigenschaft);
				if ( _isClipEigenschaft )
					strcat ( pBuf , pText);
			}
		}
	}
//	Kumulativ
	if ( _isClipKumulativ ) {
		pText = GOC.GetCumulate();
		strcat ( pBuf , pText);
	}
//	Eintraege
	if ( _isClipEintrag ) {
		pText = GOC.GetEintrag();
		strcat ( pBuf , pText);
	}

	CLP.Insert ( pBuf );
	}	// GlobalClass
	}   // ClipBoard
	DELETE_OBJ ( pBuf );
	DELETE_OBJ ( pParam);
	return;
}
/*-----------------------------------------------------------
void DBClassification :: PutGIClassToClipBoard ( void )
{

	int max = _ObjClassList.GetCount();

	if ( max <= 0 )
		return;

	char * pBuf = new char [ (max +10) * MAXRECORD ];
	if ( pBuf == NULL )
		return;

	*pBuf = '\0';
	{	//	ClipBoard
	CClipboard CLP;
	
	long Mkode = 0L;
	if ( _ObjektEigenschaften.isChecked() ) {
		Mkode = _MKode;
		if ( _AusschlMerkmal.GetState())
			Mkode = -_MKode;
 	}

//
	{	// GlobalClass
	GlobalModObjClass GOC (  &_RF, Mkode, _pGICLA );
	char *pText = GOC.GetCaption();	//woher?-l”schen??
	strcat ( pBuf , pText);

	if ( _isIDLIST ) {	// IDs wurden selektiert

		int iIndex = _ObjClassList.GetFirstSelected();

		if (iIndex != -1) {
			long Ident = SetIdent ( iIndex );


			pText = GOC.GetText ( Ident );
			strcat ( pBuf , pText);
			iIndex=_ObjClassList.GetNextSelected ();
			while ( iIndex != -1 ) {
				Ident = SetIdent ( iIndex );
				pText = GOC.GetText ( Ident );
				strcat ( pBuf , pText);
				iIndex=_ObjClassList.GetNextSelected ();
			}
		}
	} else {
	
		CTable t(*_pGICLA );

		for (t.First(); t.Valid() ; t.Next()  ) {
	
			GICLALock l(t);

			long Ident = ( l->Group());
			pText = GOC.GetText ( Ident );
			strcat ( pBuf , pText);
		}
	}
	GOC.GetCumulate();
	strcat ( pBuf , pText);
	CLP.Insert ( pBuf );
	}	// GlobalClass
	}   // ClipBoard
	DELETE_OBJ ( pBuf );
}
-------------------------------------------------------------------*/
//-------------------------------
void DBClassification :: SetHelpText ( int Flag ) 
{
	_isHelpText = Flag;
}

//--------------------------- No Member -------------------------
//-----------------------NEU-------------------------------------
//------Merkmal eines Objektes vorhanden/nicht vorhanden----------
Bool ExistMCodeInObject ( short MFlag, long MCode, long ONr )
{
	long Merkmal = MCode;

//	if ( Merkmal < 0 )
	if ( !MFlag)
		Merkmal = - MCode;
		

	TARGETMERKMAL TM;
	memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = ONr;
	TM.lMCode = Merkmal;
	TM.imaxLen = NULL;
	TM.iTTyp = TT_Objekt;
	TM.pMText = NULL;

	if( DEX_GetTextMerkmal ( TM )) {	// Merkmal gefunden
//		if ( MCode < 0 )
		if ( !MFlag )
			return FALSE;		//Frage:Mk nicht in Objekt
	} else {
	//	MCode nicht in Objekt!!!
		
//		if ( MCode > 0 )
		if ( MFlag)
			return FALSE;		//Frage:Mk in Objekt
	}
	return TRUE;
}

//--------------------ENDE NEU-----------------------------------

Bool StoreIDList ( ResourceFile *pResF, long Ident, void *pData, short DevTyp)
{

PBDDATA pbdData;
char KText[MAXFCTNAME+1];
char GITyp[5];
short GiTyp = 0;
	GITyp[0] = '\0';
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
		strcat ( KText , ResString(ResID(IDS_NODEFOBJCLASS,pResF),70));
	KText[MAXFCTNAME] = '\0';
	
	short ITyp = DEX_GetIdentObjTypes(Ident);

//--------------Id allgemein vorhandene Gi-Typen
	strcpy ( GITyp, "____");
	GiTyp = OTKO;

	if ( (GiTyp & DevTyp) > 0) {
		strcpy ( GITyp, "KOMP");
	} else {

		GiTyp = OTPunkt;
		if ( (GiTyp & ITyp) > 0) GITyp[0] = 'p';
		GiTyp = OTLinie;
		if ( (GiTyp & ITyp) > 0) GITyp[1] = 'l';
		GiTyp = OTFlaeche;
		if ( (GiTyp & ITyp) > 0) GITyp[2] = 'f';
		GiTyp = OTText;
		if ( (GiTyp & ITyp) > 0) GITyp[3] = 't';

//--------------Id : zugeordnete Gi-Typen
		GiTyp = OTPunkt;
		if ( (GiTyp & DevTyp) > 0) GITyp[0] = 'P';
		GiTyp = OTLinie;
		if ( (GiTyp & DevTyp) > 0) GITyp[1] = 'L';
		GiTyp = OTFlaeche;
		if ( (GiTyp & DevTyp) > 0) GITyp[2] = 'F';
		GiTyp = OTText;
		if ( (GiTyp & DevTyp) > 0) GITyp[3] = 'T';

	}

	char NewIdent[MAX_OKS_LENX+1];

	ClassFromIdentX ( Ident, NewIdent);
	
	wsprintf (outBuff, "%s:%s:%s", NewIdent, GITyp, KText);



#if _MSC_VER < 1200
	((ListBox *)pData) -> AddString (outBuff);
#else
	// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
	// Klammern hinten anhängen
	if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
		char cbBuffer[_MAX_PATH];
		HPROJECT hPr = DEX_GetObjectsProject(Ident);

			TX_ASSERT(NULL != hPr);
			if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
				strcat (outBuff, " (");
				strcat (outBuff, cbBuffer);
				strcat (outBuff, ")");
			}
	}

	// Ident am jeweiligen Item speichern
	int iIndex = ((ListBox *)pData) -> AddString (outBuff);

	((ListBox *)pData) -> SetItemData (iIndex, Ident);
#endif // _MSC_VER < 1200
 	
	
	return TRUE;

} 

////////////////////////////////////////////////////////////////////////
Bool StoreGIKlassList ( long Ident, void *pData, short DevTyp, double Wert1, double Wert2, char *pEinheit, long Flag)
{

char KText[MAXFCTNAME+1];
	KText[0] = '\0';

char outBuff[TEXTLEN+20];
char Buffer[30];

	ST_DtoA (KText, " %8.1f", Wert1);

//-------------- zugeordnete Gi-Typen
	if ( DevTyp == OTLinie) {
		if ( Flag )
			strcat (KText, " < L <= ");
		else
			strcat (KText, " < l <= ");
	
	}
	if ( DevTyp == OTFlaeche) {
		if ( Flag )
			strcat (KText, " < F <= ");
		else
			strcat (KText, " < f <= ");
	}

	ST_DtoA (Buffer, "%8.1f", Wert2);
	strcat ( KText, Buffer );

	wsprintf (outBuff, "%08ld:%s: %s", Ident, pEinheit, KText);
	
	((ListBox *)pData) -> AddString (outBuff);

	return TRUE;

} 
////////////////////////////////////////////////////////////////////
Bool StoreObjKlassList ( ResourceFile *pResF, long Ident, void *pData, short DevTyp)
{
Bool Flag = FALSE;
PBDDATA pbdData;
char KText[MAXFCTNAME+1];
char GITyp[5];
short GiTyp = 0;
	GITyp[0] = '\0';
	KText[0] = '\0';
	strcpy ( GITyp, "____");

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
		strcat ( KText , ResString(ResID(IDS_NODEFOBJCLASS,pResF),70) );
	KText[MAXFCTNAME] = '\0';

//--------------Id in Sicht zugeordnete Gi-Typen
	GiTyp = OTPunkt;
	if ( (GiTyp & DevTyp) > 0) GITyp[0] = 'P';
	GiTyp = OTLinie;
	if ( (GiTyp & DevTyp) > 0) GITyp[1] = 'L';
	GiTyp = OTFlaeche;
	if ( (GiTyp & DevTyp) > 0) GITyp[2] = 'F';
	GiTyp = OTText;
	if ( (GiTyp & DevTyp) > 0) GITyp[3] = 'T';


	char NewIdent[MAX_OKS_LENX+1];

	for ( short i = 0; i < 4 ; i++ ) {
 	   if ( GITyp[i] == 'L' || GITyp[i] == 'F' ) {


			ClassFromIdentX ( Ident, NewIdent);

			wsprintf (outBuff, "%s:%c:%s", NewIdent, GITyp[i], KText);


			#if _MSC_VER < 1200
				((ListBox *)pData) -> AddString (outBuff);
			#else
			// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
			// Klammern hinten anhängen
				if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
					char cbBuffer[_MAX_PATH];
					HPROJECT hPr = DEX_GetObjectsProject(Ident);

					TX_ASSERT(NULL != hPr);
					if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
						strcat (outBuff, " (");
						strcat (outBuff, cbBuffer);
						strcat (outBuff, ")");
					}
				}

				// Ident am jeweiligen Item speichern
				int iIndex = ((ListBox *)pData) -> AddString (outBuff);

				((ListBox *)pData) -> SetItemData (iIndex, Ident);
			#endif // _MSC_VER < 1200


			Flag = TRUE;
	   }
	}

	return Flag;

}

//	Liefern logische Werte fr ObjectType ( OT_... zu OT...)
short LogObjectType ( long ONr ) 
{
short TstGiTyp = 0;

	short Status = DEX_GetObjectType (ONr);

//--------------Zuordnung----------------------------
	if ( Status == OGPunkt ) TstGiTyp = OTPunkt;
	if ( Status == OGLinie ) TstGiTyp = OTLinie;
	if ( Status == OGFlaeche ) TstGiTyp = OTFlaeche;
	if ( Status == OGText ) TstGiTyp = OTText;
	if ( Status == OGKO ) TstGiTyp = OTKO;
	if ( Status == OGSachObjekt ) TstGiTyp = OTSachObjekt;
	return TstGiTyp ;
}
// _______________________________________________________________

long *ObjectContainer ( long ONr, short iObjTyp )
{

long *pCont = new long[4];
	if ( pCont == NULL )
		return NULL;

long X,Y;

	if ( iObjTyp == OT_TEXT) {



		OBJGEOMETRIE OG;
		memset (&OG,'\0',sizeof(OBJGEOMETRIE));
 		OG.dwSize = sizeof(OBJGEOMETRIE);

		OG.lONr = ONr;
		OG.lCnt = 1;
		OG.pdblX = &X;
		OG.pdblY = &Y;
		OG.iFlags &= ~OGConverted;

		if (DEX_GetObjGeometrie (OG)) {
			*pCont = X;
			*(pCont+1) = X;
			*(pCont+2) = Y;
			*(pCont+3) = Y;
		}
	} else {
	// vorher Objektcontainer definieren-----------------------------------
		long CONT[4];
		DEX_GetObjContainer ( ONr, CONT[0]);
		*pCont = CONT[0];
		*(pCont+1) = CONT[1];
		*(pCont+2) = CONT[2];
		*(pCont+3) = CONT[3];

	}
	return pCont;

}
//---------------Funktionen fr IDGITYP-Struktur-----------------

//------------------------------------------------------------------------
void  SetZero ( struct IDGITYP *p )
{
	if ( p == NULL ) return;
	p->lCount=0;
	p->lPoint=0;
	p->lLine=0;
	p->lArea=0;
	p->lComplex=0;
	p->lText=0;
	p->iITyp=0;
	p->lNoname=0;
	p->lXmin=MAXKOORD;
	p->lXmax=0L;
	p->lYmin=MAXKOORD;
	p->lYmax=0L;
	p->rPolyLen=0.0;
	p->rPolyLenMax=0.0;
	p->rPolyLenMin=MaxDouble;
	p->rPolyLenMedian=0.0;
	p->rPolyLenMittel=0.0;
	p->rAreaMax=0.0;
	p->rAreaMin=MaxDouble;
	p->rAreaMedian=0.0;
	p->rAreaMittel=0.0;
	p->rArea=0.0;
	p->lMCode = 0L;
	p->pObj = NULL;
}

//------------------------------------------------------------------
long CountObjectsFromStruct ( struct IDGITYP *p)
{

long Objects=0;

	if ( p == NULL ) return FALSE;
	Objects = p->lPoint + p->lLine + p->lArea + p->lText + p->lNoname;
	return Objects;
}
//--------------------------------------------------------------------------
//------------------------------------------------------------------
void KumulIdent ( struct IDGITYP *s , struct IDGITYP *p)
{
	if ( s == NULL || p == NULL ) return;

	s->lPoint = s->lPoint + p->lPoint;
	s->lLine = s->lLine + p->lLine;
	s->lArea = s->lArea + p->lArea;
	s->lText = s->lText + p->lText;
	s->lComplex = s->lComplex + p->lComplex;
	s->lNoname = s->lNoname + p->lNoname;
	s->iITyp = s->iITyp | p->iITyp;
	s->rArea = s->rArea + p->rArea;
	s->rPolyLen = s->rPolyLen + p->rPolyLen; 

//----------------Container----------------------------------

	if ( s->lYmin > p->lYmin ) 
		s->lYmin = p->lYmin;
	if ( s->lXmin >  p->lXmin ) 
		s->lXmin = p->lXmin;
	if ( s->lYmax < p->lYmax )
		s->lYmax = p->lYmax;
	if ( s->lXmax < p->lXmax )
		s->lXmax = p->lXmax;

	return ;
}
//---------------------------------------------------------------
short SearchObjectMCode ( short MFlag, OBJTree *pOBJ , struct IDGITYP *p )
{
	if ( pOBJ == NULL )
		return 0;
	CTable t ( *pOBJ );
	long MCode = p->lMCode;
	short Count = 0;
	IDGITYP Estr;

	for ( t.First(); t.Valid(); t.Next() ) {
		OBJLock l(t);
		long ONr = l->Object(); 
		l->MCode() = 0L;
		if ( ExistMCodeInObject ( MFlag, MCode, ONr )) {
			SetZero(&Estr);
			Estr.lMCode = p->lMCode;
			Estr.rArea =  l->FlInhalt();
			Estr.rPolyLen =  l->LinLaenge();
			Estr.rAreaMin =  l->FlInhalt();
			Estr.rPolyLenMin =  l->LinLaenge();
			Estr.rAreaMax =  l->FlInhalt();
			Estr.rPolyLenMax =  l->LinLaenge();
			l->MCode() = MCode;
			Count++;
			if ( l->ObjectTyp() == OTPunkt ||
				l->ObjectTyp() == OTLinie ||
				l->ObjectTyp() == OTFlaeche ||
				l->ObjectTyp() == OTText ) {

				if ( l->ObjectTyp() == OTPunkt )
					Estr.lPoint = 1;
				if ( l->ObjectTyp() == OTLinie ) 
					Estr.lLine = 1;
				if ( l->ObjectTyp() == OTFlaeche )
					Estr.lArea = 1;
				if ( l->ObjectTyp() == OTText )
					Estr.lText = 1;
			} else
				Estr.lNoname = 1;

			Estr.lYmin = l->RuHoch();
			Estr.lXmin = l->LoRechts();
			Estr.lYmax = l->LoHoch();
			Estr.lXmax = l->RuRechts();
			CumulateObjects( p ,&Estr);
		}
	}
	return Count;
}
//------------------------------------------------------------------------
//---------------------------------------------------------------
Bool SucheLeerZeichen ( char *pText )
{
	if ( !pText)
		return false;
	char *ptr = pText;
	while ( *ptr != NULL ) {
		if ( *ptr != ' ')
			return false;
		ptr++;
	}
	return true;
}
//------------------------------------------------------------------------
extern "C" {

//------------------------------------------------------
  Bool PASCAL _XTENSN_EXPORT SearchObjectsWithMK ( long ONr, short iObjTyp , void *pData)
  {
	if ( ONr <= 0L )
		return TRUE;
	struct IDGITYP *p = (( IDGIPOINT *)pData)->pIDGI;
	class IdentInformation  *pInfo = ((IDGIPOINT *)pData)->pStatus;

	((IDGIPOINT *)pData)->lRange++;
   	long lRange = ((IDGIPOINT *)pData)->lRange;

	if ( pInfo->Break() ) {
		((IDGIPOINT *)pData)->lCount = -1;
	   	return FALSE;
	}

	short MFlag = ((IDGIPOINT *)pData)->isMKode;

//	MKode nicht angegeben !!!
	if( p->lMCode == 0L )
		return TRUE;

//	GI-Typ nicht gefragt
	if ((iObjTyp & p->iITyp) == 0 )
		return TRUE;


	pInfo->SetPosition( (short)lRange );


//	Zulässigkeit MKode/ONr

TARGETMERKMAL TM;
	memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = ONr;
	long MKode =   p->lMCode;
	Bool Flag=FALSE;
	if ( !MFlag ) {
		Flag = TRUE;	// Inverses Merkmal
		MKode = -MKode;
	}
	TM.lMCode =MKode;
	TM.imaxLen = NULL;
	TM.iTTyp = TT_Objekt;
	TM.pMText = NULL;
	if ( Flag ) {		// Inverses Merkmal
	//	Merkmal da , dann nicht
		if ( DEX_GetTextMerkmal ( TM )) return TRUE;
	} else {
	//	Merkmal nicht gefunden , dann nicht
		if ( !DEX_GetTextMerkmal ( TM )) return TRUE;
	}

//	Bedingungen ONr - Merkmal erfüllt -> Typen sammeln


//	ON definiert ????

//---------------------------------------
	short Status = DEX_GetObjectStatus ( ONr );
	if ( Status != -1 && Status != OSNormal && Status != OSModified ) {
//		((IDGITYP *)pData)->iNoname++;
		p->lNoname++;
		return TRUE;
	}

OBJSTATISTIK OS;
	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr = ONr;

	if (!DEX_GetObjStatistik (OS)) {
//		((IDGITYP *)pData)->iNoname++;
		p->lNoname++;
		return TRUE;
	}
//	KomplexObjekte
	if (OS.iObjTyp == OT_KO ) {
//		((IDGITYP *)pData)->iComplex++;
//		((IDGITYP *)pData)->iNoname++;
		p->lComplex++;
		p->lNoname++;
		return TRUE;
	}

/*-------------------i.a. nicht n”tig -20.02.95-------------
	long* pObCont = ObjectContainer ( ONr, OS.iObjTyp );

	if ( pObCont ) {
		if( ((IDGITYP *)pData)->lXmin > *pObCont) 
			((IDGITYP *)pData)->lXmin=*pObCont;
		if( ((IDGITYP *)pData)->lXmax < *(pObCont+1))
			((IDGITYP *)pData)->lXmax=*(pObCont+1);
		if( ((IDGITYP *)pData)->lYmin > *(pObCont+2))
			((IDGITYP *)pData)->lYmin=*(pObCont+2);
		if ( ((IDGITYP *)pData)->lYmax < *(pObCont+3))
 			((IDGITYP *)pData)->lYmax=*(pObCont+3);
	}
	DELETE_OBJ ( pObCont );
------------------------------------------------------------------*/

	if ( OS.iObjTyp == OT_TEXT)  {
//		((IDGITYP *)pData)->iText++;
		p->lText++;
	}

	if (OS.iObjTyp == OT_PUNKT) {
//		((IDGITYP *)pData)->iPoint++;
		p->lPoint++;
	}
	if (OS.iObjTyp != OT_KANTE && OS.iObjTyp != OT_FLAECHE &&
	    OS.iObjTyp != OT_PUNKT && OS.iObjTyp != OT_TEXT ) {
//		((IDGITYP *)pData)->iNoname++;
		p->lNoname++;
	}

	if (OS.iObjTyp == OT_KANTE) {
//		((IDGITYP *)pData)->iLine++;
		p->lLine++;
	}

	if (OS.iObjTyp == OT_FLAECHE ) {
//		((IDGITYP *)pData)->iArea++;
		p->lArea++;
	}
	return TRUE;
  }

//----------------------------------------------------------------------
//------------------------------------------------------------------
Bool PASCAL _XTENSN_EXPORT FillMKListBox (long Mkode, Bool , void *pData)
{
PBDDATA pbdData;
char KText[MAXFCTNAME+1];
char outBuff[TEXTLEN+20];

	KText[0] = '\0';
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = Mkode;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	if ( DEX_GetPBDData (pbdData) == EC_OKAY ) {

		if ( KText[0] == NULL )
			strcat ( KText, ResString(ResID(IDS_NODEFMERKMAL,&g_pTE->RF()),70));
		KText[MAXFCTNAME] = '\0';
	} else {
		strcat ( KText, ResString(ResID(IDS_NODEFMERKMAL,&g_pTE->RF()),70));
		KText[MAXFCTNAME] = '\0';
	}
	if ( DEX_GetMkBase() == 16 )
		wsprintf (outBuff, "%08lx:%s", Mkode, KText);
	else
		wsprintf (outBuff, "%08ld:%s", Mkode, KText);

	((ListBox *)pData) -> AddString (outBuff);

	return TRUE;

}

Bool PASCAL _XTENSN_EXPORT FillIdOTypListBox (long Ident, DWORD Typ , void *pData)
{

	(* ( long * ) pData)++;
	(* ((long *)pData + *(long *)pData )) = Ident;
	(* ( long * ) pData)++;
	(* ((long *)pData + *(long *)pData )) = (long ) Typ;

	return TRUE;

}

Bool PASCAL _XTENSN_EXPORT GetIdentGiTyp (long Ident, DWORD Typ , void *pData)
{

	long Vgl =  *((long *)pData +1 );	// Ident
	if ( (ulong) Ident < (ulong) Vgl )
		return TRUE;
	if ( (ulong) Ident > (ulong) Vgl )
		return FALSE;

	(* ( long *) pData ) = (long)Typ;

	return FALSE;

}


} // extern "C"
