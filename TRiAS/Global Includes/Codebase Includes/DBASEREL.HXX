// Klasse fuer den Zugriff auf SlaveDB's
// File: DBASEREL.HXX


#if !defined(_DBASEREL_HXX)
#define _DBASEREL_HXX

#include <strdup.hxx>

class DBaseRel {
private:
	char *_pDBName;
	char *_pFName;

public:
		DBaseRel (const char *pDBName, const char *pFName) 
		{
			_pDBName = StrDup (pDBName, RC_ctDBaseRel);
			_pFName = StrDup (pFName, RC_ctDBaseRel);
		}
		~DBaseRel (void)
		{
			DELETE_VEC (_pDBName);
			DELETE_VEC (_pFName);
		}

	char * &GetDBName (void) const { return (char *&)_pDBName; }
	char * &GetFieldName (void) const { return (char *&)_pFName; }
	void OemToAnsi (void)
	{
		:: OemToAnsi (_pDBName, _pDBName);
		:: OemToAnsi (_pFName, _pFName);
	}
};


#endif // _DBASEREL_HXX
