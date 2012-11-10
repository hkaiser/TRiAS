// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 04.07.2000 16:56:55 
//
// @doc
// @module CTRiASOEProxyImpl.h | Declaration of the <c CCTRiASOEProxyImpl> class

#if !defined(__ITRiASOEProxyImpl_H__DB102700_1468_11d3_996C_0060085FC1CE)
#define	__ITRiASOEProxyImpl_H__DB102700_1468_11d3_996C_0060085FC1CE

//////////////////////////////////////////////////////////////////////
// Export Proxy

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Pragmas.h>
#pragma	HDR_ON()

#include "Xtension.h"
#include "ExportOEIface.h"

#include <com/XMLInterTRiAS.h>
#include <PropNamex.h>

//#define _DUMP_XML_TREES

#if defined(_DUMP_XML_TREES)
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#endif // defined(_DUMP_XML_TREES)

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);x=NULL;}
#define DELETE_VEC(x)	if(!(x)){}else{delete[](x);x=NULL;}
#endif // DELETE_OBJ

const long CoordChunk = 256;
const long MFChunk = 16;
const long CharChunk = 64;

#define ALIGN(val,chunk)	(((val)/(chunk))+1)*(chunk)

template<class T>
class PtrWrap {
	typedef	T* pT;
	pT&		m_p;
	long	m_nItems;
	bool	m_bDeleteOnDestroy;
	long	m_nChunkSize;
	HRESULT CheckIndex(long idx) {
		if( idx < m_nItems )
			return S_OK;
		if( m_p ) {
			RETURN_EXPR_FALSE( _CrtIsMemoryBlock( m_p, m_nItems * sizeof(T), NULL, NULL, NULL ), E_FAIL );
		}
		idx = ALIGN(idx,m_nChunkSize);
		pT p = new T[idx];
		RETURN_EXPR_FALSE( NULL != p, E_OUTOFMEMORY );
		memset( p, 0, idx * sizeof(T) );
		memcpy( p, m_p, m_nItems * sizeof(T) );
		if( m_p) {
			delete[] m_p; m_p = NULL;
		}
		m_p = p;
		m_nItems = idx;
		return S_OK;
	}
public:
	PtrWrap( pT& p, bool bDeleteOnDestroy = true, long lChunkSize = 256 )
		: m_p(p)
		, m_nItems(0)
		, m_bDeleteOnDestroy(bDeleteOnDestroy)
		, m_nChunkSize(lChunkSize)
	{ 
		_ASSERTE( NULL == m_p );
	}
	~PtrWrap() {
		if( m_bDeleteOnDestroy && m_p ) {
			_ASSERTE( _CrtIsMemoryBlock( m_p, m_nItems * sizeof(T), NULL, NULL, NULL ) );
			delete[] m_p;
		}
	}
	T& operator[]( long idx ) {
		THROW_FAILED_HRESULT( CheckIndex( idx ) );
		return m_p[idx];
	}
	const long Items() { return m_nItems; }
	void Clear( unsigned char pattern = 0x00 ) {
		if( !m_p )
			return;
		_ASSERTE( _CrtIsMemoryBlock( m_p, m_nItems * sizeof(T), NULL, NULL, NULL ) );
		memset( m_p, pattern, m_nItems * sizeof(T) );
	}
};

class MFELDHOLDER {
public:
	MFELD	*m_pFields;		// darauf wird von außen zugegriffen
private:
	int		*m_pSizes;
	long	m_nCurrIdx;
	PtrWrap<int>	m_wSizes;
	PtrWrap<MFELD>	m_wFields;
	long GetNeededSize(PUCHAR p) {
		register long s = 0;
		for( ; *p; ++p, ++s ) {
			if( isspace((int)*p) && !(_T(' ') == *p) ) {
				++s;
			}
		}
		return s;
	}

	HRESULT CopyText( char* pDst, PUCHAR pSrc ) {
		for( ; *pSrc; ++pSrc, ++pDst ) {
			if( isspace((int)*pSrc) && !(_T(' ') == *pSrc ) ) {
				*pDst = _T('\\');
				*++pDst = _T('\r') == *pSrc ? _T('r')
						: _T('\n') == *pSrc ? _T('n')
						: _T('\t') == *pSrc ? _T('t')
						: _T('\b') == *pSrc ? _T('b')
						: _T('?')
						;
			} else {
				*pDst = *pSrc;
			}
		}
		*pDst = _T('\0');
		return S_OK;
	}
public:
	MFELDHOLDER( long startSize = 32 )
		: m_nCurrIdx(0)
		, m_pFields(NULL)
		, m_pSizes(NULL)
		, m_wFields(m_pFields)
		, m_wSizes(m_pSizes)
	{ }
	~MFELDHOLDER() {
		for( long i = 0; i != m_wFields.Items(); ++i ) {
			DELETE_VEC(m_wFields[i].MText);
		}
	}
	HRESULT Init() {
		for( long nField = 0; nField != m_wFields.Items(); ++nField ) {
			m_wFields[nField].MCode = 0;
		}
		m_nCurrIdx = 0;
		return S_OK;
	}
	HRESULT Add( long MCode, CComBSTR& strText, short MTyp, LPCTSTR& lpszAddedText ) {
	// KK000906
		if( !strText ) 
			return S_FALSE;
		 
		USES_CONVERSION;
#if defined(_UNICODE)
#error "CharToOEM korrigieren!!"
#endif
		LPTSTR	lpszText = W2A(strText);
		::CharToOem( lpszText, lpszText );
		long nChars = GetNeededSize((PUCHAR) lpszText) + 1;		// abschließende '\0' nicht vergessen!
		if( m_wSizes[m_nCurrIdx] < nChars ) {
			nChars = ALIGN(nChars,CharChunk);
			DELETE_VEC(m_wFields[m_nCurrIdx].MText);
			m_wSizes[m_nCurrIdx] = 0;
			m_wFields[m_nCurrIdx].MText = new char[nChars];
			if( NULL == m_wFields[m_nCurrIdx].MText )
				return E_OUTOFMEMORY;
			m_wSizes[m_nCurrIdx] = nChars;
		}

		m_wFields[m_nCurrIdx].MCode = MCode;

		CopyText( m_wFields[m_nCurrIdx].MText, (PUCHAR) lpszText );
		m_wFields[m_nCurrIdx].MTyp = MTyp;


		lpszAddedText = m_wFields[m_nCurrIdx].MText;
		++m_nCurrIdx;
		return S_OK;
	}
};

class GSTRUCTHOLDER 
	: public GSTRUCT {
	PtrWrap<double>	m_wX;
	PtrWrap<double>	m_wY;
	PtrWrap<long>	m_wcnt;
public:
	GSTRUCTHOLDER() 
		: m_wX(x)
		, m_wY(y)
		, m_wcnt(cnt)
	{ }
	HRESULT Init() {
		GSize = 0;
		m_wcnt.Clear();
		return S_OK;
	}
	HRESULT Add( double _x, double _y ) {
		m_wX[GSize] = _x;
		m_wY[GSize] = _y;
		++GSize;
		return S_OK;
	}
	HRESULT Add( long nContour, long nCoordinates ) {
		m_wcnt[nContour] = nCoordinates;
		return S_OK;
	}
};

inline 	HRESULT MakeRealFilename( const CComBSTR& strBasename, const CComBSTR& strSourcename, BOOL bSeparateDirs, CComBSTR& strRealname ) {
	TCHAR	sD[_MAX_DRIVE];
	TCHAR	sP[_MAX_DIR];
	TCHAR	sN[_MAX_FNAME];
	TCHAR	sE[_MAX_EXT];
	TCHAR	P[_MAX_PATH];
	USES_CONVERSION;
	::_splitpath( W2A(strBasename), sD, sP, sN, sE );
	LPCTSTR	lpszName = W2A(strSourcename);
	if( bSeparateDirs ) {
		long	l = strlen( sP );
		if( 1 + l + strSourcename.Length() >= _MAX_DIR )
			return E_FAIL;
		sP[l++] = _T('\\');
		for( ; *lpszName && l < _MAX_DIR - 2; ++l, ++lpszName ) {
			sP[l] = isalnum(*lpszName) ? *lpszName : _T('_');
		}
		sP[l++] = _T('\0');
	} else {
		long	l = strlen( sN );
		if( 3 + l + strSourcename.Length() >= _MAX_FNAME )
			return E_FAIL;
		sN[l++] = _T(' ');
		sN[l++] = _T('(');
		for( ; *lpszName && l < _MAX_FNAME - 2; ++l, ++lpszName ) {
			sN[l] = isalnum(*lpszName) ? *lpszName : _T('_');
		}
		sN[l++] = _T(')');
		sN[l++] = _T('\0');
	}
	::_makepath( P, sD, sP, sN, sE );
	strRealname = P;
	return S_OK;
}

inline HRESULT RetrieveVI( CTRiASXMLDocument& doc, IXMLElement* pVisinfo, VISINFO* pVI, IXMLElement** ppAttributes ) {
	WXMLElement	pAttribute;
	RETURN_FAILED_HRESULT( RetrieveAttribute( pVisinfo, CComVariant(L"locatable"), pVI->m_fLocatable ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( pVisinfo, CComVariant(L"visible"), pVI->m_fVisible ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( pVisinfo, CComVariant(L"style"), pVI->m_Style ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( pVisinfo, CComVariant(L"priority"), pVI->m_Priority ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( pVisinfo, CComVariant(L"color"), pVI->m_C ) );
	RETURN_FAILED_HRESULT( doc.FindItem( pVisinfo, doc.AttributesTag(), ppAttributes ) );
	return S_OK;
}

inline HRESULT RetrievePVI( CTRiASXMLDocument& doc, IXMLElement* pVisinfo, PVISINFO* pPVI ) {
	WXMLElement	pAttributes;
	RETURN_FAILED_HRESULT( RetrieveVI( doc, pVisinfo, &pPVI->m_VI, pAttributes.ppi() ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( doc, pAttributes, CComVariant(L"dimension"), CComVariant(L"size"), pPVI->m_Size ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( doc, pAttributes, CComVariant(L"rotation"), CComVariant(L"value"), pPVI->m_iRot ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( doc, pAttributes, CComVariant(L"color"), CComVariant(L"color"), pPVI->m_SecC ) );
	return S_OK;
}

inline HRESULT RetrieveLVI( CTRiASXMLDocument& doc, IXMLElement* pVisinfo, LVISINFO* pLVI ) {
	WXMLElement	pAttributes;
	RETURN_FAILED_HRESULT( RetrieveVI( doc, pVisinfo, &pLVI->m_VI, pAttributes.ppi() ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( doc, pAttributes, CComVariant(L"width"), CComVariant(L"value"), pLVI->m_Width ) );
	return S_OK;
}
inline HRESULT RetrieveFVI( CTRiASXMLDocument& doc, IXMLElement* pVisinfo, FVISINFO* pFVI ) {
	WXMLElement	pAttributes;
	RETURN_FAILED_HRESULT( RetrieveVI( doc, pVisinfo, &pFVI->m_VI, pAttributes.ppi() ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( doc, pAttributes, CComVariant(L"width"), CComVariant(L"value"), pFVI->m_iWidth ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( doc, pAttributes, CComVariant(L"color"), CComVariant(L"color"), pFVI->m_FC ) );
	return S_OK;
}
inline HRESULT RetrieveTVI( CTRiASXMLDocument& doc, IXMLElement* pVisinfo, TVISINFO* pTVI ) {
	WXMLElement	pAttributes;
	CComBSTR	strFont;
	RETURN_FAILED_HRESULT( RetrieveVI( doc, pVisinfo, &pTVI->m_VI, pAttributes.ppi() ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( doc, pAttributes, CComVariant(L"size"), CComVariant(L"size"), pTVI->m_Size ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( doc, pAttributes, CComVariant(L"type"), CComVariant(L"value"), pTVI->m_Type ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( doc, pAttributes, CComVariant(L"rotation"), CComVariant(L"value"), pTVI->m_Rot ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( doc, pAttributes, CComVariant(L"orientation"), CComVariant(L"value"), pTVI->m_Orient ) );
	RETURN_FAILED_HRESULT( RetrieveAttribute( doc, pAttributes, CComVariant(L"font"), CComVariant(L"value"), strFont ) );
	USES_CONVERSION;
	memset( pTVI->m_VI.m_VisName, 0x00, VISNAMESIZE );
	strncpy( pTVI->m_VI.m_VisName, W2A(strFont), VISNAMESIZE );
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Basisklasse, die es ermöglicht, sowohl 'alte' Exportfilter mit ihren
// globalen Ausgabefunktionen, als auch neuere Module zu bedienen, die die
// Exportfunktionen als Member implementiert haben.
class ATL_NO_VTABLE CExportBaseImpl
{
public:
	virtual ErrCode ExportBegin (char *lpFileName, OFSTRUCT &of, OutMode rgMode, HWND hWnd, LPCTSTR lpszDatasource)
	{
		return ::ExportBegin (lpFileName, of, rgMode, hWnd, lpszDatasource);
	}
	virtual ErrCode ExportComment (OFSTRUCT &of, const char *lpCommentString)
	{
		return ::ExportComment (of, lpCommentString);
	}
	virtual ErrCode ExportHeader (OFSTRUCT &of, const char *lpHeaderString)
	{
		return ::ExportHeader (of, lpHeaderString);
	}
	virtual ErrCode ExportDescriptionEx (OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescInfo, DWORD dwStyle)
	{
		return ::ExportDescriptionEx (of, lpKeyInfo, lpDescInfo, dwStyle);
	}

// KK001023	
	virtual ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* lpszShortDescription, const char* lpszLongDescription, const long lVisType, const VISINFO* pVISINFO , long lIdent)
	{
		return ::ExportIdentDescription(of, lpszOKS, lpszShortDescription, lpszLongDescription, lVisType, pVISINFO, lIdent);
	}

	virtual ErrCode ExportMerkmalDescription(long lMCode, char *pBuf, short ityp, short iLen)
	{
		return ::ExportMerkmalDescription(lMCode, pBuf, ityp, iLen);
	}
	virtual ErrCode ExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *pRF, LPCTSTR pUniqueIdent, LPCTSTR lpszGUID, LPCTSTR pParentClass )
	{
		return ::ExportData (of, GS, MF, pRF, pUniqueIdent, lpszGUID, pParentClass);
	}
	virtual ErrCode ExportTrailer (OFSTRUCT &of, const char *lpTrailerString)
	{
		return ::ExportTrailer (of, lpTrailerString);
	}
	virtual ErrCode ExportEnd (OFSTRUCT &of)
	{
		return ::ExportEnd (of);
	}
	virtual ErrCode ExportBreak (OFSTRUCT &of)
	{
		return ::ExportBreak (of);
	}
};

///////////////////////////////////////////////////////////////////////////////
// 
template<class T, const CLSID *pCLSID>
class ATL_NO_VTABLE CTRiASOEProxyImpl :
	public ITRiASOEProxy,
	public CExtDataEngineImpl<T, pCLSID>,
	public CXMLTraverse<CTRiASOEProxyImpl,CTRiASXMLDocument>,
	public CErrSupport<T, &IID_ITRiASOEProxy>,
	public CExportBaseImpl
{
//	DECLARE_ERRSUPPORTENTRY(CXMLTraverseImpl_t, &IID_ITRiASOEProxy);
	long	m_nContour;					// aktuelle Kontur
	long	m_nContourCoordinates;		// aktuelle Koordinate in der Kontur

// KK000202 - Exportbeeinflussung
	long	m_nCounter;

	CComBSTR	m_strClassname;			// aktuelle Klasse in der wir uns befinden
	ULONG		m_ulIdent;				// aktueller Identifikator dieser Klasse
	GSTRUCT			m_GS;

	OFSTRUCT		m_ofs;
	GSTRUCTHOLDER	m_gs;
	MFELDHOLDER		m_mf;
	RSTRUCT			*m_rs;
	LPCTSTR			m_lpszUniqueIdent;
	CComBSTR		m_strProjectPath;
	WXMLElement		m_pHeader;		// Datenbankheader; ist für alle Datenquellen gleich

	PVISINFO		m_defPVISINFO, m_clsPVISINFO, *m_pPVISINFO;		// Punktvisinfo; Default / Klasse / aktuell
	LVISINFO		m_defLVISINFO, m_clsLVISINFO, *m_pLVISINFO;		// Linienvisinfo; Default / Klasse / aktuell
	FVISINFO		m_defFVISINFO, m_clsFVISINFO, *m_pFVISINFO;		// Flächenvisinfo; Default / Klasse / aktuell
	TVISINFO		m_defTVISINFO, m_clsTVISINFO, *m_pTVISINFO;		// Textvisinfo; Default / Klasse / aktuell
	HWND			m_hWnd;			// TRiAS-Window
	long			m_nDatasource;	// aktuelle Datenquelle

// Der Dateiname in der OFSTRUCT - Struktur ist limitiert auf 128 Zeichen.
// Das kann bei langen Dateiname zu Problemen führen. Daher wird ein
// chdir in das Exportverzeichnis ausgeführt, dort die Ausgabedatei
// mit nur dem Dateinamen geöffnet und nach abschluß des Exports wieder
// in das Ausgangsverzeichnis zurückgewechselt.
	TCHAR	m_strCurrentDir[_MAX_PATH];
	
	HRESULT ChangeToExportDir( const CComBSTR& strFullFilename, CComBSTR& strReducedFilename ) 
	{
		TCHAR	strDrive[_MAX_DRIVE];
		TCHAR	strDir[_MAX_DIR];
		TCHAR	strName[_MAX_FNAME];
		TCHAR	strExt[_MAX_EXT];
		TCHAR	strNewname[_MAX_PATH];
		TCHAR	strNewDir[_MAX_PATH];

		USES_CONVERSION;
		::_splitpath(W2A(strFullFilename), strDrive, strDir, strName, strExt);
		::_makepath(strNewname, NULL, NULL, strName, strExt);
		::_makepath(strNewDir, strDrive, strDir, NULL, NULL);

//		strReducedFilename = strNewname;
		if (strFullFilename.Length() <= OFS_MAXPATHNAME)
			strReducedFilename = strFullFilename;
		else
			strReducedFilename = strNewname;

		RETURN_EXPR_FALSE(strFullFilename.Length() <= OFS_MAXPATHNAME, E_FAIL);

	// KK991108 - abschließendes '\\' entfernen
	char *cptr;

		if (*(cptr = &strNewDir[strlen(strNewDir)-1]) == '\\')
			*cptr = '\0';

		RETURN_EXPR_TRUE( 0 == ( GetCurrentDirectory( sizeof(m_strCurrentDir), m_strCurrentDir ) ), E_FAIL );
		if (!SetCurrentDirectory( strNewDir ) ) {
			RETURN_EXPR_FALSE(CreateDirectory(strNewDir, NULL), E_FAIL);
			RETURN_EXPR_FALSE(SetCurrentDirectory(strNewDir), E_FAIL);
		}
		return S_OK;
	}
	HRESULT ChangeToCurrentDir() 
	{
		RETURN_EXPR_TRUE(!SetCurrentDirectory(m_strCurrentDir), E_FAIL);
		return S_OK;
	}

	HRESULT EnterCategory( const CComBSTR& strCategory, const CComBSTR& strDescription ) {

		CComBSTR	strComment = strCategory;	// Datasource oder Class
		strComment.Append( L" (" );
		strComment.Append( strDescription );
		strComment.Append( L")" );
		USES_CONVERSION;
		ExportComment( m_ofs, _T("#########################################################################") );
		ExportComment( m_ofs, W2A(strComment) );
		ExportComment( m_ofs, _T("#########################################################################") );

		return S_OK;
	}
	typedef enum {
		XML_HEADERENTRIES = 1
		, XML_DATASOURCEENTRIES = 2
		, XML_CLASSENTRIES = 3
		, XML_COORDINATES = 4
		, XML_DEFVISINFO = 5
		, XML_VISINFO = 6
	};

public:
	typedef CTRiASOEProxyImpl<T,pCLSID> CTRiASOEProxyImpl_t;
	CTRiASOEProxyImpl( UINT iNameID, UINT iExtID )
		: CExtDataEngineImpl_t( iNameID, iExtID )
		, m_rs(NULL)
		, m_nDatasource(0)
		, m_nCounter(0)
		, m_hWnd(NULL)
	{
	}
	virtual ~CTRiASOEProxyImpl() 
	{
	}

	STDMETHOD(ExportData)( IDispatch* pDispXMLDocument, wireHWND hWndM , long nCounter) 
	{
		m_nCounter = nCounter;	// KK000202
		COM_TRY {
			RETURN_EXPR_FALSE(hWndM->fContext == WDT_INPROC_CALL, E_FAIL);
			m_hWnd = (HWND) hWndM->u.hInproc;

		WXMLDocument pXMLDocument;

			RETURN_FAILED_HRESULT(pDispXMLDocument->QueryInterface(pXMLDocument.ppi()));

#if defined(_DUMP_XML_TREES)
			{
			char cbBuffer[_MAX_PATH], cbTempFile[_MAX_PATH];
			char cbPrefix[64];

				wsprintf(cbPrefix, "x%x", nCounter);
				GetTempPath(sizeof(cbBuffer), cbBuffer);
				GetTempFileName(cbBuffer, cbPrefix, 0, cbTempFile);

			WPersistStreamInit pPersistStreamInit;
			WStream	pStreamW;

				USES_CONVERSION;
				::CreateStreamOnHGlobal(NULL, true, pStreamW.ppi());
				pXMLDocument->QueryInterface (pPersistStreamInit.ppi());
				pPersistStreamInit -> Save(pStreamW, TRUE);

			HGLOBAL	hglbl;

				::GetHGlobalFromStream(pStreamW, &hglbl);

			int	fd = _open (cbTempFile, _O_CREAT | _O_TRUNC | _O_BINARY | _O_RDWR, _S_IREAD | _S_IWRITE);

				_write(fd, ::GlobalLock(hglbl), ::GlobalSize(hglbl));
				_close(fd);
				::GlobalUnlock(hglbl);
			}
#endif // defined(_DUMP_XML_TREES)

		CTRiASXMLDocument TRiASXMLDocument(pXMLDocument);

			RETURN_FAILED_HRESULT(Traverse(TRiASXMLDocument));


		} COM_CATCH;

		if ( m_nCounter < 0)
			return S_FALSE;

		return S_OK;
	}

//---------------------------------------------------------------------------------
	STDMETHOD(ExportDataEnd)(ENDMODE rgMode) 
	{
	// KK000215
		if (ENDMODE_Break == rgMode) {
		// Abbrechen: Dateien löschen etc.
			COM_TRY {
				ExportBreak (m_ofs);
			} COM_CATCH;
		} else {
			if (m_bSeparate || ENDMODE_End == rgMode) {
				COM_TRY {
					ExportTrailer (m_ofs, NULL);
				} COM_CATCH;
			}
			COM_TRY {
				ExportEnd (m_ofs);
			} COM_CATCH;
		}
		return S_OK;
	}

//------------------------------------------------------------------
// KK000228
	STDMETHOD(ExportMerkmalDescription)(long lMCode, short locMTyp, short iLen, char *pbuf) 
	{
		COM_TRY {
		CPropertyName Name(pbuf);

			((CExportBaseImpl *)this) -> ExportMerkmalDescription(lMCode, 
				const_cast<char *>(Name.GetName().c_str()), locMTyp, iLen);
		} COM_CATCH;
		return S_OK;
	}

//------------------------------------------------------------------------------------	
// KK001023
	STDMETHOD(ExportIDDescription) ( char *_DEXBUF,char * _buf,char * _lbuf, long lVisType, DWORD * pVis, long lIdent) 
	{
		COM_TRY {
			ExportIdentDescription( m_ofs,_DEXBUF,_buf, _lbuf, lVisType, (VISINFO *)pVis, lIdent);
		} COM_CATCH;
		return S_OK;
	}

//------------------------------------------------------------------------------------	
	BEGIN_COM_MAP(CTRiASOEProxyImpl)
		COM_INTERFACE_ENTRY(ITRiASOEProxy)
	END_COM_MAP()

	BEGIN_XML_MAP(CTRiASOEProxyImpl)
		XML_ENTRY( L"project", OnProject )
		XML_ENTRY( L"header", NULL )
		XML_ENTRY( L"datasource", OnDatasource )
		XML_ENTRY( L"views", OnViews )
	ALT_XML_MAP(XML_HEADERENTRIES)
		XML_ENTRY( L"entry", OnHeaderEntry )
	ALT_XML_MAP(XML_DATASOURCEENTRIES)
		XML_ENTRY( L"class", OnClass )
	ALT_XML_MAP(XML_CLASSENTRIES)
		XML_ENTRY( L"object", OnObject )
		XML_ENTRY( L"geometry", OnGeometry )
		XML_ENTRY( L"feature", OnFeature )
	ALT_XML_MAP(XML_VISINFO)
		XML_ENTRY( L"class", OnClassinfo )
		XML_ENTRY( L"visinfo", OnVisinfo )
		XML_ENTRY( L"objects", NULL )
		XML_ENTRY( L"attribute", OnAttribute )
	ALT_XML_MAP(XML_DEFVISINFO)
		XML_ENTRY( L"visinfo", OnDefVisinfo )
	ALT_XML_MAP(XML_COORDINATES)
#if !defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)
		XML_ENTRY( L"coordinates", OnCoordinates )
#endif // !defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)
		XML_ENTRY( L"coordinate", OnCoordinate )
		XML_ENTRY( L"contour", OnContour )
	END_XML_MAP()

	HRESULT OnProject( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pProject ) {
		if( bStart ) {
			RETURN_FAILED_HRESULT( RetrieveAttribute( pProject, doc.PathProp(), m_strProjectPath ) );
			RETURN_FAILED_HRESULT( doc.FindItem( pProject, doc.HeaderTag(), m_pHeader.ppi() ) );
		} 
		else {
			if (!m_bSeparate) {
// KK000822
//				COM_TRY {
//					ExportTrailer( m_ofs, NULL );
//				} COM_CATCH;
// KK000822

//				COM_TRY {
//					ExportEnd( m_ofs );
//				} COM_CATCH;
				ChangeToCurrentDir();
			}
		}
		return S_OK;
	}
	HRESULT OnViews( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pViews ) {
		if( !bStart ) return S_FALSE;
		Traverse( doc, pViews, XML_DEFVISINFO );
		return S_FALSE;
	}
	HRESULT	HandleVisInfo( CTRiASXMLDocument& doc, IXMLElement* pVisinfo, PVISINFO& rP, LVISINFO& rL, FVISINFO& rF, TVISINFO& rT ) {
		CComBSTR	strVistype;
		doc.GetItemName( pVisinfo, strVistype );
		///////////////////////////////////////////////////////////////////////
		// Zeiger auf aktuelle Visinfo gleich mit einstellen:
		// ==> wenn wir in der default-Visinfo sind, dann hat's keine weiteren Auswirkungen
		// ==> wenn wir in einer Klasse sind, dann wird der Zeiger nur dann umgesetzt
		//     wenn auch eine entsprechende VI da ist, ansonsten bleibt er auf der Default-
		//     Visinfo (wird im "OnClass" auf default eingestellt)
		if( 0 == wcsicmp( L"point", strVistype ) ) {
			m_pPVISINFO = &rP;
			RetrievePVI( doc, pVisinfo, &rP );
		} else if( 0 == wcsicmp( L"line", strVistype ) ) {
			m_pLVISINFO = &rL;
			RetrieveLVI( doc, pVisinfo, &rL );
		} else if( 0 == wcsicmp( L"area", strVistype ) ) {
			m_pFVISINFO = &rF;
			RetrieveFVI( doc, pVisinfo, &rF );
		} else if( 0 == wcsicmp( L"text", strVistype ) ) {
			m_pTVISINFO = &rT;
			RetrieveTVI( doc, pVisinfo, &rT );
		}
		return S_FALSE;		// nicht weitergehen
	}
	CComBSTR	m_strSClassname;
	CComBSTR	m_strLClassname;
	HRESULT OnAttribute( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pAttribute ) {
		if( !bStart ) return S_FALSE;
		CComVariant	vName;
		pAttribute->getAttribute( V_BSTR(&doc.NameProp()), &vName );
		if( 0 == wcsicmp( V_BSTR(&vName), L"short") ) {
			pAttribute->get_text( &m_strSClassname );
		} else if( 0 == wcsicmp( V_BSTR(&vName), L"long") ) {
			pAttribute->get_text( &m_strLClassname );
		}
		return S_OK;
	}
	HRESULT OnVisinfo( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pVisinfo ) {
		if( !bStart ) return S_FALSE;
		return HandleVisInfo( doc, pVisinfo, m_clsPVISINFO, m_clsLVISINFO, m_clsFVISINFO, m_clsTVISINFO );
	}
	CComBSTR	m_strOKS;
	HRESULT OnClassinfo( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pClass ) {
		if( bStart ) {
			m_pPVISINFO = &m_defPVISINFO;
			m_pLVISINFO = &m_defLVISINFO;
			m_pFVISINFO = &m_defFVISINFO;
			m_pTVISINFO = &m_defTVISINFO;
			return S_OK;
		}
		//////////////////////////////////////////////////////////////////////////
		// Eigentlich wären für die Visualisierungstypen die VT_... - Definitionen
		// korrekt; dazu müßte aber "visinfo.hxx" mit gezogen werden, der wieder
		// Abhängigkeiten Von Commonvu (Color, Dimension usw.) mitbringt
		// Wir vereinbaren hier einfach mal, daß "ExportIdentDescription" als
		// 4. Parameter entsprechend der OT... - Definition den Visualisierungstyp
		// angibt; was ja inhaltlich auch geht; es muß dann nur auf der anderen Seite
		// beachtet werden!!

		if( S_OK != RetrieveAttribute( pClass, doc.NameProp(), m_strOKS ) )
			return S_FALSE;

	// KK000217
		CComBSTR	strVistype;

		WXMLElement	pVisinfos;

		HRESULT hr = doc.FindItem( pClass, doc.VisinfosTag(), pVisinfos.ppi() );

		if( FAILED(hr) || S_FALSE == hr) {
			_ASSERTE(SUCCEEDED(hr));
			return S_FALSE; 
		}	// dumm gelaufen :-(

		WXMLElementCollection	pXMLElementCollection;
		WEnumVARIANT	pEnum;
		long			lItems;
		RETURN_FAILED_HRESULT( hr = pVisinfos->get_children( pXMLElementCollection.ppi() ) );
		if( S_FALSE == hr ) return S_FALSE;			// kein Kindergarten vorhanden
		_ASSERTE( pXMLElementCollection.IsValid() );
		RETURN_FAILED_HRESULT( hr = pXMLElementCollection->get_length( &lItems ) );
		if( 0 == lItems ) return S_FALSE;			// Kindergarten ja, aber keine Kinder
		RETURN_FAILED_HRESULT( hr = pXMLElementCollection->get__newEnum(pEnum.ppu() ) );
		if( S_FALSE == hr ) return S_FALSE;			// komisch; dürfte es eigentlich nicht geben
		_ASSERTE( pEnum.IsValid() );
	
		CComVariant		vEntry;
		DWORD			dwFetched;
		WXMLElement		pChild;
		for( pEnum->Reset(); S_OK == pEnum->Next( 1, &vEntry, &dwFetched ); vEntry.Clear() ) {
			if( !V_ISDISPATCH(&vEntry) )
				continue;
			if( FAILED( hr = V_DISPATCH(&vEntry)->QueryInterface( pChild.GetIID(), pChild.ppv() ) ) || S_FALSE == hr )
				continue;
			doc.GetItemName( pChild, strVistype );


			COM_TRY {
				USES_CONVERSION;

		// KK001023
				long lIdent = 0;

				if( 0 == wcsicmp( L"point", strVistype ) ) {
					ExportIdentDescription(m_ofs, W2A(m_strOKS), W2A(m_strSClassname), W2A(m_strLClassname), OT_PUNKT, &m_pPVISINFO->m_VI ,lIdent);
				} else if( 0 == wcsicmp( L"line", strVistype ) ) {
					ExportIdentDescription(m_ofs, W2A(m_strOKS), W2A(m_strSClassname), W2A(m_strLClassname), OT_KANTE, &m_pLVISINFO->m_VI , lIdent);
				} else if( 0 == wcsicmp( L"area", strVistype ) ) {
					ExportIdentDescription(m_ofs, W2A(m_strOKS), W2A(m_strSClassname), W2A(m_strLClassname), OT_FLAECHE, &m_pFVISINFO->m_VI , lIdent);
				} else if( 0 == wcsicmp( L"text", strVistype ) ) {
					ExportIdentDescription(m_ofs, W2A(m_strOKS), W2A(m_strSClassname), W2A(m_strLClassname), OT_TEXT, &m_pTVISINFO->m_VI , lIdent);
				}


			} COM_CATCH;
		}
		return S_OK;
	}
	HRESULT OnDefVisinfo( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pVisinfo ) {
		if( !bStart ) return S_FALSE;
		return HandleVisInfo( doc, pVisinfo, m_defPVISINFO, m_defLVISINFO, m_defFVISINFO, m_defTVISINFO );
	}
	HRESULT ExportIdentdescriptions( CTRiASXMLDocument& doc, IXMLElement* pDatasource ) {
		WXMLElement	pClasses;
		RETURN_FAILED_HRESULT( doc.FindItem( pDatasource, doc.ClassesTag(), pClasses.ppi() ) );
		Traverse( doc, pClasses, XML_VISINFO );
		return S_OK;
	}

//--------------------------------------------------------------------------------------

	HRESULT OnDatasource( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pDatasource ) {


		if( bStart ) {
			CComBSTR	strDatasourceName;
			CComBSTR	strDatasourcePath;
			CComBSTR	strRealfilename(CExtDataEngineImpl_t::m_strFilename);
			RETURN_FAILED_HRESULT( RetrieveAttribute( pDatasource, doc.NameProp(), strDatasourceName ) );
			/*work around the bug*/ 
			RETURN_FAILED_HRESULT( RetrieveAttribute( pDatasource, CComBSTR(L"path"), strDatasourcePath ) );
			if( CExtDataEngineImpl_t::m_bSeparate ) {
				MakeRealFilename( CExtDataEngineImpl_t::m_strFilename, strDatasourceName, CExtDataEngineImpl_t::m_bSeparateDirs, strRealfilename );
			}

			/*if( m_bSeparate || 0 == m_nDatasource++ )*/ {
				CComBSTR	strReducedFilename;
				RETURN_FAILED_HRESULT( ChangeToExportDir( strRealfilename, strReducedFilename ) );
				USES_CONVERSION;
				memset( &m_ofs, 0x00, sizeof(m_ofs) );

				if ( 0 < m_nCounter) {		// KK000202
					RETURN_EXPR_FALSE( EC_OKAY == ExportBegin( W2A(strReducedFilename), m_ofs, OMConcatinate, m_hWnd, W2A(strDatasourcePath) ), E_FAIL );
				} else {
					RETURN_EXPR_FALSE( EC_OKAY == ExportBegin( W2A(strReducedFilename), m_ofs, OMOverwrite, m_hWnd, W2A(strDatasourcePath) ), E_FAIL );

					CComBSTR	strExportBase;
					CComBSTR	strExportVersion;
					RETURN_FAILED_HRESULT( CExtDataEngineImpl_t::get_Name( &strExportBase ) );
					RETURN_EXPR_FALSE( strExportVersion.LoadString(1), E_FAIL );	// Versionsnummer des Moduls
					strExportBase.Append(L" (V");
					strExportBase.Append(strExportVersion);
					strExportBase.Append(L") ");
					strExportBase.Append(m_strProjectPath);
					ExportHeader( m_ofs, W2A(strExportBase) );
					WXMLElement	pHeader;
					//////////////////////////////////////////////////////////////////////////
					// Datenbankheader ausgeben
					RETURN_FAILED_HRESULT( Traverse( doc, m_pHeader, XML_HEADERENTRIES ) );
					//////////////////////////////////////////////////////////////////////////
					// Datenquellenheader ausgeben
					RETURN_FAILED_HRESULT( doc.FindItem( pDatasource, doc.HeaderTag(), pHeader.ppi() ) );
					RETURN_FAILED_HRESULT( Traverse( doc, pHeader, XML_HEADERENTRIES ) );
					//////////////////////////////////////////////////////////////////////////
					// Datenquellenname
					strExportBase = strDatasourceName;
					strExportBase.Append( L"," );
					strExportBase.Append( strDatasourcePath );
					RETURN_FAILED_HRESULT( EnterCategory( L"Datasource", strExportBase ) );
					//////////////////////////////////////////////////////////////////////////
				}

				// Identifikatorbeschreibungen
				ExportIdentdescriptions( doc, pDatasource );

				//////////////////////////////////////////////////////////////////////////
				// jetzt die eigentlichen Klassen, Objekte etc.
				Traverse( doc, pDatasource, XML_DATASOURCEENTRIES );
			}
		} else {
			if( m_bSeparate ) {

// KK000215
/*--
				COM_TRY {
					ExportTrailer( m_ofs, NULL );
				} COM_CATCH;

				COM_TRY {
					ExportEnd( m_ofs );
				} COM_CATCH;
---*/
				ChangeToCurrentDir();
			}

		}
		return S_FALSE;		// nicht weiter traversieren; wird selbst gemacht
	}
	HRESULT OnHeaderEntry( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pEntry ) {
		if( !bStart ) return S_FALSE;
		CComBSTR	strName;
		CComBSTR	strValue;
		CComBSTR	strType;
		doc.GetItemType( pEntry, strType );
		if( 0 == strType.Length() )
			strType = L"";
		int	type = ( 0 == wcsicmp( L"sys", strType ) ) ? HEADER_SYSTEM
					: ( 0 == wcsicmp( L"ro", strType ) ) ? HEADER_READONLY
					: ( 0 == wcsicmp( L"sysro", strType ) ) ? HEADER_SYSTEMRO
					: ( 0 == wcsicmp( L"dyna", strType ) ) ? HEADER_DYNAMIC
					: HEADER_NORMAL;
		doc.GetItemName( pEntry, strName );
		pEntry->get_text( &strValue );
		USES_CONVERSION;
		COM_TRY {
			ExportDescriptionEx( m_ofs, W2A(strName), W2A(strValue), type );
		} COM_CATCH;
		return S_OK;
	}
	HRESULT OnClass( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pClass ) {
		if( !bStart ) return S_FALSE;
		CComBSTR	strClassname;
		doc.GetItemName( pClass, strClassname );

	//	RETURN_FAILED_HRESULT( EnterCategory( L"Class", strClassname ) );
		//////////////////////////////////////////////////////////////////////////////
		// Identifikator merken
		CComBSTR	strIdent;
		RETURN_FAILED_HRESULT( RetrieveAttribute( pClass, doc.IdentProp(), strIdent ) );
		USES_CONVERSION;
		LPCTSTR	lpszIdent = W2A(strIdent);
		LPTSTR	lpEnd;
		m_ulIdent = strtoul( lpszIdent, &lpEnd, 16 );
		//////////////////////////////////////////////////////////////////////////////
		// Klassennamen merken
		RETURN_FAILED_HRESULT( RetrieveAttribute( pClass, doc.NameProp(), m_strClassname ) );
		//////////////////////////////////////////////////////////////////////////////
		// und jetzt die Klasse selbst durchgehen
// KK000330
		return Traverse( doc, pClass, XML_CLASSENTRIES );
//		return S_OK;
	}
	HRESULT OnObject( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pObject ) {
		if( bStart ) {	// Ausgabe vorbereiten
			//////////////////////////////////////////////////////////////////////////////
			// erst testen, ob Kinderlein da sind (Relationen!!)
			//................
			HRESULT	hr;
			WXMLElementCollection	pItems;
			WXMLElement	pFeatures;
			long	lFeatures = 0;
			doc.FindItem( pObject, doc.FeaturesTag(), pFeatures.ppi() );
			if( S_OK == ( hr = pFeatures->get_children( pItems.ppi() ) ) ) {
				pItems->get_length( &lFeatures );
			}
			_ASSERTE( pFeatures.IsValid() );	// muß vorhanden sein
			WXMLElement	pGeometrys;
			long	lGeometrys;
			doc.FindItem( pObject, doc.GeometrysTag(), pGeometrys.ppi() );
			if( S_OK == ( hr = pGeometrys->get_children( pItems.ppi() ) ) ) {
				pItems->get_length( &lGeometrys );
			}
			if( 0 == lGeometrys ) {
				return S_FALSE;
			}
			_ASSERTE( pGeometrys.IsValid() );	// muß vorhanden sein
			WXMLElement	pCoordinates;
			long	lCoordinates = 0;
			doc.FindItem( pGeometrys, doc.GeometryTag(), doc.NameProp(), doc.PrimaryProp(), pCoordinates.ppi() );
			if( S_OK == ( hr = pCoordinates->get_children( pItems.ppi() ) ) ) {
				pItems->get_length( &lCoordinates );
			}
			CComVariant	vProperty;
			pObject->getAttribute( V_BSTR(&doc.NumberProp()), &vProperty );
			vProperty.ChangeType( VT_I4 );
			m_gs.ON = V_I4(&vProperty);
			m_gs.Id = m_ulIdent;
			m_mf.Init();
			m_lpszUniqueIdent = NULL;
		} 
		else {		// jetzt ausgeben
			HRESULT	hr;
			USES_CONVERSION;
			//////////////////////////////////////////////////////////////////////////////
			// der Konstrukt "if( S_OK == ... ) { lpszGUID = W2A(...); }" funktioniert nicht
			// wegen OutOfScope und so...
			CComBSTR	strGUID;
			hr = RetrieveAttribute( pObject, L"guid", strGUID );
			LPCTSTR lpszGUID = W2A(strGUID);
			if( S_OK != hr ) {
				lpszGUID = "";
			}
			COM_TRY {
				if (EC_USERBREAK == ((CExportBaseImpl *)this) -> ExportData (m_ofs, m_gs, m_mf.m_pFields, m_rs, m_lpszUniqueIdent, lpszGUID, W2A(m_strClassname))) 
					m_nCounter = -1;	// KK000330
			} COM_CATCH;
		}
		return S_OK;
	}
	HRESULT OnGeometry( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pGeometry ) {
		if( bStart ) {
			RETURN_FAILED_HRESULT( m_gs.Init() );
			CComBSTR	strName;
			CComBSTR	strType;
			doc.GetItemName( pGeometry, strName );
			if( 0 != wcsicmp( L"Primary", strName ) )
				return S_FALSE;
			doc.GetItemType( pGeometry, strType );
			m_gs.Typ = ( 0 == wcsicmp( strType, V_BSTR(&doc.PointType()) ) ) ? OT_PUNKT
					: ( 0 == wcsicmp( strType, V_BSTR(&doc.LineType()) ) ) ? OT_KANTE
					: ( 0 == wcsicmp( strType, V_BSTR(&doc.AreaType()) ) ) ? OT_FLAECHE
					: ( 0 == wcsicmp( strType, V_BSTR(&doc.TextType()) ) ) ? OT_TEXT
					: -1;
			if( -1 == m_gs.Typ )
				return S_FALSE;
			m_nContour = 0;
			Traverse( doc, pGeometry, XML_COORDINATES );
		}
		return S_OK;
	}
	HRESULT OnContour( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pCoordinate ) {
		if( bStart ) {
			m_nContourCoordinates = 0;
		} else {
			m_gs.Add( m_nContour, m_nContourCoordinates );
			++m_nContour;
		}
		return S_OK;
	}
	HRESULT OnCoordinate( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pCoordinate ) {
		if( !bStart ) return S_OK;
		CComVariant	vCoordvalue;
		USES_CONVERSION;
		double	X, Y;
		pCoordinate->getAttribute( V_BSTR(&doc.CoordinateXProp()), CLEARED(vCoordvalue) );
		X = atof( W2A(V_BSTR(&vCoordvalue)) );
		pCoordinate->getAttribute( V_BSTR(&doc.CoordinateYProp()), CLEARED(vCoordvalue) );
		Y = atof( W2A(V_BSTR(&vCoordvalue)) );
		m_gs.Add( X, Y );
		++m_nContourCoordinates;
		return S_OK;
	}
#if !defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)
	bool TestAndAdvance (LPOLESTR &rpoleCurr, OLECHAR coleToTest)
	{
		_ASSERTE(coleToTest == *rpoleCurr);
		if (coleToTest == *rpoleCurr) {
			++rpoleCurr;
			return true;
		}
		return false;
	}
	double GetNextDouble (LPOLESTR poleCurr, LPOLESTR *poleNext, OLECHAR cEndChar)
	{
	// das Ende der Doublezahl finden
		for (LPOLESTR pT = poleCurr; L'\0' != *pT; pT++) {
			if (cEndChar == *pT)
				break;
		}

	CComBSTR bstr (pT - poleCurr, poleCurr);
	CComVariant vCoord(bstr.Detach());

		*poleNext = pT;
		if (FAILED(vCoord.ChangeType (VT_R8)))
			return 0.0;
		return V_R8(&vCoord);
	}
	HRESULT OnCoordinates (bool bStart, CTRiASXMLDocument& doc, IXMLElement *pCoords) 
	{
		if (!bStart) 
			return S_FALSE;

	CComBSTR bstrCnt;
	CComBSTR bstrText;

		doc.GetItemName (pCoords, bstrCnt);		// Name enthält Anzahl der Stützpunkte
		pCoords -> get_text (&bstrText);

	// Text durchgehen und Koordinaten herausparsen: "(X/Y/Z)," je Zeile
	int iCnt = _wtol (bstrCnt);
	LPOLESTR poleCurr = bstrText;

		for (int i = 0; i < iCnt; i++) {
			TestAndAdvance (poleCurr, L'(');		// muß mit '(' anfangen

		// X herauslösen
		double X = GetNextDouble (poleCurr, &poleCurr, L'/');

			TestAndAdvance (poleCurr, L'/');

		// Y herauslösen
		double Y = GetNextDouble (poleCurr, &poleCurr, L'/');

			TestAndAdvance (poleCurr, L'/');

		// Z herauslösen
			GetNextDouble (poleCurr, &poleCurr, L')');
			TestAndAdvance (poleCurr, L')');
			TestAndAdvance (poleCurr, L',');

		// Koordinate zur Kontur hinzufügen
			m_gs.Add (X, Y);
			++m_nContourCoordinates;
		}
		return S_OK;
	}
#endif // !defined(_EXPORT_COORDINATES_AS_ATTRIBUTES)
	HRESULT OnFeature( bool bStart, CTRiASXMLDocument& doc, IXMLElement* pFeature ) {
		if( !bStart ) return S_FALSE;
		USES_CONVERSION;
		CComBSTR	strName;
		CComBSTR	strText;
		doc.GetItemName( pFeature, strName );
		pFeature->get_text( &strText );

	// KK000906
		if( !strText ) 
			strText = "";

	long lMCode = atol(W2A(strName));
	LPCTSTR	lpszAddedText = NULL;

		m_mf.Add( lMCode, strText, -1 == lMCode ? _T('T') : _T('A'), lpszAddedText );
		if( S_OK == RetrieveAttribute( pFeature, doc.PrimaryProp(), strName ) ) {
		// wenn diese Objekteigenschaft der UIdent ist, dann diesen separat merken
			m_lpszUniqueIdent = lpszAddedText;
		}
		return S_OK;
	}
};

#pragma	HDR_OFF()

#endif // __ITRiASOEProxyImpl_H__DB102700_1468_11d3_996C_0060085FC1CE
