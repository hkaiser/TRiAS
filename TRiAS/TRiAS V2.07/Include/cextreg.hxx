// Registrieren und Unregistrieren einer TRiAS-Erweiterung --------------------
// File: CEXTREG.HXX

#if !defined(_CEXTREG_HXX)
#define _CEXTREG_HXX

#include <VersionWrap.h>

class CExtReg {
protected:
	string m_strPathName;
	CVersionBind &m_rVer;

public:
	_TRIAS03_ENTRY CExtReg (CVersionBind &rVer, string &PathName);
	_TRIAS03_ENTRY ~CExtReg (void);
		
_TRIAS03_ENTRY bool Register (void);
_TRIAS03_ENTRY bool Unregister (void);

_TRIAS03_ENTRY bool SupportsSelfRegister (void);

	const string &GetPath() const { return m_strPathName; }
};
	
#endif // _CEXTREG_HXX
