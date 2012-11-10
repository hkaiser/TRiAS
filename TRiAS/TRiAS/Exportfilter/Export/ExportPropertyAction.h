// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 23.08.2002 10:08:42 
//
// @doc
// @module ExportPropertyAction.h | Declaration of the <c CExportPropertyAction> class

#if !defined(_EXPORTPROPERTYACTION_H__1FAB4693_93CE_441E_A557_3CB15A87051D__INCLUDED_)
#define _EXPORTPROPERTYACTION_H__1FAB4693_93CE_441E_A557_3CB15A87051D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/list>
#include <ospace/std/map>

#pragma HDR_ON()

#include "ExportPropertyActionDlg.h"
#include "SelectObjPropsToExport.h"
#include "SelectCoordSysActionDlg.h"

///////// KK000305 ///////////////////////////////////////////////////
typedef list<long> CObjsFromProject;
typedef map<os_string, HFEATURE, less<os_string> > CFeatureCodes;

///////////////////////////////////////////////////////////
class CPrjMap :
	public map<HPROJECT, CObjsFromProject, less<HPROJECT> >
{
public:

	bool InsertObject (long lONr);
	void Clear() { erase(); }
	size_t Count() 
	{
	size_t lCnt = 0;

		for (iterator it = begin(); it != end(); ++it) 
			lCnt += (*it).second.size();
		return lCnt;
	}
};

// imput iterator für for_each
class CPrjMapInputIter : 
	public input_iterator<long, size_t>
{
public:
	typedef CPrjMapInputIter self;

protected:
	CPrjMap *m_pPrjMap;
	CPrjMap::iterator m_it;
	CObjsFromProject::iterator m_itl;

	long value;
	bool end_marker;

	void read (void) throw() 
		{
			if (m_it == m_pPrjMap -> end()) {
				end_marker = true;
				return;
			}
				
//			if (!end_marker && m_itl != (*m_it).second.end()) {
			if (m_itl != (*m_it).second.end()) {
				value = *m_itl;
				++m_itl;
 
				if (m_itl == (*m_it).second.end()) {
					++m_it;
					if (m_it != m_pPrjMap -> end())
						m_itl = (*m_it).second.begin();
				}

				end_marker = false; 

			} else
				end_marker = true ; 
		}

public:
	CPrjMapInputIter (void) throw() : m_pPrjMap(NULL), end_marker(true) {}
	CPrjMapInputIter (CPrjMap *pPrjMap) throw() : m_pPrjMap(pPrjMap), end_marker(false) 
	{ 
		m_it = m_pPrjMap -> begin(); 

		if (m_it != m_pPrjMap -> end()) {
			m_itl = (*m_it).second.begin();
			read(); 
		} else
			end_marker = true;
	}

	const long operator * (void) const throw() { return value; }

	self& operator++ (void)	throw() { read(); return *this; }
	self operator++ (int) throw() { self tmp = *this; read(); return tmp; }

	bool operator == (const self & x_) const throw() 
		{ 
			return (m_pPrjMap == x_.m_pPrjMap && end_marker == x_.end_marker) ||
				   (end_marker == true && x_.end_marker == true);
		}
	bool operator != (const self & x_) const throw() 
		{ return !(*this == x_); }
};

// output iterator (für copy)
class CPrjMapOutputIter : 
	public output_iterator
{
public:
	typedef CPrjMapOutputIter self;

protected:
	CPrjMap *m_pPrjMap;

public:
	CPrjMapOutputIter (void) throw() : m_pPrjMap(NULL) {}
	CPrjMapOutputIter (CPrjMap *pPrjMap) throw() : m_pPrjMap(pPrjMap) {}
	CPrjMapOutputIter (const self &iter) throw() : m_pPrjMap(iter.m_pPrjMap) {}

    self& operator = (const long lONr) throw() 
		{ m_pPrjMap -> InsertObject(lONr); return *this; }
	self& operator * (void) throw() { return *this; }
	self& operator++ (void)	throw() { return *this; }
	self operator++ (int) throw() { return *this; }
};

///////////////////////////////////////////////////////////////////////////////
// CExportPropertyAction

const long EXPORT_VERSION = 0x0100L;
const long LASTKNOWN_EXPORT_VERSION = EXPORT_VERSION;

class ATL_NO_VTABLE CExportPropertyAction
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CExportPropertyAction, &CLSID_ExportPropertyAction>
	, public CPropertyActionImpl
	, public CErrSupport<CExportPropertyAction, &IID_ITRiASExportAction>
	, public CPersistStreamInitImpl<CExportPropertyAction, &CLSID_ExportPropertyAction>
{
// persistente Eigenschaften, werden über CExportPropertyActionDlg eingestellt
	HRESULT	LoadEngines();
	vector<WTRiASExtDataEngine>		m_vecOfEngines;
	map<CLSID, WTRiASExtDataEngine, less<CLSID> >	m_mapOfRegisteredEngines;
	WTRiASExtDataEngine		m_pTRiASExtDataEngine;		// zuletzt benutzte Engine; wenn NULL, dann unbekannt
//	int			m_nSelectedEngine;	// zuletzt gewählte Engine (entspr. m_strExportEngine)

// Statusanzeige
	long					m_nMaxObjects;	// Gesamtzahl zu exportierender Objekte

// KK991111 - Pfade merken
	CComBSTR	m_strWunschDir;
	CComBSTR	m_strZielDir;
	CComBSTR	m_strWunschFile;
	long		m_lScreenContObj;

public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_NONE
	};

	CExportPropertyAction()
		: CPropertyActionImpl (PA_TYPEFLAGS, IDS_LONGCLASSNAME)
	{
		m_pCfgDlg = NULL;
		m_pObjPropDlg = NULL;
		m_pSelCsDlg = NULL;
		m_fCreated2ndPage = false;
		m_fCreated3rdPage = false;
	}
	~CExportPropertyAction()
	{
		DELETE_OBJ(m_pCfgDlg);
		DELETE_OBJ(m_pObjPropDlg);
		DELETE_OBJ(m_pSelCsDlg);
	}

	HRESULT	FinalConstruct();
	HRESULT	FinalRelease();

	DECLARE_REGISTRY_RESOURCEID(IDR_EXPORTPROPERTYACTION)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CExportPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY_CHAIN(CErrSupport_t)
		COM_INTERFACE_ENTRY_CHAIN(CPersistStreamInitImpl_t)
	END_COM_MAP()

	HRESULT	UpdateStatus( long nObjects );

// KK000128
	HRESULT ObjectDataExport(CTRiASXMLDocument&	m_xmd, long nCounter, ENDMODE rgMode = ENDMODE_DoNotBother);
	void SetScreenContObj( long lONr ) { m_lScreenContObj = lONr ; }
	void ScreenContObj_Erase(void);		// Objekt löschen

// IPropertyAction 
public:
	STDMETHOD(BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD(DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD(EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// Geokomponente hat eigenen Dialog
	STDMETHOD(PreConfigPages)(THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD(AddConfigPages)(THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);

// CPersistStreamInitImpl
	STDMETHOD(GetClassID) (THIS_ CLSID *pClassID) 
	{
		return CPersistStreamInitImpl_t::GetClassID(pClassID);
	}
	HRESULT	OnInitNew();
	HRESULT LoadData(LPSTREAM pStm, DWORD dwVersion);
	HRESULT SaveData(LPSTREAM pStm, BOOL bClearDirty);
	LONGLONG GetDataSize();
	static DWORD GetSignature() { char *s = "EXPT"; return *((DWORD*)s); }
	static DWORD GetVersion() { return LASTKNOWN_EXPORT_VERSION; }
	bool IsInitialized() 
	{ 
		return CPropertyActionImpl::IsInitialized() && CPersistStreamInitImpl_t::IsInitialized(); 
	}
	void SetInitialized (bool fIsInitialized = true) 
	{ 
		CPropertyActionImpl::SetInitialized(fIsInitialized);
		CPersistStreamInitImpl_t::SetInitialized(fIsInitialized);
	}

// KK991115
	HRESULT CopyExportFilesEx (void);
	bool CopyExportFiles ( char * strQuelle, char * strZiel);

// KK000228
	bool ExportMerkmal (BOOL fExportObjProps = TRUE);
	bool ExportIdentifikator (void);

private:
// KK000305
	CPrjMap m_Objects;		
	CExportPropertyActionDlg *m_pCfgDlg;	// Konfigurationsdialog
	CSelectObjPropsToExport *m_pObjPropDlg;	// Objekteigenschaften auwählen
	CSelectCoordSysActionDlg *m_pSelCsDlg;	// Koordinatensystem auswählen
	bool m_fCreated2ndPage;
	bool m_fCreated3rdPage;

	CFeatureCodes m_mapCodes;

public:
// KK000823
	BOOL m_bSeparate;
	BOOL m_bSelect;
	long m_lCounter;
	list<os_string> m_lstSelObjProps;

	void AddCounter (void) { m_lCounter++; }
	void SetCounter (void) { m_lCounter = 0; }

	CFeatureCodes &GetCodes() { return m_mapCodes; }
	BOOL MustExportFeature(LPCSTR pcName);
};

#pragma HDR_OFF()

#endif // !defined(_EXPORTPROPERTYACTION_H__1FAB4693_93CE_441E_A557_3CB15A87051D__INCLUDED_)
