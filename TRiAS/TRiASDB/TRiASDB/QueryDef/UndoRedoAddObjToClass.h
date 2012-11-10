// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 20.03.2000 15:10:25 
//
// @doc
// @module UndoRedoAddObjToClass.h | Declaration of the <c CUndoRedoAddObjToClass> class

#if !defined(_UNDOREDOADDOBJTOCLASS_H__33BB7734_BE87_4631_8869_4E008537CCF8__INCLUDED_)
#define _UNDOREDOADDOBJTOCLASS_H__33BB7734_BE87_4631_8869_4E008537CCF8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CUndoRedoAddObjToClass
class ATL_NO_VTABLE CUndoRedoAddObjToClass : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUndoRedoAddObjToClass, &CLSID_UndoRedoAddObjToClass>,
	public IUndoRedoAddObjToClass,
	public IPropagateObjectNumber
{
public:
	CUndoRedoAddObjToClass() :
		m_lONr(NULL), m_lIdent(NULL), m_lONrMapped(NULL),
		m_fIsInitialized(false), m_fIsAddAction(false)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_UNDOREDOADDOBJTOCLASS)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CUndoRedoAddObjToClass)
		COM_INTERFACE_ENTRY(IUndoRedoAddObjToClass)
		COM_INTERFACE_ENTRY(IUndoRedo)
		COM_INTERFACE_ENTRY(IPropagateObjectNumber)
	END_COM_MAP()

// IPropagateObjectNumber
	STDMETHOD(GetUndoObjectNumber)(INT_PTR *plONr);
	STDMETHOD(SetUndoObjectNumber)(INT_PTR lONr);
	STDMETHOD(GetRedoObjectNumber)(INT_PTR *plONr);
	STDMETHOD(SetRedoObjectNumber)(INT_PTR lONr);

// IUndoRedo
	STDMETHOD_(DWORD, Capabilities) (signed char **pDesc);
	STDMETHOD(Undo)();
	STDMETHOD(Redo)();

// IUndoRedoAddObjToClass
public:
	STDMETHOD(InitAddObjectToClass)(INT_PTR lONr, INT_PTR lIdent, INT_PTR lONrMapped);
	STDMETHOD(InitDeleteObjectFromClass)(INT_PTR lONr, INT_PTR lIdent);

private:
	INT_PTR m_lONr;			// Objektnummer des Bezugsobjektes
	INT_PTR m_lIdent;		// Objektnummer der Zuordnungsobjektklasse
	INT_PTR m_lONrMapped;	// Objektnummer des erzeugten Zuordnungsobjektes

	bool m_fIsAddAction;
	bool m_fIsInitialized;
};

#endif // !defined(_UNDOREDOADDOBJTOCLASS_H__33BB7734_BE87_4631_8869_4E008537CCF8__INCLUDED_)
