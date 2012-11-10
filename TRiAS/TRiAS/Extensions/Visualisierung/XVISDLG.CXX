// Dialogfenster zur Auswahl einer Symbolisierungsart -------------------------
// File: XVISDLG.CXX

#include "visobjp.hxx"

#include "visobj.h"

#include <registrx.hxx>
#include <icustom.hxx>

#include "VisMTree.hxx"

// FunktionsPrototypen --------------------------------------------------------
short OTypToBits (short iOTyp)
{
	switch (iOTyp) {
	case OGPunkt:
		return OTPunkt;
	case OGLinie:
		return OTLinie;
	case OGFlaeche:
	case OGKreis:
		return OTFlaeche;
	case OGLabel:
	case OGText:
		return OTText;
	case OGKO:
		return OTKO;
	case OGSachObjekt:
		return OTSachObjekt;
	default:
	case OGUnknown:
		break;
	}
	return 0;
}

typedef struct tagOBJCHANGESYMBOL {
	CVisObjExtension *m_pVOExt;
	CVisModule *m_pVM;
	char *m_pVString;
	bool m_fFirst;
	short m_iOTypes;
} OBJCHANGESYMBOL;

// Symbolisierung für ein Objekt neu einstellen -------------------------------
#if defined(_USE_PROPACT_FOR_CUSTOMVIS)
BOOL ChangeObjectSymbol (long lONr, HWND hORWnd, UINT_PTR pData, UINT_PTR dwLocalData)
#else
extern "C" BOOL _XTENSN_EXPORT PASCAL ObjChangeSymbol (long lONr, BOOL, void *pData)
#endif // defined(_USE_PROPACT_FOR_CUSTOMVIS)
{
short Status = DEX_GetObjectStatus (lONr);

	if (Status != OSNormal && Status != OSModified) 
	// Objekt existiert nicht oder ist temporär
		return true;	// weitermachen

// Symbolisierung nur neu einstellen, wenn Objekttyp übereinstimmt
OBJCHANGESYMBOL *pOCS = reinterpret_cast<OBJCHANGESYMBOL *>(pData);
short iOType = DEX_GetObjectType(lONr);

	if (OTypToBits (iOType) & pOCS -> m_iOTypes) {
	// ObjektTyp setzen
	char cOTyp = ' ';
	
		switch (iOType) {
		case OGPunkt:	cOTyp = 'c'; break;
		case OGLinie:	cOTyp = 'l'; break;
		case OGFlaeche:	cOTyp = 'a'; break;
		case OGLabel:
		case OGText:	cOTyp = 'x'; break;
		default:	return true;	// unbekannter Objekttyp
		}
		*pOCS -> m_pVString = cOTyp;
	
	// Für jedes zu bearbeitende Objekt noch einmal nachfragen, ob 
	// VisString geändert werden soll. Außerdem besteht die Möglichkeit,
	// über die Referenz auf die ObjektNummer ein anderes Objekt
	// als das gegebene zu beeinflussen.
	HRESULT hr = pOCS -> m_pVM -> m_pIVisModule -> 
			SymbolizeObject (pOCS -> m_pVOExt -> hWnd(),
					 lONr, iOType,
					 pOCS -> m_pVString, _MAX_PATH);

	// bei irgend einem Fehler einfach weitermachen
		if (FAILED(hr) && GetScode(hr) != E_NOTIMPL)
			return true;
	
	// String zwischenspeichern
	string strT = pOCS -> m_pVString;	// Zwischenspeichern wegen OemToAnsi

	// als VisInfo wegschreiben	
	bool fResult = pOCS -> m_pVOExt ->
				ModObjectSymbol (lONr, pOCS -> m_pVString, 
				pOCS -> m_fFirst);

		strcpy (pOCS -> m_pVString, strT.c_str());	// zurückkopieren
		return fResult;
	}
	return true;	// weitermachen
}

///////////////////////////////////////////////////////////////////////////////
// MenuFunktion 
bool CVisObjExtension::DefineSymbol (HWND hORWnd, CVMDMenuItem *pItem) 
{
// aktiviertes Objekt besorgen
long lActObj = DEX_GetActiveObject (hORWnd);

	if (lActObj == -1) return false;
		
short Status = DEX_GetObjectStatus (lActObj);

	if (Status != OSNormal && Status != OSModified) 
	// Objekt existiert nicht oder ist temporär
		return false;

// aktivieren des Dialoges im VisModul
	if (m_pVMT == NULL || NULL == pItem) return false;
	
// sicherstellen, daß dieser VisModule geladen ist
LPCSTR pVisModule = pItem -> GetModuleName();
CVisModule *pVM = m_pVMT -> FFindOrAdd ((char *&)pVisModule, m_pActProject);
char *cbModuleInfo[2];
	
	if (pVM == NULL) return false;
		
	cbModuleInfo[0] = cbModuleInfo[1] = NULL;
	
HANDLEVISINFO *pHVI = GetObjectVisInfo (lActObj, NULL, -1L, cbModuleInfo);

	if (pHVI == NULL) return false;

OldVisInfo *pVI = OldVisInfoFromC (*pHVI -> m_pVI, (enum VisType)pHVI -> m_iVTyp);

// VisModule auffordern, das Objekt zu behandeln
OBJCHANGESYMBOL OCS;
ResString rsVModFmt (ResID (IDS_VMODFORMAT, &RF()), 20);
HRESULT hr = E_OUTOFMEMORY;
	
	ATLTRY(OCS.m_pVString = new char [_MAX_PATH +50]);
	if (NULL != OCS.m_pVString) {
		strcpy (OCS.m_pVString, rsVModFmt);

		dtHANDLEVISINFO (pHVI);		// Speicher freigeben
		
	// Den VisModule fragen, wie er die ausgewählten Objekte symbolisieren
	// will. Dazu liefert dieser eine Zeichenkette, die als objektbezogene
	// Visualisierung abgespeichert wird und dann beim Zeichnen diesem 
	// Module zur Symbolisierung übergeben wird.
		hr = pVM -> m_pIVisModule -> QueryParameters (
				hWnd(), lActObj, reinterpret_cast<VisInfo *>(pVI), cbModuleInfo[1],
				&OCS.m_pVString[strlen(OCS.m_pVString)], 
				_MAX_PATH, &OCS.m_iOTypes
			 );
	} 

	DELETE_OBJ (pVI);
	DELETE_OBJ(cbModuleInfo[0]);
	DELETE_OBJ(cbModuleInfo[1]);
	if (FAILED(hr)) return false;
		
	strcat (OCS.m_pVString, ResString (ResID (IDS_TRAILER, &RF()), 5));
		
// Eingegebenen String am Objekt/allen selektierten Objekten abspeichern
short iCnt = 0;

	OCS.m_pVOExt = this;
	OCS.m_pVM = pVM;
	OCS.m_fFirst = false;

#if defined(_USE_PROPACT_FOR_CUSTOMVIS)
	HandleCustomVisCommands(CLSID_NULL, pItem -> GetMenuString(), ChangeObjectSymbol, hORWnd, reinterpret_cast<UINT_PTR>(&OCS));
#else
	DEXOR_SelectedObjectsCount (hORWnd, &iCnt); 
	if (iCnt > 1) {
	// alle selektierten behandeln
	ENUMLONGKEY ELK;
			
		ELK.eKey = (long)hORWnd;
		ELK.eFcn = (ENUMLONGKEYPROC)ObjChangeSymbol;
		ELK.ePtr = &OCS;
		DEX_EnumSelectedObjects (ELK);
	} else {
	// lediglich aktiviertes Objekt behandeln
		ObjChangeSymbol (lActObj, false, &OCS);
	}
#endif // defined(_USE_PROPACT_FOR_CUSTOMVIS)

	DELETE_OBJ (OCS.m_pVString);
	if (OCS.m_fFirst)
		RebuildSight();		// alles neu zeichnen, neu aufbauen
	else 
		DEX_RePaintWait();	// alles neu zeichnen
	
	return true;
}

