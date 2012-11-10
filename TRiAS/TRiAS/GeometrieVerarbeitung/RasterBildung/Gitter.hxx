// Erweiterungsklasse für "Bilden von Gittern"
// File: Gitter.hxx
// W. Mörtl
                    
                    
#if !defined(_GITTER_HXX_)
#define _GITTER_HXX_


#include <ospace/std/vector>

#include <TRiASHelper.h>	// tagPIFLAGS in "progstat.h", IProgressIndicator2
#include "progstat.h"		// BaseProgressStatus in ProgressProxy.h
#include "ProgressProxy.h"	// CProxyIProgressIndicator2

#include "SmartInterfaces.h"

#include "RastGuid.h"		// CLSID_RasterExtension



///////////////////////////////////////////////////////////////////////////////////////////////
class RasterExtension : public CTriasExtension,
#if defined(__ATL_20_USED__)
						public CProxyIProgressIndicator2<RasterExtension>,
						public IConnectionPointContainerImpl<RasterExtension>,
#else
						public CComConnectionPointContainerImpl,
#endif // defined(__ATL_20_USED__)
						public CComCoClass<RasterExtension, &CLSID_RasterExtension>
{
private:
#if defined(__ATL_20_USED__)
	typedef CProxyIProgressIndicator2<RasterExtension> CPIProxy;
	CPIProxy *GetPIProxy() { return this; }
#else
	CProxyIProgressIndicator2 m_PPI;
	typedef CProxyIProgressIndicator2 CPIProxy;
	CPIProxy *GetPIProxy() { return &m_PPI; }
#endif // !defined(__ATL_20_USED__)

	DWORD m_dwCookie;		// Nummer des ConnectionPoint

	short m_iMode;			// Parameter von InitExtension()

	Menu* m_pPopupMenu;		// PopupMenü im Hauptmenü

	long m_lGridCnt;		// Anzahl der erzeugten Gitterobjekte
	vector<long> m_vlObjNr;	// Feld der Objektnummer der gebildeten Gitterflächen bzw. -linien
	bool m_bEnableDelMenu;	// Menüpunkt für Löschen der Gitter
	bool m_bMenIt;			// MenuItem nicht/installiert (false/true)
 	bool m_bGridsDeleted;	// Gitter werden im Augenblick über Menüpunkt "Gitter löschen" gelöscht (true)

	KoOrd m_PaintRecRO;		// Koordinaten des Bereiches, der gezeichnet bzw.
	KoOrd m_PaintRecRU;		//  gelöscht werden soll
	KoOrd m_PaintRecHU;
	KoOrd m_PaintRecHO;

	bool InitAndOPEN (int iMode);
	void UnLoadAndCLOSE (void);
	HRESULT InitProgressIndicator (IProgressIndicator2* pPI, ResID uiTitel, ResID uiAdjust,
								   ulong ulMaxPos, ulong ulMinPos = 1);
	HRESULT RegisterPI (IProgressIndicator2* pPI);
	HRESULT UnRegisterPI (void);

protected:
// überladene virtuelle Funktionen
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, MenuInit) (HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (WPARAM wParam, LPARAM lParam);
	STDMETHOD_(BOOL, UnLoadExtension) (void);

public:
// Konstruktor / Destruktor
		RasterExtension (void);
		~RasterExtension (void);

	BEGIN_COM_MAP(RasterExtension)		// Makro
		COM_INTERFACE_ENTRY(ITriasXtension2)
		COM_INTERFACE_ENTRY(ITriasXtension)
#if defined(__ATL_20_USED__)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
#else
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
#endif // !defined(__ATL_20_USED__)
	END_COM_MAP()
	DECLARE_NO_REGISTRY()

	DECLARE_NOT_AGGREGATABLE_SINGLE(RasterExtension, g_pTE)

	BEGIN_CONNECTION_POINT_MAP(RasterExtension)	// Makro
#if defined(__ATL_20_USED__)
		CONNECTION_POINT_ENTRY(IID_IProgressIndicator2)
#else
		CONNECTION_POINT_ENTRY(m_PPI)
#endif // !defined(__ATL_20_USED__)
	END_CONNECTION_POINT_MAP()

// Memberfunktionen
void ReturnResults (long lGridCnt, vector<long> vlObjNr, EPunkt PLO, EPunkt PRU,
					double dXWidth, double dYWidth);
};

#endif  // _GITTER_HXX_
