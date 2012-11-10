
#include "stdafx.h"

#include <assert.h>
#include "resource.h"
#include "helper.h"
#include "waitcur.hpp"
 
CHelper :: CHelper (CTextExt *pTextExt)
{
}

// Destruktor -----------------------------------------------------------------
CHelper :: ~CHelper (void) 
{
	// nothing to do
}

bool CHelper :: CalcPointofText (long* pX, long* pY, long* pK, short iObjTp, 
				 long lAnz, long lIdent, bool fPosPtTexts)
{
	ASSERT (NULL != pX);
	ASSERT (NULL != pY);
	ASSERT (NULL != pK);
	ASSERT (0 != lIdent);

	if (iObjTp < 0) {
		ASSERT (0);
		return false;
	}

	switch(iObjTp) {
	case OGFlaeche:
		if (EvalSchwerPunkt (pX, pY, pK))
			return true;
		break;	

	case OGPunkt: 
		if (fPosPtTexts) 
			return MovingIfPntObj (pX, pY, lIdent);
		return true;	// nichts tun

	case OGLinie:
		if (EvalLinMitte (pX, pY, lAnz))
			return true;
		break;

	case OGText:
		return true;

	default :
		ASSERT (false);
		break;
	}

return false;
}       

// Berechnet Flächenschwerpunkt der Fläche ------------------------------------
bool CHelper :: EvalSchwerPunkt (long* px, long* py, long* pK) 
{
long lAnz = pK[0];		// Anzahl Stützpunkte (Außenkontur)
long *pX = px;
long *pY = py;

	if (lAnz <= 3 || pX == NULL || pY == NULL) return false;

	if (pX[0] != pX[lAnz-1] || pY[0] != pY[lAnz-1])
		return false;		// Kontur nicht geschlossen
		
// kleinste X/Y-Koordinate bestimmen
long lIndex;
long lXMin = pX[0];
long lYMin = pY[0];

	for (lIndex = 0; lIndex < lAnz; lIndex++) {
		if (pX[lIndex] < lXMin) lXMin = pX[lIndex];
		if (pY[lIndex] < lYMin) lYMin = pY[lIndex];
	}	

// Schwerpunkt berechnen
double Xs = 0.0, Ys = 0.0, Xsi, Ysi, Inh;	// Schwerpunkt-Koordinaten
double dblF = 0.0;

	for (lIndex = 0; lIndex < (lAnz - 1); lIndex++) {	// für alle Punkte der Folge
	double X1 = double (pX[lIndex] - lXMin);	// laufende Koordinaten
	double Y1 = double (pY[lIndex] - lYMin);
	double X2 = double (pX[lIndex+1] - lXMin);
	double Y2 = double (pY[lIndex+1] - lYMin);

	// Zwischenwerte berechnen
		if ((Y1 + Y2) != 0) {	   // wenn Berechnung möglich
			Xsi = X1 + ((X2 - X1) * ((2.0 * Y2) + Y1)) /
				(3.0 * (Y1 + Y2));
			Ysi = ((Y1 * Y1) + (Y1 * Y2) + (Y2 *Y2)) /
				(3.0 * (Y1 + Y2));
			Inh = (X1 - X2) * (Y1 + Y2) * 0.5;
		} else 
			Xsi = Ysi = Inh = 0.0;      // alle Werte 0 setzen

	// Zwischenwerte aktualisieren
		Xs += Xsi * Inh;	      // Schwerpunkt
		Ys += Ysi * Inh;
		dblF += Inh;		      // Inhalt der Fläche
	}

// Endkoordinaten berechnen
	if (dblF == 0.0) return false;
	
	px[0] = long ((Xs / dblF) + lXMin + 0.5);
	py[0] = long ((Ys / dblF) + lYMin + 0.5);

return true;	
}

	
bool CHelper :: EvalLinMitte (long* px, long* py, long lAnz)
{
	px[0] = px[lAnz / 2];
	py[0] = py[lAnz / 2];	
	
return true;
}       


// Berechnet für Punktobjekte die Verschiebung des Textobjekts, 
// so daß sichtbarer Punkt nicht überdeckt wird.
bool CHelper :: MovingIfPntObj (long* pX, long* pY, long lIdent)
{
	ASSERT (NULL != pX);
	ASSERT (NULL != pY);
	ASSERT (0 != lIdent);

HANDLEVISINFO HandleVisInfo;
PVISINFO PVisInfo;         

	INITSTRUCT(HandleVisInfo, HANDLEVISINFO); 
	HandleVisInfo.m_lONr = 0;		// Target (ObjektNummer)
	HandleVisInfo.m_lIdent = lIdent;	// Identifikator
	HandleVisInfo.m_iVTyp = VTPunkt;	// VisInfoTyp
	HandleVisInfo.m_fFlags = 0;		// zu ändern bzw. geändert
	HandleVisInfo.m_pDesc = NULL;		// beschreibender Text
	HandleVisInfo.m_pView = NULL;		// evtl. SichtName (aktuelle Sicht: NULL)
	HandleVisInfo.m_pVI = (VISINFO *)&PVisInfo;		// generischer Pointer auf VisInfo
	HandleVisInfo.m_hWnd = NULL;		// als ParentWindow verwenden	
		
	if (!DEX_GetIdentVisInfo(HandleVisInfo)) 
		return false;    // hole Visualisierungsinfo mit Punktgröße

double dMassStabVerh = 0;           

	DEX_GetActiveScaling(dMassStabVerh);		// Verhältnis des jetzigen aktuellen Maßstab zum allg. Bezugsmaßstabes 

long lcx = ( (long) PVisInfo.m_Size.cx ) * 100;		// Punktgröße in 1/100 mm im allg. Bezugsmaßstab
long lcy = ( (long) PVisInfo.m_Size.cy ) * 100;		// in x- u. y-Richtung
SIZE PixelDimPerMM = GetDotsPerMM (NULL);		// berechnet Pixel pro mm                            
long lMassStabVerh = (long)(dMassStabVerh * 1000);	// zum Umwandeln der double in long "*" u. "/ 1000 "  ?

// wenn Punktobjekt sehr groß, führt cast zu 0!
	if (0 == lMassStabVerh) lMassStabVerh = 1;	// 1/100 mm
	
	lcx = lcx / lMassStabVerh;			// berechnet erst aktuellen- aus Bezugsmaßstab 
	lcy = lcy / lMassStabVerh;			// von derzeitiger  Visualisierung der Punktobjekte in mm 
		
// dann von mm nach Pixel (wieviel x Pixel auf z mm)
	lcx = lcx * (long)PixelDimPerMM.cx;                  
	lcy = lcy * (long)PixelDimPerMM.cy; 

// Koordinatentransformation von DB-Koord. nach Pixel:
COORDCONVERT CoordConv;       
POINT pt;
long Pkt[2];

	CoordConv.lpPt = &pt;
	CoordConv.lpPkt = Pkt;

// übergebe die Koordinaten in DB-Koord., bekomme Pixel	
	CoordConv.lpPt -> x = 0; 
	CoordConv.lpPt -> y = 0;			// POINT
	CoordConv.lpPkt[0] = pX[0];			// Punkt Feld long!! aus DB.-Koord.
	CoordConv.lpPkt[1] = pY[0];
	DEX_OCtoDCEx (CoordConv);
		
// Koordinatentransformation von Pixel nach DB-Koord.:
	CoordConv.lpPt -> x = (int)(CoordConv.lpPt -> x + (long)lcx/20);	
	CoordConv.lpPt -> y = (int)(CoordConv.lpPt -> y + (long)lcy/20);
        
	CoordConv.lpPkt[0] = 0;// Punkt Feld long!!
	CoordConv.lpPkt[1] = 0;
	
	DEX_DCtoOCEx (CoordConv);     
		
	pX[0] = CoordConv.lpPkt[0];
	pY[0] = CoordConv.lpPkt[1];

return true;					                  
}

// Anzahl der Pixel/mm in beiden Koordinatenrichtungen für dieses Fenster -----
SIZE CHelper :: GetDotsPerMM (HDC hDC) 
{
HDC hDCloc;
SIZE dimD;

	dimD.cx = 0;
	dimD.cy = 0;

	if (hDC != NULL) hDCloc = hDC;
	else		 hDCloc = GetDC (GetDesktopWindow());

	switch (GetMapMode (hDCloc)) 
	{
	default:		// MM_ANISOTROPIC/MM_ISOTROPIC
	case MM_TEXT:		// der bisherige Stand
		{
		int HorzSize = GetDeviceCaps (hDCloc, HORZSIZE);       // Breite in mm
		int VertSize = GetDeviceCaps (hDCloc, VERTSIZE);       // Höhe in mm
		int HorzRes = GetDeviceCaps (hDCloc, HORZRES);         // Breite in Dots
		int VertRes = GetDeviceCaps (hDCloc, VERTRES);         // Höhe in Dots

			dimD.cx = HorzRes/HorzSize; 
			dimD.cy = VertRes/VertSize; 
		}
		break;

	case MM_HIMETRIC:	// [0.01 mm]
		dimD.cx = 100;
		dimD.cy = 100;
		break;
		
	case MM_LOMETRIC:// [0.1 mm]
		dimD.cx = 10;
		dimD.cy = 10;
		break;
		
	case MM_HIENGLISH:	// [0.001 inch]
		dimD.cx = 40;
		dimD.cy = 40;
		break;
		
	case MM_LOENGLISH:	// [0.01 inch]
		dimD.cx = 4;
		dimD.cy = 4;
		break;
		
	case MM_TWIPS:
		dimD.cx = 57;
		dimD.cy = 57;
		break;
	}

// DC bei Bedarf wieder freigeben
	if (hDC == NULL) ReleaseDC (GetDesktopWindow(), hDCloc);

return dimD;
}

// Textobjekt erzeugen --------------------------------------------------------
bool CHelper :: ProvTextObj (HWND hWnd, char *pcGeo, CString sTxt,
			long lIdent, long lMCode, bool bTemp, 
			bool bRelat, bool bObLoesch, bool bRename, long lCBIdent,
			bool fPosPtTexts)
{
ENUMLONGKEY  ELK;
SEnObj  stEnObj;

	stEnObj.lId = lIdent;
	stEnObj.lMerkCd = lMCode;
	stEnObj.sTxt = sTxt;
	stEnObj.bTemp = bTemp;
	stEnObj.bRelat = bRelat;                
	stEnObj.bObLoesch = bObLoesch;                
	stEnObj.bRename = bRename;                
	stEnObj.pcGeo = pcGeo;
	stEnObj.lCBIdent = lCBIdent;	            
	stEnObj.iState = NOTFOUND;
	stEnObj.fPosPtTexts = fPosPtTexts;
	            
	ELK.eFcn = (ENUMLONGKEYPROC) EnumObjs;
	ELK.ePtr = &stEnObj;        //Übergabe mit Merk.code

	if (NULL == hWnd) {
		ASSERT (0 != lIdent);
	
		ELK.eKey = lIdent;
		if (!DEX_EnumIdentObjects(ELK)) 
			return false;		// alle Objekte mit einem Identifikator
	}	
	else {
	        ELK.eKey = (DWORD)(void *)hWnd;
		if (!DEX_EnumSelectedObjects(ELK)) 
			return false;		// nur für ein selektiertes Objekt
	}

return true;
}


// zur Enum. der Obj. "Abhängen" ----------------------------------------------
bool CHelper :: AbhaengTextObj (HWND hWnd, long lIdent, bool bLoesch, char* pGeo)
{
SAbh stAbh;
ENUMLONGKEY  ELK;	
CWaitCursor WC;

	stAbh.bLoesch = bLoesch;
	stAbh.pGeo = pGeo;
	    
    	ELK.eFcn = (ENUMLONGKEYPROC) EnumObjAbh;
	ELK.ePtr = &stAbh;                           
	
	if (NULL == hWnd) {
		ASSERT (0 != lIdent);

		ELK.eKey = lIdent;
		if (!DEX_EnumIdentObjects(ELK)) 
			return false;	// alle Objekte mit einem Identifikator
	}
	else {
        	ELK.eKey = (DWORD)(void *)hWnd;
		
		if (!DEX_EnumSelectedObjects(ELK)) return false ;
	}
			
return true;
}

                        
// stellt fest, ob Objektrelation vorhanden, löscht diese ---------------------
bool CHelper :: LoeschObjRelat (long lONr, bool bObLoesch, short *pfFound)
{
	ASSERT (0 != lONr);

ENUMRELATIONOBJS ERO;
SObj stObj;

	if (pfFound) *pfFound = false;
	
	stObj.lObNr = lONr;
	stObj.bObLoesch = bObLoesch;  
	stObj.iState = NOTFOUND;

	ERO.dwSize = sizeof(ENUMRELATIONOBJS) ;
	ERO.lONr = lONr;		// Bezugsobjekt, für das Relationen geliefert werden
	ERO.lRCode = -1L;		// zu untersuchende Relation (-1: alle)
	ERO.iRTyp = RTBegleitO;		// zu untersuchende RelationsTypen
	ERO.eFcn = (ENUMRELOBJPROC)  EnumRelObj;	// zu rufende Funktion
	ERO.pData = &stObj;		// durchgereichte Daten
	
	if(!DEX_EnumRelationObjects(ERO)) 
		return false;	
	
	if (pfFound) *pfFound = stObj.iState;
	
return true;
}

// Umbenennen Textobjekt ------------------------------------------------------
bool CHelper :: Rename (SEnObj *pstEnObj)
{
	ASSERT (NULL != pstEnObj);

ENUMRELATIONOBJS ERO;
			
	ERO.dwSize = sizeof(ENUMRELATIONOBJS) ;
	ERO.lONr = pstEnObj -> lObjNr;		// Bezugsobjekt, für das Relationen geliefert werden
	ERO.lRCode = -1L;			// zu untersuchende Relation (-1: alle)
	ERO.iRTyp = RTBegleitO;			// zu untersuchende RelationsTypen
	ERO.eFcn = (ENUMRELOBJPROC)  EnumRelObjRename;	// zu rufende Funktion
	ERO.pData = (void *)pstEnObj;		// durchgereichte Daten
				
	if(!DEX_EnumRelationObjects(ERO)) 
		return false;

return true;		
}			

//stellt Objektrelation her
bool CHelper :: MakeObjRelat (long lONr , long lTxtONr)
{
MODRELATION MR;

	MR.dwSize = sizeof(MODRELATION);
	MR.lPONr = lONr;		// PrimärObjekt
	MR.lSONr = lTxtONr;		// SekundärObjekt
	MR.lRCode = -1L;		// RelationsCode
	MR.iRTyp = RTBegleitO;		// RelationsTyp
	
return (EC_OKAY == DEX_ModifyRelation (MR));
}

bool CHelper :: GetKText (CString &cbKText, char cKey ,long lItem)
{
char *pKText = NULL;
		
	TRY {                                       
		pKText = cbKText.GetBuffer(STRLENGTH);
	}
	CATCH (CMemoryException, e) {
		DEX_Error (0, EC_NOMEMORY); 
	}                  
	END_CATCH

	if (NULL == pKText) return false;		    

// KurzText aus PBD holen
PBDDATA pbdData;	
ErrCode EC;

	INITSTRUCT (pbdData, PBDDATA);
	pbdData.pbdTyp      = cKey;
	pbdData.pbdCode     = lItem;
	pbdData.pbdKText    = pKText;
	pbdData.pbdKTextLen = STRLENGTH;
	pbdData.pbdLTextLen = 0; 
	
	EC = DEX_GetPBDData (pbdData);
	cbKText.ReleaseBuffer();

	if (EC != EC_OKAY) return false;		

return true;
}

// füllt, je nachdem welche Geometrietypen  der erhaltene Ident.
// besitzt die Listbox und formatiert vorher		                    
static char s_acType[3] = { 'F', 'P', 'L' };
static DWORD s_adwType[3] = { OTFlaeche, OTPunkt, OTLinie };

bool CHelper :: FuellBox (DWORD dwType, CListBox *pLB, long lIdent)
{                                                     
	ASSERT(NULL != pLB);
	ASSERT(0 != lIdent);

// Zeichenkette formatieren
	TRY {                                       
	CString cbBuffer ('\0', _MAX_PATH);
	CString cbKText;

		for (int i = 0; i < sizeof(s_adwType)/sizeof(s_adwType[0]); i++) {
			if (!GetKText (cbKText, 'i', lIdent)) 
				continue;	// kein Kurztext oder Fehler

			if (DEX_GetIdBase() == 10) {
				if (s_adwType[i] & dwType) {
					cbBuffer.Format ("%08ld:%c:%s", lIdent, s_acType[i], (LPCSTR)cbKText);
					pLB -> AddString (cbBuffer); 
	            		}
			}
			else if (s_adwType[i] & dwType) {
				cbBuffer.Format ("%08lx:%c:%s", lIdent, s_acType[i], (LPCSTR)cbKText);
				pLB -> AddString (cbBuffer);
			}
		}
	}
	CATCH (CMemoryException, e) {
		DEX_Error (0, EC_NOMEMORY); 
		return false;
	}                  
	END_CATCH

return true;
}

bool CHelper :: FuellBox (CComboBox *pCB, long lIdent)
{
	ASSERT(NULL != pCB);
	ASSERT(0 != lIdent);

// Zeichenkette formatieren
	TRY {                                       
	CString cbBuffer ('\0', _MAX_PATH);
	CString cbKText;
	
		if (!GetKText (cbKText, 'i', lIdent))
			return false;

		if (DEX_GetIdBase() == 10) {
			cbBuffer.Format ("%08ld:%s", lIdent, cbKText);
			pCB -> AddString (cbBuffer); 
		}
		else {
			cbBuffer.Format ("%08lx:%s", lIdent, cbKText);
			pCB -> AddString (cbBuffer);
		}
	}
	CATCH (CMemoryException, e) {
		DEX_Error (0, EC_NOMEMORY); 
		return false;
	}                  
	END_CATCH

return true;
}

bool CHelper :: PutUniqueIdentMCodeText(long lObNr, long lTObNr, bool bTemp)
{                                               
// entweder Merkmalscodetext des Unique Ident des zugehörigen Objektes oder
// bei temporaerem Textobjekt irgendein Text dem Texto. zuweisen 
TARGETMERKMAL TM;
CString	sBuffer;
char *pcBuffer = NULL;

	TRY {                                       
		pcBuffer  = sBuffer.GetBuffer(STRLENGTH);
	}
	CATCH ( CMemoryException, e ) {
		DEX_Error (0, EC_NOMEMORY); 
	}                  
	END_CATCH
		
	INITSTRUCT (TM, TARGETMERKMAL);
	TM.iTTyp = TT_Objekt;		// OBL, IDL oder SICHT			

long lUIMCode = DEX_GetUniqueIdentMCode();

	if (!bTemp) {
		TM.lTarget = lObNr;			// ObjektNummer/Identifikator oder char * (SichtName)
		TM.lMCode = lUIMCode;			// MerkmalsCode
		TM.pMText = pcBuffer;			// zu lieferndes TextMerkmal 
		TM.imaxLen = STRLENGTH; 		// max Textlänge
		if(NULL == DEX_GetTextMerkmal(TM)) 		// kein Unique Ident vorhanden
			sBuffer.Format ("TEXTOBJ_%ld", lObNr);	// Standard generieren
	}

	TM.lTarget = lTObNr;				// ObjektNummer/Identifikator oder char * (SichtName)
	TM.lMCode = lUIMCode;				// MerkmalsCode
	TM.pMText = pcBuffer;				// zu modifizierendes TextMerkmal 
	TM.imaxLen = STRLENGTH; 			// max Textlänge

return EC_OKAY == DEX_ModTextMerkmal (TM);
}

// Festellen, ob ein Text was anderes als Leerzeichen enthält -----------------
bool CHelper :: TestTextContents (const char* pcBuffer)
{
	while (*pcBuffer == ' ') {
		if (*pcBuffer == '\0') 
			return false;
		pcBuffer++;
	}

return *pcBuffer == '\0' ? false : true;
}
