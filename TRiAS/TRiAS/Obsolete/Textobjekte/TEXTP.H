
#ifndef _TEXTP_H
#define _TEXTP_H


class CTextPro : public IMaintainTexts
{
private:
	DWORD m_dwRefCnt;
	CTextExt *m_pTextExt;		// Rückverweis
	CHelper *m_pHelper;
protected:
public:
		CTextPro (CTextExt *pTextExt, CHelper *pHelper);
		~CTextPro (void);
		
// Standard OLE stuff.
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID *ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	STDMETHOD_(bool, GenerateText) (THIS_ LONG lONr, ULONG ulMCode, DWORD dwFlags, LONG *plTxtObjNr);
	STDMETHOD_(bool, GenerateText) (THIS_ LONG lONr, CString sText, DWORD dwFlags, LONG *plTxtObjNr);
	
	STDMETHOD_(bool, GenerateTexts) (THIS_ ULONG ulIdent, ULONG ulMCode, short iObjTyp, DWORD dwFlags);
	STDMETHOD_(bool, GenerateTexts) (THIS_ ULONG ulIdent, CString sText, short iObjTyp, DWORD dwFlags);

	STDMETHOD_(bool, UnlinkText) (THIS_ LONG lONr, DWORD dwFlags);
	STDMETHOD_(bool, UnlinkTexts) (THIS_ ULONG ulIdent, short iOTyp, DWORD dwFlags);
};

BOOL FlagTest(SEnObj stEnObj, DWORD dwFlags);
BOOL FlagTest(BOOL bLoesch, DWORD dwFlags);

#endif // _TEXTP_H
