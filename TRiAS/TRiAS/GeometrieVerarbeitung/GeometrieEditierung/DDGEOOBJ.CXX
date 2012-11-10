// Implementation eines Interfaces für Erweiterung "GeometrieEditierung"
// Drag and Drop Source/Target für GeometrieObjekte und Textobjekte
// File: DDGEOOBJ.CXX


#include "geoeditp.hxx"

#include <winuser.h>	// InvalidateRect()

#include <ospace/com/iterenum.h>	// IEnum<long>
#include <eonrguid.h>	// IID_IEnumLONG in DefineSmartInterface(EnumLONG)
#include <xtsnguid.h>	// IID_IDragDropAction
#include <resstrg.h>    // IDS_UIFORMAT
#include <defattr.h>	// StandardAttribute für Punkte, Linien etc. (DEF_SIZE_PUNKT_X, ...)

#include <TRiASHelper_i.c>// IID_IProgressIndicator2, CLSID_ProgressIndicator
#include "SmartInterfaces.h"
#include <initguid.h>	// zum Linken von IID_* und CLSID_* erforderlich
#include <dirisole.h>	// CLSID_DataTransferObject
#include <propactn.h>	// c_feSelectedObjects

#if defined(WIN32)		// nur für 32-Bit-Variante
#include <undoguid.h>
#include <iunredo.hxx>
#endif // WIN32

#include "geoedit.hxx"



#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// --------------------------------------------------------------------------------------------
// Die Message 'DEXOR_RemoveFromListObject' führt KEIN automatisches UndoRedo mehr aus. Dafür
// sind die folgenden Messages dazugekommen, die ihrerseits ein UndoRedo erzeugen:
// DEXOR_AddObjectToListEx, DEXOR_RemoveFromListObjectEx und DEXOR_ReplaceObjectInListEx
// Da dies erst ab der TRiAS-Version V2.10.452 möglicht ist, folgendes Hilfskonstrukt
#if !defined(DEXOR_ReplaceObjectInListEx)
#define DEXOR_ReplaceObjectInListEx(x, y)	DEXOR_ReplaceObjectInList((x),(y))
#define DEXOR_AddObjectToListEx(x, y)		DEXOR_AddObjectToList((x),(y))
#define DEXOR_RemoveFromListObjectEx(x, y)	DEXOR_RemoveFromListObject((x),(y))
#endif // DEXOR_ReplaceObjectInListEx



// ------------------------------------------------------------------------------------------------
// weitere benötigte SmartInterfaces
DefineSmartInterface(DropSource);		// durch das Makro DefineSmartInterface() wird für das
										//  Interface IDropSource die Wraper-Klasse WDropSource
										//  erzeugt
DefineSmartInterface(EnumLONG);			// WEnumLONG
DefineSmartInterface(Stream);			// WStream
DefineSmartInterface(PersistStream);	// WPersistStream



// ------------------------------------------------------------------------------------------------
// globale Konstanten
extern ResourceFile* pRF;



// ------------------------------------------------------------------------------------------------
extern "C"
{
	// Objekt lAltObjNr in Recherchefenster hWnd durch Objekt lNeuObjNr ersetzen
	BOOL _GEOEDIT_EXPORT FAR PASCAL InWelchesFenster (LONG hWnd, BOOL bNotLast, void* pData)
	{
	REPLACEOBJECT RO;

		INITSTRUCT (RO, REPLACEOBJECT);
		RO.lONr = ((MoveONr*)pData) -> lAltObjNr;
		RO.lNewONr = ((MoveONr*)pData) -> lNeuObjNr;
		DEXOR_ReplaceObjectInListEx ((HWND)hWnd, RO);
		InvalidateRect ((HWND)hWnd, NULL, TRUE);	// Recherchefenster aktualisieren durch Neuzeichnen

		return TRUE;
	}

	// Liefert Objektnummer des zugehörigen Objektes (wenn es eins gibt)
	BOOL _GEOEDIT_EXPORT FAR PASCAL AttachedObject (long lONr, long lRCode, short iRTyp,
													void* pData)
	{
		(*(long*)pData) = lONr;
		return TRUE;
	}

} // extern "C"



// ------------------------------------------------------------------------------------------------
// Funktionen für EnumLONG
// Serialisieren/DeSerialisieren eines IUnknowns
HRESULT GeoEditExtension :: CreateStreamOnHGlobalFromIUnknown (IUnknown* pIUnk, IStream** ppIStream)
{
	if (NULL == ppIStream) 
		return E_POINTER;
	*ppIStream = NULL;

// neuen Stream anlegen
WStream IStream;
HRESULT hr = CreateStreamOnHGlobal (NULL, true, IStream.ppi());
	
	if (FAILED(hr)) return hr;

	try
	{
	WPersistStream IPersStr = pIUnk;	// throws_com_error
	WStream StrClone;

	// den Enumerator wegschreiben
		THROW_FAILED_HRESULT(IStream->Clone(StrClone.ppi()));
		THROW_FAILED_HRESULT(OleSaveToStream (IPersStr, StrClone));

	LARGE_INTEGER li;

		LISet32(li, 0L);
		THROW_FAILED_HRESULT(IStream -> Seek (li, SEEK_SET, NULL));

		*ppIStream = IStream.detach();		// Resultat

	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	return NOERROR;
} // CreateStreamOnHGlobalFromIUnknown


// ------------------------------------------------------------------------------------------------
// die folgende Funktion ist das konkrete Äquivalent für 'OleLoadFromStream'
HRESULT CreateEnumLONGFromStream (IStream* pIStream, IEnum<LONG>** ppEnumOut)
{
	if (NULL == ppEnumOut) return E_POINTER;

	*ppEnumOut = NULL;

	try
	{
	WStream StrClone;

		THROW_FAILED_HRESULT(pIStream -> Clone (StrClone.ppi()));
		THROW_FAILED_HRESULT(OleLoadFromStream (StrClone, IID_IEnumLONG, (LPVOID*)ppEnumOut));
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	return S_OK;
} // CreateEnumLONGFromStream


// -----------------------------------------------------------------------------------------------
// Hinzufügen eines EnumLONG zu einem IDataObject
HRESULT GeoEditExtension :: SetEnumLONGData (IEnum<LONG>* pEnum, IDataObject* pDataObj)
{
// Stream mit EnumLONG generieren
WStream IStream;
HRESULT hr = CreateStreamOnHGlobalFromIUnknown (pEnum, IStream.ppi());

	if (FAILED(hr)) return hr;

// diesen Stream im DataObject setzen
STGMEDIUM stg;

	stg.tymed = TYMED_ISTREAM;
	stg.pstm = IStream.detach();
	stg.pUnkForRelease = NULL;

	hr = pDataObj -> SetData ((FORMATETC*)&c_feSelectedObjects, &stg, true);
	if (FAILED(hr)) return hr;

	return NOERROR;
} // SetEnumLONGData


// ------------------------------------------------------------------------------------------------
// Lesen eines EnumLONG aus einem DataObjekt
HRESULT GetEnumLONGData (IDataObject* pIDataObj, IEnum<LONG>** ppIEnumOut)
{
	if (NULL == pIDataObj) return E_POINTER;

HRESULT hr = E_FAIL;
STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	try
	{
	// Testen, ob das gewünschte Format überhaupt da ist
		hr = pIDataObj -> QueryGetData ((FORMATETC*)&c_feSelectedObjects);
		if (NOERROR != hr) _com_issue_error (hr);	// Format nicht vorhanden

		if (NULL == ppIEnumOut)	
			return NOERROR;				// nur abfragen, ob Format vorhanden ist

	// Daten vom DataObject geben lassen
		hr = pIDataObj -> GetData ((FORMATETC*)&c_feSelectedObjects, &stg);
		if (FAILED(hr)) _com_issue_error (hr);

	// einlesen des Enumerators aus den erhaltenen STGMEDIUM
		hr = CreateEnumLONGFromStream (stg.pstm, ppIEnumOut);
		if (FAILED(hr)) _com_issue_error (hr);

		ReleaseStgMedium (&stg);

	}
	catch (_com_error& e)
	{
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
		return _COM_ERROR (e);
	}	

	return NOERROR;
} // GetEnumLONGData


// ------------------------------------------------------------------------------------------------
bool GeoEditExtension :: IsDropSource (void)
{
	return m_bIsDropSource;
}


// -----------------------------------------------------------------------------------------------
// letzte Möglichkeit für die DatenQuelle den Drop doch noch zu verhindern
bool GeoEditExtension :: FQueryDrop (void)
{
	return true;
}


// ------------------------------------------------------------------------------------------------
// verschobene Objekte neu erzeugen;
// wenn bCopy == true, werden die Objekte kopiert, bei bCopy == false nur verschoben
bool GeoEditExtension :: MoveObjectsBuild (long* plAltObjNr, short iAnzVO, POINT ptZiel,
										   bool bCopy)
{
bool bRet = true;
Punkt StartPkt = DBKoordinaten (m_StartPt);				// Startpunkt und
Punkt ZielPkt = DBKoordinaten ((Point&)ptZiel, true);	//  Zielpunkt in DB-Koordinaten konvertieren
KoOrd XDiff = StartPkt.X() - ZielPkt.X();				// Verschiebung in x- und
KoOrd YDiff = StartPkt.Y() - ZielPkt.Y();				//  y-Richtung

bool bText = false;		// unter den zu verschiebenden Objekten ist kein Textobjekt
long lSPAnz;			// Parameter des/der Originalobjekte(s)
KoOrd* plXK; KoOrd* plYK;
short iFlags;
char* pcUIText0 = new char [maxTextLaenge+1];	// maxTextLaenge in geokonst.hxx definiert
char* pcUIText1 = new char [maxTextLaenge+2];	// neuer UniqueIdent
long* plNeuObjNr = new long [iAnzVO];			// Objektnummern der neuen Objekte

	if (!pcUIText0 || !pcUIText1 || !plNeuObjNr)
	{
		DEX_Error (RC_ddgeoobj, EC_NOMEMORY);
		DELETE_VEC (pcUIText0);
		DELETE_VEC (pcUIText1);
		return false;
	}

	for (short i = 0; i < iAnzVO; i++)	// alle verschobenen Objekte abarbeiten
	{
		if (OT_TEXT == DEX_GetObjectType (plAltObjNr[i]))	// Textobjekte separat behandeln
		{
			bText = true;	// unter den zu verschiebenden Objekten ist mindestens ein Textobjekt
			MoveTextObject (bCopy, plAltObjNr[i], XDiff, YDiff, plNeuObjNr[i]);
			continue;
		}

	IObjektGeometrie* pIOG = NULL;

		if (FAILED(CreateInterfaceOG (&pIOG, plAltObjNr[i])))
		{
			bRet = false;
			break;
		}

		pIOG -> GetCnt (&lSPAnz);
		pIOG -> GetX ((void**)&plXK);
		pIOG -> GetY ((void**)&plYK);

		for (long j = 0; j < lSPAnz; j++)
		{
			plXK[j] -= XDiff;	// Koordinaten verschieben
			plYK[j] -= YDiff;
		}

		pIOG -> SetX ((void*)plXK);
		pIOG -> SetY ((void*)plYK);

		pIOG -> GetFlags (&iFlags);
		iFlags |= OGNewObject;		// Geometrie des Objektes nicht ersetzen sondern neu in DB ablegen
		iFlags |= OGForceGeometry;	// kein Test, ob neues Objekt innerhalb des Projekt-Containers liegt
		iFlags |= OGGeometryIsChecked;	// georein nicht anwerfen
		pIOG -> SetFlags (iFlags);

	HRESULT hr = pIOG -> GeometrieAnTRiAS (true, NULL);

		pIOG -> GetONr (&plNeuObjNr[i]);	// neue Objektnummer
		pIOG -> Release ();

		if (hr != S_OK)
		{
			bRet = false;		// kann Objekt nicht erzeugen
			break;
		}

		TX_ASSERT (plNeuObjNr[i] > 0);
	
		// UniqueIdent erweitern mit "/GEOEDIT_EXT_ ...", wenn Objekte kopiert werden
		memset (pcUIText1, '\0', sizeof(pcUIText1));
		if (bCopy)
		{
			pcUIText1[0] = '/';
			wsprintf (pcUIText0, ResString (ResID (IDS_UIFORMAT, pRF), 20), plNeuObjNr[i]);
			strcat (pcUIText1, pcUIText0);
		}

		MerkmaleKopieren (plAltObjNr[i], plNeuObjNr[i], pcUIText1);

		if (! bCopy)	// verschobene Objekte wieder in Recherchefenster aufnehmen und selektieren
			AddToORWindow (plAltObjNr[i], plNeuObjNr[i]);

	} // for i

	DELETE_VEC (pcUIText0);
	DELETE_VEC (pcUIText1);

// hier eventulle Textabhängigkeiten wieder herstellen
	RestoreTextDependence (bCopy, plAltObjNr, plNeuObjNr, iAnzVO);

	if (false == bText)				// ohne Textobjekte
	{
	Rectangle Rec;					// rechteckiger Bereich für Zeichnen der neuen Objekte

		MultiRectangle (plNeuObjNr, i, Rec);
		DEX_RePaintRectWait (Rec);	// neue Objekte zeichnen
	}
	else							// mit mindestens einem Textobjekt
		DEX_RePaintWait();			// gesamte Sicht neu zeichnen, da vor dem ersten Zeichnen
									// eines Textes dessen Größe nicht bestimmbar ist
	MVWind() -> Update();			// sofort zeichnen

	return bRet;
} // MoveObjectsBuild


// --------------------------------------------------------------------------------------------
// Verschieben/Kopieren des lAltObjNr-Textobjektes um die Koordinatendifferenz (XDiff, YDiff)
bool GeoEditExtension :: MoveTextObject (bool bCopy, long lAltObjNr, KoOrd XDiff, KoOrd YDiff,
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

	TX_ASSERT ((TG.iFlags & OGConverted) == 0x0);	// Koordinaten im KoOrd-Format

	TG.pdblX = new KoOrd [TG.lCnt];
	if (TG.pdblX == NULL) return false;
	TG.pdblY = new KoOrd [TG.lCnt];
	if (TG.pdblY == NULL) return false;
	TG.pText = new char [TG.iKCnt+1];	// "+1" für "\0"
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
	TG.iFlags |= OGGeometryIsChecked;	// georein nicht anwerfen

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
// bResult == true, lNeuObjNr > 0:   fehlerfreies Objekt, wurde gespeichert
// bResult == false, lNeuObjNr > 0:  fehlerhaftes Objekt, wurde trotzdem gespeichert
// bResult == false, lNeuObjNr == 0: fehlerhaftes Objekt, wurde nicht gespeichert
// Hier kann aber eigentlich nur der 1. Fall auftreten.

	TX_ASSERT (bResult == true);
	TX_ASSERT (lNeuObjNr > 0);

	if (lNeuObjNr > 0 && SUCCEEDED(hr))		// Initialisierung eines Undo-Objektes
		hr = pIUndo->Init (lNeuObjNr);

	if (lNeuObjNr > 0 && NOERROR == hr)
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
bool GeoEditExtension :: RestoreTextDependence (bool bCopy, long* plAltObjNr, long* plNeuObjNr,
												short iAnzVO)
{
long lBONr = 0L;	// Objektnummer des abhängigen Objektes
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
	for (register short i = 0; i < iAnzVO; i++)
	{
		lBONr = 0L;

		EREL.lONr = plAltObjNr[i];	// Bezugsobjekt, für das Relationen geliefert werden

	// der zu untersuchende RelationsTyp ist "BegleitRelation", d.h. es wird getestet, ob es zu
	// einem Geometrieobjekt ein abhängiges Textobjekt gibt bzw. ob ein gegebenes Textobjekt
	// von einem Geometrieobjekt abhängig ist
	short iOT = DEX_GetObjectType (plAltObjNr[i]);

		TX_ASSERT (iOT == OT_PUNKT || iOT == OT_KANTE || iOT == OT_FLAECHE || iOT == OT_TEXT);

		if (iOT != OT_PUNKT && iOT != OT_KANTE && iOT != OT_FLAECHE && iOT != OT_TEXT)
			continue;

		if (OT_TEXT == iOT)
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

		if (lBONr > 0)	// zugeordnetes Objekt gefunden
		{
			// testen, ob das zugeordnete Objekt auch verschoben wurde
			for (register short j = 0; j < iAnzVO; j++)
				if (plAltObjNr[j] == lBONr) break;

			if (j < iAnzVO)	// das zugeordnete Objekt wurde auch verschoben
			{
			// diese Abhängigkeit nun auch zwischen den neuen Objekten plNeuObjNr[i] und
			// plNeuObjNr[j] herstellen
			short iOT1 = DEX_GetObjectType (plNeuObjNr[i]);

				// wenn sowohl ein Geometrieobjekt und das dazugehörige abhängige Textobjekt
				// verschoben wurden, dann wird die Zuordnung nur dann hergestellt, wenn das
				// 1. Objekt das Geometrieobjekt ist
				if (OT_TEXT == iOT1) continue;

			short iOT2 = DEX_GetObjectType (plNeuObjNr[j]);

				TX_ASSERT (iOT1 == OT_PUNKT || iOT1 == OT_KANTE || iOT1 == OT_FLAECHE ||
						   iOT1 == OT_TEXT);

				if (iOT1 != OT_PUNKT && iOT1 != OT_KANTE && iOT1 != OT_FLAECHE &&
					iOT1 != OT_TEXT)
					continue;

				if (iOT1 == OT_PUNKT || iOT1 == OT_KANTE || iOT1 == OT_FLAECHE)
				{
					TX_ASSERT (iOT2 == OT_TEXT);

					if (iOT2 != OT_TEXT) continue;
				}
				else	// iOT1 == OT_TEXT
				{
					TX_ASSERT (iOT2 == OT_PUNKT || iOT2 == OT_KANTE || iOT2 == OT_FLAECHE);

					if (iOT2 != OT_PUNKT && iOT2 != OT_KANTE && iOT2 != OT_FLAECHE) continue;
				}

				if (OT_TEXT == iOT2)
				{
					MREL.lPONr = plNeuObjNr[i];		// PrimärObjekt, d.h. Geometrieobjekt
					MREL.lSONr = plNeuObjNr[j];		// SekundärObjekt, d.h. Textobjekt
					DEX_ModifyRelation (MREL);		// ohne Funktion MREL.eFcn
				}
			}

			// es gibt ein zugeordnetes Objekt, das sich jedoch nicht unter den verschobenen
			// befindet; falls die Objekte verschoben (also nicht kopiert) wurden
			// (bCopy == false), dann diese Zurordnungen auch neu aufbauen
			else if (false == bCopy)
			{
			short iOT0 = DEX_GetObjectType (lBONr);

				// zuerst die Verbindung zu dem nicht verschobenen Objekt lösen
				if (OT_TEXT == iOT)
				{
					TX_ASSERT (iOT0 == OT_PUNKT || iOT0 == OT_KANTE || iOT0 == OT_FLAECHE);

					if (iOT0 != OT_PUNKT && iOT0 != OT_KANTE && iOT0 != OT_FLAECHE) continue;

					DREL.lPONr = lBONr;				// PrimärObjekt, d.h. Geometrieobjekt
					DREL.lSONr = plAltObjNr[i];		// SekundärObjekt, d.h. Textobjekt
					DEX_DeleteRelation (DREL);		// ohne Funktion DREL.eFcn

					MREL.lPONr = lBONr;				// Geometrieobjekt für neue Zuordnung
					MREL.lSONr = plNeuObjNr[i];		// Textobjekt
				}
				else
				{
					TX_ASSERT (iOT0 == OT_TEXT);

					if (iOT0 != OT_TEXT) continue;

					DREL.lPONr = plAltObjNr[i];		// Geometrieobjekt
					DREL.lSONr = lBONr;				// Textobjekt
					DEX_DeleteRelation (DREL);

					MREL.lPONr = plNeuObjNr[i];		// Geometrieobjekt für neue Zuordnung
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
bool GeoEditExtension :: AddToORWindow (long lAltObjNr, long lNeuObjNr)
{
struct MoveONr Dat;	// in edikonst.hxx definiert

	Dat.lAltObjNr = lAltObjNr;	// Objektnummer des Originalobjektes
	Dat.lNeuObjNr = lNeuObjNr;	// Objektnummer des verschobenen Objektes

ENUMNOKEYLONG ENKL;

	memset (&ENKL, '\0', sizeof (ENUMNOKEYLONG));
	ENKL.eFcn = (ENUMNOKEYLONGPROC) InWelchesFenster;	// durch die Enumeration zu rufende Funktion
	ENKL.ePtr = (void*) &Dat;	// an die gerufene Funktion durchgereichte Daten
	DEX_EnumORWindows (ENKL);

	return true;

} // AddToORWindow


// -----------------------------------------------------------------------------------------------
// Recherchefenster für verschobene Objekte generieren
bool GeoEditExtension :: FensterVerschobeneObjekte (long* plNeuObjNr, short iAnzVO, Rectangle Rec)
{
	TX_ASSERT (plNeuObjNr != NULL);

	if (! plNeuObjNr) return false;

ResString resTitel (ResID (IDS_MOVEDOBJECTS, pRF), 70);
CREATEOBJEKTINFOEX COI;	// Struktur für Recherchefenster
	
	INITSTRUCT (COI, CREATEOBJEKTINFOEX);
	COI.lpCaption = (char*)resTitel.Addr();	// Fensterüberschrift
	COI.plObjs = plNeuObjNr;				// Objektnummern, die angezeigt werden sollen
	COI.iNumObjs = iAnzVO;					// Anzahl der Objektnummern
	COI.cMColor = RGB (255,0,0);			// Markierungsfarbe (rot, grün, blau)
	COI.m_iFlags = ROCreateHidden;			// Fenster beim Erzeugen nicht anzeigen

// das Recherchefenster soll optimal positioniert werden, und zwar möglichst unterhalb des
// Rechtecks Rec, in dem die verschobenen Objekte jetzt liegen; gelingt dies nicht, dann
// möglichts oberhalb bzw. links daneben bzw. rechts daneben; gelingt dies alles nicht, ohne den
// Rec-Bereich zu überdecken, wird das Recherchefenster in die linke untere Hauptfensterecke
// gesetzt; dazu die nachfolgenden Kopfstände
HWND hWnd = DEX_CreateObjektInfo (COI);		// Recherchefenster erzeugen (aber nicht anzeigen)
pWindow pRW = ORWind (hWnd);				// Zeiger auf Recherchefenster geben lassen
Rectangle RWRec = pRW -> WindowRect();		// Größe des Recherchefensters
Rectangle CRc = MVWind() -> CanvasRect();	// Größe des Hauptfensters
Point pt;		// linker unterer Eckpunkt des Recherchefensters
		
	pt.X() = Rec.Left();
	pt.Y() = Rec.Bottom() - RWRec.Top();	// Fenster unter Rec
	if (0 > pt.Y())
	{
		pt.Y() = Rec.Top();					// Fenster über Rec
		if (pt.Y() + RWRec.Top() > CRc.Top())
		{
			pt.X() -= RWRec.Right();			// Fenster links neben Rec
			pt.Y() = Rec.Top() - RWRec.Top();
			if (0 > pt.X())
			{
				pt.X() = Rec.Right();		// Fenster rechts neben Rec
				if (pt.X() + RWRec.Right() > CRc.Right())
				{
					pt.X() = 0;				// Fenster in die untere linke Hauptfensterecke
					pt.Y() = 0;
				}
			}
		}
	}
	if (0 > pt.X()) pt.X() = 0;
	else if (pt.X() + RWRec.Right() > CRc.Right()) pt.X() = CRc.Right() - RWRec.Right();
	if (0 > pt.Y()) pt.Y() = 0;
	else if (pt.Y() + RWRec.Top() > CRc.Top()) pt.Y() = CRc.Top() - RWRec.Top();

	pRW -> ChangePosition (pt);			// Recherchefenster optimal positionieren und
	pRW -> Show ();						//  jetzt anzeigen

	for (short i = 0; i < iAnzVO; i++)
		DEXOR_SelectObject (hWnd, plNeuObjNr[i]);

	return true;
} // FensterVerschobeneObjekte


// -----------------------------------------------------------------------------------------------
// Source-Objekte nach Objektverschiebung löschen; Rückgabe von false, wenn Löschen nicht für alle
// Objekte gelungen ist
bool GeoEditExtension :: SelObjLoeschen (IEnum<LONG>* pEnum)
{
bool bRet = true;

// Löschen aller verschobenen Source-Objekte
long lAnz = (short)((IEnum<LONG>*)(IEnumLONG*)pEnum) -> Count();	// Anzahl und
long* plObjNr = new long [lAnz];	//  Objektnummern der verschobenen Objekte
short i = 0;						// Laufindex für plObjNr

	if (! plObjNr)
	{
		DEX_Error (RC_ddgeoobj, EC_NOMEMORY);
		return false;
	}


	(IEnum<LONG>*)(IEnumLONG*)pEnum -> Reset();

HRESULT hrRet = ((IEnum<LONG>*)(IEnumLONG*)pEnum) -> Next (lAnz, plObjNr, NULL);

	TX_ASSERT (hrRet == S_OK);

	if (S_OK != hrRet)
	{
		DELETE_VEC (plObjNr);
		return false;
	}

Rectangle Rec;		// rechteckiger Bereich für Neuzeichnen nach Löschen

	MultiRectangle (plObjNr, lAnz, Rec);

	try
	{
	WProgressIndicator2 DPI (CLSID_ProgressIndicator);	// throws_com_error
	HRESULT hr = InitProgressIndicator (DPI, ResID(IDS_DELOBJECTS, pRF),
										ResID(IDS_DELETE_STATUS, pRF), lAnz);
	
		if (FAILED(hr)) return false;
		hr = RegisterPI (DPI);
		if (FAILED(hr)) return false;

	}
	catch (_com_error&)
	{
		return false;
	}

	for (i = 0; i < lAnz; i++)
	{
	HRESULT hr = m_PPI.IsCanceled();	// Abbruch des Löschens?

		if (FAILED(hr) ||
			S_OK == hr ||	// Abbruch durch den Anwender
			FAILED(m_PPI.IncrementPosition (NULL)))
		{
			bRet = false;
			break;
		}

		if (! DEX_DeleteObjectEx (plObjNr[i]))
		{
    		DEX_Error (RC_ddgeoobj, EC_OBJNODELETE);
			bRet = false;
		}
	}

	if (FAILED(UnRegisterPI())) return false;

	DELETE_VEC (plObjNr);

	DEX_RePaintRectWait (Rec);	// zu löschende Objekte durch Neuzeichnen auch auf BS löschen
	MVWind() -> Update();		// sofort zeichnen

	return bRet;
} // SelObjLoeschen


// -----------------------------------------------------------------------------------------------
// Umriß der zu verschiebenden/kopierenden Objekte zeichnen
bool GeoEditExtension :: GiveFeedBack (Point* pPolyPoly, int* piPolyCounts, long lAnz, POINTL ptlZiel)
{
	TX_ASSERT (pPolyPoly != NULL);
	TX_ASSERT (piPolyCounts != NULL);

	if (!pPolyPoly || !piPolyCounts) return false;

POINT ptZiel;
HWND hCtrl = MVWind() -> Handle(API_WINDOW_HWND);
Rectangle CRc = MVWind() -> CanvasRect();

	POINTFROMPOINTL (ptZiel, ptlZiel);
	ScreenToClient (hCtrl, &ptZiel);	// Bildschirmkoordinaten in Fensterkoordinaten konvertieren

	// Die nachfolgende Subtraktion von 1 ist Kosmetik, um mit Hartmuts Koordinatenanzeige
	// konform zu gehen !!!!!!!!!!!!
	ptZiel.y = CRc.Top() - CRc.Bottom() - 1 - ptZiel.y;	// y-Koordinate drehen

CoOrd XDiff = m_StartPt.X() - ptZiel.x;		// Verschiebung in x- und
CoOrd YDiff = m_StartPt.Y() - ptZiel.y;		//  y-Richtung

// alle Point's des Vektors pPolyPoly nach pPoPoly verschieben
long lPtAnz = 0;	// Länge des pPoPoly-Vektors

	for (short i = 0; i < lAnz; i++)
		lPtAnz += piPolyCounts[i];

Point* pPoPoly = new Point [lPtAnz];

	if (! pPoPoly)
	{
		DEX_Error (RC_ddgeoobj, EC_NOMEMORY);
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
		DEX_Error (RC_ddgeoobj, EC_NOMEMORY);
		DELETE_VEC (pPoPoly);
		return false;
	}

	pCPPO -> ChangeRop (ROP_Invert);	// das von pCPPO überzeichnete Gebiet wird invertiert
	MVWind() -> Draw (pCPPO);			// alle Polygonobjekte zeichnen

	DELETE_VEC (pPoPoly);
	DELETE (pCPPO);

	return true;
} // GiveFeedBack


// -----------------------------------------------------------------------------------------------
// Objektnummern der selektierten (markierten) Objekte in pEnum bereitstellen
HRESULT GeoEditExtension :: SetObjNummern (IEnum<LONG>* pEnum)
{
// Übertragen der Objektnummern in pEnum
CTable tab (*m_pGB);

	try
	{
		for (tab.First(); tab.Valid(); tab.Next())
		{
		GeometrieKnotenLock kl (tab);

			if (! kl)
			{
	    		DEX_Error (RC_ddgeoobj, EC_SYSERROR);
				continue;
			}
		
			pEnum -> AddItem (kl->GetONr());
		}
	}
	catch (...)
	{
		return E_OUTOFMEMORY;
	}

	return S_OK;

} // SetObjNummern


// -----------------------------------------------------------------------------------------------
// rechteckigen Bereich in BS-Koordinaten bestimmen, der durch die Objekte, deren Objektnummern
// in plObjNr sind, aufgespannt wird
bool GeoEditExtension :: MultiRectangle (long* plObjNr, long lObjAnz, Rectangle& Rec)
{
long lCO [4];	// Containerkoordinaten eines Textobjektes
				// lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax
KoOrd lBXmin = MAXKOORD;				// Koordinaten des Bereiches
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
			PointSymbolSize (plObjNr[i], iPixX, iPixY);
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
// Größe eines Punktsymbols in BS-Pixel ermitteln; Rückgabe in iPixX bzw. iPixY;
// wird false zurückgegeben, sind iPixX und iPixY unbestimmt
bool GeoEditExtension :: PointSymbolSize (long lONr, int& iPixX, int& iPixY)
{
	iPixX = 0;	// für Fehlerfall
	iPixY = 0;

	if (DEX_GetObjectType (lONr) != OT_PUNKT)
		return false;

double dQuot;   // Quotient von Bezugsmaßstab und Darstellungsmaßstab

	DEX_GetActiveScaling (dQuot);
	if (dQuot > 0) dQuot *= 100.;	
	else
	{
		TX_ASSERT (dQuot > 0);
		dQuot = 1.;   // um Division durch Null vorzubeugen
	}

Point PLO, PRU;	// linker oberer (PLO) bzw. rechter unterer Eckpunkt (PRU) des umschreibenden
				//  Rechtecks des Punktsymbols
HANDLEVISINFO HVI;

	INITSTRUCT (HVI, HANDLEVISINFO);		// Initialisierung
	HVI.m_lIdent = DEX_GetObjIdent (lONr);	// Identifikator
	HVI.m_pDesc = NULL;						// beschreibender Text
	HVI.m_pView = NULL;						// SichtName (aktuelle Sicht: NULL)

PVISINFO PVI;
SIZE sizePG;
				
	HVI.m_iVTyp = VTPunkt;				// VisInfoTyp
	HVI.m_pVI = &(PVI.m_VI);			// generischer Pointer auf VisInfo

	if (! DEX_GetIdentVisInfo (HVI))	// RückkehrCode ausgewertet
	{
		sizePG.cx = DEF_SIZE_PUNKT_X;
		sizePG.cy = DEF_SIZE_PUNKT_Y;
	}
	else
		sizePG = PVI.m_Size;   // Punktgröße (Eintrag aus der VisInfo)

	// Größe des Punktsymbols in BS-Pixel in x- bzw. y-Richtung
	iPixX = (int) (sizePG.cx * m_dimDots.Width() / dQuot);
	iPixY = (int) (sizePG.cy * m_dimDots.Height() / dQuot);

	return true;

} // PointSymbolSize


// -----------------------------------------------------------------------------------------------
// DragDrop initialisieren und auslösen
HRESULT GeoEditExtension :: DoDragDropAction (DWORD dwFlags)
{
	NeuerCursor ();		// Standard-Cursur PFEIL wieder einstellen

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

	try
	{
	CEditDropSource* pSource = CEditDropSource::CreateInstance(this);
	
		if (NULL == pSource) throw E_OUTOFMEMORY;
		
	HRESULT hr = pSource -> QueryInterface (IID_IDropSource, DropSrc.ppv());

		if (FAILED(hr)) _com_issue_error (hr);
		
		pSource -> FInit (this, dwFlags);

	}
	catch (...)
	{
		return E_OUTOFMEMORY;
	}

// eigentliches DragDrop
ResString resUndo (ResID (IDS_UNDODRAGDROPOBJECTS, pRF), 50);
DWORD dwEffect = 0L;

	DEX_BeginUndoLevel (resUndo.Addr());

// Erweiterungen eine Chance geben, ihren Senf dazuzugeben
IDragDropAction* pIDDAct = NULL;
HRESULT hr = m_pXtnSite -> QueryInterface (IID_IDragDropAction, (LPVOID*)&pIDDAct);

	if (FAILED(hr)) return hr;
HWND hWndSrc = MVWind()->Handle(API_WINDOW_HWND);
	pIDDAct -> BeginDragDrop (DRAGDROPTYPE_VIEWWINDOW, MVWind()->Handle(API_WINDOW_HWND),
							  dwFlags, DataObj);

// m_bIsDropSource für Unterscheidung, ob aus TRiAS-Fenster (true) oder woanders (z.B.
// Recherchefenster oder Legende) heraus gezogen wurde
	m_bIsDropSource = true;
	hr = ::DoDragDrop (DataObj, DropSrc, DROPEFFECT_MOVE|DROPEFFECT_COPY, &dwEffect);
	m_bIsDropSource = false;	

	if (SUCCEEDED(hr) && DRAGDROP_S_DROP == GetScode(hr)) 
	{
	// Erweiterungen davon in Kenntnis setzen, das alles vorbei ist
		pIDDAct -> EndDragDrop (DRAGDROPTYPE_VIEWWINDOW, MVWind()->Handle(API_WINDOW_HWND), dwEffect);

		if (DROPEFFECT_MOVE == dwEffect)
			SelObjLoeschen ((IEnum<LONG>*)(IEnumLONG*)EnumObj);	// selektierte Objekte aus DB löschen

		DEX_EndUndoLevel();
		pIDDAct -> Release ();
		return NOERROR;
	}

// Erweiterungen davon in Kenntnis setzen, das alles vorbei ist
	pIDDAct -> EndDragDrop (DRAGDROPTYPE_ORWINDOW, hWnd(), DROPEFFECT_NONE);
	pIDDAct -> Release();

	DEX_CancelUndoLevel(true);		// abgebrochen oder Fehler

	return hr;
} // DoDragDropAction

/*
// ------------------------------------------------------------------------------------------------
// QueryInterface ist jetzt notwendig, da ein weiteres Interface unterstützt wird
STDMETHODIMP GeoEditExtension :: QueryInterface (REFIID riid, LPVOID* ppv)
{
	// hier nur nach zusätzlichen Interfaces fragen
	if (IID_ITRiASDropTarget == riid)
	{	// sollte das Interface noch nicht existieren, dann Fehler melden;
		if (m_pEDropTarget == NULL)
		{
			m_pEDropTarget = CEditDropTarget :: CreateInstance (m_pUnk ? m_pUnk : this, this);
			if (NULL == m_pEDropTarget)
				return E_NOINTERFACE;
		}
		*ppv = m_pEDropTarget;
		LPUNKNOWN (*ppv) -> AddRef ();
		return NOERROR;
	}

	// alles weitere wird durch die Basisklasse erledigt
	return CTriasExtension :: QueryInterface (riid, ppv);
} // QueryInterface
*/

// --------------------------------------------------------------------------------------------
// Initialisierung des ProgressIndicators2
HRESULT GeoEditExtension :: InitProgressIndicator (IProgressIndicator2* pPI, ResID uiTitel,
												ResID uiAdjust, ulong ulMaxPos, ulong ulMinPos)
{
	TX_ASSERT (pPI != NULL);

//	Indicator init.: Parent setzen
HWND hWnd = NULL;
HRESULT hr = pPI -> InitNew ((INT_PTR)MWind()->Handle(), 0L, (INT_PTR*)&hWnd);

	if (FAILED(hr)) return hr; 

//	min, max setzen
PIFLAGS rgFlags = (PIFLAGS)(PIFLAGS_STATUS |			// Anzeige der Statuszeile, 
							PIFLAGS_TIME |				//  der verbleibenden Zeit,
							PIFLAGS_ADJUSTPERCENT |		//  des Prozentwertes und
							PIFLAGS_RESULT |			//	der Objektnummer
							PIFLAGS_INIT_SHOWWINDOW);	// erst dann Anzeige, wenn was zu sehen ist

	hr = pPI -> Restart (ulMinPos, ulMaxPos, rgFlags);
	if (FAILED(hr)) return hr;


//	Caption setzen
ResString resTitel (uiTitel, 100);
CComBSTR bstrTitel (resTitel.Addr());	// char* in Bi-String konvertieren

	hr = pPI -> ChangeText (PIFLAGS_CAPTION, bstrTitel);
	if (FAILED(hr)) return hr;
			
//	Adjust-Text setzen
ResString resAdjust (uiAdjust, 100);
CComBSTR bstrAdjust (resAdjust.Addr());

	hr = pPI -> ChangeText (PIFLAGS_ADJUSTPERCENT, bstrAdjust);
	if (FAILED(hr)) return hr;

	return S_OK;
} // InitProgressIndicator


// --------------------------------------------------------------------------------------------
// Registrierung des ProgressIndicators2
HRESULT GeoEditExtension :: RegisterPI (IProgressIndicator2* pPI)
{
	try
	{
		TX_ASSERT (m_dwCookie == 0);
		
	WConnectionPointContainer CPC (this);		// throws_com_error
	WConnectionPoint CP;

		THROW_FAILED_HRESULT(CPC->FindConnectionPoint(IID_IProgressIndicator2, CP.ppi()));
		THROW_FAILED_HRESULT(CP->Advise(pPI, &m_dwCookie));

	}
	catch (_com_error& e) 
	{
		return _COM_ERROR (e);
	}

	return S_OK;
} // RegisterPI


// --------------------------------------------------------------------------------------------
// Abmeldung des ProgressIndicators2
HRESULT GeoEditExtension :: UnRegisterPI (void)
{
	if (0 == m_dwCookie) return S_FALSE;	// es wurde kein Advise() ausgeführt 

	try
	{
	WConnectionPointContainer CPC (this);		// throws_com_error
	WConnectionPoint CP;

		THROW_FAILED_HRESULT(CPC->FindConnectionPoint(IID_IProgressIndicator2, CP.ppi()));
		THROW_FAILED_HRESULT(CP->Unadvise(m_dwCookie));
		m_dwCookie = 0L;

	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	return S_OK;
} // UnRegisterPI




///////////////////////////////////////////////////////////////////////////////////////////////////
// DropSourceObject
CEditDropSource :: CEditDropSource (void)
{
	m_dwRefCnt = 0L;
	m_pGeoEdit = NULL;
	m_dwFlags = 0L;
}


// ------------------------------------------------------------------------------------------------
CEditDropSource :: ~CEditDropSource (void)
{
}


// ------------------------------------------------------------------------------------------------
CEditDropSource* CEditDropSource :: CreateInstance (GeoEditExtension* pGeoEdit)
{
CEditDropSource* pEDSource = new CEditDropSource ();

	if (NULL == pEDSource || !pEDSource -> FInit(pGeoEdit))
	{
		DELETE (pEDSource);
		return NULL;
	}

	return pEDSource;
} // CreateInstance


// ------------------------------------------------------------------------------------------------
bool CEditDropSource :: FInit (GeoEditExtension* pGeoEdit, DWORD dwFlags)
{
	TX_ASSERT (pGeoEdit != NULL);

	m_pGeoEdit = pGeoEdit;
	m_dwFlags = dwFlags;
	return true;
} // FInit


// ------------------------------------------------------------------------------------------------
// IUnknown-Interfaces
STDMETHODIMP_ (ULONG) CEditDropSource :: AddRef (void)
{
	return m_dwRefCnt++;
}


// ------------------------------------------------------------------------------------------------
STDMETHODIMP_ (ULONG) CEditDropSource :: Release (void)
{
	if (0 == --m_dwRefCnt)
	{
		delete this;
		return 0;
	}
	return m_dwRefCnt;
}


// ------------------------------------------------------------------------------------------------
STDMETHODIMP CEditDropSource :: QueryInterface (REFIID riid, LPVOID* ppvObj)
{
	TX_ASSERT (ppvObj != NULL);

	if (IID_IDropSource == riid || IID_IUnknown == riid)
	{
		*ppvObj = this;
		((IUnknown*)(*ppvObj)) -> AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
} // QueryInterface


// -----------------------------------------------------------------------------------------------
// IDropSource-Methoden
STDMETHODIMP CEditDropSource :: QueryContinueDrag (BOOL fEsc, DWORD grfKeyState)
{
	TX_ASSERT (m_pGeoEdit != NULL);
	TX_ASSERT (m_dwFlags != 0);

	if (fEsc)	// DragDrop wurde mit Esc abgebrochen
		return DRAGDROP_S_CANCEL;

	if (!(grfKeyState & m_dwFlags))
	{
		if (m_pGeoEdit -> FQueryDrop()) 
			return DRAGDROP_S_DROP;
		else
			return DRAGDROP_S_CANCEL;
	}

	return NOERROR;		// entspr. S_OK
} // QueryContinueDrag


// ------------------------------------------------------------------------------------------------
STDMETHODIMP CEditDropSource :: GiveFeedback (DWORD dwEffect)
{
	return DRAGDROP_S_USEDEFAULTCURSORS;
}



/*
///////////////////////////////////////////////////////////////////////////////////////////////////
// DropTargetObject
CEditDropTarget :: CEditDropTarget (LPUNKNOWN pIUnk, GeoEditExtension* pGeoEdit)
{
	m_dwRefCnt = 0L;
	m_pGeoEdit = pGeoEdit;	// kein AddRef (), völlig abhängig
	m_pIUnk = pIUnk;
	m_plObjNrVO = NULL;
	m_pPolyPoly = NULL;
	m_piPolyCounts = NULL;
}


// ------------------------------------------------------------------------------------------------
CEditDropTarget :: ~CEditDropTarget (void)
{
	DELETE_VEC (m_plObjNrVO);
	DELETE_VEC (m_pPolyPoly);
	DELETE_VEC (m_piPolyCounts);
}


// ------------------------------------------------------------------------------------------------
CEditDropTarget* CEditDropTarget :: CreateInstance (LPUNKNOWN pIUnk, GeoEditExtension* pGeoEdit)
{
CEditDropTarget* pEDTarget = new CEditDropTarget (pIUnk, pGeoEdit);

	if (NULL == pEDTarget || !pEDTarget -> FInit())
	{
		DELETE (pEDTarget);
		return NULL;
	}

	return pEDTarget;
} // CreateInstance


// ------------------------------------------------------------------------------------------------
bool CEditDropTarget :: FInit (void)
{
	if (NULL == m_pGeoEdit)
		return false;	// m_pGeoEdit muß existieren
	return true;		// ansonsten ist nichts weiter zu tun
} // FInit


// ------------------------------------------------------------------------------------------------
// delegierte IUnknown-Interfaces
STDMETHODIMP_ (ULONG) CEditDropTarget :: AddRef (void)
{
	m_dwRefCnt++;					// nur für Debug
	return m_pIUnk -> AddRef ();	// Delegierung
}


// ------------------------------------------------------------------------------------------------
STDMETHODIMP_ (ULONG) CEditDropTarget :: Release (void)
{
	m_dwRefCnt--;					// nur für Debug
	return m_pIUnk -> Release ();	// Delegierung
}


// ------------------------------------------------------------------------------------------------
STDMETHODIMP CEditDropTarget :: QueryInterface (REFIID riid, LPVOID* ppvObj)
{
	TX_ASSERT (ppvObj);

	return m_pIUnk -> QueryInterface (riid, ppvObj);
}
*/

// ------------------------------------------------------------------------------------------------
// IDropTarget-Methoden
// Routine zeigt an, daß die Maus in ein Fenster eintritt
STDMETHODIMP GeoEditExtension :: DragEnter (DRAGDROPTYPE rgType, HWND hWnd, IDataObject* pIDataSource,
										   DWORD grfKeyState, POINTL ptl, DWORD* pdwEffect)
{
// Testen, über welchem Fenster sich die Maus befindet (rgType wird bei BeginDragDrop() gesetzt)
	if (DRAGDROPTYPE_VIEWWINDOW != rgType)
		return S_FALSE;		// Maus nicht in ein TRiAS-Fenster sondern z.B. in ein
							//  Recherchefenster eingetreten

// Testen, ob pIDataSource EnumLONG mit Objektnummern enthält
	if (NOERROR != GetEnumLONGData (pIDataSource))
		return S_FALSE;		// keine verständlichen Daten

//	TX_ASSERT (m_pGeoEdit);

// Testen, woher das Objekt stammt
	if (IsDropSource())		// Objekte aus der eigenen TRiAS-Datenbank
	{
		*pdwEffect |= DROPEFFECT_MOVE;		// verschieben
		if (grfKeyState & MK_CONTROL)
			*pdwEffect |= DROPEFFECT_COPY;	// kopieren
	}
	else
		// Maus in das TRiAS-Fenster eines anderen Projektes eingetreten
		return S_FALSE;

// Objektnummern der verschobenen Objekte in m_plObjNrVO bereitstellen 
HRESULT hr = GetObjNummern (pIDataSource);

	if (FAILED(hr)) return hr;

// Koordinaten-Vektoren in BS-Koordinaten für Zeichnen der Objektumrisse aufbauen
	UmrissVektor ();

// Umriß der zu verschiebenden Objekte zeichnen
	GiveFeedBack (m_pPolyPoly, m_piPolyCounts, m_iAnzVO, ptl);
	m_ptlOld = ptl;

	return NOERROR;
} // DragEnter


// --------------------------------------------------------------------------------------------
// Routine zeigt an, daß sich die Maus innerhalb des Bezugsfenster bewegt hat, der Zustand der
// Tastatur sich verändert hat bzw. ein interner OLE-Timer abgelaufen ist
STDMETHODIMP GeoEditExtension :: DragOver (DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState,
										  POINTL ptl, DWORD* pdwEffect)
{
// Testen, über welchem Fenster sich die Maus befindet
	if (DRAGDROPTYPE_VIEWWINDOW != rgType)
		return S_FALSE;	// Maus nicht mehr im TRiAS-Fenster sondern z.B. über Recherchefenster

// wenn die Daten nicht für mich sind, dann zurück
	if (NULL == m_plObjNrVO)
		return S_FALSE;

//	TX_ASSERT (m_pGeoEdit);

	// noch einmal testen, woher das Objekt stammt
	if (IsDropSource())	// Objekte aus der eigenen TRiAS-Datenbank
	{
		*pdwEffect |= DROPEFFECT_MOVE;		// verschieben
		if (grfKeyState & MK_CONTROL)
			*pdwEffect |= DROPEFFECT_COPY;	// kopieren
	}
	else
		// Maus in das TRiAS-Fenster eines anderen Projektes eingetreten
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
STDMETHODIMP GeoEditExtension :: DragLeave (DRAGDROPTYPE rgType, HWND hWnd)
{
// Testen, über welchem Fenster sich die Maus befindet
	if (DRAGDROPTYPE_VIEWWINDOW != rgType)
		return S_FALSE;

// wenn die Daten nicht für mich sind, dann zurück
	if (NULL == m_plObjNrVO) 
		return S_FALSE;

//	TX_ASSERT (m_pGeoEdit);

// Umriß der zu verschiebenden Objekte löschen
	GiveFeedBack (m_pPolyPoly, m_piPolyCounts, m_iAnzVO, m_ptlOld);

	return NOERROR;
} // DragLeave


// ------------------------------------------------------------------------------------------------
// Routine zeigt an, daß die Quelle "Drop" signalisiert hat
STDMETHODIMP GeoEditExtension :: Drop (DRAGDROPTYPE rgType, HWND hWnd, IDataObject* pIDataSource,
									  DWORD grfKeyState, POINTL ptl, DWORD* pdwEffect)
{
// Testen, über welchem Fenster sich die Maus befindet
	if (DRAGDROPTYPE_VIEWWINDOW != rgType)
		return S_FALSE;

// wenn die Daten nicht für mich sind, dann zurück
	if (NULL == m_plObjNrVO) 
		return S_FALSE;		// 16.1.97: bisher E_FAIL

//	TX_ASSERT (m_pGeoEdit);

	if (false == IsDropSource())	// Objekte aus fremden Quellen
		return S_FALSE;

// Umriß der zu verschiebenden Objekte löschen
	GiveFeedBack (m_pPolyPoly, m_piPolyCounts, m_iAnzVO, m_ptlOld);

// neue Objekte erzeugen
HRESULT hr = E_FAIL;	// für den Fall, daß Erzeugung nicht gelingt
POINT pt;
HWND hCtrl = MVWind() -> Handle(API_WINDOW_HWND);

	POINTFROMPOINTL (pt, ptl);
	ScreenToClient (hCtrl, &pt);	// Bildschirmkoordinaten in Fensterkoordinaten konvertieren

bool bCopy = false;	// Objekte werden kopiert/verschoben (true/false)

	if (grfKeyState & MK_CONTROL)
		bCopy = true;

	if (MoveObjectsBuild (m_plObjNrVO, m_iAnzVO, pt, bCopy))	// neue Objekte erfolgreich erzeugt
	{
		*pdwEffect |= DROPEFFECT_MOVE;		// verschieben
		if (grfKeyState & MK_CONTROL)
			*pdwEffect |= DROPEFFECT_COPY;	// kopieren

		hr = NOERROR;
	}
		
	DELETE_VEC (m_plObjNrVO);		// Daten werden nicht mehr benötigt
	return hr;	

} // Drop


// -----------------------------------------------------------------------------------------------
// Objektnummern der verschobenen Objekte aus pIEnum wieder auslesen und in m_plObjNrVO bereitstellen
HRESULT GeoEditExtension :: GetObjNummern (IDataObject* pIDataSource)
{
	TX_ASSERT (pIDataSource != NULL);

// EnumLONG mit ObjektNummern aus DataSource holen
WEnumLONG EnumObj (CLSID_EnumObjectsByNumber);		// throws_com_error
HRESULT hr = GetEnumLONGData (pIDataSource, (IEnum<LONG>**)(IEnumLONG**)&EnumObj);

	if (FAILED(hr)) return hr;

	// Objektnummern der verschobenen Objekte in m_plObjNrVO bereitstellen
	m_iAnzVO = (short)((IEnum<LONG>*)(IEnumLONG*)EnumObj) -> Count();	// Anzahl der verschobenen Objekte
	DELETE_VEC (m_plObjNrVO);
	m_plObjNrVO = new long [m_iAnzVO];	// Objektnummern der verschobenen Objekte

	if (! m_plObjNrVO)
	{
		DEX_Error (RC_ddgeoobj, EC_NOMEMORY);
		return E_OUTOFMEMORY;
	}

	(IEnum<LONG>*)(IEnumLONG*)EnumObj -> Reset();

HRESULT hrRet = ((IEnum<LONG>*)(IEnumLONG*)EnumObj) -> Next (m_iAnzVO, m_plObjNrVO, NULL);

	TX_ASSERT (hrRet == S_OK);

	return hrRet;
} // GetObjNummern


// -----------------------------------------------------------------------------------------------
// aus den DB-Koordinaten der zu verschiebenden Objekte Vektor mit BS-Koordinaten erzeugen
bool GeoEditExtension :: UmrissVektor (void)
{
long lSPAnz;			// Parameter des/der Originalobjekte(s)
KoOrd* plXK; KoOrd* plYK;
short iObjTyp;
long lAnz = 0;			// Gesamt-Stützpunktanzahl aller zu verschiebenden Objekte

	m_piPolyCounts = new int [m_iAnzVO];

	if (! m_piPolyCounts)
	{
		DEX_Error (RC_ddgeoobj, EC_NOMEMORY);
		return false;
	}

const short i5 = 5;		// Anzahl der BS-Punkte für das Zeichnen des Umrisses eines Punktsymbols

	// die einzelnen und die Gesamt-Stützpunktanzahl der zu verschiebenden Objekte feststellen
	for (short i = 0; i < m_iAnzVO; i++)
	{
	IObjektGeometrie* pIOG = NULL;

		if (FAILED(CreateInterfaceOG (&pIOG, m_plObjNrVO[i])))
			return false;

		pIOG -> GetObjTyp (&iObjTyp);

		switch (iObjTyp)
		{
			case OT_PUNKT:
				m_piPolyCounts[i] = i5;	// Rechteck um Punktsymbol
				lAnz += i5;
				break;

			case OT_KANTE:
				pIOG -> GetCnt (&lSPAnz);
				m_piPolyCounts[i] = lSPAnz;
				lAnz += lSPAnz;
				break;

			case OT_FLAECHE:
			{
			long* plCnt;

				pIOG -> GetLPCnt (&plCnt);
				m_piPolyCounts[i] = plCnt[0];	// nur die Außenkontur berücksichtigen
				lAnz += plCnt[0];
			}
				break;

			case OT_TEXT:
				m_piPolyCounts[i] = i5;			// Rechteck um Textfeld
				lAnz += i5;
				break;
		}
		pIOG -> Release ();
	}

long k = 0;		// Laufindex von m_pPolyPoly

	m_pPolyPoly = new Point [lAnz];

	if (! m_pPolyPoly)
	{
		DEX_Error (RC_ddgeoobj, EC_NOMEMORY);
		return false;
	}

long lCO [4];	// Containerkoordinaten eines Textobjektes
				// lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax

	// die DB-Koordinaten der zu verschiebenden Objekte in BS-Koordinaten konvertieren
	for (i = 0; i < m_iAnzVO; i++)
	{
	IObjektGeometrie* pIOG = NULL;

		if (FAILED(CreateInterfaceOG (&pIOG, m_plObjNrVO[i])))
			return false;

		pIOG -> GetObjTyp (&iObjTyp);
		pIOG -> GetX ((void**)&plXK);
		pIOG -> GetY ((void**)&plYK);

		switch (iObjTyp)
		{
			case OT_PUNKT:
			{
			Point Pt = BSKoordinaten (plXK[0], plYK[0]); 
			int iPixX, iPixY;	// Größe eines Punktsymbols in BS-Pixel

				PunktSymbolGroesse (pIOG, iPixX, iPixY);
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
				pIOG -> GetCnt (&lSPAnz);
				for (long j = 0; j < lSPAnz; j++, k++)
					m_pPolyPoly[k] = BSKoordinaten (plXK[j], plYK[j]);
				break;
			}

			case OT_FLAECHE:
			{
			long* plCnt;

				pIOG -> GetLPCnt (&plCnt);
				for (long j = 0; j < plCnt[0]; j++, k++)
					m_pPolyPoly[k] = BSKoordinaten (plXK[j], plYK[j]);
				break;
			}

			case OT_TEXT:
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
		pIOG -> Release ();
	}

	return true;

} // UmrissVektor
