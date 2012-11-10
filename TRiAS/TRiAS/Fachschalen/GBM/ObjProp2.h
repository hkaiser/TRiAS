// ObjProp2.h

typedef double (*GetDblWertFkt)( long );
typedef int (*SetDblWertFkt)( long, double );
typedef long (*GetLngWertFkt)( long );
typedef int (*SetLngWertFkt)( long, long );

class COPDouble : public IObjectProperty2
{
protected:
	ULONG			m_ulCount;
	double			m_ulCumu;
	ULONG			m_ulRefCnt;
	CString			m_strPropInfo;
	CString			m_strHelpInfo;

	GetDblWertFkt	m_pFktGetWert;
	SetDblWertFkt	m_pFktSetWert;

	CMapStringToString	m_mapONr;
	CMapStringToString	m_mapModi;

public:
			COPDouble();
	virtual	~COPDouble();

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
				ULONG *pulWritten/*=NULL*/) = 0;
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/);

// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

// Implementation der Funktionalität
	BOOL	AddONr( long onr );
	BOOL	RemoveONr( long onr );
	BOOL	SetONr( long onr, double wert );
	double	Wert( long onr );
	virtual void	RewriteModi( void ) = 0;

protected:
	virtual double	RequeryWert( long onr ) = 0;
};

class COPLong : public IObjectProperty2
{
protected:
	ULONG			m_ulCount;
	ULONG			m_ulCumu;
	ULONG			m_ulRefCnt;
	CString			m_strPropInfo;
	CString			m_strHelpInfo;

	GetLngWertFkt	m_pFktGetWert;
	SetLngWertFkt	m_pFktSetWert;

	CMapPtrToPtr	m_mapONr;
	CMapPtrToPtr	m_mapModi;

public:
			COPLong();
	virtual	~COPLong();

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
				ULONG *pulWritten/*=NULL*/) = 0;
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/);

// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

// Implementation der Funktionalität
	BOOL	AddONr( long onr );
	BOOL	RemoveONr( long onr );
	BOOL	SetONr( long onr, long wert );
	long	Wert( long onr );
	virtual void	RewriteModi( void ) = 0;

protected:
	virtual long	RequeryWert( long onr ) = 0;
};


class COP_AGGS : public COPDouble
{
public:
			COP_AGGS();
	virtual	~COP_AGGS();
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten );
	virtual void	RewriteModi( void );

protected:
	virtual double	RequeryWert( long onr );
};

class COP_FLG : public COPDouble
{
public:
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

			COP_FLG();
	virtual	~COP_FLG();
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten );
	virtual void	RewriteModi( void );

protected:
	virtual double	RequeryWert( long onr );
};

class COP_GEFS : public COPDouble
{
public:
			COP_GEFS();
	virtual	~COP_GEFS();
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten );
	virtual void	RewriteModi( void );

protected:
	virtual double	RequeryWert( long onr );
};

class COP_TIEB : public COPDouble
{
public:
			COP_TIEB();
	virtual	~COP_TIEB();
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten );
	virtual void	RewriteModi( void );

protected:
	virtual double	RequeryWert( long onr );
};

class COP_KAT : public COPDouble
{
public:
			COP_KAT();
	virtual	~COP_KAT();
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten );
	virtual void	RewriteModi( void );

protected:
	virtual double	RequeryWert( long onr );
};

class COP_FLN : public COPLong
{
public:
			COP_FLN();
	virtual	~COP_FLN();
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/);
	virtual void	RewriteModi( void );

protected:
	virtual long	RequeryWert( long onr );
};

class COP_TIEF : public COPLong
{
public:
			COP_TIEF();
	virtual	~COP_TIEF();
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/);
	virtual void	RewriteModi( void );

protected:
	virtual long	RequeryWert( long onr );
};
