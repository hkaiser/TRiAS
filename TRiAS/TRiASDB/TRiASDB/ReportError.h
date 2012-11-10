///////////////////////////////////////////////////////////////////////////
// @doc 
// @module ReportError.h | Funktionen zur Fehlerbehandlung mit IErrorInfo

#if !defined(_REPORTERROR_H__9D700353_872E_11D1_B9F0_080036D63803__INCLUDED_)
#define _REPORTERROR_H__9D700353_872E_11D1_B9F0_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

template <class T, const CLSID *pclsid, const IID* piid>
class CReportErrorComCoClass :
	public CComCoClass<T, pclsid>
{
	static LPCOLESTR GetHelpFileName() { return NULL; }
public:
	typedef CComCoClass<T, pclsid> base_t;
	typedef CReportErrorComCoClass<T, pclsid, piid> errsupport_t;

// Funktionen für das ErrorHandling
	HRESULT Error (HRESULT hr, LPCTSTR pcRoutine = NULL, REFIID riid = *piid)
		{ 
			CString str; FormatMessage (str, (UINT)hr, g_cbTRiAS, pcRoutine);
			return base_t::Error (str, riid, hr); 
		}
	HRESULT Error (LPCTSTR pcText, REFIID riid = *piid)
		{ 
			return base_t::Error (pcText, riid, DISP_E_EXCEPTION); 
		}
	HRESULT Error (LPCTSTR pcText, HRESULT hr, REFIID riid = *piid)
		{
			return base_t::Error (pcText, riid, hr); 
		}

#if defined(_DEBUG)
	HRESULT GenerateError (LPCTSTR strExpr, LPCTSTR strFile, int line, HRESULT hRes, LPCTSTR pcRoutine = NULL, REFIID riid = *piid)
	{
		return ::GenerateErrorE (strExpr, strFile, line, *pclsid, riid, GetHelpFileName(), hRes, g_cbTRiAS, pcRoutine);
	}
#else
	HRESULT GenerateError (HRESULT hRes, REFIID riid = *piid)
	{
		return ::GenerateErrorE (*pclsid, riid, GetHelpFileName(), hRes, g_cbTRiAS);
	}
#endif
};

///////////////////////////////////////////////////////////////////////////////
// FehlerMeldung formatieren und ausgeben
#if defined(_USE_NEW_ERRORHANDLING)
#if defined(_DEBUG)
#define REPORT_DBERROR_IID(hr,rout,riid)	GenerateError(g_cbNil,THIS_FILE,__LINE__,hr,TEXT(rout),riid)
#define REPORT_DBERROR_ROUT(hr,rout)		GenerateError(g_cbNil,THIS_FILE,__LINE__,hr,TEXT(rout))
#define REPORT_DBERROR(hr)					GenerateError(g_cbNil,THIS_FILE,__LINE__,hr)
#else
#define REPORT_DBERROR_IID(hr,rout,riid)	GenerateError(hr)
#define REPORT_DBERROR_ROUT(hr,rout)		GenerateError(hr)
#define REPORT_DBERROR(hr)					GenerateError(hr)
#endif // _DEBUG
#else
#if defined(_DEBUG)
#define REPORT_DBERROR_IID(hr,rout,riid)	Error(hr,TEXT(rout),riid)
#define REPORT_DBERROR_ROUT(hr,rout)		Error(hr,TEXT(rout))
#define REPORT_DBERROR(hr)					Error(hr)
#else
#define REPORT_DBERROR_IID(hr,rout,riid)	Error(hr,NULL,riid)
#define REPORT_DBERROR_ROUT(hr,rout)		Error(hr)
#define REPORT_DBERROR(hr)					Error(hr)
#endif // _DEBUG
#endif // _USE_NEW_ERRORHANDLING

// Kein Speicher mehr !
#define REPORT_OUTOFMEMORY()				Error (g_cbNoMemory, E_OUTOFMEMORY)


#endif // !defined(_REPORTERROR_H__9D700353_872E_11D1_B9F0_080036D63803__INCLUDED_)
