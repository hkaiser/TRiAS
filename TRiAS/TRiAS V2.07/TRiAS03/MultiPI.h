/*
Datei: MULTIPI.H

Der Modul realisiert die Unterteilung (Verwaltung) mehrerer Progressindicatoren.

Erarbeitet:	J. Benkenstein				Stand vom: 4.4.1997
*/

#ifndef _MULTIPI_H
#define _MULTIPI_H

// JG Ressourcen includen
#include "TRIAS03.H"

DefineSmartInterface(ProgressIndicator2);
DefineSmartInterface(ProgressIndicator);

class CMultiProgressIndicator;

class CSubIndicator : 
	public IProgressIndicator,
	public CComDualImpl<IProgressIndicator2, &IID_IProgressIndicator2, &LIBID_TRiASHelperLib,
		TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_IProgressIndicator2>,
	public CComObjectRoot
{
private:
	ULONG	m_ulMinBer,		//	Bereichswerte: min. Wert
			m_ulMaxBer,		//				   max. Wert	
			m_ulMinWert,	//	akt. min. Wert
			m_ulMaxWert,	//	akt. max. Wert
			m_ulActPos;		//	akt. Position

	WProgressIndicator2 m_wPI;	// Ausgabe-PI
	string	m_strPercentText;	// Text für die Prozente

// JG Hilfsfunktion zum setzen des Statustextes
	HRESULT SetStatusText();

public:
		CSubIndicator (void);		
		~CSubIndicator (void);		

// *** IProgressIndicator methods ***
	STDMETHOD_(HWND, InitNew)(THIS_ HWND hWnd, DWORD dwReserved);
	STDMETHOD(Restart)(THIS_ ULONG uiMinPos, ULONG ulMaxPos, DWORD dwFlags);
	STDMETHOD(ChangeText)(THIS_ DWORD dwWhichText, LPCSTR pcNewText);
	STDMETHOD(RetrieveText)(THIS_ DWORD dwWichText, LPSTR cbText, ULONG uiLen);

	STDMETHOD_(int, SetPosition)(THIS_ ULONG uiNewPos);
	STDMETHOD_(BOOL, WasCanceled)(THIS);
		
//	Methoden der Basisklasse
	STDMETHOD(Restart)(ULONG ulMinPos, ULONG ulMaxPos, PIFLAGS Flags);
	STDMETHOD(ChangeText)(PIFLAGS fWhichText, BSTR bstrNewText);
	STDMETHOD(RetrieveText)(PIFLAGS fWichText, BSTR *pbstrText);
	STDMETHOD(IsCanceled)(THIS);
//#if _MSC_VER >= 1100
	STDMETHOD(InitNew)(LONG hWnd, DWORD dwReserved, LONG *phWnd);
//#else
//	STDMETHOD(InitNew)(HWND hWnd, DWORD dwReserved, HWND *phWnd);
//#endif // _MSC_VER >= 1100
	STDMETHOD(SetPosition)(THIS_ ULONG ulNewPos, INT *piPercent);
	STDMETHOD(IncrementPosition)(INT *piPercent);
	STDMETHOD(get_Flags)(PIFLAGS *prgFlags);
	STDMETHOD(put_Flags)(PIFLAGS rgFlags);
	STDMETHOD(RetrieveRange)(ULONG *pulMinPos, ULONG *pulMaxPos);

	BEGIN_COM_MAP(CSubIndicator)
		COM_INTERFACE_ENTRY(IProgressIndicator)	// JG
		COM_INTERFACE_ENTRY(IProgressIndicator2)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	friend class CMultiProgressIndicator;
};


class CMultiProgressIndicator : // public IMultiProgressIndicator,
	public CComDualImpl<IMultiProgressIndicator, &IID_IMultiProgressIndicator, &LIBID_TRiASHelperLib,
		TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_IMultiProgressIndicator>,
	public CComObjectRoot,
	public CComCoClass<CMultiProgressIndicator, &CLSID_MultiProgressIndicator>
{
private:
	int m_iRangeCnt;				//	Anzahl der verwalteten Bereiche
	CComObject<CSubIndicator> **m_ppPI;	//	Zeiger auf Vektor der verwalteten PIs
	
public:
		CMultiProgressIndicator (void);					
		~CMultiProgressIndicator (void);

	STDMETHOD(Init)(int iRangeCnt, IProgressIndicator2 *pPI);			//	Init: Ausgabe-PI
	STDMETHOD(GetRange)(int iRange, IProgressIndicator2 **ppPI);		//	PI zum Bereich lesen
	STDMETHOD(get_RangeCnt)(int *piRangeCnt);							//	lese Bereischsanzahl

	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_MULTIPI_RGS);

	BEGIN_COM_MAP(CMultiProgressIndicator)
		COM_INTERFACE_ENTRY(IMultiProgressIndicator)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

protected:
	STDMETHOD(DeletePIs)(void);
};

#endif		//	_MULTIPI_H


	
