// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 06.12.2002 12:53:52 
//
// @doc    PropertyAction für Gitterbildung
// @module GitterPropAct.h | Declaration of the <c CGitterPropAct> class

#if !defined(_GITTERPROPACT_H__02FCCD93_DE4E_47A7_A480_06C7FCFA9117__INCLUDED_)
#define _GITTERPROPACT_H__02FCCD93_DE4E_47A7_A480_06C7FCFA9117__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "RasterR.h"       // Hauptsymbole (Ressourcen)

#include <triashelper.h>
#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>
#include <ospace/std/vector>

#include <eieruhr.hxx>			// CEierUhr

#include "SmartInterfaces.h"	// WExtendGeoRein
#include "GitterDlg.h"			// CGitterDlg




///////////////////////////////////////////////////////////////////////////////////////////////
// Declaration diverser Klassen
#if !defined(_ENUM_LONG_ENUMERATOR_DEFINED)
#define _ENUM_LONG_ENUMERATOR_DEFINED

DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator2(LONG, __uuidof(IEnumLONG));		// definiert WEnumLONG (Wrapper für IEnum<LONG>)
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG 

#endif // _ENUM_LONG_ENUMERATOR_DEFINED

// C6C5A147-D18E-43AE-8AE9-BDF72144A70B
EXTERN_C const GUID __declspec(selectany) CLSID_GitterPropAct = 
	{ 0xC6C5A147, 0xD18E, 0x43AE, 0x8A, 0xE9, 0xBD, 0xF7, 0x21, 0x44, 0xA7, 0x0B };


///////////////////////////////////////////////////////////////////////////////////////////////
// CGitterPropAct
class ATL_NO_VTABLE CGitterPropAct : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGitterPropAct, &CLSID_GitterPropAct>,
	public IObjectWithSiteImpl<CGitterPropAct>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE |
			PROPCAPS_ACTION_MUSTREPAINT
	};

	// Konstruktor, Destruktor
		CGitterPropAct (void);
		~CGitterPropAct (void);

	void FinalRelease (void);

	DECLARE_REGISTRY_RESOURCEID(IDR_GITTERPROPACT)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CGitterPropAct)
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
	STDMETHOD(PreConfigPages)(THIS_ IDataObject *pIDataObj, DWORD dwFlags);
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

private:
	HPROJECT m_hPr;			// Handle der Zieldatenquelle
	CoordTransX m_CTX;
	HWND m_hWnd;			// Handle des Fensters (Objektrecherchefenster oder Hauptfenster),
							//  aus dem die Gitterbildung ausgelöst wurde
	HDEX m_hDex;			// Handle der nachgeladenen Erweiterung Gitter.ext

	SEnumLONG m_InObjs;		// Objekt, für das Gitter gebildet werden sollen
	CGitterDlg* m_pCfgDlg;	// Konfigurationsdialog
	GRIDDATA m_caSelInfo;	// zuletzt weggeschriebene Parameter
	bool m_bIsDirty;		// Parameter des Dialogs wurden verändert (true)
	bool m_bHasInitData;	// Initialisierungsdaten für den Dialog wurden von Load()
							// bereitgestellt, konnten aber noch nicht an diesen
							// weitergereicht werden (true)

	bool m_bType;			// Gittertyp (Fläche: true, Linie: false)
	EPunkt m_PLO;			// linker oberer bzw. 
	EPunkt m_PRU;			//  rechter unterer Punkt des Bereiches in DB-Koordinaten
	double m_dTurnAngle;	// Winkel für Gitterdrehung (in Grad)

	long m_lGridCnt;		// Maximalanzahl der Gitterobjekte (die wirkliche Anzahl kann
							//  durch den EnthaltenIn-Test kleiner ausfallen)
	vector<long> m_vlObjNr;	// Feld der Objektnummer der gebildeten Gitterflächen bzw. -linien
	long m_lObjInd;			// Laufindex von m_vlObjNr

    WExtendGeoRein m_wGeoRein;	// Interface für Ankopplung von GeoRein.ext	
    bool m_bGeoRein;			// Ankopplung von GeoRein.ext ist erfolgt (true)


	void BuildGrids (long lONr, /*EPunkt PRO, EPunkt PLU, */double dXWidth, double dYWidth,
					 double& xb, double& yb);
	bool BuildAreaGrids (long lGridCntX, long lGridCntY, double xb, double yb, long lONr,
						 string sObjName);
	bool BuildLineGrids (long lGridCntX, long lGridCntY, double xb, double yb, long lONr,
						 string sObjName);
	void GridTerritory (EObjekt*& pGridTerr, long lONr);
	void TurnGrids (KoOrd* xr, KoOrd* yr, double xm, double ym, double dSin, double dCos,
					double dFak);
	void TurnHelpParameters (double& xm, double& ym, double& dFak, double& dSin, double& dCos);
	void StoreGrids (GeoObjekt& GO, ulong ulIdent, SpForm sfSForm, string sObjName);
	void BuildOutputObjects (IEnum<LONG>* pEnumOut);
};

#endif // !defined(_GITTERPROPACT_H__02FCCD93_DE4E_47A7_A480_06C7FCFA9117__INCLUDED_)
