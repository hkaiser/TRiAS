// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.03.2000 14:58:52
//
// @doc
// @module RemoveFromObjectClass.cpp | Implementation of the <c CRemoveFromObjectClass> class

#include "stdafx.h"

#include "QueryDef.h"
#include "RemoveFromObjectClass.h"

#include <Com/PropertyActionBase.cpp>	// include once

/////////////////////////////////////////////////////////////////////////////
// CRemoveFromObjectClass
// IPropertyAction 

STDMETHODIMP CRemoveFromObjectClass::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	return S_OK;
}

STDMETHODIMP CRemoveFromObjectClass::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY {
	WEnumLONG EnumObjs;
	OutEnumLONG iter_out_if (&m_Objects);

		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);

	} COM_CATCH;
	return S_OK;
}

namespace {
///////////////////////////////////////////////////////////////////////////////
// Klasse, die die Verarbeitung der einzelnen Objekte der Eingabemenge erlaubt
	class CRemoveFromObjectClassWorker 
	{
	public:
		CRemoveFromObjectClassWorker(OutEnumLONG &rOutIter, CRemoveFromObjectClass *pThis) : 
			m_pPA(pThis), m_rOutIter(rOutIter)
		{
		}
		~CRemoveFromObjectClassWorker() {}

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
			_ASSERTE(NULL != m_pPA);
			m_pPA -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pPA -> GoOn()))
				_com_issue_error(E_ABORT);

		INT_PTR lONrNative = DEX_GetNativeObject (lONr);

			if (0 == lONrNative)
				return;			// kein Objekt aus Zuordnungsobjektklasse

			_ASSERTE(DEX_GetObjIdent(lONr) != DEX_GetObjIdentEx(lONr));

		DELOBJECTFROMCLASS OCP;

			INITSTRUCT(OCP, DELOBJECTFROMCLASS);
			OCP.lIdent = DEX_GetObjIdentEx (lONr);
			OCP.lONr = lONr;
			OCP.fUndoRedo = m_pPA -> IsUndoEnabled();
			if (DEX_DelObjectFromClass(OCP))
				m_rOutIter++ = lONrNative;		// native (target) object is added to the output collection
		}

	private:
		CRemoveFromObjectClass *m_pPA;
		OutEnumLONG &m_rOutIter;
	};
} // namespace

STDMETHODIMP CRemoveFromObjectClass::EndAction (DWORD, IDataObject **ppDataObj)
{
	COM_TRY {
	// ProgressIndikator initialisieren
		SetMaxTicks (m_Objects.Count());

	// Undo initialisieren
	CString strUndo;

		VERIFY(strUndo.LoadString (IDS_DELETEFROMCLASS_UNDO));
		BeginUndoLevel (strUndo);

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge

		{
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

			for_each(InEnumLONG(&m_Objects), InEnumLONG(), CRemoveFromObjectClassWorker(iter_out, this));
		} // iter_out goes out of scope

	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

		EndUndoLevel();

	} COM_CATCH_OP_NOASSERT_ON(CancelUndoLevel(false), E_ABORT);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CRemoveFromObjectClass::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}
