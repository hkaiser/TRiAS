// Klasse für das automatische Ausschalten der EierUhr ------------------------
// File: EIERUHR.HXX

#if !defined(_EIERUHR_HXX)
#define _EIERUHR_HXX

class CEierUhr {
private:
	Pointer *m_pOldPtr;
	Window *m_pWnd;
	Pointer m_Wait;
	short m_fHidden;
		
public:
	inline CEierUhr (Window *pWnd);
	inline CEierUhr (Window *pWnd, LPCSTR pcCursor);
	inline ~CEierUhr (void);

inline	void Hide (void);
};

inline CEierUhr :: CEierUhr (Window *pWnd)
		 : m_pWnd (pWnd),
		   m_Wait (HourGlass),
		   m_fHidden (false)
{
	m_pOldPtr = m_pWnd ? m_pWnd -> ChangePointer (&m_Wait) : NULL;
	m_Wait.Show();
}
inline CEierUhr::CEierUhr (Window *pWnd, LPCSTR pcCursor)
		 : m_pWnd (pWnd),
		   m_Wait (pcCursor, HourGlass),
		   m_fHidden (false)
{
	m_pOldPtr = m_pWnd ? m_pWnd -> ChangePointer (&m_Wait) : NULL;
	m_Wait.Show();
}
inline CEierUhr :: ~CEierUhr (void)
{
	if (!m_fHidden) {
		if (m_pWnd) m_pWnd -> ChangePointer (m_pOldPtr);
		if (m_pOldPtr) m_pOldPtr -> Show();
	}
}
inline void CEierUhr :: Hide (void) 
{
	if (!m_fHidden) {
		if (m_pWnd) m_pWnd -> ChangePointer (m_pOldPtr);
		if (m_pOldPtr) m_pOldPtr -> Show();
		m_fHidden = true;
	}
}

#endif // _EIERUHR_HXX
