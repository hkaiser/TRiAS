// Erweiterungsklasse, für OLE2.0 Automation ----------------------------------
// File: OLE2AUTO.HXX

#if !defined(_OLE2AUTO_HXX)
#define _OLE2AUTO_HXX

#include <itriasap.h>		// IGetTRiASApplication

#include "DropTargets.h"
#include "MenuCommands.h"

extern "C" HINSTANCE g_hInstance;

///////////////////////////////////////////////////////////////////////////////
// forward declaration
class CTriasApp;

EXTERN_C const GUID CLSID_OleAutoExtension;
EXTERN_C const GUID IID_IGetTRiASApplication;

///////////////////////////////////////////////////////////////////////////////
// Erweiterung
class OLE2AutoExtension : 
	public IGetTRiASApplication,
	public ITRiASDropTarget,
	public IDragDropAction,
	public CTriasExtension,
	public CObjectProperties,
	public CComCoClass<OLE2AutoExtension, &CLSID_OleAutoExtension>
{
private:
	unsigned int m_fOleInitialized : 1;
	unsigned int m_fForceUnload : 1;
	unsigned int m_fIsDragSourceInst : 1;	// is drop source
//	unsigned int m_fDocRegistered : 1;		// DocCF ist registriert
	 	
	DWORD m_dwAppCF;				// Registrierung der ClassFactory
									// #AD20000221
	DWORD m_dwDocCF;				// Registrierung der ClassFactory DocWrapper
	DWORD m_dwProjCF;				// Registrierung der ClassFactory TRiASProject
	DWORD m_dwRegister;				// Registrierung des ActiveObject
		
	CTriasApp *m_pApp;				// Application
	_DApplication *m_pIAppPro;		// AppDispInterface
	
	LPEXTENDBSCRIPT m_pIScript;		// evtl. BasicExtension
	DWORD m_dwCookie;				// Registrierung des ConnPnts für BScript

	LPEXTENDABSTAND m_pIAbstand;	// Abstandsberechnung
	LPMAINTAINTEXTS  m_pITextGen;	// Textobjekte erzeugen
	IExtendTopRel2  *m_pITopoRel;	// Topologische Relationen
	IExtendBuffer *m_pIBuffer;		// BufferingExtension
	IExtendObjOper *m_pIObjOper;	// Objektoperationen
	IVisObjExt *m_pIVisObj;			// Visualiserung
	IExtendGeoEdit *m_pIEdit;		// GeometrieEdititierung
	IExtendGeoRein *m_pIGeoRein;	// GeometrieBereinigung

	bool RegisterBScriptExtension (void);	// beim BScript anmelden
	HRESULT FConnect (DWORD *pdwCookie);	// Connection herstellen
	HRESULT FDisconnect (DWORD dwCookie);	// Connection lösen

// Drag'n Drop support
	CDropTargets m_DropTargets;
	HPROJECT m_hPrIsDragSource;
	CMenuCommands m_Cmds;						// MenuCommands bei D&D

protected:
// überladene virtuelle Funktion(en)
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, 
						  LPARAM lParam);
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);

// *** IGetTRiASApplication methods
	STDMETHOD(GetApplication) (THIS_ REFIID riid, LPVOID *pIApp);

// *** IDropTarget
	STDMETHOD(DragEnter) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHOD(DragOver) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHOD(DragLeave) (THIS_ DRAGDROPTYPE rgType, HWND hWnd);
	STDMETHOD(Drop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);

// *** IDragDropAction
	STDMETHOD(BeginDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWndSrc, DWORD dwFlags, IDataObject *pIDO);
	STDMETHOD(DoDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDO, IDropSource *pISrc,
		DWORD dwOKEffects, LPDWORD pdwEffect);
	STDMETHOD(EndDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWndSrc, DWORD dwEffect);

///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop support
	HRESULT BeginDragDropWindow (HWND hWndSrc, DWORD dwFlags, IDataObject *pIDO);
	HRESULT InstallDropTargets (HPROJECT hPr);
	HRESULT RemoveDropTargets (void);
	HRESULT ReRegisterActiveObject (void);

public:
	HRESULT FinalConstruct (void);
// Konstruktor/Destruktor
		OLE2AutoExtension (void);
		~OLE2AutoExtension (void);

	static HRESULT WINAPI _GetObjProps (void *pThis, REFIID iid, void **ppvObject, DWORD dw);
	BEGIN_COM_MAP(OLE2AutoExtension)
		COM_INTERFACE_ENTRY(ITRiASDropTarget)
		COM_INTERFACE_ENTRY(IGetTRiASApplication)
		COM_INTERFACE_ENTRY(IDragDropAction)
		COM_INTERFACE_ENTRY(IObjectProps)		// aus CObjectProperties
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(OLE2AutoExtension, g_pTE)

inline CTriasApp *App (void) { return m_pApp; }
inline _DApplication *AppDisp (void) { return m_pIAppPro; }

	CString	m_strEmbeddedCaption;
	void	SetTitle (const char*, const char*);

	HRESULT GetIBScript (LPEXTENDBSCRIPT *ppIBScript);
	HRESULT GetIDistance (LPEXTENDABSTAND *ppIAbstand);
	HRESULT GetITextGen (LPMAINTAINTEXTS *ppITextgen);
	HRESULT GetITopoRel (IExtendTopRel2 **ppITopoRel);
	HRESULT GetIBuffer (IExtendBuffer **ppIBuffer);
	HRESULT GetIObjOper (IExtendObjOper **ppIObjOper);
	HRESULT GetIVisInfo (IVisObjExt **ppIVisObj);
	HRESULT GetIEdit (IExtendGeoEdit **ppIEdit);
	HRESULT GetIGeoRein (IExtendGeoRein **ppIGeoRein);
#if defined(_SUPPORT_QUERYDEFS)
	BOOL HasQueryDef();
#endif // defined(_SUPPORT_QUERYDEFS)

// Drag'n Drop
inline bool IsSource (void) { return m_fIsDragSourceInst ? true : false; }
inline bool IsDocSource (HPROJECT hPr) 
	{ ASSERT(NULL != hPr); return (hPr == m_hPrIsDragSource) ? true : false; }

	HRESULT TrackDragPopupMenuRight (POINTL *pPt, DWORD *pdwEffect, HPROJECT *phPr, BOOL *pfShowORWnd);
	HRESULT TrackDragPopupMenuLeft (POINTL *pPt, DWORD *pdwEffect, HPROJECT *phPr, BOOL *pfShowORWnd, BOOL fCopy);
	HRESULT AddMenuOffset (CMenu *pPopup);
	HRESULT AddDataSources (CMenu *pPopup, BOOL fShowORWnd, DWORD dwEffect, BOOL fEmpty = TRUE);
	HPROJECT GetWriteAbleDatasource();

// other stuff
inline bool ForceUnload(void) { return m_fForceUnload ? true : false; }

	HRESULT GetCorrespondingDocument (HPROJECT hPr, CComVariant &rvDoc);
};

bool RegisterAutomationServer (REFCLSID);	// RegDB initialisieren
bool UnRegisterAutomationServer (REFCLSID);	// RegDB deinitialisieren

///////////////////////////////////////////////////////////////////////////////
// OKS auswerten
bool StringIsOKS (BSTR bstrToStrip, BSTR *pStripped = NULL, BSTR *pbstrAppendix = NULL);
	
// divere Konstanten ----------------------------------------------------------
#define INVALID_IDENT		0L		// ungültiger Identifikator
#define INVALID_ONR	       -1L		// ungültige Objektnummer
#define INVALID_HWND       NULL		// ungültige Window Handle
#define INVALID_MCODE		0L		// ungültiger MerkmalsCode
#define INVALID_RCODE		0L		// ungültiger RelationsCode

///////////////////////////////////////////////////////////////////////////////
// zusätzliche D&D Flags
#define DROPEFFECT_SHOWORWINDOW		(0x8000)	// evtl. ORWindow anzeigen

#endif 	// _OLE2AUTO_HXX
