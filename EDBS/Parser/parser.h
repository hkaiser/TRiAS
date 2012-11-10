// parser.h : Deklaration von Cparser

#ifndef __PARSER_H_
#define __PARSER_H_

#include "resource.h"       // Hauptsymbole
#include "CStringEx.h"


#include "istatus.h"
// Interfacedeklaration für StatusAnzeige -------------------------------------
// 07963818-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(IID_IProgressIndicator, 0x07963818L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 07963819-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CLSID_ProgressIndicator, 0x07963819L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

#include "EDBS_Geometrie.h"
#include "EDBS_Objekte.h"
#include "EDBS_Fachparameter.h"

enum enuSourceFileType {
   EDBS,		// = 0 by default
   ALK,         // = 1
   Atkis_DLM,   // = 2
   Atkis_DKM   // = 3
};

/////////////////////////////////////////////////////////////////////////////
// Cparser
class ATL_NO_VTABLE Cparser : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<Cparser, &CLSID_parser>,
	public ISupportErrorInfo,
	public IDispatchImpl<Iparser, &IID_Iparser, &LIBID_TRiAS_EDBS>
{
public:
	Cparser();
	~Cparser();

DECLARE_REGISTRY_RESOURCEID(IDR_PARSER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(Cparser)
	COM_INTERFACE_ENTRY(Iparser)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY2(IDispatch, Iparser)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// Iparser
public:
	STDMETHOD(put_hWnd)(/*[in]*/ long newVal);
	STDMETHOD(get_Modus)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_Modus)(/*[in]*/ short newVal);
	STDMETHOD(get_Objekte)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(LoadObjects)(/*[out,retval]*/long *lResult);
	STDMETHOD(get_SourceFileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_SourceFileName)(/*[in]*/ BSTR newVal);

//	SetDefaultStatusTexte  --------------------------------------------
void SetDefaultStatusTexte( const char* = NULL, const char* = NULL,
				const char* = NULL, const char* = NULL );
//	CreateStatusDialog  -----------------------------------------------
void CreateProgressIndicator();
//	InitStatusDialog  -------------------------------------------------
HRESULT InitProgressIndicator( const char*, ULONG, const char* );
//	ChangeStatusText  -------------------------------------------------
void ChangeStatusText( const char*, const char* );
//	SetupStatus  ------------------------------------------------------
int SetProgressIndicator( ULONG );
//	ReleaseStatusDialog  ----------------------------------------------
void ReleaseProgressIndicator();
//	NutzerAbbruch  ----------------------------------------------------
bool CheckUserBreak();
//	ResetAbbruch  -----------------------------------------------------
void ResetUserBreak();

private:
	CComObject<CEDBS_Objekte>  *mpobjsEDBS;

	LPPROGRESSINDICATOR	m_pIStatus;
	bool				m_tStatusCreated;
	CString				m_strStatFile;
	CString				m_strStatFilename;
	CString				m_strStatusText1;
	CString				m_strStatusText2;
	HWND				m_hWnd;

	CString mstrSourceFileName;
	CStdioFile	mSourceFile;
	CStringEx strBuffer;
	CStringEx strSearchCriteria;
	enuSourceFileType bSourceFileType;
	short msModus;
	long lBytesParsed;
	int GetWHF( void );
	long GetKoordinate( CStringEx &strRH );
    void readULO( void);
	long GetAnfangspunktDerLinie( void );
	long GetEndpunktDerLinie( double dblRA, double dblHA );
	long GetFunktionDerLinie( CComObject<CEDBS_Geometrie> *pobjGeometrie );
	long GetFachparameter(  CComObject<CEDBS_Fachparameter> *pobjFachparameter );
	long GetLageparameter( double &pdblR, double &pdblH );
	long GetFunktionDesObjekts( double dblRA, double dblHA );
	long GetBesondereInformation( CComObject<CEDBS_Objekt> *pobjEDBS );
	long GetGeometrieangaben( double *pdblR, double *pdblH );
	void readDLOB2005( void );
	void readULQA0000( void );
};

#endif //__PARSER_H_
