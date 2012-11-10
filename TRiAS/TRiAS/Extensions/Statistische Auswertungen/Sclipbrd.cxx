
// Ausgabe von RecherchInformationen auf CLIPBOARD -------------------
// File: SCLIPBRD.CXX

#include "statistp.hxx"
#include "geostat.h"
#include <igeometr.hxx>

#include "dirmath.h"

#include "objkey.hxx"
#include "idkey.hxx"
#include "classkey.hxx"
#include "sclipbrd.hxx"



// Konstruktor ----------------------------------------------------------------
GlobalObjClass :: GlobalObjClass ( ResourceFile *pResF, short MFlag, long MCode, void *pData, short Typ, unsigned short *pParam, short iIdTyp) 
{
	_MFlag = MFlag;
	_Typ = Typ;
	_pGICLA = NULL;
	_pIDM = NULL;
	_pObj = NULL;
	if ( Typ == OKlGeometrieTyp )
		_pGICLA = ( GICLATree *) pData;
	else
		_pIDM = ( IDMTree *) pData;

	_lMCode = MCode;
	_pParam = pParam;
	_iIdTyp = iIdTyp;
	_pResF = pResF;
//	Kumulativ
	_KeyNr = _Count = _PCount = _LCount = _FCount = _TCount = _SCount = 0L;
	_SMinL = _SMaxL = _SMinF = _SMaxF = _SLinLaenge = _SFlInhalt = 0.0;

//	Zahl der Eintraege
	_EintragP = _EintragL = _EintragF = _EintragT = _EintragS = 0; 
	_EintragFlaeche = _EintragLaenge = _EintragMinL = _EintragMinF = _EintragMaxL = _EintragMaxF = 0; 
	_EintragAML = _EintragAMF = _EintragMedL = _EintragMedF = 0; 

	_pText = new char [2*MAXRECORD];
	_rGlobalWert = 0.0;	
}

// Destruktor
GlobalObjClass :: ~GlobalObjClass (void) 
{
	DELETE_OBJ ( _pText );
}

//	‹berschrift liefern
char * GlobalObjClass ::  GetCaption ( void ) 
{
	if ( _pText == NULL )
		return NULL;

	*_pText = '\0';

	if ( _pParam == NULL)
		return NULL;

//	Parameteranalyse
	for ( int i = 0 ; i < (int) *_pParam; i++ ) {
 
		unsigned short resid = *(_pParam+i+1);
	         
	       switch (*(_pParam +i +1) ) {


		case IDS_CLIPCOUNTER:
		{
		if ( (_iIdTyp & OTPunkt) > 0 ) {
			strcat ( _pText, ResString ( ResID ( IDS_CLIPPUNKT,_pResF),30));
			strcat( _pText, "\t"); 
		}
		if ( (_iIdTyp & OTLinie) > 0 ) {
			strcat ( _pText, ResString ( ResID ( IDS_CLIPLINIE,_pResF),30));
			strcat( _pText, "\t"); 
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			strcat ( _pText, ResString ( ResID ( IDS_CLIPFLAECHE,_pResF),30));
			strcat( _pText, "\t"); 
		}
		if ( (_iIdTyp & OTText) > 0 ) {
			strcat ( _pText, ResString ( ResID ( IDS_CLIPTEXT,_pResF),30));
			strcat( _pText, "\t"); 
		}
		}
		break;

		case IDS_CLIPPROZENT:
		{
		if ( (_iIdTyp & OTLinie) > 0 ) {
			strcat ( _pText, ResString ( ResID ( resid,_pResF),30));
			strcat ( _pText, "\t");
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			strcat ( _pText, ResString ( ResID ( resid,_pResF),30));
			strcat ( _pText, "\t");
		}

		}
		break;

		case IDS_CLIPMAXIMUM:
		case IDS_CLIPMINIMUM:
		case IDS_CLIPMEDIANWERT:
		case IDS_CLIPARITHMITTEL:
		{
		if ( (_iIdTyp & OTLinie) > 0 ) {
			strcat ( _pText, ResString ( ResID ( resid,_pResF),30));
			strcat ( _pText, "-");
			strcat ( _pText, ResString ( ResID ( IDT_UNITKM,_pResF),30));
			strcat ( _pText, "\t");
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			strcat ( _pText, ResString ( ResID ( resid,_pResF),30));
			strcat ( _pText, "-");
			strcat ( _pText, ResString ( ResID ( IDT_UNITQKM,_pResF),30));
			strcat ( _pText, "\t");
		}
		}
		break;

		case IDS_CLIPFLAECHENGROESSE:
		{
		strcat ( _pText, ResString ( ResID ( resid,_pResF),30));
		strcat ( _pText, "-");
		strcat ( _pText, ResString ( ResID ( IDT_UNITQKM,_pResF),30));
		strcat ( _pText, "\t");
		}
		break;

		case IDS_CLIPLINIENLAENGE:
		{
		strcat ( _pText, ResString ( ResID ( resid,_pResF),30));
		strcat ( _pText, "-");
		strcat ( _pText, ResString ( ResID ( IDT_UNITKM,_pResF),30));
		strcat ( _pText, "\t");
		}
		break;

		default:
		{
		strcat ( _pText, ResString ( ResID ( resid,_pResF),30));
		strcat ( _pText, "\t");
		}
		break;


	       }	// SWITCH
	   } // FOR-Schleife

	char *ptr = strrchr ( _pText, '\t');
	if (ptr != NULL)
		*ptr = '\n';
	
	return _pText;
}

//	Zeileninformation liefern
char * GlobalObjClass :: GetText ( long Key , bool flag) 
{
//	flag = TRUE = Objektklasseneigenschaften ausgeben

	if ( _pText == NULL )
		return NULL;
	*_pText = '\0';

	if ( _pParam == NULL)
		return NULL;
	IDGITYP ID;
	SetZero ( &ID);
	ID.lMCode = _lMCode;
	if ( _Typ == OKlGeometrieTyp ) 
		GetGIValue( Key, &ID);
	else
		GetIDValue( Key, &ID);  

	short IdTyp = ID.iITyp;

	for ( int i = 0 ; i < (int) *_pParam; i++ ) {
	         
	       switch (*(_pParam +i +1) ) {

		case IDS_CLIPOBJCLASSSHORT :
		{
		// Eintrag = _KeyNr
		if ( flag ) {

		   char *pLText = new char [_MAX_PATH];
		   if ( pLText == NULL ) {
		   	break;
		   }
		   *pLText = '\0';
		   if ( _Typ == OKlGeometrieTyp ) {

			char *pBuffer1 = new char [_MAX_PATH];
			if ( pBuffer1 == NULL ) {
				DELETE_OBJ ( pLText);
			   	break;
			}
			*pBuffer1 = '\0';
			strcat ( pLText, " [");
			ST_DtoA (pBuffer1, "%10.3f", _VglWert1);
			strcat (pLText,pBuffer1);
			strcat ( pLText, " , ");
			ST_DtoA (pBuffer1, "%10.3f", _VglWert2);
			strcat (pLText,pBuffer1);
			strcat ( pLText, "]");
			DELETE_OBJ ( pBuffer1);
		   } else {
			PBDDATA pbdData;
			memset (&pbdData, '\0', sizeof(PBDDATA));
			pbdData.dwSize = sizeof(PBDDATA);
			pbdData.pbdTyp = 'i';
			pbdData.pbdCode = Key;
			pbdData.pbdLText = 0;
			pbdData.pbdKText = pLText;
			pbdData.pbdLTextLen = 0;
			pbdData.pbdKTextLen = MAXFCTNAME;
			DEX_GetPBDData (pbdData);
			*(pLText+MAXFCTNAME) = '\0';
		   }
		   strcat ( _pText, pLText );
		   strcat ( _pText, "\t");
		   DELETE_OBJ ( pLText);
		}
		}
		break;

		case IDS_CLIPOBJCLASSLONG :
		{
		// Eintrag = _KeyNr
		if ( flag ) {
			PBDDATA pbdData;
			char *pLText = new char [_MAX_PATH];
			if ( pLText == NULL ) {
				break;
			}
			*pLText = '\0';
			memset (&pbdData, '\0', sizeof(PBDDATA));
			pbdData.dwSize = sizeof(PBDDATA);
			pbdData.pbdTyp = 'i';
			pbdData.pbdCode = Key;
			pbdData.pbdLText = pLText;
			pbdData.pbdKText = 0;
			pbdData.pbdLTextLen = _MAX_PATH-1;
			pbdData.pbdKTextLen = 0;
			DEX_GetPBDData (pbdData);
			*(pLText+MAXFCTNAME) = '\0';
			strcat ( _pText, pLText );
			strcat ( _pText, "\t");
		}
		}
		break;

		case IDS_CLIPOBJCLASSKEY:
		{
		// Eintrag = _KeyNr
		if ( flag ) {
//			char *pBuf = new char [30];
			char *pBuf = new char [_MAX_PATH];
			if ( pBuf == NULL )
				break;

			char NewIdent[MAX_OKS_LENX+1];

			ClassFromIdentX ( Key, NewIdent);
	
			wsprintf (pBuf, "%s", NewIdent);


/*Korr 15.08.95 --------------ID hexadezimal ??? 
			if ( DEX_GetIdBase() == 16 )
				wsprintf (pBuf, "%08lx", Key);
			else
				wsprintf (pBuf, "%08ld", Key);
---------------*/

			strcat( _pText,pBuf);
			strcat( _pText, "\t"); 
			DELETE_OBJ ( pBuf);
		}
		}
		break;


		case IDS_CLIPCOUNTER:
		{
		_PCount = _PCount + ID.lPoint;
		_LCount = _LCount + ID.lLine;
		_FCount = _FCount + ID.lArea;
		_TCount = _TCount + ID.lText;
		// Eintr‰ge
		if ( ID.lPoint > 0L )
			_EintragP++;
		if ( ID.lLine > 0L )
			_EintragL++;
		if ( ID.lArea > 0L )
			_EintragF++;
		if ( ID.lText > 0L )
			_EintragT++;
		if ( ID.lNoname > 0L )
			_EintragS++;

		if ( flag ) {
//			char *pBuf = new char [30];
			char *pBuf = new char [_MAX_PATH];
			if ( pBuf == NULL )
				break;

			if ( ( _iIdTyp & OTPunkt) > 0 ) {
				strcat( _pText,ltoa (ID.lPoint,pBuf,10));
				strcat( _pText, "\t"); 
			}

			if ( (_iIdTyp & OTLinie )> 0 ) {
				strcat( _pText,ltoa (ID.lLine,pBuf,10));
				strcat( _pText, "\t"); 
			}
			if ( (_iIdTyp & OTFlaeche) > 0 ) {
				strcat( _pText,ltoa (ID.lArea,pBuf,10));
				strcat( _pText, "\t"); 
			}
			if ( (_iIdTyp & OTText) > 0 ) {
				strcat( _pText,ltoa (ID.lText,pBuf,10));
				strcat( _pText, "\t"); 
			}

			DELETE_OBJ ( pBuf);
		}
		}
		break;

		case IDS_CLIPFLAECHENGROESSE:
		{
//		char *pBuf = new char [30];
		char *pBuf = new char [_MAX_PATH];
		if ( pBuf == NULL )
			break;
		double FL = ID.rArea;
		if ( FL > 0.0 ) {
			_EintragFlaeche++;
			FL = FL/(double) QuadratKiloMeter;
			_SFlInhalt = _SFlInhalt + FL;
			if ( flag ) {
				*pBuf = '\0';
				ST_DtoA ( pBuf, "%8.3f", FL);
				strcat ( _pText,pBuf);
				strcat ( _pText, ResString ( ResID ( IDT_UNITQKM,_pResF),30));
			}
		}
		if ( flag )
			strcat( _pText, "\t"); 
		DELETE_OBJ ( pBuf);
		}
		break;

		case IDS_CLIPLINIENLAENGE:
		{
//		char *pBuf = new char [30];
		char *pBuf = new char [_MAX_PATH];
		if ( pBuf == NULL )
			break;
		double L = ID.rPolyLen;
		if ( L > 0.0 ) {
			_EintragLaenge++;
			L = L / (double) KiloMeter;
			_SLinLaenge = _SLinLaenge + L;
			if ( flag ) {
				*pBuf = '\0';
				ST_DtoA ( pBuf, "%8.3f", L);
				strcat ( _pText,pBuf);
				strcat ( _pText, ResString ( ResID ( IDT_UNITKM,_pResF),30));
			}
		}
		if ( flag )
			strcat ( _pText, "\t");
		DELETE_OBJ ( pBuf);
		}
		break;

		case IDS_CLIPMAXIMUM:
		{
//		char *pBuf = new char [30];
		char *pBuf = new char [_MAX_PATH];
		if ( pBuf == NULL )
			break;
		if ( (_iIdTyp & OTLinie) > 0 ) {
			double L = ID.rPolyLenMax;
			if ( L > 0.0 ){ 
				_EintragMaxL++;
				L = L / (double) KiloMeter;
				if ( L >_SMaxL)
					_SMaxL = L;
				if ( flag ) {
					*pBuf = '\0';
					ST_DtoA ( pBuf, "%8.3f", L);
					strcat ( _pText,pBuf);
					strcat ( _pText, ResString ( ResID ( IDT_UNITKM,_pResF),30));
				}
			}
			if ( flag )
				strcat ( _pText, "\t");
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			double F = ID.rAreaMax;
			if ( F > 0.0 ) {
				_EintragMaxF++;
				F = F / (double) QuadratKiloMeter;
				if ( F > _SMaxF)
					_SMaxF = F;
				if ( flag ) {
					*pBuf = '\0';
					ST_DtoA ( pBuf, "%8.3f", F);
					strcat ( _pText,pBuf);
					strcat ( _pText, ResString ( ResID ( IDT_UNITQKM,_pResF),30));
				}
			}
			if ( flag )
				strcat ( _pText, "\t");
		}
		DELETE_OBJ ( pBuf);
		}
		break;

		case IDS_CLIPMINIMUM:
		{
//		char *pBuf = new char [30];
		char *pBuf = new char [_MAX_PATH];
		if ( pBuf == NULL )
			break;
		if ( (_iIdTyp & OTLinie) > 0 ) {
		    double L = ID.rPolyLenMin;
		    if ( L != MaxDouble) {	
			_EintragMinL++;
			L = L / (double) KiloMeter;
			if ( _SMinL == 0.0)
				_SMinL = L;
			else {
				if ( _SMinL > L )
					_SMinL = L;
			}
			if ( flag ) {
				*pBuf = '\0';
				ST_DtoA ( pBuf, "%8.3f", L);
				strcat ( _pText,pBuf);
				strcat ( _pText, ResString ( ResID ( IDT_UNITKM,_pResF),30));
			}
		    }
		    if ( flag )
			    strcat ( _pText, "\t");
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
		    double F = ID.rAreaMin;
		    if ( F != MaxDouble) {
			_EintragMinF++;
			F = F / (double) QuadratKiloMeter;
			if ( _SMinF == 0.0)
				_SMinF = F;
			else {
				if ( _SMinF > F )
					_SMinF = F;
			}
			if ( flag ) {
				*pBuf = '\0';
				ST_DtoA ( pBuf, "%8.3f", F);
				strcat ( _pText,pBuf);
				strcat ( _pText, ResString ( ResID ( IDT_UNITQKM,_pResF),30));
			}
		    }
		    if ( flag )
			    strcat ( _pText, "\t");
		}
		DELETE_OBJ ( pBuf);
		}
		break;


		case IDS_CLIPMEDIANWERT:
		{
		if (( IdTyp & OTLinie ) > 0 )
			_EintragMedL++;
		if (( IdTyp & OTFlaeche ) > 0 )
			_EintragMedF++;

		if ( flag ) {
		  if ( (( IdTyp & OTLinie) > 0 ) || ( ( IdTyp & OTFlaeche) > 0 )) {
		     double *pMWert = new double[2];
		     if ( _pObj != NULL ) {
//			char *pBuf = new char [30];
			char *pBuf = new char [_MAX_PATH];
			if ( pBuf == NULL )
				break;
			ulong Count = _pObj->Count();
			long OCount = (long) Count;
//	MedianWert bzw. Arithm. Mittel kann schon im Feld stehen !
			if ( ID.rAreaMedian > 0.0 && ID.rPolyLenMedian > 0.0 && _lMCode == 0L) {
				*pMWert = ID.rAreaMedian;
				*(pMWert+1) = ID.rPolyLenMedian;
			} else 
				pMWert = MedianWertBestimmung ( Count, _pObj, &_lMCode);
			if ( (_iIdTyp & OTLinie) > 0 ) {
				*pBuf = '\0';
				double L = *(pMWert+1);
				if ( L != -1.0 ) {
					L = L / (double) KiloMeter;
					ST_DtoA ( pBuf, "%8.3f", L);
					strcat ( _pText,pBuf);
					strcat ( _pText, ResString ( ResID ( IDT_UNITKM,_pResF),30));
				}
				strcat ( _pText, "\t");
			}
			if ( (_iIdTyp & OTFlaeche) > 0 ) {
				*pBuf = '\0';
				double L = *pMWert;
				if ( L != -1.0 ) {
					L = L / (double) QuadratKiloMeter;
					ST_DtoA ( pBuf, "%8.3f", L);
					strcat ( _pText,pBuf);
					strcat ( _pText, ResString ( ResID ( IDT_UNITQKM,_pResF),30));
				}
				strcat ( _pText, "\t");
			}
			DELETE_OBJ ( pBuf);
			DELETE_OBJ ( pMWert);
		     }
		  } else {
			if ( (_iIdTyp & OTLinie) > 0 )
				strcat ( _pText, "\t");
			if ( (_iIdTyp & OTFlaeche) > 0 ) 
				strcat ( _pText, "\t");
		  }

		}	// flag

		}
		break;

		case IDS_CLIPARITHMITTEL:
		{
		if (( IdTyp & OTLinie ) > 0 )
			_EintragAML++;
		if (( IdTyp & OTFlaeche ) > 0 )
			_EintragAMF++;

		if ( flag ) {
		  if ( (( IdTyp & OTLinie) > 0 ) || ( ( IdTyp & OTFlaeche) > 0 )) {
		     double *pMWert = new double[2];
		     if ( _pObj != NULL ) {
//			char *pBuf = new char [30];
			char *pBuf = new char [_MAX_PATH];
			if ( pBuf == NULL )
				break;
			if ( ID.rAreaMittel > 0.0 && ID.rPolyLenMittel > 0 && _lMCode == 0L ) {
				*pMWert = ID.rAreaMittel;
				*(pMWert+1) = ID.rPolyLenMittel;
			} else
				pMWert = MittelWertBerechnung ( _pObj, &_lMCode);
			if ( (_iIdTyp & OTLinie) > 0 ) {
				*pBuf = '\0';
				double L = *(pMWert+1);
				if ( L != -1.0 ) {
					L = L / (double) KiloMeter;
					ST_DtoA ( pBuf, "%8.3f", L);
					strcat ( _pText,pBuf);
					strcat ( _pText, ResString ( ResID ( IDT_UNITKM,_pResF),30));
				}
				strcat ( _pText, "\t");
			}
			if ( (_iIdTyp & OTFlaeche) > 0 ) {
				*pBuf = '\0';
				double L = *pMWert;
				if ( L != -1.0 ) {
					L = L / (double) QuadratKiloMeter;
					ST_DtoA ( pBuf, "%8.3f", L);
					strcat ( _pText,pBuf);
					strcat ( _pText, ResString ( ResID ( IDT_UNITQKM,_pResF),30));
				}
				strcat ( _pText, "\t");
			}
			DELETE_OBJ ( pBuf);
			DELETE_OBJ ( pMWert);
		     }
		  } else {
			if ( (_iIdTyp & OTLinie) > 0 )
				strcat ( _pText, "\t");
			if ( (_iIdTyp & OTFlaeche) > 0 ) 
				strcat ( _pText, "\t");
		  }

		}	// flag
		}
		break;
///////////////////////////////////////////////////////////////////////////
// Prozentualer Anteil
///////////////////////////////////////////////////////////////////////////

		case IDS_CLIPPROZENT:
		{
		if ( 0.0 ==_rGlobalWert )
			break;
//		char *pBuf = new char [30];
		char *pBuf = new char [_MAX_PATH];
		if ( pBuf == NULL )
			break;
		
		if ( (_iIdTyp & OTLinie) > 0 ) {
			double L = ID.rPolyLen;
			if ( L > 0.0 ){ 
				if ( flag ) {
					double rWert = L/_rGlobalWert;
					rWert = rWert * 100.0;
					*pBuf = '\0';
					ST_DtoA ( pBuf, "%8.3f", rWert);
					strcat ( _pText,pBuf);
				}
			}
			if ( flag )
				strcat ( _pText, "\t");
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			double F = ID.rArea;
			if ( F > 0.0 ) {
				if ( flag ) {
					double rWert = F/_rGlobalWert;
					rWert = rWert * 100.0;
					*pBuf = '\0';
					ST_DtoA ( pBuf, "%8.3f", rWert);
					strcat ( _pText,pBuf);
				}
			}
			if ( flag )
				strcat ( _pText, "\t");
		}
		DELETE_OBJ ( pBuf);
		}
		break;

///////////////////////////////////////////////////////////////////////////
	       }	// SWITCH
	} // FOR-Schleife

	if ( flag ) {
	        char *ptr = strrchr ( _pText,'\t');
	        if ( ptr != NULL)
			*ptr = '\n';
	}
	return _pText; 

}
///////////////////////////////////////////////////////////////////////
void GlobalObjClass :: SetGlobalWert (double rWert) 
{
	_rGlobalWert = 0.0;
	if ( 0.0 < rWert )
		_rGlobalWert = rWert;
	
}
//----------------------------------------------------------------------
void GlobalObjClass :: GetIDValue (long Key, IDGITYP *p) 
{

	if ( _pIDM == NULL )
		return;

	CTable t(*_pIDM);

	if ( t.Find (&Key) ) {
	  IDMLock l(t);
	  p->iITyp = l->IdentGiTyp();
	  long MKode = l->MCode();
	  _pObj = l->pObjects();
	  if ( _lMCode == MKode ) { 
		   _KeyNr++;
		   p->lMCode = _lMCode;
		   if ( _lMCode != 0L ) {
			if ( _pObj != NULL )
				short Count = SearchObjectMCode ( _MFlag, _pObj, p);
		   } else {
			p->lPoint = l->Punkt();
			p->lLine = l->Linie();
			p->lArea = l->Flaeche();
			p->lText = l->Text();
			p->lNoname = l->Sonstige();
			p->rPolyLen = l->LinLaenge();
			p->rPolyLenMin = l->rPolyLenMin();
			p->rPolyLenMax = l->rPolyLenMax();
			p->rArea = l->FlInhalt();
			p->rAreaMin = l->rAreaMin();
			p->rAreaMax = l->rAreaMax();
		}
	   }
	}
	return;
}

//----------------------------------------------------------------------
void GlobalObjClass :: GetGIValue (long Key,IDGITYP *p) 
{
	if ( _pGICLA == NULL ) return;

	CTable t(*_pGICLA);

	if ( t.Find (&Key) ) {
	  GICLALock l(t);
	  p->iITyp = l->GiTyp();
	  long MKode = l->MCode();
	  _VglWert1 = l->VglWert1();
	  _VglWert2 = l->VglWert2();
	  _pObj = l->pObjects();
	  if ( _lMCode == MKode ) { 
		   _KeyNr++;
		   p->lMCode = _lMCode;
		   if ( _lMCode != 0L ) {
			if ( _pObj != NULL )
				short Count = SearchObjectMCode ( _MFlag, _pObj, p);
		   } else {
			if ( p->iITyp == OTLinie ) {
				p->lLine = l->Count();
				p->rPolyLen = l->Kumul()*(double)l->Einheit();
				p->rPolyLenMin = l->KumulMin()*(double)l->Einheit();
				p->rPolyLenMax = l->KumulMax()*(double)l->Einheit();
			
			} else {
				p->lArea = l->Count();
				p->rArea = l->Kumul()*(double)l->Einheit();
				p->rAreaMin = l->KumulMin()*(double)l->Einheit();
				p->rAreaMax = l->KumulMax()*(double)l->Einheit();
			}
		}
	   }
	}
	return;
}

//----------------------------------------------------------------------
//	Abschluﬂ liefern
char * GlobalObjClass :: GetCumulate ( void ) 
{
	if ( _pText == NULL )
		return NULL;
	*_pText = '\0';

	if ( _pParam == NULL)
		return NULL;

char * pBuf = new char [_MAX_PATH];
	if ( pBuf == NULL )
		return NULL;
	*pBuf = '\0';

	_Count = _PCount + _LCount + _FCount + _TCount + _SCount;


//	Parameteranalyse
	for ( int i = 0 ; i < (int) *_pParam; i++ ) {
	         
	       switch (*(_pParam +i +1) ) {


		case IDS_CLIPCOUNTER:
		{
		if ( (_iIdTyp & OTPunkt) > 0 ) {
			strcat( _pText,ltoa (_PCount,pBuf,10));
			strcat( _pText, "\t"); 
		}
		if ( (_iIdTyp & OTLinie) > 0 ) {
			strcat( _pText,ltoa (_LCount,pBuf,10));
			strcat( _pText, "\t"); 
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			strcat( _pText,ltoa (_FCount,pBuf,10));
			strcat( _pText, "\t"); 
		}
		if ( (_iIdTyp & OTText) > 0 ) {
			strcat( _pText,ltoa (_TCount,pBuf,10));
			strcat( _pText, "\t"); 
		}
		}
		break;

		case IDS_CLIPMAXIMUM:
		{
		if ( (_iIdTyp & OTLinie) > 0 ) {
			*pBuf = '\0';
			ST_DtoA ( pBuf, "%8.3f", _SMaxL);
			strcat ( _pText , pBuf );
			strcat ( _pText, ResString ( ResID ( IDT_UNITKM,_pResF),30));
			strcat ( _pText , "\t" );
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			*pBuf = '\0';
			ST_DtoA ( pBuf, "%8.3f", _SMaxF);
			strcat ( _pText , pBuf );
			strcat ( _pText, ResString ( ResID ( IDT_UNITQKM,_pResF),30));
			strcat ( _pText , "\t" );
		}
		}
		break;


		case IDS_CLIPMINIMUM:
		{
		if ( (_iIdTyp & OTLinie) > 0 ) {
			*pBuf = '\0';
			ST_DtoA ( pBuf, "%8.3f", _SMinL);
			strcat ( _pText , pBuf );
			strcat ( _pText, ResString ( ResID ( IDT_UNITKM,_pResF),30));
			strcat ( _pText , "\t" );
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			*pBuf = '\0';
			ST_DtoA ( pBuf, "%8.3f", _SMinF);
			strcat ( _pText , pBuf );
			strcat ( _pText, ResString ( ResID ( IDT_UNITQKM,_pResF),30));
			strcat ( _pText , "\t" );
		}
		}
		break;


		case IDS_CLIPMEDIANWERT:
		{
		if ( (_iIdTyp & OTLinie) > 0 ) {
			strcat ( _pText, "\t");
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			strcat ( _pText, "\t");
		}
		}
		break;

		case IDS_CLIPARITHMITTEL:
		{
		if ( (_iIdTyp & OTLinie) > 0 ) {
			strcat ( _pText, "\t");
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			strcat ( _pText, "\t");
		}
		}
		break;


		case IDS_CLIPFLAECHENGROESSE:
		{
		*pBuf = '\0';
		ST_DtoA ( pBuf, "%8.3f", _SFlInhalt);
		strcat ( _pText,pBuf);
		strcat ( _pText, ResString ( ResID ( IDT_UNITQKM,_pResF),30));
		strcat( _pText, "\t"); 
		}
		break;

		case IDS_CLIPLINIENLAENGE:
		{
		*pBuf = '\0';
		ST_DtoA ( pBuf, "%8.3f", _SLinLaenge);
		strcat ( _pText,pBuf);
		strcat ( _pText, ResString ( ResID ( IDT_UNITKM,_pResF),30));
		strcat ( _pText, "\t");
		}
		break;

		default:
		{
		strcat( _pText,ltoa (_KeyNr,pBuf,10));
		strcat ( _pText, "\t");
		}
		break;


	       }	// SWITCH
	   } // FOR-Schleife

        char *ptr = strrchr ( _pText,'\t');
        if ( ptr != NULL)
		*ptr = '\r';
	strcat ( _pText , "\n" );

	DELETE_OBJ ( pBuf );
	return _pText;
}

//	Abschluﬂ Eintraege liefern
char * GlobalObjClass :: GetEintrag ( void ) 
{
	if ( _pText == NULL )
		return NULL;
	*_pText = '\0';

	if ( _pParam == NULL)
		return NULL;

char * pBuf = new char [_MAX_PATH];
	if ( pBuf == NULL )
		return NULL;
	*pBuf = '\0';

//	Parameteranalyse
	for ( int i = 0 ; i < (int) *_pParam; i++ ) {
	         
	       switch (*(_pParam +i +1) ) {


		case IDS_CLIPCOUNTER:
		{
		if ( (_iIdTyp & OTPunkt) > 0 ) {
			strcat( _pText,ltoa (_EintragP,pBuf,10));
			strcat( _pText, "\t"); 
		}
		if ( (_iIdTyp & OTLinie) > 0 ) {
			strcat( _pText,ltoa (_EintragL,pBuf,10));
			strcat( _pText, "\t"); 
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			strcat( _pText,ltoa (_EintragF,pBuf,10));
			strcat( _pText, "\t"); 
		}
		if ( (_iIdTyp & OTText) > 0 ) {
			strcat( _pText,ltoa (_EintragT,pBuf,10));
			strcat( _pText, "\t"); 
		}
		}
		break;

		case IDS_CLIPMAXIMUM:
		{
		if ( (_iIdTyp & OTLinie) > 0 ) {
			strcat( _pText,ltoa (_EintragMaxL,pBuf,10));
			strcat ( _pText , "\t" );
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			strcat( _pText,ltoa (_EintragMaxF,pBuf,10));
			strcat ( _pText , "\t" );
		}
		}
		break;


		case IDS_CLIPMINIMUM:
		{
		if ( (_iIdTyp & OTLinie) > 0 ) {
			strcat( _pText,ltoa (_EintragMinL,pBuf,10));
			strcat ( _pText , "\t" );
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			strcat( _pText,ltoa (_EintragMinF,pBuf,10));
			strcat ( _pText , "\t" );
		}
		}
		break;


		case IDS_CLIPMEDIANWERT:
		{
		if ( (_iIdTyp & OTLinie) > 0 ) {
			strcat( _pText,ltoa (_EintragMedL,pBuf,10));
			strcat ( _pText, "\t");
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			strcat( _pText,ltoa (_EintragMedF,pBuf,10));
			strcat ( _pText, "\t");
		}
		}
		break;

		case IDS_CLIPARITHMITTEL:
		{
		if ( (_iIdTyp & OTLinie) > 0 ) {
			strcat( _pText,ltoa (_EintragAML,pBuf,10));
			strcat ( _pText, "\t");
		}
		if ( (_iIdTyp & OTFlaeche) > 0 ) {
			strcat( _pText,ltoa (_EintragAMF,pBuf,10));
			strcat ( _pText, "\t");
		}
		}
		break;


		case IDS_CLIPFLAECHENGROESSE:
		{
		strcat( _pText,ltoa (_EintragFlaeche,pBuf,10));
		strcat( _pText, "\t"); 
		}
		break;

		case IDS_CLIPLINIENLAENGE:
		{
		strcat( _pText,ltoa (_EintragLaenge,pBuf,10));
		strcat ( _pText, "\t");
		}
		break;

		default:
		{
		strcat( _pText,ltoa (_KeyNr,pBuf,10));
		strcat ( _pText, "\t");
		}
		break;


	       }	// SWITCH
	   } // FOR-Schleife

        char *ptr = strrchr ( _pText,'\t');
        if ( ptr != NULL)
		*ptr = '\r';
	strcat ( _pText , "\n" );

	DELETE_OBJ ( pBuf );
	return _pText;
}
//--------Dialogfenster zum Zusammenstellen von Parametern ---------
//-------------------------------------------------------------------
//-------------Bereitstellen von Parametern fÅr die Zwischenablage----------------
// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

ClipBoardClass :: ClipBoardClass (pWindow pW, uint res, ResourceFile &RF , short Typ, unsigned short *pParam) 
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _ObjClassList (this, IDLB_CLIPPARMLISTE),
	       _RF (RF),
	       _ReihenFolge (this, IDB_CLIPREIHENFOLGE),
	       CancelButton ( this, IDCANCEL),
	       OKButton ( this, IDOK),
	       _Ueberschrift (this, IDC_CLIPUEBERSCHRIFT),
	       _OKLEigenschaft (this, IDC_CLIPOKLEIGENSCH),
	       _KumulIndex (this, IDC_CLIPKUMULATIV),
	       _AnzahlEintrag (this, IDC_CLIPCOUNTEINTRAG)
{
	if ( pParam == NULL)
		return;

	_pHelpText = NULL;
	_pHelpText = CHelpTextX :: CreateInstance (this, IDS_CLIPBESCHREIBUNG);
	if (_pHelpText == NULL)
		return;
	_pIndex = NULL;
	_pSelIndex = NULL;
	_pResParm = NULL;
	_pResHelp = NULL;
	_CountParm = MaxParam; 
	_pParam = pParam;
	_pIndex = new int [_CountParm];
	_pResParm = new unsigned short [_CountParm];
	_pResHelp = new unsigned short [_CountParm];
	_Typ = Typ;

	if ( _pIndex == NULL || _pResParm == NULL || _pResHelp == NULL ) {
		DELETE_OBJ ( _pIndex);
		DELETE_OBJ ( _pResParm);
		DELETE_OBJ ( _pResHelp);
		return;
	}
	CEierUhr Wait ( pW );
	OKButton.Disable();
//--------------Startbedingungen---------------------------------------
	_pW = pW;
//	pW->Disable();

//-------------ObjektklassenListe f¸llen------------
	FillParameterList ();
	_ReihenFolge.Disable();
       _Ueberschrift.SetChecked(TRUE);
       _OKLEigenschaft.SetChecked(TRUE);
       _KumulIndex.SetChecked(TRUE);
       _AnzahlEintrag.SetChecked(TRUE);

	return;
}

#pragma warning (default: 4355)


ClipBoardClass :: ~ClipBoardClass (void)
{
//	_pW->Enable();
	DELETE_OBJ (_pHelpText);
	DELETE_OBJ ( _pIndex);
	DELETE_OBJ ( _pSelIndex);
	DELETE_OBJ ( _pResParm);
	DELETE_OBJ ( _pResHelp);
}
//---------------------------------------------------------
void _XTENSN_EXPORT ClipBoardClass :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_CLIPPARMLISTE:
		{
		CEierUhr Wait(_pW);
		OKButton.Enable();
		ParameterAuswahl();
		}
		break;

	}
}

//---------------------------------------------
void _XTENSN_EXPORT ClipBoardClass :: ListBoxClk (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_CLIPPARMLISTE:
		{
		CEierUhr Wait(_pW);
		OKButton.Enable();
		ParameterAuswahl();
		}
		break;
	}

}

//-----------------------------------------------------------------
void _XTENSN_EXPORT ClipBoardClass :: ButtonClick (ControlEvt e)
{

	switch ((unsigned int)e.GetControlID()) {

	case IDCANCEL:
		EndDlg (0);
		break;
	case IDOK:
		{
		EndDlg ( 1);
		for ( short i = 0; i < _CountSel; i++ ) 
			*(_pParam+i+1) = *(_pResParm + (*(_pSelIndex+i)));
		*_pParam = (unsigned short) _CountSel;
		}
		break;

	case IDB_CLIPREIHENFOLGE:
		{
		CEierUhr Wait(_pW);
		ParameterSort PAS ( this, PARAMETERSORT, _RF, _CountSel, _pSelIndex, _pResParm); 
		PAS.Show();
		if ( PAS.Result()== 1) {		//OK
			for ( short i = 0; i < _CountSel; i++ ) 
				*(_pParam+i+1) = *(_pResParm + (*(_pSelIndex+i)));
			*_pParam = (unsigned short) _CountSel;
		}
		}
		break;

	case IDC_CLIPOKLEIGENSCH:
		{
		if ( _OKLEigenschaft.isChecked() )
			_OKLEigenschaft.SetChecked(TRUE);
		else
			_OKLEigenschaft.SetChecked(FALSE);
		}
		break;

	case IDC_CLIPCOUNTEINTRAG:
		{
		if ( _AnzahlEintrag.isChecked())
			_AnzahlEintrag.SetChecked(TRUE);
		else
			_AnzahlEintrag.SetChecked(FALSE);
		}
		break;

	case IDC_CLIPUEBERSCHRIFT:
		{
		if ( _Ueberschrift.isChecked() )
			_Ueberschrift.SetChecked(TRUE);
		else
			_Ueberschrift.SetChecked(FALSE);
		}
		break;

	case IDC_CLIPKUMULATIV:
		{
		if ( _KumulIndex.isChecked() )
			_KumulIndex.SetChecked(TRUE);
		else
			_KumulIndex.SetChecked(FALSE);
		}
		break;

	}
}
//---------------------------------------------------------
void ClipBoardClass :: FillParameterList ( void )
{   
	_CountParm  = 0;
// Startbedingungen
	if ( _Typ == OKlGeometrieTyp ) {
		StoreParameter(IDS_CLIPFLAECHENGROESSE, IDH_CLIPFLAECHENGROESSE );
		StoreParameter(IDS_CLIPARITHMITTEL, IDH_CLIPARITHMITTEL);
		StoreParameter(IDS_CLIPLINIENLAENGE, IDH_CLIPLINIENLAENGE);
		StoreParameter(IDS_CLIPMAXIMUM, IDH_CLIPMAXIMUM);
		StoreParameter(IDS_CLIPMEDIANWERT, IDH_CLIPMEDIANWERT);
		StoreParameter(IDS_CLIPMINIMUM, IDH_CLIPMINIMUM);
		StoreParameter(IDS_CLIPOBJCLASSSHORT, IDH_CLIPOBJCLASSSHORT);
		StoreParameter(IDS_CLIPCOUNTER, IDH_CLIPCOUNTER);
	} else {
		StoreParameter(IDS_CLIPFLAECHENGROESSE, IDH_CLIPFLAECHENGROESSE );
		StoreParameter(IDS_CLIPARITHMITTEL, IDH_CLIPARITHMITTEL);
		StoreParameter(IDS_CLIPLINIENLAENGE, IDH_CLIPLINIENLAENGE);
		StoreParameter(IDS_CLIPMAXIMUM, IDH_CLIPMAXIMUM);
		StoreParameter(IDS_CLIPMEDIANWERT, IDH_CLIPMEDIANWERT);
		StoreParameter(IDS_CLIPMINIMUM, IDH_CLIPMINIMUM);
		StoreParameter(IDS_CLIPOBJCLASSSHORT, IDH_CLIPOBJCLASSSHORT);
		StoreParameter(IDS_CLIPOBJCLASSLONG, IDH_CLIPOBJCLASSLONG);
		StoreParameter(IDS_CLIPOBJCLASSKEY, IDH_CLIPOBJCLASSKEY);
		StoreParameter(IDS_CLIPCOUNTER, IDH_CLIPCOUNTER);
	}
	if ( _Typ == OKlDataBase ) {
		StoreParameter(IDS_CLIPPROZENT, IDH_CLIPPROZENT );
	}
	return;
}
//------------------------------------------------------------
void ClipBoardClass :: StoreParameter ( unsigned short IDS, unsigned short IDH )
{

char * pBuffer = new char [_MAX_PATH];
	if ( pBuffer == NULL )
		return;

	*pBuffer = '\0';
	strcat (pBuffer, ResString (ResID (IDS, &_RF), 30));
	int Number = _ObjClassList.AddString (pBuffer );

	if ( Number < _CountParm) {
		for ( short i = _CountParm + 1 ; i > (short)Number; i-- ) {
			*(_pIndex+i) = (int) i;
			*(_pResParm+i) = *(_pResParm+i-1);
			*(_pResHelp+i) = *(_pResHelp+i-1);
		}
	}
	*(_pIndex+Number) = (int) Number;
	*(_pResParm+Number) =  IDS;
	*(_pResHelp+Number) = IDH;
			
	_CountParm++;
	return;
}
//----------------------------------------------------------

void ClipBoardClass :: ParameterAuswahl ( void )
{

int iIndex = _ObjClassList.GetFirstSelected();

	if (iIndex == -1 ) 
		return;

unsigned short resId = 0;
	_pSelIndex = new int [_CountParm];
	if ( _pSelIndex == NULL)
		return;
	_CountSel = 0;
	if ( iIndex != -1 ) {         
		_ReihenFolge.Disable();
		resId = *(_pResHelp + iIndex );
		_pHelpText -> SetHelpText (ResID(resId,&_RF));
		*(_pSelIndex+_CountSel) = iIndex;
		_CountSel++;
		iIndex=_ObjClassList.GetNextSelected ();
		while ( iIndex != -1 ) {
			_ReihenFolge.Enable();
			resId = *(_pResHelp + iIndex );
			_pHelpText -> SetHelpText (ResID(resId,&_RF));
			*(_pSelIndex+_CountSel) = iIndex;
			_CountSel++;
			iIndex=_ObjClassList.GetNextSelected ();
		}
	}	

	return;
}
//----------------------------------------------------------------------------
//-------------Sortieren der Reihenfolge von Parametern fÅr die Zwischenablage----------------
// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

ParameterSort :: ParameterSort (pWindow pW, uint res, ResourceFile &RF, short Count, int *pSelIndex, unsigned short *pResParm ) 
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _ParmList (this, IDLB_CLIPSORTPARMCLASS),
	       _RF (RF),
	       CancelButton ( this, IDCANCEL),
	       OKButton ( this, IDOK),
	       _Plus (this, IDB_CLIPSORTPLUS),
	       _Minus (this, IDB_CLIPSORTMINUS),
	       _Hilfe (this, IDB_CLIPSORTHILFE)
{

	CEierUhr Wait ( pW );
//--------------Startbedingungen---------------------------------------
	_pW = pW;
//	pW->Disable();
	_Count = Count;
	_pSelIndex = pSelIndex;
	_pResParm = pResParm;
//-------------ParameterListe f¸llen------------
	FillParameterList ();
	return;
}

#pragma warning (default: 4355)


ParameterSort :: ~ParameterSort (void)
{
//	_pW->Enable();
}
//---------------------------------------------------------
//---------------------------------------------------------
void _XTENSN_EXPORT ParameterSort :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_CLIPSORTPARMCLASS:
		{
		_iParmIndex = _ParmList.GetCurrentIndex();
		}
		break;

	}
}

//---------------------------------------------
void _XTENSN_EXPORT ParameterSort :: ListBoxClk (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_CLIPSORTPARMCLASS:
		{
		_iParmIndex = _ParmList.GetCurrentIndex();
		}
		break;
	}

}

//-----------------------------------------------------------------
void _XTENSN_EXPORT ParameterSort :: ButtonClick (ControlEvt e)
{

	switch ((unsigned int)e.GetControlID()) {

	case IDCANCEL:
		EndDlg (0);
		break;
	case IDOK:
		EndDlg ( 1);
		break;

	case IDB_CLIPSORTPLUS:
		{
		if ( _iParmIndex > 0 )
			SortPosition (true);
		}
		break;

	case IDB_CLIPSORTMINUS:
		{
		if ( _iParmIndex < _Count -1 )
			SortPosition(false);
		}
		break;
	case IDB_CLIPSORTHILFE:
		{
		}
		break;
	}
}
//---------------------------------------------------------

void ParameterSort :: FillParameterList ( void )
{
char * pBuffer = new char [_MAX_PATH];
	if ( pBuffer == NULL )
		return;
unsigned short resId = 0;
int Number = 0;
	for ( short i = 0; i < _Count; i++ ) {
		*pBuffer = '\0';
		Number = *(_pSelIndex+i );
		resId = *(_pResParm+Number);
		strcat (pBuffer, ResString (ResID(resId,&_RF), 30));
		_ParmList.AddString (pBuffer );
		
	}
	DELETE_OBJ ( pBuffer);
	return;
}
//---------------------------------------------------------
void ParameterSort :: SortPosition ( bool flag )
{
int Ref;
	if ( flag ) {		// Plus
		Ref = *(_pSelIndex + _iParmIndex);
		*(_pSelIndex + _iParmIndex ) = *(_pSelIndex + _iParmIndex - 1);
		*(_pSelIndex + _iParmIndex - 1) = Ref;
		_iParmIndex--;
	} else {		// Minus
		Ref = *(_pSelIndex + _iParmIndex);
		*(_pSelIndex + _iParmIndex ) = *(_pSelIndex + _iParmIndex + 1);
		*(_pSelIndex + _iParmIndex + 1) = Ref;
		_iParmIndex++;
	}
	
	_ParmList.Clear();
	FillParameterList();
	_ParmList.ChangeCurrentIndex( _iParmIndex);
	return;
}

//----------------------------------------------------------------------------
//	Ende SCLIPBOARD.CXX
