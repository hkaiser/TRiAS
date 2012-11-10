// VisInfo rücksetzen ---------------------------------------------------------
// File: RESETVIS.HXX

#if !defined(_RESETVIS_HXX)
#define _RESETVIS_HXX

extern "C" 
BOOL PASCAL _XTENSN_EXPORT ResetVisInfoIdent (long lIdent, BOOL, void *pPtr);

class CResetVisInfoDlg : public DialogWindow {
private:
#if !defined(WIN32)
	PushButton m_pbHelpButton;
#endif //!WIN32
	PushButton m_pbOKButton;
	MultiSelListBox m_lbIdents;
	FixedText m_ftToDo;

	long m_lMCode;
	char *m_pInBuff;
		
protected:
	void ButtonClick (ControlEvt);
	
	bool RemoveIdentVisInfo (void);

public:
		CResetVisInfoDlg (pWindow pW, ResourceFile *pRF, long lMCode);
		~CResetVisInfoDlg (void);

	bool Init (void);

friend BOOL PASCAL _XTENSN_EXPORT ResetVisInfoIdent (long lIdent, BOOL, void *pPtr);
friend BOOL PASCAL _XTENSN_EXPORT ObjResetVisInfo (long lONr, BOOL, void *pData);
};


#endif // _RESETVIS_HXX

