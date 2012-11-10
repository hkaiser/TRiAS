// Definition von Teilprojekten ------------------------------------------------------
// File: TEPRODEF.HXX

#if !defined(_TEPRODEF_HXX)
#define _TEPRODEF_HXX

// Definieren von Teilprojekten ---------------------
class TProjectDefine : public DialogWindow {
private:
	

	FixedText _TPDirectory;
//	FixedText _TProjectKey;
	TxtEdit _TProjectKey;

	ListBox _TProjects;
	
	PushButton OKButton, CancelButton, _TPDefine, _TPDelete,_TPStore,_TPNew;
	ResourceFile &_RF;

	pWindow _pW;
	char *_pInput;
	char *_pRefTP;
	char *_pKey;
	char *_pProject;
	char *_pLastKey;
	char *_pLastProject;
	char *_pLocDir;
	short _iLevel;
	short _isModified;
	short _isMenu;
	short _isNewTree;		//Neuer TP-Baum
	PROJTree *_pPROJ;
	TPRJTree *_pTPRJ;
	MMenuTree *_pMenu;

// KK010329
	short _isOR;	// Ruf aus ORF (TRUE) oder HM

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);
	void _XTENSN_EXPORT ListBoxSel (ControlEvt e);



public:
		TProjectDefine (pWindow pW, uint res, ResourceFile &RF, char *pProject, PROJTree *pPROJ, MMenuTree *pMenu, char *pInput = NULL );
		~TProjectDefine (void);

//Memberfunktionen
	Bool FillTProjectList (void);
	Bool LoadTProjectList (void);
	Bool StoreNewInformation( void);
	short &isModifiedProFile ( void ) { return _isModified; };
	char *GetNewKey ( void ) { return _pInput; } ;
	char *RefTP ( void ) { return _pRefTP; } ;
};    
//-------------------------------------------------------------
// Modifizieren von Teilprojekten ---------------------
class TProjectMod : public DialogWindow {
private:

	FixedText _TPIni;
	FixedText _TPPfad;
	FixedText _TPKey;
	FixedText _TPDir;

	char *_pINI;
	char *_pPfad;
	char *_pKey;

	PushButton OKButton, CancelButton,DelButton,_TPDefine;
	ResourceFile *_pResTarget;	// evtl. ResourceFile

	pWindow _pW;

protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);



public:
		TProjectMod (pWindow pW, uint res, ResourceFile *pResTarget, char *pIni, char *pPfad, char *pKey);
		~TProjectMod (void);

//Memberfunktionen
		char * TProjectNewPfad (void) { return _pPfad;};
		char * TProjectKey (void) { return _pKey;};
};    

#endif
