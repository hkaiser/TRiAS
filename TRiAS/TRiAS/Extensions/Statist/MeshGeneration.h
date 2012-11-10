// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 13.09.2000 15:48:18
//
// @doc
// @module MeshGeneration.h | Declaration of the <c CMeshGeneration> class

#if !defined(_MESHGENERATION_H__63E583DE_E478_4601_9F21_402BADD38967__INCLUDED_)
#define _MESHGENERATION_H__63E583DE_E478_4601_9F21_402BADD38967__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>

#include "MeshGenerationDlg.h"

/////////////////////////////////////////////////////////////////////////////
// Declaration diverser Klassen
#if !defined(_ENUM_LONG_ENUMERATOR_DEFINED)
#define _ENUM_LONG_ENUMERATOR_DEFINED

DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator2(LONG, __uuidof(IEnumLONG));		// definiert WEnumLONG (Wrapper für IEnum<LONG>)
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG 

#endif // _ENUM_LONG_ENUMERATOR_DEFINED

/////////////////////////////////////////////////////////////////////////////
// CMeshGeneration
class ATL_NO_VTABLE CMeshGeneration : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMeshGeneration, &CLSID_MeshGeneration>,
	public IObjectWithSiteImpl<CMeshGeneration>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_ACTION_MUSTREPAINT
	};

	CMeshGeneration() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_MESHGENERATION),
		m_rgOperation(CMeshGenerationDlg::MESH_CONVEXHULL)
	{
		m_pCfgDlg = NULL;
	}
	~CMeshGeneration()
	{
		DELETE_OBJ(m_pCfgDlg);
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MESHGENERATION)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CMeshGeneration)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

// IPropertyAction 
public:
	STDMETHOD(BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD(DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD(EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// Geokomponente hat eigenen Dialog
	STDMETHOD(PreConfigPages)(THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD(AddConfigPages)(THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);

// IPersist
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);

// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog);

// Operations
	HRESULT CalculateConvexHull(HPROJECT hPr, IEnum<LONG> *pEnumOut);
	HRESULT CalculateVoronoiDiagram(HPROJECT hPr, IEnum<LONG> *pEnumOut);
	HRESULT CalculateDelaunayTriangulation(HPROJECT hPr, IEnum<LONG> *pEnumOut);

private:
	typedef list<pair<SEnumLONG, os_string> > CListOfEnums;
	CListOfEnums m_listObjects;		// zu bearbeitende Objektmengen (ConvexHull)

	SEnumLONG m_Objects;			// Resultats-Objektmenge (ConvexHull) bzw. Eingabemenge (Voronoi, Delaunay)
	CMeshGenerationDlg *m_pCfgDlg;	// Konfigurationsdialog
	CMeshGenerationDlg::MESH_OPERATION m_rgOperation;
};

#endif // !defined(_MESHGENERATION_H__63E583DE_E478_4601_9F21_402BADD38967__INCLUDED_)
