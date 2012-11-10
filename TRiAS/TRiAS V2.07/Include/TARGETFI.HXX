// Iteratorklasse fuer Finden aller Targetdateien fuer eine KeyDatei ----------
// File: TARGETFI.HXX

#if !defined(_TARGETFI_HXX)
#define _TARGETFI_HXX

class CTargetFileIterator {
protected:
	short m_iKeyFile;
	short m_iActIndex;
	CDBDict &m_rDBD;

public:
// Konstruktor/Destruktor
		CTargetFileIterator (CDBDict &DBD);
		~CTargetFileIterator (void) {}

	BOOL Init (short iKeyIndex);
	
	short GetFirstTargetFile (void);
	short GetNextTargetFile (void);
	short iKeyIndex (void) { return m_iActIndex; }
};


#endif // _TARGETFI_HXX
