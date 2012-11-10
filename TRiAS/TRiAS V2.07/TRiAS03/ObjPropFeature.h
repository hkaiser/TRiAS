// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/12/1998 07:27:43 PM
//
// @doc
// @module ObjPropFeature.h | TRiAS-interne Merkmale als ReadWrite-Objekteigenschaft 

#if !defined(_OBJPROPFEATURE_H__399556B5_7A15_11D2_9EF4_006008447800__INCLUDED_)
#define _OBJPROPFEATURE_H__399556B5_7A15_11D2_9EF4_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Liefert TRiAS-internes Merkmal als Objekteigenschaft (ReadWrite!)

#if defined(_FORCE_LEGACY_CODE) || _MSC_VER < 1100
class ATL_NO_VTABLE CObjPropMerkmal : 
	public CBaseObjectProperty,
	public IInitObjPropMerkmal,
	public IPropertyTemplate,
	public IPropertyInfo2,
	public CComDualImpl<DSearchObjects, &IID_DSearchObjects, &LIBID_TRiASHelperLib, 
				TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DSearchObjects>,
	public CComCoClass<CObjPropMerkmal, &CLSID_ObjPropFeature>
{
private:
	LONG m_lCum;		// kumulativer Index
	TARGETMERKMAL m_TM;	// Struktur für DEX_...

	string m_strTemplate;
	bool m_fTemplateValid;
	bool m_fInitialized;

	short m_iMLen;
	short m_iMTyp;

protected:
	bool FInit (const CObjPropMerkmal &rOP);		// helper for Clone

public:
	static HRESULT WINAPI _Choice (void *pThis, REFIID iid, void **ppvObject, DWORD dw);
	BEGIN_COM_MAP(CObjPropMerkmal)
		COM_INTERFACE_ENTRY(IInitObjPropMerkmal)
		COM_INTERFACE_ENTRY(IPropertyTemplate)
		COM_INTERFACE_ENTRY2(IPropertyInfo, IPropertyInfo2)
		COM_INTERFACE_ENTRY(IPropertyInfo2)
		COM_INTERFACE_ENTRY_FUNC(IID_IObjectProperty2, 
					offsetofclass(IObjectProperty2, _ComMapClass),
					_Choice)
		COM_INTERFACE_ENTRY_IID(IID_IForceObjectProperty2, CObjPropMerkmal)
		COM_INTERFACE_ENTRY_CHAIN(CBaseObjectProperty)			// IDispatch der Basisklasse verwenden
		COM_INTERFACE_ENTRY(DSearchObjects)
		COM_INTERFACE_ENTRY2(IDispatch, DSearchObjects)			// ist eigentlich überflüssig
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

		CObjPropMerkmal (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IPersistStream methods ***
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);

// *** IInitObjPropMerkmal
	STDMETHOD(Init)(THIS_ LONG lMCode, BOOL fReadOnly);

// *** IPropertyTemplate specific methods
	STDMETHOD(SetTemplate)(THIS_ LPCSTR pcBuffer);
	STDMETHOD(GetTemplate)(THIS_ LPSTR pcBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(ApplyTemplate)(THIS_ LONG lONr);

	STDMETHOD(CloneTemplate)(THIS_ IPropertyTemplate **ppITempl);

// *** IPropertyInfo specific functions ***
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);
	STDMETHOD(SetHelpInfo) (THIS_ LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx);

// *** IPropertyInfo2 specific functions ***
	STDMETHOD(GetConfigData) (THIS_ VARIANT *pvOptData);
	STDMETHOD(EvaluatesForClass) (THIS_ INT_PTR hObjs);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Reset)(THIS);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

// *** DSearchObjects specific functions
	STDMETHOD(ConsiderSearch)(THIS_ BSTR bstrToMatch, SEARCHMODE rgFlags, ULONG ulCnt);
	STDMETHOD(SearchObjects)(THIS_ BSTR bstrToMatch, SEARCHMODE rgFlags, IEnumObjectsByNumber **ppvObj);

// other members
	void SetInitialized (bool fInit = true) { m_fInitialized = fInit ? true : false; }
	void SetTemplateValid (bool fFlag) { m_fTemplateValid = fFlag ? true : false; }

	void SetParams (short iMLen, short iMTyp) { m_iMLen = iMLen; m_iMTyp = iMTyp; }
	void GetParams (short &riMLen, short &riMTyp) { riMLen = m_iMLen; riMTyp = m_iMTyp; }

	void SetMCode (LONG lMCode) { m_TM.lMCode = lMCode; }
	LONG GetMCode (void) { return m_TM.lMCode; }

	string & GetTemplStr (void) { return m_strTemplate; }
	TARGETMERKMAL & GetTM (void) { return m_TM; }
};
#else
// Variante für TRiASDB
class ATL_NO_VTABLE CObjPropMerkmal : 
	public CBaseObjectProperty,
	public IInitObjPropMerkmal,
	public IPropertyTemplate,
	public IPropertyInfo,
	public IPropertyInfo2,
	public CComDualImpl<DSearchObjects, &IID_DSearchObjects, &LIBID_TRiASHelperLib, 
				TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DSearchObjects>,
	public CComCoClass<CObjPropMerkmal, &CLSID_ObjPropFeature>
{
private:
	INT_PTR m_lMCode;		// Handle der Objekteigenschaft
	short m_iMLen;
	short m_iMTyp;

	LONG m_lCum;			// kumulativer Index

	string m_strTemplate;
	bool m_fTemplateValid;
	bool m_fInitialized;


protected:
	bool FInit (const CObjPropMerkmal &rOP);		// helper for Clone
	HRESULT RetrieveFeature (INT_PTR lONr, ITRiASFeature **ppIFeat, ITRiASObject **ppIObj = NULL, bool fCreate = false);

public:
	static HRESULT WINAPI _Choice (void *pThis, REFIID iid, void **ppvObject, DWORD dw);
	BEGIN_COM_MAP(CObjPropMerkmal)
		COM_INTERFACE_ENTRY(IInitObjPropMerkmal)
		COM_INTERFACE_ENTRY(IPropertyTemplate)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IPropertyInfo2)
		COM_INTERFACE_ENTRY_FUNC(IID_IObjectProperty2, 
					offsetofclass(IObjectProperty2, _ComMapClass),
					_Choice)
		COM_INTERFACE_ENTRY_IID(IID_IForceObjectProperty2, CObjPropMerkmal)
		COM_INTERFACE_ENTRY_CHAIN(CBaseObjectProperty)			// IDispatch der Basisklasse verwenden
		COM_INTERFACE_ENTRY(DSearchObjects)
		COM_INTERFACE_ENTRY2(IDispatch, DSearchObjects)			// ist eigentlich überflüssig
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

		CObjPropMerkmal (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IPersistStream methods ***
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);

// *** IInitObjPropMerkmal
	STDMETHOD(Init)(THIS_ LONG lMCode, BOOL fReadOnly);

// *** IPropertyTemplate specific methods
	STDMETHOD(SetTemplate)(THIS_ LPCSTR pcBuffer);
	STDMETHOD(GetTemplate)(THIS_ LPSTR pcBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(ApplyTemplate)(THIS_ LONG lONr);

	STDMETHOD(CloneTemplate)(THIS_ IPropertyTemplate **ppITempl);

// *** IPropertyInfo specific functions ***
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);
	STDMETHOD(SetHelpInfo) (THIS_ LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx);

// *** IPropertyInfo2 specific functions ***
	STDMETHOD(GetConfigData) (THIS_ VARIANT *pvOptData);
	STDMETHOD(EvaluatesForClass) (THIS_ INT_PTR hObjs);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Reset)(THIS);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

// *** DSearchObjects specific functions
	STDMETHOD(ConsiderSearch)(THIS_ BSTR bstrToMatch, SEARCHMODE rgFlags, ULONG ulCnt);
	STDMETHOD(SearchObjects)(THIS_ BSTR bstrToMatch, SEARCHMODE rgFlags, IEnumObjectsByNumber **ppvObj);

// other members
	void SetInitialized (bool fInit = true) { m_fInitialized = fInit ? true : false; }
	void SetTemplateValid (bool fFlag) { m_fTemplateValid = fFlag ? true : false; }

	void SetParams (short iMLen, short iMTyp) { m_iMLen = iMLen; m_iMTyp = iMTyp; }
	void GetParams (short &riMLen, short &riMTyp) { riMLen = m_iMLen; riMTyp = m_iMTyp; }

	void SetMCode (INT_PTR lMCode) { m_lMCode = lMCode; }
	INT_PTR GetMCode (void) { return m_lMCode; }

	string & GetTemplStr (void) { return m_strTemplate; }
};
#endif // defined(_FORCE_LEGACY_CODE) || _MSC_VER < 1100

#endif // !defined(_OBJPROPFEATURE_H__399556B5_7A15_11D2_9EF4_006008447800__INCLUDED_)
