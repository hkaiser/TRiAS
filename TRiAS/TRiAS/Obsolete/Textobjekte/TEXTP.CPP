// Externe Schnittstelle zum Behandeln von Textobjekten -----------------------
// File: TEXTP.CXX

#include "stdafx.h"

#include "resource.h"
#include "helper.h"
#include "igentext.h"
#include "textp.h"

                     
bool FlagTest(SEnObj stEnObj, DWORD dwFlags)
{   
	if ( dwFlags & TEXTFLAGS_TEMPORARY && dwFlags & TEXTFLAGS_GENLINK ||
		dwFlags & TEXTFLAGS_TEMPORARY && dwFlags & TEXTFLAGS_DELETEOLD ||
		dwFlags & TEXTFLAGS_TEMPORARY && dwFlags & TEXTFLAGS_RENAME  || 
		dwFlags & TEXTFLAGS_DELETEOLD && dwFlags & TEXTFLAGS_RENAME ) { return false; } 

// ohne Optionen : permanentes Textobjekt	
	stEnObj.fPosPtTexts = true;		// erstmal immer verschieben

	if (dwFlags & TEXTFLAGS_NOOPTIONS) {
		stEnObj.bTemp = false;                                            
		stEnObj.bRelat = false;				
		stEnObj.bObLoesch = false;
		stEnObj.bRename = false;
	}
	else if(dwFlags & TEXTFLAGS_TEMPORARY) {
	// bei temporärem Textobjekt werden keine Relationen aufgebaut oder alte geloescht				
		stEnObj.bTemp = true;				     
		stEnObj.bRelat = false;				
		stEnObj.bObLoesch = false;
		stEnObj.bRename = false;
	} 
	else if (dwFlags & TEXTFLAGS_GENLINK && dwFlags & TEXTFLAGS_DELETEOLD ) {
		stEnObj.bTemp = false;				     
		stEnObj.bRelat = true;				
		stEnObj.bObLoesch = true;
		stEnObj.bRename = false;
	}
	else if (dwFlags & TEXTFLAGS_GENLINK && dwFlags & TEXTFLAGS_RENAME ) {
		stEnObj.bTemp = false;				     
		stEnObj.bRelat = true;				
		stEnObj.bObLoesch = false;
		stEnObj.bRename = true;
	} 
	else if (dwFlags & TEXTFLAGS_GENLINK) {
		stEnObj.bTemp = false;				     
		stEnObj.bRelat = true;				
		stEnObj.bObLoesch = false;
		stEnObj.bRename = true;   
	}
	else 
		return false; 

return true;
}

bool FlagTest (bool bLoesch, DWORD dwFlags)
{   
	if (dwFlags & TEXTFLAGS_TEMPORARY || dwFlags & TEXTFLAGS_GENLINK ||
		dwFlags & TEXTFLAGS_RENAME) return false;
		
	if (dwFlags & TEXTFLAGS_DELETEOLD) bLoesch = true;
	else bLoesch = false;
	
return true;	
}

// Konstruktor/Destruktor -----------------------------------------------------
CTextPro :: CTextPro (CTextExt* pTextExt, CHelper *pHelper)
{                    
	m_pTextExt = pTextExt;                                
	m_pHelper = pHelper;
}


CTextPro :: ~CTextPro (void)
{
}
		
/*// Werte für dwFlags ----------------------------------------------------------
typedef enum tagTEXTFLAGS {
	TEXTFLAGS_NOOPTIONS = 0x00,	
	TEXTFLAGS_TEMPORARY = 0x01,		// Textobjekte temporär erzeugen
	TEXTFLAGS_GENLINK = 0x02,
	TEXTFLAGS_DELETEOLD = 0x04,
} TEXTFLAGS;*/

STDMETHODIMP_(bool) CTextPro :: GenerateText (LONG lONr, ULONG ulMCode, DWORD dwFlags, LONG *plTxtObjNr)
{                                                                     
OBJSTATISTIK OS;
SEnObj  stEnObj;
		
	if (!m_pTextExt -> LoadState()) 
		return false;
	
	INITSTRUCT(OS, OBJSTATISTIK);
	OS.lONr	= lONr;				// ObjektNummer
	if (!DEX_GetObjStatistik(OS)) 
		return false; 
			              
	if (OS.iObjTyp == OGFlaeche) 
		*stEnObj.pcGeo = 'F';	            
	else if (OS.iObjTyp == OGPunkt) 
		*stEnObj.pcGeo = 'P';	            
	else if (OS.iObjTyp == OGLinie) 
		*stEnObj.pcGeo = 'L';	            
	else 
		return false;
		
	if (!FlagTest (stEnObj, dwFlags)) 
		return false;
	
	stEnObj.lMerkCd = ulMCode;  
	stEnObj.sTxt = '0';

// hier wird gleiche Funktion gerufen, die auch TRiAS zur Enumeration von Objekten ruft			
	if (!EnumObjs (lONr, true, &stEnObj)) 
		return false;
	
	*plTxtObjNr = stEnObj.lObjNr;

return true;
}

STDMETHODIMP_(bool) CTextPro :: GenerateText (LONG lONr, CString sText, DWORD dwFlags, LONG *plTxtObjNr)
{
OBJSTATISTIK OS;
SEnObj  stEnObj;
		
	if (!m_pTextExt -> LoadState()) return false;
	
	INITSTRUCT(OS, OBJSTATISTIK);
	OS.lONr	= lONr;				// ObjektNummer
	if (!DEX_GetObjStatistik(OS)) 
		return false; 
			              
	if (OS.iObjTyp == OGFlaeche) 
		*stEnObj.pcGeo = 'F';	            
	else if (OS.iObjTyp == OGPunkt) 
		*stEnObj.pcGeo = 'P';	            
	else if (OS.iObjTyp == OGLinie) 
		*stEnObj.pcGeo = 'L';	            
	else 
		return false;
		
	if (!FlagTest (stEnObj, dwFlags)) 
		return false;

	stEnObj.lMerkCd = 0;  
	stEnObj.sTxt = sText;


// hier wird gleiche Funktion gerufen, die auch TRiAS zur Enumeration von Objekten ruft			
	if (!EnumObjs (lONr, true, &stEnObj)) 
		return false;
	*plTxtObjNr = stEnObj.lObjNr;

return true;
}

// Generiert Textobjekte mit Text des gewählten Merkmalscodes
STDMETHODIMP_(bool) CTextPro :: GenerateTexts (ULONG ulIdent, ULONG ulMCode, short iOTyp, DWORD dwFlags)
{                                    
char cOTyp;          
bool bTemp = false;
bool bRelat = false;
bool bLoesch = false;                           
bool bRename = false;
bool fPosPtTexts = false;
SEnObj  stEnObj;
	
	if (!m_pTextExt -> LoadState()) return false;                         
	
	switch (iOTyp) {
	case OGFlaeche:
		cOTyp = 'F';
		break;

	case OGPunkt:
		cOTyp = 'P';
		break;

	case OGLinie:
		cOTyp = 'L';
		break;

	default:
		return false;
	}
			            	
	if (! FlagTest (stEnObj, dwFlags) ) return false;

	bTemp = stEnObj.bTemp;				     
	bRelat = stEnObj.bRelat;				
	bLoesch = stEnObj.bObLoesch;
	bRename = stEnObj.bRename;
	fPosPtTexts = stEnObj.fPosPtTexts;

	if (!m_pHelper  -> ProvTextObj (0, &cOTyp, '0', ulIdent, ulMCode, bTemp, 
					bRelat, bLoesch, bRename, 0, fPosPtTexts))
		return false;

return true;
}

// Generiert Textobjekte mit Text des gewählten Merkmalscodes
STDMETHODIMP_(bool) CTextPro :: GenerateTexts (ULONG ulIdent, CString sText, short iOTyp, DWORD dwFlags)
{
char cOTyp;          
bool bTemp = false;
bool bRelat = false;
bool bLoesch = false;
bool bRename = false;
bool fPosPtTexts = false;
SEnObj  stEnObj;
		
	if (!m_pTextExt -> LoadState()) return false;                         
		
	switch (iOTyp) {
	case OGFlaeche:
		cOTyp = 'F';
		break;

	case OGPunkt:
		cOTyp = 'P';
		break;

	case OGLinie:
		cOTyp = 'L';
		break;

	default:
		return false;
	}
			            	
	if (!FlagTest (stEnObj, dwFlags)) 
		return false;
	
	bTemp = stEnObj.bTemp;				     
	bRelat = stEnObj.bRelat;				
	bLoesch = stEnObj.bObLoesch;
	bRename = stEnObj.bRename;
	fPosPtTexts = stEnObj.fPosPtTexts;

	if (!m_pHelper  -> ProvTextObj (0, &cOTyp, sText, ulIdent, 0, bTemp, bRelat, 
					bLoesch, bRename, 0, fPosPtTexts))
		return false;

return true;
}
                    
// Textobjekt an Objekt wird abgehängt, 
// gegebenenfalls altes angehängtes !! geloescht
STDMETHODIMP_(bool) CTextPro :: UnlinkText (LONG lONr, DWORD dwFlags)
{                  
bool bLoesch = false;
short iFounded;                
	if (!m_pTextExt -> LoadState()) return false;	                  

	if (! FlagTest(bLoesch, dwFlags) ) return false;

	if (!m_pHelper -> LoeschObjRelat ( lONr, bLoesch, &iFounded)) return false;

return true;
}           

// Textobjekte an Objekten dieses Identifikators werden abgehängt, 
// gegebenenfalls alte angehängte !! geloescht
STDMETHODIMP_(bool) CTextPro :: UnlinkTexts (ULONG ulIdent, short iOTyp, DWORD dwFlags)
{                                      
bool bLoesch = false;
char cOTyp;
	if (!m_pTextExt -> LoadState()) return false;                         

	if (iOTyp == OGFlaeche) cOTyp = 'F';
	else
		if (iOTyp == OGPunkt) cOTyp = 'P';
		else
			if (iOTyp == OGLinie) cOTyp = 'L';
			else return false;
						
	if (! FlagTest(bLoesch, dwFlags) ) return false;
				
	if (!m_pHelper -> AbhaengTextObj (0, ulIdent, bLoesch, &cOTyp))
		return false;
return true;	
}               
     
// IUnknown methods (delegating unknown) --------------------------------------
STDMETHODIMP CTextPro :: QueryInterface (REFIID riid, LPVOID *ppv)
{
	return m_pTextExt -> QueryInterface (riid, ppv);
}


STDMETHODIMP_(ULONG) CTextPro :: AddRef (void)
{
	return m_pTextExt -> AddRef();
}


STDMETHODIMP_(ULONG) CTextPro :: Release (void)
{
	return m_pTextExt -> Release();
}
