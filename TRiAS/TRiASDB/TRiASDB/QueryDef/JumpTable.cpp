// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.03.2000 19:19:20
//
// @doc
// @module JumpTable.cpp | Implementation of the jumptable support

#include "StdAfx.h"

#include "Strings.h"
#include "QueryDef.h"
#include "QueryDefExt.h"
#include "JumpTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjects);
DefineSmartInterface(TRiASObject);
DefineSmartInterface(TRiASCollectObjects);
DefineSmartInterface(UndoRedoAddObjToClass);

///////////////////////////////////////////////////////////////////////////////
// Helperroutinen
#if defined(_DEBUG)
inline bool IsValidONr (INT_PTR lONr) { return 0 != lONr && -1 != lONr; }
inline bool IsValidIdent (INT_PTR lONr) { return 0 != lONr && -1 != lONr; }
#endif // defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
// alle möglichen Windows-Messages hier vorbeischicken
STDMETHODIMP_(LRESULT) CQueryDefExtension::WindowsNotification (
	UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	if (__DexCmd == wMsg) {
		_ASSERTE (NULL != m_cbDexProcs);	// über Sprungverteiler abwickeln

	register unsigned int uiMsg = wParam-m_i1stDexProc;
		
		if (uiMsg >= 0 && uiMsg < m_iDexProcsNum) 
		{
			_ASSERTE(NULL != m_cbDexProcs[uiMsg]);
			return (this ->* m_cbDexProcs[uiMsg])(NULL, lParam);
		}
	}
	return FALSE;		// alles andere normalerweise weiterleiten
}

///////////////////////////////////////////////////////////////////////////////
// Sprungverteilertabelle initialisieren
bool CQueryDefExtension::InitJumpTable()
{
// größten und kleinsten MessageID suchen
unsigned int iFirst = UINT_MAX;
unsigned int iLast = 0;
const DEXMESSAGEENTRY *pDME = DexMessageEntries;

	for (int i = 0; i < _countof(DexMessageEntries); i++, pDME++) {
	UINT uiMsg = pDME -> m_uiMsg;
	
		if (iFirst > uiMsg) iFirst = uiMsg;
		if (iLast < uiMsg) iLast = uiMsg;
	}
	if (iFirst == USHRT_MAX || iLast == 0)
		return false;
	
	m_iDexProcsNum = iLast-iFirst+1;
	m_i1stDexProc = iFirst;

	_ASSERTE(m_iDexProcsNum >= 1);
					
// Tabelle anlegen und initialisieren
	ATLTRY(m_cbDexProcs = new DEXMESSAGEPROC [2*m_iDexProcsNum]);	// BUGBUG: multiple-inheritance pointers, but sizeof(DEXMESSAGEPROC) == 4!
	if (NULL == m_cbDexProcs) return false;

	for (unsigned int j = 0; j < m_iDexProcsNum; j++) 
		 m_cbDexProcs[j] = OnNotImplementedMessage;

// Funktionen eintragen
	pDME = DexMessageEntries;
	for (i = 0; i < _countof(DexMessageEntries); i++, pDME++) {
	// erste Zuweisung ?
		_ASSERTE(OnNotImplementedMessage == m_cbDexProcs[(pDME -> m_uiMsg) - iFirst]);
		m_cbDexProcs[(pDME -> m_uiMsg) - iFirst] = pDME -> m_pProc;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Sprungverteilertabelle freigeben
void CQueryDefExtension::FreeJumpTable()
{
	DELETE_OBJ(m_cbDexProcs);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_... command handler
LRESULT CQueryDefExtension::OnNotImplementedMessage (HPROJECT hPr, LPARAM lParam)
{
	return FALSE;
}

// DEX_ADDOBJECT2CLASS
LRESULT CQueryDefExtension::AddObjectToClass (HPROJECT hPr, LPARAM lParam)
{
ADDOBJECTTOCLASS *pAOC = reinterpret_cast<ADDOBJECTTOCLASS *>(lParam);

	_ASSERTE(!IsBadReadPtr(pAOC, sizeof(ADDOBJECTTOCLASS)));
	_ASSERTE(sizeof(ADDOBJECTTOCLASS) == pAOC -> dwSize);
	_ASSERTE(IsValidONr(pAOC -> lONr));
	_ASSERTE(IsValidIdent(pAOC -> lIdent));
	_ASSERTE(!(pAOC -> iMode & ~(MODIDENT_TYP|MODIDENT_ADDTOVIEW|MODIDENT_TEMP)));

	_ASSERTE(HACTPROJECT == DEX_GetObjectsProject(pAOC -> lIdent));		// muß Zuordnungsobjektklasse sein

// eigentliche Funktionalität
	if (HACTPROJECT != DEX_GetObjectsProject(pAOC -> lIdent)) {
		SetLastError(E_UNEXPECTED);
		return FALSE;	// muß Zuordnungsobjektklasse sein
	}

HRESULT hr = S_FALSE;	// Defaultwert bedeutet: existiert schon in dieser Objektklasse

	COM_TRY {
	// 'native' Handle sicherstellen
	WTRiASObjects Objs;
	WTRiASObject Obj;
	INT_PTR hObj = NULL;
	INT_PTR hObjMapped = NULL;

		THROW_FAILED_HRESULT(GetObjectsFromMap (pAOC -> lIdent, Objs));	// Objektmenge muß existieren
		THROW_FAILED_HRESULT(GetObjectFromMap (pAOC -> lONr, Obj));		// Objekt muß existieren
		THROW_FAILED_HRESULT(Obj -> get_Handle (&hObj));

	WTRiASObject ObjT;

		if (S_OK != Objs -> Item (CComVariant(hObj), ObjT.ppi())) {
		// nur einfügen, wenn das Objekt noch nicht dazugehört
			THROW_FAILED_HRESULT(Objs -> _Add (Obj, VARIANT_FALSE));
			hr = S_OK;
		}

		if (NULL != pAOC -> plNewONr) {
		WTRiASCollectObjects CollObjs;

			if (FAILED(Objs -> QueryInterface(CollObjs.ppi())) ||
				FAILED(CollObjs -> GetMappedObjectHandle (hObj, &hObjMapped))) {
			// Zuordnungsobjektklasse unterstützt unser Interface nicht (snh)
				*(pAOC -> plNewONr) = NULL;
			} else 
				*(pAOC -> plNewONr) = hObjMapped;
		}

	// Ident ggf. zur Ansicht hinzufügen
	ADDNEWIDENT ANI;

		ANI.newIdent = pAOC -> lIdent;
		ANI.iFlags = ANI_Unload|ANI_CountObjects;
		ANI.iTyp = pAOC -> iMode & MODIDENT_TYP;
		if (pAOC -> iMode & MODIDENT_TEMP) 
			ANI.iFlags |= ANI_Temp;
		if (pAOC -> iMode & MODIDENT_ADDTOVIEW) 
			ANI.iFlags |= ANI_AddToView;
		if (!DEX_AddNewIdentEx (ANI))
			hr = GetLastError();

	// ggf. Undo initialisieren
		if (pAOC -> fUndoRedo) {
		WUndoRedoAddObjToClass Undo;

			THROW_FAILED_HRESULT(Undo.CreateInstance (CLSID_UndoRedoAddObjToClass));
			THROW_FAILED_HRESULT(Undo -> InitAddObjectToClass (pAOC -> lONr, pAOC -> lIdent, hObjMapped));
			DEX_AddUndoRedo ((IUndoRedo *)Undo);
		}

	} COM_CATCH_RETURN(FALSE);
	SetLastError(hr);
	return SUCCEEDED(hr);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_DELETEOBJECTFROMCLASS
namespace {
	BOOL CALLBACK EnumAllORWnds (long hWnd, BOOL, void *pData)
	{
		DEXOR_RemoveFromListObject (reinterpret_cast<HWND>(hWnd), *reinterpret_cast<INT_PTR *>(pData));
		return TRUE;
	}

	BOOL CALLBACK EnumAllORWndsWithUndo (long hWnd, BOOL, void *pData)
	{
		DEXOR_RemoveFromListObjectEx (reinterpret_cast<HWND>(hWnd), *reinterpret_cast<INT_PTR *>(pData));
		return TRUE;
	}
}

LRESULT CQueryDefExtension::DeleteObjectFromClass (HPROJECT hPr, LPARAM lParam)
{
DELOBJECTFROMCLASS *pDOC = reinterpret_cast<DELOBJECTFROMCLASS *>(lParam);

	_ASSERTE(!IsBadReadPtr(pDOC, sizeof(DELOBJECTFROMCLASS)));
	_ASSERTE(sizeof(DELOBJECTFROMCLASS) == pDOC -> dwSize);
	_ASSERTE(IsValidONr(pDOC -> lONr));
	_ASSERTE(IsValidIdent(pDOC -> lIdent));

	_ASSERTE(HACTPROJECT == DEX_GetObjectsProject(pDOC -> lIdent));		// muß Zuordnungsobjektklasse sein

	return DeleteObjectFromClass (pDOC -> lIdent, pDOC -> lONr, pDOC -> fUndoRedo);
}

LRESULT CQueryDefExtension::DeleteObjectFromClass (INT_PTR lIdent, INT_PTR lONr, BOOL fEnableUndo)
{
// eigentliche Funktionalität
	if (HACTPROJECT != DEX_GetObjectsProject(lIdent) || !IsObjectInClass (lIdent, lONr)) 
	{
	// ist keine Zuordnungsobjektklasse bzw. ist in keiner bzw. nicht in dieser Zuordnungsobjektklasse
		SetLastError(E_INVALIDARG);
		return FALSE;
	}

	COM_TRY {
	// ggf. Undo initialisieren
	WUndoRedoAddObjToClass Undo;

		if (fEnableUndo) {
			THROW_FAILED_HRESULT(Undo.CreateInstance (CLSID_UndoRedoAddObjToClass));
			THROW_FAILED_HRESULT(Undo -> InitDeleteObjectFromClass (lONr, lIdent));
		}

	// 'native' handle besorgen
	WTRiASObject Obj;
	INT_PTR hObj = NULL;

		_ASSERTE(0 != DEX_GetNativeObject (lONr));		// sollte Zuordnungsobjekt sein
		THROW_FAILED_HRESULT(GetObjectFromMap (lONr, Obj));
		THROW_FAILED_HRESULT(Obj -> get_Handle (&hObj));

	// Objekt aus allen ORFenstern entfernen
	ENUMNOKEYLONG EORWND;

		EORWND.eFcn = fEnableUndo ? 
			reinterpret_cast<ENUMNOKEYLONGPROC>(EnumAllORWndsWithUndo) : 
			reinterpret_cast<ENUMNOKEYLONGPROC>(EnumAllORWnds);
		EORWND.ePtr = &lONr;
		DEX_EnumORWindows(EORWND);

	// Objekt aus der (Zuordnungs-)Objektklasse entfernen
	WTRiASObjects Objs;

		THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));		// Objektmenge muß existieren
		THROW_FAILED_HRESULT(Objs -> _Remove (CComVariant(hObj)));

	// Objekt entladen (sollte alles freigeben)
		DEX_UnloadObject (lONr);

	// ggf. Undo initialisieren
		if (fEnableUndo) 
			DEX_AddUndoRedo ((IUndoRedo *)Undo);

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// DEX_OBJECTISINCLASS
LRESULT CQueryDefExtension::IsObjectInClass (HPROJECT hPr, LPARAM lParam)
{
ISOBJECTINCLASS *pIOC = reinterpret_cast<ISOBJECTINCLASS *>(lParam);

	_ASSERTE(!IsBadReadPtr(pIOC, sizeof(ISOBJECTINCLASS)));
	_ASSERTE(sizeof(ISOBJECTINCLASS) == pIOC -> dwSize);
	_ASSERTE(IsValidONr(pIOC -> lONr));
	_ASSERTE(IsValidIdent(pIOC -> lIdent));

	_ASSERTE(HACTPROJECT == DEX_GetObjectsProject(pIOC -> lIdent));	// muß Zuordnungsobjektklasse sein

// eigentliche Funktionalität
	if (HACTPROJECT != DEX_GetObjectsProject(pIOC -> lIdent)) {
		SetLastError(E_UNEXPECTED);
		return FALSE;	// muß Zuordnungsobjektklasse sein
	}
	return IsObjectInClass (pIOC -> lIdent, pIOC -> lONr, pIOC -> plONrMapped);
}

BOOL CQueryDefExtension::IsObjectInClass (INT_PTR lIdent, INT_PTR lONr, INT_PTR *plONrMapped)
{
	COM_TRY {
	// 'native' Handle besorgen
	WTRiASObject Obj;
	INT_PTR hObj = NULL;

		THROW_FAILED_HRESULT(GetObjectFromMap (lONr, Obj));
		THROW_FAILED_HRESULT(Obj -> get_Handle (&hObj));

	// Feststellen, ob das Objekt zu dieser (Zuordnungs-)Objeklasse gehört
	WTRiASObjects Objs;

		THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));	// Objektmenge muß existieren
		if (FAILED(Objs -> Item (CComVariant(hObj), Obj.ppi())))
			return FALSE;		// nicht enthalten

	// ggf. Pseudo-Objektnummer liefern (macht nur Sinn, wenn pIOC -> lONr bereits 'native' ist)
		if (NULL != plONrMapped) {
			_ASSERTE(hObj == lONr);

		WTRiASCollectObjects CollObjs;

			if (FAILED(Objs -> QueryInterface(CollObjs.ppi())) ||
				FAILED(CollObjs -> GetMappedObjectHandle (hObj, plONrMapped)))
			{
				*plONrMapped = hObj;	// ursprüngliche Objektnummer liefern
			} 
		}

	} COM_CATCH_RETURN(FALSE);
	return TRUE;		// enthalten
}

///////////////////////////////////////////////////////////////////////////////
// DEX_ENUMCLASSESFROMOBJECT
namespace {
// Helper zum Auffruf der gewünschten callback-Funktion
	inline BOOL EnumObjectClassesCallback (
		BOOL (*pFcn)(long, DWORD, void *), long lIdent, DWORD dwData, void *pData) 
	{
		return ((ENUMLONGKEYEXCALLBACK)pFcn)(lIdent, dwData, pData);
	}

// callback-Funktion zur Enumeration von Objektklassen in verschiedenen Kontexts
	BOOL CALLBACK EnumIdentsForViewOrAll (long lIdent, BOOL, void *pData)
	{
		if (HACTPROJECT != DEX_GetObjectsProject(lIdent))
			return TRUE;		// keine Zuordnungsobjektklasse

	ENUMLONGKEYEX *pK = reinterpret_cast<ENUMLONGKEYEX *>(pData);
	INT_PTR hObj = NULL;

		if (((CQueryDefExtension *)g_pTE) -> IsObjectInClass (lIdent, pK -> eKey, &hObj)) {
		// Objekt gehört zu dieser Objektklasse
			if (!EnumObjectClassesCallback (pK -> eFcn, lIdent, hObj, pK -> ePtr))
				return FALSE;
		}
		return TRUE;
	}
}

LRESULT CQueryDefExtension::EnumObjectClasses (HPROJECT hPr, LPARAM lParam)
{
ENUMLONGKEYEX *pK = reinterpret_cast<ENUMLONGKEYEX *>(lParam);

	_ASSERTE(!IsBadReadPtr(pK, sizeof(ENUMLONGKEYEX)));
	_ASSERTE(!IsBadCodePtr((FARPROC)pK -> eFcn));
	_ASSERTE(IsValidONr((long)pK -> eKey));

// sicherstellen, daß gegebene Objektnummer zum 'native' Objekt gehört

	COM_TRY {
	INT_PTR hObj = NULL;
	WTRiASObject Obj;

		THROW_FAILED_HRESULT(GetObjectFromMap ((long)pK -> eKey, Obj));
		THROW_FAILED_HRESULT(Obj -> get_Handle (&hObj));
		pK -> eKey = hObj;

	} COM_CATCH_RETURN(FALSE);

// evtl. eigene Objektklasse liefern
	if (!(pK -> eData & CFO_QueryDefsOnly)) {
	INT_PTR lIdent = DEX_GetObjIdent (pK -> eKey);

		if (!EnumObjectClassesCallback (pK -> eFcn, lIdent, pK -> eKey, pK -> ePtr))
			return FALSE;
	}
	if (pK -> eData & CFO_NativeDefsOnly)
		return TRUE;		// lediglich Originalobjektklasse enumerieren

// alle Zuordnungsobjektklassen durchgehen
BOOL fResult = FALSE;

	if (pK -> eData & CFO_ActViewOnly) {
	// nur aktuelle Ansicht auswerten
	ENUMTEXTKEY ETK;

		ETK.eKey = NULL;
		ETK.eFcn = reinterpret_cast<ENUMLONGKEYPROC>(EnumIdentsForViewOrAll);
		ETK.ePtr = pK;		// einfach weiterreichen
		fResult = DEX_EnumSightIdents (ETK);
	} 
	else {
	// alle Objektklassen durchgehen
	ENUMNOKEYLONG ENK;

		ENK.eFcn = reinterpret_cast<ENUMLONGKEYPROC>(EnumIdentsForViewOrAll);
		ENK.ePtr = pK;		// einfach weiterreichen
		fResult = DEX_EnumIdents (ENK);
	}
	return fResult;
}

///////////////////////////////////////////////////////////////////////////////
// DEX_QUERYNATIVEOBJECT
LRESULT CQueryDefExtension::OnGetNativeObject (HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(IsValidONr((long)lParam));

INT_PTR hObj = NULL;

	COM_TRY {
	WTRiASObject Obj;

		THROW_FAILED_HRESULT(GetObjectFromMap ((long)lParam, Obj));
		THROW_FAILED_HRESULT(Obj -> get_Handle (&hObj));
		if (hObj == (INT_PTR)lParam)
			hObj = NULL;		// kein Objekt aus einer Zuordnungsobjektklasse

	} COM_CATCH_RETURN(NULL);
	return (LRESULT)hObj;
}

///////////////////////////////////////////////////////////////////////////////
// DEX_QUERYOBJIDENT
namespace {
// Enumerationsfunktion zum Finden eines Objektes in einer Zuordnungsobjektklasse
	BOOL CALLBACK EnumIdentsForTest (long lIdent, BOOL, void *pData)
	{
		if (HACTPROJECT != DEX_GetObjectsProject(lIdent))
			return TRUE;		// keine Zuordnungsobjektklasse

	OBJECTCLASSPAIR *pOCP = reinterpret_cast<OBJECTCLASSPAIR *>(pData);

		if (((CQueryDefExtension *)g_pTE) -> IsObjectInClass (lIdent, pOCP -> lONr)) {
		// Objekt gehört zu dieser Objektklasse
			pOCP -> lIdent = lIdent;
			return FALSE;	// abbrechen, gefunden
		}
		return TRUE;
	}
}

LRESULT CQueryDefExtension::GetObjectIdent (INT_PTR lONr)
{
ENUMNOKEYLONG ENK;
OBJECTCLASSPAIR OCP;

	INITSTRUCT(OCP, OBJECTCLASSPAIR);
	OCP.lONr = lONr;

	ENK.eFcn = reinterpret_cast<ENUMLONGKEYPROC>(EnumIdentsForTest);
	ENK.ePtr = &OCP;
	DEX_EnumIdents (ENK);

	return OCP.lIdent;		// wenn nichts gefunden, dann weiterreichen
}

LRESULT CQueryDefExtension::OnGetObjectIdent (HPROJECT hPr, LPARAM lParam)
{
	if (HACTPROJECT != DEX_GetContextDataSource() || 0 == OnGetNativeObject(NULL, lParam))
		return 0L;		// not here, delegate to standard routine

	return GetObjectIdent (lParam);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_DELOBJECT
LRESULT CQueryDefExtension::OnDeleteObject (HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(IsValidONr(lParam));
	if (0 == OnGetNativeObject(NULL, lParam))
		return FALSE;		// not here, delegate to standard routine

	return DeleteObjectFromClass (GetObjectIdent(lParam), lParam);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_DELOBJECTEX
LRESULT CQueryDefExtension::OnDeleteObjectEx (HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(IsValidONr(lParam));
	if (0 == OnGetNativeObject(NULL, lParam))
		return FALSE;		// not here, delegate to standard routine

	return DeleteObjectFromClass (GetObjectIdent(lParam), lParam, TRUE);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_DELETEOBJECTUNDORECT
LRESULT CQueryDefExtension::OnDeleteObjectUndorect (HPROJECT hPr, LPARAM lParam)
{
DELETEOBJECTRECT *pDOR = reinterpret_cast<DELETEOBJECTRECT *>(lParam);

	_ASSERTE(!IsBadReadPtr(pDOR, sizeof(DELETEOBJECTRECT)));
	_ASSERTE(sizeof(DELETEOBJECTRECT) == pDOR -> dwSize);
	_ASSERTE(IsValidONr(pDOR -> lONr));
	_ASSERTE(!pDOR -> fWithParentUndo || pDOR -> fUndo);

	if (0 == OnGetNativeObject(NULL, pDOR -> lONr))
		return FALSE;		// not here, delegate to standard routine

	return DeleteObjectFromClass (GetObjectIdent(pDOR -> lONr), pDOR -> lONr, pDOR -> fUndo);
}

