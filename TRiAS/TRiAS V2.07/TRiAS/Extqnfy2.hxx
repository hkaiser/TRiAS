// Klassendefinitionen fuer die Messageverwaltung von QueryNotify Anforderungen
// File: EXTQNFY2.HXX

#if !defined(_EXTQNFY_HXX)
#define _EXTQNFY_HXX

// STL-related stuff ----------------------------------------------------------
#define NOMINMAX
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)		// debug info truncated
#include <ospace/std/map>

///////////////////////////////////////////////////////////////////////////////
// verwendete multimap
class QNFY;
typedef multimap<UINT, QNFY, less<UINT> > CMessageMap;

///////////////////////////////////////////////////////////////////////////////
// Klasse, die in der multimap<> drinhängt 
class QNFY 
{
private:
	HWND m_hWnd;	// FensterHandle
	bool m_fDexMsg;	// WindowsMessage oder interne Message
	Extension *m_pExt;
	HDEX m_hDex;	// workaround für LöschFehler, der sporadisch auftritt

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
// Klassen, die verhindern, daß identische Messages verschachtelt behandelt 
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
		// 'insert' schlägt fehl, wenn Message bereits existiert
		pair<CHandledMap::iterator, bool> p = m_data.insert(uiMsg); 

			return p.second;
		}
	bool Delete (UINT uiMsg)
		{ 
		CLockCS lock(m_cs); 
		
		// genau _ein_ Element muß entfernt werden
			return (1 == m_data.erase (uiMsg)) ? true : false; 
		}
};
#endif // _REJECT_MESSAGES

///////////////////////////////////////////////////////////////////////////////
// HashTabelle, die die Anforderungen enthält 
class ExtensionList;

class QueryNotifyHash : 
	public CMessageMap 
{
private:
	ExtensionList &m_rEL;
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
	LRESULT Dispatch (UINT wMsg, WPARAM w, LPARAM l);	// Message an Extensions verteilen
	bool RegisterQNFY (Extension &rExt, HWND hWnd, LPARAM Msg);	// neue Anforderung speichern
	bool UnRegisterQNFY (Extension &rExt, LPARAM Msg);	// Anforderung löschen
	bool UnRegisterAllQNFYs (HDEX hDex);
				// alle Anforderungen dieser Extension löschen

#if defined(_DEBUG)
	bool ExtHasRegisteredNfys (HDEX hDex);
	bool ExtHasRegisteredNfy (HDEX hDex, LPARAM lMsg);
#endif // _DEBUG

#if defined(_REJECT_MESSAGES)
	bool InsertNative (UINT uiMsg) { return m_Native.Insert (uiMsg); }
	bool DeleteNative (UINT uiMsg) { return m_Native.Delete (uiMsg); }
	bool InsertSystem (UINT uiMsg) { return m_System.Insert (uiMsg); }
	bool DeleteSystem (UINT uiMsg) { return m_System.Delete (uiMsg); }
#endif // _REJECT_MESSAGES
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

#endif // _EXTQNFY_HXX
