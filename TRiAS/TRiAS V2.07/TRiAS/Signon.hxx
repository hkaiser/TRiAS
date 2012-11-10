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
private:
	CBildObjekt m_bmpSignOn;	// Bildchen
	Font *m_pFont;			// SpezialFont1
	Font *m_pFontP;			// SpezialFont2
	char *m_pPersonal;
	bool m_fNativeLogo;		// original TRiAS-Logo

protected:
	void Expose (ExposeEvt);

public:
		CSignOnDlg256 (pWindow pW, HINSTANCE hInst, bool fModal = true);
		~CSignOnDlg256 (void);

	bool FInit (void);
	bool Pling (HDC);
	void PlaySound16 (void);
	
	bool WriteBmpToDisk (char *pFile, BYTE *pBmp, DWORD dwSize);
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

