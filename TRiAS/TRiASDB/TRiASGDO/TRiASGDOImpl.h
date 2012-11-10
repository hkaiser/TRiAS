// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.01.2000 23:38:41 
//
// @doc
// @module TRiASGDOImpl.h | Diverse Globale Funktionen und Klassen

#if !defined(_TRIASGDOIMPL_H__B728BBE4_2FED_11d1_96A0_00A024D6F582__INCLUDED_)
#define _TRIASGDOIMPL_H__B728BBE4_2FED_11d1_96A0_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASGDO.h"		// kömmet von's dem MIDL
#include "resource.h"       // main resource symbols

#define	TLB_TRiASGDO_SIGNAT	&LIBID_TRiASGDO, TYPELIB_TRIASGDO_VERSION_MAJOR, TYPELIB_TRIASGDO_VERSION_MINOR
#define	TLB_TRiASDB_SIGNAT	&LIBID_TRiASDB, TYPELIB_TRiASDB_VERSION_MAJOR, TYPELIB_TRiASDB_VERSION_MINOR

//#define	_GEOMETRYCACHEDBYOBJECT		// jedes Objekt bekommt beim Lesen aus der DB sofort seine Geometrie mit
//DefineSmartInterface(GDOObjectGeometry)

#include "wrapper.h"		// InterfaceWrapper
#include "Strings.h"		// StringKonstanten

#include <com/StreamHelpers.h>
#include <com/VariantHelpers.h>
#include <com/PropertyHelper.h>
#include <com/MKHelper.h>

#include "MapHelpers.h"

#include <CSRectGeom.h>

// Messagetabellen

#include "TRiASGDO.hmc"

///////////////////////////////////////////////////////////////////////////////
// ein (hoffentlich) besserer Zufallszahlengenerator als der in der Runtime-Bib;
// aber an den angelehnt; siehe also dort...

class CRandomGenerator {
	long	holdrand;
public:
	CRandomGenerator()
		: holdrand(0)	// holdrand(rand())
	{
#if !defined(_DEBUG)	// bei Debug immer dieselbe Folge
		srand();
#endif
		rand();
	}
	long	rand() {
        return( holdrand = holdrand * 214013L + 2531011L );
	}
	void srand() {
		GUID	g;
		::CoCreateGuid( &g );
		holdrand = g.Data1;
	}
};

#include <sys/timeb.h>
class CTimer {
	CComBSTR		m_strName;
	struct _timeb	m_start;
public:
	CTimer( LPCOLESTR strName )
		: m_strName(strName)
	{
		_ftime(&m_start);
	}
	virtual ~CTimer() {
	}
	void setItems( long lItems ) {
		struct _timeb	end;
		_ftime(&end);
		if( end.millitm < m_start.millitm ) {
			end.time -= 1;
			end.millitm += 1000;
		}
		end.millitm -= m_start.millitm;
		end.time -= m_start.time;
		USES_CONVERSION;
		double	dTime = end.time + (double) end.millitm / 1000;
		ATLTRACE( _T("Timer: %s: %.5lf, %ld Items"), W2A(m_strName), dTime, lItems );
		if( lItems > 0 ) {
			ATLTRACE( _T(", %.5lf Items/s"), (double) lItems / dTime );
		}
		ATLTRACE( _T("\n") );
	}
};

#if defined(_DEBUG)
#define	TIMER_START(num,descr)	CTimer	_t##num(descr);
#define	TIMER_CHECKPOINT(num,nItems)	_t##num.setItems(nItems);
#else
#define	TIMER_START(num,descr)
#define	TIMER_CHECKPOINT(num,nItems)
#endif

///////////////////////////////////////////////////////////////////////////////
// sicherer Selbstzerstörer für Objekte die die Methode 'Close()' besitzen
// (und auch nutzen sollten); besonders wichtig im Fehlerfall

template<class T>
class AutoClose : public T {
public:
	AutoClose( T::target_t *p = NULL ) : T(p) {}
	AutoClose( const T &rhs ) : T(rhs) {}
	AutoClose( IUnknown *p ) : T(p) {}
	AutoClose( IUnknown *p, bool b) : T(p,b) {}
	AutoClose( REFCLSID C, DWORD Ctx = CLSCTX_INPROC_SERVER, IUnknown *p = NULL ) : T(C,Ctx,p) {}
	virtual ~AutoClose() {
		if( T::IsValid() ) {
			try {
				HRESULT hr = CloseOnDestroy( *this );
				_ASSERTE(SUCCEEDED(hr));
//				T(*this)->Close();
			} catch(...) {
				_ASSERTE(0);
			}
		}
	}
	bool operator==( const T &r ) { return T::operator==(r); }
	bool operator<( const T &r ) { return T::operator<(r); }
	bool operator==( const AutoClose &r ) { return T::operator==(r); }
	bool operator!() { return T::operator!(); }
	T &operator=( const T *p ) { return T::operator=(p); }
	T &operator=( const T &r ) { return T::operator=(r); }
	T &operator=( const IUnknown* p ) { return T::operator=(p); }

	friend HRESULT CloseOnDestroy (AutoClose &);
};

#define DefineSmartACInterface2(IF,IID,Func)			\
	typedef __Interface<IF,__CIID<&__uuidof(IF)>,CComPtr<IF> > Func##IF;	\
	inline HRESULT CloseOnDestroy(AutoClose<Func##IF> &o) { return o->Func(); }

DefineSmartACInterface2( GDatabase, IID_GDatabase, Close )
DefineSmartACInterface2( GRecordset, IID_GRecordset, Close )
DefineSmartACInterface2( DGMConnection, IID_DGMConnection, Disconnect )

typedef AutoClose<CloseGDatabase>	AC_GDatabase;
typedef AutoClose<CloseGRecordset>	AC_GRecordset;
typedef AutoClose<DisconnectDGMConnection>	AC_DGMConnection;

///////////////////////////////////////////////////////////////////////////////
// Helfer zum sicheren Ändern von CComBSTR's
class CComBSTRChangeHelper {
	CComBSTR&	m_strOldString;
	CComBSTR	m_strSavString;
	bool		m_bSuccess;
public:
	CComBSTRChangeHelper( CComBSTR& strOldString )
		: m_strOldString(strOldString)
		, m_strSavString(strOldString)
		, m_bSuccess(false)
	{}
	~CComBSTRChangeHelper() {
		if (!m_bSuccess)
			m_strOldString = m_strSavString;
	}
	void Succeeded() {
		m_bSuccess = true;
	}
};

#define	CHECK_INITIALIZED()	ERROR_EXPR_FALSE( S_OK == IsInitialized(), GDO_E_OBJECTNOTINITIALIZED );

///////////////////////////////////////////////////////////////////////////////
// diverse globale Funktionen die so gebraucht werden 
HKEY OpenDataServerKey (void);
int CountRegisteredDataServers (HKEY hKey);

HRESULT	ParseName (LPCOLESTR lpszName);								// Namen auf gültigen Datenbankbezeichner testen
HRESULT NormalizeName (LPCOLESTR lpszName, CComBSTR& strNewName);	// Namen in gültigen Datenbankbezeichner umwandeln

CComBSTR QuoteStatement (const CComBSTR& strOldStmt);				// Umwandlung ' ==> ''
//inline CComBSTR EnBraceStatement (const CComBSTR& strOldStmt) {		// Umwandlung Stmt ==> [Stmt]
//	CComBSTR	S;
//	//S.Append(L"[");
//	S.Append(strOldStmt);
//	//S.Append(L"]");
//	return S;
//}
#define EnBraceStatement(bstr)	(bstr)

const long lSearchDefaults = mdsSM_Compare | mdsSM_NoCase;
const long lSearchKey = lSearchDefaults | mdsSM_SrchKey;
const long lSearchName = lSearchDefaults | mdsSM_SrchName;

HRESULT SearchMDSMap (WTRiASMDSMap& rMap, const CComBSTR& strKey, CComBSTR& strResult, long lMode);

HRESULT FindSpecificParent (IUnknown *pIParent, REFIID riid, void **ppIObj);
HRESULT GetFilter (IGDOObject* pObject, CComBSTR& strFilter);

//HRESULT LocateRecord( IGDOObject* pGDOObject, IGDOFeature* pGDOFeature, AC_GRecordset& rs );
//HRESULT LocateRecord( IGDODatabase* pGDODatabase, IGDOObjects* pGDOObjects, IGDOFeature* pGDOFeature, const CComBSTR& strValue, AC_GRecordset& rs );

HRESULT MakePolyFromRect( _DGMPolygonGeometry* poly, _DGMRectangleGeometry* rect );
HRESULT CopyPolygon( _DGMPolygonGeometry* polyDst, _DGMPolygonGeometry* polySrc );

//////////////////////////////////////////////////////////////////////
// bei get_ ...( BSTR*) muß alter Inhalt von CComBSTR vor dem Aufruf
// freigegeben werden (sonst wird's irgendwann knapp mit dem Speicher...)

//////////////////////////////////////////////////////////////////////
// Struktur zur Beschreibung von Tabellenlayouts
const short	idxNone = 0;
const short idxPKey = 1;				// zusätzlich Primärindex
const short idxAsc = 2;
const short idxDesc = 4;
const short idxMask = idxAsc + idxDesc;	// normaler Index

typedef struct tagFIELDLAYOUT {
	LPCOLESTR	m_lpszName;
	short	m_lFieldType;
	long	m_lSubType;
	UINT	m_iAttributes;
	long	m_lFieldSize;
	UINT	m_iKey;
} FIELDLAYOUT;

HRESULT CreateTable( WGDatabase& pGDatabase, LPCOLESTR lpszTableName, FIELDLAYOUT* pFieldLayout );

//////////////////////////////////////////////////////////////////////
// Helferobjekt für saubere Transaktionen in GDatabase

class DBTransaction {
	WGDatabase	m_db;
	bool		m_bSucceeded;
public:
	DBTransaction(WGDatabase& db)
		: m_db(db)
		, m_bSucceeded(false)
	{
		m_db->BeginTrans();
	}
	virtual ~DBTransaction() {
		if(m_bSucceeded) 
			m_db->CommitTrans();
		else
			m_db->Rollback();
	}
	void Succeeded(bool b=true) {
		m_bSucceeded = b;
	}
};

/////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen für Zugriff auf Geomedia Recordsets
//	Fehler sollten mit EXT_ERROR_FAILED_HRESULT(...) abgefangen werden

inline 
HRESULT GetField(GRecordset *rs, const LPCOLESTR& strFieldName, WGField& f) 
{
	WGFields	flds;
	HRESULT	hr;
	if (S_OK != (hr = rs->get_GFields(flds.ppi())))
		return hr;
	if (S_OK != (hr = flds->get_Item(CComVariant(strFieldName), f.ppi()))) 
		return hr;
	return S_OK;
}

inline 
HRESULT SetFieldValue(AC_GRecordset& rs, const LPCOLESTR& strFieldName, VARIANT& vValue) 
{
	WGFields	flds;
	WGField		f;
	HRESULT		hr;
	if (S_OK != (hr = rs->get_GFields(flds.ppi())))
		return hr;
	if (S_OK != (hr = flds->get_Item(CComVariant(strFieldName), f.ppi())))
		return hr;
	_ASSERTE( !!f );
	if (S_OK != (hr = f->put_Value(vValue)))
		return hr;
	return S_OK;
}

inline 
HRESULT GetFieldValue (AC_GRecordset& rs, const LPCOLESTR& strFieldName, CComVariant& vValue) 
{
WGFields flds;
WGField f;
HRESULT	hr;

	if (S_OK != (hr = rs -> get_GFields (flds.ppi())))
		return hr;
	if (S_OK != (hr = flds -> get_Item (CComVariant (strFieldName), f.ppi()))) 
		return hr;
	_ASSERTE(!!f);
	if (S_OK != (hr = f -> get_Value (CLEARED(vValue))))
		return hr;
	return S_OK;
}

inline 
HRESULT GetFieldType (AC_GRecordset& rs, const LPCOLESTR &strFieldName, long &lType, long &lAttr, long &lSize) 
{
WGFields flds;
WGField f;
HRESULT hr;

	if (S_OK != (hr = rs->get_GFields(flds.ppi())))
		return hr;

short t = 0;

	if (S_OK != (hr = flds->get_Item (CComVariant(strFieldName), f.ppi())))
		return hr;
	_ASSERTE(f.IsValid());
	if (S_OK != (hr = f->get_Type (&t)))
		return hr;
	if (S_OK != (hr = f->get_Attributes (&lAttr)))
		return hr;
	if (gdbSpatial == t) {
		if (S_OK != (hr = f->get_SubType (&lType)))
			return hr;
	} else {
		lType = t;
	}
	if (S_OK != (hr = f->get_Size (&lSize)))
		return hr;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// GDO - Geometrietyp zu TRiAS - Objekttyp
inline 
OBJECTTYPE OT_GDO2TRiAS (long gdoType) throw(_com_error &)
{
long t = 0;

	switch (gdoType) {
	case gdbPoint: 
		t |= OBJECTTYPE_Point; 
		break;

	case gdbLinear: 
		t |= OBJECTTYPE_Line; 
		break;

	case gdbAreal: 
		t |= OBJECTTYPE_Area; 
		break;

	case gdbAnySpatial: 
		t |= (OBJECTTYPE_Point | OBJECTTYPE_Line | OBJECTTYPE_Area); 
		break;

	case gdbCoverage: 
		t |= OBJECTTYPE_Area; 
		break;

	case gdbGraphicsText: 
		t |= OBJECTTYPE_Text; 
		break;
	
	default :
		THROW_FAILED_HRESULT(SUCCEEDED(GDB_E_UNKNOWNOBJECTTYPE));
	}
	return (OBJECTTYPE) t;
}

///////////////////////////////////////////////////////////////////////////////
// zwei Pipes miteinander verbinden
template<typename In, typename Out>
inline HRESULT ConnectPipes (In Src, Out Dst, BSTR bstrName) 
{
WGRecordset	rs;

	RETURN_FAILED_HRESULT(Src -> get_OutputRecordset (rs.ppi()));
	RETURN_FAILED_HRESULT(Dst -> put_InputGeometryFieldName (bstrName));
	RETURN_FAILED_HRESULT(Dst -> putref_InputRecordset (rs));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geometrietransformation in einer Pipe initialisieren
inline 
HRESULT PrepareTransformation (
	DGMServerTransService* pDGMServerTransService, OriginatingPipe* pOriginatingPipe, 
	DGMCoordSystemsMgr* pDGMCoordSystemsMgr, const CComBSTR& strGeometryname) 
{
WGRecordset rs;
WGField f;
WDGMCoordSystem cs;
WAltCoordSystemPath path;

	RETURN_FAILED_HRESULT(pOriginatingPipe -> get_OutputRecordset (rs.ppi()));
	RETURN_FAILED_HRESULT(GetField (rs, strGeometryname, f));
	if (SUCCEEDED(pDGMServerTransService -> CreateCSFromGeometryField (f, cs.ppi()))) {
	// Field hat u.U kein Koordinatensystem
		RETURN_FAILED_HRESULT(pDGMServerTransService -> CreateSimpleTransFromCSMtoCS (
			pDGMCoordSystemsMgr, cs, path.ppi()));
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Enumeratoren für Geomedia-Collections

// {E1D21DA1-B453-11d2-98E0-0060085FC1CE}
extern "C" const IID __declspec(selectany) IID_IEnumGTableDef =
	{ 0xe1d21da1, 0xb453, 0x11d2, { 0x98, 0xe0, 0x0, 0x60, 0x8, 0x5f, 0xc1, 0xce } };
DefineEnumerator2(WGTableDef, IID_IEnumGTableDef )
DefineSmartEnumerator2(WGTableDef, IID_IEnumGTableDef )

// {E1D21DA0-B453-11d2-98E0-0060085FC1CE}
extern "C" const IID __declspec(selectany) IID_IEnumGField =
	{ 0xe1d21da0, 0xb453, 0x11d2, { 0x98, 0xe0, 0x0, 0x60, 0x8, 0x5f, 0xc1, 0xce } };
DefineEnumerator2(WGField, IID_IEnumGField )
DefineSmartEnumerator2(WGField, IID_IEnumGField )

///////////////////////////////////////////////////////////////////////////////
// Finden eines besonderen Parents in der Objekthierarchie über einem gegebenen
// Objekt; *muß* durch try/catch geschützt sein!!!
inline HRESULT FindSpecificParent(IUnknown *pIParent, REFIID riid, void **ppIObj) 
{
WDispatch me_self(pIParent);

	while (me_self.IsValid()) {
		if (SUCCEEDED(me_self -> QueryInterface (riid, ppIObj)))
			return S_OK;		// gesuchtes Objekt gefunden

	// eine Etage weiter hoch
	WTRiASBase base;

		if (FAILED(me_self -> QueryInterface (base.ppi())))
			return E_UNEXPECTED;

		RETURN_FAILED_HRESULT(base -> get_Parent (me_self.ppi()));
	}
	return E_UNEXPECTED;
}

template<typename T>
inline HRESULT FindSpecificParent (IUnknown *pIParent, T **ppIObj)
{
	return FindSpecificParent (pIParent, __uuidof(T), (void **)ppIObj);
}

///////////////////////////////////////////////////////////////////////////////
// Daten in einen Stream Schreiben/von dort lesen
template<class T>
inline HRESULT LoadData (IStream *pIStm, T &riVal)
{
	return pIStm -> Read (&riVal, sizeof(T), NULL);
}

template<class T>
inline HRESULT SaveData (IStream *pIStm, T &riVal)
{
	return pIStm -> Write (&riVal, sizeof(T), NULL);
}

// backwards compatibility functions
inline HRESULT LoadLong (IStream *pIStm, long &riVal) { return LoadData (pIStm, riVal); }
inline HRESULT SaveLong (IStream *pIStm, long iVal) { return SaveData (pIStm, iVal); }

///////////////////////////////////////////////////////////////////////////////
// Debug support
#if defined(_DEBUG)
template<class T>
BOOL SupportsInterface (IUnknown *pIUnk, T *)
{
__Interface<T> Obj;

	return SUCCEEDED(pIUnk -> QueryInterface (Obj.ppi()));
}
#endif // defined(_DEBUG)

#endif // !defined(_TRIASGDOIMPL_H__B728BBE4_2FED_11d1_96A0_00A024D6F582__INCLUDED_)
