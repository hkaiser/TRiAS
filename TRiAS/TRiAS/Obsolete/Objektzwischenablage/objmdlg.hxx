// Eingabe eines neuen Merkmalswertes -----------------------------------------
// File: OBJMDLG.HXX

#if !defined(_OBJMDLG_HXX)
#define _OBJMDLG_HXX


class ObjMerkmalDlg : public DialogWindow {
private:
	MultiLineEdit MWert;

protected:
	void ButtonClick (ControlEvt);

public:
		ObjMerkmalDlg (pWindow, ResourceFile *, char *, char *);
		~ObjMerkmalDlg (void);

	char *GetNewText (char *pBuffer, short iMaxLen);
};


#endif //_OBJMDLG_HXX

