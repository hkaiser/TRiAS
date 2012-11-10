// Behandlung der Eintraege in der Projekt-INI fuer das Druck-Layout ----------
// File: PRNTPROF.HXX

#if !defined(_PRNTPROF_HXX)
#define _PRNTPROF_HXX

class PrintProfile : public ProFile {
protected:
	char *m_pRS;
	char *m_pInBuff;
	char *m_pProfPath;
		
	short GetInt (unsigned int resID, short iDefault = 0);
	void SetInt (unsigned int resID, short iVal);
	
public:
		PrintProfile (char *pUser);
		~PrintProfile (void);

	bool IsValid (void);

// SeitenR‰nder
	bool GetRand (Rectangle &Rc);
	void SetRand (Rectangle &Rc);

// Rahmen
	short GetRahmen (void);
	void SetRahmen (short iTyp);

// Legende
	bool GetLegende (void);
	void SetLegende (bool fPaint);
	bool GetLegendOnly (void);
	void SetLegendOnly (bool fPaint);

// Maﬂstab
	bool GetMasstab (void);	
	void SetMasstab (bool fPaint);

// ‹berschrift
	bool GetHeadLine (char *pBuffer, short iLen);
	void SetHeadLine (bool fPaint, char *pBuffer);

// Ausschnitt
	short GetAusschnitt (KoOrd &Li, KoOrd &Ob, KoOrd &Re, KoOrd &Un, long &M);	
	void SetAusschnitt (long Li, long Ob, long Re, long Un);
	void SetAusschnitt (long Li, long Ob, long M);

friend char *GetProjectProfile (void);
};


#endif // _PRNTPROF_HXX
