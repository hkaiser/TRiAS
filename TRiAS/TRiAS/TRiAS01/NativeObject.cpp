///////////////////////////////////////////////////////////////////////////////
// @doc 
// @module NativeObject.cpp | Definition of the <c CNativeObject> class

#include "trias01p.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "resource.h"
#include <resstrg.h>

#include <GMObjects/PBasic.tlh>
#pragma warning(disable: 4192)
#import <tlb/tdbgeo.tlb> no_namespace raw_native_types raw_interfaces_only named_guids no_implementation \
	exclude("IPersist", "IPersistMemory")

#include <dbmsg.hmc>
#include <ciid.h>
#include <ActDB.h>
#include <Array.h>
#include <ErrInst.hxx>
#include <DBTypes.h>
#include <NativeObject.h>
#include <NativePbd.h>
#include <HeaderEntry.h>
#include <ScaleHeader.h>
#include <GeometryBlob.h>
#include <ObjGuidHeader.h>

#include "Strings.h"
#include "syncdb.hxx"
#include "ConnectFilterWrappers.h"

#if !defined(_countof)
#define _countof(x)	(sizeof(x)/sizeof(x[0]))
#endif // _countof

using namespace trias_nativeheader;
using namespace trias_geometryblob;
using namespace trias_nativepbd;

/////////////////////////////////////////////////////////////////////////////
// globale Funktionen
BOOL IDLRecIsEmpty (HPROJECT hPr, struct idl *pIdl);

/////////////////////////////////////////////////////////////////////////////
// SmartInterfaces

namespace trias_nativeobject {

CNativeObject::CNativeObject(HPROJECT hPr, long lONr, bool fSupressPossibleError)
	: m_hPr(hPr), m_lONr(lONr), m_fIsValid(false)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (0 != m_lONr) {
	CActDB ActDB(m_hPr);
	DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
	struct obl OBLSatz;
	ErrCode RC = EC_OKAY;

		if (fSupressPossibleError) {
		ErrInstall EI (EC_INVADDR);

			RC = (ErrCode)z_readrec (&dbaOBL, &OBLSatz);
		} else 
			RC = (ErrCode)z_readrec (&dbaOBL, &OBLSatz);

		m_fIsValid = (EC_OKAY != RC) ? false : true;
	}
}

HRESULT CNativeObject::GetObjectType (DWORD *pdwType)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (NULL == pdwType)
		return E_POINTER;
	if (!m_fIsValid)
		return E_UNEXPECTED;

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
struct obl OBLSatz;
ErrCode RC;

	__ReadHR(dbaOBL, OBLSatz);

DWORD dwType = 0;

	if (OBLSatz.status & (SB_TEXTOBJ|SB_TEXTOBJIND)) 
		dwType = OTText;
	else if (OBLSatz.status & SB_SACHOBJ) 
		dwType = OTSachObjekt;
	else if (OBLSatz.rmaske & OREL) 
		dwType = OTKO;
	else if (OBLSatz.zokp) 
		dwType = OTPunkt;
	else if (OBLSatz.zovol) 
		dwType = OTLinie;
	else if (OBLSatz.zovoma) 
		dwType = OTFlaeche;

	*pdwType = dwType;
	return (0 != dwType) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Liefert den Guid des Koordinatensystemes
HRESULT CNativeObject::GetGeometryGuid (LPCSTR pcName, _GUID *pGuid)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
INT_PTR lIdent = 0L;

	RETURN_FAILED_HRESULT(GetIdent(&lIdent));
	return ::GetGeometryGuid (m_hPr, lIdent, pcName, pGuid);
}

/////////////////////////////////////////////////////////////////////////////
// Textmerkmal eines Objektes lesen
HRESULT CNativeObject::GetTextMerkmal (long lMCode, BSTR *pbstrVal)
{
	if (NULL == pbstrVal)
		return E_POINTER;
	*pbstrVal = NULL;

	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
long lTarget = ::GetMerkmalTarget (m_hPr, (void *)m_lONr, TT_Objekt);

	if (-1 == lTarget) return E_UNEXPECTED;

char *pT = NULL;
HRESULT hr = ::GetTextMerkmal (m_hPr, lMCode, lTarget, TT_Objekt, &pT);

	if (SUCCEEDED(hr))
		*pbstrVal = CComBSTR(pT).Detach();

	DELETE_VEC(pT);
	return hr;
}

HRESULT CNativeObject::GetTextMerkmal (long lMCode, os_string &rStr)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
long lTarget = ::GetMerkmalTarget (m_hPr, (void *)m_lONr, TT_Objekt);

	if (-1 == lTarget) return E_UNEXPECTED;

char *pT = NULL;

	try {
		THROW_FAILED_HRESULT(::GetTextMerkmal (m_hPr, lMCode, lTarget, TT_Objekt, &pT));
		rStr = pT;

	} catch (_com_error &e) {
		DELETE_VEC(pT);
		return _COM_ERROR(e);
	} catch (...) {
		DELETE_VEC(pT);
		return E_OUTOFMEMORY;
	}

	DELETE_VEC(pT);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Neues Textmerkmal erzeugen
HRESULT CNativeObject::PutTextMerkmal (long lMCode, BSTR bstrNewText, BOOL fTextMCode)
{
	USES_CONVERSION;
	return PutTextMerkmal(lMCode, (NULL != bstrNewText) ? OLE2A(bstrNewText) : NULL, fTextMCode);
}

HRESULT CNativeObject::PutTextMerkmal (long lMCode, LPCSTR pcNewText, BOOL fTextMCode)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
long lTarget = ::GetMerkmalTarget (m_hPr, (void *)m_lONr, TT_Objekt);

	if (-1 == lTarget) 
		return E_UNEXPECTED;

ErrInstall EI (WC_NOTFOUND);

	::DeleteTextMerkmal (m_hPr, lMCode, lTarget, TT_Objekt, fTextMCode);
	return ::PutTextMerkmal (m_hPr, lMCode, lTarget, TT_Objekt, pcNewText, fTextMCode);
}

/////////////////////////////////////////////////////////////////////////////
// Textmerkmal löschen
HRESULT CNativeObject::DeleteTextMerkmal (long lMCode, BOOL fTextMCode)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
long lTarget = ::GetMerkmalTarget (m_hPr, (void *)m_lONr, TT_Objekt);

	if (-1 == lTarget) 
		return E_UNEXPECTED;

ErrInstall EI (WC_NOTFOUND);

	return ::DeleteTextMerkmal (m_hPr, lMCode, lTarget, TT_Objekt, fTextMCode);
}

/*static*/
HRESULT CNativeObject::FindTextMerkmal (
	HPROJECT hPr, long lMCode, LPCSTR pcPattern, int iMode, 
	HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData)
{
	TX_ASSERT(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

CActDB ActDB(hPr);
vector<unsigned long> Objs;
HRESULT hr = ::FindTextMerkmal (hPr, lMCode, pcPattern, iMode, OBL_OLD, Objs);

	if (FAILED(hr)) {
		if (HRESULT_FROM_ERRCODE(WC_NOTFOUND) == hr)
			return hr;		// do not assert if not found anything
		RETURN_FAILED_HRESULT(hr);
	}
	if (0 == Objs.size())
		return HRESULT_FROM_ERRCODE(WC_NOTFOUND);	// nichts gefunden

	hr = S_OK;		// reinit hr
	for (vector<unsigned long>::iterator it = Objs.begin(); it != Objs.end(); ++it)
	{
		hr = trias_connectfilter::EnumObjectsWrapper (hPr, *it, pFcn, dwData);
		if (S_OK != hr)
			break;		// abgebrochen oder Fehler
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Merkmalstext für Textobjekte besorgen
HRESULT CNativeObject::GetTextObjektText (long lMCode, BSTR *pbstrVal) 
{
	if (NULL == pbstrVal)
		return E_POINTER;
	*pbstrVal = NULL;

os_string str;
HRESULT hr = GetTextObjektText(lMCode, str);

	if (SUCCEEDED(hr)) 
		*pbstrVal = CComBSTR(str.c_str()).Detach();
		
	return hr;
}

HRESULT CNativeObject::GetTextObjektText (long lMCode, os_string &rStr) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL (m_hPr, m_lONr);		// Einlesen des ObjektSatzes
struct obl OBLSatz;
ErrCode RC;			// FehlerCode

	__ReadHR (dbaOBL, OBLSatz);

	if (0 == lMCode)
		lMCode = GetHeaderLong (m_hPr, g_cbTextObjMCode, 99999100L, 10);
	TX_ASSERT(0 != lMCode);

	{
	long lFirstP = OBLSatz.zovom;

		if (LocGetDBVersion(m_hPr) >= VERSION05000008) {
		// neue TextObjekte
		ErrInstall ENF (WC_NOTFOUND);

			if (FAILED(GetVOMMI (&lFirstP, lMCode))) // irgend ein sinnloser Fehler
				return S_FALSE;		// NoFit vortäuschen
		}

	// jetzt versuchen, Text zu lesen
	long lTextLen = 0;

		if (FAILED(::GetTextMerkmalLen(m_hPr, lFirstP, &lTextLen)) || 0 == lTextLen || -1 == lTextLen) {
		ResString resNoText (ResID(IDS_NOTEXT, NULL), 32);

			rStr = resNoText;
			return S_OK;		// noch kein Text eingegeben
		}

	os_string str (g_cbNil);

		if (lTextLen < 0) {
			lTextLen = -lTextLen;	// indirektes Textobjekt
			str = g_cbIndText;
		}

	char *pText = NULL;

		ATLTRY(pText = new char [lTextLen+1]);
		if (NULL == pText) return E_OUTOFMEMORY;

		if (SUCCEEDED(::GetTextFromDBT (m_hPr, lFirstP, pText, lTextLen, TRUE))) {
			pText[lTextLen] = '\0';
			OemToAnsi (pText, pText);
			str += pText;
		}
		
		rStr = str;				// Ergebnis setzten
		DELETE_VEC(pText);
		return S_OK;
	}
	return HRESULT_FROM_ERRCODE(WC_NOTEXTOBJ);
}

HRESULT CNativeObject::DeleteTextObjectText (long lMCode)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);

	if (0 == lMCode)
		lMCode = GetHeaderLong (m_hPr, g_cbTextObjMCode, 99999100L, 10);
	TX_ASSERT(0 != lMCode);

	if (LocGetDBVersion(m_hPr) < VERSION05000008) {
#pragma MESSAGE("TODO: Ganz alte Datenbanken beim Textlöschen unterstützen!")
		TX_ASSERT(LocGetDBVersion(m_hPr) >= VERSION05000008);
		return E_UNEXPECTED;
	} else {
	// einfach nur das Merkmal löschen
		RETURN_FAILED_HRESULT(DeleteTextMerkmal(lMCode, TRUE));
	}
	return S_OK;
}

HRESULT CNativeObject::PutTextObjektText (long lMCode, BSTR bstrVal)
{
	USES_CONVERSION;
	return PutTextObjektText(lMCode, (NULL != bstrVal) ? OLE2A(bstrVal) : NULL);
}

HRESULT CNativeObject::PutTextObjektText (long lMCode, LPCSTR pcText)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);

	if (0 == lMCode)
		lMCode = GetHeaderLong (m_hPr, g_cbTextObjMCode, 99999100L, 10);
	TX_ASSERT(0 != lMCode);

// evtl. indirektes Textobjekt
int iLen = strlen (g_cbIndText);
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
struct obl OBLSatz;
ErrCode RC;
LPCSTR pcTextToStore = pcText;

	__ReadHR(dbaOBL, OBLSatz);
	OBLSatz.status |= SB_TEXTOBJ;	// Objekt ist TextObjekt
	if (strlen(pcText) > iLen && !strncmp(pcText, g_cbIndText, iLen)) {
		OBLSatz.status |= SB_TEXTOBJIND;	// Objekt ist indirektes TextObjekt
		pcTextToStore += iLen;
	}
	__WriteHR(dbaOBL, OBLSatz);				// ObjektSatz wegschreiben

// Merkmal schreiben
	if (LocGetDBVersion(m_hPr) < VERSION05000008) {
#pragma MESSAGE("TODO: Ganz alte Datenbanken beim Textschreiben unterstützen!")
		TX_ASSERT(LocGetDBVersion(m_hPr) >= VERSION05000008);
		return E_UNEXPECTED;
	} else {
		RETURN_FAILED_HRESULT(::PutTextMerkmal (m_hPr, lMCode, m_lONr, OBL_OLD, pcTextToStore, TRUE));
	}
	return S_OK;
}

// Verbindungsdatei zu Merkmalen (VOM) lesen und entspr. Satz suchen
HRESULT CNativeObject::GetVOMMI (long *plFirst, long lMCode) 
{
struct vom VOMSatz;
struct mkl MKLSatz;
DB_ADDR dbaVOM(m_hPr);
DB_ADDR dbaMKL(m_hPr);
long VOMNext = *plFirst;
long VOMPrev;
ErrCode RC;

	dbaVOM.file_no = VOM;
	dbaMKL.file_no = MKL;

	dbaVOM.rec_no = 0;
	do {
	// VOMSatz lesen
		VOMPrev = dbaVOM.rec_no;
		if ((dbaVOM.rec_no = VOMNext) == 0)
			break;	// Ende der Kette: lMCode nicht vorhanden
		__ReadHR (dbaVOM, VOMSatz);

	// MKLSatz lesen
		dbaMKL.rec_no = VOMSatz.zvommk;
		__ReadHR (dbaMKL, MKLSatz);

	// nächster VOMSatz
		VOMNext = VOMSatz.znmk;

	} while (MKLSatz.mk != lMCode);          // bis MKode gefunden

	if (MKLSatz.mk == lMCode) {
		*plFirst = VOMSatz.zvommi;
		return S_OK;
	}
	return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
}

/////////////////////////////////////////////////////////////////////////////
// ObjektGUID verwalten

HRESULT CNativeObject::GetObjectGUID (struct _GUID *pGuid)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (!m_fIsValid)
		return E_UNEXPECTED;

CActDB ActDB(m_hPr);

	if (VERSION0500000E <= LocGetDBVersion(m_hPr)) {
	// GUID's sind direkt in der GeoDB gespeichert
	DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
	struct obl OBLSatz;
	ErrCode RC;

		__ReadHR(dbaOBL, OBLSatz);
		*pGuid = OBLSatz.guid;

	} else {
	// GUID's werden als spezielle Merkmale gehalten
	CObjGuidHeader GuidHdr (m_hPr);
	HRESULT hr = S_FALSE;
	os_string str;
	long lMCode = GuidHdr.GetObjGuidCode();

		if (0 == lMCode) 
			return E_UNEXPECTED;

		if (SUCCEEDED(GetTextMerkmal (lMCode, str))) {
		os_string strGuid("{");
		
			strGuid += str;
			strGuid += "}";

		CIID Guid (strGuid.c_str());

			if (!!Guid) {
				*pGuid = Guid;
				return S_OK;
			}
			TX_ASSERT(!!Guid);

		// und durchfallen
		// ...
		} 

	// alle Fehler definiert behandeln
    BOOL fIsCompound = TRUE;

        GetIsCompoundDB(m_hPr, &fIsCompound);
		if (fIsCompound) {
		CIID Guid;		// neuen Guid erzeugen
		os_string subGuid = Guid;

		// '{' und '}' entfernen, damit es genau 36 Zeichen werden (kein FolgeSatz in der DB)
			subGuid = subGuid.substr (1, 36);
			RETURN_FAILED_HRESULT(PutTextMerkmal (lMCode, subGuid.c_str()));

			memcpy (pGuid, &Guid, sizeof(GUID));
		}
	}
	return S_OK;
}

HRESULT CNativeObject::SetObjectGUID (const _GUID &rGuid)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (!m_fIsValid)
		return E_UNEXPECTED;

CActDB ActDB(m_hPr);

	if (VERSION0500000E <= LocGetDBVersion(m_hPr)) {
	// GUID's sind direkt in der GeoDB gespeichert
	INT_PTR lTarget = 0L;
	HRESULT hr = FindObjectFromGUID (m_hPr, rGuid, &lTarget);

		if (SUCCEEDED(hr)) 
			return (lTarget == m_lONr) ? S_OK : HRESULT_FROM_ERRCODE(S_DUPLICATE);

	DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
	struct obl OBLSatz;
	ErrCode RC;

		__ReadHR (dbaOBL, OBLSatz);
		
	ErrInstall Duplicate (WC_DUPLICATE);		// GUID muß unique sein

		OBLSatz.guid = rGuid;
		__WriteHR(dbaOBL, OBLSatz);
		
	} else {
	// GUID's werden als spezielle Merkmale gehalten
	CObjGuidHeader GuidHdr (m_hPr);
	long lMCode = GuidHdr.GetObjGuidCode();

		if (0 == lMCode) return E_UNEXPECTED;

	// erstmal feststellen, on dieser Guid noch nicht vertreten ist
	INT_PTR lTarget = 0L;
	HRESULT hr = FindObjectFromGUID (m_hPr, rGuid, &lTarget);

		if (SUCCEEDED(hr)) 
			return (lTarget == m_lONr) ? S_OK : HRESULT_FROM_ERRCODE(WC_DUPLICATE);

	// jetzt wirklich schreiben
	CIID Guid (rGuid);

	// '{' und '}' entfernen, damit es genau 36 Zeichen werden (kein FolgeSatz in der DB)
	os_string subGuid = Guid;

		subGuid = subGuid.substr (1, 36);
		RETURN_FAILED_HRESULT(PutTextMerkmal (lMCode, subGuid.c_str()));
	}
	return S_OK;
}

/*static*/
HRESULT CNativeObject::FindObjectFromGUID (HPROJECT hPr, const _GUID &rGuid, INT_PTR *plONr)
{
	TX_ASSERT(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

CActDB ActDB(hPr);

	if (VERSION0500000E <= LocGetDBVersion(hPr)) {
	// GUID's sind direkt in der GeoDB gespeichert
	DB_ADDR_OBL dbaOBL(hPr);
	ErrInstall EI (WC_NOTFOUND);
	ErrCode RC;
	
		DBASSERTHR(z_keyfind (&dbaOBL, GUIDKEY, (LPVOID)&rGuid));
		if (trias_connectfilter::ApplyConnectFilter(hPr, dbaOBL.rec_no))
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

		*plONr = dbaOBL.rec_no;
	} 
	else {
	// GUID's werden als spezielle Merkmale gehalten
	CObjGuidHeader GuidHdr (hPr);
	long lMCode = GuidHdr.GetObjGuidCode();

		if (0 == lMCode) return E_UNEXPECTED;

	vector <unsigned long> Objs;
	CIID Guid (rGuid);
	// '{' und '}' entfernen, damit es genau 36 Zeichen werden (kein FolgeSatz in der DB)
	os_string subGuid = Guid;

		subGuid = subGuid.substr (1, 36);
	
	HRESULT hr = ::FindTextMerkmal (hPr, lMCode, subGuid.c_str(), SMExactMatch, OBL_OLD, Objs);

		if (FAILED(hr)) 
			return hr;

		if (1 != Objs.size())
			return E_UNEXPECTED;
		*plONr = Objs[0];
	}
	return S_OK;
}

HRESULT CNativeObject::CreateObjTemplate (long lIdent, INT_PTR *plONr)
{
	TX_ASSERT(NULL != m_hPr);
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

		__NewHR (dbaOBL, OBLSatz);
		m_lONr = dbaOBL.rec_no;
		TX_ASSERT(0 != m_lONr);

		m_fIsValid = true;

	} else if (INVALID_HOBJECTS != (HOBJECTS)lIdent) {
	// ObjektSatz einlesen, Objekt neu bilden
		RETURN_FAILED_HRESULT(DeleteIdent());		// alten Ident löschen
	}
	
// Identifikator in IDL eintragen
	if (INVALID_HOBJECTS != (HOBJECTS)lIdent)
	{
		RETURN_FAILED_HRESULT (PutIdent (lIdent));
	}
	if (NULL != plONr)
		*plONr = m_lONr;		// ObjektNummer liefern
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Identifikator behandeln
HRESULT CNativeObject::GetIdent (INT_PTR *plIdent)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
ErrCode RC;

// Objektsatz einlesen
struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);

	__ReadHR (dbaOBL, OBLSatz);

// wenn lediglich getestet werden soll, ob ident bereits existiert, dann dieses tun
	if (NULL == plIdent)
		return (0 != OBLSatz.zoid) ? S_OK : S_FALSE;

// IdentifikatorSatz lesen
DB_ADDR_IDL dbaIDL(m_hPr);
struct idl IDLSatz;

//	dbaIDL.file_no = IDL;
	dbaIDL.rec_no = OBLSatz.zoid;
	__ReadHR (dbaIDL, IDLSatz);

	*plIdent = IDLSatz.idn;		// Identifikator liefern
	return S_OK;
}

HRESULT CNativeObject::ModifyIdent (long lIdent, long *plOldIdent)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	RETURN_FAILED_HRESULT(DeleteIdent (plOldIdent));
	RETURN_FAILED_HRESULT(PutIdent (lIdent));
	return S_OK;
}

HRESULT CNativeObject::PutIdent (long lIdent, long *plOldIdent)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
struct idl IDLSatz;
DB_ADDR_IDL dbaIDL(m_hPr);
ErrCode RC;                 // FehlerVariable

// IdentifikatorSatz suchen und ggf. neu generieren
//	dbaIDL.file_no = IDL;

ErrInstall EI (WC_NOTFOUND);
long lOldIdent = 0L;

	if ((RC = (ErrCode)z_keyfind (&dbaIDL, IDN_OLD, &lIdent)) != S_OKAY) {
		if (RC == WC_NOTFOUND) {
		// erstes Objekt mit diesem Ident
			IDLSatz.idn = lIdent;
			__NewHR (dbaIDL, IDLSatz);
		} else
			return HRESULT_FROM_ERRCODE(RC);
	} else {
	// nicht erstes Objekt: IDLSatz einlesen
		__ReadHR (dbaIDL, IDLSatz);
		lOldIdent = IDLSatz.idn;
	}

// Objekt in entsprechende Verbindungsliste eintragen
	if (VERSION0500000E <= LocGetDBVersion (m_hPr)) {
	// feststellen, ob dieses Objekt schon in der allgemeinen Liste hängt
	LINKTYPE rgLink = LINKTYPE_Unknown;

		if (S_OK == ::TestDBLinkVIO (m_hPr, IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_DontCare, &rgLink)) 
		{
			if (LINKTYPE_Unknown == rgLink)
				::DeleteLinkVIO (m_hPr, &IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_Unknown);		// rausnehmen und vorne dran neu wegspeichern (s.u.)
		}

	// neu einhängen
	DWORD dwType = 0;

		RETURN_FAILED_HRESULT(GetObjectType (&dwType));
		switch (dwType) {
		case OTPunkt:
			RETURN_FAILED_HRESULT(::CreateLinkVIO (m_hPr, &IDLSatz.zpvio, m_lONr, lIdent, LINKTYPE_Point));
			IDLSatz.lpvio++;
			break;

		case OTLinie:
			RETURN_FAILED_HRESULT(::CreateLinkVIO (m_hPr, &IDLSatz.zlvio, m_lONr, lIdent, LINKTYPE_Line));
			IDLSatz.llvio++;
			break;

		case OTFlaeche:
			RETURN_FAILED_HRESULT(::CreateLinkVIO (m_hPr, &IDLSatz.zfvio, m_lONr, lIdent, LINKTYPE_Area));
			IDLSatz.lfvio++;
			break;

		case OTText:
			RETURN_FAILED_HRESULT(::CreateLinkVIO (m_hPr, &IDLSatz.ztvio, m_lONr, lIdent, LINKTYPE_Text));
			IDLSatz.ltvio++;
			break;

		case OTKO:
			RETURN_FAILED_HRESULT(::CreateLinkVIO (m_hPr, &IDLSatz.zkvio, m_lONr, lIdent, LINKTYPE_Complex));
			IDLSatz.lkvio++;
			break;

		default:		// unbekannter Objekttyp
		case OTSachObjekt:
			RETURN_FAILED_HRESULT(::CreateLinkVIO (m_hPr, &IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_Unknown));
			break;
		}
	} else {
		if (S_OK != ::TestDBLink (m_hPr, VIO_OLD, IDLSatz.zvio, m_lONr)) 
		{
			RETURN_FAILED_HRESULT(::CreateLink (m_hPr, VIO_OLD, &IDLSatz.zvio, m_lONr));
		}
	}
	__WriteHR (dbaIDL, IDLSatz);

// evtl. Ident liefern
	if (NULL != plOldIdent)
		*plOldIdent = lOldIdent;

// neuen Ident in Objektsatz schreiben
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;

	dbaOBL.rec_no = m_lONr;
	__ReadHR(dbaOBL, OBLSatz);
	OBLSatz.zoid = dbaIDL.rec_no;
	__WriteHR(dbaOBL, OBLSatz);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objekt an der richtigen Kette im IdentifikatorSatz einhängen
HRESULT CNativeObject::VerifyIdent (long lIdent, long lIdRec, DWORD rgOTyp)
{
// nur bei neuen Datenbanken
	if (VERSION0500000E > LocGetDBVersion (m_hPr))
		return S_OK;

// feststellen, ob dieses Objekt schon in der gewünschten Liste hängt
// ggf. dieses neu einhängen
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
struct idl IDLSatz;
DB_ADDR_IDL dbaIDL(m_hPr);
ErrCode RC;

//	dbaIDL.file_no = IDL;
	dbaIDL.rec_no = lIdRec;
	__ReadHR(dbaIDL, IDLSatz);

	switch (rgOTyp) {
	case OTPunkt:
		{
			if (S_OK == TestDBLinkVIO (m_hPr, IDLSatz.zpvio, m_lONr, lIdent, LINKTYPE_Point, NULL))
				return S_OK;

			if (S_OK != TestDBLinkVIO (m_hPr, IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_Unknown, NULL))
				return HRESULT_FROM_ERRCODE(EC_BADLINK);

			RETURN_FAILED_HRESULT(DeleteLinkVIO (m_hPr, &IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_Unknown));		// hier rausnehmen		
			RETURN_FAILED_HRESULT(CreateLinkVIO (m_hPr, &IDLSatz.zpvio, m_lONr, lIdent, LINKTYPE_Point));
			IDLSatz.lpvio++;
		}
		break;

	case OTLinie:
		{
			if (S_OK == TestDBLinkVIO (m_hPr, IDLSatz.zlvio, m_lONr, lIdent, LINKTYPE_Line, NULL))
				return S_OK;

			if (S_OK != TestDBLinkVIO (m_hPr, IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_Unknown, NULL))
				return HRESULT_FROM_ERRCODE(EC_BADLINK);

			RETURN_FAILED_HRESULT(DeleteLinkVIO (m_hPr, &IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_Unknown));		// hier rausnehmen		
			RETURN_FAILED_HRESULT(CreateLinkVIO (m_hPr, &IDLSatz.zlvio, m_lONr, lIdent, LINKTYPE_Line));
			IDLSatz.llvio++;
		}
		break;
	
	case OTFlaeche:
		{
			if (S_OK == TestDBLinkVIO (m_hPr, IDLSatz.zfvio, m_lONr, lIdent, LINKTYPE_Area, NULL))
				return S_OK;

			if (S_OK != TestDBLinkVIO (m_hPr, IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_Unknown, NULL))
				return HRESULT_FROM_ERRCODE(EC_BADLINK);

			RETURN_FAILED_HRESULT(DeleteLinkVIO (m_hPr, &IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_Unknown));		// hier rausnehmen		
			RETURN_FAILED_HRESULT(CreateLinkVIO (m_hPr, &IDLSatz.zfvio, m_lONr, lIdent, LINKTYPE_Area));
			IDLSatz.lfvio++;
		}
		break;
	
	case OTText:
		{
			if (S_OK == TestDBLinkVIO (m_hPr, IDLSatz.ztvio, m_lONr, lIdent, LINKTYPE_Text, NULL))
				return S_OK;

			if (S_OK != TestDBLinkVIO (m_hPr, IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_Unknown, NULL))
				return HRESULT_FROM_ERRCODE(EC_BADLINK);

			RETURN_FAILED_HRESULT(DeleteLinkVIO (m_hPr, &IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_Unknown));		// hier rausnehmen		
			RETURN_FAILED_HRESULT(CreateLinkVIO (m_hPr, &IDLSatz.ztvio, m_lONr, lIdent, LINKTYPE_Text));
			IDLSatz.ltvio++;
		}
		break;
	
	case OTKO:
		{
			if (S_OK == TestDBLinkVIO (m_hPr, IDLSatz.zkvio, m_lONr, lIdent, LINKTYPE_Complex, NULL))
				return S_OK;

			if (S_OK != TestDBLinkVIO (m_hPr, IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_Unknown, NULL))
				return HRESULT_FROM_ERRCODE(EC_BADLINK);

			RETURN_FAILED_HRESULT(DeleteLinkVIO (m_hPr, &IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_Unknown));		// hier rausnehmen		
			RETURN_FAILED_HRESULT(CreateLinkVIO (m_hPr, &IDLSatz.zkvio, m_lONr, lIdent, LINKTYPE_Complex));
			IDLSatz.lkvio++;
		}
		break;

	default:		// unbekannter Objekttyp
	case OTSachObjekt:
		return HRESULT_FROM_ERRCODE(EC_BADLINK);
	}

	__WriteHR(dbaIDL, IDLSatz);
	return S_OK;
}

HRESULT CNativeObject::DeleteIdent (long *plOldIdent)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
ErrCode RC;

// 1. ObjektSatz einlesen
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
struct obl OBLSatz;

// Objektsatz einlesen
	__ReadHR (dbaOBL, OBLSatz);

// IdentifikatorSatz lesen
DB_ADDR_IDL dbaIDL(m_hPr, OBLSatz.zoid);
struct idl IDLSatz;

	__ReadHR (dbaIDL, IDLSatz);

long lIdent = IDLSatz.idn;		// behandelter Identifikator

	if (VERSION0500000E <= LocGetDBVersion(m_hPr)) {
	DWORD dwType = 0;
	HRESULT hr = HRESULT_FROM_ERRCODE(WC_NOTFOUND);

		RETURN_FAILED_HRESULT(GetObjectType (&dwType));
		switch (dwType) {
		case OTPunkt:
			hr = ::DeleteLinkVIO (m_hPr, &IDLSatz.zpvio, m_lONr, lIdent, LINKTYPE_Point);
			if (SUCCEEDED(hr)) {
				IDLSatz.lpvio--;

				TX_ASSERT(0 <= IDLSatz.lpvio);
				TX_ASSERT(0 != IDLSatz.zpvio || 0 == IDLSatz.lpvio);
			}		
			break;

		case OTLinie:
			hr = ::DeleteLinkVIO (m_hPr, &IDLSatz.zlvio, m_lONr, lIdent, LINKTYPE_Line);
			if (SUCCEEDED(hr)) {
				IDLSatz.llvio--;

				TX_ASSERT(0 <= IDLSatz.llvio);
				TX_ASSERT(0 != IDLSatz.zlvio || 0 == IDLSatz.llvio);
			}
			break;

		case OTFlaeche:
			hr = ::DeleteLinkVIO (m_hPr, &IDLSatz.zfvio, m_lONr, lIdent, LINKTYPE_Area);
			if (SUCCEEDED(hr)) {
				IDLSatz.lfvio--;

				TX_ASSERT(0 <= IDLSatz.lfvio);
				TX_ASSERT(0 != IDLSatz.zfvio || 0 == IDLSatz.lfvio);
			}
			break;

		case OTText:
			hr = ::DeleteLinkVIO (m_hPr, &IDLSatz.ztvio, m_lONr, lIdent, LINKTYPE_Text);
			if (SUCCEEDED(hr)) {
				IDLSatz.ltvio--;

				TX_ASSERT(0 <= IDLSatz.ltvio);
				TX_ASSERT(0 != IDLSatz.ztvio || 0 == IDLSatz.ltvio);
			} 
			break;

		case OTKO:
			hr = ::DeleteLinkVIO (m_hPr, &IDLSatz.zkvio, m_lONr, lIdent, LINKTYPE_Complex);
			if (SUCCEEDED(hr)) {
				IDLSatz.lkvio--;

				TX_ASSERT(0 <= IDLSatz.lkvio);
				TX_ASSERT(0 != IDLSatz.zkvio || 0 == IDLSatz.lkvio);
			} 
			break;

		case OTSachObjekt:
		default:
			hr = ::DeleteLinkVIO (m_hPr, &IDLSatz.zvio, m_lONr, lIdent, LINKTYPE_Unknown);
			break;
		}
		if (FAILED(hr))
			return hr;		// nichts gefunden oder Fehler

	} else {
	// ON aus Verbindungsdatei VIO löschen
		RETURN_FAILED_HRESULT(::DeleteLink (m_hPr, VIO_OLD, &IDLSatz.zvio, m_lONr));
	}

// testen, ob keine Merkmale und keine Relationen mehr vorhanden sind
	if (::IDLRecIsEmpty (m_hPr, &IDLSatz)) {
		// einziges (und letztes) Objekt --> IDL freigeben
		__DisposeHR (dbaIDL, IDLSatz);
	} else {
	// modifizierten Satz wegschreiben
		__WriteHR (dbaIDL, IDLSatz);
	}

// Identifikator am Objektsatz löschen
	OBLSatz.zoid = 0L;
	__WriteHR(dbaOBL, OBLSatz);

// evtl. alten Identifikator liefern
	if (NULL != plOldIdent)
		*plOldIdent = lIdent;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objekt löschen
HRESULT CNativeObject::Delete (BOOL fDelRelated)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr);

// Relationen behandeln
	if (fDelRelated) {		// 1. evtl. Textobjekt rauswerfen
	INT_PTR lAssocON = AssociatedObject();

		if (lAssocON < 0) {
		// BegleitRelation auflösen
			RETURN_FAILED_HRESULT(DeleteRelation (-lAssocON, 0, BRELA));

		// TextObjekt vollständig löschen
		CNativeObject Text (m_hPr, -lAssocON);

			RETURN_FAILED_HRESULT(Text.Delete (FALSE));

		} else if (lAssocON > 0) {
		// Objekt ist abhängiges Begleitobjekt
			RETURN_FAILED_HRESULT(DeleteRelation (lAssocON, 0, BRELP));
		}
	}

// 2. alle anderen Relationen, die dieses Objekt hat löschen
	RETURN_FAILED_HRESULT(DeleteAllRelations());

// 3. Merkmale löschen 
HRESULT hr = S_OK;

	while (S_OK == (hr = DeleteTextMerkmal(-1L)))
		;
	if (FAILED(hr)) return hr;

	RETURN_FAILED_HRESULT(DeleteIdent());	// Identifikator löschen
	DeleteGeometry(NULL);					// Geometrie löschen
		// Fehler nicht auswerten, da sonst 'Leichen' (ohne Geometrie) nicht 
		// entfernt werden können

// ObjektSatz löschen
ErrCode RC;

	dbaOBL.rec_no = m_lONr;
	__DisposeHR(dbaOBL, obl());

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Enumeration aller Merkmale eines Objektes
HRESULT CNativeObject::EnumRelatedMCodes (
	HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
ErrCode RC;		// FehlerCode
bool fText = false;

// Objektsatz einlesen
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;

	dbaOBL.rec_no = m_lONr;
	__ReadHR(dbaOBL, OBLSatz);

	if (LocGetDBVersion(m_hPr) < VERSION05000008 && OBLSatz.status & SB_TEXTOBJ)
		return S_FALSE;

	if (OBLSatz.status & SB_TEXTOBJIND)
		fText = true;

long lVOMNext = OBLSatz.zovom;

// Merkmale der Reihe nach einlesen
DB_ADDR dbaMKL(m_hPr);
struct mkl MKLSatz;
HPROJECT hPrPbd = NULL;
HRESULT hr = S_OK;

	if (!GetRelatedProject (m_hPr, &hPrPbd)) 
		return E_UNEXPECTED;

DB_ADDR dbaVOM(m_hPr);
struct vom VOMSatz;

	dbaMKL.file_no = MKL;
	dbaVOM.file_no = VOM;
	VOMSatz.znmk = lVOMNext;
	while (0 != (dbaVOM.rec_no = VOMSatz.znmk)) {
		__ReadHR(dbaVOM, VOMSatz);

		dbaMKL.rec_no = VOMSatz.zvommk;
		__ReadHR(dbaMKL, MKLSatz);

	// MerkmalsCodes enumerieren
		{
		CNativePbdMerkmal Merkmal(hPrPbd, MKLSatz.mk, NULL, FALSE); 
		DWORD dwType = Merkmal.GetFullType();
		
			if (!fText)
				dwType &= ~CNativePbdMerkmal::PBDFEATURETYPE_TextFeature;

			hr = pFcn (Merkmal.GetCode(), dwType, dwData);
			if (S_OK != hr) 
				break;
		}
	}
	return hr;
}

HRESULT CNativeObject::GetCreationDate(DATE *pdCreate)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (NULL == pdCreate)
		return E_POINTER;
	*pdCreate = 0;

	if (LocGetDBVersion(m_hPr) < VERSION05000013)
		return S_FALSE;

CActDB ActDB(m_hPr);
ErrCode RC;		// FehlerCode

// Objektsatz einlesen
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;

	dbaOBL.rec_no = m_lONr;
	__ReadHR(dbaOBL, OBLSatz);

	*pdCreate = OBLSatz.oblcreate;
	return S_OK;
}

HRESULT CNativeObject::GetModificationDate(DATE *pdCreate)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (NULL == pdCreate)
		return E_POINTER;
	*pdCreate = 0;

	if (LocGetDBVersion(m_hPr) < VERSION05000013)
		return S_FALSE;

CActDB ActDB(m_hPr);
ErrCode RC;		// FehlerCode

// Objektsatz einlesen
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;

	dbaOBL.rec_no = m_lONr;
	__ReadHR(dbaOBL, OBLSatz);

	*pdCreate = OBLSatz.oblmodify;
	return S_OK;
}

} // namespace trias_nativeobject

HRESULT DeleteLinkVIO (HPROJECT hPr, long *pBegin, long lWert, long lIdent, LINKTYPE rgLink) 
{
long lVersion = LocGetDBVersion(hPr);

	if (VERSION0500000F <= lVersion) {
	// Rückverkettung Identifikator --> Objekt ist jetzt indiziert (IDENTBSatz)
	DB_ADDR dbaIDENTB (hPr);
	LINKTYPE rgType = rgLink;
	ErrCode RC;

		if (LINKTYPE_DontCare == rgLink)
			rgType = LINKTYPE_Unknown;

		dbaIDENTB.file_no = VIO_NEW;

		if (VERSION05000011 <= lVersion) {
		// Elemente des Keys jetzt getauscht
		struct identx::identxkey keyx;

			keyx.zvioox = TYPETOLINK(lWert, rgType);
			keyx.identx = lIdent;

		// versuchen den VerbindungsSatz wiederzufinden
			RC = (ErrCode)z_keyfind (&dbaIDENTB, IDENTX, &keyx);
			if (WC_NOTFOUND == RC) {
				if (LINKTYPE_DontCare != rgLink)
					return HRESULT_FROM_ERRCODE(RC);		// gesucht und nichts gefunden

			// wenn nichts gefunden wurde, dann auf nächsten positionieren
				RETURN_FAILED_HRESULT(z_keynext (&dbaIDENTB, IDENTX));
				RETURN_FAILED_HRESULT(z_keyread (hPr, &keyx));
				if (keyx.identx != lIdent || LINKTOLINK(keyx.zvioox) != lWert || LINKTOTYPE(keyx.zvioox) != rgLink)
					return HRESULT_FROM_ERRCODE(WC_NOTFOUND);		// nichts gefunden
			}
		} else {
		// alles wie bisher
		struct identb::identbkey key;

			key.zviook = TYPETOLINK(lWert, rgType);
			key.identk = lIdent;

		// versuchen den VerbindungsSatz wiederzufinden
			RC = (ErrCode)z_keyfind (&dbaIDENTB, IDENTB, &key);
			if (WC_NOTFOUND == RC) {
				if (LINKTYPE_DontCare != rgLink)
					return HRESULT_FROM_ERRCODE(RC);		// gesucht und nichts gefunden

			// wenn nichts gefunden wurde, dann auf nächsten positionieren
				RETURN_FAILED_HRESULT(z_keynext (&dbaIDENTB, IDENTB));
				RETURN_FAILED_HRESULT(z_keyread (hPr, &key));
				if (key.identk != lIdent || LINKTOLINK(key.zviook) != lWert || LINKTOTYPE(key.zviook) != rgLink)
					return HRESULT_FROM_ERRCODE(WC_NOTFOUND);		// nichts gefunden
			}
		}

		if (S_OK != RC)
			return HRESULT_FROM_ERRCODE(RC);		// sonstiger Fehler

	struct identb VIOSatz;

		__ReadHR (dbaIDENTB, VIOSatz);

#if defined(_DEBUG)
	long lCurrent = dbaIDENTB.rec_no;
#endif // _DEBUG
	long lPrev = VIOSatz.zviopk;
	long lNext = VIOSatz.zvionk;

		__DisposeHR(dbaIDENTB, VIOSatz);	// aktuellen Satz freigeben

	// vorhergehenden Satz lesen, korrigieren und wegschreiben
		if (0 != lPrev) {
			dbaIDENTB.rec_no = lPrev;
			__ReadHR(dbaIDENTB, VIOSatz);
		
			TX_ASSERT(VIOSatz.zvionk == lCurrent);
			VIOSatz.zvionk = lNext;
			__WriteHR(dbaIDENTB, VIOSatz);
		} else
			*pBegin = lNext;

	// nachfolgenden Satz lesen, korrigieren und wegschreiben
		if (0 != lNext) {
			dbaIDENTB.rec_no = lNext;
			__ReadHR(dbaIDENTB, VIOSatz);
		
			TX_ASSERT(VIOSatz.zviopk == lCurrent);
			VIOSatz.zviopk = lPrev;
			__WriteHR(dbaIDENTB, VIOSatz);
		}
		return S_OK;
	}

// ansonsten alles beim Alten
	return ::DeleteLink (hPr, VIO_OLD, pBegin, lWert);
}

HRESULT CreateLinkVIO (HPROJECT hPr, long *pBegin, long lWert, long lIdent, LINKTYPE rgLink) 
{
long lVersion = LocGetDBVersion(hPr);

	if (VERSION0500000F <= lVersion) {
	// Rückverkettung Merkmal --> Objekt ist jetzt indiziert (MCODEBSatz)
	DB_ADDR dbaIDENTB (hPr);
	ErrCode RC;

		dbaIDENTB.file_no = VIO_NEW;
		if (VERSION05000011 <= lVersion) {
		// Elemente im Key jetzt getauscht
		struct identx IDENTBSatz;

			IDENTBSatz.identxkey.zvioox = TYPETOLINK(lWert, rgLink);	// TargetSatz 
			IDENTBSatz.identxkey.identx = lIdent;						// Identifikator
			IDENTBSatz.zvionk = *pBegin;		// altes erstes Element

			*pBegin = 0;						// für alle Fälle Nullsetzen
			__NewHR (dbaIDENTB, IDENTBSatz);	// neues Satz generieren (incl. Index)
			*pBegin = dbaIDENTB.rec_no;			// neues erstes Element

			if (0 != IDENTBSatz.zvionk) {
			// Rückverkettung eintragen
				dbaIDENTB.rec_no = IDENTBSatz.zvionk;
				__ReadHR(dbaIDENTB, IDENTBSatz);

				TX_ASSERT(0 == IDENTBSatz.zviopk);
				IDENTBSatz.zviopk = *pBegin;
				__WriteHR(dbaIDENTB, IDENTBSatz);
			}
		} else {
		// alles wie bisher
		struct identb IDENTBSatz;

			IDENTBSatz.identbkey.zviook = TYPETOLINK(lWert, rgLink);	// TargetSatz 
			IDENTBSatz.identbkey.identk = lIdent;						// Identifikator
			IDENTBSatz.zvionk = *pBegin;		// altes erstes Element

			*pBegin = 0;						// für alle Fälle Nullsetzen
			__NewHR (dbaIDENTB, IDENTBSatz);	// neues Satz generieren (incl. Index)
			*pBegin = dbaIDENTB.rec_no;			// neues erstes Element

			if (0 != IDENTBSatz.zvionk) {
			// Rückverkettung eintragen
				dbaIDENTB.rec_no = IDENTBSatz.zvionk;
				__ReadHR(dbaIDENTB, IDENTBSatz);

				TX_ASSERT(0 == IDENTBSatz.zviopk);
				IDENTBSatz.zviopk = *pBegin;
				__WriteHR(dbaIDENTB, IDENTBSatz);
			}
		}
		return S_OK;
	}

// ansonsten alles beim Alten
	return ::CreateLink(hPr, VIO_OLD, pBegin, lWert);
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob ein Satz in einer Kette enthalten ist
HRESULT TestDBLink (HPROJECT hPr, long lFileNo, long lFirst, long lValue)
{
DB_ADDR dba(hPr);
long Data[4];
long lNext = lFirst; 
long RC = S_OK;	// FehlerCode

// ersten Satz einlesen
	dba.file_no = (short)lFileNo;
	dba.rec_no = 0;

// Suche des vorgegebenen Wertes
	do {
		if ((dba.rec_no = lNext) <= 0)
		// nichts gefunden --> raus
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

	// Satz aus VerbindungsDatei einlesen
		__ReadHREx(dba, Data[0]);

	// nächster Satz
		lNext = Data[1];
	} while (labs (Data[0]) != lValue);

	return S_OK;
}

HRESULT TestDBLinkVIO (HPROJECT hPr, long lFirst, long lValue, long lIdent, LINKTYPE rgLink, LINKTYPE *prgLink)
{
long lVersion = LocGetDBVersion(hPr);

	if (VERSION0500000E <= lVersion) {
	ErrInstall EI (WC_NOTFOUND);
	DB_ADDR dbaIDENTB (hPr);
	LINKTYPE rgType = rgLink;
	ErrCode RC;

		if (LINKTYPE_DontCare == rgType)
			rgType = LINKTYPE_Unknown;

		dbaIDENTB.file_no = VIO_NEW;
		if (VERSION05000011 <= lVersion) {
		// Elemente im Key jetzt getauscht
		struct identx::identxkey idkey;

			idkey.identx = lIdent;
			idkey.zvioox = TYPETOLINK(lValue, rgType);

		// versuchen den VerbindungsSatz wiederzufinden
			RC = (ErrCode)z_keyfind (&dbaIDENTB, IDENTX, &idkey);
			if (WC_NOTFOUND == RC) {
				if (LINKTYPE_DontCare != rgLink)
					return HRESULT_FROM_ERRCODE(RC);		// gesucht und nichts gefunden

			// wenn nichts gefunden wurde, dann auf nächsten positionieren
				RETURN_FAILED_HRESULT(z_keynext (&dbaIDENTB, IDENTX));
				RETURN_FAILED_HRESULT(z_keyread (hPr, &idkey));
				if (idkey.identx != lIdent || LINKTOLINK(idkey.zvioox) != lValue)
					return HRESULT_FROM_ERRCODE(WC_NOTFOUND);		// nichts gefunden

			// Key ist bereits eingelesen, also sind wir fertig
				if (NULL != prgLink) {
					*prgLink = LINKTOTYPE(idkey.zvioox);
					return S_OK;
				}
			}

		// wenn der Verbindungssatz gefunden wurde und der exakte Type gewünscht ist, dann
		// diesen auch liefern
			if (EC_OKAY == RC && NULL != prgLink) {
				RETURN_FAILED_HRESULT(z_keyread (hPr, &idkey));
				*prgLink = LINKTOTYPE(idkey.zvioox);
			}

		} else {
		// alles beim Alten
		struct identb::identbkey idkey;

			idkey.identk = lIdent;
			idkey.zviook = TYPETOLINK(lValue, rgType);
			dbaIDENTB.file_no = VIO_NEW;

		// versuchen den VerbindungsSatz wiederzufinden
			RC = (ErrCode)z_keyfind (&dbaIDENTB, IDENTB, &idkey);
			if (WC_NOTFOUND == RC) {
				if (LINKTYPE_DontCare != rgLink)
					return HRESULT_FROM_ERRCODE(RC);		// gesucht und nichts gefunden

			// wenn nichts gefunden wurde, dann auf nächsten positionieren
				RETURN_FAILED_HRESULT(z_keynext (&dbaIDENTB, IDENTB));
				RETURN_FAILED_HRESULT(z_keyread (hPr, &idkey));
				if (idkey.identk != lIdent || LINKTOLINK(idkey.zviook) != lValue)
					return HRESULT_FROM_ERRCODE(WC_NOTFOUND);		// nichts gefunden

			// Key ist bereits eingelesen, also sind wir fertig
				if (NULL != prgLink) {
					*prgLink = LINKTOTYPE(idkey.zviook);
					return S_OK;
				}
			}

		// wenn der Verbindungssatz gefunden wurde und der exakte Type gewünscht ist, dann
		// diesen auch liefern
			if (EC_OKAY == RC && NULL != prgLink) {
				RETURN_FAILED_HRESULT(z_keyread (hPr, &idkey));
				*prgLink = LINKTOTYPE(idkey.zviook);
			}
		}
		return (S_OK == RC) ? S_OK : HRESULT_FROM_ERRCODE(RC);
	}

// alles beim Alten
	return ::TestDBLink (hPr, VIO_OLD, lFirst, lValue);
}

///////////////////////////////////////////////////////////////////////////////
// Anhängen eines Satzes an das KettenEnde 
HRESULT CreateChainEnd (HPROJECT hPr, long lFileNo, long *pBegin, long Wert)
{
DB_ADDR dba(hPr);	// neue Datenbankadresse
long Data[4];
ErrCode RC;	// FehlerCode 
long lLast = 0;

// KettenEnde finden
	dba.file_no = lFileNo;
	dba.rec_no = *pBegin;
	while (dba.rec_no) {
		__ReadHREx(dba, Data);
		lLast = dba.rec_no;	// vorhergehendes Element der Kette
		dba.rec_no = Data[1];	// weiter in der Kette
	}
		
// Neuen Satz erzeugen und am Ende der gegebenen Kette einfügen
// Satz neu zusammensetzen
	Data[0] = Wert;		// TargetSatz eintragen
	Data[1] = 0;		// erstmal Ende der Kette
	Data[2] = 0;		// evtl. drittes/viertes Element ausnullen
	Data[3] = 0;

// Satz neu bilden
	__NewHREx(dba, Data);	// Satz neu anfordern

// in Kette einfügen
	if (lLast == 0)
		*pBegin = dba.rec_no;	// neues erstes Element
	else {
	// am Ende der Kette eintragen
	long lNew = dba.rec_no;

		dba.rec_no = lLast;	// letzten Satz lesen
		__ReadHREx(dba, Data);
		Data[1] = lNew;		// modfizieren 
		__WriteHREx(dba, Data);	// und wieder wegschreiben
	}
	return S_OK;
}

