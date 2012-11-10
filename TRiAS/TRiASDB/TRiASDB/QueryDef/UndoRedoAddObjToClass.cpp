// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 20.03.2000 15:11:46
//
// @doc
// @module UndoRedoAddObjToClass.cpp | Implementation of the <c CUndoRedoAddObjToClass> class

#include "stdafx.h"

#include "QueryDef.h"
#include "UndoRedoAddObjToClass.h"

/////////////////////////////////////////////////////////////////////////////
// CUndoRedoAddObjToClass

STDMETHODIMP_(DWORD) CUndoRedoAddObjToClass::Capabilities(signed char **pDesc)
{
	if (!m_fIsInitialized)
		return UNDOREDOCAPS_NOFLAGS;

	if (NULL != pDesc) {
	CString strUndo;

		VERIFY(strUndo.LoadString (m_fIsAddAction ? IDS_ADDTOCLASS_UNDO_ITEM : IDS_DELETEFROMCLASS_UNDO_ITEM));
		*pDesc = (signed char *)CoTaskMemAlloc (_MAX_PATH);
		if (NULL != *pDesc)
			wsprintf ((char *)*pDesc, strUndo, m_lONr);
	}
	return UNDOREDOCAPS_CANUNDO| UNDOREDOCAPS_CANREDO|UNDOREDOCAPS_REPAINT;
}

namespace {
// Umrechnen der verschiedenen Darstellungsformen der Objekttypen 
	short OTypToBits (int iOTyp)
	{
		switch (iOTyp) {
		case OGPunkt:	return OTPunkt;
		case OGLinie:	return OTLinie;
		case OGFlaeche:
		case OGKreis:	return OTFlaeche;
		case OGLabel:
		case OGText:	return OTText;
		case OGKO:		return (OTPunkt|OTLinie|OTFlaeche|OTText);
		case OGUnknown:
		default:
				break;
		}
		return 0;
	}
}

STDMETHODIMP CUndoRedoAddObjToClass::Undo ()
{
	if (!m_fIsInitialized)
		return E_UNEXPECTED;

	if (m_fIsAddAction) {
	// AddObjectAsClass
		_ASSERTE(NULL != m_lONrMapped);

	DELOBJECTFROMCLASS OCP;

		INITSTRUCT(OCP, DELOBJECTFROMCLASS);
		OCP.lIdent = m_lIdent;
		OCP.lONr = m_lONrMapped;
		OCP.fUndoRedo = FALSE;
		if (DEX_DelObjectFromClass(OCP))
			m_lONrMapped = NULL;

	} else {
	// DeleteObjectFromClass
	ADDOBJECTTOCLASS AOTC;
	INT_PTR hObjMapped = NULL;

		INITSTRUCT(AOTC, ADDOBJECTTOCLASS);
		AOTC.lONr = m_lONr;
		AOTC.lIdent = m_lIdent;
		AOTC.iMode = OTypToBits (DEX_GetObjectType(m_lONr));
		AOTC.plNewONr = &hObjMapped;
		AOTC.fUndoRedo = FALSE;
		if (DEX_AddObjectToClass (AOTC) && NULL != hObjMapped)
			m_lONrMapped = hObjMapped;
	}
	return S_OK;
}

STDMETHODIMP CUndoRedoAddObjToClass::Redo ()
{
	if (!m_fIsInitialized)
		return E_UNEXPECTED;

	if (m_fIsAddAction) {
	// AddObjectAsClass
	ADDOBJECTTOCLASS AOTC;
	INT_PTR hObjMapped = NULL;

		INITSTRUCT(AOTC, ADDOBJECTTOCLASS);
		AOTC.lONr = m_lONr;
		AOTC.lIdent = m_lIdent;
		AOTC.iMode = OTypToBits (DEX_GetObjectType(m_lONr));
		AOTC.plNewONr = &hObjMapped;
		AOTC.fUndoRedo = FALSE;
		if (DEX_AddObjectToClass (AOTC) && NULL != hObjMapped)
			m_lONrMapped = hObjMapped;

	} else {
	// DeleteObjectFromClass
		_ASSERTE(NULL != m_lONrMapped);

	DELOBJECTFROMCLASS OCP;

		INITSTRUCT(OCP, DELOBJECTFROMCLASS);
		OCP.lIdent = m_lIdent;
		OCP.lONr = m_lONrMapped;
		OCP.fUndoRedo = FALSE;
		if (DEX_DelObjectFromClass(OCP))
			m_lONrMapped = NULL;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IUndoRedoAddObjToClass
STDMETHODIMP CUndoRedoAddObjToClass::InitAddObjectToClass (INT_PTR lONr, INT_PTR lIdent, INT_PTR lONrMapped)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;	// nur einmal initialisieren

	m_lONr = lONr;				// Bezugsobjekt
	m_lIdent = lIdent;			// Zuordnungsobjektklasse
	m_lONrMapped = lONrMapped;	// Zuordnungsobjekt

	_ASSERTE(DEX_GetObjIdent(m_lONrMapped) != DEX_GetObjIdentEx(m_lONrMapped));

	m_fIsAddAction = true;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CUndoRedoAddObjToClass::InitDeleteObjectFromClass (INT_PTR lONr, INT_PTR lIdent)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;	// nur einmal initialisieren

	m_lONr = DEX_GetNativeObject(lONr);		// Bezugsobjekt bestimmen
	m_lIdent = lIdent;			// Zuordnungsobjektklasse
	m_lONrMapped = lONr;		// Zuordnungsobjekt

	_ASSERTE(DEX_GetObjIdent(m_lONrMapped) != DEX_GetObjIdentEx(m_lONrMapped));
	_ASSERTE(m_lONr != lONr);

	m_fIsAddAction = false;
	m_fIsInitialized = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPropagateObjectNumber
STDMETHODIMP CUndoRedoAddObjToClass::GetUndoObjectNumber (INT_PTR *plONr)
{
	if (NULL == plONr)
		return E_POINTER;

	if (m_fIsAddAction)
		*plONr = 0L;			// Objekt existiert nicht mehr
	else
		*plONr = m_lONrMapped;
	return S_OK;
}

STDMETHODIMP CUndoRedoAddObjToClass::SetUndoObjectNumber (INT_PTR lONr)
{
	return E_NOTIMPL;
}

STDMETHODIMP CUndoRedoAddObjToClass::GetRedoObjectNumber (INT_PTR *plONr)
{
	if (NULL == plONr)
		return E_POINTER;

	if (m_fIsAddAction)
		*plONr = m_lONrMapped;
	else
		*plONr = 0L;			// Objekt existiert nicht mehr
	return S_OK;
}

STDMETHODIMP CUndoRedoAddObjToClass::SetRedoObjectNumber (INT_PTR lONr)
{
	return E_NOTIMPL;
}

