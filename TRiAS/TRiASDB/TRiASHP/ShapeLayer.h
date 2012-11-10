// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.05.2000 17:01:52 
//
// @doc
// @module ShapeLayer.h | Declaration of the <c CShapeLayer> class

#if !defined(_SHAPELAYER_H__A79B630C_CDB6_4843_8552_D0A274F17D18__INCLUDED_)
#define _SHAPELAYER_H__A79B630C_CDB6_4843_8552_D0A274F17D18__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/stlex/pointainer.h>
#include <ShapeLib/Shapefil.h>

///////////////////////////////////////////////////////////////////////////////
// Ein Satz aus einer shp-Datei
class CShapeObject 
{
public:
	CShapeObject (SHPObject *pObj) : m_pObj(pObj) {}
	~CShapeObject () 
	{ 
		if (NULL != m_pObj) {
			SHPDestroyObject(m_pObj);
			m_pObj = NULL; 
		}
	}

	operator SHPObject * () { return m_pObj; }
	operator const SHPObject * () const { return m_pObj; }

	SHPObject * operator-> () { return m_pObj; }

	bool operator! () const { return (NULL == m_pObj) ? true : false; }
	bool IsValid() const { return !!(*this); }

private:
	SHPObject *m_pObj;
};

///////////////////////////////////////////////////////////////////////////////
// Ein Feld (Attribut) in einem Shape-Layer
class CShapeFieldBase
{
public:
	CShapeFieldBase()
	{
	}
	virtual ~CShapeFieldBase() 
	{
	}

// Properties eines Feldes
	virtual bool IsValid() = 0;
	virtual FEATURETYPE GetType() = 0;
	virtual long GetLen() = 0;
	virtual HRESULT GetName (BSTR *pbstrName) = 0;
	virtual HRESULT Eval (int iShape, BSTR *pbstrValue) = 0;
#if defined(_READWRITE)
	virtual HRESULT Update (int iShape, BSTR bstrValue) = 0;
#endif // defined(_READWRITE)
};

///////////////////////////////////////////////////////////////////////////////
// ein spezielles Attribut, welches die Satznummer liefert 
class CShapeFieldID :
	public CShapeFieldBase
{
public:
	CShapeFieldID()
	{
	}
	~CShapeFieldID()
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

	CComBSTR bstrName (g_cbShapeID);

		*pbstrName = bstrName.Detach();
		return S_OK;
	}

	HRESULT Eval (int iShape, BSTR *pbstrValue)
	{
		if (NULL == pbstrValue)
			return E_POINTER;

	wchar_t cbBuffer[64];
	CComBSTR bstrName (_ltow (iShape, cbBuffer, 10));	// der Wert ist der ObjektId selbst
		
		*pbstrValue = bstrName.Detach();
		return S_OK;
	}

#if defined(_READWRITE)
	HRESULT Update (int iShape, BSTR bstrValue)
	{
		return TRIASDB_E_FEATURENOTUPDATABLE;
	}
#endif // defined(_READWRITE)
};

///////////////////////////////////////////////////////////////////////////////
// ein 'reales' Attribut in einem Shape-Layer
class CShapeField :
	public CShapeFieldBase
{
public:
	CShapeField (DBFHandle hDBF, int iField, bool fUpdate) :
		m_hDBF(hDBF), m_iField(iField), m_fUpdate(fUpdate)
	{
	}
	~CShapeField () 
	{
	}

	bool IsValid() { return m_iField < DBFGetFieldCount(m_hDBF); }
	FEATURETYPE GetType()
	{
		return GetFeatureType (DBFGetFieldInfo (m_hDBF, m_iField, NULL, NULL, NULL));
	}
	long GetLen()
	{
	int iLen = 0;

		DBFGetFieldInfo(m_hDBF, m_iField, NULL, &iLen, NULL);
		return iLen;
	}
	HRESULT GetName (BSTR *pbstrName)
	{
		if (NULL == pbstrName)
			return E_POINTER;
		*pbstrName = NULL;

	char cbBuffer[32];

		if (FTInvalid != DBFGetFieldInfo (m_hDBF, m_iField, cbBuffer, NULL, NULL)) {
		CComBSTR bstrName (cbBuffer);

			*pbstrName = bstrName.Detach();
			return S_OK;
		}
		return E_UNEXPECTED;
	}

	HRESULT Eval (int iShape, BSTR *pbstrValue);
#if defined(_READWRITE)
	HRESULT Update (int iShape, BSTR bstrValue);
#endif // defined(_READWRITE)

protected:
	FEATURETYPE GetFeatureType (DBFFieldType rgShapeType);

private:
	DBFHandle m_hDBF;
	int m_iField;
	bool m_fUpdate;
};

///////////////////////////////////////////////////////////////////////////////
// Ein Shape-Layer (*.shp, *.dbf)
class CShapeLayer 
{
public:
	typedef pointainer<vector<CShapeFieldBase *> > CShapeFields;
	friend class CFieldIterator;

	CShapeLayer (const char *pszName, SHPHandle hSHP, DBFHandle hDBF, bool fUpdate) :
		m_strName(pszName), m_hSHP(hSHP), m_hDBF(hDBF), m_fUpdate(fUpdate), m_fHasFields(false)
	{
	}
	~CShapeLayer()
	{
		Close();
	}

	HRESULT Close()
	{
	// Dateien schließen
		if (NULL != m_hDBF) { 
			DBFClose(m_hDBF); 
			m_hDBF = NULL; 
		}
		if (NULL != m_hSHP) { 
			SHPClose(m_hSHP); 
			m_hSHP = NULL; 
		}
		return S_OK;
	}

	LPCSTR GetName() { return m_strName.c_str(); }

//	CGeometry *GetSpatialFilter() { return poFilterGeom; }
//	void SetSpatialFilter(CGeometry *);

//	void ResetReading();
//	CFeature *GetNextFeature();
//	CFeature *GetFeature(long nFeatureId);
//	CFeatureDefn *GetLayerDefn() { return poFeatureDefn; }
//
//	HRESULT SetFeature(CFeature *poFeature);
//	HRESULT CreateFeature(CFeature *poFeature);
//	int GetFeatureCount(int);
//
//	HRESULT CreateField (CFieldDefn *poField, int bApproxOK = TRUE);
	
	int TestCapability(const char *);

	OBJECTTYPE GetTypes();
	HRESULT GetBoundingRect (double *pdXMin, double *pdYMin, double *pdXmax, double *pdYMax);
	int GetObjectCount();

	bool GetUpdatable() { return m_fUpdate; }
	SHPHandle GetSHPHandle() { return m_hSHP; }
	DBFHandle GetDBFHandle() { return m_hDBF; }

protected:
	CShapeFields &GetFields() 
	{ 
		if (!m_fHasFields) {
			InitFields();
			m_fHasFields = true;
		}
		return m_Fields; 
	}
	HRESULT InitFields();

private:
//	CFeatureDefn *poFeatureDefn;
//	CGeometry *poFilterGeom;
//	int iNextShapeId;
//	int nTotalShapeCount;

	CShapeFields m_Fields;
	os_string m_strName;
	SHPHandle m_hSHP;
	DBFHandle m_hDBF;
	bool m_fUpdate;
	bool m_fHasFields;
};

///////////////////////////////////////////////////////////////////////////////
// Attribute eines Objektes
class CFieldIterator
{
public:
	CFieldIterator(CShapeLayer &rSL) : 
		m_rSL(rSL), m_it(rSL.GetFields().begin()) 
	{
	}
	~CFieldIterator() 
	{
	}

	CShapeFieldBase *GetFirstField() 
		{ m_it = m_rSL.GetFields().begin(); return (m_it != m_rSL.GetFields().end()) ? (*m_it) : NULL; }
	CShapeFieldBase *GetNextField() 
		{ ++m_it; return (m_it != m_rSL.GetFields().end()) ? (*m_it) : NULL; }

private:
	CShapeLayer &m_rSL;
	CShapeLayer::CShapeFields::iterator m_it;
};

#endif // !defined(_SHAPELAYER_H__A79B630C_CDB6_4843_8552_D0A274F17D18__INCLUDED_)
