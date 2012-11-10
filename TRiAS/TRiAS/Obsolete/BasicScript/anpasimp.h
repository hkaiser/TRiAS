#ifndef _ANPASIMP_H
#define _ANPASIMP_H

typedef class CImpIAnpassen *LPIMPIANPASSEN;
class CMacroOrg;

class CImpIAnpassen : public IAnpassen
{
private:	
	HRESULT FInit();

	bool	CutAcc (char *pc, CString &str);
	void	IDTest (	IListElement **ppILE, 
					UINT uiPreID, UINT uiSucID, 
					UINT &uiID);
	HRESULT InsertMenu(	HMENU hMenu, 
						UINT uiPosition, UINT uiFlags, UINT uiID, 
						LPCTSTR pccNewItem);	
	HRESULT	Fill(	LPCTSTR c, 
					const CString& strNewMenuEntry,
					UINT uiID, 
					IListElement *pILstEl_ListItem_Up,
					IListElement *pILE,
					bool fMacro);
	HRESULT GetListItems(	IEnum<WListElement> *pIEnum,
							CTreeCtrl *pTCtrl,
							HTREEITEM hTreeItem);
	HRESULT SetNewItemInLists (	UINT uiOldID,
								UINT uiCmpID,
								UINT &uiNewID,
								short i,
								const CString& strNewMenuEntry,
								const CString& strNew,
								IListElement *pILstEl_ListItem_Up,
								IListElement *pILE_After,
								bool fMacro);
	HRESULT SetNewItemInLists (	IEnum<WListElement> *pIEnum,
								UINT uiPreID, 
								UINT uiSucID, 
								UINT &uiNewID,
								const CString& strNew,
								const CString& strNewMenuEntry,
								IListElement *pILstEl_ListItem_Up,
								bool fMacro);
	HRESULT AddString (	CTreeCtrl *pTCtrl, LPSTR pc, UINT uiID, 
						HTREEITEM hParentTreeItem,
						HTREEITEM *phTreeItem);
	HRESULT SetNewMenuEntry(UINT uiID,
							UINT uiCmpID,
							const CString& strNew,
							IListElement *pILE,
							IListElement *pILstEl_ListItem_Up );
	HRESULT SetNewMenuEntry(IEnum<WListElement> *pIEnum,
							UINT uiID,
							const CString& strNew,
							IListElement *pILE_ListItem_Up);
	HRESULT GetEnum(IEnum<WListElement> **ppIEnum );
	HRESULT DeleteItem(	UINT ui,
						UINT uiIDDel,
						IListElement *pILE_Up,
						IListElement *pILE);
	HRESULT DeleteItem(	IEnum<WListElement> *pIEnum,
						UINT uiID,
						IListElement *pILE);

	UINT			m_uiNewID;

protected:
    ULONG           m_cRef;      //Interface reference count
    LPUNKNOWN       m_pUnkOuter; //For delegation      
    CMacroOrg		*m_pMacroOrg;

public:
	static CImpIAnpassen* Create(	LPUNKNOWN pUnkOuter, CMacroOrg *pMacroOrg);
	
    CImpIAnpassen(	LPUNKNOWN pUnkOuter, CMacroOrg* pMacroOrg);
    ~CImpIAnpassen();

	UINT GetOffset(void);
	LPIMPICOMMANDS GetCommands(void);

	/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
	STDMETHOD_(unsigned long, AddRef)(void);
    STDMETHOD_(unsigned long, Release)(void);

    /* IAnpassen methods */
	STDMETHOD(ReadMenu)(CWnd *pTC);
	STDMETHOD(SetNewMenu)(	UINT uiPreID, 
							UINT uiSucID, 
							 UINT &uiNewID,
							LPCSTR pNew, 
							LPCSTR pNewMenuEntry,
							bool fMacro);
	STDMETHOD(SetNewMenuEntry)(	UINT uiID, 
								LPCSTR pNew);
	STDMETHOD(GetDescription)(	LPSTR pc, UINT uiLen,
								UINT uiMenuID, bool &fMacro);
	STDMETHOD(DeleteItem)(UINT uiID);
	STDMETHOD_(void, GetNewMacroID)(UINT *puiID);
	STDMETHOD_(void, SetNewMacroID)(UINT uiID);
};

HRESULT GetNextListElement (IListElement **ppILE, IEnum<WListElement> *pIEnum, 
							LPSTR c, UINT &uiID);  

#endif // _ANPASIMP_H                   


