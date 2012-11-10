// VisInfo rücksetzen ---------------------------------------------------------
// File: RSETHIDE.HXX

#if !defined(_RSETHIDE_HXX)
#define _RSETHIDE_HXX

extern "C" 
BOOL PASCAL _XTENSN_EXPORT ResetShowInfoIdent (long lIdent, BOOL, void *pPtr);

class CResetShowInfoDlg : public DialogWindow {
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
	
	bool RemoveIdentShowInfo (void);

public:
		CResetShowInfoDlg (pWindow pW, ResourceFile *pRF, long lMCode);
		~CResetShowInfoDlg (void);

	bool Init (void);

};

extern "C" BOOL PASCAL _XTENSN_EXPORT ResetShowInfoIdentEx (long lIdent, DWORD, void *pPtr);
extern "C" BOOL PASCAL _XTENSN_EXPORT ObjHideVisInfoEx (long lONr, DWORD, void *pData);

#endif // _RSETHIDE_HXX

