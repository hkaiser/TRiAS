// Dialog -------------------------------------------------------------
// File: PolygisDLG.HXX

#if !defined(_POLYGISDLG_HXX)
#define _POLYGISDLG_HXX

//////////////////////////////////////////////////////////////////////////////////////

class CConfigDlg : public DialogWindow {

private:
	FixedText m_OberThemenName;
	FixedText m_ThemenName;
	FixedText m_GruppenName;

	char *_pOberThema;
	char *_pThema;
	char *_pGruppe;

protected:
	void ButtonClick (ControlEvt);


public:
		CConfigDlg (pWindow, char *, char *, char *);
		~CConfigDlg (void);

		char * GetOberThema(void) { return _pOberThema; }
		char * GetThema(void) { return _pThema; }
		char * GetGruppe(void) { return _pGruppe; }

};


/////////////////////////////////////////////////////////////////////////////////////
#endif // _POLYGISDLG_HXX
