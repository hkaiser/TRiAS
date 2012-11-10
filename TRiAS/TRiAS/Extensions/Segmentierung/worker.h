// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 19.07.2002 09:14:00 
//
// @doc
// @module Segment.h | Declaration of the <c CSegmentExtension> class

#if !defined(_WORKER_H_)
#define _WORKER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#pragma HDR_ON()

#include "resource.h"       // main symbols
#include "strecken.h"

/////////////////////////////////////////////////////////////////////////////
#define SEGMENT_Default	0x00
#define SEGMENT_Kante	0x01
#define SEGMENT_AP		0x02
#define SEGMENT_EP		0x04
#define SEGMENT_Feature	0x08
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
#define STRECKEN_Point	0x00
#define STRECKEN_Kante	0x01
/////////////////////////////////////////////////////////////////////////////
#define GUID_CCH	39

///////////////////////////////////////////////////////////////////////////////
// Map für MerkmalsCodes
typedef map<INT_PTR, os_string, less<INT_PTR> > CMCodeMap;

// StreckenObjekte (AP,EP,Kante) aus Segment generieren
typedef struct tagSEGMENTPARTS {
	DWORD dwSize;
	HOBJECT lONr;		// [in] Objektnummer des Segments
	HOBJECTS lIdent;	// [in] Zuordnungsobjektklasse
	HPROJECT hPr ;		// [in] ZuordnungsDatenquelle
	int iMode;			// [in] Modi 'SEGMENT_AP_...'
	HOBJECT *plNewKante;	// [out] Objektnummer des neu erzeugten Zuordnungsobjektes
	HOBJECT *plNewAP;	// [out] Objektnummer des neu erzeugten Zuordnungsobjektes
	HOBJECT *plNewEP;	// [out] Objektnummer des neu erzeugten Zuordnungsobjektes
} SEGMENTPARTS;

///////////////////////////////////////////////////////////////////////////////
// StreckenObjekte (AP,EP,Kante) aus Segment generieren
typedef struct tagCOPYFEAT {
	DWORD dwSize;
	HOBJECT lQuelle;		// [in] Objektnummer
	HOBJECT lZiel;			// [in] Zuordnungsobjektnummer
	HPROJECT hPr;			// [in] ZielDatenQuellenHandle
	CMCodeMap* m_Codes;
} COPYFEAT;


///////////////////////////////////////////////////////////////////////////////
//namespace {
///////////////////////////////////////////////////////////////////////////////
// Klasse, die die Verarbeitung der einzelnen Objekte der Eingabemenge erlaubt
	class CStreckenWorker 
	{
	public:
		CStreckenWorker(OutEnumLONG &rOutIter, CStrecken *pThis, CStrecken& rStreckenAction) : 
			m_pPA(pThis), m_rOutIter(rOutIter), m_rStreckenAction(rStreckenAction)
		{
			g_MCodes.clear();
			m_iMCodes = 0;
		}
		~CStreckenWorker() {}

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr);

	long StreckenKante (SEGMENTPARTS *pSP, KoOrd lXA, KoOrd lYA, KoOrd lXE, KoOrd lYE);
	long StreckenKnoten (SEGMENTPARTS *pSP, KoOrd lXP, KoOrd lYP);

	bool StreckenBasisFeature (long lONr, short iTyp);
	bool CopyFeature(long, long);
	bool StreckenGuidFeature (SEGMENTPARTS *pSP, SEGMENTGUIDS *pSG);

	HRESULT StreckenObjekte (SEGMENTPARTS *pSP, SEGMENTGUIDS *pSG);
	HRESULT StreckenError (long lONr,short iTyp, SEGMENTGUIDS *pSG);
	long LoadErrorMode(SEGMENTGUIDS *pSG);

	short DefineFeatures(long);

	private:
		IProgressIndicatorUsage *m_pPA;
		OutEnumLONG &m_rOutIter;
		CStrecken& m_rStreckenAction;
		HPROJECT m_hPr;
		CMCodeMap g_MCodes;
		short m_iMCodes;

	};
//} // namespace

#endif