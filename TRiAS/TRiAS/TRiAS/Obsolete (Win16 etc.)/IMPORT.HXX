// Dialogfenster 'Import aus anderen Formaten' --------------------------------
// File: IMPORT.HXX

#if !defined(_IMPORT_HXX)
#define _IMPORT_HXX

class CImportParamDlg : public DialogWindow {
private:
	ComboBox m_cbFormats;	// Eingabeformate
	ComboBox m_cbCoords;	// Koordinatensysteme
	PushButton m_pbHelp;	// HilfeKnopf

	char *m_pFormat;
	char *m_pCoordSys;
	
	GeoDB &m_rDB;		// aktuelle GeoDB
		
protected:
	void ButtonClick (ControlEvt e);

	short FillCBox (unsigned int uiRes, ComboBox &rCB, char *pInit = NULL);
	char *ReadDesc (unsigned int uiRes, ComboBox &rCB);
			
public:
		CImportParamDlg (pWindow, GeoDB &);
		~CImportParamDlg (void);
		
	BOOL Init (char *pInitCTF);
	
	char *GetFormatDesc (void) const { return m_pFormat; }
	char *GetCoordSysDesc (void) const { return m_pCoordSys; }
	void GenerateCoordSysEntries (HeaderEntry &rHE);
};


#endif // _IMPORT_HXX

