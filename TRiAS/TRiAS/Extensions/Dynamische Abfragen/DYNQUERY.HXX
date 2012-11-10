// Verwaltung dynamischer Abfragen
// File: DYNQUERY.HXX

#if !defined(_DYNQUERY_HXX)
#define _DYNQUERY_HXX

#include <ifndlong.h>
#include <iobjman.h>

#include <ospace/header.h>
#include <ospace/uss/std/map.h>
#include <ospace/uss/std/string.h>

///////////////////////////////////////////////////////////////////////////////
// Liste der ObjektMengen, die behandelt werden sollen
DefineSmartInterface(FindLONG);
DefineSmartInterface(EnumObjectsByNumber);
DefineSmartInterface(ObjectManagement);
DefineSmartInterface(Storage);
DefineSmartInterface(DynQueryObjEnums);

DefineSmartInterface2(DVisInfo, IID_DVisInfo);

class CVisEnum 
{
public:
	typedef CVisEnum self;

private:
	WFindLONG m_Objs;
	WDVisInfo m_Vis;
	ULONG m_ulPseudoIdent;

protected:
	void SetPseudoIdent (ULONG ulIdent) { m_ulPseudoIdent = ulIdent; }

public:
		CVisEnum (IEnumObjectsByNumber *pIObjs = NULL, DVisInfo *pIVis = NULL) throw (_com_error)
			: m_Objs(pIObjs), m_Vis(pIVis) 
		{ m_ulPseudoIdent = DEX_GetUniqueSysICode(); }
		CVisEnum (const CVisEnum & rhs) throw()
			: m_Objs(rhs.objs()), m_Vis(rhs.vis()), 
			  m_ulPseudoIdent(rhs.PseudoIdent()) {}
		~CVisEnum (void) throw() {}

	CVisEnum &operator= (const CVisEnum & rhs) throw() 
		{ m_Objs = rhs.objs(); m_Vis = rhs.vis(); m_ulPseudoIdent= rhs.PseudoIdent(); 
		  return *this; 
		}

	const WFindLONG &objs() const throw() { return m_Objs; }
	const WDVisInfo &vis() const throw() { return m_Vis; }
	ULONG PseudoIdent() const throw() { return m_ulPseudoIdent; }

	bool find (long lONr) throw(_com_error) 
		{ return (S_OK == m_Objs->HasLONG (lONr)) ? true : false; }

	friend void os_write (os_bstream& stream, const self& l);
	friend void os_read (os_bstream& stream, self& l);
};

OS_CLASS(CVisEnum);
OS_STREAM_OPERATORS(CVisEnum);

///////////////////////////////////////////////////////////////////////////////
// Menge der in einer Ansicht installierten dynamischen AbfrageListen
#include "DynQueryObjEnums.h"

///////////////////////////////////////////////////////////////////////////////
// Erweiterung
class CDynQueryExt : 
	public CTriasExtension,
	public IVisQuery,
	public CComCoClass<CDynQueryExt, &CLSID_DynQueryObjEnums>
{
public:
	typedef enum tagSTGMODE {
		STGMODE_Normal = 0,
		STGMODE_NoScribble = 1,
		STGMODE_HandsOff = 2,
		STGMODE_Unknown = -1,
	} STGMODE;

private:
	IExtendBScript *m_pIScript;		// BasicExtension
	IVisObjExt *m_pIVisObj;			// Visualiserung
	DWORD m_dwCookie;

	WDynQueryObjEnums m_Enums;		// Objektlisten der aktuellen Ansicht

	WObjectManagement m_ObjMan;		// unser Storage
	WStorage m_Stg;
	STGMODE m_StgMode;

	bool m_fSelViewReg;

protected:
	HRESULT GetIBScript (IExtendBScript **ppIBScript = NULL);
	HRESULT GetIVisInfo (IVisObjExt **ppIVisObj = NULL);
	HRESULT RegisterVisQuery (void);

// Menubefehle
	bool HilightSelectedObjects (HWND hWnd);

// Notifications
	bool OnExtensionsLoaded (void);
	HRESULT OnSaveDocument (IStorage *pIStg, bool fSameAsLoad);
	HRESULT OnSaveCompleted (IStorage *pIStg);
	HRESULT OnHandsOffStorage (void);
	bool OnProjectOpen(void);
	bool OnProjectToClose(void);
	bool OnViewSelected (char *pcView);

///////////////////////////////////////////////////////////////////////////////
// PseudoIdentBehandlung
	bool OnQueryPbdData (PBDDATA *pData);
	bool OnModPbdData (PBDDATA *pData);
	bool OnDelPbdData (PBDDATA *pData);
	bool OnEnumViewIdentsX (ENUMTEXTKEYEX *pEnumData);

// StorageHandling
	HRESULT InitStorage (void);
	HRESULT InitObjEnums (LPCSTR pcView = NULL);
	HRESULT ReleaseStorage (bool fSave = true);
	HRESULT GetSubStorage (IStorage *pIRootStg, IStorage **ppIStg, bool fCreate = false);

	bool HandleNotification (UINT uiMsg, bool &rfFlag, bool fRegister = true);

public:
// Die folgende Zeile nur, wenn aggregierte Erweiterung gefordert ist
	BEGIN_COM_MAP(CDynQueryExt)
		COM_INTERFACE_ENTRY(IVisQuery)
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)		// immer mit eintragen
	END_COM_MAP()

// Die folgende Zeile einfügen, wenn der alte Mechanismus der
// Registrierung der Erweiterungen intakt bleibt
	DECLARE_NO_REGISTRY();
	DECLARE_NOT_AGGREGATABLE_SINGLE(CDynQueryExt, g_pTE);

		CDynQueryExt (void);
		~CDynQueryExt (void);

	STDMETHOD_(bool, InitExtension) (THIS_ short iMode);
	STDMETHOD_(bool, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(bool, UnLoadExtension) (THIS);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, LPARAM lParam);

// IVisQuery
	STDMETHOD(GetIdentMode)(THIS_ LONG lIdent, BSTR bstrView, IDENTVISMODE *prgVisMode);
	STDMETHOD(GetObjectVis)(THIS_ LONG lONr, DVisInfo **ppIVis);
};

#endif // _DYNQUERY_HXX
