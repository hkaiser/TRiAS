// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.10.2000 20:22:45
//
// @doc
// @module CloneObject.cpp | Implementation of the <c CCloneObject> class

#include "trias03p.hxx"
#include "trias03.h"

#include <funcs03.h>

#include <iunredo.hxx>
#include <undoguid.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// globale Daten
extern "C" HINSTANCE g_hInstance;

#if _TRiAS_VER >= 0x0420

#include <Com/Thunk.h>

#include "ObjGeomW.h"
#include "CloneObject.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(UndoRedoPBDData);
DefineSmartInterface(UndoRedoObjectFeature);

///////////////////////////////////////////////////////////////////////////////
// Helperklasse für's Objektkopieren
namespace {
// Helperklasse fürs Undo der Änderungen der Beschreibungsdaten
	class CUndoPbd
	{
	public:
		CUndoPbd()
		{
		}
		~CUndoPbd()
		{
			if (m_Undo.IsValid()) 
				DEX_AddUndoRedo (m_Undo.p);
		}

		HRESULT ModPBDData(HPROJECT hPr, PBDMERKMAL &rPbdData) 
		{
			return ModPBDData(hPr, reinterpret_cast<PBDDATA &>(rPbdData));
		}
		HRESULT ModPBDData(HPROJECT hPr, PBDDATA &rPbdData) 
		{ 
			_ASSERTE(!m_Undo.IsValid());		// nur einmal rufen

		HRESULT hr = m_Undo.CreateInstance(CLSID_UndoRedoObject);

			if (SUCCEEDED(hr)) 
				hr = m_Undo -> InitModify(&rPbdData, NULL);
			if (FAILED(hr))
				m_Undo.Assign(NULL);

			hr = HRESULT_FROM_ERRCODE(DEX_ModPBDDataEx(hPr, rPbdData)); 
			if (FAILED(hr))
				m_Undo.Assign(NULL);
			return hr;
		}

	private:
		WUndoRedoPBDData m_Undo;
	};

// Helper fürs Undo der Änderungen eines Attributes
	class CUndoAttribute
	{
	public:
		CUndoAttribute()
		{
		}
		~CUndoAttribute()
		{
			if (m_Undo.IsValid()) 
				DEX_AddUndoRedo (m_Undo.p);
		}

		HRESULT ModTextMerkmal(TARGETMERKMAL &rTM)
		{
			_ASSERTE(!m_Undo.IsValid());		// nur einmal rufen
			_ASSERTE(TT_Objekt == rTM.iTTyp);	// funktioniert nur für Objekte

		HRESULT hr = m_Undo.CreateInstance(CLSID_UndoRedoObject);

			if (SUCCEEDED(hr)) 
				hr = m_Undo -> Init(rTM.lTarget, rTM.lMCode, rTM.pMText, NULL);
			if (FAILED(hr))
				m_Undo.Assign(NULL);

			hr = HRESULT_FROM_ERRCODE(DEX_ModTextMerkmal(rTM)); 
			if (FAILED(hr))
				m_Undo.Assign(NULL);
			return hr;
		}

	private:
		WUndoRedoObjectFeature m_Undo;
	};
};

HOBJECTS CCloneObject::GetDestClassFromSrcClass(HPROJECT hPrSrc, HOBJECTS lIdentSrc)
{
PBDDATA pbdData;
char cbKText[_MAX_PATH];
HRESULT hr = S_OK;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdentSrc;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof(cbKText)-1;
	if (EC_OKAY == DEX_GetPBDDataEx(hPrSrc, pbdData)) 
		return DEX_GetIdentFromClassNameEx(GetDestinationProject(), cbKText);

	return INVALID_HOBJECTS;
}

HRESULT CCloneObject::EnsureDestClass(HPROJECT hPrSrc, HOBJECTS lNewIdent, 
	bool fNeedsOKS)
{
// Zielobjektklasse sicherstellen
	if (hPrSrc == GetDestinationProject())
		return S_FALSE;		// nothing to do (here)

PBDDATA pbdData;
char cbKText[_MAX_PATH];
char cbLText[5*_MAX_PATH];
HRESULT hr = S_OK;
HOBJECTS ulOrgIdent = DEX_GetObjIdent(m_lObjToCopy);

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lNewIdent;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof(cbKText)-1;
	pbdData.pbdLText = cbLText;
	pbdData.pbdLTextLen = sizeof(cbLText)-1;

// Neue Objektklasse nur dann schreiben, wenn selbige noch nicht existiert
	if (EC_OKAY != DEX_GetPBDDataEx(GetDestinationProject(), pbdData)) {
	// Beschreibungsdaten umkopieren
		pbdData.pbdCode = ulOrgIdent;

	ErrCode RC = DEX_GetPBDDataEx(hPrSrc, pbdData);

		if (EC_OKAY != RC && WC_RETURN != RC)
			return HRESULT_FROM_ERRCODE(RC);

	CUndoPbd UndoCls;
		
		pbdData.pbdCode = lNewIdent;

		hr = UndoCls.ModPBDData(GetDestinationProject(), pbdData);
		if (FAILED(hr))
			return hr;
	}

// Objektklassenschlüssel nachführen
char cbOKS[MAX_OKS_LEN+2];
CLASSFROMIDENT CFI;

	INITSTRUCT(CFI, CLASSFROMIDENT);
	CFI.pClass = cbOKS;
	CFI.iBuffLen = sizeof(cbOKS)-1;
	CFI.ulIdent = lNewIdent;
	hr = S_OK;

	if (fNeedsOKS || 
		S_OK != (hr = DEX_GetClassFromIdentEx(GetDestinationProject(), CFI))) 
	{
	// OKS kopieren
		CFI.ulIdent = ulOrgIdent;
		hr = DEX_GetClassFromIdentEx(hPrSrc, CFI);
		if (SUCCEEDED(hr)) {
		MODOBJCLASSCODE MOC;

			INITSTRUCT(MOC, MODOBJCLASSCODE);
			MOC.ulIdent = lNewIdent;
			MOC.pcClass = cbOKS;
			MOC.fOverWrite = TRUE;
			return DEX_ModObjectClassCodeEx(GetDestinationProject(), MOC);
		}
	}
	return hr;
}

// Objekt (ggf. in andere Datenquelle) doppeln
HRESULT CCloneObject::Clone (HOBJECTS lNewIdent, HOBJECT *plNewObj)
{
HPROJECT hPrSrc = GetSourceProject();
bool fNeedsOKS = false;

	if (0 == lNewIdent) {
		if (hPrSrc == GetDestinationProject())
			lNewIdent = DEX_GetUnknownIdentEx(hPrSrc);
		else {
		// ggf. gibt es die Objektklasse schon
			lNewIdent = GetDestClassFromSrcClass(hPrSrc, DEX_GetObjIdent(m_lObjToCopy));
			if (INVALID_HOBJECTS == lNewIdent || -1 == lNewIdent)
				lNewIdent = DEX_GetUniqueICodeEx(GetDestinationProject());
			fNeedsOKS = true;
		}
	}

// Objektklasse in Zieldatenquelle sicherstellen
	EnsureDestClass(hPrSrc, lNewIdent, fNeedsOKS);	// Fehler ggf. ignorieren

// Geometrie doppeln (Objekt neu erzeugen)
CObjGeometrie Geom;

	if (!Geom.FillObjGeometrie(m_lObjToCopy))
		return E_FAIL;

// neues Objekt erzeugen
	if (!Geom.CreateNewObject(GetDestinationProject(), lNewIdent))
		return E_FAIL;

// Attribute doppeln, ObjUniqueIdent gesondert behandeln
	m_lNewObject = Geom.lONr;
	RETURN_FAILED_HRESULT(CopyAttributes());
	if (NULL != plNewObj)
		*plNewObj = Geom.lONr;		// neue Objektnummer liefern

	m_fIsValid = true;
	return S_OK;
}

// Neues Objekt (ggf. in andere Datenquelle) doppeln
HRESULT CCloneObject::Clone (CObjGeometrie &Geom, HOBJECTS lNewIdent,
    HOBJECT *plNewObj)
{
HPROJECT hPrSrc = GetSourceProject();
bool fNeedsOKS = false;

	if (INVALID_HOBJECTS == lNewIdent) {
		if (hPrSrc == GetDestinationProject())
			lNewIdent = DEX_GetUnknownIdentEx(hPrSrc);
		else {
		// ggf. gibt es die Objektklasse schon
			lNewIdent = GetDestClassFromSrcClass(hPrSrc, DEX_GetObjIdent(m_lObjToCopy));
			if (INVALID_HOBJECTS == lNewIdent || -1 == lNewIdent)
				lNewIdent = DEX_GetUniqueICodeEx(GetDestinationProject());
			fNeedsOKS = true;
		}
	}

// Objektklasse in Zieldatenquelle sicherstellen
	EnsureDestClass(hPrSrc, lNewIdent, fNeedsOKS);	// Fehler ggf. ignorieren

// neues Objekt erzeugen
	if (!Geom.CreateNewObject(GetDestinationProject(), lNewIdent))
		return E_FAIL;

// Attribute doppeln, ObjUniqueIdent gesondert behandeln
	m_lNewObject = Geom.lONr;
	RETURN_FAILED_HRESULT(CopyAttributes());
	if (NULL != plNewObj)
		*plNewObj = Geom.lONr;		// neue Objektnummer liefern

	m_fIsValid = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Enumeration aller Merkmale
namespace {
// Thunk für Enumeration aller Datenquellen
	class CEnumAttributesThunk :
		public CStdThunk<CCloneObject>
	{
	public:
		typedef CStdThunk<CCloneObject> base_t;

		CEnumAttributesThunk(const CCloneObject *pThis) 
		{
			InitThunk(reinterpret_cast<base_t::TMFP>(CCloneObject::EnumAttributes), pThis);
		}
		~CEnumAttributesThunk() {}

		ENUMLONGKEYPROC GetThunk() { return reinterpret_cast<ENUMLONGKEYPROC>(base_t::GetThunk()); }
	};
}

// ein Attribut kopieren
BOOL CCloneObject::EnumAttributes(HFEATURE lMCode, BOOL, void *pData)
{
HFEATURE *plMCodes = reinterpret_cast<HFEATURE *>(pData);
HFEATURE lDefMCode = 0;

	if (lMCode == plMCodes[0])		// UniqueIdent wird zum OldUniqueIdent
		lDefMCode = DEX_GetOldUniqueIdentMCodeEx(GetDestinationProject());
	else if (lMCode == plMCodes[1])
		return TRUE;	// OldUniqueIdent verschwindet
	else if (lMCode == plMCodes[2])
		return TRUE;	// Guid wird nicht geschrieben

// Objektmerkmal schreiben
TARGETMERKMAL TM;
char cbText[5*_MAX_PATH];

	INITSTRUCT(TM, TARGETMERKMAL);
	TM.iTTyp = TT_Objekt;
	TM.lMCode = lMCode;
	TM.lTarget = m_lObjToCopy;
	TM.pMText = cbText;
	TM.imaxLen = sizeof(cbText)-1;
	if (NULL != DEX_GetTextMerkmal(TM)) {
	// AttributBeschreibung und AttributWert kopieren
	CUndoAttribute UndoFeat;
	HFEATURE lNewMCode = INVALID_HFEATURE;

		EnsureDestAttribute(lMCode, lDefMCode, &lNewMCode);
		_ASSERTE(INVALID_HFEATURE != lNewMCode);

	// Wert wegschreiben
		TM.lMCode = lNewMCode;
		TM.lTarget = m_lNewObject;
		UndoFeat.ModTextMerkmal(TM);
	}	
	return TRUE;		// immer weiter machen
}

// eine Attributbeschreibung in der Zieldatenquelle sicherstellen
HRESULT CCloneObject::EnsureDestAttribute(HFEATURE lMCode, HFEATURE lDefMCode, HFEATURE *plNewMCode)
{
// Beschreibung aus Quelle einlesen
PBDMERKMAL pbdData;
char cbKText[_MAX_PATH];
char cbLText[5*_MAX_PATH];

	INITSTRUCT(pbdData, PBDMERKMAL);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof(cbKText)-1;
	pbdData.pbdLText = cbLText;
	pbdData.pbdLTextLen = sizeof(cbLText)-1;
	DEX_GetPBDDataEx(GetSourceProject(), pbdData);

	pbdData.ipbdMTyp &= ~PBDMERKMAL_READONLY;

// Merkmalscode in neuer Datenquelle wiederfinden
HFEATURE lNewMCode = DEX_GetMCodeFromFeatureNameEx(GetDestinationProject(), cbKText);

	if (NULL != lNewMCode) {
		if (NULL != plNewMCode)
			*plNewMCode = lNewMCode;
		return S_FALSE;		// nothing to do here
	}

	if (0 != lDefMCode) {
		if (NULL != plNewMCode)
			*plNewMCode = lDefMCode;
		return S_FALSE;		// nothing to do here
	}

// versuchen alten MCode beizubehalten
	lNewMCode = DEX_MapHandleToMCode(lMCode);

	if (NULL != lNewMCode) {
	MAPMCODETOHANDLE MTH;
	HFEATURE lMappedMCode = 0L;
	BOOL fCreated = FALSE;

		INITSTRUCT(MTH, MAPMCODETOHANDLE);
		MTH.lIdent = DEX_GetObjIdent(m_lNewObject);
		MTH.lMCode = lNewMCode;
		MTH.plHandle = &lMappedMCode;
		MTH.fCreate = true;
		MTH.pfCreated = &fCreated;
		if (DEX_MapOrCreateMCodeToHandle(GetDestinationProject(), MTH) && 0L != lMappedMCode)
			lNewMCode = lMappedMCode;
	}
	if (NULL == lNewMCode)
		lNewMCode = DEX_GetUniqueMCode();

	pbdData.pbdCode = lNewMCode;

CUndoPbd UndoAttrib;
HRESULT hr = UndoAttrib.ModPBDData(GetDestinationProject(), pbdData);

	if (FAILED(hr))
		return hr;

	if (NULL != plNewMCode)
		*plNewMCode = pbdData.pbdCode;
	return S_OK;
}

// alle Attribute kopieren
HRESULT CCloneObject::CopyAttributes()
{
	_ASSERTE(0 != m_lNewObject);		// neues Objekt muß existieren

// neuen Unique Ident schreiben
TARGETMERKMAL TM;
char cbUniqueId[_MAX_PATH];
ResourceFile RF (g_pDLLName);
ResString resDoppel(ResID(IDS_COPYOBJECTS_UIDENT, &RF), 64);
CUndoAttribute UndoFeat;

	wsprintf (cbUniqueId, "%s%ld", resDoppel.Addr(), m_lNewObject);

	INITSTRUCT(TM, TARGETMERKMAL);
	TM.iTTyp = TT_Objekt;
	TM.lMCode = DEX_GetUniqueIdentMCodeEx(GetDestinationProject());
	TM.lTarget = m_lNewObject;
	TM.pMText = cbUniqueId;
	TM.imaxLen = strlen(cbUniqueId);
	UndoFeat.ModTextMerkmal(TM);

// Attribute enumerieren und kopieren
CEnumAttributesThunk Thunk(this);
ENUMLONGKEY ELK;
HFEATURE lMCodes[3] = { 
		DEX_GetUniqueIdentMCodeEx(GetSourceProject()),
		DEX_GetOldUniqueIdentMCodeEx(GetSourceProject()),
		DEX_GetObjGuidMCode(DEX_GetObjIdent(m_lObjToCopy)),
	};

	ELK.eKey = m_lObjToCopy;
	ELK.eFcn = Thunk.GetThunk();
	ELK.ePtr = reinterpret_cast<void *>(lMCodes);
	return DEX_EnumObjektMerkmale(ELK) ? S_OK : E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// Kopieren eines Objektes (ggf. in eine andere Datenquelle)
HRESULT CloneObject (HPROJECT hPrDest, HOBJECT lObjToCopy, HOBJECTS lNewIdent, HOBJECT *plNewObj)
{
CCloneObject CloneObj(hPrDest, lObjToCopy);

	return CloneObj.Clone(lNewIdent, plNewObj);		// Objekt selbst kopieren
}

#else

#include <bscrguid.h>

#include <eb.h>
#include <ibscript.hxx>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ExtendBScript);

///////////////////////////////////////////////////////////////////////////////
// Kopieren eines Objektes (_nicht_ in eine andere Datenquelle)
HRESULT CloneObject (HPROJECT hPr, HOBJECT lObjToCopy, HOBJECTS lNewIdent, HOBJECT *plNewObj)
{
	_ASSERTE(hPr == DEX_GetObjectsProject(lNewIdent));

HRESULT hr = S_OK;

	COM_TRY {
	// BasicEngine 
	WExtendBScript BScript (CLSID_MacroScriptExtension);	

	// Parameter zusammenbauen
	ebPARAM Pars[3];
	LPVOID cbParam[3];
	BSPARAM bs = { Pars, cbParam };

	// Function CopyGeoObjectEx (Obj As Long, Cls As Long) As Long
		Pars[0].wType = TYP_LONG;
		Pars[0].szExtType[0] = '\0';
		cbParam[0] = plNewObj;

	// Parameter initialisieren
		Pars[1].wType = TYP_LONG;
		Pars[1].szExtType[0] = '\0';
		cbParam[1] = &lObjToCopy;

		Pars[2].wType = TYP_LONG;
		Pars[2].szExtType[0] = '\0';
		cbParam[2] = &lNewIdent;

	// Script starten
		hr = BScript -> RunCodeEx (g_hInstance, IDR_SCRIPT_COPYOBJECTS, "CopyGeoObjectEx", "CopyGeoObjectEx", 2, &bs, TRUE, reinterpret_cast<INT_PTR>(hPr));
		BScript -> StopScript ("CopyGeoObjectEx");

	} COM_CATCH;
	return hr;
}
#endif // _TRiAS_VER >= 0x0420

