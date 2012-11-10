// SignOnBildchen fuer TRIAS --------------------------------------------------
// File: SIGNON.HXX

#if !defined(_SIGNON_HXX)
#define _SIGNON_HXX

#define NOSIGNONCODE

class CSignOnDlg : 
	public DialogWindow 
{
private:
	char *m_pSnd;			// wave-resource
	unsigned int m_fGlobalFree : 1;
	unsigned int m_fModal : 1;

protected:
	HINSTANCE m_hInst;

	void MouseButtonDn (MouseEvt);
	void KeyDown (KeyEvt);

public:
		CSignOnDlg (pWindow pW, HINSTANCE hInst, uint resID, bool fModal);
	virtual ~CSignOnDlg (void);

static CSignOnDlg *CreateInstance (pWindow pW, HINSTANCE hInst, bool fModal = false);

virtual bool FInit (void) = 0;
virtual	void PlaySound16 (void) = 0;

	void PlaySound (void);

inline bool IsModal (void) { return m_fModal ? true : false; }
};

class CSignOnDlg256 : 
	public CSignOnDlg 
{
protected:
	CBildObjekt m_bmpSignOn;	// Bildchen
	pFont m_pFont;			// SpezialFont1
	pFont m_pFontP;			// SpezialFont2
	char *m_pPersonal;
	bool m_fNativeLogo;		// original TRiAS-Logo
	UINT m_uiResIDBmp;

	void Expose (ExposeEvt);

public:
		CSignOnDlg256 (pWindow pW, HINSTANCE hInst, bool fModal = true);
		~CSignOnDlg256 (void);

	bool FInit (void);
	bool Pling (HDC);
	void PlaySound16 (void);
	
	bool WriteBmpToDisk (char *pFile, BYTE *pBmp, DWORD dwSize);
};

// das gleiche noch mal, aber für InterTRiAS
class CSignOnDlg256_InterTRiAS :
	public CSignOnDlg256
{
public:
		CSignOnDlg256_InterTRiAS (pWindow pW, HINSTANCE hInst, bool fModal = true)
			: CSignOnDlg256 (pW, hInst, fModal) 
		{
			m_uiResIDBmp = IDBMP_STARTUP_T;
			m_pFontC = NULL;
		}
		~CSignOnDlg256_InterTRiAS (void) 
		{
			if (m_pFontC) delete m_pFontC;
		}

protected:
	pFont m_pFontC;			// SpezialFont3
	
	void Expose (ExposeEvt);

public:
	bool FInit (void);
};

class CSignOnDlg16 : 
	public CSignOnDlg 
{	// nur 16 Farben verfügbar
private:
	BitmapBox m_bmpLogo;
	FixedText m_ftRegName;
	FixedText m_ftRegCompany;
	FixedText m_ftRegNr;
			
public:
		CSignOnDlg16 (pWindow pW, HINSTANCE hInst, bool fModal = true);
		~CSignOnDlg16 (void);

	bool FInit (void);
	void PlaySound16 (void);
};

#endif // _SIGNON_HXX

