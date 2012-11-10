// EditControl, welches RO/nicht RO sein kann ---------------------------------
// File: EDITRO.HXX

#if !defined(_EDITRO_HXX)
#define _EDITRO_HXX

#if defined(WIN32)
class CEditCondRO : public ControlWindow {
private:
	bool m_fRO;			// derzeit ReadOnly ?

protected:
	void KeyDown (KeyEvt e);	// evtl. abblocken

public:
		CEditCondRO (pDialogWindow p, ResID r);
		~CEditCondRO (void);

	bool isRO (void) { return m_fRO; }
	void SetRO (bool fRO) 
	{ 
		m_fRO = fRO ? true : false; 
		SendMessage (GetControl()->Handle(), EM_SETREADONLY, m_fRO, 0L);
	}

	void SetTextLimit (uint nchars);
	void SetText (const char *pcBuff);
	void GetText (char *pBuff, uint uiLen);
	int GetTextLen (void);
	bool isModified (void);
	void SetModified (bool fModified);

	bool FInit (void);
};
#else
typedef MultiLineEdit CEditCondRO;
#endif // WIN32

#endif // _EDITRO_HXX
