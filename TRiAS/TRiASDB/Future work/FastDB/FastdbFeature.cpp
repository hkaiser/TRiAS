// $Header: $
// Copyright� 1998-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.02.2000 11:15:18 
//
// This file was generated by the TRiASDB Data Server Wizard V1.01.076 (#HK000225)
//
// @doc
// @module FastdbFeature.cpp | Implementation of the <c CFastdbFeature> class

#include "stdafx.h"

#include <Com/ComBool.h>

#include "Strings.h"

#include "Fastdb.h"
#include "FastdbDatabase.h"
#include "FastdbFeature.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFastdbFeature

STDMETHODIMP CFastdbFeature::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASFeature,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASFeatureCallback
STDMETHODIMP CFastdbFeature::get_DefaultType (BSTR *pbstrType)
{
	CHECKOUTPOINTER(pbstrType);

CIID Guid (GetObjectCLSID());
CComBSTR bstrType (Guid.ProgID().c_str());

	*pbstrType = bstrType.Detach();
	return S_OK;
}

STDMETHODIMP CFastdbFeature::SetupFeature (SETUPFEATUREMODE rgMode)
{
	return S_OK;
}

STDMETHODIMP CFastdbFeature::OnChanging(CHANGEDFEATURE rgWhat, VARIANT vNewValue, VARIANT_BOOL *pDisAllow)
{
	CHECKOUTPOINTER(pDisAllow);

	*pDisAllow = VARIANT_FALSE;		// immer einverstanden sein
	return S_OK;
}

STDMETHODIMP CFastdbFeature::OnChanged(CHANGEDFEATURE rgWhat, VARIANT vOldValue)
{
	switch (rgWhat) {
	case CHANGEDFEATURE_Name:
		return OnChangedName();

	case CHANGEDFEATURE_Description:
		return OnChangedDescription();

	case CHANGEDFEATURE_Handle:
		return OnChangedHandle();

	case CHANGEDFEATURE_ROMode:
		return OnChangedROMode();

	case CHANGEDFEATURE_Value:
		break;

	case CHANGEDFEATURE_Type:
		return OnChangedType();

	default:
		_ASSERTE(SUCCEEDED(E_INVALIDARG));
		break;
	}
	return E_INVALIDARG;
}

HRESULT CFastdbFeature::OnChangedName()
{
	USES_CONVERSION;
	COM_TRY {
	// neuen Namen vom Bezugsobjekt besorgen
	CComBSTR bstrName;
	WTRiASFeature BaseFeat;

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
		THROW_FAILED_HRESULT(BaseFeat -> get_Name(CLEARED(&bstrName)))

	// zugeh�riges DB-Objekt referenzieren
	LONG lCursor (GetPropertyFrom (BaseFeat, g_cbFeatureCursor, 0L));

		if (0 != lCursor) {	// Objekt fertig initialisiert
		dbCursor<CDBFeatureDesc> cursor (GetRelatedDatabase(GetUnknown()), dbCursorForUpdate);
		CDBFeatureDesc *pFeatDesc = cursor.at (dbReference<CDBFeatureDesc>(oid_t(lCursor)));

			if (NULL == pFeatDesc || cursor.isEmpty())
				THROW_FAILED_HRESULT(FASTDB_E_FEATURE_BADREFERENCE);

			cursor -> m_pName = OLE2A(bstrName);
			cursor.update();
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT CFastdbFeature::OnChangedDescription()
{
	USES_CONVERSION;
	COM_TRY {
	// neue Beschreibung vom Bezugsobjekt besorgen
	CComBSTR bstrDesc;
	WTRiASFeature BaseFeat;

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
		THROW_FAILED_HRESULT(BaseFeat -> get_Description(CLEARED(&bstrDesc)))

	// zugeh�riges DB-Objekt referenzieren
	LONG lCursor (GetPropertyFrom (BaseFeat, g_cbFeatureCursor, 0L));

		if (0 != lCursor) {	// Objekt fertig initialisiert
		dbCursor<CDBFeatureDesc> cursor (GetRelatedDatabase(GetUnknown()), dbCursorForUpdate);
		CDBFeatureDesc *pFeatDesc = cursor.at (dbReference<CDBFeatureDesc>(oid_t(lCursor)));

			if (NULL == pFeatDesc || cursor.isEmpty())
				THROW_FAILED_HRESULT(FASTDB_E_FEATURE_BADREFERENCE);

			cursor -> m_pDesc = OLE2A(bstrDesc);
			cursor.update();
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT CFastdbFeature::OnChangedHandle()
{
	return S_OK;
}

HRESULT CFastdbFeature::OnChangedType()
{
	COM_TRY {
	// neuen Typ vom Bezugsobjekt besorgen
	FEATURETYPE rgType = FEATURETYPE_Unknown;
	WTRiASFeature BaseFeat;

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
		THROW_FAILED_HRESULT(BaseFeat -> get_Type(&rgType))

	// zugeh�riges DB-Objekt referenzieren
	LONG lCursor (GetPropertyFrom (BaseFeat, g_cbFeatureCursor, 0L));

		if (0 != lCursor) {	// Objekt fertig initialisiert
		dbCursor<CDBFeatureDesc> cursor (GetRelatedDatabase(GetUnknown()), dbCursorForUpdate);
		CDBFeatureDesc *pFeatDesc = cursor.at (dbReference<CDBFeatureDesc>(oid_t(lCursor)));

			if (NULL == pFeatDesc || cursor.isEmpty())
				THROW_FAILED_HRESULT(FASTDB_E_FEATURE_BADREFERENCE);

			cursor -> m_rgType = rgType;
			cursor.update();
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT CFastdbFeature::OnChangedROMode()
{
	COM_TRY {
	// neuen Schreibschutzmode vom Bezugsobjekt besorgen
	CComBool fUpdatable;
	WTRiASFeature BaseFeat;

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
		THROW_FAILED_HRESULT(BaseFeat -> get_Updatable(&fUpdatable))

	// zugeh�riges DB-Objekt referenzieren
	LONG lCursor (GetPropertyFrom (BaseFeat, g_cbFeatureCursor, 0L));

		if (0 != lCursor) {	// Objekt fertig initialisiert
		dbCursor<CDBFeatureDesc> cursor (GetRelatedDatabase(GetUnknown()), dbCursorForUpdate);
		CDBFeatureDesc *pFeatDesc = cursor.at (dbReference<CDBFeatureDesc>(oid_t(lCursor)));

			if (NULL == pFeatDesc || cursor.isEmpty())
				THROW_FAILED_HRESULT(FASTDB_E_FEATURE_BADREFERENCE);

			cursor -> m_fROMode = !fUpdatable;
			cursor.update();
		}

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Eval: Das, worum es eigentlich geht: Wert der Objekteigenschaft abfragen
STDMETHODIMP CFastdbFeature::Eval(ITRiASObject *pIObj, VARIANT *pVal)
{
	USES_CONVERSION;
	COM_TRY {
	WTRiASFeature BaseFeat;
	CComBSTR bstrName;

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));
		THROW_FAILED_HRESULT(BaseFeat -> get_Name(&bstrName));

	CComBSTR bstrVal;
	LONG lObjCursor = GetPropertyFrom (pIObj, g_cbObjectCursor, 0L);
	LONG lThisCursor = GetPropertyFrom (BaseFeat, g_cbFeatureCursor, 0L);

		_ASSERTE(0 != lObjCursor);
		_ASSERTE(0 != lThisCursor);

	// Objektdaten zuordnen und Attribut wiederfinden
	dbCursor<CDBObject> object (GetRelatedDatabase(GetUnknown()));
	CDBObject *pObject = object.at (dbReference<CDBObject>(oid_t(lObjCursor)));

		if (NULL == pObject || object.isEmpty())
			THROW_FAILED_HRESULT(FASTDB_E_OBJECT_BADREFERENCE);

	dbReference<CDBFeatureDesc> thisdesc = oid_t(lThisCursor);

		if (thisdesc == null)
			THROW_FAILED_HRESULT(FASTDB_E_FEATURE_BADREFERENCE);
			
	// Objekteigenschaft am Objekt wiederfinden
	LPCSTR pcName = OLE2A(bstrName);
	dbCursor<CDBFeature> feature (GetRelatedDatabase(GetUnknown()));
	int iFeatCnt = object -> features.length();
	bool fFound = false;
	
		for (int i = 0; i < iFeatCnt; i++) {
			feature.at (object -> features[i]);
			if (thisdesc == feature -> featuredesc) {
				bstrVal = feature -> m_pValue;
				fFound = true;
				break;
			}
		}
		if (!fFound)		// das Objekt besitzt diese Objekteigenschaft nicht
			return TRIASDB_E_NOSUCHFEATURE;

	CComVariant var (bstrVal);

		THROW_FAILED_HRESULT(var.Detach (pVal));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CFastdbFeature::EvalEx(ITRiASObject *pIObj, SAFEARRAY **ppConstraints, VARIANT *pVal)
{
	return Eval (pIObj, pVal);		// ignore constraints	
}

// Wert der Objekteigenschaft modifizieren
STDMETHODIMP CFastdbFeature::Update(ITRiASObject *pIObj, VARIANT Val)
{
	USES_CONVERSION;
	COM_TRY {
	WTRiASFeature BaseFeat;

		THROW_FAILED_HRESULT(m_BaseUnk -> QueryInterface (BaseFeat.ppi()));

	CComBSTR bstrVal;
	LONG lObjCursor = GetPropertyFrom (pIObj, g_cbObjectCursor, 0L);
	LONG lThisCursor = GetPropertyFrom (BaseFeat, g_cbFeatureCursor, 0L);

		_ASSERTE(0 != lObjCursor);
		_ASSERTE(0 != lThisCursor);

	// Objektdaten zuordnen und Attribut wiederfinden
	dbDatabase *pdb = GetRelatedDatabase(GetUnknown());
	dbCursor<CDBObject> object (pdb);
	CDBObject *pObject = object.at (dbReference<CDBObject>(oid_t(lObjCursor)));

		if (NULL == pObject || object.isEmpty())
			THROW_FAILED_HRESULT(FASTDB_E_OBJECT_BADREFERENCE);

	dbReference<CDBFeatureDesc> thisdesc = oid_t(lThisCursor);

		if (thisdesc == null)
			THROW_FAILED_HRESULT(FASTDB_E_FEATURE_BADREFERENCE);

	// Objekteigenschaft am Objekt wiederfinden
	CComVariant vVal;
	bool fUpdate = false;		// schreiben oder l�schen
	bool fFound = false;

		if (!V_ISNULL(&Val) && SUCCEEDED(vVal.ChangeType (VT_BSTR, &Val))) 
			fUpdate = true;

		{
		dbCursor<CDBFeature> feature (pdb, dbCursorForUpdate);
		int iFeatCnt = object -> features.length();
		
			for (int i = 0; i < iFeatCnt; i++) {
				feature.at (object -> features[i]);
				if (thisdesc == feature -> featuredesc) {
					if (fUpdate) {
						feature -> m_pValue = OLE2A(V_BSTR(&vVal));
						feature.update();		// modifizieren
					} else
						feature.remove();		// l�schen

					fFound = true;
					break;
				}
			}
		} // dbCursor goes out of scope

		if (!fFound) {	// das Objekt besitzt diese Objekteigenschaft nicht --> neu erzeugen
		CDBFeature Feat;

			Feat.m_pValue = OLE2A(V_BSTR(&vVal));
			Feat.object = object.currentId();
			Feat.featuredesc = thisdesc;
			pdb -> insert (Feat);
		}

	} COM_CATCH;
	return S_OK;
}

// Kopie der Objekteigenschaft erzeugen
STDMETHODIMP CFastdbFeature::Clone (ITRiASFeature **ppIFeat)
{
	return E_NOTIMPL;
}

// Objekt wird logisch freigegeben
STDMETHODIMP CFastdbFeature::OnFinalRelease()
{
	return S_OK;
}


