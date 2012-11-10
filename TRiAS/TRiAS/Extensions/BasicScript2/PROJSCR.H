#ifndef _PROJSCR_H
#define _PROJSCR_H
 
/////////////////////////////////////////////////////////////////////////////////
// Wrapper für BasicScript-Debuggercontrol


#define GNSCRIPT_POPUPMENU_ID	0
#define FTSCRIPT_POPUPMENU_ID	1
#define OFSCRIPT_POPUPMENU_ID	2

#define GENKEY_POPUPMENU_ID		3
#define FTKEY_POPUPMENU_ID		4
#define OFKEY_POPUPMENU_ID		5

#define GENROOT_POPUPMENU_ID	6
#define FTROOT_POPUPMENU_ID		7
#define OFROOT_POPUPMENU_ID		8

#define FUNCTION_POPUPMENU_ID	9
#define INVALID					-1
#define DEBUGGERFOCUSED			10

#define IMAGE_PROJECTMACROS		5		
#define IMAGE_TEMPLATEMACROS	5		
#define IMAGE_OPENMACROS		7 // Tasche 
#define IMAGE_CLOSEMACROS		6 // Tasche 
#define IMAGE_GENERALKEY		8 
#define IMAGE_FILTERKEY			9 
#define IMAGE_OBJECTFEATUREKEY	10
#define IMAGE_SUBSCRIPT			11 
#define IMAGE_SUPERSCRIPT		12
#define IMAGE_FUNCTION			13
#define IMAGE_PROCEDURE			14

/////////////////////////////////////////////////////////////////////////////////
// allgemeine ProjectScripts
class CProjectScript2 : 
	public ITreeItem,
	public IPersist,
	public IObjManHelper,
	public IBSProperty
{
	// Constructors
public:
	
	CProjectScript2();
	virtual ~CProjectScript2();

	virtual HRESULT Init(IObjectManagement *pIOM, IStreamInfo * pIS, REFIID riid);
public:
	// *** IObjManHelper-Methods ***
	STDMETHOD(Open) (LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT &, BOOL fCreateTemp = false);
	STDMETHOD(Import)(REFIID riid, LPCSTR lpcstrFileName, LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT &);
	STDMETHOD(New)	(LPSTR *ppcMacroText);
	STDMETHOD(Save) (LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag);
	STDMETHOD(SaveAs) (LPCSTR, LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag);
	STDMETHOD(Delete) (void);
	STDMETHOD(Rename) (LPCSTR lpcstrNewName);
	STDMETHOD(NewFunction) (				
				LPCSTR lpcstrName,
				LPCSTR lpcstrDecl,
				LPCSTR lpcstrType,
				LPCSTR lpcstrParams,
				LPCSTR lpcstrComment,
				LPSTR *lplpstr)  { return E_NOTIMPL; }

	STDMETHOD_(void, SetInitNew)		(BOOL fInitNew) { m_fInitNew = fInitNew; }
	STDMETHOD_(BOOL, GetInitNew)		(void) { return m_fInitNew; }
	STDMETHOD_(void, SetDirty)			(BOOL fDirty) { m_fIsDirty = fDirty; }
	STDMETHOD_(BOOL, GetDirty)			(void) { return m_fIsDirty; }
	STDMETHOD_(void, SetEditOnly)		(BOOL f) { m_fEditOnly = f; }
	STDMETHOD_(BOOL, GetEditOnly)		(void) { return m_fEditOnly; }
	STDMETHOD(GetParentName)			(LPSTR lpstr, UINT uiLen)	{ 
			if (uiLen > m_strParentName.GetLength()) {
				strcpy(lpstr, m_strParentName); 
				return S_OK;
			}
			return E_FAIL;
		}
	STDMETHOD(SetParentName)			(LPCSTR lpcstr) { m_strParentName = lpcstr; return S_OK; }

	STDMETHOD(GetSaveAsFilters)	(LPSTR *) { return E_NOTIMPL; }
	STDMETHOD(GetFileExt)		(LPSTR *){ return E_NOTIMPL; }

	//  *** ITreeItem-Methods ***
	STDMETHOD_(BOOL, IsLabelEdit)		(void) { return m_fIsLabelEdit; }
	STDMETHOD_(void, SetLabelEdit)		(BOOL f) { m_fIsLabelEdit = f; }
	STDMETHOD_(BOOL, IsJustInsert)		(void) { return m_fIsJustInsert; }
	STDMETHOD_(void, SetJustInsert)		(BOOL f) { m_fIsJustInsert = f; }
	STDMETHOD_(int,	AskSaveChanges)		(HWND, LPCSTR);
	STDMETHOD_(void, GetInitCaretPos)	(int & ix, int & iy, int & fSelect) { ix = 3; iy = 3; fSelect = 0; }
	STDMETHOD_(BOOL, IsSuperItem)		(void) { return true; }
	STDMETHOD_(BOOL, CanLabelEdit)		(void) { return true; }
	STDMETHOD_(int, GetPopUpMenuID)		(void) { return INVALID; }
	STDMETHOD_(int, GetImage)			(void) { return -1; }
	STDMETHOD (CreateInsertItem)		(ITreeItem **pp, REFIID riid = CLSID_NULL, LPCSTR lpcstrName = NULL, LPCSTR lpcstrDecl = NULL, LPCSTR lpcstrType = NULL, LPCSTR lpcstrParams = NULL, LPCSTR lpcstrComment = NULL, BOOL fSuper = FALSE) 
		{ return E_NOTIMPL; }

	STDMETHOD(IsFirstLevel)		(void) { return E_NOTIMPL; }
	STDMETHOD(IsKeyLevel)		(void) { return E_NOTIMPL; }
	STDMETHOD(IsScriptLevel)	(void) { return E_NOTIMPL; }
	STDMETHOD(IsFunctionLevel)	(void) { return E_NOTIMPL; }

	//  *** IBSProperty ***
	STDMETHOD(SetScript)		(CebScript *pScript) { return E_UNEXPECTED; }
	STDMETHOD(GetScript)		(CebScript **ppScript) { return E_UNEXPECTED; }
	STDMETHOD(SetThread)		(CebThread *p) { return E_UNEXPECTED; }
	STDMETHOD(GetThread)		(CebThread **pp) { return E_UNEXPECTED; }
	STDMETHOD(GetCode)			(ebHCODE *);
	STDMETHOD(SetCode)			(ebHCODE); 
	STDMETHOD(GetScriptName)	(LPSTR lpstr, UINT uiLen) 
		{ 
			if(uiLen > m_strMacroName.GetLength()) {
				strcpy(lpstr, m_strMacroName); 
				return S_OK;
			}
			return E_FAIL;
		}
	STDMETHOD(SetScriptName)	(LPCSTR lpcstr) { m_strMacroName = lpcstr; return S_OK;}

	// *** IPersist-Method ***
	STDMETHOD(GetClassID)(LPCLSID pClsID)  { *pClsID = m_clsid; return S_OK; }

private:
	// Resets
	void ResetManagement();
	// Inits
	void SetManagement(IObjectManagement*, IStreamInfo *);

protected:
    ULONG m_cRef;      //Interface reference count
	CLSID m_clsid;
	ebHCODE m_hCode;
	BOOL m_fIsLabelEdit;
	BOOL m_fIsJustInsert;
	BOOL m_fRemovedInstall;
		//////////////////////////////////
	// Management
	IObjectManagement *	m_pIObjManagement;
	IStreamInfo *		m_pIStreamInfo;
	IObjectManagement * GetObjManagement(void) { return m_pIObjManagement; }
	IStreamInfo *		GetStreamInfo(void) { return m_pIStreamInfo; } 

	//////////////////////////////////
	// Properties	
	WUnknown m_IUnknown;
	CString m_strMacroName;
	CString m_strParentName;
	BOOL m_fInitNew;
	BOOL m_fIsDirty;
	BOOL m_fSuperItem;
	BOOL m_fEditOnly;
	BOOL m_fLoaded;

	HRESULT CopyCode(ebHCODE hCode);
	HRESULT CopyCodeMember(ebHCODE *phCode);

	virtual CString CorrectExtension(LPCSTR lpcstrFileName, DWORD dw);
	virtual HRESULT GetScript(LPCSTR lpcstrScriptName, REFIID riid, BOOL fCreateObject = false);
	virtual HRESULT SetScript (LPCSTR lpcstr);
	virtual HRESULT	SetProperty (LPCSTR lpcstrName, LPCSTR pText, ebHCODE hCode, LPSTR *lplp, UINT, DWORD dwSaveFlag);
	virtual HRESULT GetProperty (LPCSTR lpcstrName, LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT &);
	virtual HRESULT CopyTo(REFIID riid, LPCSTR lpcstrFileName, LPCSTR lpcstrMacroName, LPSTR *ppMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT & ui);
	HRESULT SetPropertyRelated(LPCSTR lpcstr, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag);
	HRESULT SaveAsFromDisc (LPCSTR lpcstrFileName, DWORD dwSaveFlag);
	HRESULT SaveAsFromDebugger (LPCSTR lpcstrFileName, LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag);
	HRESULT Delete (LPCSTR lpcstr);
	HRESULT GetTextsAndCreateNew(LPCSTR lpcstrImportName, LPSTR *lplpstrRelScriptNames, UINT uiCnt);
	HRESULT SetMan(LPCSTR lpcstrImportName);
	HRESULT RemoveInstall (LPCSTR lpcstr);
	HRESULT Install (LPCSTR lpcstr);
	HRESULT Compile (LPSTR lpstrText, ebHCODE *phCode);
};

/////////////////////////////////////////////////////////////////////////////////////////
// allgemeine Makros
/////////////////////////////////////////////////////////////////////////////////////////
class CProjectScript :
	public CProjectScript2,
	public CComObjectRoot
{
public:
	CProjectScript () 
	{ SetEditOnly(false); }

public:
	BEGIN_COM_MAP(CProjectScript)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(ITreeItem)
		COM_INTERFACE_ENTRY(IObjManHelper)
		COM_INTERFACE_ENTRY(IBSProperty)
	END_COM_MAP()
	STDMETHOD_(int, GetPopUpMenuID)		(void) { return GNSCRIPT_POPUPMENU_ID; }
	STDMETHOD_(int, GetImage)			(void) { return IMAGE_SUPERSCRIPT; }
	STDMETHOD (CreateInsertItem)		(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										);
	STDMETHOD(IsFirstLevel)		() { return S_FALSE; }
	STDMETHOD(IsKeyLevel)		() { return S_FALSE; }
	STDMETHOD(IsScriptLevel)	() { return S_OK; }
	STDMETHOD(IsFunctionLevel)	() { return S_FALSE; }
	STDMETHOD(GetSaveAsFilters)	(LPSTR *) ;
	STDMETHOD(GetFileExt)		(LPSTR *);

protected:
	HRESULT GetGeneralScripts(IObjectManagement **ppIObj) {
			IObjectManagement *pIObj = g_pBSE -> GetGeneralScripts();
			ASSERT(pIObj);
			if (pIObj) {
				*ppIObj = pIObj; (*ppIObj) -> AddRef();
				return NOERROR;
			}
			return E_FAIL;
		}

	HRESULT GetInfoGeneralScripts(IStreamInfo **ppISI) {
			IStreamInfo *pISI = g_pBSE -> GetInfoGeneralScripts();
			ASSERT(pISI);
			if (pISI) 	{
				*ppISI = pISI; (*ppISI) -> AddRef();
				return NOERROR;
			}
			return E_FAIL;
		}

};

/////////////////////////////////////////////////////////////////////////////////
// allgemeine Unter-ProjectScripts
/////////////////////////////////////////////////////////////////////////////////
class CSubProjectScript : public CProjectScript
{
public:
	CSubProjectScript () 
		: CProjectScript () 
	{ SetEditOnly(false); }

public:
	STDMETHOD(New)	(LPSTR *ppcMacroText);
	STDMETHOD_(void, GetInitCaretPos) (int & ix, int & iy, int & fSelect)  { ix = 3; iy = 3; fSelect = 0; }
	STDMETHOD_(BOOL, IsSuperItem)		(void) { return false; }
	STDMETHOD_(int, GetPopUpMenuID)		(void) { return GNSCRIPT_POPUPMENU_ID; }
	STDMETHOD_(int, GetImage)			(void) { return IMAGE_SUBSCRIPT; }
	STDMETHOD (CreateInsertItem)		(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										);
	STDMETHOD(IsFirstLevel)		() { return S_FALSE; }
	STDMETHOD(IsKeyLevel)		() { return S_FALSE; }
	STDMETHOD(IsScriptLevel)	() { return S_OK; }
	STDMETHOD(IsFunctionLevel)	() { return S_FALSE; }

private:
	CString GenerateDefaultMakroText(void);
	LPSTR StrTokCaption(CString & strContainerText);
	
protected:
	virtual HRESULT	SetProperty (LPCSTR lpcstr, LPCSTR pText, ebHCODE hCode, LPSTR *lplp, UINT, DWORD dwSaveFlag);
	virtual HRESULT GetProperty (LPCSTR lpcstr, LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT &);
};

/////////////////////////////////////////////////////////////////////////////////
// Filter Unter-ProjectScripts
/////////////////////////////////////////////////////////////////////////////////
class CSubFilterProjectScript : public CSubProjectScript
{
public:
	CSubFilterProjectScript () 
		: CSubProjectScript ()
	{ SetEditOnly(true); }
	
public:
	STDMETHOD_(int, GetPopUpMenuID)		(void) { return FTSCRIPT_POPUPMENU_ID; }
	STDMETHOD (CreateInsertItem)		(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										);
	STDMETHOD(GetSaveAsFilters)	(LPSTR *);
	STDMETHOD(GetFileExt)		(LPSTR *);

	HRESULT GetFilterScripts(IObjectManagement **ppIObj) {
			IObjectManagement *pIObj = g_pBSE -> GetFilterScripts();
			ASSERT(pIObj);
			if (pIObj) {
				*ppIObj = pIObj; (*ppIObj) -> AddRef();
				return NOERROR;
			}
			return E_FAIL;
		}
	HRESULT GetInfoFilterScripts(IStreamInfo **ppISI) {
			IStreamInfo *pISI = g_pBSE -> GetInfoFilterScripts();
			ASSERT(pISI);
			if (pISI) {
				*ppISI = pISI;(*ppISI) -> AddRef();
				return NOERROR;
			}
			return E_FAIL;
		}
protected:
	virtual CString CorrectExtension(LPCSTR lpcstrFileName, DWORD dw);
};

/////////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft Unter-ProjectScripts
/////////////////////////////////////////////////////////////////////////////////
class CSubObjFeatProjectScript : public CSubProjectScript
{
public:
	CSubObjFeatProjectScript () 
		: CSubProjectScript() 
	{ SetEditOnly(true); }

public:
	STDMETHOD_(int, GetPopUpMenuID)		(void) { return OFSCRIPT_POPUPMENU_ID; }
	STDMETHOD (CreateInsertItem)		(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										);
	STDMETHOD(GetSaveAsFilters)	(LPSTR *);
	STDMETHOD(GetFileExt)		(LPSTR *);

	HRESULT GetObjFeatScripts(IObjectManagement **ppIObj) {
			IObjectManagement *pIObj = g_pBSE -> GetObjectFeatureScripts();
			ASSERT(pIObj);
			if (pIObj) {
				*ppIObj = pIObj; (*ppIObj) -> AddRef(); 
				return NOERROR;
			}
			return E_FAIL;
		}
	HRESULT GetInfoObjFeatScripts(IStreamInfo **ppISI) {
			IStreamInfo *pISI = g_pBSE -> GetInfoObjFeatureScripts();
			ASSERT(pISI);
			if (pISI) {
				*ppISI = pISI;(*ppISI) -> AddRef();
				return NOERROR;
			}
			return E_FAIL;
		}
protected:
	virtual HRESULT CopyTo(REFIID riid, LPCSTR lpcstrFileName, LPCSTR lpcstrMacroName, LPSTR *ppMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT & ui);
	virtual CString CorrectExtension(LPCSTR lpcstrFileName, DWORD dw);

};


/////////////////////////////////////////////////////////////////////////////////
// FilterScripts
/////////////////////////////////////////////////////////////////////////////////
class CFilterProjectScript : public CProjectScript
{
public:	
	CFilterProjectScript () 
		: CProjectScript ()
	{ SetEditOnly(true); }

public:	
	STDMETHOD(New)	(LPSTR *ppcMacroText);
	STDMETHOD_(void, GetInitCaretPos) (int & ix, int & iy, int & fSelect)  { ix = 3; iy = 4; fSelect = 0; }
	STDMETHOD_(int, GetPopUpMenuID)		(void) { return FTSCRIPT_POPUPMENU_ID; }
	STDMETHOD (CreateInsertItem)		(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										);
	STDMETHOD(GetSaveAsFilters)	(LPSTR *);
	STDMETHOD(GetFileExt)		(LPSTR *);

	HRESULT GetFilterScripts(IObjectManagement **ppIObj) {
			IObjectManagement *pIObj = g_pBSE -> GetFilterScripts();
			ASSERT(pIObj);
			if (pIObj) {
				*ppIObj = pIObj; (*ppIObj) -> AddRef();
				return NOERROR;
			}
			return E_FAIL;
		}
	HRESULT GetInfoFilterScripts(IStreamInfo **ppISI) {
			IStreamInfo *pISI = g_pBSE -> GetInfoFilterScripts();
			ASSERT(pISI);
			if (pISI) {
				*ppISI = pISI;(*ppISI) -> AddRef();
				return NOERROR;
			}
			return E_FAIL;
		}
protected:
	virtual CString CorrectExtension(LPCSTR lpcstrFileName, DWORD dw);
};


/////////////////////////////////////////////////////////////////////////////////
// ObjFeatScripts
/////////////////////////////////////////////////////////////////////////////////
class CObjFeatProjectScript : public CProjectScript
{
public:
	CObjFeatProjectScript () 
		: CProjectScript () 
	{ SetEditOnly(true); }

public:
	STDMETHOD(New)	(LPSTR *ppcMacroText);
	STDMETHOD_(int, GetPopUpMenuID)		(void) { return OFSCRIPT_POPUPMENU_ID; }
	STDMETHOD (CreateInsertItem)		(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										);
	STDMETHOD(GetSaveAsFilters)	(LPSTR *);
	STDMETHOD(GetFileExt)		(LPSTR *);

	HRESULT GetObjFeatScripts(IObjectManagement **ppIObj) {
			IObjectManagement *pIObj = g_pBSE -> GetObjectFeatureScripts();
			ASSERT(pIObj);
			if (pIObj) {
				*ppIObj = pIObj; (*ppIObj) -> AddRef(); 
				return NOERROR;
			}
			return E_FAIL;
		}
	HRESULT GetInfoObjFeatScripts(IStreamInfo **ppISI) {
			IStreamInfo *pISI = g_pBSE -> GetInfoObjFeatureScripts();
			ASSERT(pISI);
			if (pISI) {
				*ppISI = pISI;(*ppISI) -> AddRef();
				return NOERROR;
			}
			return E_FAIL;
		}
protected:
	virtual HRESULT CopyTo(REFIID riid, LPCSTR lpcstrFileName, LPCSTR lpcstrMacroName, LPSTR *ppMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT & ui);
	virtual CString CorrectExtension(LPCSTR lpcstrFileName, DWORD dw);

};


/////////////////////////////////////////////////////////////////////////////////
// externe Scripts
/////////////////////////////////////////////////////////////////////////////////
class CExternProjectScript : public CSubProjectScript
{
public:
	STDMETHOD(New)	(LPSTR *ppcMacroText);
	STDMETHOD(Open) (LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT &, BOOL fCreateTemp = false);
	STDMETHOD(Save) (LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag);
	STDMETHOD(SaveAs) (LPCSTR, LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag);
	STDMETHOD(Delete) (void);
	STDMETHOD(Rename) (LPCSTR lpcstrNewName) { return E_UNEXPECTED; }
	STDMETHOD_(void, SetInitNew) (BOOL fInitNew) { m_fInitNew = true; }
	STDMETHOD_(void, GetInitCaretPos) (int & ix, int & iy, int & fSelect)  { ix = 0; iy = 0; fSelect = 0; }
	STDMETHOD_(BOOL, CanLabelEdit)		(void) { return false; }
	STDMETHOD_(int, GetPopUpMenuID)		(void) { return INVALID; }
	STDMETHOD(NewFunction) (				
				LPCSTR lpcstrName,
				LPCSTR lpcstrDecl,
				LPCSTR lpcstrType,
				LPCSTR lpcstrParams,
				LPCSTR lpcstrComment,
				LPSTR *lplpstr);
	STDMETHOD_(int, GetImage)			(void) { return -1; }
	//Ohne StreamInfo
	HRESULT	SetProperty (LPCSTR lpcstrName, LPCSTR pText, ebHCODE hCode, LPSTR *lplp, UINT, DWORD dwSaveFlag);
	HRESULT Delete		(LPCSTR lpcstr);
	STDMETHOD (CreateInsertItem)	(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										)
				 { return E_UNEXPECTED; }
};

/////////////////////////////////////////////////////////////////////////////////
// SchlüsselDummyScripts
/////////////////////////////////////////////////////////////////////////////////
class CKeyDummyProjectScript : public CProjectScript
{// Constructors
public:	
	CKeyDummyProjectScript() 
		: CProjectScript()
	{ Init(NULL, NULL, CLSID_KeyItem); }
public:
	STDMETHOD(New)	(LPSTR *ppcMacroText) { return S_FALSE; }
	STDMETHOD(Open) (LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT &, BOOL fCreateTemp = false){ return S_FALSE; }
	STDMETHOD(Save) (LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag) { return E_UNEXPECTED; }
	STDMETHOD(SaveAs) (LPCSTR, LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag) { return E_UNEXPECTED; }
	STDMETHOD(Delete) (void) { 	((ITreeItem *)this) -> Release(); return S_OK; }
	STDMETHOD(Rename) (LPCSTR lpcstrNewName) { return E_UNEXPECTED; }
	STDMETHOD_(int, AskSaveChanges) (HWND, LPCSTR) { return E_UNEXPECTED; }

	STDMETHOD(GetCode) (ebHCODE*) { return E_UNEXPECTED; }
	STDMETHOD(SetCode) (ebHCODE) { return E_UNEXPECTED; } 
	STDMETHOD_(void, SetInitNew) (BOOL fInitNew) { m_fInitNew = false; }
	STDMETHOD_(BOOL, GetInitNew) (void) { return false; }
	STDMETHOD_(void, SetDirty) (BOOL fDirty) { m_fIsDirty = false; }
	STDMETHOD_(BOOL, GetDirty) (void) { return false; }
	STDMETHOD_(void, SetEditOnly) (BOOL f) { m_fEditOnly = false; }
	STDMETHOD_(BOOL, GetEditOnly) (void) { return false; }
	STDMETHOD_(int, GetPopUpMenuID)	(void) { return GENKEY_POPUPMENU_ID; }
	STDMETHOD_(int, GetImage)		(void) { return IMAGE_GENERALKEY; }
	STDMETHOD (CreateInsertItem)		(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										);


	STDMETHOD(IsFirstLevel)		() { return S_FALSE; }
	STDMETHOD(IsKeyLevel)		() { return S_OK; }
	STDMETHOD(IsScriptLevel)	() { return S_FALSE; }
	STDMETHOD(IsFunctionLevel)	() { return S_FALSE; }

	STDMETHOD(GetParentName) (LPSTR lpstr, UINT) { *lpstr = '\0'; return S_OK;}
	STDMETHOD(SetParentName) (LPCSTR lpcstr) { m_strParentName.Empty(); return S_OK;}
	STDMETHOD_(void, GetInitCaretPos) (int & ix, int & iy, int & fSel) { return ; }
	STDMETHOD_(BOOL, IsSuperItem)		(void) { return false; }
	STDMETHOD_(BOOL, CanLabelEdit)		(void) { return false; }
};

/////////////////////////////////////////////////////////////////////////////////
// FilterSchlüsselDummyScripts
/////////////////////////////////////////////////////////////////////////////////
class CKeyFilterProjectScript : public CKeyDummyProjectScript
{// Constructors
	STDMETHOD_(int, GetPopUpMenuID)	(void) { return FTKEY_POPUPMENU_ID; }
	STDMETHOD_(int, GetImage)		(void) { return IMAGE_FILTERKEY; }
	STDMETHOD (CreateInsertItem)		(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										);
protected:
	HRESULT GetFilterScripts(IObjectManagement **ppIObj) {
			IObjectManagement *pIObj = g_pBSE -> GetFilterScripts();
			ASSERT(pIObj);
			if (pIObj) {
				*ppIObj = pIObj; (*ppIObj) -> AddRef();
				return NOERROR;
			}
			return E_FAIL;
		}
	HRESULT GetInfoFilterScripts(IStreamInfo **ppISI) {
			IStreamInfo *pISI = g_pBSE -> GetInfoFilterScripts();
			ASSERT(pISI);
			if (pISI) {
				*ppISI = pISI;(*ppISI) -> AddRef();
				return NOERROR;
			}
			return E_FAIL;
		}
};

/////////////////////////////////////////////////////////////////////////////////
// ObjFeatSchlüsselDummyScripts
/////////////////////////////////////////////////////////////////////////////////
class CKeyObjFeatProjectScript : public CKeyDummyProjectScript
{// Constructors
	STDMETHOD_(int, GetPopUpMenuID)	(void) { return OFKEY_POPUPMENU_ID; }
	STDMETHOD_(int, GetImage)		(void) { return IMAGE_OBJECTFEATUREKEY; }
	STDMETHOD (CreateInsertItem)		(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										);
private:
	HRESULT GetObjFeatScripts(IObjectManagement **ppIObj) {
			IObjectManagement *pIObj = g_pBSE -> GetObjectFeatureScripts();
			ASSERT(pIObj);
			if (pIObj) {
				*ppIObj = pIObj; (*ppIObj) -> AddRef(); 
				return NOERROR;
			}
			return E_FAIL;
		}
	HRESULT GetInfoObjFeatScripts(IStreamInfo **ppISI) {
			IStreamInfo *pISI = g_pBSE -> GetInfoObjFeatureScripts();
			ASSERT(pISI);
			if (pISI) {
				*ppISI = pISI;(*ppISI) -> AddRef();
				return NOERROR;
			}
			return E_FAIL;
		}
};
/////////////////////////////////////////////////////////////////////////////////
// RootDummyScripts
/////////////////////////////////////////////////////////////////////////////////
class CRootDummyScript : public CProjectScript
{// Constructors
public:
	CRootDummyScript()
		: CProjectScript()
	{ Init(NULL, NULL, CLSID_RootKeyItem); }

public:
	STDMETHOD(New)	(LPSTR *ppcMacroText) { return S_FALSE; }
	STDMETHOD(Open) (LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT &, BOOL fCreateTemp = false) { return S_FALSE; }
	STDMETHOD(Save) (LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag) { return E_UNEXPECTED; }
	STDMETHOD(SaveAs) (LPCSTR, LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag) { return E_UNEXPECTED; }
	STDMETHOD(Delete) (void) { 	((ITreeItem *)this) -> Release(); return S_OK; }
	STDMETHOD(Rename) (LPCSTR lpcstrNewName) { return E_UNEXPECTED; }
	STDMETHOD_(int, AskSaveChanges) (HWND, LPCSTR) { return E_UNEXPECTED; }

	STDMETHOD_(BOOL, IsLabelEdit) (void) { return false; }
	STDMETHOD_(void, SetLabelEdit) (BOOL f) { m_fIsLabelEdit = false; }
	STDMETHOD_(BOOL, IsJustInsert) (void) { return false; }
	STDMETHOD_(void, SetJustInsert) (BOOL f) { m_fIsJustInsert = false; }
	STDMETHOD_(BOOL, CanLabelEdit)		(void) { return false; }
	STDMETHOD_(int, GetPopUpMenuID)	(void) { return GENROOT_POPUPMENU_ID; }
	STDMETHOD_(int, GetImage)		(void) { return IMAGE_CLOSEMACROS; }
	STDMETHOD (CreateInsertItem)		(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										);

	STDMETHOD(IsFirstLevel)		() { return S_OK; }
	STDMETHOD(IsKeyLevel)		() { return S_FALSE; }
	STDMETHOD(IsScriptLevel)	() { return S_FALSE; }
	STDMETHOD(IsFunctionLevel)	() { return S_FALSE; }

	STDMETHOD(GetCode) (ebHCODE*) { return E_UNEXPECTED; }
	STDMETHOD(SetCode) (ebHCODE) { return E_UNEXPECTED; } 
	STDMETHOD_(void, SetInitNew) (BOOL fInitNew) { m_fInitNew = false; }
	STDMETHOD_(BOOL, GetInitNew) (void) { return false; }
	STDMETHOD_(void, SetDirty) (BOOL fDirty) { m_fIsDirty = false; }
	STDMETHOD_(BOOL, GetDirty) (void) { return false; }
	STDMETHOD_(void, SetEditOnly) (BOOL f) { m_fEditOnly = false; }
	STDMETHOD_(BOOL, GetEditOnly) (void) { return false; }
	STDMETHOD(GetScriptName) (LPSTR lpstr, UINT) { *lpstr = '\0'; return S_OK; }
	STDMETHOD(SetScriptName) (LPCSTR lpcstr) { m_strMacroName.Empty(); return S_OK; }
	STDMETHOD(GetParentName) (LPSTR lpstr, UINT) { *lpstr = '\0'; return S_OK; }
	STDMETHOD(SetParentName) (LPCSTR lpcstr) { m_strParentName.Empty(); return S_OK; }
	STDMETHOD_(void, GetInitCaretPos) (int & ix, int & iy, int & fSel) { return ; }
	STDMETHOD_(BOOL, IsSuperItem)		(void) { return false; }
};
class CRootFilterScript : public CRootDummyScript
{// Constructors
	STDMETHOD_(int, GetPopUpMenuID)	(void) { return FTROOT_POPUPMENU_ID; }
	STDMETHOD (CreateInsertItem)		(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										);

};
class CRootObjFeatScript : public CRootDummyScript
{// Constructors
	STDMETHOD_(int, GetPopUpMenuID)	(void) { return OFROOT_POPUPMENU_ID; }
	STDMETHOD (CreateInsertItem)		(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										);

};

/////////////////////////////////////////////////////////////////////////////////
// FunctionScripts
/////////////////////////////////////////////////////////////////////////////////
class CFunctionScript : public CProjectScript
{
public:	
	CFunctionScript();
	virtual ~CFunctionScript();

	virtual HRESULT Init(				
				IObjManHelper *pParentProject,
				IObjectManagement *pIOM, 
				IStreamInfo * pIS, 
				REFIID riid,
				LPCSTR lpcstrName,
				LPCSTR lpcstrDecl,
				LPCSTR lpcstrType,
				LPCSTR lpcstrParams,
				LPCSTR lpcstrComment
				);

protected:
	IObjManHelper *m_pParentProject;

	CString m_strFunctionName;	
	CString m_strType;
	CString m_strDecl;
	CString m_strParams;
	CString m_strComment;
	int m_ix;
	int m_iy;
	int m_iImage;

public:
	STDMETHOD(New)	(LPSTR *ppcMacroText);
	STDMETHOD(Open) (LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT &, BOOL fCreateTemp = false);
	STDMETHOD(Save) (LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag);
	STDMETHOD(Delete) (void);
	STDMETHOD(Rename) (LPCSTR lpcstrNewName) { return E_UNEXPECTED; }

	STDMETHOD_(BOOL, IsLabelEdit) (void) { return false; }
	STDMETHOD_(void, SetLabelEdit) (BOOL f) { m_fIsLabelEdit = false; }
	STDMETHOD_(BOOL, IsJustInsert) (void) { return false; }
	STDMETHOD_(void, SetJustInsert) (BOOL f) { m_fIsJustInsert = false; }
	STDMETHOD_(BOOL, CanLabelEdit)		(void) { return false; }
	STDMETHOD_(int, GetPopUpMenuID)	(void) { return FUNCTION_POPUPMENU_ID; }
	STDMETHOD_(int, GetImage)		(void) { return m_iImage; }
	STDMETHOD (CreateInsertItem)	(										
										ITreeItem **pp, 
										REFIID riid = CLSID_NULL, 
										LPCSTR lpcstrName = NULL,
										LPCSTR lpcstrDecl = NULL,
										LPCSTR lpcstrType = NULL,
										LPCSTR lpcstrParams = NULL,		
										LPCSTR lpcstrComment = NULL,		
										BOOL fSuper = false
										) { return E_UNEXPECTED; }

	STDMETHOD(IsFirstLevel)		() { return S_FALSE; }
	STDMETHOD(IsKeyLevel)		() { return S_FALSE; }
	STDMETHOD(IsScriptLevel)	() { return S_FALSE; }
	STDMETHOD(IsFunctionLevel)	() { return S_OK; }

	STDMETHOD(GetCode) (ebHCODE* phCode);
	STDMETHOD(SetCode) (ebHCODE hCode);
	STDMETHOD_(void, SetInitNew) (BOOL fInitNew) { m_pParentProject -> SetInitNew(fInitNew); }
	STDMETHOD_(BOOL, GetInitNew) (void) { return m_pParentProject -> GetInitNew(); }
	STDMETHOD_(void, SetDirty) (BOOL fDirty) { m_pParentProject -> SetDirty(fDirty); }
	STDMETHOD_(BOOL, GetDirty) (void) { return  m_pParentProject  -> GetDirty(); }
	STDMETHOD_(void, SetEditOnly) (BOOL f) { m_pParentProject  -> SetEditOnly(GetEditOnly()); }
	STDMETHOD_(BOOL, GetEditOnly) (void) { return m_pParentProject  -> GetEditOnly(); }
	STDMETHOD_(BOOL, IsSuperItem)		(void) { 
		ITreeItem *pIT = NULL;
		HRESULT hr = m_pParentProject -> QueryInterface(IID_ITreeItem, (LPVOID *)&pIT); 
		if (FAILED(hr)) return hr;
		return pIT -> IsSuperItem(); 
	}
	STDMETHOD_(void, GetInitCaretPos) (int & ix, int & iy, int & fSelect) { ix = m_ix; iy = m_iy; fSelect = m_strFunctionName.GetLength();}

private:
	HRESULT FindSubOrFunctionString (const ebHCODE hCode);
	CString GenerateDefaultFunctionText(void);
	BOOL CopyCode(ebHCODE hCode);
	HRESULT OpenFromNewScript(void);
	HRESULT OpenFromSavedScript(LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT & ui, BOOL fCreateTemp);
};

#endif // _PROJSCR_H
