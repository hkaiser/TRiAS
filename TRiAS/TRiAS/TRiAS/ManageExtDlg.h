// Klassendefinition für das Erweiterung-Lade/Entlade Dialogfenster -----------
// File: MANAGEEXTDLG.H

#if !defined(_MANAGEEXTDLG_H)
#define _MANAGEEXTDLG_H

#include <shlobj.h>
#include <comcat.h>

#include <regprop.hxx>
#include <CheckTreeView.h>

class CQueryExtensionNameDlg : 
	public DialogWindow 
{
private:
	PushButton m_pbOK;
	SingleLineEdit m_sleExtName;
	FixedText m_ftQueryText;

protected:
	void ButtonClick (ControlEvt);
	void EditChange (ControlEvt);

public:
		CQueryExtensionNameDlg (pWindow, const string &);
		~CQueryExtensionNameDlg (void) {}

	bool GetExtName (string &strExtName);
};

///////////////////////////////////////////////////////////////////////////////
// AnpassenDialog 
// verwendete Interfaces
DefineSmartInterface(Storage);
DefineSmartInterface(DataObject);

class CManageExtDlg : 
	public CPropertySheetExt 
{
public:
		CManageExtDlg (pWindow pWnd);
		~CManageExtDlg (void);

	void Activate (Event e);
	LRESULT Dispatch (Event e);
	LRESULT OnFloatStatus (WPARAM wParam);

friend HRESULT CreateDataObject (WStorage &rIStg, WDataObject &rIDO);
friend HRESULT LoadPages (CPropertySheetExt &, LPCSTR pcKey, LPCSTR pcSubKey, IUnknown *pIUnkSite, LPCSTR pcProgID = NULL, int *piPage = NULL);
};

///////////////////////////////////////////////////////////////////////////////
// erste Page für AnpassenDialog - Verwalten der Erweiterungen 
// verwendete Interfaces
DefineSmartInterface(EnumGUID);

class CManageExtPage : 
	public CPropertyPage 
{
private:
	CCheckTreeView *m_pExtList;
	PushButton m_pbInstall, m_pbRemove;
//	CImageList m_ilHdr;

	ExtDirisWindow *m_pWnd;
	ExtensionList &m_rEL;		// Verweis auf ExtensionList
	HTREEITEM m_hIterItem;

	HTREEITEM m_hNormal;
	HTREEITEM m_hProject;
	HTREEITEM m_hSystem;
	enum ITERMODE {
		ITERMODE_Normal = 1,
		ITERMODE_Project = 2,
		ITERMODE_System = 3,
	};
	ITERMODE m_rgMode;

	char *m_pExtName;			// Bezeichner der Extension
	char *m_pDLLName;			// DLL-PfadName
	char *m_pBuffer;

	EXTENSIONFLAG m_rgFlags;
	WEnumGUID m_EnumGuids;		// Enumerator der RegisterTRiASExtension-Objekte

	unsigned int m_fToLoad : 1;
	unsigned int m_fToUnload : 1;
	unsigned int m_fBttnsEnabled : 1;
	unsigned int m_fNoProject : 1;		// keine Projekt-Erweiterungen
	unsigned int m_fNoSystem : 1;		// keine systeminternen Erweiterungen
	unsigned int m_fModified : 1;

// private members
	bool GetNames (HTREEITEM hItem);
	HTREEITEM InstallExtension (void);
	bool RemoveExtension (void);
	bool InitExtList (bool fDelete = false);
	HRESULT RetrieveTemplate (string &rStrTempl);

protected:
	void ButtonClick (ControlEvt);

	void WindowInit (Event e);
	BOOL OnOK (NotifyEvt e);
	long Dispatch (Event);
	void OnItemExpanded (NotifyEvt e);
	void OnSelChanged (NotifyEvt e);

	void AdjustImage (HTREEITEM hItem);
	BOOL OnNotify (NotifyEvt);
	BOOL OnChangingCheckState (NM_TREEVIEWCHECK *pHdr);

public:
		CManageExtPage (ExtDirisWindow *pParent, bool fForceBttns);
		~CManageExtPage (void);

// sonstige Member
	char * &GetExtName (void) const { return (char *&)m_pExtName; }
	char * &GetDLLName (void) const { return (char *&)m_pDLLName; }
	EXTENSIONFLAG GetFlags (void) { return m_rgFlags; }

	bool GetFirstExtName (void);
	bool GetNextExtName (void);

	bool toLoad (void) { return m_fToLoad ? true : false; }
	bool toUnload (void) { return m_fToUnload ? true : false; }
	bool isUnLoadable (void) { return m_rgFlags & EF_UnLoadable; }

	void SetModified (bool fFlag) 
		{ m_fModified = fFlag; CPropertyPage::SetModified (fFlag); }
	bool IsModified() { return m_fModified ? true : false; }
};

bool FindExtNameFromDLLName (
	pWindow pW, string &strDLLName, string &strExtName, string &rStrProgID,
	const char *pShort);
bool CompareDLLName (string &strKey, string &strDLL, string &rStrProgID);

///////////////////////////////////////////////////////////////////////////////
// Konstanten für die ImageList 
#define	IMG_NONE				0
#define IMG_FOLDER				1
#define IMG_OPENFOLDER			2

#define IMG_EXTENSION			8
#define IMG_EXTENSION_SYS		9
#define IMG_EXTENSION_PRJ		10
#define IMG_EXTENSION_PRJSYS	11
#define IMG_EXTENSION_MACRO		12
#define IMG_EXTENSION_MACROSYS	13
#define IMG_EXTENSION_VB		14
#define IMG_EXTENSION_VBSYS		15
#define IMG_EXTENSION_IMPORT	16
#define IMG_EXTENSION_IMPORTSYS	17

#endif // _MANAGEEXTDLG_H
