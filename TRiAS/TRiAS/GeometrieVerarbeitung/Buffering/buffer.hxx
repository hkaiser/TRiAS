// Erweiterungsklasse für "Puffer um GeoObjekte"
// File: BUFFER.HXX
// W. Mörtl

#if !defined(_BUFFER_HXX)
#define _BUFFER_HXX


#include "BufferR.h"		// Ressourcekonstante IDS_BEARB_OBJEKT in ProgressProxy.h

#include <TRiASHelper.h>	// tagPIFLAGS in "progstat.h", IProgressIndicator2
#include "progstat.h"		// BaseProgressStatus in ProgressProxy.h
#include "ProgressProxy.h"	// CProxyIProgressIndicator2

#include "SmartInterfaces.h"

///////////////////////////////////////////////////////////////////////////////
// LizensierungsKlasse
#if defined(_DEBUG)
extern "C" bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

class CMyLicense
{
protected:
	static BOOL VerifyLicenseKey(BSTR bstr)
	{
	CComBSTR bstrKey;

		USES_CONVERSION;
		if ((GetLicenseKey (0, &bstrKey) && !wcscmp (bstrKey, bstr)) ||
			 ::SetLicensed (OLE2A(bstr)))
		{
			return TRUE;
		}
		return FALSE;
	}

	static BOOL GetLicenseKey (DWORD, BSTR *pBstr) 
	{
	CComBSTR bstrKey (_MAX_PATH, (LPCOLESTR)NULL);

		if (!::GetLicenseKey (bstrKey.m_str, _MAX_PATH))
			return FALSE;

		*pBstr = bstrKey.Detach(); 
		return TRUE;
	}

	static BOOL IsLicenseValid() { return g_fGlobalLic || ::GetLicensed(); }
};

class BufferExtension : public IExtendBuffer,
						public CTriasExtension,
#if defined(__ATL_20_USED__)
						public CProxyIProgressIndicator2<BufferExtension>,
						public IConnectionPointContainerImpl<BufferExtension>,
#else
						public CComConnectionPointContainerImpl,
#endif // defined(__ATL_20_USED__)
						public CComCoClass<BufferExtension, &CLSID_BufferExtension>
{
private:
#if defined(__ATL_20_USED__)
	typedef CProxyIProgressIndicator2<BufferExtension> CPIProxy;
	CPIProxy *GetPIProxy() { return this; }
#else
	CProxyIProgressIndicator2 m_PPI;
	typedef CProxyIProgressIndicator2 CPIProxy;
	CPIProxy *GetPIProxy() { return &m_PPI; }
#endif // !defined(__ATL_20_USED__)
	DWORD m_dwCookie;	// Nummer des ConnectionPoint

	ERRHANDLER m_oldEH;	// alte Fehlerbehandlungs-Methode

	pWindow m_pW;		// Zeiger auf ein Fenster (ObjektRechercheFenster oder HauptFenster)
	HWND _hWnd;
	short m_iMode;		// Parameter von InitExtension()

	CoordTransX* m_pCT;

    WExtendGeoRein m_wGeoRein;	// Interface für Ankopplung von GeoRein.ext	
    bool m_bGeoRein;			// Ankopplung von GeoRein.ext ist erfolgt (true)

	string m_sBuffer;	// Kurztext einer neuen Puffer-Objektklasse
	double m_dWidth;	// Pufferbreite
	int m_iPuffAnzahl;	// Anzahl der zu bildenden Puffer
	bool _bTyp;      	// Puffertyp (echter Puffer: true, Kreis: false)
	PuffBau m_PBau;		// Puffer ringförmig / als volle Fläche
//	PuffBau m_PBauSave;	// zwischengespeicherter m_PBau-Wert, wenn m_RingCBox deaktiviert ist
	ConvexMode m_cmMode;// Ausformung der konvexen Ecken
	double m_dPrec;		// Kantenlänge (in Meter) des n-Ecks, durch den Kreisbogen an konvexen
						// Ecken approximiert wird
	BuffSide m_bsSide;	// die Seite, bei der der Puffer gebildet werden soll
	bool m_bPosTurn;	// aktuelle Kantenstrecke dreht sich im Vergleich zur vorhergehenden
						// Strecke mathematisch positiv/negativ (true/false)
	KoOrd m_px, m_py;	// Stützpunkt eines Pufferelementes bei m_cmMode == BUFF_TIP
	int m_iKonvex;		// bei geschlossener Kante ist Ecke am Anfangs-/Endpunkt konvex (+1)
						// bzw. konkav (-1); m_iKonvex == 0 bedeutet, daß Kante nicht
	KoOrd m_sx, m_sy;	// Stützpunkt eines Pufferelementes für geschlossene Kante bei
						// m_cmMode == BUFF_TIP

	long* m_plONr;		// Feld der Objektnummer der gebildeten Pufferflächen
	long m_lAnzPuff;	// Größe des m_plONr-Feldes
	long m_lObjInd;		// Laufindex von m_plONr
	bool _LoeMenAkt;	// Lösch-Menüpunkt aktiviert (true) oder nicht (false)
	bool _bPuffLoesch;	// Puffer werden über Menüpunkt "Puffer löschen" gelöscht (true)

	bool InitAndOPEN (int iMode);
	void UnLoadAndCLOSE (void);

	bool Vorarbeit (int i, ulong ulBIdent, long lONr, ulong ulObjIdent, ulong& ulBufIdent,
					SpForm& sfSForm);
	bool PunktPuffer (long lONr, ulong ulObjIdent, KoOrd* plXK, KoOrd* plYK, ulong ulBIdent,
					  bool bFortAnz = true);
	bool KantenPuffer (long lONr, ulong ulObjIdent, KoOrd* plXK, KoOrd* plYK, long lCnt,
					   ulong ulBIdent, bool bFortAnz = true);
	bool FlaechenPuffer (long lONr, ulong ulObjIdent, KoOrd* plXK, KoOrd* plYK, long* plCnt,
						 ulong ulBIdent, bool bFortAnz = true);
	EFlaeche* PointBuffering (KoOrd x, KoOrd y, double dWidth, double dPrec,
							  CPIProxy* pPSt = NULL);
	EFlaeche* LineBuffering (KoOrd* plXK, KoOrd* plYK, long lCnt, double dWidth,
					  BuffSide bsSide, ConvexMode cmMode, double dPrec, CPIProxy* pPSt = NULL);
	EFlaeche* AreaBuffering (KoOrd* plXK, KoOrd* plYK, long lCnt, double dWidth,
					  BuffSide bsSide, ConvexMode cmMode, double dPrec, CPIProxy* pPSt = NULL);
	void PufferLoeschen (void);
	void PufferVisualisieren (ObjTyp iOT, ulong ulObjIdent, ulong ulBufIdent, int i);
	void RangeToPaint (Rectangle& Rec);

	HRESULT InitProgressIndicator (IProgressIndicator2* pPI, ResID uiTitel, ResID uiAdjust,
								   ulong ulMaxPos, ulong ulMinPos = 1);
	HRESULT RegisterPI (IProgressIndicator2* pPI);
	HRESULT UnRegisterPI (void);

//	EFlaeche* BufferElement1 (KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2, KoOrd lX3, KoOrd lY3,
//							double dWidth, BuffSide bsSide, ConvexMode cmMode, DoublePair dUF);
	EFlaeche* BufferElement2 (KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2, KoOrd lX3, KoOrd lY3,
			  double dWidth, BuffSide bsSide, ConvexMode cmMode, double dPrec, DoublePair dUF);
	EFlaeche* BufferElement3 (KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2, KoOrd lX3, KoOrd lY3,
			  double dWidth, BuffSide bsSide, ConvexMode cmMode, double dPrec, DoublePair dUF);
	EFlaeche* BufferElement4 (KoOrd lX0, KoOrd lY0, KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2,
			  double dWidth, BuffSide bsSide, ConvexMode cmMode, double dPrec, DoublePair dUF);
	EFlaeche* BufferElement5 (KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2, KoOrd lX3, KoOrd lY3,
			  double dWidth, BuffSide bsSide, ConvexMode cmMode, double dPrec, DoublePair dUF);
	bool StartValuesForTipMode (KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2, KoOrd lX3,
								KoOrd lY3, double dWidth, DoublePair dUF);
	EFlaeche* TipModePositive (double* xb, double* yb, KoOrd lX3, KoOrd lY3, double k21,
							   double k22, DoublePair dUF);
	EFlaeche* TipModeNegative (double* xb, double* yb, KoOrd lX3, KoOrd lY3, double k21,
							   double k22, DoublePair dUF);
	EFlaeche* TipModeStart (double* xb, double* yb, KoOrd lX0, KoOrd lY0, KoOrd lX1, KoOrd lY1,
					KoOrd lX2, KoOrd lY2, double dWidth, double k1, double k2, DoublePair dUF);
	EFlaeche* TipModeStop (double* xb, double* yb, double k1, double k2, DoublePair dUF);

	HRESULT GeoReinInterface (void);

protected:
// überladene virtuelle Funktionen
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, MenuInit) (HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (WPARAM wParam, LPARAM lParam);
	STDMETHOD_(BOOL, UnLoadExtension) (void);

public:
// Konstruktor / Destruktor
		BufferExtension (void);
		~BufferExtension (void);

	BEGIN_COM_MAP(BufferExtension)		// Makro
		COM_INTERFACE_ENTRY(ITriasXtension2)
		COM_INTERFACE_ENTRY(ITriasXtension)
		COM_INTERFACE_ENTRY(IExtendBuffer)
#if defined(__ATL_20_USED__)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
#else
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
#endif // !defined(__ATL_20_USED__)
	END_COM_MAP()
	DECLARE_NO_REGISTRY()

	DECLARE_NOT_AGGREGATABLE_SINGLE(BufferExtension, g_pTE)
	DECLARE_CLASSFACTORY2(CMyLicense)

	BEGIN_CONNECTION_POINT_MAP(BufferExtension)		// Makro
#if defined(__ATL_20_USED__)
		CONNECTION_POINT_ENTRY(IID_IProgressIndicator2)
#else
		CONNECTION_POINT_ENTRY(m_PPI)
#endif // !defined(__ATL_20_USED__)
	END_CONNECTION_POINT_MAP()


// Memberfunktion
	// Member setzen
	void SetBreite (double dWidth) { m_dWidth = dWidth; }
	void SetAnzahl (int iPuffAnzahl) { m_iPuffAnzahl = iPuffAnzahl; }
	void SetTyp (bool bTyp) { _bTyp = bTyp; }

	// Puffer bilden
	bool PufferBilden (long lONr, ulong ulBIdent = 0, bool bFortAnz = true);

	// IUnknown methods
	HRESULT Pufferbildung_ONr (long lONr, double dWidth, int iPuffAnzahl, PuffBau bPBau,
			 SpForm sfSForm, bool _bTyp, ulong ulBIdent, bool bFortAnz, IEnumLONG** ppEnumOut);
	HRESULT Pufferbildung_Geom (IObjektGeometrie* pIOG, double dWidth, int iPuffAnzahl,
								PuffBau bPBau, SpForm sfSForm, bool bTyp,
								ulong ulBIdent, bool bFortAnz, IEnumLONG** ppEnumOut);

	// IExtendBuffer-Methoden
	// echter Puffer um lONr- bzw. pIOG-Objektes
	STDMETHOD_ (HRESULT, RealBuffering_ONr) (LONG lONr, double dWidth, short iPuffAnzahl,
						 PuffBau bPBau, SpForm sfSForm, ULONG ulBIdent, IEnumLONG** ppEnumOut);

	STDMETHOD_ (HRESULT, RealBuffering_Geom) (IObjektGeometrie* pIOG, double dWidth,
					 short iPuffAnzahl, SpForm sfSForm, ULONG ulBIdent, IEnumLONG** ppEnumOut);

	// kreisförmiger Puffer um Mittelpunkt des Objektcontainers
	STDMETHOD_ (HRESULT, CircularBuffering_ONr) (LONG lONr, double dWidth, short iPuffAnzahl,
						 PuffBau bPBau, SpForm sfSForm, ULONG ulBIdent, IEnumLONG** ppEnumOut);

	// Pufferung des pIOG-Objektes
	STDMETHOD_ (HRESULT, CircularBuffering_Geom) (IObjektGeometrie* pIOG, double dWidth,
					 short iPuffAnzahl, SpForm sfSForm, ULONG ulBIdent, IEnumLONG** ppEnumOut);

	// einzelner echter Puffer um lONr-Objekt
	STDMETHOD_ (HRESULT, WorkingBuffer_ONr) (LONG lONr, double dWidth, PuffBau bPBau,
								BuffSide bsSide, ConvexMode cmMode, double dPrec, LONG* plONr);

	// einzelner echter Puffer um pInObj-Objekt, der NICHT in die DB gespeichert wird
	STDMETHOD_ (HRESULT, WorkingBuffer_Geom) (IObjektGeometrie* pInObj, double dWidth,
											 PuffBau bPBau, BuffSide bsSide, ConvexMode cmMode,
											 double dPrec, IObjektGeometrie** ppOutObj);
};


EFlaeche* ArcModePositive (double* xb, double* yb, KoOrd lX2, KoOrd lY2, DoublePair dUF,
						   double dPrec);
EFlaeche* ArcModeNegative (double* xb, double* yb, KoOrd lX2, KoOrd lY2, DoublePair dUF,
						   double dPrec);
EFlaeche* ArcModeStart (double* xb, double* yb, KoOrd lX1, KoOrd lY1, double k1, double k2,
						DoublePair dUF, double dPrec);
EFlaeche* ArcModeStop (double* xb, double* yb, KoOrd lX2, KoOrd lY2, double k1, double k2,
					   DoublePair dUF, double dPrec);
EFlaeche* KiteModePositive (double* xb, double* yb, KoOrd lX2, KoOrd lY2, KoOrd lX3, KoOrd lY3,
							double k11, double k12, DoublePair dUF);
EFlaeche* KiteModeNegative (double* xb, double* yb, KoOrd lX2, KoOrd lY2, KoOrd lX3, KoOrd lY3,
							double k11, double k12, DoublePair dUF);
EFlaeche* KiteModeStart (double* xb, double* yb, KoOrd lX1, KoOrd lY1, double k1, double k2,
						 DoublePair dUF);
EFlaeche* KiteModeStop (double* xb, double* yb, KoOrd lX2, KoOrd lY2, double k1, double k2,
						DoublePair dUF);
EFlaeche* PlainModePositive (double* xb, double* yb, KoOrd lX2, KoOrd lY2, KoOrd lX3,
							 KoOrd lY3);
EFlaeche* PlainModeNegative (double* xb, double* yb, KoOrd lX2, KoOrd lY2, KoOrd lX3,
							 KoOrd lY3);
EFlaeche* PlainModeStop (double* xb, double* yb, KoOrd lX1, KoOrd lY1, KoOrd lX2, KoOrd lY2,
						 KoOrd lX3, KoOrd lY3, double dWidth, DoublePair dUF);

bool KreisbogenApprox (EFlaeche* pBE, double xm, double ym, double x0, double y0, double x1,
					   double y1, DoublePair dUF, double dPrec);

EFlaeche* BuildInsideBuffer (EFlaeche* pPartBuff, EFlaeche* pBE);

#endif // _BUFFER_HXX
