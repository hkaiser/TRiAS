// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 09.12.2002 09:16:25 
//
// @doc
// @module SaveObjectCollection.h | Declaration of the <c CSaveObjectCollection> class

#if !defined(_SAVEOBJECTCOLLECTION_H__CA0D63EB_6D59_4A9F_8163_20E8684C188D__INCLUDED_)
#define _SAVEOBJECTCOLLECTION_H__CA0D63EB_6D59_4A9F_8163_20E8684C188D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "trias03.h"       // main symbols

#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>

#include "SaveObjectCollectionDlg.h"

///////////////////////////////////////////////////////////////////////////////
// Versioning (CSaveObjectCollection)
#define SAVEOBJCOLL_VERSION_100			0x0100
#define SAVEOBJCOLL_LASTKNOWNVERSION	SAVEOBJCOLL_VERSION_100
#define SAVEOBJCOLL_MINORVERSIONMASK	0xff
#define SAVEOBJCOLL_SIGNATURE			0x43424F53		// SOBC

///////////////////////////////////////////////////////////////////////////////
// Versioning (Objektmenge selbst)
#define OBJECTCOLL_VERSION_100			0x0100
#define OBJECTCOLL_LASTKNOWNVERSION		OBJECTCOLL_VERSION_100
#define OBJECTCOLL_MINORVERSIONMASK		0xff
#define OBJECTCOLL_SIGNATURE			0x434A424F		// OBJC

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
// CSaveObjectCollection
class ATL_NO_VTABLE CSaveObjectCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSaveObjectCollection, &CLSID_SaveObjectCollection>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_NONE
	};

	CSaveObjectCollection() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_SAVEOBJECTCOLLECTION)
	{
		m_pCfgDlg = NULL;
		TidySaveData(m_CfgData);
	}
	~CSaveObjectCollection()
	{
		DELETE_OBJ(m_pCfgDlg);
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_SAVEOBJECTCOLLECTION)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CSaveObjectCollection)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction3)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IPropertyInfo)
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
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);

// IPersistPropertyBag
	STDMETHOD(Load)(IPropertyBag *pBag, IErrorLog *pLog);

	static CLIPFORMAT GetClipFormat() { return RegisterClipboardFormat("TRiASEx.SaveObjectCollection.1"); }
	static LPWSTR GetUserType() { return L"TRiAS_PersistObjectCollection"; }
	static LPCWSTR GetSubStreamName() { return L"PersistObjectCollection"; }

	HRESULT SavePropertySet(IStorage *pIStg, DWORD rgMode);

protected:
	HRESULT InitStream (long lCnt);
	HRESULT ReOpenStream (IStream **ppIStm);

private:
	typedef list<pair<SEnumLONG, os_string> > CListOfPackets;
	CListOfPackets m_Objects;				// zu bearbeitende Objektmenge
	CListOfPackets::iterator m_itlist;
	long m_lPacket;							// Paketnummer

	CSaveObjectCollectionDlg *m_pCfgDlg;	// Konfigurationsdialog

	SAVEOBJCOLLDATA m_CfgData;
};

#endif // !defined(_SAVEOBJECTCOLLECTION_H__CA0D63EB_6D59_4A9F_8163_20E8684C188D__INCLUDED_)
