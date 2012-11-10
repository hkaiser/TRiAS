///////////////////////////////////////////////////////////////////////////
// @doc 
// @module RecordsetSource.h | Declaration of the <c CRecordsetSource>
// class

#if !defined(_RECORDSETSOURCE_H__7417A5E8_AED0_11D1_859A_00600875138A__INCLUDED_)
#define _RECORDSETSOURCE_H__7417A5E8_AED0_11D1_859A_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASGMR.H"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(GDatabase, IID_GDatabase);
DefineSmartInterface2(GRecordset, IID_GRecordset);

/////////////////////////////////////////////////////////////////////////////
// CRecordsetSource
class ATL_NO_VTABLE CRecordsetSource : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CRecordsetSource, &CLSID_RecordsetSource>,
	public IRecordsetSource
{
public:
	CRecordsetSource()
	{
		m_pIDB = NULL;
		m_hPr = NULL;
		m_fIsReadOnly = true;
		m_fIsTemporary = false;
	}

	DECLARE_NOT_AGGREGATABLE(CRecordsetSource)
	DECLARE_REGISTRY_RESOURCEID(IDR_RECORDSETSOURCE)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	static HRESULT WINAPI _RetrievePtr(void* pv, REFIID iid, void** ppvObject, DWORD dw);
	BEGIN_COM_MAP(CRecordsetSource)
		COM_INTERFACE_ENTRY(IRecordsetSource)
		COM_INTERFACE_ENTRY_FUNC(IID_GDatabase, 0, _RetrievePtr)
	END_COM_MAP()

	HRESULT FinalConstruct();
	void FinalRelease()
	{
		Close();
		m_Alias.Assign(NULL);
		m_CoordSys.Assign(NULL);
	}

// IRecordsetSource
public:
// This method is called when OpenDatabase is called on the GDO Framework GDatabase object
	STDMETHOD(OpenSource)(THIS_ BSTR pName,		// (in) Source Name
						  VARIANT pExclusive,	// (in) VT_BOOL. Exclusive? 
						  VARIANT pReadonly,	// (in) VT_BOOL. Read only? 
						  VARIANT pModTrack,	// (in) VT_BOOL. Turn tracking on? 
						  VARIANT pSource);		// (in) Additionnal source info 

// This method is called when the GDO Framework needs to build a list of GTableDef objects 
	STDMETHOD (GetTableNames)(THIS_ SAFEARRAY**  pTableNames); // (out) VT_ARRAY | VT_BSTR. Array of table names 
  
// This method is called when the GDO Framework needs to create a Framework 
// GRecordset for the client and it doesn't have the source GRecordset for a 
// certain feature.
	STDMETHOD(GetGRecordset)(THIS_ BSTR TableName,				// (in)  Table name 
							 GRecordset** pSourceGRecordset);	// (out) Returned Source GRecordset

// This method is called when the GDO Framework needs to collect information about this server. 
// e.g. CaseSensitive? ReadOnly? DataUpdatable? Server Version? CollatingOrder? The GDO Framework
// assumes the defaults whenever the returned VARIANT value is VT_EMPTY.
	STDMETHOD(GetProperty)(THIS_ BSTR pPropName,		// (in)  Property name 
						   VARIANT *pPropValue);		// (out) Property value 

// This method is called whenever the OpenRecordset method is called on the GDatabase object
// of the GDO Framework. It's meant to be as a hook for the Recordset Source in case it needs
// to build the GRecordset itself. If the Recordset source doesn't want to implement the 
// OpenRecordset, it can simply return E_NOTIMPL which is the indication for the GDO 
// Framework to proceed and create a Framework GRecordset for the query.
	STDMETHOD(OpenRecordset)(THIS_ BSTR pName,				// (in)  SQL statement 
							 VARIANT pType,					// (in)  Recordset type 
							 VARIANT pOptions,				// (in)  Read Only? 
							 VARIANT pSpatialOp,			// (in)  Spatial operation 
							 VARIANT pSpatialGeometryFilter,// (in)  Spatial filter 
							 VARIANT pGeometryFieldName,	// (in)  Geometry field name to use for filter 
							 GRecordset **ppGRecordset);	// (out) Returned GRecordset 

protected:
// Datenbank öffnen/schließen
	HPROJECT Open (LPCTSTR pcName, bool &rfReadOnly) throw (_com_error &);
	HPROJECT OpenStoragePbd (IStorage *pIStg, bool &rfReadOnly) throw (_com_error &);

	HRESULT OpenMetaDatabase (void);
	HRESULT Close(void);
	HRESULT get_TemporaryName(BSTR *pVal);

	HRESULT GetProjectStorage (IStorage **ppIStg)
		{ ASSERT(NULL != m_hPr); return ::GetProjectStorage(m_hPr, ppIStg); }
	HRESULT GetMetaStorage (IStorage **ppIStg)
		{ ASSERT(NULL != m_hPrPbd); return ::GetProjectStorage(m_hPrPbd, ppIStg); }

// Zugriffsfunktionen auf DBHandles
	HPROJECT GetHandle() { return m_hPr; }
	HPROJECT GetPbdHandle() { return m_hPrPbd; }

// spezielle Recordsets erzeugen
	HRESULT GetAliasTableRecordset (GRecordset **pSourceGRecordset);
	HRESULT GetCSTableRecordset (GRecordset **pSourceGRecordset);
	HRESULT GetMetaTableRecordSet (GRecordset **pSourceGRecordset);
	HRESULT GetViewRecordset (BSTR TableName, BSTR bstrViewName, GRecordset **pSourceGRecordset);
	HRESULT GetOKSRecordset (BSTR TableName, GRecordset **pSourceGRecordset);
	HRESULT GetFeatureTableRecordset (GRecordset **pSourceGRecordset);

	HRESULT GenerateOKSSourceInfo (BSTR bstrName, ITRiASSourceInfo **ppISrcInfo);
	HRESULT GenerateViewSourceInfo (BSTR bstrName, ITRiASSourceInfo **ppISrcInfo);

// Enumeration aller Identifikatoren der gesamten Datenbank
	class CTableEntry
	{
	private:
		long m_lIdent;
		DWORD m_dwTypes;
		os_string m_strKText;
		os_string m_strLText;

	public:
		CTableEntry(long lIdent, DWORD dwTypes, LPCSTR pcKText, LPCSTR pcLText)
			: m_lIdent(lIdent), m_dwTypes(dwTypes), 
			  m_strKText(pcKText), m_strLText(pcLText)
		{
		}
		CTableEntry (const CTableEntry& rhs)
			: m_lIdent(rhs.GetIdent()), 
			  m_dwTypes(rhs.GetTypes()), 
			  m_strKText(rhs.GetName()),
			  m_strLText(rhs.GetDescription())
		{
		}
		CTableEntry &operator= (const CTableEntry & rhs)
		{
			if (this != &rhs) {
				m_lIdent = rhs.GetIdent(); 
				m_dwTypes = rhs.GetTypes(); 
				m_strKText = rhs.GetName();
				m_strLText = rhs.GetDescription();
			}
			return *this;
		}
		long GetIdent() const { return m_lIdent; }
		DWORD GetTypes() const { return m_dwTypes; } 
		LPCSTR GetName() const { return m_strKText.c_str(); }
		LPCSTR GetDescription() const { return m_strLText.c_str(); }
	};
	typedef map<os_string, CTableEntry, less<os_string> > CTables;
	struct CEnumIdentEntryCallback
	{
		CRecordsetSource *m_pRSS;
		CTables *m_pNames;
	};
	static HRESULT CALLBACK EnumIdentCallBack (LONG lIdent, DWORD dwTypes, DWORD dwData);

// Ansichten enumerieren
	typedef map<os_string, os_string, less<os_string> > CViews;
	struct CEnumViewEntryCallback
	{
		CRecordsetSource *m_pRSS;
		CViews *m_pViews;
	};
	static HRESULT CALLBACK EnumViewCallBack (LPCSTR pcView, DWORD dwData);

// Generieren der CSS-Parameter aus den Headereinträgen
	CSBaseStorageConstants RetrieveBaseStorageType();

private:
	GDatabase *m_pIDB;

	HPROJECT m_hPr;				// geöffnete TRiAS-Datenbank
	HPROJECT m_hPrPbd;			// zugehörige Pbd
	CComBSTR m_bstrSource;		// übergebenes SourceString
	CComBSTR m_bstrName;		// Dateiname
	CComVariant m_CsGuid;		// CLSID des CKoordinatensystems

	bool m_fIsReadOnly;			// RO geöffnet
	bool m_fIsTemporary;		// ist temporär angelegt

	CTables m_Names;			// Objektklassen dieser GeoDB
	CViews m_Views;				// Ansichten dieser GeoDB

	WGRecordset m_Alias;		// spezielle Recordsets
	WGRecordset m_CoordSys;
	WGRecordset m_OKS;
	WGRecordset m_Features;
};

#endif // !defined(_RECORDSETSOURCE_H__7417A5E8_AED0_11D1_859A_00600875138A__INCLUDED_)
