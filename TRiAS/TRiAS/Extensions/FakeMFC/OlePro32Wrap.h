///////////////////////////////////////////////////////////////////////////////
// Wrapper für Funktionen aus der OlePro32.dll

#if !defined(_OLEPRO32WRAP_H)
#define _OLEPRO32WRAP_H

#include <dllbindx.hxx>

class COlePro32Bind :
	public CDllBindX 
{
private:
	typedef HRESULT (STDAPICALLTYPE *OLECREATEPICTUREINDIRECTPROC)(LPPICTDESC lpPictDesc, REFIID riid, BOOL fOwn, LPVOID FAR* lplpvObj);

	OLECREATEPICTUREINDIRECTPROC m_pOleCreatePictureIndirect;
	bool m_fIsValid;

public:
		COlePro32Bind (void);

	HRESULT OleCreatePictureIndirect (LPPICTDESC lpPictDesc, REFIID riid, BOOL fOwn, LPVOID FAR* lplpvObj);
	bool IsValid (void) { return m_fIsValid; }
};

inline
COlePro32Bind::COlePro32Bind (void)
	: CDllBindX (TEXT("OLEPRO32.DLL")), m_fIsValid(false)
{
	if (NULL == hLib()) return;		// Initialisierungs-Fehler

	m_pOleCreatePictureIndirect = (OLECREATEPICTUREINDIRECTPROC)GetProcAddress (TEXT("OleCreatePictureIndirect"));;
	if (NULL != m_pOleCreatePictureIndirect)
	{
		m_fIsValid = true;
	}
}

inline
HRESULT COlePro32Bind::OleCreatePictureIndirect (LPPICTDESC lpPictDesc, REFIID riid, BOOL fOwn, LPVOID FAR* lplpvObj)
{
	TX_ASSERT(NULL != m_pOleCreatePictureIndirect);
	return m_pOleCreatePictureIndirect (lpPictDesc, riid, fOwn, lplpvObj);
}

#endif // _OLEPRO32WRAP_H
