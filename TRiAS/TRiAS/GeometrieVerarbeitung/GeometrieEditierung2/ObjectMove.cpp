// Definitionen: Implementation eines Interfaces für Erweiterung "GeometrieEditierung"
// Drag and Drop Source/Target für Geometrie- und Textobjekte
// File: ObjectMove.cpp


#include "GeoEditP.h"

#include "objgguid.h"	// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie

#include <resstrg.h>    // IDS_UIFORMAT
#include <defattr.h>	// StandardAttribute für Punkte, Linien etc. (DEF_SIZE_PUNKT_X, ...)
#include <propactn.h>	// c_feSelectedObjects

#include <dirisole.h>	// CLSID_DataTransferObject (muß NACH initguid.h stehen !!!)
#include <undoguid.h>	// IID_IUndoRedoCreateText, CLSID_UndoRedoObject
#include <iunredo.hxx>	// LPUNDOREDOCREATETEXT

#if _TRiAS_VER >= 0x0300
#include <Com/PropertyActionBaseDataImpl.cpp>
#endif // _TRiAS_VER >= 0x0300

#include "ObjectMove.h"



#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// --------------------------------------------------------------------------------------------
// Die Message 'DEXOR_RemoveFromListObject' führt KEIN automatisches UndoRedo mehr aus. Dafür
// sind die folgenden Messages dazugekommen, die ihrerseits ein UndoRedo erzeugen:
// DEXOR_AddObjectToListEx, DEXOR_RemoveFromListObjectEx und DEXOR_ReplaceObjectInListEx
// Da dies erst ab der TRiAS-Version V2.10.452 möglicht ist, folgendes Hilfskonstrukt
#ifndef DEXOR_ReplaceObjectInListEx
#define DEXOR_ReplaceObjectInListEx(x, y)	DEXOR_ReplaceObjectInList((x),(y))
#define DEXOR_AddObjectToListEx(x, y)		DEXOR_AddObjectToList((x),(y))
#define DEXOR_RemoveFromListObjectEx(x, y)	DEXOR_RemoveFromListObject((x),(y))
#endif // DEXOR_ReplaceObjectInListEx




///////////////////////////////////////////////////////////////////////////////////////////////
// externe Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// Objekt lAltObjNr in Recherchefenster hWnd durch Objekt lNeuObjNr ersetzen
BOOL _GEOEDIT_EXPORT FAR PASCAL InWelchesFenster (LONG hWnd, BOOL bNotLast, void* pData)
{
REPLACEOBJECT RO;

    INITSTRUCT (RO, REPLACEOBJECT);
    RO.lONr = ((MoveONr*)pData)->lAltObjNr;
    RO.lNewONr = ((MoveONr*)pData)->lNeuObjNr;
    DEXOR_ReplaceObjectInListEx ((HWND)hWnd, RO);
    InvalidateRect ((HWND)hWnd, NULL, true);	// Recherchefenster aktualisieren durch Neuzeichnen

    return true;
}

// Liefert Objektnummer des zugehörigen Objektes (wenn es eins gibt)
BOOL _GEOEDIT_EXPORT FAR PASCAL AttachedObject (long lONr, long lRCode, int iRTyp,
    											void* pData)
{
    (*(long*)pData) = lONr;
    return true;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor / Destruktor
CObjectMove::CObjectMove (void)
#if !defined(__ATL_20_USED__)
    	   : m_PPI(this)

#endif // !defined(__ATL_20_USED__)
{
    m_dwCookieN = 0L;
    m_dwCookieSN = 0L;
    m_dwCookiePI = 0L;
    m_pVWnd = g_pTE->MVWind();	// TRiAS-ViewFenster
    m_LeftButtonSem = false;	// linke Maustaste noch nicht gedrückt
    m_lParamOld = 0;			// letzte Mausposition
    m_bIsDropSource = false;	// DragDrop (noch) nicht von mir ausgelöst
    m_iVerz = GetProfileInt ("windows", "DragMinDist", DD_DEFDRAGMINDIST);
    m_plObjNrVO = NULL;
    m_plNeuObjNr = NULL;
    m_pPolyPoly = NULL;
    m_piPolyCounts = NULL;
    m_iAnzVO = 0;
    m_ptlOld.x = 0;
    m_ptlOld.y = 0;
}


// --------------------------------------------------------------------------------------------
CObjectMove::~CObjectMove (void)
{
	DELETE_VEC (m_plObjNrVO);
	DELETE_VEC (m_plNeuObjNr);
	DELETE_VEC (m_piPolyCounts);
	DELETE_VEC (m_pPolyPoly);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Verbindung zur GeoEdit-Erweiterung über deren Interface IEditExtensionSite herstellen
STDMETHODIMP CObjectMove::SetEditExtensionSite (IEditExtensionSite* pIEdExSite)
{
    try
    {
    	if (pIEdExSite != NULL)
    	{
    	WUnknown wISite;

    		// Verbindung zu TRiAS über Interface ITriasExtension herstellen
    		THROW_FAILED_HRESULT (pIEdExSite->GetXtensionSite (wISite.ppi()));
    		THROW_FAILED_HRESULT (pIEdExSite->CreateInterfaceTO (m_wTopObjs.ppi()));

    		if (wISite.IsValid()) 		// in TRiAS reinhängen
    		{
    			if (m_dwCookieN != 0L || m_dwCookieSN != 0L)	// anmelden
    				_com_issue_error (E_UNEXPECTED);		// darf noch nicht angemeldet sein

    			m_Site = wISite;			// throws_com_error
    			THROW_FAILED_HRESULT (AtlAdvise (m_Site, (ITRiASNotificationSink*)this,
    								  IID_ITRiASNotificationSink, &m_dwCookieN));

    			THROW_FAILED_HRESULT (AtlAdvise (m_Site, (ITRiASSysNotificationSink*)this,
    								  IID_ITRiASSysNotificationSink, &m_dwCookieSN));
    		}

    		m_wEdExSite = pIEdExSite;
    		THROW_FAILED_HRESULT (m_wTopObjs->GetEnumTopicalObjectsGeometry (TRUE, m_wAllTObjs.ppi()));
    	}
    	else
    	{
    		// Cursor wieder auf die Standard-Form "PFEIL" zurücksetzen
    		m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);

    		if (m_dwCookieN != 0L || m_dwCookieSN != 0L )	// abmelden
    			THROW_FAILED_HRESULT (DisconnectFromServer());	// gibt uns u.u. frei

    		m_wTopObjs.Assign (NULL);	// freigeben
    		m_wEdExSite.Assign (NULL);	// freigeben
    	}
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // SetEditExtensionSite


// --------------------------------------------------------------------------------------------
// TRiASNotificationSink und TRiASSysNotificationSink bei TRiAS wieder abmelden
HRESULT CObjectMove::DisconnectFromServer (void)
{
// künstliches AddRef, da uns nachfolgendes AtlUnadvise freigeben kann
WUnknown Unk ((IEditOperation*)this);

    AtlUnadvise (m_Site, IID_ITRiASNotificationSink, m_dwCookieN); 
    AtlUnadvise (m_Site, IID_ITRiASSysNotificationSink, m_dwCookieSN); 
    
    m_Site.Assign (NULL);	// freigeben von TRiAS
    m_dwCookieN = 0L;
    m_dwCookieSN = 0L;
    return S_OK;

} // DisconnectFromServer


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectMove::InformRestrictLinesState (IRestrictLine*, IRestrictLine*)
{
    ATLTRACENOTIMPL("CObjectMove::InformRestrictLinesState");
}

// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectMove::DeleteRestrictedCursor (void)
{
    ATLTRACENOTIMPL("CObjectMove::DeleteRestrictedCursor");
}


// --------------------------------------------------------------------------------------------
// Interface ITRiASNotificationSink: TRiAS-Notification's abfangen
STDMETHODIMP CObjectMove::ServerEvent (SERVEREVT se)
{
    ATLTRACE("CObjectMove::ServerEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectMove::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT vProj)
{
    ATLTRACE("CObjectMove::ProjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectMove::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
{
    ATLTRACE("CObjectMove::GeoViewEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectMove::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
    ATLTRACE("CObjectMove::GeoClassEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectMove::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
    switch (oe)
	{
		case GEOOBJECTEVT_ObjectSelected:
	    case GEOOBJECTEVT_ObjectUnSelected:
	    case GEOOBJECTEVT_ObjectDeleted:
		{
			try
			{
    			THROW_FAILED_HRESULT (m_wTopObjs->GetEnumTopicalObjectsGeometry (TRUE, m_wAllTObjs.ppi()));
			}
			catch (_com_error&)
			{
			    ATLTRACE("throw-failure in CObjectMove::GeoObjectEvent");
			}
			break;
		}
	}

    return S_OK;	// immer weiterleiten

} // GeoObjectEvent


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectMove::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
    ATLTRACE("CObjectMove::GeoFeatureEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectMove::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
    ATLTRACE("CObjectMove::GeoRelationEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectMove::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
    ATLTRACE("CObjectMove::ObjectWindowEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Interface ITRiASSysNotificationSink: WindowsNotification's abfangen
STDMETHODIMP CObjectMove::WindowsMessage (long hWnd, long uiMsg, long wParam, long lParam)
{
    switch (uiMsg)
    {
    	case WM_MOUSEMOVE:
//    		return MouseMove (lParam);
    		MouseMove (lParam);		// war das hier auch richtig ??? (21.01.99)
    		break;

    	case WM_LBUTTONDOWN:
    		LeftMouseDown (lParam);
    		break;

    	case WM_LBUTTONUP:
    		LeftMouseUp();
    }

    return S_OK;	// immer weiterleiten

} // WindowsMessage


// --------------------------------------------------------------------------------------------
// MouseMove bearbeiten
HRESULT CObjectMove::MouseMove (LPARAM lParam)
{
	if (NULL == g_pTE->MVWind())	// Projekt wird geschlossen oder kein Projekt geöffnet
    	return S_FALSE;				// NICHT "if (NULL == m_pVWnd)" !!!!

    if (lParam == m_lParamOld) return S_FALSE;		// keine neue Mausposition

    m_lParamOld = lParam;

CursPos CPos;		// aktuelle CursorPosition
HRESULT hr = m_wTopObjs->CursorInSomeTopObjects (m_wAllTObjs, false, &CPos);

    if (FAILED(hr)) return hr;

CursForm CForm;		// aktuelle CursorForm

    if (CURSPOS_OBJECT == CPos)	// Cursor innerhalb eines ausgewählten Objektes
    	CForm = CURSFORM_INOBJEKT;	// CursorForm für "Objekte verschieben"
    else
    	CForm = CURSFORM_PFEIL;		// Normalform des Cursors
    hr = m_wEdExSite->SetCursor (CForm, TRUE);

    // wenn Cursor noch CURSFORM_INOBJEKT-Form hat, dann Testung, ob DragDrop zu starten ist,
    // d.h. ob linke MausTaste gedrückt ist und
// (wenn NICHT nur Punktobjekte verschoben werden sollen)   seit 21.09.98 nun doch wieder nicht
	// mindestens m_iVerz Pixel bewegt wurden
    if (CURSFORM_INOBJEKT == CForm &&
    	m_LeftButtonSem)				// linke Maustaste wurde gedrückt
    {
/*	doch wieder heraus genommen, da Cursor bei Punktobjekten schon innerhalb des Rechtecks
	// umgeschaltet wird, das durch die Größe des Punktsymbols gebildet wird (21.09.98)
	long lONr;					// Objektnummer eines zu verschiebenden Objektes
	bool bOnlyPoints = true;	// nur Punktobjekte

		// Objekttyp aller zu verschiebenden Objekte prüfen
		for (m_wAllTObjs->Reset(); S_OK == m_wAllTObjs->Next (1, &lONr, NULL); )
    		if (OT_PUNKT != DEX_GetObjectType (lONr))
			{
				bOnlyPoints = false;
				break;
			}
*/
    Point Pt = BSPoint (lParam);

    	if (/*bOnlyPoints ||*/ // (31.12.98)
			abs(Pt.X() - m_StartPt.X()) >= m_iVerz ||
    		abs(Pt.Y() - m_StartPt.Y()) >= m_iVerz)
    	{
    		// m_LeftButtonSem = false ist an dieser Stelle erforderlich, um WM_LBUTTONUP
    		// nachzubilden, das in OLE "untergeht"
    		m_LeftButtonSem = false;
    		DoDragDropAction (MK_LBUTTON);		// "Drag" starten
    	}
    }

    return hr;

} // MouseMove


// --------------------------------------------------------------------------------------------
// Verschieben der Objekte beim Drücken der linken Maustaste vorbereiten
void CObjectMove::LeftMouseDown (LPARAM lParam)
{
    m_LeftButtonSem = true;	// linke Maustaste wurde gedrückt

	// BS-Punkt, bei dem linke Maustaste gedrückt wurde, als Startpunkt retten
    m_StartPt = BSPoint (lParam);

} // LeftMouseDown


// --------------------------------------------------------------------------------------------
// linke Maustaste nach Verschieben von Objekten losgelassen;
// im Normalfall wird diese Routine nicht gerufen, da WM_LBUTTONUP in OLE "untergeht";
// nachfolgende Zeile deshalb nur für den Fall, daß bei eingeschaltetem ObjectMove-Modus die
// linke Maustaste NEBEN einem recherchierten Objekt gedrückt wird, also keine Verschiebung
// erfolgt
void CObjectMove::LeftMouseUp (void)
{
    m_LeftButtonSem = false;

} // LeftMouseUp



///////////////////////////////////////////////////////////////////////////////////////////////
// DragDrop initialisieren und auslösen
HRESULT CObjectMove::DoDragDropAction (DWORD dwFlags)
{
HRESULT hr = S_OK;

	COM_TRY {
		m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);	// Standard-Cursor PFEIL wieder einstellen

	// Erzeugen des DataObjektes
	WDataObject DataObj (CLSID_DataTransferObject);
	WEnumLONG EnumObj (CLSID_EnumObjectsByNumber);		// throws_com_error

		// Füllen des DataObjektes
		{
		HRESULT hr = SetObjNummern ((IEnum<LONG>*)(IEnumLONG*)EnumObj);

    		if (SUCCEEDED(hr))
    			hr = SetEnumLONGData ((IEnum<LONG>*)(IEnumLONG*)EnumObj, DataObj);

    		if (FAILED(hr)) return hr;
		}

	// Erzeugen der DropSource
	WDropSource DropSrc;
	CEditDropSource* pSource = CEditDropSource::CreateInstance(this);
    
    	if (NULL == pSource) 
			_com_issue_error (E_OUTOFMEMORY);
    	
	THROW_FAILED_HRESULT (pSource->QueryInterface (IID_IDropSource, DropSrc.ppv()));
    	
    	pSource->FInit (this, dwFlags);

	// eigentliches DragDrop
	ResString resUndo (ResID (IDS_UNDOOBJECTSDRAGDROP, pRF), 50);
	DWORD dwEffect = DROPEFFECT_NONE;

		DEX_BeginUndoLevel (resUndo.Addr());

	// Erweiterungen eine Chance geben, zusätzliche Daten in das DataObject DataObj einzufügen
	WDragDropAction wDDAct;
	// m_pXtnSite ist das ITriasXtensionSite-Interface, in welches wir eingebaut sind
		THROW_FAILED_HRESULT(g_pTE->m_pXtnSite->QueryInterface (IID_IDragDropAction, wDDAct.ppv()));

	HWND hWndSrc = m_pVWnd->Handle(API_WINDOW_HWND);

		wDDAct->BeginDragDrop (DRAGDROPTYPE_VIEWWINDOW, hWndSrc, dwFlags, DataObj);

	// m_bIsDropSource für Unterscheidung, ob Daten aus TRiAS-Fenster (true) oder woanders
	// (z.B. aus Recherchefenster oder Legende) heraus gezogen wurden
		m_bIsDropSource = true;
		hr = ::DoDragDrop (DataObj, DropSrc, DROPEFFECT_MOVE|DROPEFFECT_COPY, &dwEffect);
		m_bIsDropSource = false;	

		if (SUCCEEDED(hr) && DRAGDROP_S_DROP == hr) {
    	// Erweiterungen davon in Kenntnis setzen, das alles vorbei ist
    		wDDAct->EndDragDrop (DRAGDROPTYPE_VIEWWINDOW, hWndSrc, dwEffect);

    		if (DROPEFFECT_MOVE == dwEffect)		// selektierte Objekte aus DB löschen
    			DeleteTopObjects ((IEnum<LONG>*)(IEnumLONG*)EnumObj);

    		DEX_EndUndoLevel();
    		return S_OK;
		}
	
	// Erweiterungen davon in Kenntnis setzen, das alles vorbei ist
		wDDAct->EndDragDrop (DRAGDROPTYPE_VIEWWINDOW, hWndSrc, DROPEFFECT_NONE);

		DEX_CancelUndoLevel(true);	// abgebrochen oder Fehler

	} COM_CATCH;
    return hr;
} // DoDragDropAction


// --------------------------------------------------------------------------------------------
// Objektnummern der ausgewählten Objekte in pEnum bereitstellen
HRESULT CObjectMove::SetObjNummern (IEnum<LONG>* pEnum)
{
long lONr;	// Objektnummer eines ausgewählten Objektes
WUnknown Unk;

//  for (m_wAllTObjs->Reset(); S_OK == m_wAllTObjs->Next (1, &lONr, NULL); )
    for (m_wAllTObjs->Reset(); S_OK == m_wAllTObjs->Next (1, Unk.ppi(), NULL); /**/) {
	WObjektGeometrie wObj (Unk);

		wObj->GetONr (&lONr);

	HRESULT hrRet = pEnum->AddItem (lONr);

    	if (FAILED (hrRet)) return hrRet;
    }
    return S_OK;

} // SetObjNummern


// --------------------------------------------------------------------------------------------
// Source-Objekte nach Objektverschiebung löschen
HRESULT CObjectMove::DeleteTopObjects (IEnum<LONG>* pEnum)
{
HRESULT hrRet = S_OK;	// return-Wert

// Löschen aller verschobenen Source-Objekte
long lAnz = (int)((IEnum<LONG>*)(IEnumLONG*)pEnum)->Count();	// Anzahl und
long* plObjNr = new long[lAnz];		//  Objektnummern der verschobenen Objekte
int i = 0;						// Laufindex für plObjNr

    if (! plObjNr)
    {
    	DEX_Error (RC_ObjectMove, EC_NOMEMORY);
    	return E_OUTOFMEMORY;
    }


    ((IEnum<LONG>*)(IEnumLONG*)pEnum)->Reset();

    hrRet = ((IEnum<LONG>*)(IEnumLONG*)pEnum)->Next (lAnz, plObjNr, NULL);

    _ASSERTE (hrRet == S_OK);

    if (S_OK != hrRet)
    {
	 	DELETE_VEC (plObjNr);
    	return hrRet;
    }

Rectangle Rec;		// rechteckiger Bereich für Neuzeichnen nach Löschen

    MultiRectangle (plObjNr, lAnz, Rec);

    if (lAnz >= 10)	{
	// ProgressIndicator erst ab 10 Objekten anwerfen
    	try
    	{
    	WProgressIndicator2 DPI (CLSID_ProgressIndicator);	// throws_com_error

    		THROW_FAILED_HRESULT (InitProgressIndicator (DPI, ResID(IDS_DELOBJECTS, pRF),
    							  ResID(IDS_DELETE_STATUS, pRF), lAnz));
    		THROW_FAILED_HRESULT (RegisterPI (DPI));

    	}
    	catch (_com_error& e)
    	{
	 		DELETE_VEC (plObjNr);
    		return _COM_ERROR (e);
    	}
	}

    for (i = 0; i < lAnz; i++)
    {
		hrRet = GetPIProxy()->IsCanceled();	// Abbruch des Löschens?

    if (FAILED(hrRet) ||
    	S_OK == hrRet ||	// Abbruch durch den Anwender
		FAILED(hrRet = GetPIProxy()->IncrementPosition (NULL)))
		break;

//char Buff [100] = { '\0' };
//sprintf (Buff, "DEX_DeleteObjectEx; lONr = %lu\n", plObjNr[i]);			          
//OutputDebugString (Buff);
    	if (! DEX_DeleteObjectEx (plObjNr[i]))
    	{
        	DEX_Error (RC_ObjectMove, EC_OBJNODELETE);
    		hrRet = E_UNEXPECTED;
    	}
    }

	DELETE_VEC (plObjNr);

    // die Objektnummern der gelöschten Objekte aus m_wAllTObjs entfernen und die neuen
    // Objektnummern aus m_plNeuObjNr übernehmen
    // !!! muß VOR  m_pVWnd->Update()  kommen, weil andererseits ein MouseMove() dazwischen
    // schlagen kann, das mit den schon gelöschten aber noch nicht refresh-ten Objekten
    // arbeiten will, was natürlich zu einem Fehler führen muß !!!
    RefreshTopObjects();

    if  (lAnz >= 10)
    {
    	hrRet = UnRegisterPI();
    	if (FAILED(hrRet)) return hrRet;
    }

    DEX_RePaintRectWait (Rec);	// zu löschende Objekte durch Neuzeichnen auch auf BS löschen
    m_pVWnd->Update();			// sofort zeichnen

    return hrRet;

} // DeleteTopObjects


// --------------------------------------------------------------------------------------------
// die Objektnummern der gelöschten Objekte aus m_wAllTObjs entfernen und die neuen
// Objektnummern /*aus m_plNeuObjNr */ übernehmen
void CObjectMove::RefreshTopObjects (void)
{
    m_wAllTObjs->Clear();

    if (NULL == m_plNeuObjNr)	// tritt bei Verschieben (nicht Kopieren) in ein anderes
    	return;					// Projekt auf

	m_wTopObjs->InitWithSelectedObjects();
	m_wTopObjs->GetEnumTopicalObjectsGeometry (TRUE, m_wAllTObjs.ppi());

} // RefreshTopObjects


// --------------------------------------------------------------------------------------------
bool CObjectMove::IsDropSource (void)
{
    return m_bIsDropSource;
}


// --------------------------------------------------------------------------------------------
// letzte Möglichkeit für die DatenQuelle den Drop doch noch zu verhindern
bool CObjectMove::FQueryDrop (void)
{
    return true;
}


// --------------------------------------------------------------------------------------------
// Objektnummern der verschobenen Objekte aus pIEnum wieder auslesen und in m_plObjNrVO
// bereitstellen
HRESULT CObjectMove::GetObjNummern (IDataObject* pIDataSource)
{
    _ASSERTE (pIDataSource != NULL);

// EnumLONG mit ObjektNummern aus DataSource holen
WEnumLONG EnumObj (CLSID_EnumObjectsByNumber);		// throws_com_error
HRESULT hr = GetEnumLONGData (pIDataSource, (IEnum<LONG>**)(IEnumLONG**)&EnumObj);

    if (FAILED(hr)) return hr;

    // Objektnummern der verschobenen Objekte in m_plObjNrVO bereitstellen, dazu zuerst Anzahl
    // der verschobenen Objekte	ermitteln
    m_iAnzVO = (int)((IEnum<LONG>*)(IEnumLONG*)EnumObj)->Count();
	DELETE_VEC (m_plObjNrVO);
    m_plObjNrVO = new long[m_iAnzVO];	// Objektnummern der verschobenen Objekte

    if (! m_plObjNrVO)
    {
    	DEX_Error (RC_ObjectMove, EC_NOMEMORY);
    	return E_OUTOFMEMORY;
    }

    ((IEnum<LONG>*)(IEnumLONG*)EnumObj)->Reset();

HRESULT hrRet = ((IEnum<LONG>*)(IEnumLONG*)EnumObj)->Next (m_iAnzVO, m_plObjNrVO, NULL);

    _ASSERTE (hrRet == S_OK);

    return hrRet;

} // GetObjNummern


// --------------------------------------------------------------------------------------------
// aus den DB-Koordinaten der zu verschiebenden Objekte Vektor mit BS-Koordinaten erzeugen
bool CObjectMove::UmrissVektor (void)
{
long lSPAnz;			// Parameter des/der Originalobjekte(s)
KoOrd* plXK; KoOrd* plYK;
short iObjTyp;
long lAnz = 0;			// Gesamt-Stützpunktanzahl aller zu verschiebenden Objekte

	DELETE_VEC (m_piPolyCounts);
    m_piPolyCounts = new int[m_iAnzVO];

    if (! m_piPolyCounts)
    {
    	DEX_Error (RC_ObjectMove, EC_NOMEMORY);
    	return false;
    }

const int i5 = 5;	// Anzahl der BS-Punkte für das Zeichnen des Umrisses eines Punktsymbols
WObjektGeometrie wObj;

    // die einzelnen und die Gesamt-Stützpunktanzahl der zu verschiebenden Objekte feststellen
    for (int i = 0; i < m_iAnzVO; i++)
    {
    	if (FAILED(CreateInterfaceOG (wObj.ppi(), m_plObjNrVO[i])))
    		return false;

    	wObj->GetObjTyp (&iObjTyp);

    	switch (iObjTyp)
    	{
    		case OT_PUNKT:
    			m_piPolyCounts[i] = i5;	// Rechteck um Punktsymbol
    			lAnz += i5;
    			break;

    		case OT_KANTE:
    			wObj->GetCnt (&lSPAnz);
    			m_piPolyCounts[i] = lSPAnz;
    			lAnz += lSPAnz;
    			break;

    		case OT_FLAECHE:
    		{
    		long* plCnt;

    			wObj->GetLPCnt (&plCnt);
    			m_piPolyCounts[i] = plCnt[0];	// nur die Außenkontur berücksichtigen
    			lAnz += plCnt[0];
    		}
    			break;

    		case OT_TEXT:
    		case OT_LABEL:		// indirektes Textobjekt
    			m_piPolyCounts[i] = i5;			// Rechteck um Textfeld
    			lAnz += i5;
    			break;
    	}
    }

long k = 0;		// Laufindex von m_pPolyPoly

	DELETE_VEC (m_pPolyPoly);
    m_pPolyPoly = new Point[lAnz];

    if (! m_pPolyPoly)
    {
    	DEX_Error (RC_ObjectMove, EC_NOMEMORY);
    	return false;
    }

KoOrd lCO[4];	// Containerkoordinaten eines Textobjektes
    			// lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax

    // die DB-Koordinaten der zu verschiebenden Objekte in BS-Koordinaten konvertieren
    for (i = 0; i < m_iAnzVO; i++)
    {
    	if (FAILED(CreateInterfaceOG (wObj.ppi(), m_plObjNrVO[i])))
    		return false;

    	wObj->GetObjTyp (&iObjTyp);
    	wObj->GetX ((void**)&plXK);
    	wObj->GetY ((void**)&plYK);

    	switch (iObjTyp)
    	{
    		case OT_PUNKT:
    		{
    		Point Pt = BSKoordinaten (plXK[0], plYK[0]); 
    		int iPixX, iPixY;	// Größe eines Punktsymbols in BS-Pixel

    			PointSymbolSize (DEX_GetObjIdentEx (m_plObjNrVO[i]), iPixX, iPixY);
    			m_pPolyPoly[k]   = Point (Pt.X()-iPixX/2, Pt.Y()+iPixY/2);
    			m_pPolyPoly[k+1] = Point (Pt.X()+iPixX/2, Pt.Y()+iPixY/2);
    			m_pPolyPoly[k+2] = Point (Pt.X()+iPixX/2, Pt.Y()-iPixY/2);
    			m_pPolyPoly[k+3] = Point (Pt.X()-iPixX/2, Pt.Y()-iPixY/2);
    			m_pPolyPoly[k+4] = Point (Pt.X()-iPixX/2, Pt.Y()+iPixY/2);
    			k += i5;
    			break;
    		}

    		case OT_KANTE:
    		{
    			wObj->GetCnt (&lSPAnz);
    			for (long j = 0; j < lSPAnz; j++, k++)
    				m_pPolyPoly[k] = BSKoordinaten (plXK[j], plYK[j]);
    			break;
    		}

    		case OT_FLAECHE:
    		{
    		long* plCnt;

    			wObj->GetLPCnt (&plCnt);
    			for (long j = 0; j < plCnt[0]; j++, k++)
    				m_pPolyPoly[k] = BSKoordinaten (plXK[j], plYK[j]);
    			break;
    		}

    		case OT_TEXT:
    		case OT_LABEL:		// indirektes Textobjekt
    		{
    			DEX_GetObjContainer (m_plObjNrVO[i], lCO);	// Container des Textfeldes

    		Point PLO = BSKoordinaten (lCO[0], lCO[3]);
    		Point PRU = BSKoordinaten (lCO[1], lCO[2]);

    			m_pPolyPoly[k]   = Point (PLO.X(), PRU.Y());
    			m_pPolyPoly[k+1] = PRU;
    			m_pPolyPoly[k+2] = Point (PRU.X(), PLO.Y());
    			m_pPolyPoly[k+3] = PLO;
    			m_pPolyPoly[k+4] = Point (PLO.X(), PRU.Y());
    			k += i5;
    			break;
    		}
    	}
    }

    return true;

} // UmrissVektor


// --------------------------------------------------------------------------------------------
// Umriß der zu verschiebenden/kopierenden Objekte zeichnen
bool CObjectMove::GiveFeedBack (Point* pPolyPoly, int* piPolyCounts, long lAnz, POINTL ptlZiel)
{
    _ASSERTE (pPolyPoly != NULL);
    _ASSERTE (piPolyCounts != NULL);

    if (!pPolyPoly || !piPolyCounts) return false;

POINT ptZiel;
HWND hWndSrc = m_pVWnd->Handle(API_WINDOW_HWND);
Rectangle CRc = m_pVWnd->CanvasRect();

    POINTFROMPOINTL (ptZiel, ptlZiel);
    ScreenToClient (hWndSrc, &ptZiel);	// Bildschirmkoordinaten in Fensterkoordinaten konvertieren

#if _TRiAS_VER < 0x0300
    // Die nachfolgende Subtraktion von 1 ist Kosmetik, um mit Hartmuts Koordinatenanzeige
    // konform zu gehen !!!!!!!!!!!!
    ptZiel.y = CRc.Top() - CRc.Bottom() - 1 - ptZiel.y;	// y-Koordinate drehen
#else			// ist das an dieser Stelle auch richtig ?????
    ptZiel.y = CRc.Top() - CRc.Bottom() - ptZiel.y;		// y-Koordinate drehen
#endif // _TRiAS_VER < 0x0300

CoOrd XDiff = m_StartPt.X() - ptZiel.x;		// Verschiebung in x- und
CoOrd YDiff = m_StartPt.Y() - ptZiel.y;		//  y-Richtung

// alle Point's des Vektors pPolyPoly nach pPoPoly verschieben
long lPtAnz = 0;	// Länge des pPoPoly-Vektors

    for (int i = 0; i < lAnz; i++)
    	lPtAnz += piPolyCounts[i];

Point* pPoPoly = new Point[lPtAnz];

    if (! pPoPoly)
    {
    	DEX_Error (RC_ObjectMove, EC_NOMEMORY);
    	return false;
    }

    for (long j = 0; j < lPtAnz; j++)
    {
    	pPoPoly[j].X() = pPolyPoly[j].X() - XDiff;
    	pPoPoly[j].Y() = pPolyPoly[j].Y() - YDiff;
    }

Pen P (SolidLine, 1, Color(BLACK));
CPolyPolygonObject* pCPPO = new CPolyPolygonObject (Point(0,0), pPoPoly, piPolyCounts, lAnz, &P);

    if (! pCPPO)
    {
    	DEX_Error (RC_ObjectMove, EC_NOMEMORY);
	 	DELETE_VEC (pPoPoly);
    	return false;
    }

    pCPPO->ChangeRop (ROP_Invert);	// das von pCPPO überzeichnete Gebiet wird invertiert
    m_pVWnd->Draw (pCPPO);			// alle Polygonobjekte zeichnen

	DELETE_VEC (pPoPoly);
	DELETE_OBJ (pCPPO);

    return true;
} // GiveFeedBack


// --------------------------------------------------------------------------------------------
// verschobene Objekte neu erzeugen;
// wenn bCopy == true, werden die Objekte kopiert, bei bCopy == false nur verschoben
bool CObjectMove::BuildMovedObjects (POINT ptZiel, bool bCopy)
{
bool bRet = true;
EPunkt StartPkt = DBKoordinaten (m_StartPt);			// Startpunkt und
EPunkt ZielPkt = DBKoordinaten ((Point&)ptZiel, true);	//  Zielpunkt in DB-Koordinaten konvertieren
KoOrd XDiff = StartPkt.X() - ZielPkt.X();				// Verschiebung in x- und
KoOrd YDiff = StartPkt.Y() - ZielPkt.Y();				//  y-Richtung

bool bText = false;		// unter den zu verschiebenden Objekten ist kein Textobjekt
long lSPAnz;			// Parameter des/der Originalobjekte(s)
KoOrd* plXK; KoOrd* plYK;
short iFlags;
string sUIText0, sUIText1;	// UniqueIdent's

	DELETE_VEC (m_plNeuObjNr);
    m_plNeuObjNr = new long[m_iAnzVO];		// Objektnummern der neuen Objekte
    if (! m_plNeuObjNr)
    {
    	DEX_Error (RC_ObjectMove, EC_NOMEMORY);
    	return false;
    }

WObjektGeometrie wObj;

    for (int i = 0; i < m_iAnzVO; i++)	// alle verschobenen Objekte abarbeiten
    {
    	if (OT_TEXT == DEX_GetObjectType (m_plObjNrVO[i]) ||	// Textobjekte bzw.
    		OT_LABEL == DEX_GetObjectType (m_plObjNrVO[i]))		// indirekte Textobjekte
    	{														// separat behandeln
    		bText = true;	// unter den zu verschiebenden Objekten ist mindestens ein Textobjekt
    		MoveTextObject (bCopy, m_plObjNrVO[i], XDiff, YDiff, m_plNeuObjNr[i]);
    		continue;
    	}

    	if (FAILED(CreateInterfaceOG (wObj.ppi(), m_plObjNrVO[i])))
    	{
			_ASSERTE(false);
    		bRet = false;
    		break;
    	}

    	wObj->GetCnt (&lSPAnz);
    	wObj->GetX ((void**)&plXK);
    	wObj->GetY ((void**)&plYK);

    	for (long j = 0; j < lSPAnz; j++)
    	{
    		plXK[j] -= XDiff;	// Koordinaten verschieben
    		plYK[j] -= YDiff;
    	}

    	wObj->SetX ((void*)plXK);
    	wObj->SetY ((void*)plYK);

    	wObj->GetFlags (&iFlags);
    	iFlags |= OGNewObject;		// permanentes Objekt in Datenbank aufnehmen
    	iFlags |= OGForceGeometry;	// auch außerhalb des aktuellen Projekt-Containers speichern
    	iFlags |= OGGeometryIsChecked;	// GeoRein.ext nicht anwerfen
    	wObj->SetFlags (iFlags);

#if _TRiAS_VER < 0x0300
    HRESULT hr = wObj->GeometrieAnTRiAS (true, NULL);
#else
	ulong ulIdent = (ulong)-1;

		wObj->GetIdent (&ulIdent);

		_ASSERTE (0 != ulIdent);
		_ASSERTE ((ulong)-1 != ulIdent);

	INT_PTR hPr = reinterpret_cast<INT_PTR>(DEX_GetObjectsProject (ulIdent));
    HRESULT hr = wObj->GeometrieAnTRiASEx (hPr, true, NULL);
#endif // _TRiAS_VER < 0x0300

    	wObj->GetONr (&m_plNeuObjNr[i]);	// neue Objektnummer

    	if (hr != S_OK)
    	{
			_ASSERTE(false);
    		bRet = false;		// kann Objekt nicht erzeugen
    		break;
    	}

    	_ASSERTE (m_plNeuObjNr[i] != 0);
    	_ASSERTE (m_plNeuObjNr[i] != -1);
    
    	// UniqueIdent erweitern mit "EDIT_ ..."
    	sUIText1 = "";
    	if (bCopy)
    	{
		ResString resText (ResID (IDS_UIFORMAT, pRF), 20);

    		sUIText1 = sMTrenn;
    		Format (sUIText0, (char*)resText.Addr(), m_plNeuObjNr[i]);
    		sUIText1 += sUIText0;
    	}

    	MerkmaleKopieren (m_plObjNrVO[i], m_plNeuObjNr[i], sUIText1, true, (MPObjectFeature | MPSystemFeatures));

    	// verschobene Objekte wieder in Recherchefenster aufnehmen und selektieren
    	if (! bCopy)
    		AddToORWindow (m_plObjNrVO[i], m_plNeuObjNr[i]);

    } // for i

// hier eventulle Textabhängigkeiten wieder herstellen
    RestoreTextDependence (bCopy);

    if (!bText)				// ohne Textobjekte
    {
    Rectangle Rec;					// rechteckiger Bereich für Zeichnen der neuen Objekte

    	MultiRectangle (m_plNeuObjNr, i, Rec);
    	DEX_RePaintRectWait (Rec);	// neue Objekte zeichnen
    }
    else							// mit mindestens einem Textobjekt
    	DEX_RePaintWait();			// gesamte Sicht neu zeichnen, da vor dem ersten Zeichnen
    								// eines Textes dessen Größe nicht bestimmbar ist
    m_pVWnd->Update();		// sofort zeichnen

    return bRet;

} // BuildMovedObjects


// -----------------------------------------------------------------------------------------------
// rechteckigen Bereich in BS-Koordinaten bestimmen, der durch die Objekte, deren Objektnummern
// in plObjNr sind, aufgespannt wird
bool CObjectMove::MultiRectangle (long* plObjNr, long lObjAnz, Rectangle& Rec)
{
KoOrd lCO[4];	// Containerkoordinaten eines Textobjektes
    			// lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax
KoOrd lBXmin = MAXKOORD;	// Koordinaten des Bereiches
KoOrd lBXmax = -1;
KoOrd lBYmin = MAXKOORD;
KoOrd lBYmax = -1;	
int iPixX, iPixY;	// Größe eines Punktsymbols in BS-Pixel
int iMaxPixX = 0;	// größte Breite bzw.
int iMaxPixY = 0;	//  Höhe eines Punktsymbols


    for (long i = 0; i < lObjAnz; i++)	// alle plObjNr-Objekte abarbeiten
    {
    	DEX_GetObjContainer (plObjNr[i], lCO);
    	if (lCO[0] < lBXmin) lBXmin = lCO[0];
    	if (lCO[1] > lBXmax) lBXmax = lCO[1];
    	if (lCO[2] < lBYmin) lBYmin = lCO[2];
    	if (lCO[3] > lBYmax) lBYmax = lCO[3];

    	if (OT_PUNKT == DEX_GetObjectType (plObjNr[i]))
    	{
    		PointSymbolSize (DEX_GetObjIdentEx (plObjNr[i]), iPixX, iPixY);
    		if (iPixX > iMaxPixX) iMaxPixX = iPixX;
    		if (iPixY > iMaxPixY) iMaxPixY = iPixY;
    	}
    }

Point PLO, PRU;		// Eckpunkte des rechteckigen Bereiches

    PLO = BSKoordinaten (lBXmin, lBYmax);
    PRU = BSKoordinaten (lBXmax, lBYmin);

    Rec.Left() = PLO.X() - iMaxPixX - iZeiZug;	// Zugabe iZeiZug ist in geokonst.hxx definiert
    if (Rec.Left() < 0) Rec.Left() = 0;
    Rec.Top() = PLO.Y() + iMaxPixY + iZeiZug;
    Rec.Right() = PRU.X() + iMaxPixX + iZeiZug;
    Rec.Bottom() = PRU.Y() - iMaxPixY - iZeiZug;
    if (Rec.Bottom() < 0) Rec.Bottom() = 0;

    return true;

} // MultiRectangle


// --------------------------------------------------------------------------------------------
// Verschieben/Kopieren des lAltObjNr-Textobjektes um die Koordinatendifferenz (XDiff, YDiff)
bool CObjectMove::MoveTextObject (bool bCopy, long lAltObjNr, KoOrd XDiff, KoOrd YDiff,
    							  long& lNeuObjNr)
{
// statistische Angaben des lAltObjNr-Textobjektes von TRiAS holen
// da Struktur TEXTGEOMETRIE am Anfang wie Struktur OBJSTATISTIK aufgebaut ist, können die
// statistischen Angaben gleich in die Struktur TEXTGEOMETRIE eingetragen werden, wodurch das
// Umkopieren entfällt 
TEXTGEOMETRIE TG;

    INITSTRUCT (TG, TEXTGEOMETRIE);
    TG.dwSize = sizeof (OBJSTATISTIK);	// nur für DEX_GetObjStatistik()
    TG.lONr = lAltObjNr;
    if (! DEX_GetObjStatistik (TG))
    	return false;

    TG.dwSize = sizeof (TEXTGEOMETRIE);

    _ASSERTE ((TG.iFlags & OGConverted) == 0x0);	// Koordinaten im KoOrd-Format

    TG.pdblX = new KoOrd[TG.lCnt];
    if (TG.pdblX == NULL) return false;
    TG.pdblY = new KoOrd[TG.lCnt];
    if (TG.pdblY == NULL) return false;
    TG.pText = new char[TG.iKCnt+1];	// "+1" für "\0"
    if (TG.pText == NULL) return false;

    if (! DEX_GetObjGeometrie (TG))		// weitere Angaben des Textobjektes von TRiAS holen
    {
	 	DELETE_VEC (TG.pdblX);
	 	DELETE_VEC (TG.pdblY);
	 	DELETE_VEC (TG.pText);
    	return false;
    }

    ((KoOrd*)TG.pdblX)[0] -= XDiff;		// Koordinaten verschieben
    ((KoOrd*)TG.pdblY)[0] -= YDiff;

    TG.iFlags |= OGNewObject;			// Geometrie des Objektes nicht ersetzen sondern neu in
    									// DB ablegen
    TG.iFlags |= OGForceGeometry;		// kein Test, ob neues Objekt innerhalb des
    									// Projekt-Containers liegt
    TG.iFlags |= OGGeometryIsChecked;	// GeoRein.ext nicht anwerfen

// Undo-Mechanismus für Textobjekte
LPUNDOREDOCREATETEXT pIUndo = NULL;

// Undo-Objekt erzeugen (über OLE)
HRESULT hr = CoCreateInstance (CLSID_UndoRedoObject, NULL, CLSCTX_INPROC_SERVER,
    						   IID_IUndoRedoCreateText, (LPVOID*) &pIUndo);	
    
bool bResult = DEX_ModObjGeometrie (TG);

	DELETE_VEC (TG.pdblX);
	DELETE_VEC (TG.pdblY);
	DELETE_VEC (TG.pText);

    lNeuObjNr = TG.lONr;	// Objektnummer des neuen Objektes

// es gibt (allgemein) 3 Fälle:
// bResult == true, lNeuObjNr != 0, lNeuObjNr != -1:  fehlerfreies Objekt, wurde gespeichert
// bResult == false, lNeuObjNr != 0, lNeuObjNr != -1: fehlerhaftes Objekt, wurde trotzdem gespeichert
// bResult == false, lNeuObjNr == 0:				  fehlerhaftes Objekt, wurde nicht gespeichert
// Hier kann aber eigentlich nur der 1. Fall auftreten.

    _ASSERTE (bResult == true);
    _ASSERTE (lNeuObjNr != 0);
    _ASSERTE (lNeuObjNr != -1);

    if (0 != lNeuObjNr && -1 != lNeuObjNr && SUCCEEDED(hr))		// Initialisierung eines Undo-Objektes
    	hr = pIUndo->Init (lNeuObjNr);

    if (0 != lNeuObjNr && -1 != lNeuObjNr && NOERROR == hr)
    	DEX_AddUndoRedo (pIUndo);	// Undo-Objekt an TRiAS

    if (pIUndo)
    {
    	pIUndo->Release();		// Undo-Objekt wieder freigeben
    	pIUndo = NULL;
    }
// Ende des Undo-Mechanismus

    if (! bCopy)	// verschobene Objekte wieder in Recherchefenster aufnehmen und selektieren
    	AddToORWindow (lAltObjNr, lNeuObjNr);

    return bResult;

} // MoveTextObject


// --------------------------------------------------------------------------------------------
// eventuelle Textabhängigkeiten nach dem Verschieben wieder erzeugen
bool CObjectMove::RestoreTextDependence (bool bCopy)
{
long lBONr = 0L;		// Objektnummer des abhängigen Objektes
ENUMRELATIONOBJS EREL;	// Struktur für Test auf Abhängigkeit

    INITSTRUCT (EREL, ENUMRELATIONOBJS);
    EREL.lRCode = -1;	// zu untersuchende Relation (-1: alle)

MODRELATION MREL;		// Struktur für Veränderung von Abhängigkeiten

    INITSTRUCT (MREL, MODRELATION);
    MREL.iRTyp = RTBegleitO;		// RelationsTyp "Begleitrelation"
    // durch INITSTRUCT() wird MREL.lRCode = 0 gesetzt, was auch ausreicht, da es bei
    // Begleitrelationen nur EINE Verbindung geben kann (im Gegensatz zur Komplexrelation, wo
    // MEHRERE Verbindungen bestehen können)

DELRELATION DREL;		// Struktur zum Lösen von Abhängigkeiten

    INITSTRUCT (DREL, DELRELATION);	// hierbei wird DREL.lRCode = 0 gesetzt (siehe MREL)
    DREL.iRTyp = RTBegleitO;	// RelationsTyp "Begleitrelation"

    // alle verschobenen Geometrie/Textobjekte prüfen, ob eine Abhängigkeit zu einem
    // Text/Geometrieobjekt besteht
    for (int i = 0; i < m_iAnzVO; i++)
    {
    	lBONr = 0L;

    	EREL.lONr = m_plObjNrVO[i];	// Bezugsobjekt, für das Relationen geliefert werden

    // der zu untersuchende RelationsTyp ist "BegleitRelation", d.h. es wird getestet, ob es zu
    // einem Geometrieobjekt ein abhängiges Textobjekt gibt bzw. ob ein gegebenes Textobjekt
    // von einem Geometrieobjekt abhängig ist
    int iOT = DEX_GetObjectType (m_plObjNrVO[i]);

    	_ASSERTE (iOT == OT_PUNKT || iOT == OT_KANTE || iOT == OT_FLAECHE || iOT == OT_TEXT ||
    			   iOT == OT_LABEL);

    	if (OT_PUNKT != iOT && OT_KANTE != iOT && OT_FLAECHE != iOT && OT_TEXT != iOT &&
    		OT_LABEL != iOT)
    		continue;

    	if (OT_TEXT == iOT || OT_LABEL == iOT)
    		EREL.iRTyp = RTBegleitU;	// in EREL.lONr ist die Objektnummer eines Textobjektes
    									// eingetragen, d.h. es ist möglicherweise ein
    									// Begleitobjekt
    	else
    		EREL.iRTyp = RTBegleitO;	// in EREL.lONr ist die Objektnummer eines
    									// Geometrieobjektes eingetragen, d.h. es wird gefragt,
    									// ob es ein Begleitobjekt hat

    	EREL.eFcn = (ENUMRELOBJPROC) AttachedObject;
    	EREL.pData = &lBONr;
    	DEX_EnumRelationObjects (EREL);

    	if (0 != lBONr && -1 != lBONr)	// zugeordnetes Objekt gefunden
    	{
    		// testen, ob das zugeordnete Objekt auch verschoben wurde
    		for (int j = 0; j < m_iAnzVO; j++)
    			if (m_plObjNrVO[j] == lBONr) break;

    		if (j < m_iAnzVO)	// das zugeordnete Objekt wurde auch verschoben
    		{
    		// diese Abhängigkeit nun auch zwischen den neuen Objekten m_plNeuObjNr[i] und
    		// m_plNeuObjNr[j] herstellen
    		int iOT1 = DEX_GetObjectType (m_plNeuObjNr[i]);

    			// wenn sowohl ein Geometrieobjekt und das dazugehörige abhängige Textobjekt
    			// verschoben wurden, dann wird die Zuordnung nur dann hergestellt, wenn das
    			// 1. Objekt das Geometrieobjekt ist
    			if (OT_TEXT == iOT1 || OT_LABEL == iOT1) continue;

    		int iOT2 = DEX_GetObjectType (m_plNeuObjNr[j]);

    			_ASSERTE (iOT1 == OT_PUNKT || iOT1 == OT_KANTE || iOT1 == OT_FLAECHE ||
    					   iOT1 == OT_TEXT || iOT1 == OT_LABEL);

    			if (OT_PUNKT != iOT1 && OT_KANTE != iOT1 && OT_FLAECHE != iOT1 &&
    				OT_TEXT != iOT1 && OT_LABEL != iOT1)
    				continue;

    			if (iOT1 == OT_PUNKT || iOT1 == OT_KANTE || iOT1 == OT_FLAECHE)
    			{
    				_ASSERTE (iOT2 == OT_TEXT || iOT2 == OT_LABEL);

    				if (OT_TEXT != iOT2 || OT_LABEL != iOT2) continue;
    			}
    			else	// iOT1 == OT_TEXT oder iOT1 == OT_LABEL
    			{
    				_ASSERTE (iOT2 == OT_PUNKT || iOT2 == OT_KANTE || iOT2 == OT_FLAECHE);

    				if (iOT2 != OT_PUNKT && iOT2 != OT_KANTE && iOT2 != OT_FLAECHE) continue;
    			}

    			if (OT_TEXT == iOT2 || OT_LABEL == iOT2)
    			{
    				MREL.lPONr = m_plNeuObjNr[i];	// PrimärObjekt, d.h. Geometrieobjekt
    				MREL.lSONr = m_plNeuObjNr[j];	// SekundärObjekt, d.h. Textobjekt
    				DEX_ModifyRelation (MREL);		// ohne Funktion MREL.eFcn
    			}
    		}

    		// es gibt ein zugeordnetes Objekt, das sich jedoch nicht unter den verschobenen
    		// befindet; falls die Objekte verschoben (also nicht kopiert) wurden
    		// (bCopy == false), dann diese Zurordnungen auch neu aufbauen
    		else if (!bCopy)
    		{
    		int iOT0 = DEX_GetObjectType (lBONr);

    			// zuerst die Verbindung zu dem nicht verschobenen Objekt lösen
    			if (OT_TEXT == iOT || OT_LABEL == iOT)
    			{
    				_ASSERTE (iOT0 == OT_PUNKT || iOT0 == OT_KANTE || iOT0 == OT_FLAECHE);

    				if (iOT0 != OT_PUNKT && iOT0 != OT_KANTE && iOT0 != OT_FLAECHE) continue;

    				DREL.lPONr = lBONr;				// PrimärObjekt, d.h. Geometrieobjekt
    				DREL.lSONr = m_plObjNrVO[i];	// SekundärObjekt, d.h. Textobjekt
    				DEX_DeleteRelation (DREL);		// ohne Funktion DREL.eFcn

    				MREL.lPONr = lBONr;				// Geometrieobjekt für neue Zuordnung
    				MREL.lSONr = m_plNeuObjNr[i];	// Textobjekt
    			}
    			else
    			{
    				_ASSERTE (iOT0 == OT_TEXT || iOT0 == OT_LABEL);

    				if (OT_TEXT != iOT0 && OT_LABEL != iOT0) continue;

    				DREL.lPONr = m_plObjNrVO[i];	// Geometrieobjekt
    				DREL.lSONr = lBONr;				// Textobjekt
    				DEX_DeleteRelation (DREL);

    				MREL.lPONr = m_plNeuObjNr[i];	// Geometrieobjekt für neue Zuordnung
    				MREL.lSONr = lBONr;				// Textobjekt
    			}

    			DEX_ModifyRelation (MREL);
    		}
    	}
    }

    return true;

} // RestoreTextDependence


// --------------------------------------------------------------------------------------------
// das verschobene lNeuObjNr-Objekt in das/die gleiche/n Recherchefenster eintragen, in
// dem/denen das lAltObjNr-Originalobjekt stand
bool CObjectMove::AddToORWindow (long lAltObjNr, long lNeuObjNr)
{
struct MoveONr Dat;	// in EditKonst.h definiert

    Dat.lAltObjNr = lAltObjNr;	// Objektnummer des Originalobjektes
    Dat.lNeuObjNr = lNeuObjNr;	// Objektnummer des verschobenen Objektes

ENUMNOKEYLONG ENKL;

    memset (&ENKL, '\0', sizeof (ENUMNOKEYLONG));
    ENKL.eFcn = (ENUMNOKEYLONGPROC) InWelchesFenster;	// durch die Enumeration zu rufende
    													// Funktion
    ENKL.ePtr = (void*) &Dat;		// an die gerufene Funktion durchgereichte Daten
    DEX_EnumORWindows (ENKL);

    return true;

} // AddToORWindow



///////////////////////////////////////////////////////////////////////////////////////////////
// IDropTarget-Methoden
// Routine zeigt an, daß die Maus in ein Fenster eintritt
STDMETHODIMP CObjectMove::DragEnter (DRAGDROPTYPE rgType, HWND hWnd, IDataObject* pIDataSource,
    								 DWORD grfKeyState, POINTL ptl, DWORD* pdwEffect)
{
// Testen, über welchem Fenster sich die Maus befindet (rgType wird bei BeginDragDrop()
// gesetzt)
    if (DRAGDROPTYPE_VIEWWINDOW != rgType)
    	return S_FALSE;		// Maus nicht in ein TRiAS-Fenster sondern z.B. in ein
    						//  Recherchefenster eingetreten

// Testen, ob pIDataSource EnumLONG mit Objektnummern enthält
    if (NOERROR != GetEnumLONGData (pIDataSource))
    	return S_FALSE;		// keine verständlichen Daten

// Testen, woher das Objekt stammt
    if (IsDropSource())		// Objekte aus der eigenen TRiAS-Datenbank
    {
    	*pdwEffect |= DROPEFFECT_MOVE;		// verschieben
    	if (grfKeyState & MK_CONTROL)
    		*pdwEffect |= DROPEFFECT_COPY;	// kopieren
    }
    else	// Maus in das TRiAS-Fenster eines anderen Projektes eingetreten
    	return S_FALSE;

// Objektnummern der verschobenen Objekte in m_plObjNrVO bereitstellen 
HRESULT hr = GetObjNummern (pIDataSource);

    if (FAILED(hr))
    	return hr;

// Koordinaten-Vektoren in BS-Koordinaten für Zeichnen der Objektumrisse aufbauen
    UmrissVektor();

// Umriß der zu verschiebenden Objekte zeichnen
    GiveFeedBack (m_pPolyPoly, m_piPolyCounts, m_iAnzVO, ptl);
    m_ptlOld = ptl;

    return NOERROR;

} // DragEnter


// --------------------------------------------------------------------------------------------
// Routine zeigt an, daß sich die Maus innerhalb des Bezugsfenster bewegt hat, der Zustand der
// Tastatur sich verändert hat bzw. ein interner OLE-Timer abgelaufen ist
STDMETHODIMP CObjectMove::DragOver (DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState,
    								POINTL ptl, DWORD* pdwEffect)
{
// Testen, über welchem Fenster sich die Maus befindet
    if (DRAGDROPTYPE_VIEWWINDOW != rgType)
    	return S_FALSE;	// Maus nicht mehr im TRiAS-Fenster sondern z.B. über Recherchefenster

// wenn die Daten nicht für mich sind, dann zurück
    if (NULL == m_plObjNrVO)
    	return S_FALSE;

    // noch einmal testen, woher das Objekt stammt
    if (IsDropSource())	// Objekte aus der eigenen TRiAS-Datenbank
    {
    	*pdwEffect |= DROPEFFECT_MOVE;		// verschieben
    	if (grfKeyState & MK_CONTROL)
    		*pdwEffect |= DROPEFFECT_COPY;	// kopieren
    }
    else	// Maus in das TRiAS-Fenster eines anderen Projektes eingetreten
    	return S_FALSE;

// Umriß der zu verschiebenden Objekte löschen und neu zeichnen
    if (ptl.x != m_ptlOld.x || ptl.y != m_ptlOld.y)
    {
    	GiveFeedBack (m_pPolyPoly, m_piPolyCounts, m_iAnzVO, m_ptlOld);
    	GiveFeedBack (m_pPolyPoly, m_piPolyCounts, m_iAnzVO, ptl);
    	m_ptlOld = ptl;
    }

    return NOERROR;

} // DragOver


// --------------------------------------------------------------------------------------------
// Routine zeigt an, daß sich die Maus aus dem Bezugsfenster heraus bewegt hat
STDMETHODIMP CObjectMove::DragLeave (DRAGDROPTYPE rgType, HWND hWnd)
{
// Testen, über welchem Fenster sich die Maus befindet
    if (DRAGDROPTYPE_VIEWWINDOW != rgType)
    	return S_FALSE;

// wenn die Daten nicht für mich sind, dann zurück
    if (NULL == m_plObjNrVO) 
    	return S_FALSE;

// Umriß der zu verschiebenden Objekte löschen
    GiveFeedBack (m_pPolyPoly, m_piPolyCounts, m_iAnzVO, m_ptlOld);

    return NOERROR;
} // DragLeave


// --------------------------------------------------------------------------------------------
// Routine zeigt an, daß die Quelle "Drop" signalisiert hat
STDMETHODIMP CObjectMove::Drop (DRAGDROPTYPE rgType, HWND hWnd, IDataObject* pIDataSource,
    							DWORD grfKeyState, POINTL ptl, DWORD* pdwEffect)
{
// Testen, über welchem Fenster sich die Maus befindet
    if (DRAGDROPTYPE_VIEWWINDOW != rgType)
    	return S_FALSE;

// wenn die Daten nicht für mich sind, dann zurück
    if (NULL == m_plObjNrVO) 
    	return S_FALSE;

    if (!IsDropSource())	// Objekte aus fremden Quellen
    	return S_FALSE;

// Umriß der zu verschiebenden Objekte löschen
    GiveFeedBack (m_pPolyPoly, m_piPolyCounts, m_iAnzVO, m_ptlOld);

// neue Objekte erzeugen
HRESULT hr = E_FAIL;	// für den Fall, daß Erzeugung nicht gelingt
POINT pt;
HWND hWndSrc = m_pVWnd->Handle(API_WINDOW_HWND);

    POINTFROMPOINTL (pt, ptl);
    ScreenToClient (hWndSrc, &pt);	// Bildschirmkoordinaten in Fensterkoordinaten konvertieren

bool bCopy = false;	// Objekte werden kopiert/verschoben (true/false)

    if (grfKeyState & MK_CONTROL)
    	bCopy = true;

    if (BuildMovedObjects (pt, bCopy)) // neue Objekte erfolgreich erzeugt
    {
    	*pdwEffect |= DROPEFFECT_MOVE;		// verschieben
    	if (grfKeyState & MK_CONTROL)
    		*pdwEffect |= DROPEFFECT_COPY;	// kopieren

    	hr = NOERROR;
    }
    	
	DELETE_VEC (m_plObjNrVO);		// Daten werden nicht mehr benötigt
    return hr;	

} // Drop



///////////////////////////////////////////////////////////////////////////////////////////////
// Funktionen für EnumLONG
// Hinzufügen eines EnumLONG zu einem IDataObject
HRESULT CObjectMove::SetEnumLONGData (IEnum<LONG>* pEnum, IDataObject* pDataObj)
{
// Stream mit EnumLONG generieren
WStream wStream;
HRESULT hr = CreateStreamOnHGlobalFromIUnknown (pEnum, wStream.ppi());

    if (FAILED(hr)) return hr;

// diesen Stream im DataObject setzen
STGMEDIUM stg;

    stg.tymed = TYMED_ISTREAM;
    stg.pstm = wStream.detach();
    stg.pUnkForRelease = NULL;

    hr = pDataObj->SetData ((FORMATETC*)&c_feSelectedObjects, &stg, true);
    if (FAILED(hr)) return hr;

    return NOERROR;

} // SetEnumLONGData


// -----------------------------------------------------------------------------------------------
// Serialisieren/DeSerialisieren eines IUnknowns
HRESULT CObjectMove::CreateStreamOnHGlobalFromIUnknown (IUnknown* pIUnk, IStream** ppIStream)
{
    if (NULL == ppIStream) return E_POINTER;

    *ppIStream = NULL;

    COM_TRY {
    // neuen Stream anlegen
    WStream wStream;

    	THROW_FAILED_HRESULT (CreateStreamOnHGlobal (NULL, true, wStream.ppi()));

    WPersistStream IPersStr = pIUnk;	// throws_com_error
    WStream StrClone;

    // den Enumerator wegschreiben
    	THROW_FAILED_HRESULT(wStream->Clone(StrClone.ppi()));
    	THROW_FAILED_HRESULT(OleSaveToStream (IPersStr, StrClone));

    LARGE_INTEGER li;

    	LISet32(li, 0L);
    	THROW_FAILED_HRESULT(wStream->Seek (li, SEEK_SET, NULL));

    	*ppIStream = wStream.detach();		// Resultat

    } COM_CATCH;

    return S_OK;
} // CreateStreamOnHGlobalFromIUnknown


// --------------------------------------------------------------------------------------------
// Lesen eines EnumLONG aus einem DataObjekt
HRESULT CObjectMove::GetEnumLONGData (IDataObject* pIDataObj, IEnum<LONG>** ppIEnumOut)
{
    if (NULL == pIDataObj) return E_POINTER;

HRESULT hr = E_FAIL;
STGMEDIUM stg;

    memset (&stg, 0, sizeof(STGMEDIUM));
    try {
    // Testen, ob das gewünschte Format überhaupt da ist
    	hr = pIDataObj->QueryGetData ((FORMATETC*)&c_feSelectedObjects);
    	if (NOERROR != hr) _com_issue_error (hr);	// Format nicht vorhanden

    	if (NULL == ppIEnumOut)	
    		return NOERROR;		// nur abfragen, ob Format vorhanden ist

    // Daten vom DataObject geben lassen
//		hr = pIDataObj->GetData ((FORMATETC*)&c_feSelectedObjects, &stg);	(23.03.98)
//		if (FAILED(hr)) _com_issue_error (hr);
    	THROW_FAILED_HRESULT (pIDataObj->GetData ((FORMATETC*)&c_feSelectedObjects, &stg));

    // einlesen des Enumerators aus den erhaltenen STGMEDIUM
//		hr = CreateEnumLONGFromStream (stg.pstm, ppIEnumOut);				(23.03.98)
//		if (FAILED(hr)) _com_issue_error (hr);
    	THROW_FAILED_HRESULT (CreateEnumLONGFromStream (stg.pstm, ppIEnumOut));

    	ReleaseStgMedium (&stg);
    }
    catch (_com_error& e) {
    	if (TYMED_NULL != stg.tymed)
    		ReleaseStgMedium (&stg);
    	return _COM_ERROR (e);
    }	

    return NOERROR;

} // GetEnumLONGData


// ------------------------------------------------------------------------------------------------
// die folgende Funktion ist das konkrete Äquivalent für 'OleLoadFromStream'
HRESULT CObjectMove::CreateEnumLONGFromStream (IStream* pIStream, IEnum<LONG>** ppEnumOut)
{
    if (NULL == ppEnumOut) 
		return E_POINTER;
    *ppEnumOut = NULL;

    COM_TRY {
    WStream StrClone;

    	THROW_FAILED_HRESULT (pIStream->Clone (StrClone.ppi()));
    	THROW_FAILED_HRESULT (OleLoadFromStream (StrClone, IID_IEnumLONG, (LPVOID*)ppEnumOut));

    } COM_CATCH;
    return S_OK;

} // CreateEnumLONGFromStream



///////////////////////////////////////////////////////////////////////////////////////////////
// Initialisierung des ProgressIndicators2
HRESULT CObjectMove::InitProgressIndicator (IProgressIndicator2* pPI, ResID uiTitel,
    										ResID uiAdjust, ulong ulMaxPos, ulong ulMinPos)
{
    _ASSERTE (pPI != NULL);

// Parent setzen
HWND hWnd = NULL;
HRESULT hr = pPI->InitNew ((INT_PTR)g_pTE->MWind()->Handle(), 0L, (LONG *)&hWnd);

    if (FAILED(hr)) return hr; 

// min, max setzen
PIFLAGS rgFlags = (PIFLAGS)(PIFLAGS_STATUS |			// Anzeige der Statuszeile, 
    						PIFLAGS_TIME |				//  der verbleibenden Zeit,
    						PIFLAGS_ADJUSTPERCENT |		//  des Prozentwertes und
#if _TRiAS_VER < 0x0300
    						PIFLAGS_RESULT |			//	der Objektnummer
#endif // _TRiAS_VER < 0x0300
    						PIFLAGS_INIT_SHOWWINDOW);	// erst dann Anzeige, wenn etwas zu
														//  sehen ist
    hr = pPI->Restart (ulMinPos, ulMaxPos, rgFlags);
    if (FAILED(hr)) return hr;

// Caption setzen
ResString resTitel (uiTitel, 100);
CComBSTR bstrTitel (resTitel.Addr());	// char* in Bi-String konvertieren

    hr = pPI->ChangeText (PIFLAGS_CAPTION, bstrTitel);
    if (FAILED(hr)) return hr;
    		
// Adjust-Text setzen
ResString resAdjust (uiAdjust, 100);
CComBSTR bstrAdjust (resAdjust.Addr());

    hr = pPI->ChangeText (PIFLAGS_ADJUSTPERCENT, bstrAdjust);
    if (FAILED(hr)) return hr;

    return S_OK;

} // InitProgressIndicator


// --------------------------------------------------------------------------------------------
// Registrierung des ProgressIndicators2
HRESULT CObjectMove::RegisterPI (IProgressIndicator2* pPI)
{
    COM_TRY {
    	_ASSERTE (m_dwCookiePI == 0);
    	
	WConnectionPointContainer CPC (GetUnknown());		// throws_com_error
    WConnectionPoint CP;

    	THROW_FAILED_HRESULT (CPC->FindConnectionPoint(IID_IProgressIndicator2, CP.ppi()));
    	THROW_FAILED_HRESULT (CP->Advise(pPI, &m_dwCookiePI));

    } COM_CATCH;
    return S_OK;

} // RegisterPI


// --------------------------------------------------------------------------------------------
// Abmeldung des ProgressIndicators2
HRESULT CObjectMove::UnRegisterPI (void)
{
    if (0 == m_dwCookiePI) return S_FALSE;	// es wurde kein Advise() ausgeführt 

    COM_TRY {
	WConnectionPointContainer CPC (GetUnknown());		// throws_com_error
    WConnectionPoint CP;

    	THROW_FAILED_HRESULT (CPC->FindConnectionPoint(IID_IProgressIndicator2, CP.ppi()));
    	THROW_FAILED_HRESULT (CP->Unadvise(m_dwCookiePI));
    	m_dwCookiePI = 0L;

    } COM_CATCH;
    return S_OK;

} // UnRegisterPI




///////////////////////////////////////////////////////////////////////////////////////////////
// DropSourceObject
CEditDropSource::CEditDropSource (void)
{
    m_dwRefCnt = 0L;
    m_pObjMove = NULL;
    m_dwFlags = 0L;
}


// --------------------------------------------------------------------------------------------
CEditDropSource::~CEditDropSource (void)
{
}


// --------------------------------------------------------------------------------------------
CEditDropSource* CEditDropSource::CreateInstance (CObjectMove* pObjMove)
{
CEditDropSource* pEDSource = new CEditDropSource();

    if (NULL == pEDSource || !pEDSource->FInit(pObjMove))
    {
	 	DELETE_OBJ (pEDSource);
    	return NULL;
    }

    return pEDSource;
} // CreateInstance


// --------------------------------------------------------------------------------------------
bool CEditDropSource::FInit (CObjectMove* pObjMove, DWORD dwFlags)
{
    m_pObjMove = pObjMove;
    m_dwFlags = dwFlags;
    return true;
} // FInit


// --------------------------------------------------------------------------------------------
// IUnknown-Interfaces
STDMETHODIMP_ (ULONG) CEditDropSource::AddRef (void)
{
    return ++m_dwRefCnt;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_ (ULONG) CEditDropSource::Release (void)
{
    if (0 == --m_dwRefCnt)
    {
    	delete this;
    	return 0;
    }
    return m_dwRefCnt;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CEditDropSource::QueryInterface (REFIID riid, LPVOID* ppvObj)
{
    if (IID_IDropSource == riid || IID_IUnknown == riid)
    {
    	*ppvObj = this;
    	((IUnknown*)(*ppvObj))->AddRef();
    	return NOERROR;
    }

    return E_NOINTERFACE;

} // QueryInterface


// --------------------------------------------------------------------------------------------
// IDropSource-Methoden
STDMETHODIMP CEditDropSource::QueryContinueDrag (BOOL bEsc, DWORD grfKeyState)
{
    _ASSERTE (m_dwFlags != 0);

    if (bEsc)	// Drag-Drop-Operation wurde mit Esc abgebrochen
    	return DRAGDROP_S_CANCEL;

    if (!(grfKeyState & m_dwFlags))
    {
    	_ASSERTE (m_pObjMove != NULL);

    	if (m_pObjMove->FQueryDrop()) 
    		return DRAGDROP_S_DROP;		// "Drop" erfolgreich durchgeführt
    	else
    		return DRAGDROP_S_CANCEL;	// Drag-Drop-Operation wurde abgebrochen
    }

    return NOERROR;		// entspr. S_OK

} // QueryContinueDrag


// --------------------------------------------------------------------------------------------
// dwEffect kann sein: DROPEFFECT_NONE (0), DROPEFFECT_COPY (1) oder DROPEFFECT_MOVE (2)
STDMETHODIMP CEditDropSource::GiveFeedback (DWORD dwEffect)
{
    return DRAGDROP_S_USEDEFAULTCURSORS;
}
