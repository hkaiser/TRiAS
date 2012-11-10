// Registrieren und Unregistrieren einer TRiAS-Erweiterung --------------------
// File: CEXTREG.HXX

#if !defined(_CEXTREG_HXX)
#define _CEXTREG_HXX

#include <ospace/file/path.h>
#include <VersionWrap.h>

class CExtReg 
{
protected:
	os_path m_strPathName;
	string m_strFileVersion;
	CVersionBind &m_rVer;
	int m_fh;

public:
	_TRIAS03_ENTRY CExtReg (CVersionBind &rVer, string &PathName, int fh = HFILE_ERROR);
	_TRIAS03_ENTRY ~CExtReg (void);
		
_TRIAS03_ENTRY bool Register (void);
_TRIAS03_ENTRY bool Unregister (void);

_TRIAS03_ENTRY bool SupportsSelfRegister (void);

	const string &GetPath() const { return m_strPathName; }
};
	
#endif // _CEXTREG_HXX
