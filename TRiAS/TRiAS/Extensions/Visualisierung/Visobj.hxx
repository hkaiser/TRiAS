// BeispielErweiterungsklasse, um den gesamten Mechanismus zu dokumentieren
// File: VISOBJ.HXX

#if !defined(_VISOBJ_HXX)
#define _VISOBJ_HXX

#include "CPVisInfo.h"
#include "VmdMenuMap.h"
#include "AutoAssignColors.h"

#define MCODESIZE	20
#define MWERTSIZE	_MAX_PATH

extern "C" BOOL _XTENSN_EXPORT PASCAL ObjChangeVisInfo (long lONr, BOOL, void *pData);
extern "C" BOOL _XTENSN_EXPORT PASCAL ObjChangeSymbol (long lONr, BOOL, void *pData);
extern "C" BOOL _XTENSN_EXPORT PASCAL ObjResetVisInfo (long lONr, BOOL, void *pData);
extern "C" BOOL _XTENSN_EXPORT PASCAL ObjHideVisInfo (long lONr, BOOL, void *pData);
extern "C" bool _XTENSN_EXPORT PASCAL ChangeVisInfo (HANDLEVISINFO *pHVI, char **);
extern "C" BOOL _XTENSN_EXPORT PASCAL ExportViewIdent (long lIdent, BOOL, void *pData);
extern "C" BOOL _XTENSN_EXPORT PASCAL ExportViewObject (long lONr, BOOL, void *pData);
extern "C" BOOL _XTENSN_EXPORT PASCAL HandleIdentOnDeleteSight (long lIdent, BOOL, void *pData);
extern "C" BOOL _XTENSN_EXPORT PASCAL HandleViewCreatedObject (long lONr, DWORD, void *pData);

bool HandleViewCreatedIdentEx (long lIdent, VIEWCREATED *pVC, short iOTyp, short iVTyp = 0);

class VisInfo;

#define OVModVisInfo		0x0100
#define OVModShow			0x0200
#define OVObjectTypeUsed	0x0400	// Objekttypen in höherwertigem Wort gespeichert
#define OVMCodeCorrected	0x0800	// MCode wurde bereits korrigiert

class CVisObjExtension : 
	public CTriasExtension,
	public IVisObjExt,
#if _ATL_VER >= 0x200
	public IConnectionPointContainerImpl<CVisObjExtension>,
	public CProxyIVisQuery<CVisObjExtension>,
#else
	public CComConnectionPointContainerImpl,
#endif // _ATL_VER
	public CComCoClass<CVisObjExtension, &CLSID_ObjVisInfoExtension>
{
private:
#if _ATL_VER < 0x200
	CProxyIVisQuery m_cp;
#endif // _ATL_VER

	char *m_pActProject;
	char *m_pActSight;
	long m_lSichtVisMCode;
//	long m_lObjVisMCode;
	long m_lSichtLegMCode;
	
	char *m_pMWert;				// permanenter Puffer;
	
	class CIgnoreVisErrorTree *m_pVIE;

#if defined(EXTVIS)
	class CVisModuleTree *m_pVMT;
	HDC m_hDC;				// aktueller DC
	HDC m_hTargetDC;			// aktueller TargetDC
#endif
	
	unsigned int m_fAllVisErrIgnore : 1;	// alle VisInfoFehler ignorieren
	unsigned int m_fAutoAssignColors : 1;	// im weiteren Farben automatisch zuweisen
	unsigned int m_fModifyAllSelected : 1;	// alle selektierten Objekte beeinflussen		
	unsigned int m_fFullVisInfo : 1;		// VisInfo vollständig speichern
	unsigned int m_fShowHidden : 1;		// versteckte Objekte anzeigen

#if defined(EXTVIS)
	unsigned int m_fOleInitialized : 1;	// Ole hier initialisiert
#endif
	unsigned int m_fForceShutdown : 1;	// darf nicht entladen werden, wenn OLE initialisiert wurde
	unsigned int m_fRebuildView : 1;	// RebuildSight nochmal rufen

	unsigned int m_fIsDrawing : 1;		// derzeit wird gezeichnet
		
	long m_lIdentHandled;				// Fehlerbehandlung für diesem Ident aktiv

	class CColorControlDlg *m_CCDlg;	// FarbRegelungsDlg
	CVMDMenuMap m_VMDMap;				// MenuItemMap für VMD's

	Menu *m_pMenu;
	CAutoAssignColors m_Colors;			// Farben automatisch zuweisen

public:
	bool AdjustIdentifier (
		long lIdent, DWORD iMode, DWORD iObjTypBits, bool fSet, 
		bool *pfFirst = NULL, const char *pView = NULL);

protected:
// überladene virtuelle Funktion(en) ITriasExtension
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (void);
	STDMETHOD_(BOOL, MenuInit) (HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (UINT uiMenuID, HWND hWnd);
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (WPARAM wParam, LPARAM lParam);

// IVisObjExt
	STDMETHOD(SetVisInfoClass)(long lIdent, VISINFOTYPE rgType, DVisInfo *pIVisInfo, VARIANT vViewName);
	STDMETHOD(GetVisInfoClass)(long lIdent, VISINFOTYPE rgType, VARIANT vViewName, DVisInfo **ppIVisInfo);
	STDMETHOD(ResetVisInfoClass)(long lIdent, VISINFOTYPE rgType, VARIANT vView);
	STDMETHOD(SetVisInfoObject)(long lONr, VISINFOTYPE rgType, DVisInfo *pIVisInfo, VARIANT_BOOL fSameAsSource, VARIANT vViewName);
	STDMETHOD(GetVisInfoObject)(long lONr, VISINFOTYPE rgType, VARIANT vViewName, DVisInfo **ppIVisInfo);
	STDMETHOD(ResetVisInfoObject)(long lONr, VISINFOTYPE rgType, VARIANT vViewName);
	STDMETHOD(GetObjectHiddenStatus)(long lONr, VARIANT vViewName, VARIANT_BOOL *pfShow);
	STDMETHOD(SetObjectHiddenStatus)(long lONr, VARIANT_BOOL fShow, VARIANT vViewName);

// sonstige member
	bool InitMCodes (void);
	void DeInitMCodes (void);

public:
	long GetIdentMCode (bool fGenerate = false, const char *pView = NULL, LONG lIdent = 0);

protected:
	long GetObjMCode (bool fGenerate = false, const char *pView = NULL, LONG lIdent = 0);
	long GetViewMCode (LPCSTR pcView = NULL, bool fGenerate = false);
	long GetViewLegMCode (void);
	long FindFeatureInDataSource (HPROJECT hPr, LPCSTR pcKText);

	DWORD GetIDMode (long Ident, const char *pView = NULL);

	short GetNewVI (long lONr, VisInfo * & rpVI, bool fHidden = false, long lMCode = -1, short fFlags = DF_Normal, char ** = NULL);
	short GetNewVI (HANDLEVISINFO *pHVI, long lMCode = -1, short fFlags = DF_Normal, char ** = NULL);
	short GetNewVIFromView (HPROJECT hPr, LONG lONr, LONG lIdent, LONG lMCode, short fFlags, bool fHidden, LPCSTR pcView, VisInfo *& rpVI, char ** = NULL);

	short HandleErrorMessage (ERRORMESSAGE *pEM);
	bool HandleQueryRechObject (RECHOBJECT *pRO);
	bool HandleDeleteSight (char *pView);
	bool HandleViewCreated (VIEWCREATED *pVC);

// MenuFunktionen
	bool ChangeVisInfo (HWND hORWnd, bool fHSB);
	bool DefineSymbol (HWND hORWnd, CVMDMenuItem *pItem);
	bool ResetVisInfo (HWND hORWnd);
	bool ShowObjects (HWND hWnd);
	bool HideObjects (HWND hWnd);
	
	short HandleVisInfoError (class CVisError *pCVE);
	short DefineNewVisInfo (long lIdent, short iVTyp, bool fHSB);
	bool AutoAssignNextColor (long lIdent, short iVTyp);
	void ResetAutoColors() 
	{
		m_fAutoAssignColors = false;
		m_Colors.Reset();
	}

	bool FindMenuItem (HMENU hMenu, UINT uiID);

public:
	bool ModObjectVisInfo (HANDLEVISINFO *pHVI, bool &fFirst);
	bool ModObjectSymbol (long lONr, char *pVStr, bool &fFirst);
	bool HandleHiddenFlag (long lONr, bool fHide, bool &fFirst, HWND hORWnd = NULL);
	bool HandleHiddenFlag (long lONr, bool fHide, bool &fFirst, LPCSTR pcView, HWND hORWnd = NULL);
	bool GetHiddenFlag (long lONr, bool &rfShow, LPCSTR pcView);
	bool ResetObjectVisInfo (long lONr, LPCSTR pcView = NULL);
	bool WasLastObject (long lIdent, long lMCode, DWORD dwObjTypBit);

protected:
	bool RemoveVisInfo (void);		// ObjektKlasse behandeln
	bool RemoveShowInfo (void);

	typedef BOOL (* HANDLEREMOVECASEPROC)(LONG lONr, HWND hORWnd = NULL, UINT_PTR dwData = 0, UINT_PTR dwLocalData = 0);
	bool HandleCustomVisCommands (REFCLSID rClsId, LPCSTR pcCaption, HANDLEREMOVECASEPROC pFcn, HWND hORWnd = NULL, UINT_PTR dwData = 0, UINT_PTR dwLocalData = 0);
	bool HandleCustomVisCommands (REFCLSID rClsId, UINT uiResCap, HANDLEREMOVECASEPROC pFcn, HWND hORWnd = NULL, UINT_PTR dwData = 0, UINT_PTR dwLocalData = 0);

	bool ExportVisInfo (void);		// Exportieren der VisAsc
	bool ImportVisInfo (void);		// Importieren einer VisAsc

	bool ControlColors (void);		// Farbregelung
			
	short ParseVisString (long lONr, VisInfo *& rVI, short fFlags, char **);

#if defined(EXTVIS)
// Funktion, die ein Objekt in einem Vismodule zeichnen läßt ------------------
	DWORD DrawCustom (long lONr, char *pVisModule, short &fFlags,
			  VisInfo *pVI, char *pVisInfoString);
#endif

friend BOOL PASCAL _XTENSN_EXPORT ObjChangeVisInfo (long lONr, BOOL, void *pData);
friend BOOL PASCAL _XTENSN_EXPORT ObjChangeSymbol (long lONr, BOOL, void *pData);
friend BOOL PASCAL _XTENSN_EXPORT ObjResetVisInfo (long lONr, BOOL, void *pData);
friend BOOL PASCAL _XTENSN_EXPORT ObjHideVisInfo (long lONr, BOOL, void *pData);
friend bool PASCAL _XTENSN_EXPORT ChangeVisInfo (HANDLEVISINFO *pHVI, char **);
friend BOOL PASCAL _XTENSN_EXPORT ExportViewIdent (long lIdent, BOOL, void *pData);
friend BOOL PASCAL _XTENSN_EXPORT ExportViewObject (long lONr, BOOL, void *pData);
friend BOOL PASCAL _XTENSN_EXPORT HandleIdentOnDeleteSight (long lIdent, BOOL, void *pData);
friend BOOL PASCAL _XTENSN_EXPORT HandleViewCreatedObject (long lONr, DWORD, void *pData);
	
public:
// Konstruktor / Destruktor
		CVisObjExtension (void);
		~CVisObjExtension (void);

	BEGIN_COM_MAP(CVisObjExtension)
		COM_INTERFACE_ENTRY(IVisObjExt)
#if _ATL_VER >= 0x200
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
#else
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
#endif // _ATL_VER
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

// unterstützte ConnectionPoints
	BEGIN_CONNECTION_POINT_MAP(CVisObjExtension)
#if _ATL_VER >= 0x200
		CONNECTION_POINT_ENTRY(IID_IVisQuery)
#else
		CONNECTION_POINT_ENTRY(m_cp)
#endif // _ATL_VER
	END_CONNECTION_POINT_MAP()

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(CVisObjExtension, g_pTE)

static DWORD StringToIdMode (char *pMText, long *plObjMCode = NULL);
static char *IdModeToString (DWORD iMode, long lObjMCode);

	bool RebuildSight (void);

inline bool SaveFullVisInfo (void) { return m_fFullVisInfo ? true : false; }

friend bool WriteTextMerkmal (short iTTyp, long lTarget, long lMCode, const char *pText, const char *pcView = NULL);
friend bool ReadTextMerkmal (short iTTyp, long lTarget, long lMCode, char *pText, int iLen = -1, const char *pcView = NULL);
friend HANDLEVISINFO *GetObjectVisInfo (long lONr, char *pView = NULL, long lMCode = -1, 
			char ** = NULL, short fFlags = DF_Analyze);
friend HANDLEVISINFO *GetIdentVisInfo (long lIdent, short iVTyp, char *pView = NULL);
friend bool HandleViewCreatedIdentEx (long lIdent, VIEWCREATED *pVC, short iVTyp, short iOTyp);
};


// globale Funktionen ---------------------------------------------------------
char * VisInfoToString (HANDLEVISINFO *pHVI, bool fFullVisInfo = true, ResourceFile *pRF = NULL, 
	bool fRGB = true, char *pIdString = NULL, bool fExport = false, char **cbModuleInfo = NULL, 
	char *pLegInfo = NULL, long lUpperScale = 0, long lLowerScale = 0);

extern const ResID resMissing;
bool SaveMCodeInPbd (long lMCode, const char *pView, const char *pKT, const char *pLT = "", bool fView = true, LONG lIdent = 0);
long GetObjMCodeView (const char *pView, long lSichtMCode, ResID resKT = resMissing, ResID resLT = resMissing, bool fGenerate = false, LONG lIdent = 0);

HRESULT CreateVisInfo (VisInfo *pVis, class CVisInfoInterfaceBase **ppIVis);

HANDLEVISINFO *ctHANDLEVISINFO (short iTyp, bool fExtended = false);	// Konstruktor
void dtHANDLEVISINFO (HANDLEVISINFO *& pHVI);	// Destruktor

bool AddIDtoSight (char *chViewName, long lIdent, VisInfo *pVI, long lUpper = 0, long lLower = 0, short iTypes = -1);
bool AddOKStoSight (char *chViewName, char *pOKS, VisInfo *pVI, long lUpper = 0, long lLower = 0, short iTypes = -1);
bool AddVItoObject (char *chViewName, long lONr, VisInfo *pVI, short iDrawResult, char **);
bool AddLegInfoToIdent (char *pView, long lIdent, char *pLegInfo);
bool AddLegInfoToObject (char *pView, long lONr, char *pLegInfo);

short OTypToVTyp (short iOTyp);
long FindObjekt (char *pUIdent, long lMCode);
long GetHeaderMCode (bool fGenerate, ResID resID, ResID resKT, ResID resLT, LPCSTR pcView = NULL);

bool InitYY1Parse (void);
void EndYY1Parse (void);

///////////////////////////////////////////////////////////////////////////////
// Objekttypen werden operationsspezifisch als Bits kodiert:
// Objektbezogene Visualisierung:	Bits 16..19
// Objektbezogenes Ausblenden:		Bits 20..23
inline 
DWORD GetObjectModeBits (DWORD iObjTypBits, DWORD iMode)
{
DWORD dwBits = 0L;

	if (iMode & OVModVisInfo)
		dwBits |= (iObjTypBits & (OTPunkt|OTLinie|OTFlaeche|OTText)) << 16;
	if (iMode & OVModShow)
		dwBits |= (iObjTypBits & (OTPunkt|OTLinie|OTFlaeche|OTText)) << 20;
	return dwBits;
}

inline
DWORD GetObjectTypeBits (DWORD iIdentMode, DWORD iMode)
{
	if (iIdentMode & OVObjectTypeUsed) {
		if (iMode & OVModVisInfo)
			return (iIdentMode >> 16) & (OTPunkt|OTLinie|OTFlaeche|OTText);
		if (iMode & OVModShow)
			return (iIdentMode >> 20) & (OTPunkt|OTLinie|OTFlaeche|OTText);
		return 0;
	} 
	return (OTPunkt|OTLinie|OTFlaeche|OTText);
}

///////////////////////////////////////////////////////////////////////////////
// Stringhelper-Funktionen
void __cdecl Format (os_string& rStr, LPCTSTR lpszFormat, ...);
void FormatV (os_string& rStr, LPCTSTR lpszFormat, va_list argList);
os_string __cdecl FakeTRiASName (ResID resID, ...);
os_string __cdecl FakeTRiASName (LPCSTR pcTempl, ...);

#endif 	// _VISOBJ_HXX
