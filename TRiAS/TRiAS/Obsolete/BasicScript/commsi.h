#ifndef _COMMSI_H
#define _COMMSI_H

typedef class CImpICommands *LPIMPICOMMANDS;

class CImpICommands : public ICommands
{
private:	
	class XPersistStream : public IPersistStream
	{
		bool m_fIsDirty;
		ULONG m_cRef;

		CImpICommands *m_pICommands;
		
	public: 
		XPersistStream (CImpICommands *pICommands);
		~XPersistStream ();
		
		STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
		STDMETHOD_(unsigned long, AddRef)(void);
		STDMETHOD_(unsigned long, Release)(void);
		
		STDMETHOD (GetClassID) (LPCLSID);
		STDMETHOD (IsDirty) (void);
		STDMETHOD (Load) (LPSTREAM);
		STDMETHOD (Save) (LPSTREAM, BOOL);
		STDMETHOD (GetSizeMax) (ULARGE_INTEGER FAR *);

	} m_PersStream ;
	
	friend XPersistStream;
	friend class CImpISave;
	friend class CImpIAnpassen;
	friend class CImpIAnalyse;
	friend class CImpIProcess;

	HRESULT FInit(void);

	HRESULT GetMenuStructure (	HMENU hMenu, 
								IListElement *pILE);
	HRESULT GetMenuStructureFromFile(HMENU hMenu);
	HRESULT InsertMenuItem(	LPCSTR cMenuEntry, 
							UINT uiID,
							IListElement **ppIListItem, 
							IListElement *pILE_ListItem_Up);
	HRESULT InsertMenuItem(	LPCSTR cMenuEntry, 
							UINT uiMenuID, 
							IListElement *pILstEl_Up);
	HRESULT InsertMenu(HMENU hMenu, IListElement *pILE);

	HRESULT	file_out	(LPCSTR pc);
	HRESULT file_in		(LPCSTR pc);
	HRESULT storage_in	(LPSTREAM pIStream);
	HRESULT storage_out	(LPSTREAM pIStream);
	HRESULT out			(os_bstream &stream);
	HRESULT in			(os_bstream &stream);

 	HRESULT GetEnum (IEnum<WListElement> ** ppIEn) ;
	HRESULT GetMenuItems (HMENU hMenu);
	HRESULT InsertMenuItem (	LPCSTR cMenuEntry, 
								UINT uiMenuID, 
								IListElement *pILstEl_ListItem_Up,
								IListElement *pILE_After);
	HRESULT InsertCommand (	LPCSTR pcMacroName, 
								UINT uiMenuID,
								bool fMacro);							
	HRESULT FireEvent (UINT uiMenuID);
	HRESULT GetDescription (LPSTR pc, UINT uiLen,
								UINT uiMenuID, bool &fMacro);
	HRESULT DeleteItem (UINT uiID,
							IListElement *pILstEl_Up, 
							IListElement *pILE);
	HRESULT SaveFile (void);
	HRESULT LoadFile (void);

	ICommand *GetCommand (UINT uiID);
	IScriptContainer	*m_pIScriptContainer;

	UINT				m_uiTrashID;
	UINT				m_uiDropDownID;
	CListItem						m_ListItem;
	map< UINT,WCommand,less<UINT> >	m_mapCommand;
	UINT				m_iState;

protected:
    ULONG					m_cRef;      //Interface reference count
    LPUNKNOWN				m_pUnkOuter; //For delegation      
	
public:
	static CImpICommands* Create(LPUNKNOWN pUnkOuter, IScriptContainer *pISC);
	
    CImpICommands(LPUNKNOWN pUnkOuter, IScriptContainer *pISC);
    ~CImpICommands();

	/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
	STDMETHOD_(unsigned long, AddRef)(void);
    STDMETHOD_(unsigned long, Release)(void);

};


HRESULT MakeFileName(LPCSTR pPathName, LPSTR pNameToUse, LPCSTR pcFileExt);
HRESULT GetNextListElement (IListElement **ppILE, 
							IEnum<WListElement> *pIEnum,
							LPSTR c, UINT &uiID);  

#define MIN_SEPARATORID 0xA000
#define MIN_DROPDOWNID 0xB000

#endif // _COMMSI_H                   
					  

