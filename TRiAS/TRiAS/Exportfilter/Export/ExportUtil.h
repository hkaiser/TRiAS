// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 23.08.2002 10:25:02 
//
// @doc
// @module ExportUtil.h | Declaration of the <c CExportUtil> class

#if !defined(_EXPORTUTIL_H__4CC4183A_433E_4FF5_A2CF_F5C93293E4C2__INCLUDED_)
#define _EXPORTUTIL_H__4CC4183A_433E_4FF5_A2CF_F5C93293E4C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#pragma HDR_ON()

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectProps);
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(EnumObjProps);

///////////////////////////////////////////////////////////////////////////////
//
#include <ospace/std/map>
#include "../DoubleBuf.h"

///////////////////////////////////////////////////////////////////////////////
// Klasse, die die Verarbeitung der einzelnen Objekte der Eingabemenge erlaubt

typedef enum tagEXPCAPABILITY {
	EXP_HEADER				= 0x00000001,
	EXP_FEATURES			= 0x00000002,
	EXP_VISINFO				= 0x00000004,
	EXP_RAWCOORDINATES		= 0x00000008,

// KK000225
	EXP_STANDARDMERKMALE	= 0x00010000,	// Nur ObjName + UniqueIdent
	EXP_MERKMALDESCRIPTION	= 0x00020000,	// Merkmal-Beschreibungsdaten
	EXP_IDENTDESCRIPTION	= 0x00040000,	// ObjKl-Beschreibungsdaten
	EXP_RELATIONEN			= 0x00080000,	// Them. Relationen

// #HK020821
	EXP_OBJECTPROPERTIES	= 0x00100000,	// Objekteigenschaften exportieren
};

///////////////////////////////////////////////////////////////////////////////
// Datenstruktur zur Enumeration von Objekteigenschaften
typedef struct tagELKDATAHOLDER {
	long				m_lONr;
	long				m_lObjnameMCode;		// MCode des Objektnames
	long				m_lUniqueIdentMCode;	// MCode des UniqueIdent
	long				m_lGUIDMCode;			// MCode des GUID
	DOUBLEBUF*			m_pdblBuf;
	CTRiASXMLDocument	*m_xmd;
	IXMLElement			*m_pFeatures;
	IXMLElement			*m_pObject;
	tagELKDATAHOLDER(DOUBLEBUF *pdblBuf)
		: m_pdblBuf(pdblBuf)
		, m_lONr(-1)
		, m_lObjnameMCode(-1)
		, m_xmd(NULL)
		, m_pFeatures(NULL)
		, m_pObject(NULL)
	{}
} ELKDATAHOLDER, *LPELKDATAHOLDER;

///////////////////////////////////////////////////////////////////////////////
// TRiAS-Koordinatentransformator

#define __IParseRegularExpression_INTERFACE_DEFINED__
#define __IParseStringPairs_INTERFACE_DEFINED__
#define __IComposeStringPairs_INTERFACE_DEFINED__
#define _OBJECTTYPE_DEFINED

#include <CtfxMfc.h>
class CExportPropertyAction;

class CExportPropertyActionWorker 
{
private:
	///////////////////////////////////////////////////////////////////////////////
	// Iteration
	OutEnumLONG				&m_rOutIter;
	///////////////////////////////////////////////////////////////////////////////
	// Progressanzeige
	long					m_nObjects;
	// KK 000202 - Objektausgabe
	long					m_nCounter;
	HPROJECT				m_ActiveHPR;

	// Selektion
	BOOL m_bSelect;
	long m_lContONr;

	// Koordinatensystem
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> m_CS;

	CExportPropertyAction&	m_rExportPropertyAction;
	///////////////////////////////////////////////////////////////////////////////
	CCoordTransX			m_ctx;
	///////////////////////////////////////////////////////////////////////////////
	// XML-Dokument für Ausgabe
	DWORD					m_dwCapabilitys;
	CTRiASXMLDocument&		m_xmd;
	WXMLElement				m_pDatasources;	// zeigt auf Container mit Projekten
	WXMLElement				m_pCurrentDatasource;	// aktuelle Datenquelle
	HPROJECT				m_hCurrentDatasource;	// Handle der aktuellen Datenquelle
	long					m_lCurrentUIMCode;		// UniqueIdent MCode für die aktuelle Datenquelle
	long					m_lCurrentGUIDMCode;	// GUID MCode für die aktuelle Datenquelle
	WXMLElement				m_pCurrentObjects;		// Objektcontainer der aktuellen Objektklasse
	ULONG					m_hCurrentClass;		// Handle der aktuellen Objektklasse
	///////////////////////////////////////////////////////////////////////////////
	// Helferfunktionen
	HRESULT		GetXMLObjects( long lONr, IXMLElement** ppObjects );
	HRESULT		GetXMLObjectEntry( long lONr, IXMLElement* pObjects, IXMLElement** ppObject );
	HRESULT		FindOrCreateDatasource( HPROJECT hDatasource, IXMLElement** ppDatasource );
	HRESULT		FindOrCreateObjects( ULONG hClass, IXMLElement** ppObjects );
	///////////////////////////////////////////////////////////////////////////////
	// die eigentlichen Exporteure
	DOUBLEBUF&			m_dblBuf;				// Hilfspuffer
	char		m_DEXBUF[_MAX_PATH];
	HRESULT		BuildGeoDBHeader( WXMLElement& rpEntries, HPROJECT hDatasource );
	HRESULT		ExportHeader( WXMLElement& pProject, HPROJECT hDatasource = (HPROJECT) -1 );
	HRESULT		ExportVisinfo( long hClass, WXMLElement& pObject );
	HRESULT		ExportObject( long lONr, WXMLElement& pObjects, WXMLElement& pObject );
	HRESULT		ExportDependants( long lONr );
	HRESULT		ExportBaseFeatures( WXMLElement& pObject, ELKDATAHOLDER& ELKDH );
	HRESULT		ExportExtendedFeatures( WXMLElement& pObject, ELKDATAHOLDER& ELKDH );
	HRESULT		ExportCoordinates( WXMLElement& pObject, long lONr );

	BOOL EnumObjectProperties(ELKDATAHOLDER& ELKDH);

public:
	CExportPropertyActionWorker(CTRiASXMLDocument& xmlDocument, DOUBLEBUF& dblBuf, 
		OutEnumLONG &rOutIter, CExportPropertyAction& rExportPropertyAction, 
		DWORD dwCapabilitys, ITRiASCS *pICS)
	:	m_xmd(xmlDocument),
		m_rOutIter(rOutIter),
		m_rExportPropertyAction(rExportPropertyAction),
		m_nObjects(0),
		m_dblBuf(dblBuf),
		m_dwCapabilitys(dwCapabilitys),
		m_nCounter(0),
		m_lContONr(0),
		m_CS(pICS)
	{ 
	}

	~CExportPropertyActionWorker() 
	{
		m_nCounter = -1;
//		DeleteActiveSelection(-1);
		DeleteActiveSelection(m_nCounter);
	}

	HRESULT Initialize();
// KK000215
	HRESULT ReInitialize();
	HRESULT End (ENDMODE rgMode);

// KK000824
	HRESULT SetActiveSelection (void);
	HRESULT DeleteActiveSelection (long);
	bool GetActiveObjectSelection (long ONr, long lONr);

	///////////////////////////////////////////////////////////////////////////////
	// wird für jedes zu bearbeitende Objekt gerufen
	bool operator() ( LONG lONr );
};

namespace {
	inline
	HRESULT GetObjectProps (IObjectProps **ppIProps, HOBJECT lONr = INVALID_HOBJECT)
	{
	WObjectProps Props;
	BOOL fMustReInit = DEX_GetObjectProps (Props.ppi());

		if (Props.IsValid()) {
		// evtl. alle ObjProps installieren
			if (fMustReInit) {
				Props -> OnNewReferenceObject (-1L);	// alles bisherige löschen
				if (FAILED(Props -> OnNewReferenceObject (lONr))) 
					return FALSE;
				DEX_SetMustInitOPFs(FALSE);
			}
			*ppIProps = Props.detach();
			return S_OK;
		}
		return E_FAIL;
	}
}

#pragma HDR_OFF()

#endif // !defined(_EXPORTUTIL_H__4CC4183A_433E_4FF5_A2CF_F5C93293E4C2__INCLUDED_)
