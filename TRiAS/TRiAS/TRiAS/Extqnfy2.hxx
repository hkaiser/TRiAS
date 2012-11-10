// Klassendefinitionen fuer die Messageverwaltung von QueryNotify Anforderungen
// File: EXTQNFY2.HXX

#if !defined(_EXTQNFY_HXX)
#define _EXTQNFY_HXX

#if defined(_DEBUG)
#define _GUARD_NOTIFICATIONS
#endif // defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff 
#define NOMINMAX
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)		// debug info truncated
#include <ospace/std/set>
#include <ospace/std/map>
#include <ospace/std/list>

///////////////////////////////////////////////////////////////////////////////
// forward declarations
class QNFY;
class QueryNotifyHash;

///////////////////////////////////////////////////////////////////////////////
// verwendete multimap
typedef multimap<UINT, QNFY, less<UINT> > CMessageMap;
typedef list<QNFY> CMessageList;

#if defined(_GUARD_NOTIFICATIONS)
///////////////////////////////////////////////////////////////////////////////
// Die folgende Klasse hilft beim Testen, ob w‰hrend der Abarbeitung einer
// Notifikation evtl. eine andere (oder diese?) abgemeldet wurde.
// Das Ziel ist es, s‰mtlichen 'kritischen' Notifikationen anders zu behandeln
// (Anlegen einer Kopie der Liste der zu benachrichtigenden Erweiterungen).
class CMessageGuard 
{
public:
	CMessageGuard (UINT uiMsg, QueryNotifyHash *pBack);
	~CMessageGuard();

	UINT GetMsgId() { return m_uiMsg; }

private:
	UINT m_uiMsg;
	QueryNotifyHash *m_pBack;
};
#else
///////////////////////////////////////////////////////////////////////////////
// Release: keine besonderen Aufgaben
class CMessageGuard 
{
public:
	CMessageGuard(UINT uiMsg, QueryNotifyHash *pBack) {}
	~CMessageGuard() {}
};
#endif // defined(_GUARD_NOTIFICATIONS)

///////////////////////////////////////////////////////////////////////////////
// Klasse, die in der multimap<> drinh‰ngt 
class QNFY 
{
private:
	HWND m_hWnd;	// FensterHandle
	bool m_fDexMsg;	// WindowsMessage oder interne Message
	Extension *m_pExt;
	HDEX m_hDex;	// workaround f¸r LˆschFehler, der sporadisch auftritt

public:
	QNFY (void) 
		: m_hWnd(NULL), m_pExt(NULL), m_hDex(NULL), m_fDexMsg(false)
	{}
	QNFY (HWND hWnd, Extension &rExt, bool iDexMsg)
		: m_hWnd(hWnd), m_pExt(&rExt)
	{
		m_fDexMsg = iDexMsg ? true : false;	// WindowsMessage oder interne Message
		m_hDex = rExt.hLib();
	}
	QNFY (const QNFY &rEntry)
		: m_hWnd(rEntry.hWnd()), m_pExt(rEntry.Ext())
	{
		m_fDexMsg = rEntry.isDexMsg();		// WindowsMessage oder interne Message
		m_hDex = rEntry.hDex();
	}
	~QNFY (void) {}

	HDEX hDex (void) const { return m_hDex; }
	HWND hWnd (void) const { return m_hWnd; }
	bool isDexMsg (void) const { return m_fDexMsg ? true : false; }
	Extension *Ext (void) const { return m_pExt; }

	LRESULT Notify (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
		{ return m_pExt -> Notify (hWnd, uiMsg, wParam, lParam); }

	operator< (const QNFY &rEntry) const { return -1; }
	operator== (const QNFY &rEntry) const { return 0; }
};

#if defined(_REJECT_MESSAGES)
///////////////////////////////////////////////////////////////////////////////
// Klassen, die verhindern, daﬂ identische Messages verschachtelt behandelt 
// werden
class QueryNotifyHash;		// forward declaration

///////////////////////////////////////////////////////////////////////////////
// Wrapperklasse, welche automatisch Lebensdauer der gerade behandelten Messages
// speichert
class CMessageToHandle 
{
private:
	bool m_fToHandle;

	QueryNotifyHash &m_rQ;
	UINT m_uiMsg;
	bool m_fIsDexMsg;

public:
	inline CMessageToHandle (QueryNotifyHash &rQ, UINT uiMsg, bool fIsDexMsg);
	inline ~CMessageToHandle (void);

inline bool toHandle (void) { return m_fToHandle; }
};

///////////////////////////////////////////////////////////////////////////////
// thread sichere Liste der behandelten messages
class CActiveMessages 
{
private:
// Liste der derzeit behandelten Messages
	typedef set<UINT, less<UINT> > CHandledMap;

	CComAutoCriticalSection m_cs;
	CHandledMap m_data;

	class CLockCS {
	private:
		CComAutoCriticalSection &m_rCS;

	public: 
			CLockCS (CComAutoCriticalSection &rCS) 
				: m_rCS (rCS) { m_rCS.Lock(); }
			~CLockCS (void) { m_rCS.Unlock(); }
	};

public:
		CActiveMessages (void) {}
		~CActiveMessages (void) {}

	bool Insert (UINT uiMsg)
		{ 
		CLockCS lock(m_cs); 
		// 'insert' schl‰gt fehl, wenn Message bereits existiert
		pair<CHandledMap::iterator, bool> p = m_data.insert(uiMsg); 

			return p.second;
		}
	bool Delete (UINT uiMsg)
		{ 
		CLockCS lock(m_cs); 
		
		// genau _ein_ Element muﬂ entfernt werden
			return (1 == m_data.erase (uiMsg)) ? true : false; 
		}
};
#endif // _REJECT_MESSAGES

///////////////////////////////////////////////////////////////////////////////
// HashTabelle, die die Anforderungen enth‰lt 
class ExtensionList;

class QueryNotifyHash : 
	public CMessageMap 
{
private:
	ExtensionList &m_rEL;
	Point m_ptLastMousePos;			// letzte MousePos
	HPROJECT m_hPrCtx;				// Kontext der aktuellen Message
#if defined(_GUARD_NOTIFICATIONS)
	typedef list<CMessageGuard *> CMessageGuardList;
	CMessageGuardList m_lstMsgList;
#endif // defined(_GUARD_NOTIFICATIONS)
	typedef set<UINT> CCriticalMsgSet;
	CCriticalMsgSet m_setCritMsg;	// Menge der 'kritischen' Notifikationen
	
#if defined(_REJECT_MESSAGES)
	CActiveMessages m_Native;		// derzeit behandelte DEX-Messages
	CActiveMessages m_System;		// derzeit behandelte WindowsMessages
#endif // _REJECT_MESSAGES

protected:
	void UserDelete (void *);

public:
		QueryNotifyHash (ExtensionList &rEL);
		~QueryNotifyHash (void);

	LRESULT Dispatch (HWND hWnd, Event &);		// Message an Extensions verteilen
	LRESULT Dispatch (HPROJECT hPr, UINT wMsg, WPARAM w, LPARAM l);	// Message an Extensions verteilen
	bool RegisterQNFY (Extension &rExt, HWND hWnd, LPARAM Msg);		// neue Anforderung speichern
	bool UnRegisterQNFY (Extension &rExt, LPARAM Msg);	// Anforderung lˆschen
	bool UnRegisterAllQNFYs (HDEX hDex);		// alle Anforderungen dieser Extension lˆschen

	bool MsgIsCritical (UINT uiMsg)
	{
		return (m_setCritMsg.find(uiMsg) != m_setCritMsg.end()) ? true : false;
	}

#if defined(_DEBUG)
	bool ExtHasRegisteredNfys (HDEX hDex);
	bool ExtHasRegisteredNfy (HDEX hDex, LPARAM lMsg);
#endif // defined(_DEBUG)

#if defined(_GUARD_NOTIFICATIONS)
// die Folgenden Funktionen dienen lediglich dem Feststellen der 'kritischen'
// Notifikationen
	void RegisterActiveMsgHandler (CMessageGuard *pList)
	{
		m_lstMsgList.push_back(pList);
	}
	void UnRegisterActiveMsgHandler (CMessageGuard *pList)
	{
		for (CMessageGuardList::iterator it = m_lstMsgList.begin(); it != m_lstMsgList.end(); ++it)
		{
			if (*it == pList) {
				m_lstMsgList.erase(it);
				return;
			}
		}
		_ASSERTE(FALSE);		// Liste nicht wiedergefunden
	}

// hier passierts: alle aktiven Messages als Assertion melden (m_lstMsgList enth‰lt nur die
// CMessageGuard's f¸r nicht als kritisch bekannte Messages)
	void UnRegisterQNFY(UINT uiMsgToDel)
	{
		for (CMessageGuardList::iterator it = m_lstMsgList.begin(); 
			 it != m_lstMsgList.end(); ++it)
		{
			if ((*it) -> GetMsgId() == uiMsgToDel) {
			// nur um den Debugger hier anhalten zu lassen
				_ASSERTE(MsgIsCritical(uiMsgToDel));	
			}
		}
	}
#else
	void UnRegisterQNFY(UINT uiMsgToDel) {}
#endif // defined(_GUARD_NOTIFICATIONS)

#if defined(_REJECT_MESSAGES)
	bool InsertNative (UINT uiMsg) { return m_Native.Insert (uiMsg); }
	bool DeleteNative (UINT uiMsg) { return m_Native.Delete (uiMsg); }
	bool InsertSystem (UINT uiMsg) { return m_System.Insert (uiMsg); }
	bool DeleteSystem (UINT uiMsg) { return m_System.Delete (uiMsg); }
#endif // _REJECT_MESSAGES

	LPARAM SetShownCoords (LPARAM lParam)
	{
	LPARAM lResult = MAKELONG(m_ptLastMousePos.X(), m_ptLastMousePos.Y());

		m_ptLastMousePos = Point (LOWORD(lParam), HIWORD(lParam));
		return lResult;
	}
	HPROJECT GetContextHandle() { return m_hPrCtx; }
};

#if defined(_REJECT_MESSAGES)
///////////////////////////////////////////////////////////////////////////////
//
inline CMessageToHandle::CMessageToHandle (
	QueryNotifyHash &rQ, UINT uiMsg, bool fIsDexMsg)
		: m_rQ(rQ), m_uiMsg(uiMsg), m_fIsDexMsg(fIsDexMsg)
{
	if (fIsDexMsg)
		m_fToHandle = rQ.InsertNative(uiMsg);
	else
		m_fToHandle = rQ.InsertSystem(uiMsg);
}

inline CMessageToHandle::~CMessageToHandle (void)
{
	if (m_fToHandle) {
		if (m_fIsDexMsg)
			m_rQ.DeleteNative(m_uiMsg);
		else
			m_rQ.DeleteSystem(m_uiMsg);
	}
}
#endif // _REJECT_MESSAGES

///////////////////////////////////////////////////////////////////////////////
// Messagerouting 
inline LRESULT ExtDirisWindow::DispatchThroughXtensions (HWND hWnd, Event &e)
		{ LRESULT R = 0L ; if (m_pQNH) R = m_pQNH -> Dispatch(hWnd, e); return R; }

///////////////////////////////////////////////////////////////////////////////
// inline Funktionen, die erst hier definiert werden kˆnnen
#if defined(_GUARD_NOTIFICATIONS)
inline CMessageGuard::CMessageGuard (UINT uiMsg, QueryNotifyHash *pBack) :
	m_uiMsg(uiMsg), m_pBack(pBack)
{
	m_pBack -> RegisterActiveMsgHandler (this);
}

inline CMessageGuard::~CMessageGuard()
{
	m_pBack -> UnRegisterActiveMsgHandler (this);
}
#endif // defined(_GUARD_NOTIFICATIONS)

#endif // _EXTQNFY_HXX
