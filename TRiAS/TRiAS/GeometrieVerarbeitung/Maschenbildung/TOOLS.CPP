/*
File: TOOLS.CPP
Das Modul beinhaltet allgemeine Funktionen zur Kommunikation mit TRIAS

Erarbeitet: J. Benkenstein                                     Stand vom 14.10.1996
*/

#include "pheader.h"			// vorübers. Header

#include "resource.h"			// Resource-Konstanten

#include <xtensnn.h>			// DEXN_PBDMCodeChanged
#include <errinstx.hxx>			// ErrInstall
#include <iunredo.hxx>			// LPUNDOREDOPBDDATA
#include <Hdrentrx.hxx>			// HeaderEntryX

//	GUID-Header
#include <xtsnguid.h>
#include <initguid.h>           
#include <undoguid.h>			// CLSID_UndoRedoObject

//	allg. Header
#include <math.h>				//	fabs ()

//	Projekt-Header
#include "tools.hpp"			// zugeh. Header


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//  Konstanten
const short KurzTextLen = 32;   		// max. Länge eines KurzTextes
const short LangTextLen = 80;   		// max. Länge eines LangTextes
const char LinverText [] = "LinVer_";	// UniqueIdent-Vorspann 

//	globale Variablen
//extern CTriasExtension *g_pTE;	// Deklaration nicht nötig


// --------------------------------------------------------------------------------------------
//  UniqueIdent für ein bestimmtes Objekt ausgeben
ErrCode OutputUniqueIdent (long lObjNr, ULONG ulMCode) 
{
	ASSERT (lObjNr > 0);
	ASSERT (0 != ulMCode);
	ASSERT ((ULONG)-1 != ulMCode);
	
	char Buffer [sizeof (LinverText) + 15] = "";
	lstrcpy (Buffer, LinverText);
	ltoa (lObjNr, &Buffer [lstrlen (Buffer)], 10);		// Nummer anhängen
	return OutputMerkmal (lObjNr, ulMCode, Buffer);		// Merkmal ausgeben
}


// --------------------------------------------------------------------------------------------
//  Merkmal für ein bestimmtes Objekt ausgeben
ErrCode OutputMerkmal (ULONG lObjNummer, ULONG MerkmalsKode, const char *pMerkmalsText) 
{
	ASSERT (0 != MerkmalsKode);
	ASSERT ((ULONG)-1 != MerkmalsKode);

#if _MSC_VER >= 1200	// #WM990709
HPROJECT hPr = DEX_GetObjectProject (lObjNummer);

	if (DEX_GetROModeFeatureEx (hPr, MerkmalsKode))	// Objekteigenschaft schreibgeschützt
	{
		DEX_Error (RC_Maschenbildung, WC_FEATURE_ISRO);	// wegen Malaysia temporär herausgenommen (30.07.-16.09.99)
		return WC_FEATURE_ISRO;
	}
#endif // _MSC_VER >= 1200

	ASSERT (lObjNummer > 0);
	ASSERT ((NULL != pMerkmalsText) && AfxIsValidString (pMerkmalsText));
	ASSERT (strlen (pMerkmalsText) > 0);

	TARGETMERKMALEX TM;
	memset (&TM, 0, sizeof (TARGETMERKMALEX));              // init.
	TM.dwSize = sizeof (TARGETMERKMALEX);
	TM.lTarget = lObjNummer;
	TM.lMCode = MerkmalsKode;
	TM.imaxLen = lstrlen (pMerkmalsText);
	TM.iTTyp = TT_Objekt;
	TM.pMText = (char *) pMerkmalsText;         
	TM.iFlags = TMNoCaching;

//	Undo implementieren
	LPTRIASXTENSIONSITE pXtsnSite = NULL;
	HRESULT hr = g_pTE -> GetXtensionSite (&pXtsnSite);
	ASSERT (NULL != pXtsnSite);
	LPUNDOREDOOBJECTFEATURE pIUndo = NULL;

	ErrCode EC = EC_OKAY;
	if (SUCCEEDED(hr)) 
	{
		hr = pXtsnSite -> CreateInstance (NULL, CLSID_UndoRedoObject, 
										  IID_IUndoRedoObjectFeature, (LPVOID *)&pIUndo);
		pXtsnSite -> Release();
		if (SUCCEEDED(hr))
			hr = pIUndo -> Init (lObjNummer, MerkmalsKode, pMerkmalsText, NULL);
						
		if (FAILED(hr)) 
		{
			pIUndo -> Release();
			pIUndo = NULL;
		}
	
		EC = DEX_ModTextMerkmal (TM);
		if (EC_OKAY == EC) 
		{
			if (pIUndo) 
				DEX_AddUndoRedo (pIUndo);
		}
		if (pIUndo) 
			pIUndo -> Release();
	}

	return EC;
}


// --------------------------------------------------------------------------------------------
//	Merkmal für ein bestimmtes Objekt lesen
char *GetTextMerkmal (long lObjNr, ULONG ulMK, char *pText, short sMaxLen)
{
	ASSERT (lObjNr > 0);
	ASSERT (0 != ulMK);
	ASSERT ((ULONG)-1 != ulMK);
	ASSERT (NULL != pText);
	ASSERT (sMaxLen > 0);

	TARGETMERKMAL TM;
	memset (&TM, 0, sizeof (TARGETMERKMAL));              // init.
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = lObjNr;
	TM.lMCode = ulMK;
	TM.imaxLen = sMaxLen;
	TM.iTTyp = TT_Objekt;
	TM.pMText = pText;         
	
	return DEX_GetTextMerkmal (TM);
}


// --------------------------------------------------------------------------------------------
//  neues Merkmal in der PBD erzeugen
//  (falls noch nicht vorhanden)
ErrCode CreateMerkmal (LONG lIdent, ULONG MK, char *pText, short MaxLen, BOOL bSystemMerkmal,
					   BOOL bReadOnly) 
{
	ASSERT (0 != MK);
	ASSERT ((ULONG)-1 != MK);

#if _MSC_VER >= 1200	// #WM990707
HPROJECT hPr = DEX_GetObjectsProject (lIdent);

	if (DEX_GetROModeFeatureEx (hPr, MK))	// Objekteigenschaft schreibgeschützt
	{
		DEX_Error (RC_Maschenbildung, WC_FEATURE_ISRO);	// wegen Malaysia temporär herausgenommen (30.07.-16.09.99)
		return WC_FEATURE_ISRO;
	}
#endif // _MSC_VER >= 1200

	ASSERT ((NULL != pText) && AfxIsValidString (pText));
	ASSERT (strlen (pText) > 0);
	ASSERT (MaxLen > 0);

//  Fehlermeldung von TRIAS ausschalten
	ErrInstall E1 (WC_NOMERKMAL);

	PBDMERKMALEX Data;
	memset (&Data, '\0', sizeof (PBDMERKMALEX));  // init.
	Data.dwSize = sizeof (PBDMERKMALEX);
	Data.pbdTyp = 'm';                          // Merkmal
	Data.pbdCode = MK;
	Data.lIdent = lIdent;
	ErrCode EC = DEX_GetPBDData (Data);

	if (EC == EC_OKAY && MaxLen <= Data.ipbdMLen)   // wenn bereits vorh.
		return EC_OKAY;                             // dann zurück

	if (EC != EC_OKAY) {            // wenn noch nicht vorh.
	//  Text ggf. trimmen
		short Len = 0;
		while (((Len = lstrlen (pText)) > 0) && (*(pText + Len - 1) == ' '))
			*(pText + Len - 1) = '\0';

	//  LangText setzen
		Len = lstrlen (pText);
		if (Len > LangTextLen)                             	// LangText ggf. begrenzen
			*(pText + LangTextLen) = '\0';
		Data.pbdLTextLen = Len;
		Data.pbdLText = pText;

	//  KurzText setzen
		Len = lstrlen (pText);
		if (Len > KurzTextLen)                             	// KurzText ggf. begrenzen
			*(pText + KurzTextLen) = '\0';
		Data.pbdKTextLen = Len;
		Data.pbdKText = pText;
		Data.ipbdMTyp = 'a';                               	// Objekt-Merkmal
		if (bSystemMerkmal)
			Data.ipbdMTyp |= PBDMERKMAL_SYSTEMFLAG;
		if (bReadOnly)
			Data.ipbdMTyp |= PBDMERKMAL_READONLY;
	}

//  diese Länge ggf. vergrößern
	Data.ipbdMLen = MaxLen;                              	// max. Länge des Merkmals

//	Undo implementieren
	LPTRIASXTENSIONSITE pXtsnSite = NULL;
	HRESULT hr = g_pTE -> GetXtensionSite (&pXtsnSite);
	ASSERT (NULL != pXtsnSite);
	LPUNDOREDOPBDDATA pIUndo = NULL;

	if (SUCCEEDED(hr)) 
	{
		hr = pXtsnSite -> CreateInstance (NULL, CLSID_UndoRedoObject, 
										  IID_IUndoRedoPBDData, (LPVOID *)&pIUndo);
		pXtsnSite -> Release();
		if (SUCCEEDED(hr))
			hr = pIUndo -> InitModify ((const PBDDATA *)&Data, NULL);
		if (FAILED(hr)) 
		{
			pIUndo -> Release();
			pIUndo = NULL;
		}
	
		EC = DEX_ModPBDData (Data);
		if (EC_OKAY == EC) 
		{
			if (pIUndo) 
				DEX_AddUndoRedo (pIUndo);
		}
		if (pIUndo) 
			pIUndo -> Release();
	}

	if (EC == EC_OKAY)
		DEXN_PBDMCodeChanged (MK);
	return EC;
}



// --------------------------------------------------------------------------------------------
//	Repräsentiert das übergebene Objekt eine Fläche ?
BOOL IsFlaeche (long *pX, long *pY, long lCnt)
{
	ASSERT ((NULL != pX) && (NULL != pY));
	return ((lCnt >= MinAreaVerticeCnt) && (pX[0]==pX[lCnt-1]) && (pY[0]==pY[lCnt-1]));
}

//	Repräsentiert das übergebene Objekt eine Fläche ?
BOOL IsFlaeche (double *pdX, double *pdY, long lCnt)
{
	ASSERT ((NULL != pdX) && (NULL != pdY));
	return ((lCnt >= MinAreaVerticeCnt) && (pdX[0]==pdX[lCnt-1]) && (pdY[0]==pdY[lCnt-1]));
}

//	berechne vorzeichenbehafteten Inhalt einer Fläche:
//	+/- --> math. positiver/negativer Umlaufsinn
double FlaechenInhalt (long *plX, long *plY, long lCnt)
{
//	prüfe übergebene Zeiger
	ASSERT ((NULL != plX) && (NULL != plY));
	
	if (!IsFlaeche (plX, plY, lCnt))
		return 0;

//	berechne Anfangswert der Fläche
	double dInhalt = (double)plX [lCnt-1] * ((double)(plY [1] - plY [lCnt-2]));

//	berechne Summe
	for (long i = 1; i < lCnt - 1; i++)
		dInhalt += (double)plX [i] * ((double)(plY [i+1] - plY [i-1]));

	return (dInhalt / 2.0);        // Inhalt halbieren und zurück
}


// --------------------------------------------------------------------------------------------
double FlaechenInhalt (double *pdX, double *pdY, long lCnt)
{
//	prüfe übergebene Zeiger
	ASSERT ((NULL != pdX) && (NULL != pdY));
	
	if (!IsFlaeche (pdX, pdY, lCnt))
		return 0;

//	berechne Anfangswert der Fläche
	double dInhalt = pdX [lCnt-1] * (pdY [1] - pdY [lCnt-2]);
	
//	berechne Summe
	for (long i = 1; i < lCnt - 1; i++)
		dInhalt += pdX [i] * (pdY [i+1] - pdY [i-1]);

	return (dInhalt / 2.0);        // Inhalt halbieren und zurück
}


// --------------------------------------------------------------------------------------------
//	Merkmalskode und Systemmerkmal erzeugen
LONG GetMerkmalsKode (LONG lONr, UINT uiHdrEntry, UINT uiPbdEntry, BOOL fSystem, BOOL fRO) 
{
	CString hdr; 
	VERIFY(hdr.LoadString(uiHdrEntry));
	LONG lMCode = 0;
	HPROJECT hPr = DEX_GetObjectProject(lONr);
	HeaderEntryX HD (hdr, hPr);
	if (HD.Status () != HE_INVALID)
		lMCode = HD.EntryLong(0L);
	else
	{
	//  sonst neuen Eintrag erzeugen und speichern
		char cbBuffer [20] = "";
//		lMCode = DEX_GetUniqueSysMCodeEx(hPr);
		lMCode = DEX_GetUniqueSysMCode();		// #WM990607
		ultoa (lMCode, cbBuffer, 10);
		HD.SetEntryText (cbBuffer);
		HD.Flags() = HEADER_SYSTEMRO;
		if (HD.WriteBack() != EC_OKAY)  // Wert speichern
			return 0;
	}

//	und in Pbd erzeugen
	CString strPbd; 
	VERIFY(strPbd.LoadString(uiPbdEntry));
	long lIdent = DEX_GetObjIdent(lONr);
	return EC_OKAY == CreateMerkmal (lIdent, lMCode, (char *)(const char*)strPbd, 32, fSystem,
									 fRO) ? lMCode : 0;
		
/*
PBDMERKMAL pbd;
CString strPbd; 

	VERIFY(strPbd.LoadString(IDS_MARKOBJECT_PBD));
	INITSTRUCT(pbd, PBDMERKMAL);
	pbd.pbdTyp = 'm';
	pbd.pbdCode = lMCode;
	pbd.pbdKText = (LPSTR)(LPCSTR)strPbd;
	pbd.pbdKTextLen = strPbd.GetLength();
	pbd.ipbdMTyp = 'a' | PBDMERKMAL_SYSTEMFLAG;		// Objektmerkmal + systemintern
	pbd.ipbdMLen = 32;

BOOL fResult = (EC_OKAY == DEX_ModPBDData(pbd)) ? TRUE : FALSE;

	if (fResult)
		DEXN_PBDMCodeChanged(lMCode);

	return lMCode;
*/
}


// --------------------------------------------------------------------------------------------
// Wert zwischen 0 und 360, der nicht gleich dem Winkel ist, den eine Strecke mit der
// Waagrechten bildet, der jedoch die gleiche Ordnungseigenschaft wie dieser Winkel besitzt
double QuasiWinkel (double &dXa, double &dYa, double &dXe, double &dYe)
{
double dx, dy, ax, ay;
double t;

	dx = dXe - dXa;
	ax = fabs(dx);
	dy = dYe - dYa;
	ay = fabs(dy);
	t = (ax+ay == 0) ? 0.0 : dy / (ax+ay);
	if (dx < 0)
		t = 2 - t;
	else
		if (dy < 0)
			t = 4 + t;
	return t * 90.0;
}


// --------------------------------------------------------------------------------------------
// Kurztext für Code ulCode (IdentCode, MerkmalsCode, ReltCode) des Typs iType
// ('i' - Identifikator, 'm' - Merkmal, 'r' - Relation) ermitteln (#WM990616)
BOOL GetKurzText (ULONG ulCode, short iType, CString& strKText)
{
	strKText = "";	// für den Fehlerfall

PBDDATA PD;

	INITSTRUCT(PD, PBDDATA);		// Initialisierung
	PD.pbdTyp = iType;				// Typ: 'i' - Identifikator, 'm' - Merkmal, 'r' - Relation
	PD.pbdCode = ulCode;			// IdentCode, MerkmalsCode, RelatCode
	PD.pbdKText = new char[KurzTextLen];

	if (! PD.pbdKText)
	{
		DEX_Error (RC_Maschenbildung, EC_NOMEMORY);
		return FALSE;
	}

	memset (PD.pbdKText, '\0', KurzTextLen); // Initialisierung
	PD.pbdKTextLen = KurzTextLen;

ErrCode EC = DEX_GetPBDData (PD);

	if (EC_OKAY != EC)
		return FALSE;

	strKText = PD.pbdKText;
	DELETE_VEC (PD.pbdKText);

	return TRUE;

} // GetKurzText


// --------------------------------------------------------------------------------------------
// 2 Strecken (lX11,lY11)-(lX21,lY21) und (lX12,lY12)-(lX22,lY22) haben wenigstens einen Punkt
// gemeinsam; dann Rückageb von TRUE
BOOL Intersection (long lX11, long lY11, long lX21, long lY21, long lX12, long lY12, long lX22,
				   long lY22)
{
	return ((TurnDirection (lX11, lY11, lX21, lY21, lX12, lY12) *
			 TurnDirection (lX11, lY11, lX21, lY21, lX22, lY22)) <= 0) &&
			((TurnDirection (lX12, lY12, lX22, lY22, lX11, lY11) *
			  TurnDirection (lX12, lY12, lX22, lY22, lX21, lY21)) <= 0);
}


// --------------------------------------------------------------------------------------------
// Bewegungsrichtung, wenn man bei 3 gegebenen Punkten P1(lX1,lY1), P2(lX2,lY2) und P3(lX3,lY3)
// vom ersten, zum zweiten und dann zum dritten geht; return-Werte sind
// +1 bei Drehung im mathem. pos. Sinn (gegen Uhrzeigersinn) bzw. 
//    bei Kollinearität, wenn P2 zwischen P1 und P3 liegt bzw.
//    bei P1 == P2
// -1 bei Drehung im mathem. neg. Sinn (im Uhrzeigersinn) bzw.
//    bei Kollinearität, wenn P1 zwischen P3 und P2 liegt
//  0 bei Kollinearität, wenn P3 zwischen P1 und P2 liegt bzw.
//    bei P1 == P3, P2 == P3, P1 == P2 == P3
int TurnDirection (long lX1, long lY1, long lX2, long lY2, long lX3, long lY3)
{
double dx1 = lX2 - lX1;
double dy1 = lY2 - lY1;
double dx2 = lX3 - lX1;
double dy2 = lY3 - lY1;

	if (dx1*dy2 > dy1*dx2)
		return +1;
	if (dx1*dy2 < dy1*dx2)
		return -1;
	if (dx1*dx2 < 0 || dy1*dy2 < 0)
		return -1;
	if (dx1*dx1+dy1*dy1 < dx2*dx2+dy2*dy2)
		return +1;
	return 0;

} // TurnDirection
