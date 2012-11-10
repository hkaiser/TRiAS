#include "stdafx.h"

#include "resource.h"
#include "del.hpp"
#include "helper.h"

extern CTextExt* g_pTextExt;
// Fkt. erhalten Textobj. die abgehängt werden
//---------------------------------------------------------------------

// für Obj. "Erzeugen" , dann auf Wunsch abhängen 

extern "C"
{

BOOL FAR PASCAL _XTENSN_EXPORT EnumRelObj (long lTxtONr, long lRCode, short iRTyp, void *pData)
{
	ASSERT (lTxtONr);

DELRELATION DR;	                            
OBJSTATISTIK OS;
SObj *pstOb = (SObj*)pData;                             
	ASSERT (pstOb);

HWND ORhWnd;	

	if(pstOb -> iState == FOUND) return TRUE;

	memset((void*)&OS, 0, sizeof(OBJSTATISTIK));
	OS.dwSize	= sizeof(OBJSTATISTIK);	// Größe dieser Struktur
	OS.lONr		= lTxtONr;// ObjektNummer
	if (!DEX_GetObjStatistik(OS)) return FALSE; 
			              
	if (OS.iObjTyp != OGText) return TRUE;	            
	
	DR.dwSize = sizeof(DELRELATION);
	DR.lPONr = pstOb->lObNr;		// PrimärObjekt
	DR.lSONr = lTxtONr;		// SekundärObjekt
	DR.lRCode = -1L;		// RelationsCode
	DR.iRTyp = RTBegleitO;		// RelationsTyp
	
    DEX_DeleteRelation(DR);
    
    if (pstOb -> bObLoesch) {
    	ORhWnd = g_pTextExt -> m_hWnd;
        if (ORhWnd != 0 )
    		DEXOR_DeleteObject(ORhWnd, lTxtONr);
    	else
            DEX_DeleteObject(lTxtONr);
        }                     
        
	pstOb -> iState = FOUND;        
return TRUE;
}	                              

BOOL FAR PASCAL _XTENSN_EXPORT EnumRelObjRename (long lTxtONr, long lRCode, short iRTyp, void *pData)
{
	ASSERT (lTxtONr);

SEnObj *pstEnObj = (SEnObj*)pData;	
	
	if (pstEnObj == NULL)
		ASSERT (0);
						
/* nur erstes Textobjekt umbenennen*/
	if(pstEnObj -> iState == FOUND) return TRUE;
/* liefern der Objektstatistik zur Ueberpruefung, ob angehaengtes Obj. TEXTOBJ.*/
OBJSTATISTIK OSRELAT;                   
	memset((void*)&OSRELAT, 0, sizeof(OBJSTATISTIK));
	OSRELAT.dwSize	= sizeof(OBJSTATISTIK);	// Größe dieser Struktur
	OSRELAT.lONr		= lTxtONr;// ObjektNummer
	if (!DEX_GetObjStatistik(OSRELAT)) return FALSE; 

	if (OSRELAT.iObjTyp != OGText) return TRUE;	            

DelPointer PLoesch;
short iKAnz = OSRELAT.iKCnt;
	if (iKAnz == 0) iKAnz = 1;	
long* pY = new long[OSRELAT.lCnt];
long* pX = new long[OSRELAT.lCnt];
long* pK = new long[iKAnz];
	if (pY == NULL || pX == NULL || pK == NULL) return FALSE;		    

/* liefern der Objektgeometrie des ersten enum. Textobjektes */
/* zum Zuweisen der Koordinaten fuer neues Textobjekt und nicht (wie sonst) */
/* Zuweisen der Geom. des Bezugsobjektes */			
OBJGEOMETRIE OG;
	OG.dwSize   = sizeof(OBJGEOMETRIE);			
	OG.lONr     = lTxtONr;			// ObjektNummer
	OG.lIdent   = OSRELAT.lIdent;	// Identifikator
	OG.iObjTyp	= OGText; 	   	// ObjektTyp (Punkt, Kante, Fläche, ...)
	OG.iFlags	= OSRELAT.iFlags;     // double Koordinate
// neue Geometrie :
	OG.lCnt	    = OSRELAT.lCnt; // Gesamtanzahl der Stützpunkte (Größe der KoordFelder)
	OG.iKCnt	= iKAnz;	// Größe des KonturFeldes
	OG.pdblX	= pX;	// KoordinatenFelder (double */ *)
	OG.pdblY    = pY;
	OG.plCnt	= pK;	// Anzahl der Stützpunkte in Konturen
	OG.iKCnt = 0;
	OG.plCnt = NULL;
	if(!DEX_GetObjGeometrie(OG)) {
		PLoesch.Del(pX,pY,pK);
		return FALSE;
	}

CString CBuffer;
char* pcBuffer = NULL;
	
	TRY {                                       
		pcBuffer = CBuffer.GetBuffer(STRLENGTH);
	}
	CATCH ( CMemoryException, e ) {
		DEX_Error (0, EC_NOMEMORY); 
	}                  
	END_CATCH

CBuffer = pstEnObj -> sTxt;

// Wenn Text nicht selbst generiert, hole für Objekt das Textmerkmal vom Bezugsobjekt
TARGETMERKMAL TM;

	if (!g_pTextExt  -> m_pHelper -> TestTextContents (pcBuffer)) {
		TM.dwSize = sizeof(TARGETMERKMAL);
		TM.lTarget = pstEnObj -> lObjNr;		// ObjektNummer/Identifikator oder char * (SichtName)
		TM.lMCode = pstEnObj -> lMerkCd;		// MerkmalsCode
		TM.pMText = pcBuffer;		// zu lieferndes TextMerkmal 
		TM.imaxLen = STRLENGTH; 		// max Textlänge
		TM.iTTyp = TT_Objekt;		// OBL, IDL oder SICHT			
		if(!DEX_GetTextMerkmal(TM) || *pcBuffer == '0') {
			CBuffer.ReleaseBuffer();
			PLoesch.Del(pX,pY,pK);                              
			return TRUE;         
		}
	}		
	if (!g_pTextExt  -> m_pHelper -> TestTextContents (pcBuffer))
		return TRUE;			

// dieses schon angehaengte Textobjekt abhaengen und loeschen
DELRELATION DR;	                            
	DR.dwSize = sizeof(DELRELATION);
	DR.lPONr = pstEnObj -> lObjNr;		// PrimärObjekt
	DR.lSONr = lTxtONr;		// SekundärObjekt
	DR.lRCode = -1L;		// RelationsCode
	DR.iRTyp = RTBegleitO;		// RelationsTyp
	
    DEX_DeleteRelation(DR);
    
HWND ORhWnd = g_pTextExt  -> m_hWnd;		
    if (ORhWnd != 0 )
    	DEXOR_DeleteObject(ORhWnd, lTxtONr);
    else
		DEX_DeleteObject(lTxtONr);

// Schaffe neues Textobjekt mit neuer Nummer, neuem Text an den Koordinaten des ersten enum. Textobjektes      
TEXTGEOMETRIE TG;		
	TG.dwSize = sizeof(TEXTGEOMETRIE);
	TG.lONr = -1L;		// ObjektNummer
	if (pstEnObj -> lCBIdent == 0) TG.lIdent = OSRELAT.lIdent;// Identifikator
	else TG.lIdent = pstEnObj -> lCBIdent;
	TG.iObjTyp = OGText;		// ObjektTyp (Punkt, Kante, Fläche, ...)
	TG.iFlags = OGNewObject;		// Modi von ModGI			
	if(pstEnObj -> bTemp) TG.iFlags |= OGTempObject;		
// dieser Teil ist spezifisch für den Fall Textobjekt
	TG.lCnt = 1;		// Gesamtanzahl der Stützpunkte (Größe der KoordFelder)
	TG.iKCnt = STRLENGTH;		// hier: (max.) Textlänge
	TG.pdblX = pX;		// KoordinatenFelder (double */long *)
	TG.pdblY = pY;
	TG.pText = pcBuffer;		// Text des Textobjektes		
	if(!DEX_ModObjGeometrie(TG)) {
		CBuffer.ReleaseBuffer();
		PLoesch.Del(pX,pY,pK);
		return FALSE;
	}		
                                            
	if (ORhWnd != 0) DEXOR_AddObjectToList(ORhWnd, TG.lONr);	

	if (pstEnObj -> bRelat == TRUE) {
		if (!g_pTextExt  -> m_pHelper -> MakeObjRelat ( pstEnObj -> lObjNr, TG.lONr )) {
			CBuffer.ReleaseBuffer();
			PLoesch.Del(pX,pY,pK);
			return FALSE;
		}
    }

	if (!g_pTextExt  -> m_pHelper -> PutUniqueIdentMCodeText(pstEnObj -> lObjNr, TG.lONr, pstEnObj->bTemp)) {
		CBuffer.ReleaseBuffer();
		PLoesch.Del(pX,pY,pK);
		return FALSE;
	}								 				
	CBuffer.ReleaseBuffer();
	PLoesch.Del(pX,pY,pK);

	pstEnObj -> iState = FOUND;                   
	pstEnObj -> lObjNr = TG.lONr;
return TRUE;
}	                              

};
