// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 20.12.2002 11:31:12
//
// @doc    PropertyAction für topologische Relationen von GeoObjekten zu einem Bezugsobjekt
// @module TopoRelPropAct.h | Declaration of the <c CTopoRelPropAct> class

#if !defined(__TOPORELPROPACT_H_)
#define __TOPORELPROPACT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TopoRelR.h"       // Hauptsymbole (Ressourcen)

#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>

#include "TopoRelDlg.h"			// CTopoRelDlg
#include "TopoRelRefDlg.h"		// CTopoRelRefDlg
#include "TopoRelFunctions.h"	// TopoRelFunc



// {98B9B6D3-86F1-4D35-B613-D47267BD1EDC}
extern const __declspec(selectany) GUID CLSID_TopoRelPropAct = 
	{ 0x98b9b6d3, 0x86f1, 0x4d35, { 0xb6, 0x13, 0xd4, 0x72, 0x67, 0xbd, 0x1e, 0xdc } };



///////////////////////////////////////////////////////////////////////////////////////////////
// Deklaration diverser Klassen
#if !defined(_ENUM_LONG_ENUMERATOR_DEFINED)
#define _ENUM_LONG_ENUMERATOR_DEFINED

DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG 

#endif // _ENUM_LONG_ENUMERATOR_DEFINED



///////////////////////////////////////////////////////////////////////////////////////////////
// CTopoRelPropAct: Klasse für die Ermittlung topologischer Relationen
class ATL_NO_VTABLE CTopoRelPropAct : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTopoRelPropAct, &CLSID_TopoRelPropAct>,
	public IObjectWithSiteImpl<CTopoRelPropAct>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_NONE
	};

	// Konstruktor, Destruktor
		CTopoRelPropAct (void);
		~CTopoRelPropAct (void);

	void FinalRelease (void);

	DECLARE_REGISTRY_RESOURCEID(IDR_TOPORELPROPACT)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CTopoRelPropAct)
		COM_INTERFACE_ENTRY2 (IPropertyAction, IPropertyAction2)
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

// IPersistStreamInit
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL bClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);

// IPersistPropertyBag
	STDMETHOD(Load) (THIS_ IPropertyBag *pBag, IErrorLog *pLog);
	
public:
	CTopoRelDlg* GetRelationDlg (void) { return m_pRelationDlg; }
	CTopoRelRefDlg* GetMultiRefDlg (void) { return m_pMultiRefDlg; }

private:
	HDEX m_hDex;					// Handle der nachgeladenen Erweiterung TopoRel.ext
	SEnumLONG m_RefObjects;			// Bezugsobjekte
	SEnumLONG m_AnalyObjects;		// Objekte, für die die topologischen Relationen ermittelt werden sollen
	CTopoRelDlg* m_pRelationDlg;	// RelationenDialog für die topologischen Relationen
	TOPORELRESULT m_caRelationInfo;	// zuletzt weggeschriebene Relationen
	bool m_bIsDirtyRelation;		// Parameter des RelationenDialogs wurden verändert (true)
	bool m_bHasInitRelationData;	// Initialisierungsdaten für den RelationenDialog wurden von
									// Load() bereitgestellt, konnten aber noch nicht an diesen
									// weitergereicht werden (true)
	CTopoRelRefDlg* m_pMultiRefDlg;	// MultiRefDialog
	MULTIREFRESULT m_caMultiRefInfo;// zuletzt ausgewählte Daten bei mehreren Bezugsobjekten
	bool m_bIsDirtyMultiRef;		// Parameter des RelationenDialogs wurden verändert (true)
	bool m_bHasInitMultiRefData;	// Initialisierungsdaten für den MultiRefDialog wurden von
									// Load() bereitgestellt, konnten aber noch nicht an diesen
									// weitergereicht werden (true)
	TopoRelFunc* m_pTRF;			// Funktionen für die topologische Analyse
	bool m_bFirstEndAction;			// erster Aufruf von EndAction (true)
	long m_lPacket;					// Paketnummer
	CComBSTR m_bstrMessageNoObjects;// Mitteilung, wenn die Analyse für mindestens eine
									// ausgewählte Relation keine Ergebnisobjekte liefert
};

#endif // !defined(__TOPORELPROPACT_H_)
