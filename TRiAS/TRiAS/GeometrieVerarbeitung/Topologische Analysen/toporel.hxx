// Erweiterungsklasse für "Topologische Relationen von Geometrie-Objekten"
// File: TopoRel.hxx
// W. Mörtl

#if !defined(_TOPOREL_HXX)
#define _TOPOREL_HXX


#include <TRiASHelper.h>		// tagPIFLAGS in progstat.h, IProgressIndicator2
#include "progstat.h"			// BaseProgressStatus in ProgressProxy.h
#include "ProgressProxy.h"		// CProxyIProgressIndicator2

#include "SmartInterfaces.h"

#include "TopoRelFunctions.h"	// TopoRelFunc




///////////////////////////////////////////////////////////////////////////////////////////////
class TopoRelatExtension : public IExtendTopRel2,
						   public CTriasExtension,
#if defined(__ATL_20_USED__)
						   public CProxyIProgressIndicator2<TopoRelatExtension>,
						   public IConnectionPointContainerImpl<TopoRelatExtension>,
#else
						   public CComConnectionPointContainerImpl,
#endif // defined(__ATL_20_USED__)
						   public CComCoClass<TopoRelatExtension, &CLSID_Topologie>
{
private:
#if defined(__ATL_20_USED__)
	typedef CProxyIProgressIndicator2<TopoRelatExtension> CPIProxy;
	CPIProxy *GetPIProxy() { return this; }
#else
	CProxyIProgressIndicator2 m_PPI;
	typedef CProxyIProgressIndicator2 CPIProxy;
	CPIProxy *GetPIProxy() { return &m_PPI; }
#endif // !defined(__ATL_20_USED__)

	short m_iMode;			// Parameter von InitExtension()
	bool m_bMenIt;			// MenuItem installiert (true)
//	Menu* m_pMenu;			// Menüpunkt im Hauptmenü
	OGCPosit m_OGCRelat;
	TopoRelFunc* m_pTRF;
	ERRHANDLER m_oldEH;		// alte Fehlerbehandlungs-Methode
	
	// Memberfunktionen
	bool InitAndOPEN (int iMode);
	void UnLoadAndCLOSE (void);

protected:
	// überladene virtuelle Funktionen
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, MenuInit) (HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (WPARAM wParam, LPARAM lParam);
	STDMETHOD_(BOOL, UnLoadExtension) (void);

public:
	// Konstruktor / Destruktor
		TopoRelatExtension (void);
		~TopoRelatExtension (void);

	BEGIN_COM_MAP(TopoRelatExtension)		// Makro
		COM_INTERFACE_ENTRY(ITriasXtension2)
		COM_INTERFACE_ENTRY(ITriasXtension)
		COM_INTERFACE_ENTRY(IExtendTopRel2)
#if defined(__ATL_20_USED__)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
#else
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
#endif // !defined(__ATL_20_USED__)
	END_COM_MAP()
	DECLARE_NO_REGISTRY()

	DECLARE_NOT_AGGREGATABLE_SINGLE(TopoRelatExtension, g_pTE)

	BEGIN_CONNECTION_POINT_MAP(TopoRelatExtension)	// Makro
#if defined(__ATL_20_USED__)
		CONNECTION_POINT_ENTRY(IID_IProgressIndicator2)
#else
		CONNECTION_POINT_ENTRY(m_PPI)
#endif // !defined(__ATL_20_USED__)
	END_CONNECTION_POINT_MAP()

	// weitere Memberfunktionen
	TopoRelFunc* GetRelFunctions (void) const { return m_pTRF; }

	// IExtendTopRel2-Methoden
	STDMETHOD_ (HRESULT, TopoRelationObjObj_ONr) (LONG lONr1, LONG lONr2, Relat* prTR);
	STDMETHOD_ (HRESULT, TopoRelationObjObj_Geom) (IObjektGeometrie* pIOG1,
												   IObjektGeometrie* pIOG2, Relat* prTR);
	STDMETHOD_ (HRESULT, GetObjectsObj_ONr) (LONG lONr, Relat rTR, IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, GetObjectsObj_Geom) (IObjektGeometrie* pIOG, Relat rTR,
											  IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, GetPointInsideArea_ONr) (LONG lONr, double* pdInX, double* pdInY);
	STDMETHOD_ (HRESULT, GetPointInsideArea_Geom) (IObjektGeometrie* pIOG, double* pdInX,
												   double* pdInY);
	STDMETHOD_ (HRESULT, TopoRelationObjObj2_ONr) (LONG lONr1, LONG lONr2, UINT* puiTR);
	STDMETHOD_ (HRESULT, TopoRelationObjObj2_Geom) (IObjektGeometrie* pIOG1,
												    IObjektGeometrie* pIOG2, UINT* puiTR);
};

#endif  // _TOPOREL_HXX
