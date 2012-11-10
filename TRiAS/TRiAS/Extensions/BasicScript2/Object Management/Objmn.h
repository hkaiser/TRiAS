///////////////////////////////////////////////////////////////////////////
// @doc 
// @module Objmn.h | Declaration of the CObjMan class

#if !defined(_OBJMN_H__3DB1F093_E1AB_11D1_860B_00600875138A__INCLUDED_)
#define _OBJMN_H__3DB1F093_E1AB_11D1_860B_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "macrguid.h"

/////////////////////////////////////////////////////////////////////////////
// ObjMan
//REVIEW -- using pointers to ID's is necessary because some compilers don't like
//references as template arguments.

DefineEnumerator2(os_wstring, IID_IEnumos_wstring);

class EnumEx : public NEnumos_wstring
{
public:
	void ClearItem (item_t str) { 
		iterator it = m_data.begin();
		while (it != m_data.end() && *it != str) it++;
		if (it != m_data.end()) 
			m_data.erase (it); 
	}
};

class CObjectHolder : public IObjectHolder
{
public:
// Konstruktor
	CObjectHolder();
	~CObjectHolder();

private:
	ULONG		m_cRef;

// notwendige Member, die Objekt beschreiben
	LPSTREAM	m_lpStream;
	LPUNKNOWN	m_lpObject;
	CString		m_strName;
	LPMONIKER	m_lpMoniker;
	bool		m_fCreateTemp;
	bool		m_fInitNew;
	bool		m_fDelayedDel;

public:
// Properties
/* IObjectHolder */
	STDMETHOD(GetStream)	(LPSTREAM*	lplpStream);
	STDMETHOD(SetStream)	(LPSTREAM	lpStream);
	STDMETHOD(GetMoniker)	(LPMONIKER*	lplpMon);
	STDMETHOD(SetMoniker)	(LPMONIKER	lpMon);
	STDMETHOD(GetName)		(BSTR *pbstrName);
	STDMETHOD(SetName)		(BSTR bstrName);
	STDMETHOD(GetObject)	(LPUNKNOWN*	lplpUnk);
	STDMETHOD(SetObject)	(LPUNKNOWN	lpUnk);
	STDMETHOD(ReleaseObject)(VARIANT_BOOL fFullRelease);
	STDMETHOD(GetTemporaer)	(bool & fTemp);
	STDMETHOD(SetTemporaer)	(bool fTemp);
	STDMETHOD(SetNew)		(bool fNew);
	STDMETHOD(GetNew)		(bool *pfNew);
	STDMETHOD(Rename)		(BSTR);
	STDMETHOD(GetDelayedDel)(bool & fDelayedDel);
	STDMETHOD(SetDelayedDel)(void);

/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
	STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void);
};

class CHideTimerDialog;

class CObjectManagement : 
	public CComDualImpl<IObjectManagement, &IID_IObjectManagement, &LIBID_OBJMANLib>, 
	public ISupportErrorInfo,
	public IPersistStorage,
	public IPersistStream,
	public IOleItemContainer,
	public CComObjectRoot,
	public CComCoClass<CObjectManagement,&CLSID_CObjectManagement>
{
private:
	int		m_iState;
	bool	m_fIsDirty;
	DWORD	m_dwVersion;
	
	LPSTORAGE m_lpIStorage;
	LPSTREAM  m_lpIStreamStorageContents;
//	CHideTimerDialog *m_pHideTimerDlg;		// jedes Objektmanagement hat seinen eigenen "TimerDialog"
	
	CEnumObjects *m_pEnumObjects;
	HRESULT CreateEnum(bool fForceRelease = true);

	// CObjectHolder PropertiesHelper
	HRESULT GetDelayedDel		(BSTR bstr, bool & fDelayedDel);
	HRESULT SetDelayedDel		(BSTR bstr);
	HRESULT SetLoad				(BSTR bstr);
	HRESULT GetLoad				(BSTR bstrName);
	HRESULT GetTemporaer		(BSTR bstr, bool & fTemp);
	HRESULT SetTemporaer		(BSTR bstr, bool fTemp);
	HRESULT GetStream			(BSTR bstr, LPSTREAM*	lplpStream);
	HRESULT SetStream			(BSTR bstr, LPSTREAM	lpStream);
	HRESULT GetMoniker			(BSTR bstr, LPMONIKER*	lplpMon);
	HRESULT SetMoniker			(BSTR bstr, LPMONIKER	lpMon);
	HRESULT GetUnknownObject	(BSTR bstr, LPUNKNOWN*	lplpUnk);
	HRESULT SetUnknownObject	(BSTR bstr, LPUNKNOWN	lpUnk);
	HRESULT Rename				(BSTR bstr, BSTR bstrNew);
	HRESULT GetObjectHolder		(BSTR bstrName, IObjectHolder **pp);
	HRESULT SetNew				(BSTR bstrName, bool fNew);
	HRESULT GetNew				(BSTR bstrName, bool *pfNew);

// *** Hilfsfunktionen ***

	HRESULT LoadFile			(LPUNKNOWN lpUnk, BSTR bstrName, DWORD dwMode);
	HRESULT LoadStream			(LPUNKNOWN lpUnk, BSTR bstrName, IStorage *pIStg = NULL, BOOL fInitNew = TRUE);
	HRESULT LoadFileOrStream	(LPUNKNOWN lpUnk, BSTR bstrName, DWORD dwMode, IStorage *pIStg = NULL, BOOL fInitNew = TRUE);
	HRESULT SaveToFileOrStorage	(BSTR bstrName);
	HRESULT SetUnknownToStream	(LPUNKNOWN pUnk,	LPSTREAM pIStream);
	HRESULT GetUnknownFromStream(LPSTREAM pIStream, REFIID riid, LPVOID *ppUnk);
	HRESULT	CreateMoniker		(LPUNKNOWN, BSTR);
	HRESULT CreateStream		(UINT uiResID, LPSTORAGE, LPSTREAM *lplpStream);
	HRESULT CreateStream		(BSTR bstrName, LPSTORAGE, LPSTREAM *lplpStream);
	HRESULT CreateStreamName	(BSTR bstrName, BSTR bstrCorrName, LPSTORAGE pIStg, LPSTREAM *lplpStream);
	HRESULT OpenStream			(UINT uiResID, LPSTORAGE, LPSTREAM *lplpStream);
	HRESULT OpenStream			(BSTR bstrName, LPSTORAGE, LPSTREAM *lplpStream);
	HRESULT OpenStreamName		(BSTR bstrName, BSTR bstrCorrName, LPSTORAGE pIStg, LPSTREAM *lplpStream);
	HRESULT EnumElements		(LPSTORAGE pIStorage);
//	HRESULT	CreateTimer			(void);

// EnumHelper
	UINT	ObjectCount			(void);
	HRESULT	ObjectCountToWrite	(ULONG *pul);
	HRESULT Find				(BSTR bstr, LPUNKNOWN *ppUnk);
	HRESULT DeleteFromEnum		(BSTR bstr);

	void	Reset (bool fFullRelease = true);
	HRESULT ReLoad (IStorage *pIStg, IStream *pIStrm);

	HRESULT DestroyNewContentStream(void); 
	
	HRESULT IsValidName(BSTR bstrName);

	HRESULT OpenObject (BSTR bstrName, LPUNKNOWN *ppUnk); 
	HRESULT MakeObject (REFCLSID riid, BSTR bstrName, DWORD dwMode, LPUNKNOWN *ppUnk, bool fCreateTemp) ;
	HRESULT InsertObject (LPUNKNOWN pUnk, BSTR bstrName, DWORD dwMode, BOOL fCreateTemp); 

	HRESULT GetObjectMoniker	(BSTR bstrName, IMoniker **ppMon);
	HRESULT GetTRiASMoniker		(IMoniker **ppMon);
	HRESULT GetManagementMoniker(IMoniker **ppMon);
	HRESULT GetMoniker			(BSTR bstrName, IMoniker **ppIRunningMon, IMoniker **ppIBindingMon);
	HRESULT RenameMoniker		(BSTR bstrName, BSTR bstrNewName);
	HRESULT RenameStream		(BSTR bstrName, BSTR bstrNewName);

	HRESULT RegisterAsRunning(DWORD grfFlags, IUnknown *pIUnk, IMoniker *pIMk, DWORD *pdwRegROT);
	HRESULT RevokeAsRunning	(DWORD *pdwRegROT);

	HRESULT SaveDirtyObjects(void);
	
// Namen korrigieren (Stream-like und evtl. längenbegrenzt)
	HRESULT CorrectName (LPOLESTR poleName, BSTR *pbstrNewName);

public:
	CObjectManagement();
	~CObjectManagement();
	
	BEGIN_COM_MAP(CObjectManagement)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IObjectManagement)
		COM_INTERFACE_ENTRY(IPersistStorage)
		COM_INTERFACE_ENTRY(IPersistStream)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IOleItemContainer)
	END_COM_MAP()

	HRESULT DelayedDelete(void);

// Use DECLARE_NOT_AGGREGATABLE(CObjectManagement) if you don't want your object
// to support aggregation
	DECLARE_AGGREGATABLE(CObjectManagement)
	DECLARE_REGISTRY_RESOURCEID(IDR_OBJMAN_REG)

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IObjectManagement
	STDMETHOD(GetObject)	(BSTR bstrName, LPUNKNOWN *ppUnk);
	STDMETHOD(SaveObject)	(BSTR bstrName);
	STDMETHOD(RenameObject)	(BSTR bstrName, BSTR bstrNew);
	STDMETHOD(ReleaseObject)(BSTR bstrName);
	STDMETHOD(DelObject)	(BSTR bstrName);
	STDMETHOD(CreateObject)	(REFGUID rClsID, BSTR bstrName, DWORD dwMode, IUnknown **ppUnk, VARIANT_BOOL fCreateTemporaer = false);
//	STDMETHOD(EnumObjects)(DWORD, LPENUMUNKNOWN*);
    STDMETHOD(EnumStrings)	(LPUNKNOWN *ppUnk);
	STDMETHOD(SetObject)	(IUnknown *pUnk, BSTR bstrName, DWORD dwMode, BOOL fCreateTemp);
	STDMETHOD(Commit)		();

// IPersistStorage
	STDMETHOD(GetClassID)(LPCLSID);
	STDMETHOD(IsDirty)(void);
    STDMETHOD(InitNew)(LPSTORAGE);
    STDMETHOD(Load)(LPSTORAGE);
    STDMETHOD(Save)(LPSTORAGE, BOOL);
    STDMETHOD(SaveCompleted)(LPSTORAGE);
    STDMETHOD(HandsOffStorage)(void);

// IPersistStream
//  STDMETHOD(GetClassID)(LPCLSID);
//  STDMETHOD(IsDirty)(void);
    STDMETHOD(Load)(LPSTREAM);
    STDMETHOD(Save)(LPSTREAM, BOOL);
    STDMETHOD(GetSizeMax)(ULARGE_INTEGER FAR *);

// IOleItemContainer
	STDMETHOD(ParseDisplayName)(LPBC, LPOLESTR, ULONG*, LPMONIKER*);
	STDMETHOD(EnumObjects)(DWORD, LPENUMUNKNOWN*);
	STDMETHOD(LockContainer)(BOOL);
	STDMETHOD(GetObject)(LPOLESTR, DWORD, LPBINDCTX, REFIID, LPVOID*);
	STDMETHOD(GetObjectStorage)(LPOLESTR, LPBINDCTX, REFIID, LPVOID*);
	STDMETHOD(IsRunning)(LPOLESTR);
};

///////////////////////////////////////////////////////////////////////////////
// Versionskonstanten
const long OBJECTMANAGEMENT_SIGNATURE = 0x4D4A424FL;		// "OBJM"
const long OBJECTMANAGEMENT_VERSION_100 = 0x0100L;
const long OBJECTMANAGEMENT_VERSION_101 = 0x0101L;
const long OBJECTMANAGEMENT_VERSION = OBJECTMANAGEMENT_VERSION_101;
const long LASTKNOWN_OBJECTMANAGEMENT_VERSION = 0x01FFL;

///////////////////////////////////////////////////////////////////////////////
// 
typedef enum {
	PSSTATE_UNINIT,
	PSSTATE_WRITE,
	PSSTATE_ZOMBIE,
	PSSTATE_HANDSOFF
} PSSTATE;

typedef enum {
	MONIKER_FILE,
	MONIKER_STREAM,
	MONIKER_OTHER,
} MONIKER;

///////////////////////////////////////////////////////////////////////////////
// sonstige globale (i.e. nützliche) Funktionen
HRESULT LoadString (CString & str, int IDS);

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(p) if(!(p)){}else{delete p; p = NULL;}
#endif // DELETE_OBJ

#define RELEASE(p) if(p) { p -> Release(); p = NULL; }

///////////////////////////////////////////////////////////////////////////////
// Daten in einen Stream Schreiben/von dort lesen
template<class T>
inline HRESULT LoadData (IStream *pIStm, T &riVal)
{
ULONG ulBytes = 0;
HRESULT hr = pIStm -> Read (&riVal, sizeof(T), &ulBytes);

	if (sizeof(T) != ulBytes)
		return E_FAIL;
	return hr;
}

template<class T>
inline HRESULT SaveData (IStream *pIStm, T &riVal)
{
ULONG ulBytes = 0;
HRESULT hr = pIStm -> Write (&riVal, sizeof(T), &ulBytes);

	if (sizeof(T) != ulBytes)
		return E_FAIL;
	return hr;
}

#endif // !defined(_OBJMN_H__3DB1F093_E1AB_11D1_860B_00600875138A__INCLUDED_)
