// GBM-Objekteigenschaften
// ObjProp.h

#ifndef _GBM_OBJPROP_H_
#define _GBM_OBJPROP_H_

//class COPAngeschlGS : public IObjectProperty
class COPAngeschlGS : public IObjectProperty2
{
protected:
	CMapStringToPtr m_mapNameToONr;
	CMapStringToPtr m_mapName;
	long m_lGebIdent;
	long m_lHofIdent;
	long m_lDachIdent;
	long m_lGS_Ident;
	CString GetObjectName( long );
	CString GetIdentNummer( long );
	BOOL IsObjectOf( UINT, long );
	ULONG			m_ulCount;
	ULONG			m_ulCumu;
	ULONG			m_ulRefCnt;

	CMapPtrToWord	m_mapONr;
	CMapPtrToWord	m_mapModi;

public:
	BOOL SetName( const char*, const char*, char, BOOL );
	BOOL RemoveName( const char*, const char*, char );
	BOOL AddName( const char*, const char*, char );
	void InitData();
			COPAngeschlGS();
			~COPAngeschlGS();

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags/*=NULL*/);

	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/);

	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/);

// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

// Implementation der Funktionalität
	BOOL	AddONr( long onr );
	BOOL	RemoveONr( long onr );
	BOOL	SetONr( long onr, BOOL flag );
	BOOL	IstAngeschlossen( long onr );
};

//class COPGedrucktGS : public IObjectProperty
class COPGedrucktGS : public IObjectProperty2
{
protected:
	ULONG			m_ulCount;
	ULONG			m_ulCumu;
	ULONG			m_ulRefCnt;

	CMapPtrToWord	m_mapONr;
	CMapPtrToWord	m_mapModi;

public:
	UINT			m_uiInfo;
	UINT			m_uiHelp;

			COPGedrucktGS();
			~COPGedrucktGS();

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags/*=NULL*/);

	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/);

	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/);

// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

// Implementation der Funktionalität
	BOOL	AddONr( long onr );
	BOOL	RemoveONr( long onr );
	BOOL	SetONr( long onr, BOOL flag );
	BOOL	IstGedruckt( long onr );
};

class COPBeitragsartGS : public IObjectProperty
{
protected:
	CStringArray m_arrText;
	ULONG			m_ulCount;
	ULONG			m_ulCumu;
	ULONG			m_ulRefCnt;

	CMapPtrToWord	m_mapONr;

public:
			COPBeitragsartGS();
			~COPBeitragsartGS();

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags/*=NULL*/);

	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/);

	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/);

// Implementation der Funktionalität
	BOOL	SetONr( long onr, WORD flag );
};

class COPEigentumGS : public IObjectProperty
{
protected:
	CStringArray m_arrText;
	ULONG			m_ulCount;
	ULONG			m_ulCumu;
	ULONG			m_ulRefCnt;

	CMapPtrToWord	m_mapONr;

public:
			COPEigentumGS();
			~COPEigentumGS();

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags/*=NULL*/);

	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/);

	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/);

// Implementation der Funktionalität
	BOOL	SetONr( long onr, WORD flag );
};

#endif	// _GBM_OBJPROP_H_
