// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/11/1998 08:33:16 PM
//
// @doc
// @module SignOnDlg.h | SignOnBildchen fuer TRIAS

#if !defined(_SIGNONDLG_H__1C4ADCB5_912B_11D2_9F03_006008447800__INCLUDED_)
#define _SIGNONDLG_H__1C4ADCB5_912B_11D2_9F03_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <EsnecilExt.h>

///////////////////////////////////////////////////////////////////////////////
// 
class CSignOnDlg : 
	public DialogWindow 
{
private:
#if _TRiAS_VER < 0x0510
	BYTE *m_pSnd;			// wave-resource
#endif
	bool m_fModal;

protected:
	HINSTANCE m_hInst;

	void MouseButtonDn (MouseEvt);
	void KeyDown (KeyEvt);

public:
	CSignOnDlg (pWindow pW, HINSTANCE hInst, uint resID, bool fModal);
	virtual ~CSignOnDlg (void);

static CSignOnDlg *CreateInstance (pWindow pW, HINSTANCE hInst, bool fModal = false);

virtual bool FInit (void) = 0;
virtual void Show (ShowState = Normal);

#if _TRiAS_VER < 0x0510
	void PlaySound (void);
#endif

inline bool IsModal (void) { return m_fModal ? true : false; }
};

class CSignOnDlg256 : 
	public CSignOnDlg 
{
private:
	CEsnecilExt m_Lic;

protected:
	CBildObjekt m_bmpSignOn;	// Bildchen
	pFont m_pFont;				// SpezialFont1
	pFont m_pFontP;				// SpezialFont2
	UINT m_uiResIDBmp;
	bool m_fNativeLogo;			// original TRiAS-Logo

	void Expose (ExposeEvt);
	os_string GetLicString();

public:
		CSignOnDlg256 (pWindow pW, HINSTANCE hInst, bool fModal = true);
		~CSignOnDlg256 (void);

	bool FInit (void);
	bool Pling (HDC hDC, int iX, int iY, COLORREF crPling);
	
	bool WriteBmpToDisk (char *pFile, BYTE *pBmp, DWORD dwSize);
};

#endif // !defined(_SIGNONDLG_H__1C4ADCB5_912B_11D2_9F03_006008447800__INCLUDED_)
