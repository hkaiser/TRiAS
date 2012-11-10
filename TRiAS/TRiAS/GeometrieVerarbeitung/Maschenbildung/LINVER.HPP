/* 
	File: LINVER.HPP
	Allgemeine TRiAS-Schnittstelle.

	Erarbeitet: J. Benkenstein						Stand vom 11.4.1997
*/

#ifndef _LINVER_HPP
#define _LINVER_HPP

///////////////////////////////////////////////////////////////////////////////
// LizensierungsKlasse
#if defined(_DEBUG)
extern "C" bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

class CMyLicense
{
protected:
	static BOOL VerifyLicenseKey(BSTR bstr)
	{
	CComBSTR bstrKey;

		USES_CONVERSION;
		if ((GetLicenseKey (0, &bstrKey) && !wcscmp (bstrKey, bstr)) ||
			 ::SetLicensed (OLE2A(bstr)))
		{
			return TRUE;
		}
		return FALSE;
	}

	static BOOL GetLicenseKey (DWORD, BSTR *pBstr) 
	{
	CComBSTR bstrKey (_MAX_PATH, (LPCOLESTR)NULL);

		if (!::GetLicenseKey (bstrKey.m_str, _MAX_PATH))
			return FALSE;

		*pBstr = bstrKey.Detach(); 
		return TRUE;
	}

	static BOOL IsLicenseValid() { return g_fGlobalLic || ::GetLicensed(); }
};

class CLinVerExtension : public CTriasExtension, 
						 public CSyncMonitor, 
						 public CComCoClass<CLinVerExtension, &CLSID_LinienVerfolgung>
//			public CComDualImpl<IExtLinienVerfolgung, &IID_IExtLinienVerfolgung, &LIBID_LinienVerfolgung>,
//			public CComISupportErrorInfoImpl<&IID_IExtLinienVerfolgung> 	
{
public:
// 	Konstruktor / Destruktor
	CLinVerExtension (void);
	~CLinVerExtension (void);

//  überladene virtuelle Funktion(en)
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);
	STDMETHOD_(BOOL, MenuCommand) (UINT MenuItemID, HWND hWnd);
	
	BEGIN_COM_MAP(CLinVerExtension)
		COM_INTERFACE_ENTRY(ITriasXtension)
		COM_INTERFACE_ENTRY(ITriasXtension2)
		// COM_INTERFACE_ENTRY(IExtLinienVerfolgung)
		// COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(CLinVerExtension, g_pTE)
	DECLARE_CLASSFACTORY2(CMyLicense)

/*
//	Interface Methoden
	STDMETHOD(LinesUnion)(IEnumObjectsByNumber *pInput,		//	Objektnummern-Eingabe-Strom
						 double	dTolerance,					//	Fangbereich zweier Stützpunkte
						 VARIANT_BOOL bOutputMerkmal,		//	Merkmale der Vereinigten vererben
						 VARIANT_BOOL bCreateAreas,			//	TRUE/FALSE erzeuge Flächen/Linien
						 IProgressIndicator2 *pPI,			//	Fortschrittsanzeige
						 IEnumObjectsByNumber **ppUnion,	//	Objektnummern der Vereinigten
						 IEnumObjectsByNumber **ppUsed);	//	Objektnummern der zur Vereinigung beitragenden
*/

//	HRESULT FinalConstruct (void);
//	void FinalRelease (void);
};

#endif // _LINVER_HPP
