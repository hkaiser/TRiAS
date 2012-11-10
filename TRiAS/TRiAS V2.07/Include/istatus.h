// Interfacedeklaration für StatusAnzeige -------------------------------------
// File: ISTATUS.H

#if !defined(_ISTATUS_H)
#define _ISTATUS_H

#undef INTERFACE
#define INTERFACE IProgressIndicator

// 07963818-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IProgressIndicator, 0x07963818L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

DECLARE_INTERFACE_(IProgressIndicator, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IProgressIndicator methods ***
	STDMETHOD_(HWND, InitNew)(THIS_ HWND hWnd, DWORD dwReserved) PURE;
	STDMETHOD(Restart)(THIS_ ULONG uiMinPos, ULONG ulMaxPos, DWORD dwFlags) PURE;
	STDMETHOD(ChangeText)(THIS_ DWORD dwWhichText, LPCSTR pcNewText) PURE;
	STDMETHOD(RetrieveText)(THIS_ DWORD dwWichText, LPSTR cbText, ULONG uiLen) PURE;

	STDMETHOD_(int, SetPosition)(THIS_ ULONG uiNewPos) PURE;
	STDMETHOD_(BOOL, WasCanceled)(THIS) PURE;
};
typedef IProgressIndicator *LPPROGRESSINDICATOR;

///////////////////////////////////////////////////////////////////////////////
// Flags für ChangeText und Init 
#define PIFLAG_CAPTION		0x0001		// Caption beeinflussen
#define PIFLAG_FILE			0x0002		// Feld 'Datei:' beeinflussen
#define PIFLAG_FILENAME		0x0004		// Feld 'Dateiname' beeinflussen
#define PIFLAG_STATUS		0x0008		// Statusfeld1 beeinflussen
#define PIFLAG_RESULT		0x0010		// Statusfeld2 beeinflussen
#define PIFLAG_TIME			0x0020		// automatische Zeitanzeige aktivieren
#define PIFLAG_ADJUSTPERCENT	0x0040	// automatisch Prozente aktualisieren

#define PIFLAG_INIT_SHOWWINDOW	0x0100	// mit erstem Wert anzeigen 

#define PIFLAG_AVI_COPY		0x1000		// Copy-AVI anzeigen
#define PIFLAG_AVI_MOVE		0x2000		// Move-Avi anzeigen
#define PIFLAG_AVI_DELETE	0x3000		// Löschen-AVI anzeigen
#define PIFLAG_AVI_MASK		0x7000		// Maske für AVI-Nummer

#define PIFLAG_ALL			0x007f		// alles anzeigen

#define PIFLAG_RESETCANCEL	0x8000		// nur Canceled rücksetzen

///////////////////////////////////////////////////////////////////////////////
// Flag für dwReserved in InitNew (use only, if you know what you're doing!)
#define PI_INIT_LATER		0x0001		// internal use only !

#endif // _ISTATUS_H
