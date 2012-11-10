// Memberfunktionen zur Verwaltung der QNFY - Anforderungen
// File: EXTQNFY.CXX

#include "triaspre.hxx"

#include <ospace/views/mapview.h>

#include <dirisole.h>
#include <ScopeVar.h>

#include "extmain3.hxx"
#include "extqnfy2.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// 
#define WM_CORRECTSHOWNPOSITION	(WM_USER+0x4321)

namespace {
///////////////////////////////////////////////////////////////////////////////
// Liste von Notifikationen, die es erfordern, das die Liste der zu benachrichtigenden
// Erweiterungen kopiert und zwischengespeichert wird, da während ihrer Bearbeitung
// andere (oder diese?) Notifikationen abgemeldet werden können.
// Diese Liste wird in der Debug-Variante empirisch durch _ASSERTE's ermittelt und
// muß dann entsprechend laufend gehalten werden.
	const UINT g_uiCritMsgs[] = {
		DEX_INITIALIZEDSERVER,
		DEX_N_UIREADY,
		DEX_N_TIPOFTHEDAY,
		DEX_OBJECTCHANGED,		// #HK020426: IGM
		DEX_MODIFYMERKMAL,		// #HK020426: IGM
	};
	const int CRITICAL_MESSAGE_COUNT = _countof(g_uiCritMsgs);
}

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen für die Hashtabelle in der die QNFY (QueryNotifications) 
// abgelegt sind. Diese HashTabelle ist über die Message sortiert, wobei
// an einer Message alle die Extensions hängen, die die entsprechende 
// Message erhalten sollen.
QueryNotifyHash::QueryNotifyHash (ExtensionList &rEL)
	: m_rEL(rEL), m_ptLastMousePos(0, 0), m_hPrCtx(HACTCONNECTION)
{
	for (int i = 0; i < CRITICAL_MESSAGE_COUNT; ++i)
		m_setCritMsg.insert(g_uiCritMsgs[i]);
}

QueryNotifyHash::~QueryNotifyHash (void)
{
	_ASSERTE(0 == size());		// hier sollte alles abgemeldet sein
	erase();
}

//#pragma optimize ("", off)

// Die folgende Funktion verteilt eine Message an alle Erweiterungen, die
// diese Message registriert haben
LRESULT QueryNotifyHash::Dispatch (HWND hWnd, Event &e)
{
bool iDexMsg = false;	// WindowsMessage annehemen
WPARAM iKey = e.Msg();
LRESULT R;

	if (e.Msg() == __DexNotify) {	
	// interne Messages haben einen anderen Aufbau
		iKey = e.WParam();
		iDexMsg = true;
	} else if (NULL != hWnd) {	// nur solange m_rEL gültig ist
	// Alle WindowsMessages über ITRiASSysNotificationSink verschicken
	HRESULT hr = S_OK;

		if (e.Msg() >= WM_MOUSEFIRST && e.Msg() <= WM_MOUSELAST) {
			m_ptLastMousePos = Point (LOWORD(e.LParam()), HIWORD(e.LParam()));
			hr = m_rEL.WindowsMessage (hWnd, e.Msg(), e.WParam(), e.LParam());

		// anzuzeigende Koordinaten durchrufen
			m_rEL.WindowsMessage (hWnd, WM_CORRECTSHOWNPOSITION, e.Msg(), MAKELONG(m_ptLastMousePos.X(), m_ptLastMousePos.Y()));
		} else 
			hr = m_rEL.WindowsMessage (hWnd, e.Msg(), e.WParam(), e.LParam());

		if (S_FALSE == hr)
			return true;	// Message verarbeitet
	}

iterator it_lower = lower_bound(iKey);

	if (it_lower == end() || (*it_lower).first != iKey)
		return false;	// keine potentiellen Empfänger vorhanden

#if defined(_REJECT_MESSAGES)
// Verhindern, daß identische WindowsMessages verschachtelt werden
CMessageToHandle hm (*this, iKey, iDexMsg);

	if (!hm.toHandle()) {
		TX_TRACE2("TRiAS:Rejected %s message %ld\r\n", iDexMsg ? "native" : "system", iKey);
		return false;
	}
#endif // _REJECT_MESSAGES

// SnapShot der geforderten Extensions anlegen
iterator it_upper = upper_bound(iKey);
size_type iEntries = 0;

	distance (it_lower, it_upper, iEntries);
	if (iEntries > 1) {		// mehr als ein Empfänger
		if (MsgIsCritical(iKey)) {
		// kritische Messages müssen Liste der Erweiterungen kopieren
		CMessageList lstCopy;

			try {
			insert_iterator<CMessageList> ins (lstCopy, lstCopy.begin());
			multimap_values<UINT, QNFY, less<UINT> > values (*this, it_lower, it_upper);

				copy (values.begin(), values.end(), ins);

			} catch (...) {
				TX_ASSERT(false);
				return false;
			}

		// jetzt durch alle gewünschten Extensions durchgehen
			for (CMessageList::iterator it = lstCopy.begin(); it != lstCopy.end(); ++it) 
			{
			QNFY &rQ = *it;
			HWND h = iDexMsg ? (HWND)rQ.hWnd() : (HWND)rQ.hDex();

				if (iDexMsg == rQ.isDexMsg()) {
					R = rQ.Notify (h, e.Msg(), e.WParam(), e.LParam());
					if (R != 0) return R;	// Message bearbeitet -> raus
				}
			} 
		}
		else {
		// unkritische Messages können direkt enumeriert werden
		CMessageGuard Guard (iKey, this);

			for (iterator it = it_lower; it != it_upper; ++it) 
			{
			QNFY &rQ = (*it).second;
			HWND h = iDexMsg ? (HWND)rQ.hWnd() : (HWND)rQ.hDex();

				if (iDexMsg == rQ.isDexMsg()) {
					R = rQ.Notify (h, e.Msg(), e.WParam(), e.LParam());
					if (R != 0) return R;	// Message bearbeitet -> raus
				}
			} 
		// dtor von CMessageGuard löst ggf. ASSERT's aus, wenn Liste der 
		// Msgs modifiziert wurde
		} 
	} 
	else {
		TX_ASSERT(1 == iEntries);	// darf nur noch einer da sein

	QNFY &rQ = (*it_lower).second;
	HWND h = iDexMsg ? (HWND)rQ.hWnd() : (HWND)rQ.hDex();

		if (iDexMsg == rQ.isDexMsg()) {
			R = rQ.Notify (h, e.Msg(), e.WParam(), e.LParam());
			if (R != 0) return R;	// Message bearbeitet -> raus
		}
	} 
	return false;	// Message nicht verarbeitet
}

LRESULT QueryNotifyHash::Dispatch (HPROJECT hPr, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
bool iDexMsg = false;	// WindowsMessage annehmen
WPARAM iKey = wMsg;
LRESULT R;

	if (wMsg == __DexNotify) {	
	// interne Messages haben einen anderen Aufbau
		iKey = wParam;
		iDexMsg = true;
	}

iterator it_lower = lower_bound(iKey);

	if (it_lower == end() || (*it_lower).first != iKey)
		return false;	// keine potentiellen Empfänger vorhanden

#if defined(_REJECT_MESSAGES)
// Verhindern, daß identische WindowsMessages verschachtelt werden
CMessageToHandle hm (*this, iKey, iDexMsg);

	if (!hm.toHandle()) {
		TX_TRACE2("TRiAS:Rejected %s message %ld\r\n", iDexMsg ? "native" : "system", iKey);
		return false;
	}
#endif // _REJECT_MESSAGES

// SnapShot der geforderten Extensions anlegen
iterator it_upper = upper_bound(iKey);
size_type iEntries = 0;
CScopeVar<HPROJECT> Ctx (m_hPrCtx, hPr);

	distance (it_lower, it_upper, iEntries);
	if (iEntries > 1) {		// mehr als ein Empfänger
		if (MsgIsCritical(iKey)) {
		CMessageList lstCopy;

			try {
			insert_iterator<CMessageList> ins (lstCopy, lstCopy.begin());
			multimap_values<UINT, QNFY, less<UINT> > values (*this, it_lower, it_upper);

				copy (values.begin(), values.end(), ins);

			} catch (...) {
				TX_ASSERT(false);
				return false;
			}

		// jetzt durch alle gewünschten Extensions durchgehen
			for (CMessageList::iterator it = lstCopy.begin(); it != lstCopy.end(); ++it) 
			{
			QNFY &rQ = *it;
			HWND h = iDexMsg ? (HWND)rQ.hWnd() : (HWND)rQ.hDex();

				if (iDexMsg == rQ.isDexMsg()) {
					R = rQ.Notify (h, wMsg, wParam, lParam);
					if (R != 0) return R;	// Message bearbeitet -> raus
				}
			} 
		}
		else {
		// unkritische Messages können direkt enumeriert werden
		CMessageGuard Guard (iKey, this);

			for (iterator it = it_lower; it != it_upper; ++it) 
			{
			QNFY &rQ = (*it).second;
			HWND h = iDexMsg ? (HWND)rQ.hWnd() : (HWND)rQ.hDex();

				if (iDexMsg == rQ.isDexMsg()) {
					R = rQ.Notify (h, wMsg, wParam, lParam);
					if (R != 0) return R;	// Message bearbeitet -> raus
				}
			} 
		// dtor von CMessageGuard löst ggf. ASSERT's aus, wenn Liste der 
		// Msgs modifiziert wurde
		}
	} 
	else {
		TX_ASSERT(1 == iEntries);	// darf nur noch einer da sein

	QNFY &rQ = (*it_lower).second;
	HWND h = iDexMsg ? (HWND)rQ.hWnd() : (HWND)rQ.hDex();

		if (iDexMsg == rQ.isDexMsg()) {
			R = rQ.Notify (h, wMsg, wParam, lParam);
			if (R != 0) return R;	// Message bearbeitet -> raus
		}
	}
	return false;	// Message nicht verarbeitet
}

// Einhängen einer NotifikationsAnforderung in die HashTabelle ----------------
bool QueryNotifyHash::RegisterQNFY (Extension &rExt, HWND hWnd, LPARAM lMsg)
{
	try {
	QNFY Entry (hWnd, rExt, HIWORD(lMsg));
	iterator it = insert(value_type(LOWORD(lMsg), Entry));

		return it != end();
	} catch (...) {
		return false;
	}
}

bool QueryNotifyHash::UnRegisterQNFY (Extension &rExt, LPARAM lMsg)
{
UINT uiMsg = LOWORD(lMsg);
HDEX hDex = rExt.hLib();
pair<iterator, iterator> p = equal_range(uiMsg);
bool fResult = false;

	if (p.first != end() && (*p.first).first == uiMsg) {
	// wenigstens eine Extension mit dieser Message gefunden
		while (p.first != p.second) {
			if ((*p.first).second.hDex() == hDex && 
			    (*p.first).second.isDexMsg() == (HIWORD(lMsg) != 0)) 
			{
				UnRegisterQNFY((*p.first).first);	// aktive Messages melden
				erase(p.first);				// QNFY aus HashTabelle löschen
				fResult =  true;
				break;
			}
			++p.first;
		} 
	}

	TX_ASSERT(fResult);
	return fResult;		// nichts gefunden
}

bool QueryNotifyHash::UnRegisterAllQNFYs (HDEX hDex)
{
bool fRet = true;

// gesamte HashTabelle durchgehen und alles löschen, was zu einer 
// Extension gehört
	for (iterator it = begin(); it != end(); ) {
		if ((*it).second.hDex() == hDex) {
		iterator it_del = it++;

			UnRegisterQNFY((*it_del).first);	// aktive Messages melden
			erase(it_del);
		} else
			it++;
	}
	TX_ASSERT(!ExtHasRegisteredNfys (hDex));
	return fRet;
}

#if defined(_DEBUG)
///////////////////////////////////////////////////////////////////////////////
// Testen, ob Erweiterung Notifications angemeldet hat 
bool QueryNotifyHash::ExtHasRegisteredNfys (HDEX hDex)
{
// Gesamte HashTabelle durchgehen und nachsehen, ob was zu einer 
// Extension gehört.
	for (iterator it = begin(); it != end(); ++it) {
		if ((*it).second.hDex() == hDex) 
			return true;
	}
	return false;		// nichts registriert
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob Erweiterung eine bestimmte Notification angemeldet hat 
bool QueryNotifyHash::ExtHasRegisteredNfy (HDEX hDex, LPARAM lMsg)
{
// Gesamte HashTabelle durchgehen und nachsehen, ob was zu einer 
// Extension gehört.
	for (iterator it = begin(); it != end(); ++it) {
		if ((*it).second.hDex() == hDex && 
		    (*it).second.isDexMsg() == (HIWORD(lMsg) != 0)) 
		{
			return true;
		}
	}
	return false;		// nichts registriert
}
#endif // _DEBUG
