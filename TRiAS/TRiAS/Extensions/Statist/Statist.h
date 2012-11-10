// @doc 
// @module Statist.h | Declaration of the <c CStatist> class

#if !defined(_STATIST_H__CF461D86_EE47_11D2_9BE4_BAF620524153__INCLUDED_)
#define _STATIST_H__CF461D86_EE47_11D2_9BE4_BAF620524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <SIUnits/stdModel.h>

#include "resource.h"				// main symbols
#include "ProjectValueWindowImpl.h"

///////////////////////////////////////////////////////////////////////////////
// Guids etc.
EXTERN_C const CLSID __declspec(selectany) CLSID_FakeTRiASLockFeature = {0x26A3BD85,0x6D09,0x11D2,{0x9E,0xE7,0x00,0x60,0x08,0x44,0x78,0x00}};
EXTERN_C const IID __declspec(selectany) IID_IInitInnerObject = {0x58DAD7D6,0x6F34,0x11D2,{0x9E,0xEC,0x00,0x60,0x08,0x44,0x78,0x00}};
EXTERN_C const IID __declspec(selectany) IID_ITRiASLockFeatureEx = {0x9F6A6EC3,0x83A6,0x47FC,{0x9A,0x27,0xF1,0x9A,0x87,0xBD,0x8B,0x2B}};

///////////////////////////////////////////////////////////////////////////////
// Componet categories
// 19BBA822-01AA-4A90-B8E8-3F9D095A1216
EXTERN_C const CATID __declspec(selectany) CATID_TRiASStatistValue = 
	{ 0x19BBA822, 0x01AA, 0x4A90, 0xB8, 0xE8, 0x3F, 0x9D, 0x09, 0x5A, 0x12, 0x16 };

// 5784231F-3487-4EA9-ACE8-C5EADDB58794
EXTERN_C const GUID __declspec(selectany) CATID_TRiASStatistValuesContainer = 
	{ 0x5784231F, 0x3487, 0x4EA9, 0xAC, 0xE8, 0xC5, 0xEA, 0xDD, 0xB5, 0x87, 0x94 };

///////////////////////////////////////////////////////////////////////////////
// CStatist
class CConnectedCtf;

class ATL_NO_VTABLE CStatist : 
	public CComCoClass<CStatist, &CLSID_Statist>,
	public CTriasExtension,
	public CObjectProperties,
	public IDispatchImpl<ITRiASUsedUnits, &IID_ITRiASUsedUnits, &LIBID_TRiASStatistics>
{
public:
	CStatist() :
		m_lLastONr(-1L), m_lLastId(-1L), m_pCT(NULL),
		m_iUnitOfArea(-1), m_iUnitOfLength(-1), m_fAppendUnits(true)
	{
#if defined(_USE_PROJECTVALUES)
		m_pProjectBar = NULL;
#endif // defined(_USE_PROJECTVALUES)
	}

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(CStatist, g_pTE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CStatist)
		COM_INTERFACE_ENTRY(IObjectProps)
		COM_INTERFACE_ENTRY(ITRiASUsedUnits)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
	HRESULT hr = CTriasExtension::FinalConstruct();

		if (SUCCEEDED(hr))
			hr = CObjectProperties::FinalConstruct();
		return hr;
	}
	void FinalRelease()
	{
		FreeCoordTrans();
	}

// ITriasXtension
public:
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (void);
	STDMETHOD_(LRESULT, Notification) (WPARAM wParam, LPARAM lParam);

// IObjectProps
// Funktionen, welche gerufen werden, wenn BezugsObjekt/BezugsKlasse ge‰ndert wurde
	STDMETHOD(OnNewReferenceObject) (THIS_ INT_PTR hRefONr);
	STDMETHOD(OnNewReferenceObjects) (THIS_ INT_PTR hRefObjs, INT_PTR hRefObj);

	CConnectedCtf *GetCTF();
	int GetUnitOfArea() { return m_iUnitOfArea; }
	int GetUnitOfLength() { return m_iUnitOfLength; }
	bool GetAppendUnits() { return m_fAppendUnits; }
	void SetUnitOfArea(int iUnitOfArea, bool fSave = false) 
		{ m_iUnitOfArea = iUnitOfArea; if (fSave) SaveUnits(); }
	void SetUnitOfLength(int iUnitOfLength, bool fSave = false) 
		{ m_iUnitOfLength = iUnitOfLength; if (fSave) SaveUnits(); }
	void SetAppendUnits(bool fAppend = true, bool fSave = false)
		{ m_fAppendUnits = fAppend; if (fSave) SaveUnits(); }

	si::Length GetUoL(si::Length &rLength, os_string &rstrUnit);
	si::Area GetUoA(si::Area &rArea, os_string &rstrUnit);

#if defined(_USE_PROJECTVALUES)
// ProjektStatistiken
	bool IsProjectBarActive() { return (NULL != m_pProjectBar) ? true : false; }
	bool CreateProjectBar();
	bool ShowProjectBar();
	bool FreeProjectBar();
#endif // defined(_USE_PROJECTVALUES)

// ITRiASUsedUnits
	STDMETHOD(SaveUsedUnits)();
	STDMETHOD(RestoreUsedUnits)();
	STDMETHOD(get_AppendUnits)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_AppendUnits)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_UnitOfArea)(/*[out, retval]*/ UNITCONSTANTS *pVal);
	STDMETHOD(put_UnitOfArea)(/*[in]*/ UNITCONSTANTS newVal);
	STDMETHOD(get_UnitOfLength)(/*[out, retval]*/ UNITCONSTANTS *pVal);
	STDMETHOD(put_UnitOfLength)(/*[in]*/ UNITCONSTANTS newVal);

protected:
// manage object property stuff
	HRESULT InitObjectProperties();
	void FreeObjectProperties();
	HRESULT InstallPropertyFunctions (int iOTypes);

// Notification handlers
	HRESULT OnOpenDocument();
	HRESULT OnClosingProject();
	HRESULT OnProjectToClose();

// Koordinatensystem verwalten
	HRESULT InitCoordTrans();
	HRESULT FreeCoordTrans();

// Toolbar verwalten
	HRESULT InitToolbar();
	HRESULT FreeToolbar();

// Maﬂeinheiten verwalten
	void InitUnits();
	void SaveUnits();
	
private:
// Objekteigenschaften
	class CObjProps :
		public list<WObjectProperty> 
	{
	public:
		HRESULT InitObjectProperties (const CLSID **pClsId) 
		{
			for (/**/; NULL != *pClsId; pClsId++) {
			WObjectProperty ObjProp, Prop;

				if (SUCCEEDED(Prop.LocalCreateInstance (**pClsId))) {
				WInitInnerObject FakeLock (CLSID_FakeTRiASLockFeature);

					FakeLock -> SetInnerObject (Prop, ObjProp.GetIID(), ObjProp.ppu());
					if (!ObjProp.IsValid())
						ObjProp = Prop;

					push_back (ObjProp);
				}
			}
			return S_OK;
		}
		void FreeObjectProperties()	{ clear(); }
	};

	CObjProps m_PProps;		// Punkte
	CObjProps m_LProps;		// Linien
	CObjProps m_FProps;		// Fl‰chen
	CObjProps m_TProps;		// Texte

	INT_PTR m_lLastONr;		// zuletzt registriertes Objekt
	INT_PTR m_lLastId;		// zuletzt registrierte Objektklasse

// Koordinatentransformation
	CComObject<CConnectedCtf> *m_pCT;

// Maﬂeinheiten
	int m_iUnitOfArea;
	int m_iUnitOfLength;
	bool m_fAppendUnits; 

#if defined(_USE_PROJECTVALUES)
// ProjektStatistiken
	CProjectValueWindowImpl *m_pProjectBar;
#endif // defined(_USE_PROJECTVALUES)
};

#endif // !defined(_STATIST_H__CF461D86_EE47_11D2_9BE4_BAF620524153__INCLUDED_)
