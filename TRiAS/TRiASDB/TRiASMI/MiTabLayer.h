// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.01.2001 20:32:24 
//
// @doc
// @module MiTabLayer.h | Declaration of the <c CMiTabLayer> class

#if !defined(_MITABLAYER_H__251E2EF4_8DDD_4C43_AC22_E789824B3976__INCLUDED_)
#define _MITABLAYER_H__251E2EF4_8DDD_4C43_AC22_E789824B3976__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/CieThis.h>
#include <ospace/std/algorithm>
#include <ospace/stlex/pointainer.h>
#include <mitab/mitab.h>

///////////////////////////////////////////////////////////////////////////////
// Ein Satz aus einer MIF-Datei
class CMiTabObject 
{
public:
	CMiTabObject (mitab_feature rObj) : m_rObj(rObj) {}
	~CMiTabObject () 
	{ 
		if (NULL != m_rObj) {
			mitab_c_destroy_feature(m_rObj);
			m_rObj = NULL; 
		}
	}

	operator mitab_feature () { return m_rObj; }
	operator const mitab_feature () const { return m_rObj; }

	bool operator! () const { return (NULL == m_rObj) ? true : false; }
	bool IsValid() const { return !!(*this); }

	OBJECTTYPE GetObjectType();
	
private:
	mitab_feature m_rObj;
};

class CMiTabObjectMBR :
	public CMiTabObject
{
public:
	CMiTabObjectMBR(mitab_feature rObj) :
		CMiTabObject(rObj), m_dXMin(0.0), m_dYMin(0.0), m_dXMax(0.0), m_dYMax(0.0),
		m_fHasMBR(false)
	{
	}
	~CMiTabObjectMBR()
	{
	}

	bool GetMBR (double &rdXMin, double &rdYMin, double &rdXMax, double &rdYMax)
	{
		if (!m_fHasMBR) {
			if (!mitab_c_get_mbr(*this, m_dXMin, m_dYMin, m_dXMax, m_dYMax))
				return false;
			m_fHasMBR = true;
		}
		rdXMin = m_dXMin;
		rdYMin = m_dYMin;
		rdXMax = m_dXMax;
		rdYMax = m_dYMax;
		return true;
	}

private:
	double m_dXMin;
	double m_dYMin;
	double m_dXMax;
	double m_dYMax;
	bool m_fHasMBR;
};

///////////////////////////////////////////////////////////////////////////////
// Ein Feld (Attribut) in einem MapInfo-Layer
class CMiTabFieldBase
{
public:
	CMiTabFieldBase()
	{
	}
	virtual ~CMiTabFieldBase() 
	{
	}

// Properties eines Feldes
	virtual bool IsValid() = 0;
	virtual FEATURETYPE GetType() = 0;
	virtual long GetLen() = 0;
	virtual HRESULT GetName (BSTR *pbstrName) = 0;
	virtual HRESULT Eval (int iFeatureId, BSTR *pbstrValue) = 0;
#if defined(_READWRITE)
	virtual HRESULT Update (int iFeatureId, BSTR bstrValue) = 0;
#endif // defined(_READWRITE)
};

///////////////////////////////////////////////////////////////////////////////
// ein spezielles Attribut, welches die Satznummer liefert 
class CMiTabFieldID :
	public CMiTabFieldBase
{
public:
	CMiTabFieldID()
	{
	}
	~CMiTabFieldID()
	{
	}

// Feldlängen
	enum FEATURELEN {
		FEATURELEN_DEFAULT_INTEGERLEN = 10,
	};

// Properties
	bool IsValid() { return true; }		// immer gültig

	FEATURETYPE GetType() 
	{ 
		return FEATURETYPE(FEATURETYPE_IsPrimaryFeature|FEATURETYPE_Object|FEATURETYPE_ReadOnly|FEATURETYPE_System|DATATYPE_FROM_VT(VT_I4)); 
	}
	long GetLen() { return FEATURELEN_DEFAULT_INTEGERLEN; }

	HRESULT GetName(BSTR *pbstrName) 
	{
		if (NULL == pbstrName)
			return E_POINTER;

	CComBSTR bstrName (g_cbMapInfoId);

		*pbstrName = bstrName.Detach();
		return S_OK;
	}

	HRESULT Eval (int iFeatureId, BSTR *pbstrValue)
	{
		if (NULL == pbstrValue)
			return E_POINTER;

	wchar_t cbBuffer[64];
	CComBSTR bstrName (_ltow (iFeatureId, cbBuffer, 10));	// der Wert ist der ObjektId selbst
		
		*pbstrValue = bstrName.Detach();
		return S_OK;
	}

#if defined(_READWRITE)
	HRESULT Update (int iFeatureId, BSTR bstrValue)
	{
		return TRIASDB_E_FEATURENOTUPDATABLE;
	}
#endif // defined(_READWRITE)
};

///////////////////////////////////////////////////////////////////////////////
// ein 'reales' Attribut in einem Shape-Layer
class CMiTabField :
	public CMiTabFieldBase
{
public:
	CMiTabField (mitab_handle hMIF, int iField, bool fUpdate) :
		m_hMIF(hMIF), m_iField(iField), m_fUpdate(fUpdate)
	{
	}
	~CMiTabField () 
	{
	}

	bool IsValid() { return m_iField < mitab_c_get_field_count(m_hMIF); }
	FEATURETYPE GetType()
	{
		return GetFeatureType (mitab_c_get_field_type(m_hMIF, m_iField));
	}
	long GetLen() { return mitab_c_get_field_width(m_hMIF, m_iField); }
	HRESULT GetName (BSTR *pbstrName)
	{
		if (NULL == pbstrName)
			return E_POINTER;
		*pbstrName = NULL;

	LPCSTR pcName = mitab_c_get_field_name(m_hMIF, m_iField);

		if (NULL != pcName) {
		CComBSTR bstrName (pcName);

			*pbstrName = bstrName.Detach();
			return S_OK;
		}
		return E_UNEXPECTED;
	}

	HRESULT Eval (int iFeatureId, BSTR *pbstrValue);
#if defined(_READWRITE)
	HRESULT Update (int iFeatureId, BSTR bstrValue);
#endif // defined(_READWRITE)

protected:
	FEATURETYPE GetFeatureType (int rgFieldType);

private:
	mitab_handle m_hMIF;
	int m_iField;
	bool m_fUpdate;
};

///////////////////////////////////////////////////////////////////////////////
// Ein MapInfo-Layer (*.mif oder *.tab, nebst zugehörigen Dateien)
class CTRiASMIObjects;

class CMiTabLayer 
{
public:
	typedef pointainer<vector<CMiTabFieldBase *> > CMiTabFields;
	friend class CFieldIterator;

	CMiTabLayer (const char *pszName, mitab_handle hMIF, bool fUpdate) :
		m_pObjs(NULL), m_strName(pszName), m_hMIF(hMIF), 
		m_fUpdate(fUpdate), m_fHasFields(false)
	{
		if (m_strName.size() > 0) {
			transform(m_strName.begin(), m_strName.end(), m_strName.begin(), tolower);
			m_strName[0] = toupper(m_strName[0]);
		}
	}
	~CMiTabLayer()
	{
		Close();
	}

	HRESULT Close()
	{
	// Dateien schließen
		if (NULL != m_hMIF) { 
			mitab_c_close(m_hMIF); 
			m_hMIF = NULL; 
		}
		return S_OK;
	}

// required initialization
	HRESULT EnsureInitialized(ITRiASObjects *pIObjs);
	bool IsInitialized() { return (NULL != m_pObjs) ? true : false; }
	CTRiASMIObjects *GetObjsObject() { return m_pObjs; }

// inline properties
	LPCSTR GetName() { return m_strName.c_str(); }
	long GetObjectCount() { return long(((IMapInfoFile *)m_hMIF) -> GetFeatureCount(TRUE)); }
	bool GetUpdatable() { return m_fUpdate; }
	mitab_handle GetMiTabHandle() { return m_hMIF; }
	OGRSpatialReference *GetSpatialRef() { return ((IMapInfoFile *)m_hMIF) -> GetSpatialRef(); }

// liefert zugehöriges Datenbank-Objekt
	IDispatch *GetDatabase();
	HRESULT GetCSSGuid(CSID &rGuid);
	OBJECTTYPE GetTypes();
	HRESULT GetBoundingRect (double *pdXMin, double *pdYMin, double *pdXMax, double *pdYMax, bool fTransform = true);

protected:
	CMiTabFields &GetFields() 
	{ 
		if (!m_fHasFields) {
			InitFields();
			m_fHasFields = true;
		}
		return m_Fields; 
	}
	HRESULT InitFields();

private:
	CMiTabFields m_Fields;
	CTRiASMIObjects *m_pObjs;
	os_string m_strName;
	mitab_handle m_hMIF;
	bool m_fUpdate;
	bool m_fHasFields;
};

///////////////////////////////////////////////////////////////////////////////
// Attribute eines Objektes
class CFieldIterator
{
public:
	CFieldIterator(CMiTabLayer &rSL) : 
		m_rSL(rSL), m_it(rSL.GetFields().begin()) 
	{
	}
	~CFieldIterator() 
	{
	}

	CMiTabFieldBase *GetFirstField() 
		{ m_it = m_rSL.GetFields().begin(); return (m_it != m_rSL.GetFields().end()) ? (*m_it) : NULL; }
	CMiTabFieldBase *GetNextField() 
		{ ++m_it; return (m_it != m_rSL.GetFields().end()) ? (*m_it) : NULL; }

private:
	CMiTabLayer &m_rSL;
	CMiTabLayer::CMiTabFields::iterator m_it;
};

#endif // !defined(_MITABLAYER_H__251E2EF4_8DDD_4C43_AC22_E789824B3976__INCLUDED_)
