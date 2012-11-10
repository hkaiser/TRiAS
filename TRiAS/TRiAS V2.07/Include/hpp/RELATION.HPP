// Klasse fuer den Zugriff auf SlaveDB's
// File: DBASEREL.HPP


#if !defined(_DBASEREL_HPP)
#define _DBASEREL_HPP         

const char RelSep = ':';		// Separator für Alias- und Feldname
const char RelatSep [] = ":";
  
class DBaseRel {
private:
	CString _pDBName;
	CString _pFName;

public:
		DBaseRel (const char *pDBName, const char *pFName) 
		{
			_pDBName = pDBName; 
			_pFName = pFName;     
		}
		DBaseRel (CString &FullCon)
		{                  
			short sFind = FullCon.Find (RelSep);
			if (sFind > 0)
			{
				_pDBName = FullCon.Left (sFind);
				_pFName = FullCon.Right (FullCon.GetLength () - ++sFind);
			}				
		} 		
		~DBaseRel (void)
		{
			// nothing to do
		}

	const char *GetDBName (void) { return _pDBName; }
	const char *GetFieldName (void) { return _pFName; }

	void OemToAnsi (void)
	{
		_pDBName.OemToAnsi ();
		_pFName.OemToAnsi ();
	}
};

#endif // _DBASEREL_HPP
