// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.08.99 22:25:27 
//
// @doc
// @module ObjectPropertyBase.h | Basisklasse für eine Objekteigenschaft
// (Declaration of the <c CObjectPropertyBase> class

#if !defined(_OBJECTPROPERTYBASE_H__CD5874B9_F0A4_11D2_9BE6_349620524153__INCLUDED_)
#define _OBJECTPROPERTYBASE_H__CD5874B9_F0A4_11D2_9BE6_349620524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/AtlCtlEx.h>		// ISpecifyPropertyPagesExImpl

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für eine Objekteigenschaft
class ATL_NO_VTABLE CObjectPropertyBase : 
	public IObjectProperty2,
	public IPersistStreamInit,
	public CComObjectRootEx<CComObjectThreadModel>
{
private:
	bool m_fIsReadOnly;
	bool m_fIsDirty;
	bool m_fIsInitialized;

	ULONG m_ulCnt;
	UINT m_uiHelpID;
	string m_strName;

public:
	static HRESULT WINAPI _Choice (void *pThis, REFIID iid, void **ppvObject, DWORD dw);
	BEGIN_COM_MAP(CObjectPropertyBase)
		COM_INTERFACE_ENTRY(IObjectProperty)
		COM_INTERFACE_ENTRY_FUNC(_ATL_IIDOF(IObjectProperty2), offsetofclass(IObjectProperty2, _ComMapClass), _Choice)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY_IID(_ATL_IIDOF(IPersistStream), IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

///////////////////////////////////////////////////////////////////////////////
//
public:
	CObjectPropertyBase (LPCSTR pcName, UINT uiHelpID, bool fReadOnly = true);
	CObjectPropertyBase (UINT uiNameID, UINT uiHelpID, bool fReadOnly = true);
	virtual	~CObjectPropertyBase (void);

// IPersist methods
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// IPersistStream methods
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);

// IPersistStreamInit methods
	STDMETHOD(InitNew)(THIS);

// IObjectProperty specific functions
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

// muß vom abgeleiteten Objekt überladen werden
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten) PURE;

// IObjectProperty2 specific functions
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

// sonstige Member
	void SetRO (bool fRO) { m_fIsReadOnly = fRO; }
	bool GetRO (void) { return m_fIsReadOnly; }
	void SetDirty (bool fDirty) { m_fIsDirty = fDirty; }
	bool GetDirty (void) { return m_fIsDirty; }
	bool GetInitialized (void) { return m_fIsInitialized; }
	void SetInitialized (bool fFlag = true) { m_fIsInitialized = fFlag; }

	void SetName (LPCSTR pcName) { if (NULL != pcName) m_strName = pcName; }
	LPCSTR GetName (void) { return m_strName.c_str(); }
	string &GetNameStr (void) { return m_strName; }

	ULONG IncrementCount() { return ++m_ulCnt; }
};

#endif // !defined(_OBJECTPROPERTYBASE_H__CD5874B9_F0A4_11D2_9BE6_349620524153__INCLUDED_)
