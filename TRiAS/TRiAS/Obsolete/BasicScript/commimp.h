#ifndef _COMMIMP_H
#define _COMMIMP_H

class CImpICommand : public ICommand
{
private:	
	HRESULT FInit();		

	class XPersistBStream : public IPersistBStream 
	{
	private:
		CImpICommand *m_pParent;

	public:
			XPersistBStream (CImpICommand *pParent);

	// *** IUnknown methods
		STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj);
		STDMETHOD_ (ULONG, AddRef) (THIS);
		STDMETHOD_ (ULONG, Release) (THIS);
		
	// *** IPersistBStream methods
		STDMETHOD (GetClassID) (THIS_ CLSID *pClassID);	
		STDMETHOD (Load) (THIS_ os_bstream *stream);
		STDMETHOD (Save) (THIS_ os_bstream *stream);
	} m_BStream;
	friend XPersistBStream;

protected:
    ULONG				m_cRef;      //Interface reference count
	CString				m_strCommandName;
	bool				m_fMacro;

public:
	static CImpICommand* Create(CString& strCommandName,
								bool fMacro);
	
    CImpICommand(	CString& strCommandName,
					bool fMacro);
    CImpICommand();
    virtual ~CImpICommand();

/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
	STDMETHOD_(unsigned long, AddRef)(void);
    STDMETHOD_(unsigned long, Release)(void);

	STDMETHOD (GetDescription) (LPSTR pDesc, UINT uiLen, bool &fMacro);		// liefert Beschreibung des Kommandos
	STDMETHOD (InitCommand) (void);
	STDMETHOD (FireEvent) (UINT uiID) ;

	STDMETHOD (GetClassID) (THIS_ CLSID *pClassID) 
		{ return ResultFromScode(E_NOTIMPL); }	
	STDMETHOD (Load) (THIS_ os_bstream *stream) 
		{ return ResultFromScode(E_NOTIMPL); }
	STDMETHOD (Save) (THIS_ os_bstream *stream) 
		{ return ResultFromScode(E_NOTIMPL);}

	friend void os_write (os_bstream& stream, const CImpICommand& IC);
	friend void os_read (os_bstream& stream, CImpICommand& IC);

	OS_POLY_FUNCTION((CImpICommand *));
};

void os_write (os_bstream &, const CImpICommand&);
void os_read (os_bstream &, CImpICommand&);

OS_POLY_CLASS(CImpICommand);
OS_STREAM_OPERATORS(CImpICommand);

typedef class CImpICommand *LPIMPICOMM;

typedef class CImpIMenu *LPIMPIMENU;

class CImpIMenu : public CImpICommand
{
private:	
	HRESULT FInit();
	HMENU m_hMenu;

protected:
	LPUNKNOWN GetMacroScripts(void);
	
    
public:	
	static CImpIMenu* Create(	CString& strCommandName,
								bool fMacro);

    CImpIMenu(	CString& strCommandName, bool fMacro);
    CImpIMenu();
    ~CImpIMenu();

	STDMETHOD_(HRESULT, InitCommand) (void);
	STDMETHOD_(HRESULT, FireEvent) (UINT uiID);
	STDMETHOD_(HRESULT, GetDescription) (LPSTR, UINT, bool &fMacro);
	
	STDMETHOD (GetClassID) (CLSID *pClassID); 
	STDMETHOD (Load) (os_bstream *stream);
	STDMETHOD (Save) (os_bstream *stream);

	friend void os_write (os_bstream& stream, const CImpIMenu& IM);
	friend void os_read (os_bstream& stream, CImpIMenu& IM);

	OS_POLY_FUNCTION((CImpIMenu *));
};

void os_write (os_bstream &, const CImpIMenu&);
void os_read (os_bstream &, CImpIMenu&);

OS_POLY_CLASS(CImpIMenu);
OS_STREAM_OPERATORS(CImpIMenu);

typedef class CImpINotification *LPIMPINOTIF;

class CImpINotification : public CImpICommand
{
private:	
	HRESULT FInit();		

protected:

public:
	static CImpINotification * Create (	CString& strCommandName,
										bool fMacro);

    CImpINotification(	CString& strCommandName,
						bool fMacro);
    ~CImpINotification();

	STDMETHOD_(HRESULT, InitCommand) (void) ;
	STDMETHOD_(HRESULT, FireEvent) (UINT uiID) ;
	STDMETHOD_(HRESULT, GetDescription) (LPSTR, UINT, bool &fMacro) ;
};

typedef class CImpIWndNotification *LPIMPIWNDNOTIF;

class CImpIWndNotification : public CImpICommand
{
private:	
	HRESULT FInit();

protected:

public:	
	static CImpIWndNotification * Create (	CString& strCommandName,
											bool fMacro);

    CImpIWndNotification(	CString& strCommandName,
							bool fMacro);
    ~CImpIWndNotification();

	STDMETHOD_(HRESULT, InitCommand) (void) ;
	STDMETHOD_(HRESULT, FireEvent) (UINT uiID) ;
	STDMETHOD_(HRESULT, GetDescription) (LPSTR strDesc, UINT uiLen, bool &fMacro) ;
};

extern HRESULT RunThread(	IScriptContainer *pISC,
							CebInstance *pebInstance, 
							const CString& strMacroName,
							bool fAutoSt);

HRESULT CreateObject(CLSID *pClID, LPVOID *ppv);

#endif // _COMMIMP_H                   


