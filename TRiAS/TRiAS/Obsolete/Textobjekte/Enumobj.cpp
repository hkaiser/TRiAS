#include "stdafx.h"

#include "resource.h"
#include "del.hpp" //löscht Zeiger
#include "helper.h"

extern CTextExt* g_pTextExt;
//-----------------------------------------------------------------
// Enumeration der Objekte

extern "C"
bool FAR PASCAL _XTENSN_EXPORT EnumObjs (long lObjNr, bool, void *pData)
{
	ASSERT (0 != lObjNr);

OBJSTATISTIK OS;
OBJGEOMETRIE OG;
TARGETMERKMAL TM;

	SEnObj *pstEnObj = (SEnObj*)pData;						

	ASSERT (NULL != pstEnObj);

DelPointer PLoesch;                              
char cOTyp = *(pstEnObj -> pcGeo);
short iOTyp = 0;		 	

	INITSTRUCT (OS, OBJSTATISTIK);
	OS.lONr	= lObjNr;// ObjektNummer
	if (!DEX_GetObjStatistik(OS)) return false;			

long lIdent = OS.lIdent;	
short iObjTp = OS.iObjTyp;			

// Abfragen nur nötig, wenn Objekte nach Identifikator enumeriert werden, 
// da ALLE Objekte des Identifikators ob Punkt, Flaeche o. Linie geschickt werden 
HWND ORhWnd = g_pTextExt  -> m_hWnd;		

	if (NULL == ORhWnd) {
	/* Vergleich mit gewaehltem Objekt */
		switch (cOTyp) {
		case 'F':
			iOTyp = OGFlaeche;
			break;

		case 'P':
			iOTyp = OGPunkt;
			break;

		case 'L':
			iOTyp = OGLinie;
			break;

		default:
			if (iObjTp == OGText) 
				return true;
			ASSERT (false);
			return false;
		}

		if (iObjTp != iOTyp) return true;	// gerade nicht interessant
	}

// wenn nur Umbenennen gewünscht, wird jeweils das erste gefundene ursprünglich 
// angehaengte Textobjekt umbenannt
	pstEnObj -> iState = NOTFOUND;
	if (pstEnObj -> bRelat && (pstEnObj -> bRename && !pstEnObj -> bObLoesch)) 
	{
	// zum Zuweisen des Textes des Bezugsobjektes		                             
		pstEnObj -> lObjNr = lObjNr;
		if (!g_pTextExt  -> m_pHelper -> Rename(pstEnObj))
			return false;

		if (pstEnObj -> iState == FOUND) {
			pData = (void *)pstEnObj;				
			return true; 
		}
	}

// wenn wenigstens ein angehaengtes Textobjekt gefunden wurde
// geht weiter, wenn kein Textobjekt gefunden
short iKAnz = OS.iKCnt;

	if (iKAnz == 0) iKAnz = 1;	

long* pY = new long[OS.lCnt];
long* pX = new long[OS.lCnt];
long* pK = new long[iKAnz];

	if (pY == NULL || pX == NULL || pK == NULL) return false;		    
		
	INITSTRUCT(OG, OBJGEOMETRIE);
 	OG.lONr = lObjNr;	// ObjektNummer
	OG.lIdent = lIdent;	// Identifikator
	OG.iObjTyp = iObjTp; 	// ObjektTyp (Punkt, Kante, Fläche, ...)
	OG.iFlags = OS.iFlags;  // double Koordinate

// neue Geometrie
	OG.lCnt	= OS.lCnt; 	// Gesamtanzahl der Stützpunkte (Größe der KoordFelder)
	OG.iKCnt = iKAnz;	// Größe des KonturFeldes
	OG.pdblX = pX;		// KoordinatenFelder (double */ *)
	OG.pdblY = pY;
	OG.plCnt = pK;		// Anzahl der Stützpunkte in Konturen

	if (iObjTp != OGFlaeche) {
		OG.iKCnt = 0;
		OG.plCnt = NULL;
	}	   
	if(!DEX_GetObjGeometrie(OG)) {
		PLoesch.Del(pX,pY,pK);
		return false;
	}

// Berechne den Punkt für Textobjekt	
CString eBuffer (' ', STRLENGTH);

	if (!g_pTextExt -> m_pHelper -> CalcPointofText(pX, pY, pK, iObjTp, OG.lCnt, lIdent, 
							pstEnObj -> fPosPtTexts)) 
	{
		PLoesch.Del(pX,pY,pK);
		return false;
	}

char* pcBuffer = NULL;		
CString CBuffer = pstEnObj -> sTxt;

	TRY {                                       
		pcBuffer = CBuffer.GetBuffer(STRLENGTH);
	}
	CATCH (CMemoryException, e) {
		DEX_Error (0, EC_NOMEMORY);
		return true;		// trotzdem weitermachen
	}                  
	END_CATCH


// Wenn Text nicht selbst generiert, hole für Objekt das Textmerkmal
	if (!g_pTextExt  -> m_pHelper -> TestTextContents (pcBuffer)) {

		INITSTRUCT(TM, TARGETMERKMAL);
		TM.lTarget = lObjNr;			// ObjektNummer/Identifikator oder char * (SichtName)
		TM.lMCode = pstEnObj -> lMerkCd;	// MerkmalsCode
		TM.pMText = pcBuffer;			// zu lieferndes TextMerkmal 
		TM.imaxLen = STRLENGTH; 		// max Textlänge
		TM.iTTyp = TT_Objekt;			// OBL, IDL oder SICHT			
		if(!DEX_GetTextMerkmal(TM)) {
			PLoesch.Del (pX, pY, pK);
			return true;        
		}                         
	}	                          
	CBuffer.ReleaseBuffer();			// weg damit
		
	if (!g_pTextExt  -> m_pHelper -> TestTextContents (CBuffer))
		return true;

// Schaffe neues Textobjekt...    
TEXTGEOMETRIE TG;		

	INITSTRUCT (TG, TEXTGEOMETRIE);
	TG.lONr = -1L;			// ObjektNummer

	if (0 == pstEnObj -> lCBIdent) {
		TG.lIdent = lIdent;	// Identifikator
	} else 
		TG.lIdent = pstEnObj -> lCBIdent;	//schon im Dialog konvertiert
	
	TG.iObjTyp = OGText;		// ObjektTyp (Punkt, Kante, Fläche, ...)
	TG.iFlags = OGNewObject;	// Modi von ModGI			
	
	if(pstEnObj -> bTemp) 
		TG.iFlags = OGTempObject | OGAddToView;		
	else 
		TG.iFlags = OGAddToView;

// dieser Teil ist spezifisch für den Fall Textobjekt
	TG.lCnt = 1;			// Gesamtanzahl der Stützpunkte (Größe der KoordFelder)
	TG.iKCnt = STRLENGTH;		// hier: (max.) Textlänge
	TG.pdblX = pX;			// KoordinatenFelder (double */long *)
	TG.pdblY = pY;
	TG.pText = (char *)(const char *)CBuffer;		// Text des Textobjektes		
	if(!DEX_ModObjGeometrie(TG)) {
		PLoesch.Del (pX, pY, pK);
		return false;
	}		

bool bObLoesch = pstEnObj -> bObLoesch;

// Wenn Objektrecherche, hinzufügen des neuen Textobjektes zur Liste
	if (ORhWnd != 0) DEXOR_AddObjectToList(ORhWnd, TG.lONr);	

short iFounded = NOTFOUND;
		
	if (pstEnObj->bRelat == true) {
		if (!g_pTextExt  -> m_pHelper -> LoeschObjRelat (lObjNr, bObLoesch, &iFounded)) {
			PLoesch.Del (pX, pY, pK);
			return false;
        	}
		
		if (!g_pTextExt  -> m_pHelper -> MakeObjRelat (lObjNr, TG.lONr)) {
			PLoesch.Del (pX, pY, pK);
			return false;
        	}
	}

	if (!g_pTextExt  -> m_pHelper -> PutUniqueIdentMCodeText (lObjNr, TG.lONr, pstEnObj->bTemp)) {
		PLoesch.Del (pX, pY, pK);
		return false;
	}								 				

	PLoesch.Del (pX, pY, pK);
	pstEnObj -> lObjNr = TG.lONr;

return true; 
}

