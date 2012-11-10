// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/30/1998 09:12:06 AM
//
// @doc
// @module NativeGeometry.cpp | GeometrieFunktionen für TRiAS-Objekte

#include "trias01p.hxx"

#include "resource.h"

#include <math.h>
#include <float.h>
#include <GMObjects/GMObjects.h>

#include <dbmsg.hmc>
#include <ciid.h>
#include <ActDB.h>
#include <Array.h>
#include <ErrInst.hxx>
#include <DBTypes.h>
#include <NativeObject.h>
#include <ScaleHeader.h>
#include <GeometryBlob.h>
#include <GeometryWKT.h>

#include "Strings.h"
#include "ObjGuidHeader.h"
#include "syncdb.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

using namespace trias_nativeheader;
using namespace trias_geometryblob;
using namespace trias_geometrywkt;

namespace trias_nativeobject {

///////////////////////////////////////////////////////////////////////////////
// 
inline 
long ToCoOrd (double dVal)
{
	if (0 == dVal)
		return 0;
	return dVal > 0 ? long(dVal + 0.5) : long(dVal - 0.5);
}

/////////////////////////////////////////////////////////////////////////////
// Punktobjekte
HRESULT CNativeObject::GetPointGeometry (LPCSTR pcName, 
	double_v &rX, double_v &rY, double *plWindow, double *plCont)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (!m_fIsValid)
		return E_UNEXPECTED;

#if defined(_DEBUG)
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetObjectType (&dwType));
	_ASSERTE(dwType == OTPunkt || dwType == OTText);		// gegebenes Objekt ist wirklich Punkt-/TextObjekt
#endif // _DEBUG

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
struct obl OBLSatz;
ErrCode RC;

	__ReadHR(dbaOBL, OBLSatz);

	if (0 == OBLSatz.zokp)
		return HRESULT_FROM_ERRCODE(EC_STATUSERROR);		// falscher Objekttyp

DB_ADDR dbapol(m_hPr);
struct pol POLSatz;

	dbapol.file_no = POL;
	dbapol.rec_no = OBLSatz.zokp;
	__ReadHR (dbapol, POLSatz);

// Container des Objektes setzen
	if (NULL != plCont) {
		plCont[0] = plCont[1] = POLSatz.kpkrd.px;
		plCont[2] = plCont[3] = POLSatz.kpkrd.py;
	}

// wenn außerhalb des benötigten Bereiches, dann wieder raus
	if (NULL != plWindow) {
		if (POLSatz.kpkrd.px < plWindow[0] || POLSatz.kpkrd.px > plWindow[1] ||
		    POLSatz.kpkrd.py < plWindow[2] || POLSatz.kpkrd.py > plWindow[3])
		{
			return S_FALSE;
		}
	}

// Koordinaten merken
	try {
		rX.push_back (POLSatz.kpkrd.px);
		rY.push_back (POLSatz.kpkrd.py);

	} catch (...) {
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// LinienObjekte
HRESULT CNativeObject::GetLineGeometry (
	LPCSTR pcName, double_v &rX, double_v &rY, double *plWindow, double *plCont)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (!m_fIsValid)
		return E_UNEXPECTED;

#if defined(_DEBUG)
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetObjectType (&dwType));
	_ASSERTE(dwType == OTLinie);		// gegebenes Objekt ist wirklich LinienObjekt
#endif // _DEBUG

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
struct obl OBLSatz;
ErrCode RC;

	__ReadHR(dbaOBL, OBLSatz);

	if (0 == OBLSatz.zovol)
		return HRESULT_FROM_ERRCODE(EC_STATUSERROR);		// falscher Objekttyp

// einzelne Kanten der Linie durchgehen
DB_ADDR dbavol(m_hPr);
struct vol vol;

// Anfangswerte setzen
	dbavol.file_no = VOL;

// evtl. Container mit Window vergleichen 
	if (NULL != plCont) { 
	// Container besorgen
		if (NULL != plWindow) {
			RETURN_FAILED_HRESULT(GetKantenCont (OBLSatz.zovol, plCont));
			if (plCont[1] < plWindow[0] || plCont[0] > plWindow[1] ||
				plCont[3] < plWindow[2] || plCont[2] > plWindow[3])
			{
				return S_FALSE;
			}
		}
		else {
		// Container vorinitialisieren
			plCont[XMIN_IDX] = plCont[YMIN_IDX] = DBL_MAX;	// enthalten dann Minima
			plCont[XMAX_IDX] = plCont[YMAX_IDX] = -DBL_MAX;	// enthalten dann Maxima
		}
	}

// Auffinden der einzelnen Kanten
bool fLast = true;

	dbavol.rec_no = OBLSatz.zovol;
	do {
		__ReadHR (dbavol, vol);
	
	// Zeiger nächste Kante auf VOL
		fLast = (0 != vol.znvol) ? false : true;
		RETURN_FAILED_HRESULT (GetKante (vol.zvolk, fLast, rX, rY, plCont));
		dbavol.rec_no = vol.znvol;
	} while (!fLast);

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Flächenobjekte
HRESULT CNativeObject::GetAreaGeometry (
	LPCSTR pcName, double_v &rX, double_v &rY, ulong_v &rKnt, 
	double *plWindow, double *plCont)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (!m_fIsValid)
		return E_UNEXPECTED;

#if defined(_DEBUG)
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetObjectType (&dwType));
	_ASSERTE(dwType == OTFlaeche);		// gegebenes Objekt ist wirklich FlächenObjekt
#endif // _DEBUG

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
struct obl OBLSatz;
ErrCode RC;

	__ReadHR(dbaOBL, OBLSatz);

	if (0 == OBLSatz.zovoma)
		return HRESULT_FROM_ERRCODE(EC_STATUSERROR);		// falscher Objekttyp

DB_ADDR dbakal(m_hPr), dbakfm(m_hPr), dbamal(m_hPr);
struct kal kal;
struct mal mal;
struct kfm kfm;
long izap, izep, zkl, zkln;
long zkfn = 0;

// Anfangswerte setzen
	dbamal.file_no = MAL;
	dbakfm.file_no = KFM;
	dbakal.file_no = KAL;

// Auffinden der einzelnen Kanten
	dbamal.rec_no = OBLSatz.zovoma;
	__ReadHR (dbamal, mal);
	dbakfm.rec_no = mal.zmkfm;

// evtl. Container mit Window vergleichen 
	if (NULL != plCont) {
	// Container besorgen
		if (NULL != plWindow) {
			RETURN_FAILED_HRESULT(GetMaschenCont (dbakfm.rec_no, plCont));
			if (plCont[1] < plWindow[0] || plCont[0] > plWindow[1] ||
				plCont[3] < plWindow[2] || plCont[2] > plWindow[3])
			{
				return S_FALSE;
			}
		}
		else {
		// Container vorinitialisieren
			plCont[XMIN_IDX] = plCont[YMIN_IDX] = DBL_MAX;	// enthalten dann Minima
			plCont[XMAX_IDX] = plCont[YMAX_IDX] = -DBL_MAX;	// enthalten dann Maxima
		}
	}

// Geometrie einer Masche einlesen
BOOL fLast = TRUE;

	do {
		__ReadHR (dbakfm, kfm);		// nächste Kante
		zkl = kfm.zkfmk;			// Zeiger auf KAL (+oder-)
		zkfn = kfm.znkfm;			// nächste Kante

	// Zeiger wieder auf KFM
	// Prüfung, ob Kante des gleichen Randes folgt
		if (0 != zkfn) {
			dbakfm.rec_no = zkfn;
			__ReadHR (dbakfm, kfm);
			zkln = kfm.zkfmk;

		// Zeiger nächste Kante aus KFM
			dbakal.rec_no = labs (zkl);
			__ReadHR (dbakal, kal);		// Kante lesen
			if (zkl < 0)  izep = kal.zap;
			else	      izep = kal.zep;

			dbakal.rec_no = labs (zkln);
			__ReadHR (dbakal, kal);		// folgende Kante
			if (zkln < 0) izap = kal.zep;
			else	      izap = kal.zap;

			if (izap == izep)
				fLast = FALSE;
			else 
				fLast = TRUE;
		} else
			fLast = TRUE;

	// Bearbeitung einer Kante
	size_t iCurrSize = rX.size();

		RETURN_FAILED_HRESULT (GetKante (zkl, fLast, rX, rY, plCont));

	// weitere Kante vorhanden
		if (fLast)		// Ende der Kontur 
			rKnt.push_back (rX.size()-iCurrSize);

		if (0 != zkfn) 
			dbakfm.rec_no = zkfn;
		else
			return S_OK;	// fertig, alles eingelesen

	} while (TRUE);

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// TextObjekte

HRESULT CNativeObject::GetTextGeometryAndText (
	LPCSTR pcName, double_v &rX, double_v &rY, double &rdAngle, 
	os_string &rStr, double *plWindow, double *plCont)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (!m_fIsValid)
		return E_UNEXPECTED;

#if defined(_DEBUG)
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetObjectType (&dwType));
	_ASSERTE(dwType == OTText);		// gegebenes Objekt ist wirklich TextObjekt
#endif // _DEBUG

// Geometry besorgen
CActDB ActDB(m_hPr);
HRESULT hr = GetPointGeometry(pcName, rX, rY, plWindow, plCont);

	if (S_OK != hr) return hr;	// S_FALSE ist NoFit

// Winkel besorgen
	rdAngle = 0.0;

// Text besorgen
	return GetTextObjektText (GetHeaderLong (m_hPr, g_cbTextObjMCode, 99999100L, 10), rStr);
}

/////////////////////////////////////////////////////////////////////////////
// allgemeine Geometrieroutine, liefert Geoemtrie als eindimensionales DoubleSafeArray
// ab, welches Wertetripel (X,Y,Z) bzw. (R,H,Z) enthält
HRESULT CNativeObject::GetGeometry (
	LPCSTR pcName, SAFEARRAY **ppGeom, double *plWindow, double *plCont)
{
	if (NULL == ppGeom)
		return E_POINTER;

// Geometrie des Objektes liefern
CSPoint vec(0.0, 0.0, 1.0);		// Standard-Normale

	COM_TRY {
	DWORD dwType = 0;
	double_v vX, vY;
//	CPoints pts;
	CScaleHeader Hdr (m_hPr);
	HRESULT hr = S_OK;

	// evtl. Fenster Scalieren
		if (NULL != plWindow) {
			Hdr.Scale (plWindow[0], plWindow[2]);
			Hdr.Scale (plWindow[1], plWindow[3]);
		}

	// eigentliche Geometrie besorgen
		THROW_FAILED_HRESULT(GetObjectType (&dwType));
		switch (dwType) {
		case OTPunkt:
			{
			// Punktobjekte
				THROW_FAILED_HRESULT(hr = GetPointGeometry (pcName, vX, vY, plWindow, plCont));
				if (S_FALSE == hr) return TRIASDB_S_OBJECTDOESNOTFIT;

				_ASSERTE(vX.size() == vY.size() && 1 == vX.size());
				THROW_FAILED_HRESULT(CreateSABlobFromVertices(Hdr, vX, vY, &vec, NULL, CLSID_TRiASCSPointGeometry, ppGeom));
			}
			break;

		case OTLinie:
			{
			// Linienobjekte
				THROW_FAILED_HRESULT(hr = GetLineGeometry (pcName, vX, vY, plWindow, plCont));
				if (S_FALSE == hr) return TRIASDB_S_OBJECTDOESNOTFIT;

				_ASSERTE(vX.size() == vY.size());
				THROW_FAILED_HRESULT(CreateSABlobFromVertices(Hdr, vX, vY, &vec, NULL, CLSID_TRiASCSPolylineGeometry, ppGeom));
			}
			break;

		case OTFlaeche:
			{
			// Flächenobjekte
			ulong_v vKnt;

				THROW_FAILED_HRESULT(hr = GetAreaGeometry (pcName, vX, vY, vKnt, plWindow, plCont));
				if (S_FALSE == hr) return TRIASDB_S_OBJECTDOESNOTFIT;

				_ASSERTE(vX.size() == vY.size());
				_ASSERTE(vKnt.size() > 0);

				if (1 == vKnt.size()) {
				// nur eine Kontur
					THROW_FAILED_HRESULT(CreateSABlobFromVertices(Hdr, vX, vY, &vec, NULL, CLSID_TRiASCSPolygonGeometry, ppGeom));
				
				} else {
				// Außenkontur mit Inseln
				vector<void *> vBlobs;
				ulong_v vSizes;
				size_t j = 0;
				double_i itx = vX.begin();
				double_i ity = vY.begin();

					for (size_t iKnt = 0; iKnt < vKnt.size(); iKnt++) {
					void *pBlob = NULL;
					unsigned long uiSize = 0L;

						if (iKnt != 0) {
							advance (itx, vKnt[iKnt-1]);
							advance (ity, vKnt[iKnt-1]);
						}
						THROW_FAILED_HRESULT(CreateBlobFromVertices (Hdr, vKnt[iKnt], itx, ity, &vec, NULL, CLSID_TRiASCSPolygonGeometry, &pBlob, &uiSize));
						vBlobs.push_back (pBlob);
						vSizes.push_back (uiSize);
					}
					_ASSERTE(vBlobs.size() == vKnt.size());
					_ASSERTE(vSizes.size() == vKnt.size());

					THROW_FAILED_HRESULT(CreateSABlobBoundaryFromArray (vBlobs.size(), vBlobs.begin(), vSizes.begin(), ppGeom));

					for (size_t i = 0; i < vKnt.size(); i++) 
						::CoTaskMemFree(vBlobs[i]);	// Speicher wieder freigeben
				}
			}
			break;

		case OTText:
			{
			// Textobjekte
			os_string str (g_cbNil);
			double dAngle = 0.0;

				THROW_FAILED_HRESULT(hr = GetTextGeometryAndText (pcName, vX, vY, dAngle, str, plWindow, plCont));
				if (S_FALSE == hr) return TRIASDB_S_OBJECTDOESNOTFIT;

				_ASSERTE(vX.size() == vY.size() && 1 == vX.size());

			unsigned char PropertiesBytes[4] = {0, 0, 0, 0};

				PropertiesBytes[3] = 0;		// Alignment
				PropertiesBytes[2] = 1;		// unformatted text

				_ASSERTE(sizeof(long) == sizeof(PropertiesBytes));

			CMakeBlobs::TEXTBLOBDATA TBD;

				TBD.dRotation = 0.0;
				TBD.lFlags = *(long *)&PropertiesBytes;
				TBD.strText = str;
				THROW_FAILED_HRESULT(CreateSABlobFromVertices(Hdr, vX, vY, &vec, &TBD, CLSID_TRiASCSTextPointGeometry, ppGeom));
			}
			break;

		default:
			{
			// Komplexobjekte etc.
				*ppGeom = NULL;
				return E_INVALIDARG;
			}
			break;
		}

	// evtl. Container DeScalieren
		if (NULL != plCont) {
			Hdr.UnScale (plCont[XMIN_IDX], plCont[YMIN_IDX]);	// in RealKoordinaten umrechnen
			Hdr.UnScale (plCont[XMAX_IDX], plCont[YMAX_IDX]);
		}

	} COM_CATCH;

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// allgemeine Geometrieroutine, liefert Geoemtrie als OGC WKT (well-known text)
HRESULT CNativeObject::GetGeometryWKT (
	LPCSTR pcName, BSTR *pbstrWKT, double *plWindow, double *plCont)
{
	if (NULL == pbstrWKT)
		return E_POINTER;

// Geometrie des Objektes liefern
	COM_TRY {
	DWORD dwType = 0;
	double_v vX, vY;
	CScaleHeader Hdr (m_hPr);
	HRESULT hr = S_OK;

	// evtl. Fenster Scalieren
		if (NULL != plWindow) {
			Hdr.Scale (plWindow[0], plWindow[2]);
			Hdr.Scale (plWindow[1], plWindow[3]);
		}

	// eigentliche Geometrie besorgen
		THROW_FAILED_HRESULT(GetObjectType (&dwType));
		switch (dwType) {
		case OTPunkt:
			{
			// Punktobjekte
				THROW_FAILED_HRESULT(hr = GetPointGeometry (pcName, vX, vY, plWindow, plCont));
				if (S_FALSE == hr) return TRIASDB_S_OBJECTDOESNOTFIT;

				_ASSERTE(vX.size() == vY.size() && 1 == vX.size());
				THROW_FAILED_HRESULT(CreatePointWKTFromVertices(Hdr, vX, vY, pbstrWKT));
			}
			break;

		case OTLinie:
			{
			// Linienobjekte
				THROW_FAILED_HRESULT(hr = GetLineGeometry (pcName, vX, vY, plWindow, plCont));
				if (S_FALSE == hr) return TRIASDB_S_OBJECTDOESNOTFIT;

				_ASSERTE(vX.size() == vY.size());
				THROW_FAILED_HRESULT(CreateLineWKTFromVertices(Hdr, vX, vY, pbstrWKT));
			}
			break;

		case OTFlaeche:
			{
			// Flächenobjekte
			ulong_v vKnt;

				THROW_FAILED_HRESULT(hr = GetAreaGeometry (pcName, vX, vY, vKnt, plWindow, plCont));
				if (S_FALSE == hr) return TRIASDB_S_OBJECTDOESNOTFIT;

				_ASSERTE(vX.size() == vY.size());
				_ASSERTE(vKnt.size() > 0);
				THROW_FAILED_HRESULT(CreateAreaWKTFromVertices(Hdr, vKnt, vX, vY, pbstrWKT));
			}
			break;

		case OTText:
			{
			// Textobjekte
			os_string str (g_cbNil);
			double dAngle = 0.0;

				THROW_FAILED_HRESULT(hr = GetTextGeometryAndText (pcName, vX, vY, dAngle, str, plWindow, plCont));
				if (S_FALSE == hr) return TRIASDB_S_OBJECTDOESNOTFIT;

				_ASSERTE(vX.size() == vY.size() && 1 == vX.size());
				THROW_FAILED_HRESULT(CreatePointWKTFromVertices(Hdr, vX, vY, pbstrWKT));
			}
			break;

		default:
			{
			// Komplexobjekte etc.
				*pbstrWKT = NULL;
				return E_INVALIDARG;
			}
			break;
		}

	// evtl. Container DeScalieren
		if (NULL != plCont) {
			Hdr.UnScale (plCont[XMIN_IDX], plCont[YMIN_IDX]);	// in RealKoordinaten umrechnen
			Hdr.UnScale (plCont[XMAX_IDX], plCont[YMAX_IDX]);
		}

	} COM_CATCH;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige Helper
HRESULT CNativeObject::GetKante (
	long lFirst, BOOL fLast, double_v &rX, double_v &rY, double *plCont)
{
DB_ADDR dbakal(m_hPr), dbakpl(m_hPr), dbaspl(m_hPr);
ErrCode RC;
struct kal kal;
struct kpl kpl;

// Anfangswerte setzen
	dbakal.file_no = KAL;
	dbakpl.file_no = KPL;

// Beginn Kante
	dbakal.rec_no = labs (lFirst);
	__ReadHR (dbakal, kal);
	
// Container korrigieren
	if (NULL != plCont) {
		if (plCont[XMIN_IDX] > kal.kcont.kxmin) 
			plCont[XMIN_IDX] = kal.kcont.kxmin;
		if (plCont[XMAX_IDX] < kal.kcont.kxmax) 
			plCont[XMAX_IDX] = kal.kcont.kxmax;
		if (plCont[YMIN_IDX] > kal.kcont.kymin) 
			plCont[YMIN_IDX] = kal.kcont.kymin;
		if (plCont[YMAX_IDX] < kal.kcont.kymax) 
			plCont[YMAX_IDX] = kal.kcont.kymax;
	}

long izap, izep;

	if (lFirst < 0) {
	// Vertauschen Anfangs- und Endpunkt
		izep = kal.zap;		// Zeiger Endpkt. auf KPL
		izap = kal.zep;		// Zeiger Anf.pkt. auf KPL
	} else if (lFirst > 0) {
	// Anfangs- und Endpunkt in richtiger Folge
		izap = kal.zap;
		izep = kal.zep;
	} else 
		return HRESULT_FROM_ERRCODE(EC_BADKAL); // Zeiger ZKL darf nicht 0 sein

long zspl = kal.zksp;		// Zeiger Stützpunkt KL -> SPL
long iasp = kal.asp;

// Anzahl Stützpunkte, Anfangspunktbearbeitung einer Kante
	dbakpl.rec_no = izap;
	__ReadHR (dbakpl, kpl);

	try {
		rX.push_back (kpl.pkrd.kpx);		// AnfangsPunkt X
		rY.push_back (kpl.pkrd.kpy);		// AnfangsPunkt Y

		if (0 != iasp) {
		// ab hier ist es versionsspezifisch
			if (VERSION05000010 <= LocGetDBVersion(m_hPr)) {
			struct longspl SPLSatz;

			// Stützpunktbearbeitung
				dbaspl.file_no = SPL_NEW;
				if (lFirst > 0) {
				// Stützpkt. in Kantenrichtung
					for (long j = 0; j < iasp; /**/) {
						if (zspl == 0)
							return HRESULT_FROM_ERRCODE(EC_BADSPL);

						dbaspl.rec_no = zspl;
						__ReadHR (dbaspl, SPLSatz);
						for (long i = 0; i < NUMSPLCOORDS && j < iasp; i++, j++) {
							rX.push_back (SPLSatz.spxl[i]);
							rY.push_back (SPLSatz.spyl[i]);
						}

					// Zeiger auf nächsten Satz
						zspl = SPLSatz.znspl;
					}
				} else {
				// Stützpunkt entgegen Kantenrichtung, Zeiger auf SPL speichern
				vector<long> Recs;

					while (0 != zspl) {
						dbaspl.rec_no = zspl;
						__ReadHR (dbaspl, SPLSatz);
						Recs.push_back (zspl);
						zspl = SPLSatz.znspl;
					}
				
				// Zeiger ZSPL von hinten abarbeiten
				long lCnt = iasp;	// Anzahl der Stützpunkte
				long k = 0;			// Anzahl der SPLSätze

					for (vector<long>::reverse_iterator rit = Recs.rbegin(); rit != Recs.rend(); ++rit) {
					// vorhergehenden Satz einlesen
						dbaspl.rec_no = *rit;
						__ReadHR (dbaspl, SPLSatz);

					// Koordinaten speichern
						for (long i = lCnt % NUMSPLCOORDS; i >= 0 && lCnt >= 0; i--, lCnt--) {
							rX.push_back (SPLSatz.spxl[i]);
							rY.push_back (SPLSatz.spyl[i]);
						}
					}
				}
			} else {
			// ansonsten mit alter Struktur arbeiten
			struct spl spl;

			// Stützpunktbearbeitung
				dbaspl.file_no = SPL_OLD;
				if (lFirst > 0) {
				// Stützpkt. in Kantenrichtung
					for (long j = 0; j < iasp; j++) {
						if (zspl <= 0)
							return HRESULT_FROM_ERRCODE(EC_BADSPL);
						dbaspl.rec_no = zspl;
						__ReadHR (dbaspl, spl);
						rX.push_back (spl.spx);
						rY.push_back (spl.spy);
						zspl = spl.znsp;
					}
				} else {
				// Stützpunkt entgegen Kantenrichtung, Zeiger auf SPL speichern
				vector<long> Recs;

					for (long j = 0; j < iasp; j++) {
						if (zspl <= 0)
							return HRESULT_FROM_ERRCODE(EC_BADSPL);
						Recs.push_back (zspl);

						dbaspl.rec_no = zspl;
						__ReadHR (dbaspl, spl);
						zspl = spl.znsp;
					}
				
				// Zeiger ZSPL von hinten abarbeiten
					for (vector<long>::reverse_iterator rit = Recs.rbegin(); rit != Recs.rend(); ++rit) {
						dbaspl.rec_no = *rit;
						__ReadHR (dbaspl, spl);
						rX.push_back (spl.spx);
						rY.push_back (spl.spy);
					}
				}
			}
		}

	// Endpunkt bearbeiten
		if (fLast) {
		// Endpunkt speichern, es kommen keine Kanten mehr
			dbakpl.rec_no = izep;
			__ReadHR (dbakpl, kpl);
			rX.push_back (kpl.pkrd.kpx);	// EndPunkt X
			rY.push_back (kpl.pkrd.kpy);	// EndPunkt Y
		}

	} catch (...) {
	// einer der push_back's ist fehlgeschlagen
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

HRESULT CNativeObject::GetKantenCont (long lFirst, double *plCont)
{
// Container vorinitialisieren
	plCont[XMIN_IDX] = plCont[YMIN_IDX] = DBL_MAX;	// enthalten dann Minima
	plCont[XMAX_IDX] = plCont[YMAX_IDX] = -DBL_MAX;	// enthalten dann Maxima

// Container laden
DB_ADDR dbavol(m_hPr), dbakal(m_hPr);
struct vol vol;
struct kal kal;
ErrCode RC;

	dbavol.file_no = VOL;
	dbakal.file_no = KAL;

	dbavol.rec_no = lFirst;
	do {
		__ReadHR (dbavol, vol);	// Verweis auf nächste Kante

	// Zeiger nächste Kante aus KFM
		dbakal.rec_no = labs (vol.zvolk);	// Zeiger auf KAL (+oder-)
		__ReadHR (dbakal, kal);				// Kante lesen

	// Container aktualisieren
		if (plCont[XMIN_IDX] > kal.kcont.kxmin) 
			plCont[XMIN_IDX] = kal.kcont.kxmin;
		if (plCont[XMAX_IDX] < kal.kcont.kxmax) 
			plCont[XMAX_IDX] = kal.kcont.kxmax;
		if (plCont[YMIN_IDX] > kal.kcont.kymin) 
			plCont[YMIN_IDX] = kal.kcont.kymin;
		if (plCont[YMAX_IDX] < kal.kcont.kymax) 
			plCont[YMAX_IDX] = kal.kcont.kymax;

		dbavol.rec_no = vol.znvol;
	} while	(0 != vol.znvol);

	return S_OK;
}

HRESULT CNativeObject::GetMaschenCont (long lFirst, double *plCont)
{
// Container vorinitialisieren
	plCont[XMIN_IDX] = plCont[YMIN_IDX] = DBL_MAX;	// enthalten dann Minima
	plCont[XMAX_IDX] = plCont[YMAX_IDX] = -DBL_MAX;	// enthalten dann Maxima

// Container laden
DB_ADDR dbakfm(m_hPr), dbakal(m_hPr);
struct kfm kfm;
struct kal kal;
ErrCode RC;
long izap, izep, zkl, zkln, zkfn;

	dbakfm.file_no = KFM;
	dbakal.file_no = KAL;

	dbakfm.rec_no = lFirst;
	do {
		__ReadHR (dbakfm, kfm);		// nächste Kante
		zkl = kfm.zkfmk;			// Zeiger auf KAL (+oder-)
		zkfn = kfm.znkfm;

	// Zeiger wieder auf KFM
	// Prüfung, ob Kante des gleichen Randes folgt
		if (0 != zkfn) {
			dbakfm.rec_no = zkfn;
			__ReadHR (dbakfm, kfm);
			zkln = kfm.zkfmk;

		// Zeiger nächste Kante aus KFM
			dbakal.rec_no = labs (zkl);
			__ReadHR (dbakal, kal);			// Kante lesen
			if (zkl < 0) izep = kal.zap;
			else	     izep = kal.zep;

		// Container aktualisieren
			if (plCont[XMIN_IDX] > kal.kcont.kxmin) 
				plCont[XMIN_IDX] = kal.kcont.kxmin;
			if (plCont[XMAX_IDX] < kal.kcont.kxmax) 
				plCont[XMAX_IDX] = kal.kcont.kxmax;
			if (plCont[YMIN_IDX] > kal.kcont.kymin) 
				plCont[YMIN_IDX] = kal.kcont.kymin;
			if (plCont[YMAX_IDX] < kal.kcont.kymax) 
				plCont[YMAX_IDX] = kal.kcont.kymax;

			dbakal.rec_no = labs (zkln);
			__ReadHR (dbakal, kal);			// folgende Kante
			if (zkln < 0) izap = kal.zep;
			else	      izap = kal.zap;

			if (izap != izep) 
				break;	// Ende dieser Masche
		} else {
		// nur eine Kante
			dbakal.rec_no = labs (zkl);
			__ReadHR (dbakal, kal);			// Kante lesen

		// Container aktualisieren
			if (plCont[XMIN_IDX] > kal.kcont.kxmin) 
				plCont[XMIN_IDX] = kal.kcont.kxmin;
			if (plCont[XMAX_IDX] < kal.kcont.kxmax) 
				plCont[XMAX_IDX] = kal.kcont.kxmax;
			if (plCont[YMIN_IDX] > kal.kcont.kymin)	
				plCont[YMIN_IDX] = kal.kcont.kymin;
			if (plCont[YMAX_IDX] < kal.kcont.kymax) 
				plCont[YMAX_IDX] = kal.kcont.kymax;
			break;				// Ende dieser Kante
		}
		dbakfm.rec_no = zkfn;
	} while (TRUE);
	
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Generiert ein neues Punktobjekt 
HRESULT CNativeObject::PutPointObject (long lIdent, LPCSTR pcName, double_v &rX, double_v &rY) 
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;
ErrCode RC;

// Objektsatz lesen/generieren
	if (!m_fIsValid) {
	// neuen ObjektSatz generieren
//		if (VERSION0500000E <= LocGetDBVersion(m_hPr))	// evtl. GUID generieren
//			CoCreateGuid (&OBLSatz.guid);

		__NewHR (dbaOBL, OBLSatz);
		m_lONr = dbaOBL.rec_no;
		_ASSERTE(0 != m_lONr);

		m_fIsValid = true;

	// neuen KoordinatenSatz generieren
		RETURN_FAILED_HRESULT(PutPointGeometry (pcName, rX[0], rY[0]));

	// Identifikator bei Bedarf in IDL eintragen
		if (INVALID_HOBJECTS != (HOBJECTS)lIdent) 
		{
			RETURN_FAILED_HRESULT(PutIdent (lIdent));
		}
	} else {
	// evtl. bestehende Geometrie löschen
		RETURN_FAILED_HRESULT(DeletePointGeometry(pcName));
#if defined(_DEBUG)
		dbaOBL.rec_no = m_lONr;
		__ReadHR(dbaOBL, OBLSatz);
		_ASSERTE(0 == OBLSatz.zokp);		// Objekt darf keine (mehr) PunktGeometrie haben
#endif // _DEBUG

	// neuen KoordinatenSatz generieren
		RETURN_FAILED_HRESULT(PutPointGeometry (pcName, rX[0], rY[0]));

	// IdentifikatorSatz richten
#if defined(_DEBUG)
	HOBJECTS lId = 0L;

		RETURN_FAILED_HRESULT(GetIdent (&lId));
		if (INVALID_HOBJECTS != (HOBJECTS)lIdent) 
		{
			_ASSERTE(lIdent == lId);		// das hier ist _kein_ ModIdent !
		} 
		_ASSERTE(0 != OBLSatz.zoid);

		__ReadHR(dbaOBL, OBLSatz);
		RETURN_FAILED_HRESULT(VerifyIdent(lId, OBLSatz.zoid, OTPunkt));
#else
		if (INVALID_HOBJECTS == (HOBJECTS)lIdent)
			RETURN_FAILED_HRESULT(GetIdent ((HOBJECTS *)&lIdent));

		dbaOBL.rec_no = m_lONr;
		__ReadHR(dbaOBL, OBLSatz);
		RETURN_FAILED_HRESULT(VerifyIdent(lIdent, OBLSatz.zoid, OTPunkt));
#endif // _DEBUG
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geometrie löschen
HRESULT CNativeObject::DeleteGeometry(LPCSTR pcName)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetObjectType (&dwType));
	switch (dwType) {
	case OTPunkt:
	case OTText:
		RETURN_FAILED_HRESULT(DeletePointGeometry(pcName));
		break;

	case OTLinie:
		RETURN_FAILED_HRESULT(DeleteLineGeometry(pcName));
		break;

	case OTFlaeche:
		RETURN_FAILED_HRESULT(DeleteAreaGeometry(pcName));
		break;

	default:
		return E_INVALIDARG;		// Komplexobjekte etc.
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Löschen der Geometrie für einen Punkt
HRESULT CNativeObject::DeletePointGeometry (LPCSTR pcName)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

#if defined(_DEBUG)
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetObjectType (&dwType));
	_ASSERTE(0 == dwType || OTPunkt == dwType || OTText == dwType);		// gegebenes Objekt ist wirklich Punkt-/TextObjekt
#endif // _DEBUG

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
DB_ADDR dbaPOL(m_hPr);
struct obl OBLSatz;
struct pol POLSatz;
ErrCode RC;

// Objektsatz einlesen
	__ReadHR(dbaOBL, OBLSatz);
	if (0 == OBLSatz.zokp)
		return S_FALSE;		// keine Geometrie mehr da

// PunktSatz einlesen
	dbaPOL.file_no = POL;
	dbaPOL.rec_no = OBLSatz.zokp;
	__ReadHR(dbaPOL, POLSatz);

// diverse Tests
	if (0 == POLSatz.zpvgo)
		return HRESULT_FROM_ERRCODE(S_BADPOLVGO);

// Verweis zum Objekt rauslöschen
	RETURN_FAILED_HRESULT(DeleteLink (m_hPr, VGO, &POLSatz.zpvgo, m_lONr));
	if (0 != POLSatz.zpvgo) {
	// nicht einziges Objekt, wegschreiben und raus
		__WriteHR(dbaPOL, POLSatz);

	// ObjektSatz aktualisieren: keine Punktgeometrie mehr
		OBLSatz.zokp = 0;
		__WriteHR(dbaOBL, OBLSatz);
		return S_OK;
	}

// PunktObjekt muß gleichzeitig KnotenPunkt sein
	if (0 != POLSatz.zpkfk) {
	// PunktObjekt ist KnotenPunkt, also als Knoten ablegen
		__DisposeHR(dbaPOL, POLSatz);
		dbaPOL.file_no = KPL;	// jetzt KnotenPunkt
		__NewHR(dbaPOL, POLSatz);

	// ObjektSatz aktualisieren: keine Punktgeometrie mehr
		OBLSatz.zokp = 0;
		__WriteHR(dbaOBL, OBLSatz);
		return S_OK;
	}

// PunktSatz kann nun gelöscht werden
	__DisposeHR(dbaPOL, POLSatz);

// ObjektSatz aktualisieren: keine Punktgeometrie mehr
	OBLSatz.zokp = 0;
	__WriteHR(dbaOBL, OBLSatz);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Generiert einen neuen singulären Punkt 
HRESULT CNativeObject::PutPointGeometry (LPCSTR pcName, double dX, double dY) 
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
DB_ADDR dbaPOL(m_hPr);
struct obl OBLSatz;
struct pol POLSatz;
ErrCode RC;

	__ReadHR(dbaOBL, OBLSatz);

// neuen POLSatz generieren
	dbaPOL.file_no = POL;
	POLSatz.kpkrd.px = ToCoOrd(dX);		// Koordinaten merken
	POLSatz.kpkrd.py = ToCoOrd(dY);
	__NewHR (dbaPOL, POLSatz);

// Rückverkettung der Geometrie in Objektliste vornehmen
	RETURN_FAILED_HRESULT(CreateLink (m_hPr, VGO, &POLSatz.zpvgo, m_lONr));
	__WriteHR(dbaPOL, POLSatz);

// SatzNummer im Objektsatz wegschreiben
	_ASSERTE(0 == OBLSatz.zokp);		// Objekt darf noch keine Punktgeometrie haben

	OBLSatz.zokp = dbaPOL.rec_no;
	__WriteHR(dbaOBL, OBLSatz);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// LinienGeometrien löschen
HRESULT CNativeObject::DeleteLineGeometry (LPCSTR pcName) 
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

#if defined(_DEBUG)
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetObjectType (&dwType));
	_ASSERTE(0 == dwType || OTLinie == dwType);		// gegebenes Objekt ist wirklich Linienobjekt
#endif // _DEBUG

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
DB_ADDR dbaVOL(m_hPr);
struct obl OBLSatz;
struct vol VOLSatz;
ErrCode RC;

// Objektsatz einlesen
	__ReadHR(dbaOBL, OBLSatz);
	if (0 == OBLSatz.zovol)
		return S_FALSE;		// keine Geometrie mehr da

// VerbindungsListe Objekt -> Kante
	dbaVOL.file_no = VOL;
	dbaVOL.rec_no = OBLSatz.zovol;

// Rückverkettung auflösen, Kantenfolge zerlegen
	while (0 != dbaVOL.rec_no) {
		__ReadHR(dbaVOL, VOLSatz);		// VerbindungsSatz lesen

	// Kante löschen
		RETURN_FAILED_HRESULT(DeleteKante(labs(VOLSatz.zvolk)));
		__DisposeHR(dbaVOL, VOLSatz);			// VerbindungsSatz freigeben
		dbaVOL.rec_no = VOLSatz.znvol;	// nächste Kante
	}

// ObjektSatz korrigieren
	OBLSatz.zovol = 0;	// keine Geometrie mehr
	__WriteHR(dbaOBL, OBLSatz);
	return S_OK;
}

HRESULT CNativeObject::DeleteKante (long lKante) 
{
struct kal KALSatz;
DB_ADDR dbaKAL(m_hPr);
ErrCode RC;	// FehlerCode

// KantenSatz einlesen
	dbaKAL.file_no = KAL;
	dbaKAL.rec_no = lKante;
	__ReadHR(dbaKAL, KALSatz);

// ObjektSatz aus Verbindung zur OBL löschen 
	RETURN_FAILED_HRESULT(DeleteLink (m_hPr, VGO, &KALSatz.zkvgo, m_lONr));
	if (0 != KALSatz.zkvgo) {
	// war nicht das letzte Objekt
		__WriteHR(dbaKAL, KALSatz);
	} else if (0 != KALSatz.zlm || 0 != KALSatz.zrm) {
	// war das letzte LinienObjekt, aber Kante gehört noch zu Fläche
		__WriteHR(dbaKAL, KALSatz);
	} else {
	// Kante muß gelöscht werden, Stützpunktfolge löschen
		RETURN_FAILED_HRESULT(DeletePoints (KALSatz.zksp));

	// Anfangs und Endpunkt der Kante behandeln
		RETURN_FAILED_HRESULT(DeleteNode (KALSatz.zap, lKante));
		RETURN_FAILED_HRESULT(DeleteNode (KALSatz.zep, lKante));
	
	// KantenSatz freigeben 
		__DisposeHR(dbaKAL, KALSatz);
	}
	return S_OK;
}

// Löschen der StützpunktFolge einer Kante 
HRESULT CNativeObject::DeletePoints (long lPunkt) 
{
DB_ADDR dbaSPL(m_hPr);
ErrCode RC;	// FehlerCode

	if (VERSION05000010 <= LocGetDBVersion(m_hPr)) {
	struct longspl SPLSatz;

		dbaSPL.file_no = SPL_NEW;
		dbaSPL.rec_no = lPunkt;

	// jetzt einfach alles freigeben
		while (dbaSPL.rec_no > 0) {
			__ReadHR(dbaSPL, SPLSatz);		// Satz lesen
			__DisposeHR(dbaSPL, SPLSatz);	// freigeben
			dbaSPL.rec_no = SPLSatz.znspl;	// nächster Satz
		}
		return S_OK;
	}

// ansonsten mit alter Struktur arbeiten
struct spl SPLSatz;

	dbaSPL.file_no = SPL_OLD;
	dbaSPL.rec_no = lPunkt;
	while (dbaSPL.rec_no > 0) {
		__ReadHR(dbaSPL, SPLSatz);		// Satz lesen
		__DisposeHR(dbaSPL, SPLSatz);	// freigeben
		dbaSPL.rec_no = SPLSatz.znsp;	// nächster Satz
	}
	return S_OK;
}

// Behandeln eines Knotenpunktes 
HRESULT CNativeObject::DeleteNode (long Node, long Kante) 
{
struct kpl KPLSatz;
DB_ADDR dbaKPL(m_hPr);
long RC;	// FehlerCode

// EInlesen des KnotenSatzes
	dbaKPL.file_no = KPL;
	dbaKPL.rec_no = Node;
	__ReadHR(dbaKPL, KPLSatz);

// Herauslöschen der Kante aus Kantenfolge
	RETURN_FAILED_HRESULT(DeleteLink (m_hPr, KFK, &KPLSatz.zkpkfk, Kante));
	if (0 != KPLSatz.zkpkfk) {
	// es sind noch Kanten auf diesem KnotenPunkt
		__WriteHR(dbaKPL, KPLSatz);
	} else if (0 != KPLSatz.zkpvgo) {
	// es war die letzte Kante, aber es sitzt noch ein PunktO drauf
		__WriteHR(dbaKPL, KPLSatz);
	} else {
	// das war die letzte Kante dieses Knotens, und kein PunktO mehr
		__DisposeHR(dbaKPL, KPLSatz);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Container aufbauen 
/* static */
inline void CNativeObject::UpdateContainer (struct kcont *pCont, long x, long y)
{
	if (pCont -> kxmin > x) pCont -> kxmin = x;
	if (pCont -> kxmax < x) pCont -> kxmax = x;
	if (pCont -> kymin > y) pCont -> kymin = y;
	if (pCont -> kymax < y) pCont -> kymax = y;
}

///////////////////////////////////////////////////////////////////////////////
// Winkel zwischen AnfangsPunkt und 2. Punkt einer Kante berechnen 
/* static */
inline long CNativeObject::Winkel (long x1, long y1, long x2, long y2)
{
double rwin;

	if (x2 == x1 && y2 == y1) 
		return 16000L;		// per Definition ist Winkel 0

	rwin = 1.0 + ((double)(x2 - x1) / (double)(labs (x2 - x1) + labs (y2 - y1)));
	return (long)fabs (rwin * 16000.0);
} 

// Schreibt KantenSatz mit allgemeiner Information 
HRESULT CNativeObject::PutKante (
	double *pX, double *pY, long lCnt, long *pKNr, struct kcont *pCont)
{
long iNum = lCnt;
ErrCode RC;
struct kal KALSatz;
DB_ADDR dbaKAL(m_hPr);

// KantenSatz anlegen
	dbaKAL.file_no = KAL;
	__NewHR(dbaKAL, KALSatz);

	KALSatz.kcont.kxmin = MAXKOORD;
	KALSatz.kcont.kymin = MAXKOORD;

// Anfangs-/Endpunkt der Kante anlegen
	RETURN_FAILED_HRESULT(PutKnoten (pX[0], pY[0], dbaKAL.rec_no, &KALSatz.zap));
	UpdateContainer (&KALSatz.kcont, pX[0], pY[0]);
	if (pX[0] != pX[iNum-1] || pY[0] != pY[iNum-1]) {
		RETURN_FAILED_HRESULT(PutKnoten (pX[iNum-1], pY[iNum-1], -dbaKAL.rec_no, &KALSatz.zep));
		UpdateContainer (&KALSatz.kcont, pX[iNum-1], pY[iNum-1]);
	} else {
		RETURN_FAILED_HRESULT(ChainKnoten (KALSatz.zap, -dbaKAL.rec_no));
		KALSatz.zep = KALSatz.zap;
	}

// Stützpunktliste anlegen
	RETURN_FAILED_HRESULT(PutPoints (&pX[1], &pY[1], iNum-2, &KALSatz.zksp, &KALSatz.kcont));

// Anzahl der Stützpunkte und Winkel schreiben
	KALSatz.asp = iNum-2;
	KALSatz.wi = Winkel (pX[iNum-1], pY[iNum-1], pX[iNum-2], pY[iNum-2]);

// erstmal wegschreiben
	__WriteHR(dbaKAL, KALSatz);
	*pKNr = dbaKAL.rec_no;

// evtl. Container kopieren
	if (pCont) 
		memcpy (pCont, &KALSatz.kcont, sizeof (KALSatz.kcont));
	return S_OK;
}

// Generiert einen neuen KnotenPunktSatz 
HRESULT CNativeObject::PutKnoten (double x, double y, long zKPL, long *pKAL)
{
ErrCode RC;
struct kpl KPLSatz;
DB_ADDR dbaKPL(m_hPr);

	*pKAL = 0;		// ausnullen für alle Fälle

// Satz in der KPL neu anlegen
	dbaKPL.file_no = KPL;

	KPLSatz.pkrd.kpx = ToCoOrd(x);
	KPLSatz.pkrd.kpy = ToCoOrd(y);
	RETURN_FAILED_HRESULT(CreateLink (m_hPr, KFK, &KPLSatz.zkpkfk, zKPL));

	__NewHR(dbaKPL, KPLSatz);	// Knoten anlegen

	*pKAL = dbaKPL.rec_no;		// neuer KnotenPunkt
	return S_OK;
}

// Fall geschlossene Kontur (zap == zep) 
HRESULT CNativeObject::ChainKnoten (long lKPL, long lKante)
{
ErrCode RC;
struct kpl KPLSatz;
DB_ADDR dbaKPL(m_hPr);

// KnotenpunktSatz einlesen
	dbaKPL.file_no = KPL;
	dbaKPL.rec_no = lKPL;
	__ReadHR(dbaKPL, KPLSatz);

// letzten Knoten zusätzlich verketten
	THROW_FAILED_HRESULT(CreateLink (m_hPr, KFM, &KPLSatz.zkpkfk, lKante));
	__WriteHR(dbaKPL, KPLSatz);
	return S_OK;
}

// Anlegen der Stützpunktfolge einer Kante 
HRESULT CNativeObject::PutPoints (
	double *pX, double *pY, long iNum, long *pKAL, struct kcont *pCont)
{
ErrCode RC;

// ausnullen des ersten Zeigers
	*pKAL = 0;

	if (VERSION05000010 <= LocGetDBVersion(m_hPr)) {
	DB_ADDR dbaSPL(m_hPr);

	// Neuen Satz in die StützpunktFolge am Anfang einfügen
	// (Koordinaten von hinten bearbeiten)
		dbaSPL.file_no = SPL_NEW;

		for (long i = iNum -1; i >= 0; /**/) {
		struct longspl SPLSatz;

			for (long lCnt = i % NUMSPLCOORDS; lCnt >= 0; lCnt--, i--) {
				SPLSatz.spxl[lCnt] = ToCoOrd(pX[i]);
				SPLSatz.spyl[lCnt] = ToCoOrd(pY[i]);
				UpdateContainer (pCont, pX[i], pY[i]);
			}
			SPLSatz.znspl = *pKAL;

			__NewHR(dbaSPL, SPLSatz);
			*pKAL = dbaSPL.rec_no;
		}
		return S_OK;
	}

// ansonsten mit alter Struktur arbeiten
	for (long i = iNum -1; i >= 0; i--) {
		THROW_FAILED_HRESULT(PutPoint (pX[i], pY[i], pKAL));
		UpdateContainer (pCont, pX[i], pY[i]);
	}
	return S_OK;
}

// Anlegen eines StützPunktSatzes mit Rückverkettung 
HRESULT CNativeObject::PutPoint (double x, double y, long *pSPL)
{
ErrCode RC;
struct spl SPLSatz;
DB_ADDR dbaSPL(m_hPr);

// Neuen Satz in die StützpunktFolge am Anfang einfügen
	dbaSPL.file_no = SPL_OLD;

	SPLSatz.spx = ToCoOrd(x);
	SPLSatz.spy = ToCoOrd(y);
	SPLSatz.znsp = *pSPL;
	__NewHR(dbaSPL, SPLSatz);

	*pSPL = dbaSPL.rec_no;
	return S_OK;
}

// Generieren der Verkettung einer Kante vom und zum Objekt 
HRESULT CNativeObject::LinkKante (long lKante, long *povol)
{
ErrCode RC;
struct kal KALSatz;
DB_ADDR dbaKAL(m_hPr);

// Generieren der Verbindung Objekt -> Kante
	THROW_FAILED_HRESULT(CreateLink (m_hPr, VOL, povol, lKante));

// Generieren der Verkettung Kante -> Objekt
	dbaKAL.file_no = KAL;
	dbaKAL.rec_no = labs (lKante);
	__ReadHR(dbaKAL, KALSatz);

	THROW_FAILED_HRESULT(CreateLink (m_hPr, VGO, &KALSatz.zkvgo, m_lONr));
	__WriteHR(dbaKAL, KALSatz);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Generiert ein neues Linienobjekt 
HRESULT CNativeObject::PutLineObject (
	long lIdent, LPCSTR pcName, double_v &rX, double_v &rY) 
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;
ErrCode RC;
long lKante = 0L;	// neue KantenNummer

// Objektsatz lesen/generieren
	if (!m_fIsValid) {
	// neuen ObjektSatz generieren
//		if (VERSION0500000E <= LocGetDBVersion (m_hPr))	// evtl. GUID generieren
//			CoCreateGuid (&OBLSatz.guid);

		__NewHR(dbaOBL, OBLSatz);
		m_lONr = dbaOBL.rec_no;
		_ASSERTE(0 != m_lONr);

	// Geometrie/neuen KantenSatz generieren
		THROW_FAILED_HRESULT(PutKante (&rX[0], &rY[0], rX.size(), &lKante, NULL));
		THROW_FAILED_HRESULT(LinkKante (lKante, &OBLSatz.zovol));
		__WriteHR(dbaOBL, OBLSatz);	// ObjektSatz nochmal wegschreiben

		m_fIsValid = true;

	// Identifikator bei Bedarf in IDL eintragen
		if (INVALID_HOBJECTS != (HOBJECTS)lIdent) 
		{
			RETURN_FAILED_HRESULT(PutIdent (lIdent));
		}
	} else {
	// evtl. bestehende Geometrie löschen
		RETURN_FAILED_HRESULT(DeleteLineGeometry(pcName));

		dbaOBL.rec_no = m_lONr;
		__ReadHR(dbaOBL, OBLSatz);
		_ASSERTE(0 == OBLSatz.zovol);		// Objekt darf keine (mehr) LinienGeometrie haben

	// neuen KantenSatz generieren
		THROW_FAILED_HRESULT(PutKante (&rX[0], &rY[0], rX.size(), &lKante, NULL));
		THROW_FAILED_HRESULT(LinkKante (lKante, &OBLSatz.zovol));
		__WriteHR(dbaOBL, OBLSatz);	// ObjektSatz nochmal wegschreiben

	// IdentifikatorSatz richten
#if defined(_DEBUG)
	HOBJECTS lId = 0L;

		RETURN_FAILED_HRESULT(GetIdent (&lId));
		if (INVALID_HOBJECTS != (HOBJECTS)lIdent) 
		{
			_ASSERTE(lIdent == lId);		// das hier ist _kein_ ModIdent !
		} 
		_ASSERTE(0 != OBLSatz.zoid);

		__ReadHR(dbaOBL, OBLSatz);
		RETURN_FAILED_HRESULT(VerifyIdent(lId, OBLSatz.zoid, OTLinie));
#else
		if (INVALID_HOBJECTS == (HOBJECTS)lIdent)
			RETURN_FAILED_HRESULT(GetIdent ((HOBJECTS *)&lIdent));

		dbaOBL.rec_no = m_lONr;
		__ReadHR(dbaOBL, OBLSatz);
		RETURN_FAILED_HRESULT(VerifyIdent(lIdent, OBLSatz.zoid, OTLinie));
#endif // _DEBUG
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Flächengeometrie löschen
HRESULT CNativeObject::DeleteAreaGeometry (LPCSTR pcName) 
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

#if defined(_DEBUG)
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetObjectType (&dwType));
	_ASSERTE(0 == dwType || OTFlaeche == dwType);		// gegebenes Objekt ist wirklich Flächenobjekt
#endif // _DEBUG

CActDB ActDB(m_hPr);
struct obl OBLSatz;
struct mal MALSatz;
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
DB_ADDR dbaMAL(m_hPr);
ErrCode RC;	// FehlerCode

// Objektsatz einlesen
	__ReadHR(dbaOBL, OBLSatz);
	if (0 == OBLSatz.zovoma)
		return S_FALSE;		// keine Geometrie mehr da

// FlächenListe einlesen
	dbaMAL.file_no = MAL;
	dbaMAL.rec_no = OBLSatz.zovoma;
	__ReadHR(dbaMAL, MALSatz);

// Verbindung Geometrie -> Objekt auflösen
	{
	struct kfm KFMSatz;
	DB_ADDR dbaKFM(m_hPr);

	// Kantenfolge der Fläche abklappern
		dbaKFM.file_no = KFM;
		dbaKFM.rec_no = MALSatz.zmkfm;
		while (dbaKFM.rec_no != 0) {
		// Kante einlesen
			__ReadHR(dbaKFM, KFMSatz);
		
		// Kante herauslöschen (behandeln)
			RETURN_FAILED_HRESULT(DeleteKanteArea(KFMSatz.zkfmk, OBLSatz.zovoma));

			__DisposeHR(dbaKFM, KFMSatz);	// Satz löschen
			dbaKFM.rec_no = KFMSatz.znkfm;	// nächster Satz
		}
	} 

// FlächenSatz freigeben
	__DisposeHR(dbaMAL, MALSatz);

// ObjektSatz aktualisieren: keine FlächenGeometrie mehr
	OBLSatz.zovoma = 0;
	__WriteHR(dbaOBL, OBLSatz);
	return S_OK;
}

template<class T>
inline void Swap (T &rFirst, T &rSecond)
{
T tmp = rFirst;

	rFirst = rSecond;
	rSecond = tmp;
}

HRESULT CNativeObject::DeleteKanteArea (long lKante, long lFNo) 
{
struct kal KALSatz;
DB_ADDR dbaKAL(m_hPr);
long *pFirst = NULL, *pSecond = NULL;
ErrCode RC;				// FehlerCode

// KantenSatz einlesen
	dbaKAL.file_no = KAL;
	dbaKAL.rec_no = labs (lKante);
	__ReadHR(dbaKAL, KALSatz);

// Unterscheidung linke/rechte Fläche
	if (lKante > 0) {
		pFirst = &KALSatz.zlm;
		pSecond = &KALSatz.zrm;
	} else if (lKante < 0) {
		pFirst = &KALSatz.zrm; 
		pSecond = &KALSatz.zlm;
	} else {
		_ASSERTE(0 != lKante);
		return E_UNEXPECTED;
	}
	_ASSERTE(NULL != pFirst && NULL != pSecond);

// FlächenSatz aus Verbindung der MaschenListen (linke/rechte) löschen 
HRESULT hr = DeleteLink (m_hPr, VZO, pFirst, lFNo);

	if (S_OK != hr) {
	// Falls nichts gefunden wurde, dann kann es sein, daß die Fläche 
	// (Loch) falsch orientiert ist (ohne Verschnitt geladen). Daher 
	// versuchen wir es eben von hinten.
		if (hr == HRESULT_FROM_ERRCODE(S_NOTFOUND)) {
			Swap (pFirst, pSecond);
			RETURN_FAILED_HRESULT(DeleteLink (m_hPr, VZO, pFirst, lFNo));
		} else
			return hr;
	}

	if (0 != *pFirst) {
	// war nicht die letzte Fläche
		__WriteHR(dbaKAL, KALSatz);
	} else if (0 != *pSecond) {
	// die Kante mißbraucht einer von der anderen Seite
		__WriteHR(dbaKAL, KALSatz);
	} else if (0 != KALSatz.zkvgo) {
	// Kante wird von LinienObjekt benutzt
		__WriteHR(dbaKAL, KALSatz);
	} else {
	// Kante muß gelöscht werden, Stützpunktfolge löschen
		RETURN_FAILED_HRESULT(DeletePoints (KALSatz.zksp));
	
	// Anfangs und Endpunkt der Kante behandeln
		RETURN_FAILED_HRESULT(DeleteNode (KALSatz.zap, labs (lKante)));
		RETURN_FAILED_HRESULT(DeleteNode (KALSatz.zep, labs (lKante)));

	// KantenSatz freigeben 
		__DisposeHR(dbaKAL, KALSatz);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Flächengeometrie schreiben
HRESULT CNativeObject::PutMasche (
	double *pX, double *pY, unsigned long *pK, unsigned long iKCnt, long *pzvoma)
{
ErrCode RC;
struct mal MALSatz;
DB_ADDR dbaMAL(m_hPr);
long j = 0;

// neuen MaschenSatz erzeugen
	dbaMAL.file_no = MAL;

// Bearbeiten der einzelnen Konturen
	for (long i = 0; i < iKCnt; i++) {
	long lKNr = 0;
	struct kcont *pCont = (struct kcont *)&MALSatz.mcont;

		RETURN_FAILED_HRESULT(PutKante (&pX[j], &pY[j], pK[i], &lKNr, i ? NULL : pCont));
		RETURN_FAILED_HRESULT(::CreateChainEnd (m_hPr, KFM, &MALSatz.zmkfm, lKNr));
		j += pK[i];
	}
	__NewHR(dbaMAL, MALSatz);

// MaschenSatzNummer liefern
	*pzvoma = dbaMAL.rec_no;
	return S_OK;
}


// Generierung der Verkettung zum und vom Objekt zur Masche 
HRESULT CNativeObject::LinkMasche (long lMasche)
{
long RC;
struct mal MALSatz;
DB_ADDR dbaMAL(m_hPr);

// Verkettung von Masche zu Objekt eintragen
	dbaMAL.file_no = MAL;
	dbaMAL.rec_no = lMasche;
	__ReadHR(dbaMAL, MALSatz);

	MALSatz.zmvgo = m_lONr;
	__WriteHR(dbaMAL, MALSatz);

// Rückverkettung Kanten zu Objekt eintragen
	RETURN_FAILED_HRESULT(LinkKanteM (lMasche, MALSatz.zmkfm));
	return S_OK;
}

// Rückverkettung aller Kanten zum MaschenObjekt 
HRESULT CNativeObject::LinkKanteM (long lMasche, long lKFM)
{
long RC;
struct kfm KFMSatz; 
struct kal KALSatz;
DB_ADDR dbaKFM(m_hPr);
DB_ADDR dbaKAL(m_hPr);
bool fFirst = true;

	dbaKFM.file_no = KFM;
	dbaKAL.file_no = KAL;
	while (lKFM) {
	// VerbindungsSatz lesen
		dbaKFM.rec_no = lKFM;
		__ReadHR(dbaKFM, KFMSatz);
		lKFM = KFMSatz.znkfm;

	// KantenSatz lesen
		dbaKAL.rec_no = KFMSatz.zkfmk;
		__ReadHR(dbaKAL, KALSatz);

	// Rückverkettung eintragen
		if (fFirst) {
		// äußere Kontur positiv, alles andere negativ
			RETURN_FAILED_HRESULT(CreateLink (m_hPr, VZO, &KALSatz.zlm, lMasche));
			fFirst = false;
		} else {
			RETURN_FAILED_HRESULT(CreateLink (m_hPr, VZO, &KALSatz.zrm, lMasche));
		}

	// Kantensatz wieder wegschreiben
		__WriteHR(dbaKAL, KALSatz);
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Generiert ein neues Flächenobjekt
HRESULT CNativeObject::PutAreaObject (
	long lIdent, LPCSTR pcName, double_v &rX, double_v &rY, ulong_v &rKnt) 
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;
ErrCode RC;
long lKante = 0L;	// neue KantenNummer

// Objektsatz lesen/generieren
	if (!m_fIsValid) {
	// ObjektSatz neu erzeugen
//		if (VERSION0500000E <= LocGetDBVersion (m_hPr))	// evtl. GUID generieren
//			CoCreateGuid (&OBLSatz.guid);

		__NewHR(dbaOBL, OBLSatz);
		m_lONr = dbaOBL.rec_no;
		_ASSERTE(0 != m_lONr);

	// Geometrie/neuen KantenSatz generieren
		RETURN_FAILED_HRESULT(PutMasche (&rX[0], &rY[0], &rKnt[0], rKnt.size(), &OBLSatz.zovoma));
		RETURN_FAILED_HRESULT(LinkMasche (OBLSatz.zovoma));
		__WriteHR(dbaOBL, OBLSatz);	// ObjektSatz nochmal wegschreiben

		m_fIsValid = true;

	// Identifikator bei Bedarf in IDL eintragen
		if (INVALID_HOBJECTS != (HOBJECTS)lIdent) 
		{
			RETURN_FAILED_HRESULT(PutIdent (lIdent));
		}
	} else {
	// evtl. bestehende Geometrie löschen
		RETURN_FAILED_HRESULT(DeleteAreaGeometry(pcName));

		dbaOBL.rec_no = m_lONr;
		__ReadHR(dbaOBL, OBLSatz);
		_ASSERTE(0 == OBLSatz.zovoma);		// Objekt darf keine (mehr) FlächenGeometrie haben

	// Geometrie/neuen KantenSatz generieren
		RETURN_FAILED_HRESULT(PutMasche (&rX[0], &rY[0], &rKnt[0], rKnt.size(), &OBLSatz.zovoma));
		RETURN_FAILED_HRESULT(LinkMasche (OBLSatz.zovoma));
		__WriteHR(dbaOBL, OBLSatz);

	// IdentifikatorSatz richten
#if defined(_DEBUG)
	HOBJECTS lId = 0L;

		RETURN_FAILED_HRESULT(GetIdent (&lId));
		if (INVALID_HOBJECTS != (HOBJECTS)lIdent) 
		{
			_ASSERTE(lIdent == lId);		// das hier ist _kein_ ModIdent !
		} 
		_ASSERTE(0 != OBLSatz.zoid);
		RETURN_FAILED_HRESULT(VerifyIdent(lId, OBLSatz.zoid, OTFlaeche));
#else
		if (INVALID_HOBJECTS == (HOBJECTS)lIdent)
			RETURN_FAILED_HRESULT(GetIdent ((HOBJECTS *)&lIdent));
		RETURN_FAILED_HRESULT(VerifyIdent(lIdent, OBLSatz.zoid, OTFlaeche));
#endif // _DEBUG
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Generiert ein neues Flächenobjekt
HRESULT CNativeObject::PutTextObject (
	long lIdent, LPCSTR pcName, double_v &rX, double_v &rY, LPCSTR pcText) 
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;
ErrCode RC;
long lMCode = GetHeaderLong (m_hPr, g_cbTextObjMCode, 99999100L, 10);

// Objektsatz lesen/generieren
	if (!m_fIsValid) {
//		if (VERSION0500000E <= LocGetDBVersion (m_hPr))	// evtl. GUID generieren
//			CoCreateGuid (&OBLSatz.guid);

		__NewHR(dbaOBL, OBLSatz);
		m_lONr = dbaOBL.rec_no;
		_ASSERTE(0 != m_lONr);

	// Geometrie/Text generieren
		RETURN_FAILED_HRESULT(PutPointGeometry (pcName, rX[0], rY[0]));
		RETURN_FAILED_HRESULT(PutTextObjektText (lMCode, pcText));

	// Identifikator bei Bedarf in IDL eintragen
		m_fIsValid = true;
		if (INVALID_HOBJECTS != (HOBJECTS)lIdent) 
		{
			RETURN_FAILED_HRESULT(PutIdent (lIdent));
		}
	} else {
	// evtl. bestehende Geometrie löschen
		RETURN_FAILED_HRESULT(DeleteTextObjectText(lMCode));
		RETURN_FAILED_HRESULT(DeletePointGeometry(pcName));
#if defined(_DEBUG)
		dbaOBL.rec_no = m_lONr;
		__ReadHR(dbaOBL, OBLSatz);
		_ASSERTE(0 == OBLSatz.zokp);		// Objekt darf keine (mehr) LinienGeometrie haben
#endif // _DEBUG

	// Geometrie/Text generieren
		RETURN_FAILED_HRESULT(PutPointGeometry (pcName, rX[0], rY[0]));
		RETURN_FAILED_HRESULT(PutTextObjektText (lMCode, pcText));

	// IdentifikatorSatz richten
#if defined(_DEBUG)
	HOBJECTS lId = 0L;

		RETURN_FAILED_HRESULT(GetIdent (&lId));
		__ReadHR(dbaOBL, OBLSatz);
		if (INVALID_HOBJECTS != (HOBJECTS)lIdent) 
		{
			_ASSERTE(lIdent == lId);		// das hier ist _kein_ ModIdent !
		} 
		_ASSERTE(0 != OBLSatz.zoid);
		RETURN_FAILED_HRESULT(VerifyIdent(lId, OBLSatz.zoid, OTText));
#else
		if (INVALID_HOBJECTS == (HOBJECTS)lIdent)
			RETURN_FAILED_HRESULT(GetIdent ((HOBJECTS *)&lIdent));

		dbaOBL.rec_no = m_lONr;
		__ReadHR(dbaOBL, OBLSatz);
		RETURN_FAILED_HRESULT(VerifyIdent(lIdent, OBLSatz.zoid, OTText));
#endif // _DEBUG
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ObjektSatz erzeugen
HRESULT CNativeObject::CreateObjectTemplate (long lIdent)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;
ErrCode RC;

// Objektsatz lesen/generieren
	if (!m_fIsValid) {
	// neuen ObjektSatz generieren
//		if (VERSION0500000E <= LocGetDBVersion (m_hPr))	// evtl. GUID generieren
//			CoCreateGuid (&OBLSatz.guid);

		__NewHR(dbaOBL, OBLSatz);
		m_lONr = dbaOBL.rec_no;
		_ASSERTE(0 != m_lONr);

		m_fIsValid = true;

	} else {
		RETURN_FAILED_HRESULT(DeleteIdent());		// alten Ident löschen
	}
	
// Identifikator in IDL/Objekt eintragen
	if (INVALID_HOBJECTS != (HOBJECTS)lIdent) 
	{
		RETURN_FAILED_HRESULT(PutIdent (lIdent));
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// allgemeine Geometrieroutine, schreibt Geoemtrie aus eindimensionalem DoubleSafeArray
// ab, welches Wertetripel (X,Y,Z) bzw. (R,H,Z) enthält
HRESULT CNativeObject::PutGeometry (long lIdent, DWORD rgType, LPCSTR pcName, SAFEARRAY *pGeom)
{
	if (NULL == pGeom)
		return E_POINTER;

	COM_TRY {
	double_v vX, vY;
	CScaleHeader Hdr (m_hPr);		// Koordinaten in DB-Koords umrechnen

		switch (rgType) {
		case OTPunkt:
			{
			// Punktobjekte
				THROW_FAILED_HRESULT(CreateVerticesFromSABlob(pGeom, Hdr, vX, 
					vY, NULL, CLSID_TRiASCSPointGeometry));
				_ASSERTE(vX.size() == vY.size() && 1 == vX.size());

				THROW_FAILED_HRESULT(PutPointObject (lIdent, pcName, vX, vY));
			}
			break;

		case OTLinie:
			{
			// Linienobjekte
				THROW_FAILED_HRESULT(CreateVerticesFromSABlob(pGeom, Hdr, vX, 
					vY, NULL, CLSID_TRiASCSPolylineGeometry));
				_ASSERTE(vX.size() == vY.size());

				THROW_FAILED_HRESULT(PutLineObject (lIdent, pcName, vX, vY));
			}
			break;

		case OTFlaeche:
			{
			// Flächenobjekte
			ulong_v vKnt;

				if (!BlobHasBoundaryGeometry (pGeom)) {
					THROW_FAILED_HRESULT(CreateVerticesFromSABlob(pGeom, Hdr, 
						vX, vY, NULL, CLSID_TRiASCSPolygonGeometry));
					_ASSERTE(vX.size() == vY.size());

					vKnt.push_back(vX.size());		// Kantenlänge setzen
				} else {
				vector<BYTE *> vBlobs;
				ulong_v vSizes;
				size_t j = 0;

					THROW_FAILED_HRESULT(CreateArrayFromSABlobBoundary (pGeom, 
						vBlobs, vSizes));
					_ASSERTE(vBlobs.size() == vSizes.size());

					for (size_t iKnt = 0; iKnt < vSizes.size(); iKnt++) {
					size_t iKCnt = vX.size();

						THROW_FAILED_HRESULT(CreateVerticesFromBlob (vBlobs[iKnt], 
							Hdr, vX, vY, NULL, CLSID_TRiASCSPolygonGeometry));
						_ASSERTE(vX.size() == vY.size());

						iKCnt = vX.size() - iKCnt;
						vKnt.push_back(iKCnt);					// immer differenz zu vorheriger kante speichern

						::CoTaskMemFree(vBlobs[iKnt]);			// Speicher wieder freigeben
					}
				}
				THROW_FAILED_HRESULT(PutAreaObject (lIdent, pcName, vX, vY, vKnt));
			}
			break;

		case OTText:
			{
			// Textobjekte
			CMakeBlobs::TEXTBLOBDATA TBD;

				THROW_FAILED_HRESULT(CreateVerticesFromSABlob(pGeom, Hdr, vX, 
					vY, &TBD, CLSID_TRiASCSTextPointGeometry));
				_ASSERTE(vX.size() == vY.size() && 1 == vX.size());

			unsigned char PropertiesBytes[4] = {0, 0, 0, 0};
			os_string str;
			double dAngle = 0.0;

				_ASSERTE(sizeof(long) == sizeof(PropertiesBytes));
				*(long *)PropertiesBytes = TBD.lFlags;

				THROW_FAILED_HRESULT(PutTextObject (lIdent, pcName, vX, vY, 
					TBD.strText.c_str()));
			}
			break;

		default:
			return E_INVALIDARG;		// Komplexobjekte etc.
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 
HRESULT CNativeObject::GetContainer (LPCSTR pcName, double *plCont)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
struct obl OBLSatz;
ErrCode RC;

	__ReadHR(dbaOBL, OBLSatz);

DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetObjectType (&dwType));
	switch (dwType) {
	case OTPunkt:
	case OTText:
		{
		DB_ADDR dbapol(m_hPr, POL, OBLSatz.zokp);
		struct pol POLSatz;

		// Container des Objektes setzen
			__ReadHR (dbapol, POLSatz);
			plCont[0] = plCont[1] = POLSatz.kpkrd.px;
			plCont[2] = plCont[3] = POLSatz.kpkrd.py;
		}
		break;

	case OTLinie:
		RETURN_FAILED_HRESULT(GetKantenCont (OBLSatz.zovol, plCont));
		break;

	case OTFlaeche:
		{
		DB_ADDR dbamal(m_hPr, MAL, OBLSatz.zovoma);
		struct mal mal;

		// Container besorgen
			__ReadHR (dbamal, mal);
			RETURN_FAILED_HRESULT(GetMaschenCont (mal.zmkfm, plCont));
		}
		break;

	default:
		return E_INVALIDARG;		// Komplexobjekte etc.
	}

CScaleHeader Hdr (m_hPr);

	Hdr.UnScale (plCont[0], plCont[2]);	// in RealKoordinaten umrechnen
	Hdr.UnScale (plCont[1], plCont[3]);
	return S_OK;
}

} // namespace trias_nativeobject
