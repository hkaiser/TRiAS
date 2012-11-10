// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 19.07.2002 09:47:45
//
// @doc
// @module Strecken.h | Declaration of the <c CStrecken> class

#if !defined(__STRECKEN_H_)
#define __STRECKEN_H_

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

#include "StreckenDlg.h"
#include "SegmKey.hxx"

/////////////////////////////////////////////////////////////////////////////
// Declaration diverser Klassen
#if !defined(_ENUM_LONG_ENUMERATOR_DEFINED)
#define _ENUM_LONG_ENUMERATOR_DEFINED

DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator2(LONG, __uuidof(IEnumLONG));		// definiert WEnumLONG (Wrapper für IEnum<LONG>)
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG 

#endif // _ENUM_LONG_ENUMERATOR_DEFINED

////////////////////////////////////////////////////////////////////////////

// Feature für spezielle Guids der Objekte generieren
typedef struct tagSEGMENTGUIDS {
	DWORD dwSize;
	HOBJECTS lIdent;	// [in] Zuordnungsobjektklasse
	HPROJECT hPr;		// [in] ZuordnungsDatenquelle
	HOBJECTS lPartIdent;	// [in] Zuordnungsobjektklasse Splittingergebnis
	HPROJECT hPartPr;		// [in] ZuordnungsDatenquelle Splittingergebnis
	short iMode;		// true - gefüllt
	TCHAR sGuid_Knoten[_MAX_PATH];
	long lGuid_Knoten;
	long lGuid_Knoten_Orig;
	TCHAR sGuid_Kante[_MAX_PATH];
	long lGuid_Kante;
	TCHAR sGuid_Original[_MAX_PATH];
	long lGuid_Original;
	TCHAR sErrorMode[_MAX_PATH];
	long lErrorMode;
} SEGMENTGUIDS;


/////////////////////////////////////////////////////////////////////////////
// CStrecken
class ATL_NO_VTABLE CStrecken : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStrecken, &CLSID_Strecken>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_ACTION_MUSTREPAINT |
			PROPCAPS_NONE
	};

	CStrecken() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_STRECKEN)
	{
		m_pCfgDlg = NULL;
		m_pKnoten = NULL;
	}
	~CStrecken()
	{
		DELETE_OBJ(m_pCfgDlg);

		DELETE_OBJ(m_pKnoten);
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_STRECKEN)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CStrecken)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
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
//
	CStreckenDlg * ActionDlg(void) { return m_pCfgDlg; }
	CSegKnotenTree * KnotenBaum(void) { return m_pKnoten; }

	bool AddConfigKnoten (const char *pKeyText);
	long GetConfigKnoten (const char *pKeyText);
	bool SetConfigKnoten (const char *pKeyText, long lONr);
	SEGMENTGUIDS *GetConfigGuid ( long lIdent);
	bool SetConfigGuid ( long lIdent);
	long LoadGuidInfo(char * sText,SEGMENTGUIDS *pSG, bool iMode = false);
	bool CreatePBDData ( SEGMENTGUIDS *pSG);


private:
	SEnumLONG m_Objects;		// zu bearbeitende Objektmenge
	CStreckenDlg *m_pCfgDlg;	// Konfigurationsdialog

//  Baum für Knoten
	CSegKnotenTree *m_pKnoten;
	SEGMENTGUIDS SG;

};

#endif // !defined(__STRECKEN_H_)
