// Definition des Interface für die Klasse "ObjektGeometrie"
// File: OBJGEXT.CXX


#include "GeometrP.hxx"

#include <defattr.h>	// StandardAttribute für Punkte, Linien etc. (DEF_SIZE_PUNKT_X, ...)

#include "objgguid.h"	// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie

#include <initguid.h>	// beim für Linken CLSID_UndoRedoObject erforderlich
#include <undoguid.h>	// CLSID_UndoRedoObject, IID_IUndoRedoModifyObject
#include <iunredo.hxx>	// LPUNDOREDOMODIFYOBJECT

#include "zeichnen.hxx"	// GetDotsPerMM


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// ================================================================================================
// Implementation des IInitObjektGeometrie-Interfaces
CObjGeometrieInit :: CObjGeometrieInit (LPUNKNOWN pIUnk, ObjektGeometrie* pOG)
{
	m_dwRefCnt = 0L;	// für Debug
	m_pOG = pOG;		// kein AddRef(), völlig abhängig
	m_pIUnk = pIUnk;
}



// ------------------------------------------------------------------------------------------------
CObjGeometrieInit :: ~CObjGeometrieInit (void)
{
}



// ------------------------------------------------------------------------------------------------
CObjGeometrieInit* CObjGeometrieInit :: CreateInstance (LPUNKNOWN pIUnk, ObjektGeometrie* pOG)
{
	_ASSERTE (pOG != 0);

CObjGeometrieInit* pOGInit = new CObjGeometrieInit (pIUnk, pOG);

	if (pOGInit == 0 || !pOGInit->FInit())
	{
		DELETE_OBJ (pOGInit);
		return 0;
	}

	return pOGInit;
} // CreateInstance


// ------------------------------------------------------------------------------------------------
bool CObjGeometrieInit :: FInit (void)
{
	if (m_pOG == 0)
		return false;	// m_pOG muß existieren
	return true;		// ansonsten ist nichts weiter zu tun
} // FInit


// ------------------------------------------------------------------------------------------------
// delegierte IUnknown-Interfaces
STDMETHODIMP CObjGeometrieInit :: QueryInterface (REFIID riid, LPVOID* ppvObj)
{
	_ASSERTE (ppvObj != 0);

	return m_pIUnk->QueryInterface (riid, ppvObj);
}


// ------------------------------------------------------------------------------------------------
STDMETHODIMP_ (ULONG) CObjGeometrieInit :: AddRef (void)
{
	m_dwRefCnt++;				// nur für Debug
	return m_pIUnk->AddRef();	// Delegierung
}


// ------------------------------------------------------------------------------------------------
STDMETHODIMP_ (ULONG) CObjGeometrieInit :: Release (void)
{
	m_dwRefCnt--;				// nur für Debug
	return m_pIUnk->Release();	// Delegierung
}


// ------------------------------------------------------------------------------------------------
// IInitObjektGeometrie-Methoden
STDMETHODIMP_ (HRESULT) CObjGeometrieInit :: InitObjGeometry (VOID)
{
	_ASSERTE (m_pOG != 0);

	if (m_pOG->FInit())
		return S_OK;
	return E_FAIL;
}


// ------------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieInit :: InitObjGeometry (LONG lONr)
{
	_ASSERTE (m_pOG != 0);

	if (m_pOG->FInit (lONr))
		return S_OK;
	return E_FAIL;
}


// ------------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieInit :: InitObjGeometry (LONG x, LONG y, short iOT)
{
	if (x > MAXKOORD || y > MAXKOORD)
		return E_FAIL;

	_ASSERTE (m_pOG != 0);

	if (m_pOG->FInit (x, y, iOT))
		return S_OK;
	return E_FAIL;
}


// ------------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieInit :: InitObjGeometry (LONG* x, LONG* y, LONG lAnz,
															  short iOT)
{
	_ASSERTE (m_pOG != 0);

	if (m_pOG->FInit (x, y, lAnz, iOT))
		return S_OK;
	return E_FAIL;
}



// ================================================================================================
// Implementation des IObjektGeometrie-Interfaces
CObjGeometrieFunkt :: CObjGeometrieFunkt (LPUNKNOWN pIUnk, ObjektGeometrie* pOG)
{
	m_dwRefCnt = 0L;
	m_pOG = pOG;	// kein AddRef(), völlig abhängig
	m_pIUnk = pIUnk;
}



// ------------------------------------------------------------------------------------------------
CObjGeometrieFunkt :: ~CObjGeometrieFunkt (void)
{
}



// ------------------------------------------------------------------------------------------------
CObjGeometrieFunkt* CObjGeometrieFunkt :: CreateInstance (LPUNKNOWN pIUnk, ObjektGeometrie* pOG)
{
CObjGeometrieFunkt* pOGFunkt = new CObjGeometrieFunkt (pIUnk, pOG);

	if (pOGFunkt == 0 || !pOGFunkt->FInit())
	{
		DELETE_OBJ (pOGFunkt);
		return 0;
	}

	return pOGFunkt;
} // CreateInstance


// ------------------------------------------------------------------------------------------------
bool CObjGeometrieFunkt :: FInit (void)
{
	if (m_pOG == 0)
		return false;	// m_pOG muß existieren
	return true;		// ansonsten ist nichts weiter zu tun
} // FInit


// ------------------------------------------------------------------------------------------------
// delegierte IUnknown-Interfaces
STDMETHODIMP CObjGeometrieFunkt :: QueryInterface (REFIID riid, LPVOID* ppvObj)
{
	_ASSERTE (ppvObj != 0);

	return m_pIUnk->QueryInterface (riid, ppvObj);
}


// ------------------------------------------------------------------------------------------------
STDMETHODIMP_ (ULONG) CObjGeometrieFunkt :: AddRef (void)
{
	m_dwRefCnt++;				// nur für Debug
	return m_pIUnk->AddRef();	// Delegierung
}


// ------------------------------------------------------------------------------------------------
STDMETHODIMP_ (ULONG) CObjGeometrieFunkt :: Release (void)
{
	m_dwRefCnt--;				// nur für Debug
	return m_pIUnk->Release();	// Delegierung
}



// ------------------------------------------------------------------------------------------------
// IObjektGeometrie-Methoden
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GetONr (LONG* plONr)
{
	_ASSERTE (m_pOG != 0);

	*plONr = m_pOG->lONr;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GetIdent (ULONG* pulIdent)
{
	_ASSERTE (m_pOG != 0);

	*pulIdent = m_pOG->lIdent;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: SetIdent (ULONG ulIdent)
{
	_ASSERTE (m_pOG != 0);

	m_pOG->lIdent = ulIdent;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GetObjTyp (short* piObjTyp)
{
	_ASSERTE (m_pOG != 0);

	*piObjTyp = m_pOG->iObjTyp;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: SetObjTyp (short iObjTyp)
{
	_ASSERTE (m_pOG != 0);

	m_pOG->iObjTyp = iObjTyp;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GetFlags (short* piFlags)
{
	_ASSERTE (m_pOG != 0);

	*piFlags = m_pOG->iFlags;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: SetFlags (short iFlags)
{
	_ASSERTE (m_pOG != 0);

	m_pOG->iFlags = iFlags;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GetCnt (LONG* plCnt)
{
	_ASSERTE (m_pOG != 0);

	*plCnt = m_pOG->lCnt;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: SetCnt (long lCnt)
{
	_ASSERTE (m_pOG != 0);

	m_pOG->lCnt = lCnt;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GetKCnt (short* piKCnt)
{
	_ASSERTE (m_pOG != 0);

	*piKCnt = m_pOG->iKCnt;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: SetKCnt (short iKCnt)
{
	_ASSERTE (m_pOG != 0);

	m_pOG->iKCnt = iKCnt;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GetX (VOID** ppX)
{
	if (ppX == 0)
		return E_POINTER;

	_ASSERTE (m_pOG != 0);

	*ppX = m_pOG->pdblX;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: SetX (void* pX)
{
	if (pX == 0)
		return E_POINTER;

	_ASSERTE (m_pOG != 0);

//	if (NULL != m_pOG->pdblX)		// #HK000208
//		delete (long *)m_pOG->pdblX;
	m_pOG->pdblX = pX;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GetY (VOID** ppY)
{
	if (ppY == 0)
		return E_POINTER;

	_ASSERTE (m_pOG != 0);

	*ppY = m_pOG->pdblY;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: SetY (void* pY)
{
	if (pY == 0)
		return E_POINTER;

	_ASSERTE (m_pOG != 0);

//	if (NULL != m_pOG->pdblY)		// #HK000208
//		delete (long *)m_pOG->pdblY;
	m_pOG->pdblY = pY;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GetLPCnt (LONG** pplCnt)
{
	if (pplCnt == 0)
		return E_POINTER;

	_ASSERTE (m_pOG != 0);

	*pplCnt = m_pOG->plCnt;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: SetLPCnt (LONG* plCnt, short iCnt)
{
	_ASSERTE (m_pOG != 0);

	DELETE_VEC (m_pOG->plCnt);

	if (0 == plCnt)	// wenn nicht Fläche
	{
		m_pOG->plCnt = 0;
		return S_OK;
	}

	_ASSERTE (iCnt > 0);

	m_pOG->plCnt = new long [iCnt];
	memcpy (m_pOG->plCnt, plCnt, sizeof (long) * iCnt);
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: AddPunkt (LONG x, LONG y, LONG lIndGes,
														short iKInd)
{
	if (x > MAXKOORD || y > MAXKOORD)
		return E_UNEXPECTED;

	_ASSERTE (m_pOG != 0);

	if (m_pOG->AddPunkt (EPunkt(x,y), lIndGes, iKInd))
		return S_OK;
	return E_FAIL;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: AddPunkt (LONG* plX, LONG* plY, LONG lAnzahl,
														LONG lIndGes, short iKInd)
{
	for (long i = 0; i < lAnzahl; i++)
	{
		if (plX[i] > MAXKOORD || plY[i] > MAXKOORD)
			return E_UNEXPECTED;
	}

	_ASSERTE (m_pOG != 0);

	if (m_pOG->AddPunkt ((KoOrd*)plX, (KoOrd*)plY, lAnzahl, lIndGes, iKInd))
		return S_OK;
	return E_FAIL;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: AddKante (LONG* x, LONG* y, LONG lSize,
														short iKontInd)
{
	if (m_pOG->AddKante (x, y, lSize, iKontInd))
		return S_OK;
	return E_FAIL;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: AddKantenTeil (IObjektGeometrie* pIOG,
														  LONG lAnfId, LONG lEndId, MoveDir MD)
{
	if (m_pOG->AddKantenTeil (pIOG, lAnfId, lEndId, MD))
		return S_OK;
	return E_FAIL;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: SubPunkt (LONG lIndGes, short* piKInd)
{
	if (m_pOG->SubPunkt (lIndGes, true, *piKInd))
		return S_OK;
	return E_FAIL;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: SubPunkt (LONG lIndGes, BOOL bEqVertDel,
														short* piKInd)
{
	if (m_pOG->SubPunkt (lIndGes, bEqVertDel, *piKInd))
		return S_OK;
	return E_FAIL;
}


// --------------------------------------------------------------------------------------------
// Ich kann mich noch nicht dazu durchringen, eine Routine zu schreiben, in der gleich mit
// "einem Schlag" alle lAnz Punkte gelöscht werden, da dieser Bereich der zu löschenden Punkte
// über eine Konturgrenze, ja sogar über mehrere Konturen gehen kann; dies hätte dann zur
// Folge, daß neben dem erneuten Zuziehen der Konturen auch noch das Löschen der Konturen
// abgetestet werden müßte.
// lTotalInd: Index des 1. zu löschenden Stützpunktes (als fortlaufender Index gezählt, d.h.
//            bei Flächenobjekten ohne Berücksichtigung von Konturen)
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: SubPunkt (LONG lAnz, LONG lIndGes,
														BOOL bEqVertDel, short* piKInd)
{
short iKInd = -1;	// Konturindex des 1. gelöschten Punktes (-1: für  den Fall, daß kein Punkt
					//  gelöscht wird)

	for (long j = 1; j <= lAnz; j++)
	{
		if (lIndGes < m_pOG->lCnt)
			if (!m_pOG->SubPunkt (lIndGes, bEqVertDel, iKInd))
				return E_FAIL;

		if (1 == j)
			*piKInd = iKInd;
	}
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: SubKante (short iAnzahl, short iKontInd)
{
	if (m_pOG->SubKante (iAnzahl, iKontInd))
		return S_OK;
	return E_FAIL;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: ModPunkt (LONG x, LONG y, LONG lIndGes)
{
	if (x > MAXKOORD || y > MAXKOORD)
		return E_UNEXPECTED;

	_ASSERTE (m_pOG != 0);

	if (m_pOG->ModPunkt (EPunkt(x,y), lIndGes))
		return S_OK;
	return E_FAIL;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GetVertexIndex (LONG lX, LONG lY, LONG* plInd)
{
	_ASSERTE (m_pOG != 0);
	_ASSERTE (plInd != 0);

	if (! m_pOG) return E_OUTOFMEMORY;

	if (m_pOG->GetVertexIndex (lX, lY, *plInd))
		return S_OK;

	return E_UNEXPECTED;	// Punkt (lX, lY) gehört nicht zu m_pOG
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GetLineIndex (LONG lX, LONG lY, LONG lEps,
															LONG* plInd)
{
	_ASSERTE (m_pOG != 0);
	_ASSERTE (plInd != 0);

	if (! m_pOG) return E_OUTOFMEMORY;

	if (m_pOG->GetLineIndex (lX, lY, lEps, *plInd))
		return S_OK;

	return E_UNEXPECTED;	// Punkt (lX, lY) liegt nicht in der Nähe einer m_pOG-Strecke
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: IndexTest (LONG lIndGes, short* piKInd,
														 LONG* plInd, IndPos* pipIP)
{
	_ASSERTE (m_pOG != 0);
	_ASSERTE (piKInd != 0);
	_ASSERTE (plInd != 0);
	_ASSERTE (pipIP != 0);

	*pipIP = m_pOG->IndexTest (lIndGes, *piKInd, *plInd);
	if (NICHTS == *pipIP)
		return E_FAIL;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: IndexVorNach (LONG lIndGes, LONG* plIndv,
															LONG* plIndn)
{
	_ASSERTE (m_pOG != 0);
	_ASSERTE (plIndv != 0);
	_ASSERTE (plIndn != 0);

	if (m_pOG->IndexVorNach (lIndGes, *plIndv, *plIndn))
		return S_OK;
	return E_FAIL;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: IndexVor (LONG lIndGes, LONG* plIndv)
{
	_ASSERTE (m_pOG != 0);
	_ASSERTE (plIndv != 0);

	if (m_pOG->IndexVor (lIndGes, *plIndv))
		return S_OK;
	return E_FAIL;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GetCont (LONG* plXmin, LONG* plXmax,
													   LONG* plYmin, LONG* plYmax)
{
	_ASSERTE (m_pOG != 0);

ObjRechteck OC = m_pOG->GetCont();

	*plXmin = OC.XMin();
	*plXmax = OC.XMax();
	*plYmin = OC.YMin();
	*plYmax = OC.YMax();
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: OrientDreh (short iKInd)
{
	_ASSERTE (m_pOG != 0);

	if (m_pOG->OrientDreh (iKInd))
		return S_OK;
	return E_FAIL;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: IsClear (void)
{
	_ASSERTE (m_pOG != 0);

	if (! m_pOG) return E_POINTER;

	return m_pOG->IsClear();
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: CursorPositionAtObject (LONG x, LONG y,
										  LONG lEpsX, LONG lEpsY, LONG lEpsStr, BOOL bInBorder,
										  CursPos* pCP, LONG* pGrabX, LONG* pGrabY)
{
	_ASSERTE (m_pOG != 0);

	if (! m_pOG) return E_POINTER;

	*pCP = m_pOG->CursorPositionAtObject (x, y, lEpsX, lEpsY, lEpsStr, bInBorder, *pGrabX, *pGrabY);
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: CursorInMarker (LONG x, LONG y, LONG lEpsX,
										LONG lEpsY, BOOL* pbInMark, LONG* pGrabX, LONG* pGrabY)
{
	_ASSERTE (m_pOG != 0);

	if (! m_pOG) return E_POINTER;

	*pbInMark = m_pOG->CursorInMarker (x, y, lEpsX, lEpsY, *pGrabX, *pGrabY);
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: CursorInObject (LONG x, LONG y, LONG lEpsX,
									LONG lEpsY, LONG lEpsLine, BOOL bInBorder, CursPos* pCP)
{
	_ASSERTE (m_pOG != 0);

	if (! m_pOG) return E_POINTER;

	*pCP = m_pOG->CursorInObject (x, y, lEpsX, lEpsY, lEpsLine, bInBorder);
	return S_OK;
}


// ------------------------------------------------------------------------------------------------
// neue bzw. modifizierte Geometrie an TRiAS übergeben;
// für bUndo == true wird Undo ermöglicht; in pRec wird der Bereich übergeben, der nach dem Undo
// neu zu zeichnen ist, für pRec == 0 wird der gesamte Bildschirm neu gezeichnet
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GeometrieAnTRiAS (BOOL bUndo, RECT* pRec)
{
#if _TRiAS_VER >= 0x0300
	_ASSERTE (_TRiAS_VER >= 0x0300);
#endif // _TRiAS_VER >= 0x0300
	return GeometrieAnTRiASEx (INT_PTR(NULL), bUndo, pRec);
}


// ------------------------------------------------------------------------------------------------
// neue bzw. modifizierte Geometrie an TRiAS übergeben;
// für bUndo == true wird Undo ermöglicht; in pRec wird der Bereich übergeben, der nach dem Undo
// neu zu zeichnen ist, für pRec == 0 wird der gesamte Bildschirm neu gezeichnet
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GeometrieAnTRiASEx (INT_PTR hPr, BOOL bUndo,
																  RECT* pRec)
{
#if _TRiAS_VER >= 0x0300
ulong ulIdent = m_pOG->lIdent;

	if (0 != ulIdent && (ulong)-1 != ulIdent)
	{
		if (DEX_GetROModeIdent (ulIdent))	// Objektklasse schreibgeschützt (R/O-Modus)
		{
			DEX_Error (RC_GeometrieAnTRiASEx, WC_CLASS_ISRO);
			return ERROR_WRITE_PROTECT;
		}
	}
	else
#endif // _TRiAS_VER >= 0x0300
	// Datenquelle schreibgeschützt (R/O-Modus)
	if (0 != DEX_GetROModeEx (reinterpret_cast<HPROJECT>(hPr)))
	{
		DEX_Error (RC_GeometrieAnTRiASEx, WC_DATASOURCE_ISRO);
		return ERROR_WRITE_PROTECT;
	}

	_ASSERTE (m_pOG != 0);

bool bResult = false;	// return-Wert von DEX_ModObjGeometrieEx()
long lONr = -1;			// Objektnummer des (i.d.R.) gespeicherten Objektes

	if (! bUndo)
	{
		// Cast vor m_pOG ist erforderlich, da ObjektGeometrie jetzt nicht nur mehr von
		// tagOBJGEOMETRIE sondern auch von IUnknown abgeleitet ist; DEX_GetObjGeometrie()
		// verlangt als Parameter tagOBJGEOMETRIE, am Beginn von ObjektGeometrie steht aber der
		// IUnknown-Pointer
		m_pOG->iFlags |= OGNoExtendedErrorCheck;	// das Teilen von Kanten wird erst einmal unterbunden (#WM021217)
		bResult = DEX_ModObjGeometrieEx (reinterpret_cast<HPROJECT>(hPr), *(OBJGEOMETRIE*)m_pOG);
		lONr = m_pOG->lONr;	// Objektnummer von m_pOG, wenn dieses Objekt abgespeichert wurde
	}

	else
	{
	HRESULT hr;

		_ASSERTE ((m_pOG->iFlags & OGNewObject) != 0 || (m_pOG->iFlags & OGModObject) != 0);

		// Abspeichern eines neuen Objektes
		if (m_pOG->iFlags & OGNewObject)
		{
		LPUNDOREDOCREATEOBJECT pIUndo = 0;

			// Undo-Objekt erzeugen (über OLE)
			// Undo-Text "Objekt erzeugen" kommt von TRiAS durch IID_IUndoRedoCreateObject
			hr = CoCreateInstance (CLSID_UndoRedoObject, 0, CLSCTX_INPROC_SERVER,
								   IID_IUndoRedoCreateObject, (LPVOID*) &pIUndo);

			m_pOG->iFlags |= OGNoExtendedErrorCheck;	// das Teilen von Kanten wird erst einmal unterbunden (#WM021217)
			bResult = DEX_ModObjGeometrieEx (reinterpret_cast<HPROJECT>(hPr), *(OBJGEOMETRIE*)m_pOG);
			lONr = m_pOG->lONr;	// Objektnummer von m_pOG, wenn dieses Objekt abgespeichert wurde

			if (0 != lONr && -1 != lONr)
			{
				if (SUCCEEDED(hr))				// Initialisierung eines Undo-Objektes
					hr = pIUndo->Init (m_pOG->lONr, m_pOG, pRec);
				if (NOERROR == hr)
					DEX_AddUndoRedo (pIUndo);	// Undo-Objekt an TRiAS
			}

			if (pIUndo)
			{
				pIUndo->Release();		// Undo-Objekt wieder freigeben
				pIUndo = 0;
			}
		}


		// Modifizierung eines schon vorhandenen Objektes
		else if (m_pOG->iFlags & OGModObject)
		{
		LPUNDOREDOMODIFYOBJECT pIUndo = 0;

			// Undo-Objekt erzeugen (über OLE)
			// Undo-Text "Objekt modifiziert" kommt von TRiAS durch IID_IUndoRedoModifyObject
			hr = CoCreateInstance (CLSID_UndoRedoObject, 0, CLSCTX_INPROC_SERVER,
								   IID_IUndoRedoModifyObject, (LPVOID*) &pIUndo);

			if (SUCCEEDED(hr))			// Initialisierung eines Undo-Objektes
				hr = pIUndo->Init (m_pOG->lONr, m_pOG, pRec);

			m_pOG->iFlags |= OGNoExtendedErrorCheck;	// das Teilen von Kanten wird erst einmal unterbunden (#WM021217)
			bResult = DEX_ModObjGeometrieEx (reinterpret_cast<HPROJECT>(hPr), *(OBJGEOMETRIE*)m_pOG);
			lONr = m_pOG->lONr;	// Objektnummer von m_pOG, wenn dieses Objekt abgespeichert wurde

			if (bResult && NOERROR == hr)
				DEX_AddUndoRedo (pIUndo);	// Undo-Objekt an TRiAS

			if (pIUndo)
			{
				pIUndo->Release();			// Undo-Objekt wieder freigeben
				pIUndo = 0;
			}
		}
	}

// ganz nach hinten genommen
	// es gibt 3 Fälle:
	// bResult == true,  lONr != 0, lONr != -1: fehlerfreies Objekt, wurde gespeichert
	// bResult == false, lONr != 0, lONr != -1: fehlerhaftes Objekt, wurde trotzdem gespeichert
	// bResult == false, lONr == 0:				fehlerhaftes Objekt, wurde nicht gespeichert

	_ASSERTE (lONr != 0 || bResult == false);
	_ASSERTE (lONr != -1 || bResult == false);

	if (bResult) return S_OK;		// fehlerfreies Objekt, wurde gespeichert
	if (0 != lONr && -1 != lONr)
		return S_FALSE;				// fehlerhaftes Objekt, wurde trotzdem gespeichert
	return E_FAIL;					// fehlerhaftes Objekt, wurde nicht gespeichert

} // GeometrieAnTRiASEx


// --------------------------------------------------------------------------------------------
// Rechteck, in dem das m_pOG-Objekt liegt (unter Berücksichtigung der Kontur-, Linienbreite
// bzw. Symbolgröße) ermitteln und zurückgeben
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: RectangleToDraw (RECT* pRec)
{
	return RectangleToDraw2 (pRec, 0);
}


// --------------------------------------------------------------------------------------------
// Rechteck, in dem das m_pOG-Objekt liegt (unter Berücksichtigung der Kontur-, Linienbreite
// bzw. Symbolgröße) ermitteln und zurückgeben
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: RectangleToDraw2 (RECT* pRec, int iMarkGr)
{
	_ASSERTE (m_pOG != 0);

	if (! m_pOG) return E_POINTER;

HRESULT hrRet = S_OK;	// return-Wert
double dQuot = 1.;		// Quotient von Bezugsmaßstab und Darstellungsmaßstab

	// Quotient aus Bezugs- und Darstellungsmaßstab ermitteln
	if (!DEX_GetActiveScaling (dQuot))
		dQuot = 1.;

	if (dQuot > 0)
		dQuot *= 100.;
	else	
	{
		_ASSERTE (dQuot > 0);
		hrRet = S_FALSE;
		dQuot = 1.;   // um Division durch Null vorzubeugen
	}
	
ObjRechteck OC;	// Container um editiertes Objekt
Point PLO, PRU;	// linker oberer (PLO) bzw. rechter unterer Eckpunkt (PRU) von OC im Point-Format
HANDLEVISINFO HVI;

	INITSTRUCT(HVI, HANDLEVISINFO);		// Initialisierung
	HVI.m_lIdent = m_pOG->lIdent;		// Identifikator
	HVI.m_pDesc = 0;					// beschreibender Text
	HVI.m_pView = 0;					// SichtName (aktuelle Sicht: 0)

Dimension dimDots = GetDotsPerMM (0);	// Pixel pro Millimeter für den Bildschirm

	switch (m_pOG->iObjTyp)
	{
		case OT_PUNKT:
		{
		SIZE sizePG;

			sizePG.cx = 1;	// für den Fall, daß kein Identifikator vergeben wurde (z.B. wenn
			sizePG.cy = 1;	// der Abbrechen-Button gedrückt wurde)
		
			if (0 != HVI.m_lIdent && -1 != HVI.m_lIdent)
			{
			PVISINFO PVI;

				HVI.m_iVTyp = VTPunkt;			// VisInfoTyp
				HVI.m_pVI = &(PVI.m_VI);		// generischer Pointer auf VisInfo
				if (DEX_GetIdentVisInfo (HVI))	// RückkehrCode ausgewertet
					sizePG = PVI.m_Size;		// Punktgröße (Eintrag aus der VisInfo)
				else
				{
					sizePG.cx = DEF_SIZE_PUNKT_X;
					sizePG.cy = DEF_SIZE_PUNKT_Y;
				}
			}

		// Größe des Punktsymbols in BS-Pixel in x- bzw. y-Richtung
		int ixpix = (int) (sizePG.cx * dimDots.Width() / dQuot);
		int iypix = (int) (sizePG.cy * dimDots.Height() / dQuot);
		Point PEO = BSKoordinaten (((KoOrd*)m_pOG->pdblX)[0], ((KoOrd*)m_pOG->pdblY)[0]);
					    
			PLO = Point (PEO.X() - ixpix/2, PEO.Y() + iypix/2);
			PRU = Point (PEO.X() + ixpix/2, PEO.Y() - iypix/2);
			break;
		}
			

		case OT_KANTE:
		{
		int iLinBr = 1;	// für den Fall, daß kein Identifikator vergeben wurde
		
			if (0 != HVI.m_lIdent && -1 != HVI.m_lIdent)
			{
			LVISINFO LVI;

				HVI.m_iVTyp = VTLinie;			// VisInfoTyp
				HVI.m_pVI = &(LVI.m_VI);        // generischer Pointer auf VisInfo
				if (DEX_GetIdentVisInfo (HVI))	// RückkehrCode ausgewertet
					iLinBr = LVI.m_Width;		// LinienBreite (Eintrag aus der
												//  Visualisierungsinformation)
				else
					iLinBr = DEF_WIDTH_LINIE;
			}
			
			OC = m_pOG->GetCont();
			PLO = BSKoordinaten (OC.XMin(), OC.YMax());

			// zu bildendes Rechteck noch um Linienbreite vergrößern
			PLO.X() -= (int) (iLinBr * dimDots.Width() / dQuot);
			PLO.Y() += (int) (iLinBr * dimDots.Height() / dQuot);
			PRU = BSKoordinaten (OC.XMax(), OC.YMin());
			PRU.X() += (int) (iLinBr * dimDots.Width() / dQuot);
			PRU.Y() -= (int) (iLinBr * dimDots.Height() / dQuot);
			break;
		}

		
		case OT_FLAECHE:
		{
		double dKontBr = 1.;	// für den Fall, daß kein Identifikator vergeben wurde
				
			if (0 != HVI.m_lIdent && -1 != HVI.m_lIdent)
			{
			FVISINFO FVI;

				HVI.m_iVTyp = VTFlaeche;			// VisInfoTyp
				HVI.m_pVI = &(FVI.m_VI);			// generischer Pointer auf VisInfo
				if (DEX_GetIdentVisInfo (HVI))	// RückkehrCode ausgewertet
					// m_Style ist ein 16-Bit-Wort mit mehreren Informationen; wenn das 16. Bit
					// ausgeblendet und der Rest durch 100 dividiert wird, liefert das ganzzahligen
					// Divisionsergebnis die Konturbreite in 0.01 mm, d.h. den Eintrag aus der
					// Visualisierungsinformation
					dKontBr = ((FVI.m_VI.m_Style) & 0x7FFF) / 100.;
				else
					dKontBr = DEF_WIDTH_FRAME;
			}
		
			OC = m_pOG->GetCont();
			PLO = BSKoordinaten (OC.XMin(), OC.YMax());

			// zu bildendes Rechteck noch um Konturbreite vergrößern
			PLO.X() -= (int) (dKontBr * dimDots.Width() / dQuot);
			PLO.Y() += (int) (dKontBr * dimDots.Height() / dQuot);
			PRU = BSKoordinaten (OC.XMax(), OC.YMin());
			PRU.X() += (int) (dKontBr * dimDots.Width() / dQuot);
			PRU.Y() -= (int) (dKontBr * dimDots.Height() / dQuot);
			break;
		}


		default:
			_ASSERTE (false);
			return E_UNEXPECTED;
	}

	// zu zeichnendes Rechteck noch um Markergröße und eine Sicherheitszugabe vergrößern
	pRec->left = PLO.X() - iMarkGr - iSicher;
	pRec->right = PRU.X() + iMarkGr + iSicher;
	pRec->top = PLO.Y() + iMarkGr + iSicher;
	pRec->bottom = PRU.Y() - iMarkGr - iSicher;
	 
	return hrRet;

} // RectangleToDraw2


// --------------------------------------------------------------------------------------------
// Testen, ob der Punkt (*plXP,*plYP) auf dem m_pOG-Objekt liegt; wenn nicht, dann den
// nächstgelegenen Punkt bestimmen und in (*plXP,*plYP) zurückgeben; dabei ist (*plXP,*plYP)
// mit einem Stützpunkt (Index *plInd) identisch (*pbSP = true) oder liegt auf der Strecke
// (*plInd, *plInd+1) (*pbSP = false)
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: GetPointOnObject (LONG* plXP, LONG* plYP,
																LONG* plInd, BOOL* pbSP)
{
	_ASSERTE (m_pOG != 0);
	_ASSERTE (plXP != 0);
	_ASSERTE (plYP != 0);

	if (!m_pOG || !plXP || !plYP) return E_POINTER;

HRESULT hrRet = S_OK;	// return-Wert

long lCnt = m_pOG->lCnt;
KoOrd* plX = (KoOrd*)m_pOG->pdblX;
KoOrd* plY = (KoOrd*)m_pOG->pdblY;
int iKCnt = m_pOG->iKCnt;
long* plCnt = m_pOG->plCnt;

KoOrd MinAbst1 = LONG_MAX;	// kleinster Abstand von (*plXP,*plYP) zu den Strecken des
							// m_pOG-Objektes
KoOrd Abst1;	// Abstand von Strecke Str (in for-Schleife)
long lInd1;		// Index für den kleinsten Abstand
EPunkt LPkt;		// Lotpunkt von (*plXP,*plYP) auf die m_pOG-Strecken mit MinAbst1
EPunkt LP;		// Lotpunkt von (*plXP,*plYP) auf eine m_pOG-Strecke

// kleinster Abstand von (*plXP,*plYP) zu den Stützpunkten des m_pOG-Objektes (Startwert ist
// der Abstand zum ersten Stützpunkt
EPunkt Pkt (*plXP,*plYP);
EPunkt P0 (plX[0], plY[0]);
KoOrd MinAbst2 = AbstandPktPktM (Pkt, P0);
KoOrd Abst2;	// Abstand vom Stützpunkt P2 (in for-Schleife)
long lInd2 = 0;	// Index für den kleinsten Abstand

	for (long i = 0; i < lCnt-1; i++)
	{
		// ist m_pOG eine Fläche, müssen die "Strecken" zwischen den Konturen beim Test
		// ausgelassen werden
		if (plCnt)	// m_pOG ist eine Fläche
		{
		bool bCont = false;		// die Strecke Str (P1, P2) ist keine "Strecke" zwischen den
								// Konturen

			for (int j = 0; j < iKCnt; j++)
				if (i == plCnt[j]-1)
				{
					bCont = true;
					break;			// Abbruch der j-for-Schleife
				}
			if (bCont) continue;	// für i-for-Schleife 
		}

	EPunkt P1 (plX[i], plY[i]);
	EPunkt P2 (plX[i+1], plY[i+1]);
	Strecke Str (P1, P2);

		if (Str.LotPktStrecke (Pkt, Abst1, LP) &&	// Abst1 gilt echt für die Strecke Str
			Abst1 < MinAbst1)						//  (nicht für deren Trägergerade)
		{
			lInd1 = i;
			MinAbst1 = Abst1;
			LPkt = LP;
		}

		if (MinAbst1 == 0)	// (*plXP,*plYP) liegt auf der Strecke Str, d.h. Routine kann
		{					//  beendet werden
			*plInd = i;
			if (*plXP == P1.X() && *plYP == P1.Y())
			{
				*pbSP = true;	// (*plXP,*plYP) ist mit P[i] identisch
				return S_OK;
			}
			if (*plXP == P2.X() && *plYP == P2.Y())
			{
				*plInd = i + 1;
				*pbSP = true;	// (*plXP,*plYP) ist mit P[i+1] identisch
				return S_OK;
			}
			*plXP = LPkt.X();
			*plYP = LPkt.Y();
			*pbSP = false;		// (*plXP,*plYP) liegt zwischen P[i] und P[i+1]
			return S_OK;
		}

		Abst2 = AbstandPktPktM (Pkt, P2);	// Abstand vom Stützpunkt P2 (pXK[i+1], pYK[i+1])
		if (Abst2 < MinAbst2)
		{
			lInd2 = i + 1;
			MinAbst2 = Abst2;
		}
	}


	// (*plXP,*plYP) liegt nicht auf dem m_pOG-Objekt, ist aber der m_pOG-Strecke
	// (lInd1, lInd1+1) näher als jedem Stützpunkt
	if (MinAbst1 < MinAbst2)
	{
		*plXP = LPkt.X();	// Lotpunkt von (*plXP,*plYP) auf Strecke (lInd1, lInd1+1) ist
		*plYP = LPkt.Y();	//  der Anfangspunkt
		*plInd = lInd1;
		if (*plXP == plX[lInd1] && *plYP == plY[lInd1])
		{
			*pbSP = true;	// (*plXP,*plYP) ist mit P[lInd1] identisch
			return S_OK;
		}
		if (*plXP == plX[lInd1+1] && *plYP == plY[lInd1+1])
		{
			(*plInd)++;
			*pbSP = true;	// (*plXP,*plYP) ist mit P[lInd1+1] identisch
			return S_OK;
		}
		*pbSP = false;		// (*plXP,*plYP) liegt zwischen P[lInd1] und P[lInd1+1]
		return S_OK;
	}


	// (*plXP,*plYP) liegt dem Stützpunkt mit dem Index lInd2 näher als jeder Strecke
	*plInd = lInd2;
	*plXP = plX [lInd2];
	*plYP = plY [lInd2];

	*pbSP = true;
	return S_OK;

} // GetPointOnObject


// --------------------------------------------------------------------------------------------
// Enthaltensein des Punktes (x,y) in der Fläche, die durch eine geschlossene Kante bzw. eine
// Flächenkontur gebildet wird; Rückgabe-Wert ist
//   INNERH   Punkt liegt innerhalb der Fläche
//   KONTUR   Punkt liegt auf Flächenrand
//   AUSSERH  Punkt liegt außerhalb der Fläche
//   OFFEN    Flächenrand nicht geschlossen bzw. entartete Fläche
// In bIsland wird angezeigt, ob bei einer Fläche die Inseln berücksichtigt werden sollen
// (true) oder nicht (false)
STDMETHODIMP_ (HRESULT) CObjGeometrieFunkt :: Position (LONG x, LONG y, BOOL bIsland,
														Posit* pLage)
{
	_ASSERTE (m_pOG != 0);

long n;		// Kantenlänge
KoOrd* plX = (KoOrd*)m_pOG->pdblX;
KoOrd* plY = (KoOrd*)m_pOG->pdblY;

	switch (m_pOG->iObjTyp)
	{
		case OT_KANTE:
			n = m_pOG->lCnt;
			break;

		case OT_FLAECHE:
			if (bIsland)
			{
				_ASSERTE (false);			// vorläufig !!!
				*pLage = UNKLAR;
				return S_FALSE;
			}
			else
				n = m_pOG->plCnt[0];
			break;

		default:
			*pLage = UNKLAR;
			return E_UNEXPECTED;
	}

	if (plX[0] != plX[n-1] && plY[0] != plY[n-1])	// Kante nicht geschlossen
	{
		*pLage = OFFEN;
		return S_FALSE;
	}

Strecke TLinie;		// Testlinie

	TLinie.AP().X() = x;
	TLinie.AP().Y() = y;
	TLinie.EP().X() = LONG_MAX;		// Testlinie soll waagrecht sein
	TLinie.EP().Y() = y;

long lAnzSchn = 0;	// Zähler für echte Schnitte der Testlinie mit der Kante
long j = n - 2;		// Index des letzten Konturpunktes, von dem bekannt ist, daß er nicht auf
					// der Testlinie liegt

	while (plX[j] == x && plY[j] >= y)
	{
		j--;
		if (j < 0)		// entartete Fläche, d.h. alle Punkte liegen auf einer Geraden, die mit
		{				// der Trägergeraden der TLinie identsch ist
			*pLage = UNKLAR;
			return E_UNEXPECTED;
		}
	}

int iBR1, iBR2, iBR3;
EPunkt TPkt (x, y);		// zu testender Punkt
Strecke Str1/*, Str2*/;		// Strecken der untersuchten Kante 

	for (long i = 0; i < n-1; i++)
	{
		Str1.AP().X() = plX[i];
		Str1.AP().Y() = plY[i];
		Str1.EP().X() = plX[i+1];
		Str1.EP().Y() = plY[i+1];

		if (Str1 == TPkt)
		{
			*pLage = KONTUR;
			return S_OK;
		}

		// Im 1. Teil der nachfolgenden if-Anweisung wird der Fall behandelt, daß der nächste
		// Stützpunkt SP(i) nicht auf der waagrechten Testlinie liegt. Liegt SP(i) auf der
		// Testlinie (else-Zweig), wird SP(i) i.a. ignoriert. Liegt jedoch der zu testende
		// Punkt im Dreieck SP(i-1),SP(i),SP(i+1), ergibt sich durch das Weglassen von SP(i)
		// eine Fehlinterpretation. Deshalb ist dieser Fall gesondert abzutesten.
		if (!(TLinie == Str1.AP()))
		{
			// Zähler inkrementieren, wenn echter Schnitt vorliegt, d. h. SP(i) und und SP(j)
			// auf verschiedenen Seiten der Testlinie liegen
			if (Intersection (plX[i], plY[i], plX[j], plY[j], TLinie.AP().X(), TLinie.AP().Y(),
							  TLinie.EP().X(), TLinie.EP().Y()))
				lAnzSchn++;
			j = i;
		}
		else    // SP(i) liegt auf der Teststrecke
		{
			iBR2 = TurnDirection (plX[i], plY[i], plX[i+1], plY[i+1], x, y);

			if (i > 0)
			{
				iBR1 = TurnDirection (plX[i-1], plY[i-1], plX[i], plY[i], x, y);
				iBR3 = TurnDirection (plX[i+1], plY[i+1], plX[i-1], plY[i-1], x, y);
			}
			else    // i = 0
			{
				iBR1 = TurnDirection (plX[n-2], plY[n-2], plX[0], plY[0], x, y);
				iBR3 = TurnDirection (plX[1], plY[1], plX[n-2], plY[n-2], x, y);
			}

			if (iBR1 >= 0 && iBR2 >= 0 && iBR3 >= 0)	// konvexe Ecke der geschlossenen Kante
			{
				*pLage = INNERH;	//  d.h. Punkt liegt innerhalb
				return S_OK;
			}
			if (iBR1 <= 0 && iBR2 <= 0 && iBR3 <= 0)	// konkave Ecke der geschlossenen Kante
			{
				*pLage = AUSSERH;	//  d.h. Punkt liegt außerhalb
				return S_OK;
			}
		}

	}

	if (lAnzSchn & 1)		// ungerader Zähler bedeutet Enthaltensein
		*pLage = INNERH;
	else
		*pLage = AUSSERH;
	return S_OK;

} // Position





// ============================================================================================
// globale Funktionen
// --------------------------------------------------------------------------------------------
// Erzeugung von IObjektGeometrie-Objekten
// Objekt aus Datenbank mit der Objektnummer lONr bereitstellen
HRESULT _GEOMETR_EXPORT CreateInterfaceOG (IObjektGeometrie** ppIOG, LONG lONr)
{
	if (! ppIOG) return E_POINTER;

	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

IInitObjektGeometrie* pInitOG = 0;
HRESULT hr1 = CoCreateInstance (CLSID_ObjektGeometrie, 0, CLSCTX_INPROC_SERVER,
								IID_IInitObjektGeometrie, (LPVOID*) &pInitOG);

	if (FAILED(hr1))
	{
		if (pInitOG)
		{
			pInitOG->Release();
			pInitOG = 0;
		}
		DEX_Error (RC_CreateInterfaceOG, EC_NOINTERFACEOG);
		return E_NOINTERFACE;
	}
	
HRESULT hrRet = pInitOG->InitObjGeometry (lONr);

	if (hrRet != S_OK)
	{
		if (pInitOG)
		{
			pInitOG->Release();
			pInitOG = 0;
		}
		DEX_Error (RC_CreateInterfaceOG, EC_NOINTERFACEOG);
		return E_NOINTERFACE;
	}
	hr1 = pInitOG->QueryInterface (IID_IObjektGeometrie, (LPVOID*) ppIOG);

ULONG ulRet = pInitOG->Release();

	pInitOG = 0;

	if (FAILED(hr1) || ulRet < 0 || *ppIOG == 0)
	{
		DEX_Error (RC_CreateInterfaceOG, EC_NOINTERFACEOG);
		return E_NOINTERFACE;
	}

	return S_OK;

} // CreateInterfaceOG


// --------------------------------------------------------------------------------------------
// Anlegen eines neuen Objektes mit dem Punkt (x,y) und dem Objekttyp iOT
HRESULT _GEOMETR_EXPORT CreateInterfaceOG (IObjektGeometrie** ppIOG, LONG x, LONG y, int iOT)
{
	if (! ppIOG) return E_POINTER;

	_ASSERTE (x >= 0);
	_ASSERTE (y >= 0);
	_ASSERTE (x <= MAXKOORD);
	_ASSERTE (y <= MAXKOORD);

IInitObjektGeometrie* pInitOG = 0;
HRESULT hr1 = CoCreateInstance (CLSID_ObjektGeometrie, 0, CLSCTX_INPROC_SERVER,
								IID_IInitObjektGeometrie, (LPVOID*) &pInitOG);

	if (FAILED(hr1))
	{
		if (pInitOG)
		{
			pInitOG->Release();
			pInitOG = 0;
		}
		DEX_Error (RC_CreateInterfaceOG, EC_NOINTERFACEOG);
		return E_NOINTERFACE;
	}

HRESULT hrRet = pInitOG->InitObjGeometry (x, y, iOT);

	if (hrRet != S_OK)
	{
		if (pInitOG)
		{
			pInitOG->Release();
			pInitOG = 0;
		}
		DEX_Error (RC_CreateInterfaceOG, EC_NOINTERFACEOG);
		return E_NOINTERFACE;
	}
	hr1 = pInitOG->QueryInterface (IID_IObjektGeometrie, (LPVOID*) ppIOG);

ULONG ulRet = pInitOG->Release();

	pInitOG = 0;

	if (FAILED(hr1) || ulRet < 0 || *ppIOG == 0)
	{
		DEX_Error (RC_CreateInterfaceOG, EC_NOINTERFACEOG);
		return E_NOINTERFACE;
	}

	return S_OK;

} // CreateInterfaceOG


// --------------------------------------------------------------------------------------------
// Anlegen eines neuen Objektes mit den x- bzw. y-Vektoren der Länge lAnz und dem Objekttyp iOT
HRESULT _GEOMETR_EXPORT CreateInterfaceOG (IObjektGeometrie** ppIOG, LONG* x, LONG* y,
										   LONG lAnz, int iOT)
{
	if (! ppIOG) return E_POINTER;

	_ASSERTE (x != 0);
	_ASSERTE (y != 0);
	_ASSERTE (lAnz > 0);

IInitObjektGeometrie* pInitOG = 0;
HRESULT hr1 = CoCreateInstance (CLSID_ObjektGeometrie, 0, CLSCTX_INPROC_SERVER,
								IID_IInitObjektGeometrie, (LPVOID*) &pInitOG);

	if (FAILED(hr1))
	{
		if (pInitOG)
		{
			pInitOG->Release();
			pInitOG = 0;
		}
		DEX_Error (RC_CreateInterfaceOG, EC_NOINTERFACEOG);
		return E_NOINTERFACE;
	}

HRESULT hrRet = pInitOG->InitObjGeometry (x, y, lAnz, iOT);

	if (hrRet != S_OK)
	{
		if (pInitOG)
		{
			pInitOG->Release();
			pInitOG = 0;
		}
		DEX_Error (RC_CreateInterfaceOG, EC_NOINTERFACEOG);
		return E_NOINTERFACE;
	}
	hr1 = pInitOG->QueryInterface (IID_IObjektGeometrie, (LPVOID*) ppIOG);

ULONG ulRet = pInitOG->Release();

	pInitOG = 0;

	if (FAILED(hr1) || ulRet < 0 || *ppIOG == 0)
	{
		DEX_Error (RC_CreateInterfaceOG, EC_NOINTERFACEOG);
		return E_NOINTERFACE;
	}

	return S_OK;

} // CreateInterfaceOG


// --------------------------------------------------------------------------------------------
// Berechnung des vorzeichenbehafteten Inhalts eines Polygonzuges (plXK,plYK) vom lAInd- bis
// zum lEInd-Index;
// ist der Polygonzug nicht geschlossen, dann wird zwischen dem ersten und dem letzten Punkt
// eine Verbindung angenommen;
// das (Nicht)Geschlossensein könnte einmal über bIsClosed zurückgegeben werden
//   Inhalt > 0: Umlaufsinn des Polygonzuges im math. positiven Drehsinn
//   Inhalt < 0: Umlaufsinn des Polygonzuges im math. negativen Drehsinn
//   Inhalt = 0: weniger als 3 Punkte
//   Formel: Anfangswert + Summe über alle x(n) * (y(n+1) - y(n-1))
BOOL _GEOMETR_EXPORT AreaSize (KoOrd* plXK, KoOrd* plYK, long lAInd, long lEInd,
							   CoordTransX* pCT, double* pdFlInh)
{
	*pdFlInh = 0.;		// für den Fehlerfall

	_ASSERTE (plXK != 0);
	_ASSERTE (plYK != 0);

	if (!plXK || !plYK) return false;

	if (lEInd - lAInd < 2) return false;	// zu wenig Punkte

long lLastInd = lEInd - 1;	// Index des letzten Punktes, mit dessen Koordinaten gerechnet wird
							// (lEInd-1 gilt für einen geschlossenen Polygonzug)
bool bIsClosed = true;

	if (plXK[lAInd] != plXK[lEInd] ||	// Polygonzug nicht
		plYK[lAInd] != plYK[lEInd])		//  geschlossen
	{
		lLastInd = lEInd;
		bIsClosed = false;
	}

	if (! pCT)
	{
	// Berechnung des Startwertes
	double dFl = (double)plXK[lAInd] * (double)(plYK[lAInd+1] - plYK[lLastInd]);

		// iterative Berechnung des Flächeninhaltes
		for (long i = lAInd + 1; i < lEInd; i++)
			dFl += (double)plXK[i] * (double)(plYK[i+1] - plYK[i-1]);

		// bei offenem Polygonzug noch zusätzlich
		if (!bIsClosed)
			dFl += (double)plXK[lEInd] * (double)(plYK[lAInd] - plYK[lEInd-1]);

		*pdFlInh = dFl / 2.;	// Inhalt halbieren und zurück
		return true;
	}


// Berechnung mit CoordTransX pCT (H. Kaiser)
DoublePair DP1, DP2, DP3;
double dFl = 0.0;

LPVOID pCTFData = 0;

	// Koordinatentransformation an erstem Punkt orientieren
	if (pCT->GetMetricParam (plXK[lAInd+1], plYK[lAInd+1], &pCTFData))
	{
		// Berechnung des Startwertes
		pCT->MetricEx (plXK[lAInd], plYK[lAInd], &DP1.X(), &DP1.Y(), pCTFData);
		pCT->MetricEx (plXK[lAInd+1], plYK[lAInd+1], &DP2.X(), &DP2.Y(), pCTFData);
		pCT->MetricEx (plXK[lLastInd], plYK[lLastInd], &DP3.X(), &DP3.Y(), pCTFData);
	
		// dFl = pdblX[lAInd] * (pdblY[lAInd+1] - pdblY[lLastInd])
		dFl = DP1.X() * (DP2.Y() - DP3.Y());

		// iterative Berechnung des Flächeninhaltes
		for (long i = lAInd + 1; i < lEInd; i++)
		{
			pCT->MetricEx (plXK[i], plYK[i], &DP1.X(), &DP1.Y(), pCTFData);
			pCT->MetricEx (plXK[i+1], plYK[i+1], &DP2.X(), &DP2.Y(), pCTFData);
			pCT->MetricEx (plXK[i-1], plYK[i-1], &DP3.X(), &DP3.Y(), pCTFData);
		
			// dFl += pdblX[i] * (pdblY[i+1] - pdblY[i-1])
			dFl += DP1.X() * (DP2.Y() - DP3.Y());
		}
		
		// bei offenem Polygonzug noch zusätzlich
		if (!bIsClosed)
		{
			pCT->MetricEx (plXK[lEInd], plYK[lEInd], &DP1.X(), &DP1.Y(), pCTFData);
			pCT->MetricEx (plXK[lAInd], plYK[lAInd], &DP2.X(), &DP2.Y(), pCTFData);
			pCT->MetricEx (plXK[lEInd-1], plYK[lEInd-1], &DP3.X(), &DP3.Y(), pCTFData);
		
			dFl += DP1.X() * (DP2.Y() - DP3.Y());
		}

		if (pCTFData) pCT->FreeMetricParam (pCTFData);
	}
	else
	{
		// Berechnung des Startwertes
		pCT->Metric (plXK[lAInd], plYK[lAInd], &DP1.X(), &DP1.Y());
		pCT->Metric (plXK[lAInd+1], plYK[lAInd+1], &DP2.X(), &DP2.Y());
		pCT->Metric (plXK[lLastInd], plYK[lLastInd], &DP3.X(), &DP3.Y());
		
		dFl = DP1.X() * (DP2.Y() - DP3.Y());

		// iterative Berechnung des Flächeninhaltes
		for (long i = lAInd + 1; i < lEInd; i++)
		{
			pCT->Metric (plXK[i], plYK[i], &DP1.X(), &DP1.Y());
			pCT->Metric (plXK[i+1], plYK[i+1], &DP2.X(), &DP2.Y());
			pCT->Metric (plXK[i-1], plYK[i-1], &DP3.X(), &DP3.Y());
			
			dFl += DP1.X() * (DP2.Y() - DP3.Y());
		}
		
		// bei offenem Polygonzug noch zusätzlich
		if (!bIsClosed)
		{
			pCT->Metric (plXK[lEInd], plYK[lEInd], &DP1.X(), &DP1.Y());
			pCT->Metric (plXK[lAInd], plYK[lAInd], &DP2.X(), &DP2.Y());
			pCT->Metric (plXK[lEInd-1], plYK[lEInd-1], &DP3.X(), &DP3.Y());
			
			dFl += DP1.X() * (DP2.Y() - DP3.Y());
		}
	}

	*pdFlInh = dFl / 2.;	// Inhalt halbieren und zurück
	return true;

} // AreaSize


// --------------------------------------------------------------------------------------------
// Berechnung des Flächeninhalt eines Flächenobjektes unter Berücksichtigung aller Inseln
BOOL _GEOMETR_EXPORT GetInhalt (IObjektGeometrie* pIOG, CoordTransX* pCT, double* pdFlInh)
{
	*pdFlInh = 0.;		// für Fehlerfall

	_ASSERTE (pIOG != 0);

	if (! pIOG) return false;

short iOT;

	pIOG->GetObjTyp (&iOT);

	if (OT_FLAECHE != iOT) return false;

KoOrd* plXK; KoOrd* plYK;
short iKCnt;
long* plCnt;

	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);
	pIOG->GetKCnt (&iKCnt);
	pIOG->GetLPCnt (&plCnt);

	// Inhalt der Außenkontur berechnen
	AreaSize (plXK, plYK, 0, plCnt[0]-1, pCT, pdFlInh);

	_ASSERTE (*pdFlInh > 0.);

    if (*pdFlInh <= 0.) return false;	// Inhalt konnte nicht (sinnvoll) berechnet werden

	if (iKCnt > 1)	// Fläche hat Innenkonturen
	{
	double dInhalt;
	long lAInd = plCnt[0];	// 1. Index der i-ten Innenkontur
	long lEInd;				// letzter Index der i-ten Innenkontur

		for (int i = 1; i < iKCnt; i++)
		{
			lEInd = lAInd + plCnt[i] - 1;
			AreaSize (plXK, plYK, lAInd, lEInd, pCT, &dInhalt);

			_ASSERTE (dInhalt <= 0.);

			*pdFlInh += dInhalt;	// Inhalt der Inseln subtrahieren (dInhalt ist negativ !)
			lAInd = lEInd + 1;
		}
	}

	return true;

} // GetInhalt


// --------------------------------------------------------------------------------------------
// Pkt auf den nächstgelegenen Punkt des pIOG-Objektes ziehen;
// i.d.R. wird das ein Punkt sein, der auf der Verbindungsstrecke zwischen 2 Stützpunkten liegt;
// lAInd ist der Anfangs- und lEInd der Endindex, innerhalb dessen der return-Punkt zu suchen
// ist (bei Linienobjekten wohl meistens die gesamte Linie, bei Flächenobjekten vermutlich oft
// nur eine Kontur);
// bei Flächenobjekten gibt bOuter an, ob return-Punkt außerhalb (true) oder innerhalb (false)
// des Objektes liegen soll;
// plPInd: Index des Stützpunktes, dem der return-Punkt am nächsten liegt
// plSInd: Index der Strecke, dem der return-Punkt am nächsten liegt
EPunkt _GEOMETR_EXPORT NearestPointToObject (EPunkt Pkt, IObjektGeometrie* pIOG, LONG lAInd,
										   LONG lEInd, BOOL bOuter, LONG* plPInd, LONG* plSInd)
{
	_ASSERTE (pIOG != NULL);

KoOrd* plXK; KoOrd* plYK;
long lCnt;

	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);
	pIOG->GetCnt (&lCnt);

KoOrd lMinAbst1 = LONG_MAX;	// kleinster Abstand von Pkt zu den Strecken des Objektes
KoOrd lMinAbst2 = LONG_MAX;	// kleinster Abstand von Pkt zu den Punkten des Objektes
KoOrd lAbst1;				// Abstand zur Strecke Str
KoOrd lAbst2;				// Abstand zum Punkt P1
EPunkt LPkt;				// Lotpunkt von Pkt auf die Strecken mit lMinAbst1
EPunkt LP;					// Lotpunkt von Pkt auf eine Strecke

    for (long i = lAInd; i < lEInd; i++)
    {
    EPunkt P1 (plXK[i], plYK[i]);
    EPunkt P2 (plXK[i+1], plYK[i+1]);
    Strecke Str (P1, P2);

    	if (Str.LotPktStrecke (Pkt, lAbst1, LP) &&	// lAbst1 gilt echt für die Strecke Str
    		lAbst1 < lMinAbst1)						//  (nicht für deren Trägergerade)
    	{
    		if (0 == lAbst1)		// Pkt liegt auf der Strecke Str
			{
				*plPInd = -1;
	    		*plSInd = -1;
				if (Pkt == P1)
					*plPInd = i;
				else if (Pkt == P2)
					*plPInd = i + 1;
				else
    				*plSInd = i;
    			return Pkt;
			}

			*plSInd = i;
    		lMinAbst1 = lAbst1;
    		LPkt = LP;
    	}

    	lAbst2 = AbstandPktPktM (Pkt, P1);
    	if (lAbst2 < lMinAbst2)
    	{
    		*plPInd = i;
    		lMinAbst2 = lAbst2;
    	}
    }

	// Abtestung des letzten Punktes (könnte bei offenen Linien noch etwas bringen)
	lAbst2 = AbstandPktPktM (Pkt.X(), Pkt.Y(), plXK[lEInd], plYK[lEInd]);
    if (lAbst2 < lMinAbst2)
    {
    	*plPInd = lEInd;
    	lMinAbst2 = lAbst2;
    }

    // Pkt liegt nicht auf dem Objekt, ist aber der Strecke (plSInd, plSInd+1) näher als jedem
    // Stützpunkt
    if (lMinAbst1 < lMinAbst2)
    {
	// wenn pIOG eine Fläche ist, muß zuerst getestet werden, ob die Strecke (plSInd, plSInd+1)
	// eine Verbindung zwischen 2 Kontur"schlössern" ist; wenn ja, dann wird der Endpunkt
	// dieser Strecke zurück gegeben, der Pkt am nächsten liegt
	if (!IslLinesegmentPermissible (pIOG, *plSInd))
	{
	KoOrd lAb1 = AbstandPktPktM (Pkt.X(), Pkt.Y(), plXK[*plSInd], plYK[*plSInd]);
	KoOrd lAb2 = AbstandPktPktM (Pkt.X(), Pkt.Y(), plXK[*plSInd+1], plYK[*plSInd+1]);

		if (lAb1 < lAb2)
			*plPInd = *plSInd;
		else
			*plPInd = *plSInd + 1;
		*plSInd = -1;
	    return EPunkt (plXK[*plPInd], plYK[*plPInd]);
	}

    EPunkt PA (plXK[*plSInd], plYK[*plSInd]);
    EPunkt PE (plXK[*plSInd+1], plYK[*plSInd+1]);

    	if (bOuter &&	// LPkt soll (trotz Rundung der LPkt-Koordinaten auf ganzzahlige Werte)
						// außerhalb des (plXK,plYK)-Objektes liegen
			// LPkt liegt innerhalb der Kontur (stimmt das auch bei Innenkonturen ?????)
			-1 == TurnDirection (PA.X(), PA.Y(), LPkt.X(), LPkt.Y(), PE.X(), PE.Y()))
    	{
    		LPkt.X()++;
    		if (-1 == TurnDirection (PA.X(), PA.Y(), LPkt.X(), LPkt.Y(), PE.X(), PE.Y()))
    		{
    			LPkt.X() = LPkt.X() - 2;
    			if (-1 == TurnDirection (PA.X(), PA.Y(), LPkt.X(), LPkt.Y(), PE.X(), PE.Y()))
    			{
    				LPkt.X()++;
    				LPkt.Y()++;
    				if (-1 == TurnDirection (PA.X(), PA.Y(), LPkt.X(), LPkt.Y(), PE.X(), PE.Y()))
    				{
    					LPkt.Y() = LPkt.Y() - 2;
    					if (-1 == TurnDirection (PA.X(), PA.Y(), LPkt.X(), LPkt.Y(), PE.X(), PE.Y()))
    						_ASSERTE (false);	// bis hierhin dürfte keiner mehr kommen
    				}
    			}
    		}
    	}

		*plPInd = -1;
    	return LPkt;		// Lotpunkt von Pkt auf Strecke (plSInd, plSInd+1)
    }

    // Pkt ist dem plPInd-ten Stützpunkt näher als jeder Strecke
	*plSInd = -1;
    return EPunkt (plXK[*plPInd], plYK[*plPInd]);

} // NearestPointToObject


// --------------------------------------------------------------------------------------------
// Hilfsroutine für NearestPointToObject();
// wenn pIOG eine Fläche ist, muß zuerst getestet werden, ob die Strecke (plSInd, plSInd+1)
// eine Verbindung zwischen 2 Kontur"schlössern" ist; wenn ja, dann wird der Endpunkt
// dieser Strecke zurück gegeben, der Pkt am nächsten liegt;
// der return-Wert ist "true", wenn (plSInd, plSInd+1) eine zulässige Strecke ist und "false",
// wenn es sich um eine Verbindungsstrecke zwischen 2 Kontur"schlössern" handelt
bool IslLinesegmentPermissible (IObjektGeometrie* pIOG, long lSInd)
{
	_ASSERTE (pIOG != NULL);

short iOT;

	pIOG->GetObjTyp (&iOT);

	if (OT_FLAECHE != iOT) return true;

short iKCnt;

	pIOG->GetKCnt (&iKCnt);

	if (iKCnt <= 1) return true;	// keine Innenkontur

long* plCnt;

	pIOG->GetLPCnt (&plCnt);
	for (int i = 1; i < iKCnt; i++)
	{
		if (lSInd == plCnt[i-1]-1)	// lSInd ist der Anfangsindex einer Strecke zwischen 2
			return false;			// Kontur"schlössern"
	}

	return true;

} // IslLinesegmentPermissible
