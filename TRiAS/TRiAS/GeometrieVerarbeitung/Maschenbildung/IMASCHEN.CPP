/*
Datei: IMASCHEN.CPP

Stellt ein Interface für die Funktionen
	- Linenvereinigung und
	- Maschenbildung
zu Verfügung.

Erarbeitet:	J. Benkenstein				Stand vom 10.4.1997
*/

#include "pheader.h"			// vorübersetzter Header
#include "resource.h"			// Resource-Konstanten

//	STL-Header
#include <ospace/std/list>		// list
#include <ospace/std/map>		// map
//#include <ospace/std/algorithm>	// for_each 

//	TRiAS-Header
#include <IGeometr.hxx>			// IObjektGeometrie

//	GUID-Header
#include <objgguid.h>			// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie
#include <eonrguid.h>
#include <triashelper.h>
#include "linvguid.h"

//	Standard-Header
#include <ospace/com/smartif.h>			

//	Projekt-Header
#include "tools.hpp"			// FlaechenInhalt (), OutputFlaeche ()
#include "objkante.hpp"			// CObjektKante
#define _NO_PARAM_DIAOLOG
#include "ParamDlg.hpp"			// CParameters

//	Typdefs
typedef list<CObjektKante> CObjektKantenListe;
typedef list<CObjektKante>::iterator CObjektKantenList_tit;

//	Projekt-Header
DefineSmartInterface(EnumObjectsByNumber);	
#include "maschbil.hpp"			// CMaschenBildung
#include <hpp/progrsst.hpp>		// CProgressIndicator

#include "imaschen.h"			// zugeh. Interface-Header		
#include "imaschen_i.c"			// zugeh. Interface-Header		

#include "imaschen.hpp"			// zugeh. Header	

//	externe Variablen
extern const char ExtensionName [];		// Name der Erweiterung

#if _MSC_VER >= 1100
#include <new>
using std::bad_alloc;
#endif // _MSC_VER >= 1100

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CMaschenBildungI ------------------------------------------------------------
CMaschenBildungI :: CMaschenBildungI (void)
{
	//	nothing to do
}

HRESULT CMaschenBildungI :: FinalConstruct (void)
{
	HRESULT hr = S_OK;       

	try 
	{
	//	Erweiterung laden
		LOADEXTENSIONEX le;
		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = NULL;
		le.m_pName = ExtensionName;
		le.m_iMode = LEFullLoad;
		le.m_fGlobal = TRUE;		
		hr = DEX_ExternalLoadExtensionEx (le) ? S_OK : E_FAIL;
	} 
	catch (CException *e)
	{
		hr = E_OUTOFMEMORY;
		e -> Delete ();
	}
	return hr;
}

void CMaschenBildungI :: FinalRelease (void) 
{
//	Erweiterung entladen
	LOADEXTENSIONEX le;
	memset (&le, 0, sizeof (LOADEXTENSIONEX));
	le.m_pDesc = NULL;
	le.m_pName = ExtensionName;
	le.m_iMode = LENoLoad;
	le.m_fGlobal = TRUE;		
	DEX_ExternalUnLoadExtensionEx (le);
}

STDMETHODIMP CMaschenBildungI :: LinesUnion (
	IEnumObjectsByNumber *pInput,	// Objektnummern-Eingabe-Strom
	double	dTolerance,				// Fangbereich zweier Stützpunkte
	VARIANT_BOOL bOutputMerkmal,	// Merkmale der Vereinigten vererben
	VARIANT_BOOL bCreateAreas,		// erzeuge Flächen (TRUE) bzw. Linien (FALSE)
	VARIANT varPI,					// optional: Fortschrittsanzeige
	VARIANT *pvUsed,				// optional: Objektnummern der zur Vereinigung beitragenden
	IEnumObjectsByNumber **ppUnion)	// Objektnummern der Vereinigten
{
#if _MSC_VER >= 1200
	ASSERT(_MSC_VER < 1200);
#endif // _MSC_VER >= 1200
	return LinesUnion (INT_PTR(NULL), pInput, dTolerance, bOutputMerkmal, bCreateAreas, varPI,
					   pvUsed, ppUnion);
}

STDMETHODIMP CMaschenBildungI :: LinesUnion (
	INT_PTR hPr,
	IEnumObjectsByNumber *pInput,	// Objektnummern-Eingabe-Strom
	double	dTolerance,				// Fangbereich zweier Stützpunkte
	VARIANT_BOOL bOutputMerkmal,	// Merkmale der Vereinigten vererben
	VARIANT_BOOL bCreateAreas,		// erzeuge Flächen (TRUE) bzw. Linien (FALSE)
	VARIANT varPI,					// optional: Fortschrittsanzeige
	VARIANT *pvUsed,				// optional: Objektnummern der zur Vereinigung beitragenden
	IEnumObjectsByNumber **ppUnion)	// Objektnummern der Vereinigten
{
//	prüfe Parameter
	if ((NULL == pInput) || (NULL == ppUnion))
		return E_POINTER;

ULONG ulCnt = 0;	// Anzahl der Objekte im Eingabe-Strom (#WM990409)

	pInput->GetCount (&ulCnt);
	if (0 == ulCnt)
		return NOERROR;
	if (ulCnt < 0)
		return E_INVALIDARG;

	if (dTolerance < 0)
		return E_INVALIDARG;

	HRESULT hr = NO_ERROR;
	CProgressIndicator *pCPI = NULL;

	try
	{
	//	Undo beginnen
		CString strText;
		VERIFY (strText.LoadString(IDS_UNDO_TEXT_UNION));
		DEX_BeginUndoLevel ((const char*)strText);

		long lONr = 0;
		CObjektKantenListe Liste;			//	Liste der zu bildenden Maschen

	//	alle fehlerfreien Kanten speichern
		HRESULT hrt = NO_ERROR;
		for (pInput -> Reset(); S_OK == pInput -> Next (1, &lONr, NULL); /**/) 
		{
			ASSERT (lONr > 0);
			
			if (OGLinie != DEX_GetObjectType (lONr))	// wenn keine Linie
				continue;								// dann nächstes Objekt

		//	neues Objekt erzeugen und in Liste aufnehmen
			CObjektKante OK (lONr);
			hrt = OK.m_wIObjGeo -> IsClear ();
			if (S_OK == hrt)
				Liste.push_back (OK);
		}

	//	wenigstens 1 Objekt in Liste ?
		if (Liste.size () < 1)
			_com_issue_error (NOERROR);

	//	Ausgabestrom erzeugen
		WEnumObjectsByNumber wOutput (CLSID_EnumObjectsByNumber);

	//	Toleranzen berechnen
		CParameters Params;
		Params.Init ();
		Params.CalculateTolerances (Liste.front (), dTolerance);

	//	ggf. ProgressIndicator erzeugen
		HRESULT hrr = VariantChangeType (&varPI, &varPI, 0, VT_DISPATCH);
		if ((S_OK == hrr) && (NULL != varPI.pdispVal))
		{
			try 
			{
				WProgressIndicator2 wPI;
				wPI = varPI.pdispVal;
				pCPI = new CProgressIndicator (NULL, wPI);
			}
			catch (_com_error&)
			{
			}
		}

	//	Maschenbildung/LinienVereinigung
		CObjektKante Predikat;
		CMaschenBildung Maschen (Liste, wOutput, Params, Predikat);
		if (bCreateAreas)
			hr = Maschen.CreateMaschen (reinterpret_cast<HPROJECT>(hPr), pCPI, bOutputMerkmal);
		else
			hr = Maschen.CreateLines (reinterpret_cast<HPROJECT>(hPr), pCPI, bOutputMerkmal);

	//	bei schreibgeschützter Zieldatenquelle zurück
		if (ERROR_WRITE_PROTECT == hr)
		{
			DELETE_OBJ (pCPI);
			DEX_CancelUndoLevel (TRUE);
			return hr;
		}

	//	bei Nutzerabbruch zurück
		if (FAILED(hr))
			_com_issue_error (hr);

	//	ggf. restlichen Ausgabeströme zusammenbauen		
		if ((NULL != pvUsed) && (VT_ERROR != pvUsed -> vt))
		{
			WEnumObjectsByNumber wUsed (CLSID_EnumObjectsByNumber);
			CObjektKantenList_tit Iter;
			CObjektKante *pActKante = NULL;
			for (Iter = Liste.begin(); Iter != Liste.end(); Iter++)
			{
			//	Objektnummer lesen
				pActKante = &(*Iter);
				ASSERT (NULL != pActKante);
				lONr = pActKante -> GetObjNummer ();
				ASSERT (lONr > 0);

			//	Objektnummer speichern
				if ((*Iter).m_sBuildCnt > 0)				// wenn wenigstens einmal benutzt
					hr = wUsed -> AddItem (lONr);

				if (FAILED(hr))
					_com_issue_error (hr);
			}

		//	Ströme speichern
			V_VT (pvUsed) = VT_UNKNOWN;
			V_UNKNOWN (pvUsed) = (IUnknown *) wUsed.detach (); 
		}

		*ppUnion = wOutput.detach ();
	}	
	catch (_com_error& hrr)
	{
		hr = _COM_ERROR (hrr);
	}
	catch (CMemoryException *me)
	{
		me -> Delete ();
		hr = E_OUTOFMEMORY; 	
	}
	catch (bad_alloc *be)
	{
		be = NULL;
		
		hr = E_OUTOFMEMORY; 	
	}

//	Objekte wieder freigeben
	DELETE_OBJ (pCPI);

//	Undo auswerten
	if (SUCCEEDED (hr))
		DEX_EndUndoLevel ();
	else
		DEX_CancelUndoLevel (TRUE);

	return hr;
}
