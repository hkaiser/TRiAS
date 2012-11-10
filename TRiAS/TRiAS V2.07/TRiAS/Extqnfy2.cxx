// Memberfunktionen zur Verwaltung der QNFY - Anforderungen
// File: EXTQNFY.CXX

#include "triaspre.hxx"

#include <dirisole.h>
#include "extmain3.hxx"
#include "extqnfy2.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Memberfunktionen für die Hashtabelle in der die QNFY (QueryNotifications) 
// abgelegt sind. Diese HashTabelle ist über die Message sortiert, wobei
// an einer Message alle die Extensions hängen, die die entsprechende 
// Message erhalten sollen.
QueryNotifyHash::QueryNotifyHash (ExtensionList &rEL)
		 : m_rEL(rEL)
{
}

QueryNotifyHash::~QueryNotifyHash (void)
{
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
		if (S_FALSE == m_rEL.WindowsMessage (hWnd, e.Msg(), e.WParam(), e.LParam()))
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
	CMessageMap mapCopy;

		try {
		insert_iterator<CMessageMap> ins (mapCopy, mapCopy.begin());

			copy (it_lower, it_upper, ins);
		} catch (bad_alloc) {
			TX_ASSERT(false);
			return false;
		}

	// jetzt durch alle gewünschten Extensions durchgehen
		for (iterator it = mapCopy.begin(); it != mapCopy.end(); ++it) 
		{
		QNFY &rQ = (*it).second;
		HWND h = iDexMsg ? (HWND)rQ.hWnd() : (HWND)rQ.hDex();

			if (iDexMsg == rQ.isDexMsg()) {
//				TX_ASSERT(m_rEL.IsValidExtension(rQ.hDex()));
				
				R = rQ.Notify (h, e.Msg(), e.WParam(), e.LParam());
				if (R != 0) return R;	// Message bearbeitet -> raus
			}
		} 
	} else {
		TX_ASSERT(1 == iEntries);	// darf nur noch einer da sein

	QNFY &rQ = (*it_lower).second;
	HWND h = iDexMsg ? (HWND)rQ.hWnd() : (HWND)rQ.hDex();

		if (iDexMsg == rQ.isDexMsg()) {
//			TX_ASSERT(m_rEL.IsValidExtension(rQ.hDex()));
			
			R = rQ.Notify (h, e.Msg(), e.WParam(), e.LParam());
			if (R != 0) return R;	// Message bearbeitet -> raus
		}
	} 

return false;	// Message nicht verarbeitet
}

LRESULT QueryNotifyHash::Dispatch (UINT wMsg, WPARAM wParam, LPARAM lParam)
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
	
	distance (it_lower, it_upper, iEntries);
	if (iEntries > 1) {		// mehr als ein Empfänger
	CMessageMap mapCopy;

		try {
		insert_iterator<CMessageMap> ins (mapCopy, mapCopy.begin());

			copy (it_lower, it_upper, ins);
		} catch (bad_alloc) {
			TX_ASSERT(false);
			return false;
		}

	// jetzt durch alle gewünschten Extensions durchgehen
		for (iterator it = mapCopy.begin(); it != mapCopy.end(); ++it) 
		{
		QNFY &rQ = (*it).second;
		HWND h = iDexMsg ? (HWND)rQ.hWnd() : (HWND)rQ.hDex();

			if (iDexMsg == rQ.isDexMsg()) {
//				TX_ASSERT(m_rEL.IsValidExtension(rQ.hDex()));

				R = rQ.Notify (h, wMsg, wParam, lParam);
				if (R != 0) return R;	// Message bearbeitet -> raus
			}
		} 
	} else {
		TX_ASSERT(1 == iEntries);	// darf nur noch einer da sein

	QNFY &rQ = (*it_lower).second;
	HWND h = iDexMsg ? (HWND)rQ.hWnd() : (HWND)rQ.hDex();

		if (iDexMsg == rQ.isDexMsg()) {
//			TX_ASSERT(m_rEL.IsValidExtension(rQ.hDex()));

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
	} catch (bad_alloc) {
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
				erase(p.first);		// QNFY aus HashTabelle löschen
				fResult =  true;
				break;
			}
			++p.first;
		} 
#if defined(_DEBUG)
//		TX_ASSERT(!ExtHasRegisteredNfy (hDex, lMsg));
#endif // _DEBUG
	}

	TX_ASSERT(fResult);
	return fResult;		// nichts gefunden
}

bool QueryNotifyHash :: UnRegisterAllQNFYs (HDEX hDex)
{
bool fRet = true;

// gesamte HashTabelle durchgehen und alles löschen, was zu einer 
// Extension gehört
	for (iterator it = begin(); it != end(); ) {
		if ((*it).second.hDex() == hDex) {
		iterator it_del = it++;

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
