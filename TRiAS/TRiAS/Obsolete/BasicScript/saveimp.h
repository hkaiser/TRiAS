#ifndef _SAVEIMP_H
#define _SAVEIMP_H

class CMacroOrg;

#ifndef _PSSTATE
typedef enum {
	PSSTATE_UNINIT,
	PSSTATE_WRITE,
	PSSTATE_ZOMBIE,
	PSSTATE_HANDSOFF
} PSSTATE;
#define _PSSTATE
#endif

class CImpISave : public ISave
{
private:	
	
	HRESULT		FInit();		
	HRESULT		OpenStream(LPSTORAGE pIStorage);
	HRESULT		OpenStreamOnly(LPSTORAGE pIStorage);
	HRESULT		Create(LPSTORAGE pIStorage, LPSTREAM *ppIStream, LPCSTR pName);
	HRESULT		Open(LPSTORAGE pIStorage, LPSTREAM *ppIStream, LPCSTR pName);

	HRESULT		Run(void);
	LPIMPICOMMANDS GetCommands(void);

	bool		m_fIsDirty;
	short		m_iState;

	LPSTORAGE	m_pISubStorage;
	LPSTREAM	m_pIStream;

protected:
    ULONG           m_cRef;      //Interface reference count
    LPUNKNOWN       m_pUnkOuter; //For delegation      
    CMacroOrg 		*m_pMacroOrg;

public:
	static CImpISave* Create(LPUNKNOWN pUnkOuter, CMacroOrg *pMacroOrg);
	
    CImpISave(LPUNKNOWN pUnkOuter, CMacroOrg* pMacroOrg);
    ~CImpISave();

	STDMETHOD (SaveFile) (void);
	STDMETHOD (LoadFile) (void);
	STDMETHOD (InsertMenu)(HMENU hMenu);
	STDMETHOD (SaveToStorage) (bool fClearDirty);
	STDMETHOD (LoadFromStorage) (void);
	STDMETHOD (DestroyStorage) (int IDS);

	/* IPersistStorage methods */
	STDMETHOD (GetClassID) (LPCLSID pClsID);
	STDMETHOD (IsDirty) (void);
    STDMETHOD (InitNew) (LPSTORAGE);
	STDMETHOD (Load)(LPSTORAGE);
	STDMETHOD (Save) (LPSTORAGE, BOOL);
	STDMETHOD (SaveCompleted) (LPSTORAGE);
	STDMETHOD (HandsOffStorage) (void);

	/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
	STDMETHOD_(unsigned long, AddRef)(void);
    STDMETHOD_(unsigned long, Release)(void);
};

typedef CImpISave * LPIMPISAVE;

#endif // _SAVEIMP_H                   


