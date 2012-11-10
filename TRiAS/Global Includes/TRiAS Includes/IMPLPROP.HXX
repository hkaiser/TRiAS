// Interface für Erweiterungen, die Objekteigenschaften generieren ------------
// File: IMPLPROP.HXX

#if !defined(_IMPLPROP_HXX)
#define _IMPLPROP_HXX

// Diverse Typdefinitionen und Konstanten -------------------------------------
typedef LPSTR (*OBJPROPPROC)(long, LPSTR, short);
typedef LPSTR (*OBJPROPEXPROC)(long, LPSTR, short, DWORD);
typedef void (*OBJPROPDELPROC)(DWORD);

typedef LPSTR (CALLBACK *OBJPROPCALLBACK)(long, LPSTR, short);
typedef LPSTR (CALLBACK *OBJPROPEXCALLBACK)(long, LPSTR, short, DWORD);
typedef void (CALLBACK *OBJPROPDELCALLBACK)(DWORD);

enum ObjPropType {
	OProp = 1,
	OPropEx = 2,
};


// die eigentlichen Objekteigenschaften ---------------------------------------
class CImpObjectProperty : public IObjectProperty {
private:
	DWORD m_dwRefCnt;		// reference count
	
	LPSTR m_pFName;
	short m_iFuncID;
	OBJPROPPROC m_pFunc;

protected:
inline	OBJPROPPROC F (void) { return m_pFunc; }

public:
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IObjectProperty specific functions ***
	STDMETHOD_(LPSTR, Invoke) (THIS_ OBJPROPTYPE rgOPT, LONG lONr, 
				   LPSTR pBuffer, short iLen);

// Konstruktor/Destruktor
		CImpObjectProperty (LPCSTR pFName, short iFuncID, OBJPROPPROC pFunc);
	virtual	~CImpObjectProperty (void);

inline  LPSTR FName (void) const { return m_pFName; }
inline	short FuncID (void) { return m_iFuncID; }

virtual ObjPropType isA (void);
virtual LPSTR GetHelpText (LPSTR pBuffer, short iLen);

friend void *GetFuncIDPtr (void *);
};

class CImpObjectPropertyEx : public CImpObjectProperty {
private:
	DWORD m_dwData;

public:
// *** IObjectProperty specific functions ***
	STDMETHOD_(LPSTR, Invoke) (THIS_ OBJPROPTYPE rgOPT, LONG lONr, 
				   LPSTR pBuffer, short iLen);

		CImpObjectPropertyEx (LPCSTR pFName, short iFuncID, 
			   	      OBJPROPEXPROC pFunc, DWORD dwData = 0);
		~CImpObjectPropertyEx (void);

inline	DWORD GetData (void) { return m_dwData; }
	
	ObjPropType isA (void);
	LPSTR GetHelpText (LPSTR pBuffer, short iLen);
};


// Baum enthält alle zur Zeit installierten OPFs ------------------------------
class CObjPropList : public CTree {
protected:
	void UserDelete (void *pObj);

public:
		CObjPropList (void);
		~CObjPropList (void);
};
DeclareLock (CObjectPropertyTree, CImpObjectProperty);


class CImpObjectProps : public IObjectProps {
private:
#if defined(_DEBUG)
	DWORD 			m_dwIRefCnt;	// interface reference count
#endif
	LPUNKNOWN 		m_pUnk;		// Rückverweis
	
	CObjectPropertyTree *	m_pOPList;	// Liste aller registrierten OPFunc's
	short 			m_iFuncIDCnt;	// eindeutiger ID für die Funktionen 
		
protected:
// Memberfunktionen zur Verwaltung der OPF's
	short AddOPF (const char *pFuncName, OBJPROPPROC pFunc);
	short AddOPFEx (const char *pFuncName, OBJPROPEXPROC pFunc, DWORD dwData = 0);
	
// Freigeben einer/aller OPFs
	bool RemoveOPF (short iFuncID);
	bool RemoveAllOPFs (void);		

// Freigeben einer/aller OPFs, wobei pDelF mit eData gerufen wird
	bool RemoveOPFEx (short iFuncID, OBJPROPDELPROC pDelF);
	bool RemoveAllOPFsEx (OBJPROPDELPROC pDelF);

public:
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IObjectProps specific functions ***
	STDMETHOD(EnumObjectProps) (THIS_ LONG lONr, LPENUMUNKNOWN *ppEnumUnk);

// Konstruktor/Destruktor/Initialisierung
		CImpObjectProps (LPUNKNOWN pUnk);
		~CImpObjectProps (void);
		
static CImpObjectProps *CreateInstance (LPUNKNOWN pUnk);

friend class CTriasextension;
};

#endif // _IMPLPROP_HXX

