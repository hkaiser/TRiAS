// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.07.2000 14:17:06 
//
// @doc
// @module ArcViewLayer.h | Declaration of the <c CArcViewLayer> class

#if !defined(_ARCVIEWLAYER_H__062BCA46_1E0D_4A64_A54B_EFCC75466CF1__INCLUDED_)
#define _ARCVIEWLAYER_H__062BCA46_1E0D_4A64_A54B_EFCC75466CF1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Shapelib/Shapefil.h>
#include "ArcViewAttribute.h"

///////////////////////////////////////////////////////////////////////////////
// Ein Satz aus einer shp-Datei
class CArcViewObject 
{
public:
	explicit CArcViewObject (SHPObject *pObj = NULL) : m_pObj(pObj) {}
	~CArcViewObject () 
	{ 
		Tidy();
	}

	operator SHPObject * () { return m_pObj; }
	operator const SHPObject * () const { return m_pObj; }

	SHPObject * operator-> () { return m_pObj; }
	const SHPObject * operator-> () const { return m_pObj; }

	CArcViewObject &operator= (SHPObject *pObj)
	{
		Tidy();
		m_pObj = pObj;
	}

	bool operator! () const { return (NULL == m_pObj) ? true : false; }
	bool IsValid() const { return !!(*this); }

protected:
	void Tidy()
	{
		if (NULL != m_pObj) {
			SHPDestroyObject(m_pObj);
			m_pObj = NULL; 
		}
	}

private:
	SHPObject *m_pObj;
};

///////////////////////////////////////////////////////////////////////////////
// ein zu exportierender Layer 
class CArcViewLayer
{
public:
	typedef map<os_string, os_string> CFieldNames;

	CArcViewLayer (const char *pszName, OBJECTTYPE rgType, os_string strRoot, SHPHandle hSHP, DBFHandle hDBF) :
		m_strName(pszName), m_rgType(rgType), m_strRoot(strRoot), m_fHasFields(false), 
		m_hSHP(hSHP), m_hDBF(hDBF), m_nShapeType(SHPT_NULL)
	{
		_ASSERTE(NULL != m_hSHP && NULL != m_hDBF);
		SHPGetInfo (m_hSHP, NULL, &m_nShapeType, NULL, NULL);
	}
	~CArcViewLayer()
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
	HRESULT CloseAndDeleteFiles();
	HRESULT ExportData (GSTRUCT *pGS, MFELD *pMF, LPCSTR pcUIdent, CArcViewLayerAttributes *pMap);
	
	LPCSTR GetName() { return m_strName.c_str(); }
	bool HasFields() { return m_fHasFields; }
	void SetHasFields (bool fHasFields = true) { m_fHasFields = fHasFields; }

	OBJECTTYPE GetType();

// Attributbehandlung
	HRESULT FieldExists (LPCSTR pcName, DBFFieldType rgType, int *piField);
	HRESULT AddField (LPCSTR pcName, DBFFieldType rgTyp, int iLen, int iDecimal, int *piField);

protected:
	os_string GetUniqueFieldName (LPCSTR pcName);
	bool IsUniqueName (os_string &rStr);

private:
	os_string m_strName;
	OBJECTTYPE m_rgType;
	os_string m_strRoot;
	bool m_fHasFields;

	SHPHandle m_hSHP;
	DBFHandle m_hDBF;
	int m_nShapeType;

	CFieldNames m_Names;		// KurzText -> Feldname
};

#endif // !defined(_ARCVIEWLAYER_H__062BCA46_1E0D_4A64_A54B_EFCC75466CF1__INCLUDED_)
