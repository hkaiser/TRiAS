// Rahmen, in dem ein Bildchen gezeichnet werden soll --------------------------
// File: CPICBOX.HXX

#if !defined(_CPICBOX_HXX)
#define _CPICBOX_HXX

class CPictureBox : public ControlWindow {
private:
	CTortenVisModule &m_rVM;
	short m_iType;
	char *m_pPalName;	// PaletteName

	short m_iNums;		// Anzahl der Beispielsektoren
	long *m_pSectors;	// BeispielSektoren
	char **m_ppMWerte;	// BeispielTexte
	
protected:
	void Expose (ExposeEvt e);
	
public:
		CPictureBox (pDialogWindow pDW, ResID uiID, CTortenVisModule *);
		~CPictureBox (void);
		
	BOOL FInit (short iType, char *pPalName, short iNum, 
		    long *pWerte, char **ppMWerte);
};


#endif // _CPICBOX_HXX
