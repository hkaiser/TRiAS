// Berechnung diverser Objekteigenschaften ------------------------------------
// File: OBJPROP.CXX

#include "statistp.hxx"
#include "geostat.h"

#include <igeometr.hxx>

#include "objgguid.h"	// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie
#include <trelguid.h>

#include "dirmath.h"

#include <triashelper.h>

#include <oleguid.h>
#include <dirisole.h>
#include <eonrguid.h>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include "about.hxx"
#include "trfkoord.hxx"
#include "trfvect.hxx"
#include "idkey.hxx"
#include "objkey.hxx"
#include "classkey.hxx"
#include "stohwnd.hxx"
#include "dbinfo.hxx"
#include "geostat.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Definitionen
// ObjektPropertyFunktionen ---------------------------------------------------

#if !defined(WIN32)
#pragma function (memcpy)		// immer HUGE-Variante benutzen
static char s_cbBuffer[2048];		// ZeichenKettenBuffer f¸r OProps
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(InitObjektGeometrie);		// WInitObjektGeometrie
DefineSmartInterface(ObjektGeometrie);			// WObjektGeometries

//--------------------------------------------------------------------------
extern "C" char * _XTENSN_EXPORT PASCAL OPFlaechenInhalt (long lONr, char *pBuffer, short iLen, DWORD pExt)
{
static long lCnt = 0;			// Fl‰chenObjekte
static double dFullArea = 0.0;	// GesamtFl‰cheninhalt
double dFL;

	if (lONr == OBJPROP_RESET) {		// R¸cksetzen der akumulierten Werte
		lCnt = 0L;
		dFullArea = 0.0;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
	// GesamtAnzahl ausgeben
		StatistExtension *pMyTE = (StatistExtension *)pExt;
		DWORD dFLM = pMyTE->FLM();

#if defined(WIN32)
		ST_DtoA (pBuffer, "%9.4f", dFullArea);
		strcat (pBuffer, " ");

		if ( dFLM == FLM_QuadratKiloMeter)
			strcat (pBuffer, ResString (ResID (IDT_UNITQKM, &g_pTE -> RF()), 10));
		if ( dFLM == FLM_Default)
			strcat (pBuffer, ResString (ResID (IDT_UNITQKM, &g_pTE -> RF()), 10));
		if ( dFLM == FLM_Hektar)
			strcat (pBuffer, ResString (ResID (IDT_UNITHA, &g_pTE -> RF()), 10));
		if ( dFLM == FLM_QuadratMeter)
			strcat (pBuffer, ResString (ResID (IDT_UNITQM, &g_pTE -> RF()), 10));
#else
		ST_DtoA (s_cbBuffer, "%9.4f", dFullArea);

		strcat (s_cbBuffer, " ");

		if ( dFLM == FLM_Default )
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITQKM, &g_pTE -> RF()), 10));
		if ( dFLM == FLM_QuadratKiloMeter )
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITQKM, &g_pTE -> RF()), 10));
		if ( dFLM == FLM_Hektar )
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITHA, &g_pTE -> RF()), 10));
		if ( dFLM == FLM_QuadratMeter )
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITQM, &g_pTE -> RF()), 10));

		memcpy (pBuffer, s_cbBuffer, strlen(s_cbBuffer)+1);
#endif
		return pBuffer;	
	} else if (lONr == OBJPROP_COUNT) {

#if defined(WIN32)
		ltoa (lCnt, pBuffer, 10);
#else
		ltoa (lCnt, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
	        return pBuffer;

	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDH_HELPAREA, &g_pTE -> RF()), MAXSTRING);
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;

//	} else if (lONr > 0) {
	} else if (lONr != 0L) {
		TX_ASSERT(NULL != pBuffer);
		short iOTyp = DEX_GetObjectType (lONr);

		*pBuffer = '\0';

		if (iOTyp != OGFlaeche && iOTyp != OGKO ) 
			return pBuffer;

		StatistExtension *pMyTE = (StatistExtension *)pExt;
		CoordTransX *pCTF = pMyTE->MyCTF();
		DWORD dFLM = pMyTE->FLM();

		if (iOTyp == OGKO ) {
			short Num = GetNumberSecObjects ( lONr );
			if ( Num == 0 ) 
				return pBuffer;
			long *pObj = new long [ Num +1 ];
			Num = GetSecObjects ( lONr, pObj ); 	// Parameter iTyp noch einf¸hren ??
			dFL = 0.0;
			for ( short i = 1; i < Num+1; i++ ) {
				dFL = dFL + GetFlaechenParams ( *(pObj+i) , pCTF);
			}
			DELETE_OBJ ( pObj );
			if ( dFL == 0.0 )
				 return pBuffer;
		} else
			dFL = GetFlaechenParams (lONr,pCTF);

		double dSumFL;
		if ( dFLM == FLM_Default )
			dSumFL = dFL / (double) QuadratKiloMeter;	// von QMeter in QKilometer
		if ( dFLM == FLM_QuadratKiloMeter )
			dSumFL = dFL / (double) QuadratKiloMeter;	// von QMeter in QKilometer
		if ( dFLM == FLM_Hektar )
			dSumFL = dFL / (double) Hektar	;	// von QMeter in Hektar
		if ( dFLM == FLM_QuadratMeter )
			dSumFL = dFL ;				//  QMeter

		unsigned short resID = 0;
		
		if (dFL != 0.0) {
			if ( dFLM == FLM_Default ) {
				if (dFL > (double) Hektar) {
					if (dFL > (double) QuadratKiloMeter) {	// QKilometer
						dFL = dFL / (double) QuadratKiloMeter;
						resID = IDT_UNITQKM;
					} else {
						dFL = dFL / (double) Hektar;	// Hektar
						resID = IDT_UNITHA;
					}
				} else
					resID = IDT_UNITQM;		// Quadratmeter
			}

			if ( dFLM == FLM_QuadratKiloMeter ) {
			// QKilometer
				dFL = dFL / (double) QuadratKiloMeter;
				resID = IDT_UNITQKM;
			}

			if ( dFLM == FLM_Hektar ) {
				dFL = dFL / (double) Hektar;	// Hektar
				resID = IDT_UNITHA;
			}

			if ( dFLM == FLM_QuadratMeter ) {
				resID = IDT_UNITQM;		// Quadratmeter
			}


#if defined(WIN32)
			ST_DtoA (pBuffer, "%9.4f", dFL);
			strcat (pBuffer, " ");
			strcat (pBuffer, ResString (ResID (resID, &g_pTE -> RF()), 10));
#else			
			ST_DtoA (s_cbBuffer, "%9.4f", dFL);
			strcat (s_cbBuffer, " ");
			strcat (s_cbBuffer, ResString (ResID (resID, &g_pTE -> RF()), 10));
			memcpy (pBuffer, s_cbBuffer, strlen(s_cbBuffer)+1);
#endif
		// Kumulative Werte berechnen
			lCnt++;
			dFullArea += dSumFL;
		}	
	}

return pBuffer;
}

//--------------------------------------------------------------------------
extern "C" char * _XTENSN_EXPORT PASCAL OPFlaechenRadius (long lONr, char *pBuffer, short iLen, DWORD pExt)
{
static long lCnt = 0;			// Fl‰chenObjekte
static double dFullRadius = 0.0;	// GesamtFl‰chenRadius
double dFL,dFLR;

	if (lONr == OBJPROP_RESET) {		// R¸cksetzen der akumulierten Werte
		lCnt = 0L;
		dFullRadius = 0.0;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
	// GesamtAnzahl ausgeben
		StatistExtension *pMyTE = (StatistExtension *)pExt;
		DWORD dLM = pMyTE->LM();

#if defined(WIN32)
		ST_DtoA (pBuffer, "%9.4f", dFullRadius);
		strcat (pBuffer, " ");
		if ( dLM == LM_Default)
			strcat (pBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_KiloMeter)
			strcat (pBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_Meter)
			strcat (pBuffer, ResString (ResID (IDT_UNITM, &g_pTE -> RF()), 10));
#else
		ST_DtoA (s_cbBuffer, "%9.4f", dFullRadius);
		strcat (s_cbBuffer, " ");

		if ( dLM == LM_Default)
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_KiloMeter)
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_Meter)
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITM, &g_pTE -> RF()), 10));

		memcpy (pBuffer, s_cbBuffer, strlen(s_cbBuffer)+1);

#endif
		return pBuffer;	

	} else if (lONr == OBJPROP_COUNT) {
#if defined(WIN32)
		ltoa (lCnt, pBuffer, 10);
#else
		ltoa (lCnt, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32

	        return pBuffer;

	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDH_HELPAREARADIUS, &g_pTE -> RF()), MAXSTRING);
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;


//	} else if (lONr > 0) {
	} else if (lONr != 0L) {
		TX_ASSERT(NULL != pBuffer);
		short iOTyp = DEX_GetObjectType (lONr);
	
		*pBuffer = '\0';

		if (iOTyp != OGFlaeche && iOTyp != OGKO ) return pBuffer;

		StatistExtension *pMyTE = (StatistExtension *)pExt;
		CoordTransX *pCTF = pMyTE->MyCTF();
		DWORD dLM = pMyTE->LM();

		if (iOTyp == OGKO ) {
			short Num = GetNumberSecObjects ( lONr );
			if ( Num == 0 ) return pBuffer;
			long *pObj = new long [ Num +1 ];
			Num = GetSecObjects ( lONr, pObj ); 	// Parameter iTyp noch einf¸hren ??
			dFL = 0.0;
			for ( short i = 1; i < Num+1; i++ ) {
				dFL = dFL + GetFlaechenParams ( *(pObj+i) ,pCTF);
			}
			DELETE_OBJ ( pObj );
			if ( dFL == 0.0 ) return pBuffer;
		} else
			dFL = GetFlaechenParams (lONr, pCTF);

		dFLR = sqrt ( dFL / Pi );

		double dSumFLR;

		if ( dLM == LM_Default)
			dSumFLR = dFLR / (double) KiloMeter;	// von Meter in Kilometer
		if ( dLM == LM_KiloMeter)
			dSumFLR = dFLR / (double) KiloMeter;	// von Meter in Kilometer
		if ( dLM == LM_Meter)
			dSumFLR = dFLR;		//  Meter 

		unsigned short resID = 0;
		
		if (dFLR != 0.0) {
			if ( dLM == LM_Default ) {
				if (dFLR > (double) KiloMeter) {	// Kilometer
					dFLR = dFLR / (double) KiloMeter;
					resID = IDT_UNITKM;
				} else
					resID = IDT_UNITM;		// Meter
			}
			if ( dLM == LM_KiloMeter ) {
				dFLR = dFLR / (double) KiloMeter;
				resID = IDT_UNITKM;
			}
			if ( dLM == LM_Meter ) {
				resID = IDT_UNITM;		// Meter
			}


#if defined(WIN32)
			ST_DtoA (pBuffer, "%9.4f", dFLR);
			strcat (pBuffer, " ");
			strcat (pBuffer, ResString (ResID (resID, &g_pTE -> RF()), 10));
#else
			ST_DtoA (s_cbBuffer, "%9.4f", dFLR);
			strcat (s_cbBuffer, " ");
			strcat (s_cbBuffer, ResString (ResID (resID, &g_pTE -> RF()), 10));
			memcpy (pBuffer, s_cbBuffer, strlen(s_cbBuffer)+1);
#endif			
		// Kumulative Werte berechnen
			lCnt++;
			dFullRadius += dSumFLR;
		}	
	}

return pBuffer;
}

//-------------------------------------------------------------------

extern "C" char * _XTENSN_EXPORT PASCAL OPFlaechenDifferenz (long lONr, char *pBuffer, short iLen, DWORD pExt)
{
static long lCnt = 0;			// Fl‰chenObjekte
static double dFullArea = 0.0;	// GesamtFl‰cheninhalt
double dFL,BFL,OFL;

	if (lONr == OBJPROP_RESET) {		// R¸cksetzen der akumulierten Werte
		lCnt = 0L;
		dFullArea = 0.0;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
	// GesamtAnzahl ausgeben
		StatistExtension *pMyTE = (StatistExtension *)pExt;
		DWORD dFLM = pMyTE->FLM();

#if defined(WIN32)
		ST_DtoA (pBuffer, "%9.4f", dFullArea);
		strcat (pBuffer, " ");

		if ( dFLM == FLM_QuadratKiloMeter)
			strcat (pBuffer, ResString (ResID (IDT_UNITQKM, &g_pTE -> RF()), 10));
		if ( dFLM == FLM_Default)
			strcat (pBuffer, ResString (ResID (IDT_UNITQKM, &g_pTE -> RF()), 10));
		if ( dFLM == FLM_Hektar)
			strcat (pBuffer, ResString (ResID (IDT_UNITHA, &g_pTE -> RF()), 10));
		if ( dFLM == FLM_QuadratMeter)
			strcat (pBuffer, ResString (ResID (IDT_UNITQM, &g_pTE -> RF()), 10));

#else
		ST_DtoA (s_cbBuffer, "%9.4f", dFullArea);
		strcat (s_cbBuffer, " ");

		if ( dFLM == FLM_Default )
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITQKM, &g_pTE -> RF()), 10));
		if ( dFLM == FLM_QuadratKiloMeter )
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITQKM, &g_pTE -> RF()), 10));
		if ( dFLM == FLM_Hektar )
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITHA, &g_pTE -> RF()), 10));
		if ( dFLM == FLM_QuadratMeter )
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITQM, &g_pTE -> RF()), 10));

		memcpy (pBuffer, s_cbBuffer, strlen(s_cbBuffer)+1);
#endif
		return pBuffer;	

	} else if (lONr == OBJPROP_COUNT) {
#if defined(WIN32)
		ltoa (lCnt, pBuffer, 10);
#else
		ltoa (lCnt, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
	        return pBuffer;

	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDH_HELPDIFF, &g_pTE -> RF()), MAXSTRING);
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;
//	} else if (lONr > 0) {
	} else if (lONr != 0L) {
		TX_ASSERT(NULL != pBuffer);
		short iOTyp = DEX_GetObjectType (lONr);
	
		*pBuffer = '\0';

		if (iOTyp != OGKO ) return pBuffer;

		StatistExtension *pMyTE = (StatistExtension *)pExt;
		CoordTransX *pCTF = pMyTE->MyCTF();
		DWORD dFLM = pMyTE->FLM();

		short Num = GetNumberSecObjects ( lONr );
		if ( Num == 0 ) return pBuffer;
		long *pObj = new long [ Num +1 ];
		Num = GetSecObjects ( lONr, pObj ); 	// Parameter iTyp noch einfÅhren ??
		dFL = 0.0;
		OFL = 0.0;
		BFL = 0.0;
		for ( short i = 1; i < Num+1; i++ ) {
			OFL = GetFlaechenParams ( *(pObj+i) ,pCTF);	// Bestimmen der EinzelflÑchen
			if ( OFL > BFL ) BFL = OFL;		// Bestimmen der grî·ten FlÑche
			dFL = dFL + OFL;			// Kumulieren der FlÑcheninhalte
		}
		DELETE_OBJ ( pObj );
		dFL = dFL - BFL;	// Restfl‰chen ( auﬂer der grˆﬂten )
		dFL = BFL - dFL;	// Differenz " Grˆﬂte - Rest "

		double dSumFL;
		if ( dFLM == FLM_Default )
			dSumFL = dFL / (double) QuadratKiloMeter;	// von QMeter in QKilometer
		if ( dFLM == FLM_QuadratKiloMeter )
			dSumFL = dFL / (double) QuadratKiloMeter;	// von QMeter in QKilometer
		if ( dFLM == FLM_Hektar )
			dSumFL = dFL / (double) Hektar	;	// von QMeter in Hektar
		if ( dFLM == FLM_QuadratMeter )
			dSumFL = dFL ;				//  QMeter

		unsigned short resID = 0;
		
		if (dFL != 0.0) {
			if ( dFLM == FLM_Default ) {
				if (dFL > (double) Hektar) {
					if (dFL > (double) QuadratKiloMeter) {	// QKilometer
						dFL = dFL / (double) QuadratKiloMeter;
						resID = IDT_UNITQKM;
					} else {
						dFL = dFL / (double) Hektar;	// Hektar
						resID = IDT_UNITHA;
					}
				} else
					resID = IDT_UNITQM;		// Quadratmeter
			}

			if ( dFLM == FLM_QuadratKiloMeter ) {
				dFL = dFL / (double) QuadratKiloMeter;
				resID = IDT_UNITQKM;
			}

			if ( dFLM == FLM_Hektar ) {
				dFL = dFL / (double) Hektar;	// Hektar
				resID = IDT_UNITHA;
			}

			if ( dFLM == FLM_QuadratMeter ) {
				resID = IDT_UNITQM;		// Quadratmeter
			}

#if defined(WIN32)
			ST_DtoA (pBuffer, "%9.4f", dFL);
			strcat (pBuffer, " ");
			strcat (pBuffer, ResString (ResID (resID, &g_pTE -> RF()), 10));
#else
			ST_DtoA (s_cbBuffer, "%9.4f", dFL);
			strcat (s_cbBuffer, " ");
			strcat (s_cbBuffer, ResString (ResID (resID, &g_pTE -> RF()), 10));
			memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
			
		// Kumulative Werte berechnen
			lCnt++;
			dFullArea += dSumFL;
		}	
	}

return pBuffer;
}

extern "C" char * _XTENSN_EXPORT PASCAL OPFlaechenUmfang (long lONr, char *pBuffer, short iLen, DWORD pExt)
{
static long lCnt = 0;			// Fl‰chenObjekte
static double dFullRange = 0.0;	// GesamtFl‰chenUmfang
double dR = 0.0;

	if (lONr == OBJPROP_RESET) {		// R¸cksetzen der akumulierten Werte
		lCnt = 0L;
		dFullRange = 0.0;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
	// GesamtAnzahl ausgeben
		StatistExtension *pMyTE = (StatistExtension *)pExt;
		DWORD dLM = pMyTE->LM();

#if defined(WIN32)
		ST_DtoA (pBuffer, "%9.4f", dFullRange);
		strcat (pBuffer, " ");

		if ( dLM == LM_Default)
			strcat (pBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_KiloMeter)
			strcat (pBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_Meter)
			strcat (pBuffer, ResString (ResID (IDT_UNITM, &g_pTE -> RF()), 10));

#else
		ST_DtoA (s_cbBuffer, "%9.4f", dFullRange);
		strcat (s_cbBuffer, " ");

		if ( dLM == LM_Default)
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_KiloMeter)
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_Meter)
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITM, &g_pTE -> RF()), 10));

		memcpy (pBuffer, s_cbBuffer, strlen(s_cbBuffer)+1);
#endif
		return pBuffer;	

	} else if (lONr == OBJPROP_COUNT) {

#if defined(WIN32)
		ltoa (lCnt, pBuffer, 10);
#else
		ltoa (lCnt, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
	        return pBuffer;

	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDH_HELPRANGE, &g_pTE -> RF()), MAXSTRING);
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;

//	} else if (lONr > 0) {
	} else if (lONr != 0L) {
		TX_ASSERT(NULL != pBuffer);
		short iOTyp = DEX_GetObjectType (lONr);
	
		*pBuffer = '\0';

		if (iOTyp != OGFlaeche && iOTyp != OGKO ) return pBuffer;

		StatistExtension *pMyTE = (StatistExtension *)pExt;
		CoordTransX *pCTF = pMyTE->MyCTF();
		DWORD dLM = pMyTE->LM();

		if (iOTyp == OGKO ) {
			short Num = GetNumberSecObjects ( lONr );
			if ( Num == 0 ) return pBuffer;
			long *pObj = new long [ Num +1 ];
			Num = GetSecObjects ( lONr, pObj ); 	// Parameter iTyp noch einf¸hren ??
			dR = 0.0;
			for ( short i = 1; i < Num+1; i++ ) {
				dR = dR + GetFlaechenUmfang ( *(pObj+i) ,pCTF);
			}
			DELETE_OBJ ( pObj );
			if ( dR == 0.0 ) return pBuffer;
		} else
			dR = GetFlaechenUmfang (lONr, pCTF);

		double dSumR ;

		if ( dLM == LM_Default)
			dSumR = dR / (double) KiloMeter;	// von Meter in Kilometer
		if ( dLM == LM_KiloMeter)
			dSumR = dR / (double) KiloMeter;	// von Meter in Kilometer
		if ( dLM == LM_Meter)
			dSumR = dR;		//  Meter 

		unsigned short resID = 0;
		
		if (dR != 0.0) {
			if ( dLM == LM_Default ) {
				if (dR > (double) KiloMeter) {
					dR = dR / (double) KiloMeter;
					resID = IDT_UNITKM;
				} else
					resID = IDT_UNITM;		// Meter
			}

			if ( dLM == LM_KiloMeter ) {
				dR = dR / (double) KiloMeter;
				resID = IDT_UNITKM;
			}

			if ( dLM == LM_Meter ) {
				resID = IDT_UNITM;		// Meter
			}

#if defined(WIN32)
			ST_DtoA (pBuffer, "%9.4f", dR);
			strcat (pBuffer, " ");
			strcat (pBuffer, ResString (ResID (resID, &g_pTE -> RF()), 10));
#else
			ST_DtoA (s_cbBuffer, "%9.4f", dR);
			strcat (s_cbBuffer, " ");
			strcat (s_cbBuffer, ResString (ResID (resID, &g_pTE -> RF()), 10));
			memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
			
		// Kumulative Werte berechnen
			lCnt++;
			dFullRange += dSumR;
		}	
	}

return pBuffer;
}

extern "C" char * _XTENSN_EXPORT PASCAL OPFlaechenUmrandung (long lONr, char *pBuffer, short iLen, DWORD pExt)
{
static long lCnt = 0;			// Fl‰chenObjekte
static double dFullRange = 0.0;	// GesamtFl‰chenUmfang
double dR = 0.0;

	if (lONr == OBJPROP_RESET) {		// R¸cksetzen der akumulierten Werte
		lCnt = 0L;
		dFullRange = 0.0;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
	// GesamtAnzahl ausgeben
		StatistExtension *pMyTE = (StatistExtension *)pExt;
		DWORD dLM = pMyTE->LM();

#if defined(WIN32)
		ST_DtoA (pBuffer, "%9.4f", dFullRange);
		strcat (pBuffer, " ");

		if ( dLM == LM_Default)
			strcat (pBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_KiloMeter)
			strcat (pBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_Meter)
			strcat (pBuffer, ResString (ResID (IDT_UNITM, &g_pTE -> RF()), 10));
#else
		ST_DtoA (s_cbBuffer, "%9.4f", dFullRange);
		strcat (s_cbBuffer, " ");

		if ( dLM == LM_Default)
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_KiloMeter)
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_Meter)
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITM, &g_pTE -> RF()), 10));

		memcpy (pBuffer, s_cbBuffer, strlen(s_cbBuffer)+1);
#endif
		return pBuffer;	
	} else if (lONr == OBJPROP_COUNT) {
#if defined(WIN32)
		ltoa (lCnt, pBuffer, 10);
#else
		ltoa (lCnt, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
	        return pBuffer;

	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDH_HELPBIGRANGE, &g_pTE -> RF()), MAXSTRING);
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;
//	} else if (lONr > 0) {
	} else if (lONr != 0L) {
		TX_ASSERT(NULL != pBuffer);
		short iOTyp = DEX_GetObjectType (lONr);
	
		*pBuffer = '\0';

		if (iOTyp != OGFlaeche && iOTyp != OGKO ) return pBuffer;

		StatistExtension *pMyTE = (StatistExtension *)pExt;
		CoordTransX *pCTF = pMyTE->MyCTF();
		DWORD dLM = pMyTE->LM();


		if (iOTyp == OGKO ) {
			short Num = GetNumberSecObjects ( lONr );
			if ( Num == 0 ) return pBuffer;
			long *pObj = new long [ Num +1 ];
			Num = GetSecObjects ( lONr, pObj ); 	// Parameter iTyp noch einf¸hren ??
			dR = 0.0;
			for ( short i = 1; i < Num+1; i++ ) {
				dR = dR + GetFlaechenUmrandung ( *(pObj+i) , pCTF);
			}
			DELETE_OBJ ( pObj );
			if ( dR == 0.0 ) return pBuffer;
		} else
			dR = GetFlaechenUmrandung (lONr, pCTF);

		double dSumR;

		if ( dLM == LM_Default)
			dSumR = dR / (double) KiloMeter;	// von Meter in Kilometer
		if ( dLM == LM_KiloMeter)
			dSumR = dR / (double) KiloMeter;	// von Meter in Kilometer
		if ( dLM == LM_Meter)
			dSumR = dR;		//  Meter 

		unsigned short resID = 0;
		
		if (dR != 0.0) {
			if ( LM_Default ) {
				if (dR > (double) KiloMeter) {
					dR = dR / (double) KiloMeter;
					resID = IDT_UNITKM;
				} else
					resID = IDT_UNITM;		// Meter
			}

			if ( dLM == LM_KiloMeter ) {
				dR = dR / (double) KiloMeter;
				resID = IDT_UNITKM;
			}

			if ( dLM == LM_Meter ) {
				resID = IDT_UNITM;		// Meter
			}


#if defined(WIN32)
			ST_DtoA (pBuffer, "%9.4f", dR);
			strcat (pBuffer, " ");
			strcat (pBuffer, ResString (ResID (resID, &g_pTE -> RF()), 10));
#else
			ST_DtoA (s_cbBuffer, "%9.4f", dR);
			strcat (s_cbBuffer, " ");
			strcat (s_cbBuffer, ResString (ResID (resID, &g_pTE -> RF()), 10));
			memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
			
		// Kumulative Werte berechnen
			lCnt++;
			dFullRange += dSumR;
		}	
	}

return pBuffer;
}

//--------------------------------------------------------------------------

double GetFlaechenParams (long lONr, CoordTransX *pCTF, double *pdX, double *pdY ) 
{
// allgemeine Info's zur Fl‰che ranholen
OBJSTATISTIK OS;
	memset (&OS,'\0',sizeof(OBJSTATISTIK));
double FL = 0.0;

	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr = lONr;
	if (!DEX_GetObjStatistik (OS))
		return 0.0;

	if (OS.iObjTyp == OT_FLAECHE) {

		double *pX = new double [OS.lCnt];
		double *pY = new double [OS.lCnt];
		long *pK = new long [OS.iKCnt];

		if ( !HoleFlaechenInformation ( lONr, pCTF, OS.lCnt, OS.iKCnt, pX, pY, pK, true)) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			DELETE_OBJ (pK);
			return 0.0;
		}

		//Fl‰chenparameter
		double SX, SY;
	
		FL = GetAreaObject ( pX, pY, pK, OS.lCnt, OS.iKCnt , &SX, &SY );
		if (pdX) *pdX = SX / (*pK - 1);
		if (pdY) *pdY = SY / (*pK - 1);

		if ( pdX && pdY )
			SetCoordinate ( pdX, pdY , pCTF);

	// aufr‰umen
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		DELETE_OBJ (pK);
	}
	return FL;
}	
//------------------------------------------------------------------------
//--------------------------------------------------------------------------

Bool GetFlaechenPunkt (long lONr, CoordTransX *pCTF, double *pdX, double *pdY ) 
{
// allgemeine Info's zur Fl‰che ranholen
OBJSTATISTIK OS;
	memset (&OS,'\0',sizeof(OBJSTATISTIK));

	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr = lONr;
	if (!DEX_GetObjStatistik (OS))
		return FALSE;

	if (OS.iObjTyp == OT_FLAECHE) {

		double *pX = new double [OS.lCnt];
		double *pY = new double [OS.lCnt];
		long *pK = new long [OS.iKCnt];

#if _TRiAS_VER < 0x0400
		if ( !HoleFlaechenInformation ( lONr, pCTF, OS.lCnt, OS.iKCnt, pX, pY, pK,false)) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			DELETE_OBJ (pK);
			return FALSE;
		}
#else
// KK010205
			
		OBJGEOMETRIE OG;
		memset (&OG,'\0',sizeof(OBJGEOMETRIE));
		OG.dwSize = sizeof(OBJGEOMETRIE);
		OG.lONr = lONr;
		OG.lCnt = OS.lCnt;
		OG.iKCnt = OS.iKCnt;
		OG.pdblX = pX;
		OG.pdblY = pY;
		OG.plCnt = pK;
		OG.iFlags = OGConverted;

	if (!DEX_GetObjGeometrie (OG)) 
		return FALSE;

#endif

		//Fl‰chenparameter
		double SX, SY;
	
		GetAreaObjectPoint ( pX, pY, pK, OS.lCnt, OS.iKCnt , &SX, &SY );
		if (pdX) *pdX = SX / (*pK - 1);
		if (pdY) *pdY = SY / (*pK - 1);


	// aufr‰umen
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		DELETE_OBJ (pK);
	}
	return TRUE;
}	
//------------------------------------------------------------------------
//-------------Fl‰chenschwerpunktberechnung---------------------------------------------
void GetAreaObjectPoint ( double *pX, double *pY, long * pK,
		       long Count, short Kount ,double *SX, double *SY ) 
{

long i, j, K;

double SSX,SSY;		// Vielleicht wird es noch gebraucht
	K = *pK;

	GetAreaObjectPointPart ( pX, pY, K ,SX, SY );		// Auﬂenrahmen

	if ( Kount == 1 ) return;	// Keine Lˆcher
	j = 0;
	for ( i = 1; i < Kount ; i++ ) {
		j = j + K;
		K = * (pK+i);	// Koordinatenanzahl
		GetAreaObjectPointPart ( pX+j, pY+j, K, &SSX, &SSY);
	}
	return;
}

//----------------Teilfl‰chenschwerpunktberechnung--------------------------------------
void GetAreaObjectPointPart ( double *pX, double *pY, long K,
		       double *SX, double *SY ) 
{

double *pX1,*pY1;
long i;

double * pXX, *pYY;
	
	pXX = pX;
	pX1 = pX + 1;
	pYY = pY;
	pY1 = pY + 1;
	*SX = 0.0;
	*SY = 0.0;

	for ( i = 1 ; i < K ; i++ )  {
	
		  *SX = *SX + *pXX;
		  *SY = *SY + *pYY;

		  pXX = pX1 ;
		  pX1 = pX1 + 1;
		  pYY = pY1;
		  pY1 = pY1 + 1;

	}

	return;
}
//-----------------------------------------------------------------------

//------------------------------------------------------------------------
double GetFlaechenUmfang (long lONr, CoordTransX *pCTF) 
{
// allgemeine Info's zur Fl‰che ranholen
OBJSTATISTIK OS;
	memset (&OS,'\0',sizeof(OBJSTATISTIK));
double R = 0.0;

	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr = lONr;
	if (!DEX_GetObjStatistik (OS))
		return 0.0;

	if (OS.iObjTyp == OT_FLAECHE) {

		double *pX = new double [OS.lCnt];
		double *pY = new double [OS.lCnt];
		long *pK = new long [OS.iKCnt];

// KK010205
//		if ( !HoleFlaechenInformation ( lONr, pCTF, OS.lCnt, OS.iKCnt, pX, pY, pK,true)) {
		if ( !HoleFlaechenInformation ( lONr, pCTF, OS.lCnt, OS.iKCnt, pX, pY, pK,false)) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			DELETE_OBJ (pK);
			return 0.0;
		}

		//Fl‰chenparameter
		double SX,SY;	
//		R = GetPolyLen ( pX, pY, *pK, &SX, &SY );
		R = GetPolyLen ( pCTF, pX, pY, *pK, &SX, &SY );

	// aufr‰umen
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		DELETE_OBJ (pK);
	}

return R;
}	

double GetFlaechenUmrandung (long lONr, CoordTransX *pCTF) 
{
// allgemeine Info's zur Fl‰che ranholen
OBJSTATISTIK OS;
	memset (&OS,'\0',sizeof(OBJSTATISTIK));
double R = 0.0;

	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr = lONr;
	if (!DEX_GetObjStatistik (OS))
		return 0.0;

	if (OS.iObjTyp == OT_FLAECHE) {

		double *pX = new double [OS.lCnt];
		double *pY = new double [OS.lCnt];
		long *pK = new long [OS.iKCnt];

// KK010205
		if ( !HoleFlaechenInformation ( lONr, pCTF, OS.lCnt, OS.iKCnt, pX, pY, pK,false)) {
//		if ( !HoleFlaechenInformation ( lONr, pCTF, OS.lCnt, OS.iKCnt, pX, pY, pK,true)) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			DELETE_OBJ (pK);
			return 0.0;
		}

		//Fl‰chenparameter
		double SX,SY;	
		long K,i,j;

		K = *pK;
//		R = GetPolyLen ( pX, pY, K ,&SX, &SY );		// Auﬂenrahmen
		R = GetPolyLen ( pCTF, pX, pY, K ,&SX, &SY );		// Auﬂenrahmen

		if ( OS.iKCnt == 1 ) {
			DELETE_OBJ ( pX);
			DELETE_OBJ ( pY);
			DELETE_OBJ ( pK);
			return R;	// Keine Lˆcher
		}

		j = 0;
		for ( i = 1; i < OS.iKCnt ; i++ ) {
			j = j + K;
			K = * (pK+i);	// Koordinatenanzahl
//			R = GetPolyLen ( pX+j, pY+j, K-j, &SX, &SY);
//			R = R + GetPolyLen ( pY+j, pY+j, K, &SX, &SY);
			R = R + GetPolyLen ( pCTF, pX+j, pY+j, K, &SX, &SY);
		}

	// aufr‰umen
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		DELETE_OBJ (pK);
	}

return R;
}	

//----------------------------------------------------------------------

// LinienL‰ngenberechnung ---------------------------------------------------

extern "C" char * _XTENSN_EXPORT PASCAL OPLinienLaenge (long lONr, char *pBuffer, short iLen, DWORD pExt)
{
static long lCnt = 0;			// LinienObjekte
static double dFullLine = 0.0;	// GesamtL‰nge
double dLL = 0.0;

	if (lONr == OBJPROP_RESET) {		// R¸cksetzen der akumulierten Werte
		lCnt = 0L;
		dFullLine = 0.0;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
	// GesamtAnzahl ausgeben
		StatistExtension *pMyTE = (StatistExtension *)pExt;
		DWORD dLM = pMyTE->LM();

#if defined(WIN32)
		ST_DtoA (pBuffer, "%9.4f", dFullLine);
		strcat (pBuffer, " ");

		if ( dLM == LM_Default)
			strcat (pBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_KiloMeter)
			strcat (pBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_Meter)
			strcat (pBuffer, ResString (ResID (IDT_UNITM, &g_pTE -> RF()), 10));
#else
		ST_DtoA (s_cbBuffer, "%9.4f", dFullLine);
		strcat (s_cbBuffer, " ");

		if ( dLM == LM_Default)
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_KiloMeter)
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITKM, &g_pTE -> RF()), 10));
		if ( dLM == LM_Meter)
			strcat (s_cbBuffer, ResString (ResID (IDT_UNITM, &g_pTE -> RF()), 10));

		memcpy (pBuffer, s_cbBuffer, strlen(s_cbBuffer)+1);
#endif
		return pBuffer;	

	} else if (lONr == OBJPROP_COUNT) {
#if defined(WIN32)
		ltoa (lCnt, pBuffer, 10);
#else
		ltoa (lCnt, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
	        return pBuffer;

	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDH_HELPLINE, &g_pTE -> RF()), MAXSTRING);
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;
//	} else if (lONr > 0) {
	} else if (lONr != 0L) {
		TX_ASSERT(NULL != pBuffer);
		short iOTyp = DEX_GetObjectType (lONr);
	
		*pBuffer = '\0';

		if (iOTyp != OGLinie && iOTyp != OGKO) return pBuffer;

		StatistExtension *pMyTE = (StatistExtension *)pExt;
		CoordTransX *pCTF = pMyTE->MyCTF();
		DWORD dLM = pMyTE->LM();

		if (iOTyp == OGKO ) {
			short Num = GetNumberSecObjects ( lONr );
			if ( Num == 0 ) return pBuffer;
			long *pObj = new long [ Num +1 ];
			Num = GetSecObjects ( lONr, pObj ); 	// Parameter iTyp noch einf¸hren ??
			dLL = 0.0;
			for ( short i = 1; i < Num+1; i++ ) {
				dLL = dLL + GetLinienParams ( *(pObj+i) ,pCTF);
			}
			DELETE_OBJ ( pObj );
			if ( dLL == 0.0 ) return pBuffer;
		} else
			dLL = GetLinienParams (lONr,pCTF);

		double dSumLL;

		if ( dLM == LM_Default)
			dSumLL = dLL / (double) KiloMeter;	// von Meter in Kilometer
		if ( dLM == LM_KiloMeter)
			dSumLL = dLL / (double) KiloMeter;	// von Meter in Kilometer
		if ( dLM == LM_Meter)
			dSumLL = dLL;		//  Meter 
		unsigned short resID = 0;
		
		if (dLL != 0.0) {
			if ( dLM == LM_Default ) {
				if (dLL > (double) KiloMeter) {
					dLL = dLL / (double) KiloMeter;
					resID = IDT_UNITKM;
				} else 
					resID = IDT_UNITM;		// Meter
			}
			if ( dLM == LM_KiloMeter ) {
				dLL = dLL / (double) KiloMeter;
				resID = IDT_UNITKM;
			}
			if ( dLM == LM_Meter ) {
				resID = IDT_UNITM;		// Meter
			}

#if defined(WIN32)
			ST_DtoA (pBuffer, "%9.4f", dLL);
			strcat (pBuffer, " ");
			strcat (pBuffer, ResString (ResID (resID, &g_pTE -> RF()), 10));
#else
			ST_DtoA (s_cbBuffer, "%9.4f", dLL);
			strcat (s_cbBuffer, " ");
			strcat (s_cbBuffer, ResString (ResID (resID, &g_pTE -> RF()), 10));
			memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
			
		// Kumulative Werte berechnen
			lCnt++;
			dFullLine += dSumLL;
		}	
	}

return pBuffer;
}
//--------------------------------------------------------------------------
double GetLinienParams (long lONr, CoordTransX *pCTF, double *pdX, double *pdY) 
{
// allgemeine Info's zur Linie ranholen
OBJSTATISTIK OS;
	memset (&OS,'\0',sizeof(OBJSTATISTIK));
double LL = 0.0;

	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr = lONr;
	if (!DEX_GetObjStatistik (OS))
		return LL;

	if (OS.iObjTyp == OT_KANTE) {

		//Linienparameter
		double SX, SY;
		double *pX = new double [OS.lCnt];
		double *pY = new double [OS.lCnt];

		if (!HoleLinienInformation (lONr, pCTF, OS.lCnt, pX, pY)) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			return LL;
		}

//		LL = GetPolyLen ( pX, pY, OS.lCnt, &SX, &SY );

		try {
			LL = GetPolyLen ( pCTF, pX, pY, OS.lCnt, &SX, &SY );
		} catch ( ... ) {
			char *pONR = new char [_MAX_PATH];
			if (pONR ) {
				*pONR = '\0';
				wsprintf (pONR, ResString( ResID( IDS_CATCHPOLYLEN,&g_pTE->RF()),50),lONr);

				MessageBox ( 0,
					pONR,
					ResString ( ResID ( IDS_CATCHCAPTION,&g_pTE->RF()),60),
					MB_OK);
				DELETE_OBJ ( pONR);
				LL = 0.0;
			}
		}

		if (pdX) *pdX = SX;
		if (pdY) *pdY = SY;
		

		if ( pdX && pdY )
			SetCoordinate ( pdX, pdY , pCTF);

	// aufr‰umen
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
	}

return LL;
}	
//--------------------------------------------------------------------
//--------------------------------------------------------------------------
Bool GetLinienPunkt (long lONr, CoordTransX *pCTF, double *pdX, double *pdY) 
{
	if ( pdX == NULL || pdY == NULL )
		return FALSE;

// allgemeine Info's zur Linie ranholen
OBJSTATISTIK OS;
	memset (&OS,'\0',sizeof(OBJSTATISTIK));

	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr = lONr;
	if (!DEX_GetObjStatistik (OS))
		return FALSE;

	if (OS.iObjTyp == OT_KANTE) {
 /*---------------------------------------

		OBJGEOMETRIE OG;
		long *pX = new long [OS.lCnt];
		long *pY = new long [OS.lCnt];

		if (pX == NULL || pY == NULL) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			return FALSE;
		}

		memset (&OG,'\0',sizeof(OBJGEOMETRIE));
		OG.dwSize = sizeof(OBJGEOMETRIE);
		OG.lONr = lONr;
		OG.lCnt = OS.lCnt;
		OG.pdblX = pX;
		OG.pdblY = pY;
		OG.iFlags = OGConverted;
		if (DEX_GetObjGeometrie (OG)) {
 ----------------------------------------------------------------*/

		//Linienparameter
		double SX, SY;
		double *pX = new double [OS.lCnt];
		double *pY = new double [OS.lCnt];

		if (!HoleLinienInformation (lONr, pCTF, OS.lCnt, pX, pY)) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			return FALSE;
		}
		
		
		
		long j;

		if ( OS.lCnt == 2 ) {
				SX = (*pX + *( pX+1 ))/2.0;
				SY = (*pY + *( pY+1 ))/2.0;
		} else {
				j = OS.lCnt/2;
				SX = *(pX+j);
				SY = *(pY+j);
		}

		if (pdX) *pdX = SX;
		if (pdY) *pdY = SY;
		
    	
	// aufr‰umen
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
	}
	return TRUE;
}	
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//	ReferenzPunktBestimmung

// ReferenzpunktX berechnen -----------------------------------------------
extern "C" char * _XTENSN_EXPORT PASCAL OPReferenzPunktX (long lONr, char *pBuffer, short iLen, DWORD pExt)
{
static long lCnt = 0;				// Objekte

	if (lONr == OBJPROP_RESET) {		// R¸cksetzen der akumulierten Werte
		lCnt = 0L;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
	// GesamtAnzahl ausgeben
		*pBuffer = '\0';
		return pBuffer;	

	} else if (lONr == OBJPROP_COUNT) {
#if defined(WIN32)
		ltoa (lCnt, pBuffer, 10);
#else
		ltoa (lCnt, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
	        return pBuffer;

	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDH_HELPRPOINTX, &g_pTE -> RF()), MAXSTRING);
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;
//	} else if (lONr > 0) {
	} else if (lONr != 0L) {
		TX_ASSERT(NULL != pBuffer);

		short iOTyp = DEX_GetObjectType (lONr);
	
		*pBuffer = '\0';
		
		double dX, dY;
		Bool Metric = TRUE;

		StatistExtension *pMyTE = (StatistExtension *)pExt;
		CoordTransX *pCTF = pMyTE->MyCTF();
		IExtendTopRel2 *pTop = pMyTE->MyTop();
		if ( !pTop)
				pMyTE->LadeTopRel();

		pTop = pMyTE->MyTop();


		if (iOTyp == OGFlaeche ) {	// Fl‰che = Container
		
			if (GetContainerPunkt (pTop,lONr, pCTF, &dX, &dY)) {

				if ( pCTF != NULL )  {
					Metric = pCTF->isMetric();
					pCTF->Transform (&dX, &dY);
				}

//----------------------------------------------------------------------------------

				if ( Metric ) {
#if defined(WIN32)
					ST_DtoA (pBuffer, "%9.4f", dX);
#else
					ST_DtoA (s_cbBuffer, "%9.4f", dX);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				} else {
#if defined(WIN32)
					ST_NoMtoA (pBuffer, FALSE, dX, dY, pCTF);
#else
					ST_NoMtoA (s_cbBuffer, FALSE, dX, dY, pCTF);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				}
			

		// Kumulative Werte berechnen
				lCnt++;
			}	
		}

		if (iOTyp == OGLinie ) {	// Linie = MittelPunkt
			if (GetLinienPunkt (lONr, pCTF, &dX, &dY) ) {

				if ( pCTF != NULL )  {
					Metric = pCTF->isMetric();
					pCTF->Transform (&dX, &dY);
				}

				if ( Metric ) {
#if defined (WIN32)
					ST_DtoA (pBuffer, "%9.4f", dX);
#else
					ST_DtoA (s_cbBuffer, "%9.4f", dX);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				} else {
#if defined (WIN32)
					ST_NoMtoA (pBuffer, FALSE, dX, dY, pCTF);
#else
					ST_NoMtoA (s_cbBuffer, FALSE, dX, dY, pCTF);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				}


		// Kumulative Werte berechnen
				lCnt++;
			}	
		}

		if (iOTyp == OGPunkt ) {	// Punkt = Koordinate
			if (GetPunktParams (lONr, &dX, &dY) ) { 
				if ( pCTF != NULL )  {
					Metric = pCTF->isMetric();
				}
				if ( Metric ) {
#if defined (WIN32)
					ST_DtoA (pBuffer, "%9.4f", dX);
#else
					ST_DtoA (s_cbBuffer, "%9.4f", dX);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				} else {
#if defined (WIN32)
					ST_NoMtoA (pBuffer, FALSE, dX, dY, pCTF);
#else
					ST_NoMtoA (s_cbBuffer, FALSE, dX, dY, pCTF);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				}

		// Kumulative Werte berechnen
				lCnt++;
			}	
		}

//-----Texte
		if (iOTyp == OGText ) {	// Text = Koordinate
			if (GetPunktParams (lONr, &dX, &dY) ) { 
				if ( pCTF != NULL )  {
					Metric = pCTF->isMetric();
				}
				if ( Metric ) {
#if defined (WIN32)
					ST_DtoA (pBuffer, "%9.4f", dX);
#else
					ST_DtoA (s_cbBuffer, "%9.4f", dX);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				} else {
#if defined (WIN32)
					ST_NoMtoA (pBuffer, FALSE, dX, dY, pCTF);
#else
					ST_NoMtoA (s_cbBuffer, FALSE, dX, dY, pCTF);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				}

		// Kumulative Werte berechnen
				lCnt++;
			}	
		}


	}

return pBuffer;
}

//============================================================================

//==========================================================================
// ReferenzpunktY berechnen -----------------------------------------------
extern "C" char * _XTENSN_EXPORT PASCAL OPReferenzPunktY (long lONr, char *pBuffer, short iLen, DWORD pExt)
{
static long lCnt = 0;				// Objekte

	if (lONr == OBJPROP_RESET) {		// R¸cksetzen der akumulierten Werte
		lCnt = 0L;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {

		*pBuffer = '\0';
		return pBuffer;	

	} else if (lONr == OBJPROP_COUNT) {
#if defined(WIN32)
		ltoa (lCnt, pBuffer, 10);
#else
		ltoa (lCnt, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
	        return pBuffer;

	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDH_HELPRPOINTY, &g_pTE -> RF()), MAXSTRING);
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;
//	} else if (lONr > 0) {
	} else if (lONr != 0L) {
		TX_ASSERT(NULL != pBuffer);

		short iOTyp = DEX_GetObjectType (lONr);
	
		*pBuffer = '\0';
		
		double dX, dY;
		Bool Metric = TRUE;

		StatistExtension *pMyTE = (StatistExtension *)pExt;
		CoordTransX *pCTF = pMyTE->MyCTF();
		IExtendTopRel2 *pTop = pMyTE->MyTop();
		if ( !pTop)
				pMyTE->LadeTopRel();

		pTop = pMyTE->MyTop();


		if (iOTyp == OGFlaeche ) {	// Fl‰che = Container
		
			if (GetContainerPunkt (pTop,lONr, pCTF, &dX, &dY) ) {


				if ( pCTF != NULL )  {
					Metric = pCTF->isMetric();
					pCTF->Transform (&dX, &dY);
				}
	
//----------------------------------------------------------------------------------

				
				if ( Metric ) {
#if defined(WIN32)
					ST_DtoA (pBuffer, "%9.4f", dY);
#else
					ST_DtoA (s_cbBuffer, "%9.4f", dY);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				} else {
#if defined(WIN32)
					ST_NoMtoA (pBuffer, TRUE, dX, dY, pCTF);
#else
					ST_NoMtoA (s_cbBuffer, TRUE, dX, dY, pCTF);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				}
		// Kumulative Werte berechnen
				lCnt++;
			}	
		}
		if (iOTyp == OGLinie ) {	// Linie = MittelPunkt
			if (GetLinienPunkt (lONr, pCTF, &dX, &dY) ) {

				if ( pCTF != NULL )  {
					Metric = pCTF->isMetric();
					pCTF->Transform (&dX, &dY);
				}
	
				if ( Metric ) {
#if defined(WIN32)
					ST_DtoA (pBuffer, "%9.4f", dY);
#else
					ST_DtoA (s_cbBuffer, "%9.4f", dY);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				} else {
#if defined(WIN32)
					ST_NoMtoA (pBuffer, TRUE, dX, dY, pCTF);
#else
					ST_NoMtoA (s_cbBuffer, TRUE, dX, dY, pCTF);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				}
		// Kumulative Werte berechnen
				lCnt++;
			}	
		}


		if (iOTyp == OGPunkt ) {	// Punkt = Koordinate
			if (GetPunktParams (lONr, &dX, &dY) ) { 
				if ( pCTF != NULL )  {
					Metric = pCTF->isMetric();
				}
				if ( Metric ) {
#if defined(WIN32)
					ST_DtoA (pBuffer, "%9.4f", dY);
#else
					ST_DtoA (s_cbBuffer, "%9.4f", dY);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				} else {
#if defined(WIN32)
					ST_NoMtoA (pBuffer, TRUE, dX, dY, pCTF);
#else
					ST_NoMtoA (s_cbBuffer, TRUE, dX, dY, pCTF);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				}


		// Kumulative Werte berechnen
				lCnt++;
			}	
		}


		if (iOTyp == OGText ) {	// Text = Koordinate
			if (GetPunktParams (lONr, &dX, &dY) ) { 
				if ( pCTF != NULL )  {
					Metric = pCTF->isMetric();
				}
				if ( Metric ) {
#if defined(WIN32)
					ST_DtoA (pBuffer, "%9.4f", dY);
#else
					ST_DtoA (s_cbBuffer, "%9.4f", dY);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				} else {
#if defined(WIN32)
					ST_NoMtoA (pBuffer, TRUE, dX, dY, pCTF);
#else
					ST_NoMtoA (s_cbBuffer, TRUE, dX, dY, pCTF);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				}


		// Kumulative Werte berechnen
				lCnt++;
			}	
		}


	}

return pBuffer;
}
//------------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//	SchwerPunktBestimmung

// ReferenzpunktX berechnen -----------------------------------------------
extern "C" char * _XTENSN_EXPORT PASCAL OPSchwerPunktX (long lONr, char *pBuffer, short iLen, DWORD pExt)
{
static long lCnt = 0;				// Objekte

	if (lONr == OBJPROP_RESET) {		// R¸cksetzen der akumulierten Werte
		lCnt = 0L;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
	// GesamtAnzahl ausgeben
		*pBuffer = '\0';
		return pBuffer;	

	} else if (lONr == OBJPROP_COUNT) {
#if defined(WIN32)
		ltoa (lCnt, pBuffer, 10);
#else
		ltoa (lCnt, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
	        return pBuffer;

	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDH_HELPRSPOINTX, &g_pTE -> RF()), MAXSTRING);
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;
//	} else if (lONr > 0) {
	} else if (lONr != 0L) {
		TX_ASSERT(NULL != pBuffer);

		short iOTyp = DEX_GetObjectType (lONr);
	
		*pBuffer = '\0';
		if (iOTyp != OGFlaeche ) 
			return pBuffer;
		

		double dX, dY;
		Bool Metric = TRUE;

		StatistExtension *pMyTE = (StatistExtension *)pExt;
		CoordTransX *pCTF = pMyTE->MyCTF();
		IExtendTopRel2 *pTop = pMyTE->MyTop();
		if ( !pTop)
				pMyTE->LadeTopRel();

		pTop = pMyTE->MyTop();


		if (iOTyp == OGFlaeche ) {	// Fl‰che = SchwerPunkt
		
			if (GetFlaechenPunkt (lONr, pCTF, &dX, &dY)) {

				if ( pCTF != NULL )  {
					Metric = pCTF->isMetric();
#if _TRiAS_VER < 0x0400

					pCTF->Transform (&dX, &dY);
#endif
				}

//------------------Problem SWP innen/auﬂen - Korr. 18.11.97 -----------------------
//				if ( pTop ) {

//					ModFlaechenPunkt ( pTop, pCTF,lONr, &dX, &dY );
//				}
				
//----------------------------------------------------------------------------------



				if ( Metric ) {
#if defined(WIN32)
					ST_DtoA (pBuffer, "%9.4f", dX);
#else
					ST_DtoA (s_cbBuffer, "%9.4f", dX);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				} else {
#if defined(WIN32)
					ST_NoMtoA (pBuffer, FALSE, dX, dY, pCTF);
#else
					ST_NoMtoA (s_cbBuffer, FALSE, dX, dY, pCTF);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				}
			

		// Kumulative Werte berechnen
				lCnt++;
			}	
		}

	}

return pBuffer;
}

//============================================================================
void ModFlaechenPunkt (IExtendTopRel2 *pTop, CoordTransX* pCTF,long lONF, double *pX, double *pY)
{
	if (NULL == pTop || NULL == pCTF) 
		return;

	COM_TRY {
	WInitObjektGeometrie InitOG1 (CLSID_ObjektGeometrie);
	WInitObjektGeometrie InitOG2 (CLSID_ObjektGeometrie);
	Punkt P;

	double Min,Max;

		Min = *pX;
		Max = *pY;
		pCTF -> InvTransform (&Min, &Max);
		pCTF -> Scale (Min, Max, P);

#if _MSC_VER >= 1100
	long lX = P.GetX();
	long lY = P.GetY();
#else
	long lX = P.X();
	long lY = P.Y();
#endif // _MSC_VER >= 1100

		THROW_FAILED_HRESULT(InitOG1 -> InitObjGeometry (lX,lY,OT_PUNKT));

	WObjektGeometrie OG1 (InitOG1);		// implizites QI, throws hr

		THROW_FAILED_HRESULT(InitOG2 -> InitObjGeometry (lONF));

	WObjektGeometrie OG2 (InitOG2);		// implizites QI, throws hr
	Relat Rel;

		THROW_FAILED_HRESULT(pTop -> TopoRelationObjObj_Geom (OG2, OG1, &Rel));
		if (Rel == REL_INN)
			return;

		if (SetFlaechenPunkt (pTop, lONF, OG2, InitOG1, &lX, &lY)) {
#if _MSC_VER >= 1100
			P.SetX(lX);
			P.SetY(lY);
#else
			P.X() = lX;
			P.Y() = lY;
#endif // _MSC_VER >= 1100
			pCTF->UnScale (P, &Min, &Max);
			pCTF->Transform (&Min, &Max);

			*pX = Min;
			*pY = Max;
		}
	} COM_CATCH_NORETURN;
}
//------------------------------------------------------------------------
//============================================================================
bool SetFlaechenPunkt (IExtendTopRel2* pTop, long lONr, IObjektGeometrie *pIOG2, IInitObjektGeometrie *pInitOG1,long *lX, long *lY)
{
	if (!pInitOG1 || !pIOG2)
		return false;

long Cont[4];
long MinX, MaxX, MinY, MaxY;

	DEX_GetObjContainer (lONr, Cont[0]);

	MinX = Cont[0];
	MaxX = Cont[1];
	MinY = Cont[2];
	MaxY = Cont[3];

// Kurze Strecke suchen
long dY = MaxY - MinY;
long dX = MaxX - MinX;

long lX1 = *lX;
long lY1 = *lY;

long lTeiler,lAP,lEP;
long lDiffR,lDiffL;

// Verh‰ltnis bestimmen
short iFlag;

	if (dY > dX) {
		iFlag = true;
		lDiffR = MaxX - *lX; 
		lDiffL = *lX - MinX;
		if (lDiffR < lDiffL) 
			lTeiler = (MaxX-MinX)/lDiffR;
		else
			lTeiler = (MaxX-MinX)/lDiffL;

		lAP = MinX;
		lEP = MaxX;
	} else {
		iFlag = false;
		lDiffR = MaxY - *lY; 
		lDiffL = *lY - MinY;

		if (lDiffR < lDiffL) 
			lTeiler = (MaxY-MinY)/lDiffR;
		else 
			lTeiler = (MaxY-MinY)/lDiffL;

		lAP = MinY;
		lEP = MaxY;
	}

//	Neuen Punkt bestimmen
	for (long i = 0; i < 10; i++) {
		if (BildeFlaechenPunkt (pTop, pIOG2, pInitOG1, iFlag, lTeiler, lAP, lEP, lX, lY))
			return true;
		lTeiler = lTeiler * 2;
	}


	return false;
}

//------------------------------------------------------------------------
bool BildeFlaechenPunkt (IExtendTopRel2* pTop, IObjektGeometrie *pIOG2, IInitObjektGeometrie *pInitOG1,short iFlag,long lTeiler, long lAP, long lEP, long *lX, long *lY)
{
long lX1 = *lX;
long lY1 = *lY;

// Schrittweite/StartPunkt
long lSW = (lEP-lAP)/lTeiler;
//long lSP = lSW/2;

	if (0 == lSW)
		return false;		// EndlosIteration verhindern

// Punkt suchen
long lRefE = lEP - lSW;
long lRefA = lAP + lSW;

	while (lRefE > lRefA) {

		if (iFlag)		//	dY > dX 
			lX1 = lRefE;
		else
			lY1 = lRefE;

		if (TestFlaechenPunkt (pTop, pIOG2, pInitOG1, lX1, lY1)) {
			*lX = lX1;
			*lY = lY1;
			return true;
		}

		if (iFlag)		//	dY > dX 
			lX1 = lRefA;
		else
			lY1 = lRefA;

		if (TestFlaechenPunkt (pTop, pIOG2, pInitOG1, lX1, lY1)) {
			*lX = lX1;
			*lY = lY1;
			return true;
		}

		lRefE = lRefE - lSW;
		lRefA = lRefA + lSW;
	}
	return false;
}
//============================================================================
bool TestFlaechenPunkt ( IExtendTopRel2* pTop, IObjektGeometrie *pIOG2, IInitObjektGeometrie *pInitOG1,long lX, long lY)
{
	if (!pInitOG1 || !pIOG2)
		return false;

	COM_TRY {
		THROW_FAILED_HRESULT(pInitOG1 -> InitObjGeometry (lX, lY, OT_PUNKT));

	WObjektGeometrie OG1 (pInitOG1);
	Relat Rel;

		THROW_FAILED_HRESULT(pTop -> TopoRelationObjObj_Geom (pIOG2, OG1, &Rel));
		if (Rel == REL_INN)
			return true;

	} COM_CATCH_RETURN(false);
	return false;
}
//------------------------------------------------------------------------
//==================ContainerPunkt======================================
//============================================================================
Bool GetContainerPunkt (IExtendTopRel2* pTop, long lONr, CoordTransX *pCTF, double *dX, double *dY)
{
long Cont[4];
long MinX,MaxX,MinY,MaxY;

	*dY = 0.0;
	*dX = 0.0;

	DEX_GetObjContainer ( lONr, Cont[0]);

	MinX = Cont[0];
	MaxX = Cont[1];
	MinY = Cont[2];
	MaxY = Cont[3];

// Kurze Strecke suchen
long ldY = MaxY - MinY;
long ldX = MaxX - MinX;

long lX1 = MinX + ldX/2;
long lY1 = MinY + ldY/2;

long lAP;
long lEP;

short iFlag;

// Verh‰ltnis bestimmen
	if (ldY > ldX) {
		iFlag = true;
		lAP = MinX;
		lEP = MaxX;
	} else {
		iFlag = false;
		lAP = MinY;
		lEP = MaxY;
	}

	if (NULL == pTop || NULL == pCTF) 
		return false;

WObjektGeometrie OG1;
WObjektGeometrie OG2;
WInitObjektGeometrie InitOG2;
WInitObjektGeometrie InitOG1;

	COM_TRY {
	// GeometrieObjekte erzeugen
		THROW_FAILED_HRESULT(InitOG1.CreateInstance (CLSID_ObjektGeometrie));
		THROW_FAILED_HRESULT(InitOG2.CreateInstance (CLSID_ObjektGeometrie));

	// GeometrieObjekte initialisieren
		THROW_FAILED_HRESULT(InitOG1 -> InitObjGeometry (lX1, lY1, OT_PUNKT));
		OG1 = InitOG1;		// implizites QI, throws hr

		THROW_FAILED_HRESULT(InitOG2 -> InitObjGeometry (lONr));
		OG2 = InitOG2;		// implizites QI, thows hr

		Relat Rel;

		THROW_FAILED_HRESULT(pTop -> TopoRelationObjObj_Geom (OG2, OG1, &Rel));
		if (Rel == REL_INN){
			Punkt P (lX1, lY1);

			return pCTF -> UnScale (P, dX, dY);
		}
	} COM_CATCH_RETURN(false);

//	Neuen Punkt bestimmen

	long lTeiler = 4;
	long lRefX = lX1;
	long lRefY = lY1;

	if (BildeFlaechenPunkt (pTop, OG2, InitOG1, iFlag, lTeiler, lAP, lEP, &lX1, &lY1)) {
		Punkt P (lX1, lY1);
		return pCTF -> UnScale (P, dX, dY);
	}

	return false;
}
//------------------------------------------------------------------------
//==========================================================================
// ReferenzpunktY berechnen -----------------------------------------------
extern "C" char * _XTENSN_EXPORT PASCAL OPSchwerPunktY (long lONr, char *pBuffer, short iLen, DWORD pExt)
{
static long lCnt = 0;				// Objekte

	if (lONr == OBJPROP_RESET) {		// R¸cksetzen der akumulierten Werte
		lCnt = 0L;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {

		*pBuffer = '\0';
		return pBuffer;	

	} else if (lONr == OBJPROP_COUNT) {
#if defined(WIN32)
		ltoa (lCnt, pBuffer, 10);
#else
		ltoa (lCnt, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
	        return pBuffer;

	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDH_HELPRSPOINTY, &g_pTE -> RF()), MAXSTRING);
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;
//	} else if (lONr > 0) {
	} else if (lONr != 0L) {
		TX_ASSERT(NULL != pBuffer);

		short iOTyp = DEX_GetObjectType (lONr);
	
		*pBuffer = '\0';
		
		if (iOTyp != OGFlaeche ) 
			return pBuffer;

		double dX, dY;
		Bool Metric = TRUE;

		StatistExtension *pMyTE = (StatistExtension *)pExt;
		CoordTransX *pCTF = pMyTE->MyCTF();
		IExtendTopRel2 *pTop = pMyTE->MyTop();
		if ( !pTop)
				pMyTE->LadeTopRel();

		pTop = pMyTE->MyTop();


		if (iOTyp == OGFlaeche ) {	// Fl‰che = SchwerPunkt
		
			if (GetFlaechenPunkt (lONr, pCTF, &dX, &dY) ) {


				if ( pCTF != NULL )  {
					Metric = pCTF->isMetric();
#if _TRiAS_VER < 0x0400
					pCTF->Transform (&dX, &dY);
#endif
				}
	
//------------------Problem SWP innen/auﬂen - Korr. 18.11.97 -----------------------
//				if ( pTop ) {

//					ModFlaechenPunkt ( pTop, pCTF,lONr, &dX, &dY );
//				}
				
//----------------------------------------------------------------------------------

				
				if ( Metric ) {
#if defined(WIN32)
					ST_DtoA (pBuffer, "%9.4f", dY);
#else
					ST_DtoA (s_cbBuffer, "%9.4f", dY);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				} else {
#if defined(WIN32)
					ST_NoMtoA (pBuffer, TRUE, dX, dY, pCTF);
#else
					ST_NoMtoA (s_cbBuffer, TRUE, dX, dY, pCTF);
					memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
				}
		// Kumulative Werte berechnen
				lCnt++;
			}	
		}
	}

return pBuffer;
}
//------------------------------------------------------------------------
//--------------------------------------------------------------------
//	BegleitTextBestimmung

// BegleitText bereitstellen -----------------------------------------------
extern "C" char * _XTENSN_EXPORT PASCAL OPBegleitText (long lONr, char *pBuffer, short iLen)
{
static long lCnt = 0;				// Objekte

	if (lONr == OBJPROP_RESET) {		// R¸cksetzen der akumulierten Werte
		lCnt = 0L;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
		*pBuffer = '\0';
		return pBuffer;	

	} else if (lONr == OBJPROP_COUNT) {
#if defined(WIN32)
		ltoa (lCnt, pBuffer, 10);
#else
		ltoa (lCnt, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
	        return pBuffer;

	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDH_HELPRTEXT, &g_pTE -> RF()), MAXSTRING);
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;

//	} else if (lONr > 0) {
	} else if (lONr != 0L) {
		TX_ASSERT(NULL != pBuffer);
		short iOTyp = DEX_GetObjectType (lONr);
	
		*pBuffer = '\0';
		
		if (iOTyp == OGFlaeche || iOTyp == OGKO || iOTyp == OGLinie || iOTyp == OGPunkt || iOTyp == OGKreis) {	// Objekte, die BO haben
			long BONr = GetDescriptObject ( lONr ); 	// BegleitObjekt
			if ( BONr == 0L )
				 return pBuffer;
char *pBOText = new char [MCODESIZE + 1];
			if ( pBOText == NULL )
				 return pBuffer;
			*pBOText = '\0';

	TARGETMERKMAL gm;

			memset (&gm, '\0', sizeof (TARGETMERKMAL));
			gm.dwSize = sizeof(TARGETMERKMAL);
			gm.lTarget = BONr;		// ObjektNummer
			gm.lMCode = GetHeaderMCode ( ResID( IDT_HEADTEXTMCODE ,&g_pTE->RF()));
			gm.imaxLen = MCODESIZE;
			gm.pMText = pBOText;
			gm.iTTyp = TT_Objekt;

			if ( gm.lMCode != -1L ) {
				pBOText = DEX_GetTextMerkmal ( gm );
				if ( *pBOText != '\0' ) {
					memcpy (pBuffer, pBOText,MCODESIZE + 1);

	// Kumulative Werte berechnen
					lCnt++;
				}
			}
			DELETE_OBJ ( pBOText );
		}
	}

return pBuffer;
}
//------------------------------------------------------------------------
//--------------------------------------------------------------------
//	BegleitObjektBestimmung

// BegleitText bereitstellen -----------------------------------------------
extern "C" char * _XTENSN_EXPORT PASCAL OPBegleitObjekt (long lONr, char *pBuffer, short iLen)
{
static long lCnt = 0;				// Objekte

	if (lONr == OBJPROP_RESET) {		// R¸cksetzen der akumulierten Werte
		lCnt = 0L;
		return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
		*pBuffer = '\0';
		return pBuffer;	

	} else if (lONr == OBJPROP_COUNT) {
#if defined(WIN32)
		ltoa (lCnt, pBuffer, 10);
#else
		ltoa (lCnt, s_cbBuffer, 10);
		memcpy (pBuffer, s_cbBuffer, strlen (s_cbBuffer)+1);
#endif // WIN32
	        return pBuffer;

	} else if (lONr == OBJPROP_GETHELPTEXT) {	// HilfeText besorgen
	ResString resHelp (ResID (IDH_HELPROBJEKT, &g_pTE -> RF()), MAXSTRING);
		memcpy (pBuffer, resHelp.Addr(), strlen(resHelp.Addr())+1);
		return pBuffer;

//	} else if (lONr > 0) {
	} else if (lONr != 0L) {
		TX_ASSERT(NULL != pBuffer);
		short iOTyp = DEX_GetObjectType (lONr);
	
		*pBuffer = '\0';
		
		if (iOTyp == OGFlaeche || iOTyp == OGKO || iOTyp == OGLinie || iOTyp == OGPunkt || iOTyp == OGKreis) {	// Objekte, die BO haben

			long BONr = GetDescriptObject ( lONr ); 	// BegleitObjekt
			if ( BONr == 0L )
				 return pBuffer;

			char *pBOText = new char [MCODESIZE + 1];
			if ( pBOText == NULL )
				 return pBuffer;
			*pBOText = '\0';
			wsprintf ( pBOText,"%ld",BONr);
			memcpy (pBuffer, pBOText,MCODESIZE + 1);

			DELETE_OBJ ( pBOText );
		}
	}

return pBuffer;
}
//-----------------------------------------------------------------------
//------------------------------------------------------------------------
//	EinzelPunkt
short GetPunktParams (long lONr, double *pdX, double *pdY) 
{
	if ( pdX == NULL || pdY == NULL )
		return FALSE;

// allgemeine Info's zum Punkt ranholen
OBJSTATISTIK OS;
	memset (&OS,'\0',sizeof(OBJSTATISTIK));

	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr = lONr;
	if (!DEX_GetObjStatistik (OS))
		return FALSE;

	if (OS.iObjTyp == OT_PUNKT) {

		OBJGEOMETRIE OG;
		double *pX = new double [OS.lCnt];
		double *pY = new double [OS.lCnt];
    
		if (pX == NULL || pY == NULL) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			return FALSE;
		}

		memset (&OG,'\0',sizeof(OBJGEOMETRIE));
		OG.dwSize = sizeof(OBJGEOMETRIE);
		OG.lONr = lONr;
		OG.lCnt = OS.lCnt;
		OG.pdblX = pX;
		OG.pdblY = pY;
		OG.iFlags = OGConverted;
		if (DEX_GetObjGeometrie (OG)) {

			if (pdX) *pdX = *pX;
			if (pdY) *pdY = *pY;
		}

	// aufr‰umen
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
	}

	if (OS.iObjTyp == OT_TEXT) {

		OBJGEOMETRIE OG;
		double *pX = new double [OS.lCnt];
		double *pY = new double [OS.lCnt];
    
		if (pX == NULL || pY == NULL) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			return FALSE;
		}

		memset (&OG,'\0',sizeof(OBJGEOMETRIE));
		OG.dwSize = sizeof(OBJGEOMETRIE);
		OG.lONr = lONr;
		OG.lCnt = OS.lCnt;
		OG.pdblX = pX;
		OG.pdblY = pY;
		OG.iFlags = OGConverted;
		if (DEX_GetObjGeometrie (OG)) {

			if (pdX) *pdX = *pX;
			if (pdY) *pdY = *pY;
		}

	// aufr‰umen
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
	}

return TRUE;
}	
//------------------------------------------------------------------------
//----------------Koordinaten besorgen und bearbeiten---------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
Bool HoleFlaechenInformation (long lONr, CoordTransX *pCTF, long lCnt, short iKCnt, double *pDX , double *pDY , long *pK, bool iVerarb)
{

	Bool Flag = false;

	if ( !pDX || !pDY )
		return Flag;

#if _TRiAS_VER < 0x0400
	long *pX = new long [lCnt];
	long *pY = new long [lCnt];
#else
	double *pX = new double [lCnt];
	double *pY = new double [lCnt];
#endif

	if (pX == NULL || pY == NULL || pK == NULL) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return Flag;
	}

	OBJGEOMETRIE OG;
	memset (&OG,'\0',sizeof(OBJGEOMETRIE));
	OG.dwSize = sizeof(OBJGEOMETRIE);
	OG.lONr = lONr;
	OG.lCnt = lCnt;
	OG.iKCnt = iKCnt;
	OG.pdblX = pX;
	OG.pdblY = pY;
	OG.plCnt = pK;
#if _TRiAS_VER < 0x0400
	OG.iFlags = ~OGConverted;
#else
	OG.iFlags = OGConverted;
#endif

	if (DEX_GetObjGeometrie (OG)) {

		{
		StatistTrfVect TrfV ( pCTF, pX, pY, lCnt );
			if ( iVerarb )
				TrfV.FromDBToMetric (pDX,pDY);
			else
				TrfV.FromDBToASC (pDX,pDY);
		}

		if ( pDX && pDY ) {
			Flag = true;
//		} else {
//			DELETE_OBJ ( pDX);
//			DELETE_OBJ ( pDY);
		}
	}

	DELETE_OBJ (pX);
	DELETE_OBJ (pY);
	return Flag;
}
//--------------------------------------------------------------------------
Bool HoleLinienInformation (long lONr, CoordTransX *pCTF, long lCnt, double *pDX , double *pDY )
{

	Bool Flag = false;

#if _TRiAS_VER < 0x0400
	long *pX = new long [lCnt];
	long *pY = new long [lCnt];
#else
	double *pX = new double [lCnt];
	double *pY = new double [lCnt];
#endif

	if (pX == NULL || pY == NULL ) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return Flag;
	}

	OBJGEOMETRIE OG;

	memset (&OG,'\0',sizeof(OBJGEOMETRIE));
	OG.dwSize = sizeof(OBJGEOMETRIE);
	OG.lONr = lONr;
	OG.lCnt = lCnt;
	OG.pdblX = pX;
	OG.pdblY = pY;

#if _TRiAS_VER < 0x0400
	OG.iFlags = ~OGConverted;
#else
	OG.iFlags = OGConverted;
#endif

	if (DEX_GetObjGeometrie (OG)) {


	//------------------------CoordTrans---------------	
	
		{
		StatistTrfVect TrfV ( pCTF, pX, pY, lCnt );
//			TrfV.FromDBToMetric (pDX,pDY);
			TrfV.FromDBToASC (pDX,pDY);
		}

		if ( pDX && pDY ) {
			Flag = true;
		} else {
			DELETE_OBJ ( pDX);
			DELETE_OBJ ( pDY);
		}
	}

	DELETE_OBJ (pX);
	DELETE_OBJ (pY);

	return Flag;
}
//--------------------------------------------------------------------------
//----------------------------------------------------------------------------
//-------------Fl‰chenberechnung---------------------------------------------
double GetAreaObject ( double *pX, double *pY, long * pK,
		       long Count, short Kount ,double *SX, double *SY ) 
{


long i, j, K;
double FL = 0.0, FLS = 0.0;
double SSX,SSY;		// Vielleicht wird es noch gebraucht
	K = *pK;

	FLS = GetAreaObjectPart ( pX, pY, K ,SX, SY );		// Auﬂenrahmen

	if ( Kount == 1 ) return FLS;	// Keine Lˆcher
	j = 0;
	for ( i = 1; i < Kount ; i++ ) {
		FL = 0.0;
		j = j + K;
		K = * (pK+i);	// Koordinatenanzahl
		FL = GetAreaObjectPart ( pX+j, pY+j, K, &SSX, &SSY);
		FLS = FLS - FL;		// Lˆcher abziehen
	}
	return FLS;
}

//----------------Teilfl‰chenberechnung--------------------------------------
double GetAreaObjectPart ( double *pX, double *pY, long K,
		       double *SX, double *SY ) 
{


double *pX1,*pY1;
long i;
double FL = 0.0;

double * pXX, *pYY;
	
	FL = *(pX + K - 1 ) * (*(pY + 1) -  *(pY + K - 2 )); 

	pXX = pX;
	pX1 = pX + 1;
	pYY = pY;
	pY1 = pY + 1;
	*SX = 0.0;
	*SY = 0.0;

	for ( i = 1 ; i < K ; i++ )  {
//	Fl‰che
		  if ( i < K - 1 )
		 	  FL = FL + *(pX + i ) * ( *(pY + i + 1 ) - *(pY + i - 1 ));
	
		  *SX = *SX + *pXX;
		  *SY = *SY + *pYY;

		  pXX = pX1 ;
		  pX1 = pX1 + 1;
		  pYY = pY1;
		  pY1 = pY1 + 1;
	}

	FL = fabs ( FL / 2.) ;

	TX_ASSERT ( 0.0 != FL);

	return FL;
}
//-----------------------------------------------------------------------
void SetCoordinate ( double *pX, double *pY, CoordTransX *pCTF)
{
	if ( !pCTF)
		return;

	long K = 1L;
/*-----------
	StatistTrfVect TrfV ( pCTF, pX, pY, K );
	Bool Metric = TrfV.isDBMetric();
	if ( !Metric) {	
		TrfV.FromMetricToAsc ();
		TrfV.GetKoord( pX, pY );
	}
---------------------------------------------*/
	return;

}
//---------------------------------------------------------------------
char * PASCAL ST_NoMtoA ( LPSTR String, Bool flag, double WertX, double WertY, CoordTransX *pCTF)
{

	long *pContainer = new long[4];
	*pContainer = (long) WertX;
	*(pContainer+3) = (long) WertY;   
	char *pText;
	StatistTrfKoord Trf ( pCTF, pContainer );
	if ( !flag ) {
		pText = Trf.TransToLoR ();
		if ( pText)
			strcpy (String,pText);
	} else {
		pText = Trf.TransToLoH();
		if ( pText)
			strcpy (String,pText);      
			
	}  
	return String;
}

//----------------Linienberechnung--------------------------------------
double GetPolyLen ( CoordTransX *pCTF, double *pX, double *pY, long Count,
		       double *SX, double *SY ) 
{ 

double polylen =0.0;
long i,j;
double *pX1,*pY1,*pXX,*pYY;

double Xa,Ya,Xe,Ye;

	DoublePair AP,EP;

	pXX = pX;
	pX1 = pX + 1;
	pYY = pY;
	pY1 = pY + 1;

	Xa = *pXX;
	Xe = *pX1;
	Ya = *pYY;
	Ye = *pY1;

	AP = DoublePair ( Xa, Ya);
	EP = DoublePair ( Xe, Ye);

	for ( i = 1 ; i < Count ; i++ )  {


		AP = DoublePair ( Xa, Ya);
		EP = DoublePair ( Xe, Ye);

//		  polylen = polylen + sqrt ( ( *pX1 - *pXX ) * ( *pX1 - *pXX ) +( *pY1 - *pYY ) * ( *pY1 - *pYY ) );
		  polylen = polylen + pCTF->CoordTransDistance(&AP,&EP);

		if ( i < Count - 1 ) {
			  pXX = pX1 ;
			  pX1 = pX1 + 1;
			  pYY = pY1;
			  pY1 = pY1 + 1;

			Xa = *pXX;
			Xe = *pX1;
			Ya = *pYY;
			Ye = *pY1;
		}
	}
	if ( Count == 2 ) {
		*SX = (*pX + *( pX+1 ))/2.0;
		*SY = (*pY + *( pY+1 ))/2.0;
	} else {
		j = Count/2;
		*SX = *(pX+j);
		*SY = *(pY+j);
	}

	return polylen;
}
//----------------Relationen enumerieren -------------------------------
short GetNumberSecObjects ( long lONr )
{
short Number = 0;
ENUMRELATIONOBJS EREL;
	memset ( &EREL, '\0', sizeof (EREL) );
	EREL.dwSize = sizeof(EREL);
	EREL.lONr = lONr;
	EREL.lRCode = -1;
	EREL.iRTyp = RTKomplexU;	// O ist Prim‰robjekt
	EREL.eFcn = (ENUMRELOBJPROC) NumberSecObjects;
	EREL.pData = &Number;
	DEX_EnumRelationObjects( EREL );

return Number;
}
//-------------------------------------------------------------------
short GetSecObjects ( long lONr, long *pObj )
{
short Number;
ENUMRELATIONOBJS EREL;
	memset ( &EREL, '\0', sizeof (EREL) );
	EREL.dwSize = sizeof(EREL);
	EREL.lONr = lONr;
	EREL.lRCode = -1;
	EREL.iRTyp = RTKomplexU;	// O ist Prim‰robjekt
	EREL.eFcn = (ENUMRELOBJPROC) SecObjects;
	EREL.pData = pObj;
	*pObj = 0;
	DEX_EnumRelationObjects( EREL );
	Number = ( short ) *pObj;
return Number;
}
//----------------------------------------------------------------
long GetDescriptObject ( long lONr )
{
long BONr = 0L;
ENUMRELATIONOBJS EREL;
	memset ( &EREL, '\0', sizeof (EREL) );
	EREL.dwSize = sizeof(EREL);
	EREL.lONr = lONr;
	EREL.lRCode = -1;
	EREL.iRTyp = RTBegleitO;	// O ist Prim‰robjekt
	EREL.eFcn = (ENUMRELOBJPROC) DescriptObject;
	EREL.pData = &BONr;
	DEX_EnumRelationObjects( EREL );
return BONr;
}
// SchlÅssel Datenbankheader besorgen
//-------------------------------------------------------------------
long GetHeaderMCode ( ResID resID)
{
GEODBHDRENTRY hdrEntry;
long result = -1L;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, ResString (resID, 17), 16);
	hdrEntry.lphdrText = new char [MCODESIZE +1];
	hdrEntry.hdrTextLen = MCODESIZE;

	if (DEX_ReadGeoDBHdrEntry (hdrEntry) == EC_OKAY) {
	// HeaderEintrag existiert
		result = atol (hdrEntry.lphdrText);
	}
	DELETE_OBJ (hdrEntry.lphdrText);

return result;
}


// Objekte einer Relation z‰hlen -----------------------------------------------
extern "C" Bool PASCAL _XTENSN_EXPORT  NumberSecObjects(long lONr, long IRCode, short iRTyp, void *pData)
{
	(*( short * )pData)++;
	return TRUE;
}
// Objekte einer Relation ausgeben -----------------------------------------------
extern "C" Bool PASCAL _XTENSN_EXPORT  SecObjects(long lONr, long IRCode, short iRTyp, void *pData)
{
	(* (long *)pData)++;
	(* ((long *)pData + *(long *)pData )) = lONr;
	return TRUE;
}
// Objekte einer Relation ausgeben -----------------------------------------------
extern "C" Bool PASCAL _XTENSN_EXPORT  DescriptObject(long lONr, long IRCode, short iRTyp, void *pData)
{
	(* (long *)pData) = lONr;
	return TRUE;
}
