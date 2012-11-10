// SatzKontext, der einen gelesenen Satz mit aktivem Feld repräsentiert
// File: KONSSATZ.HXX

#if !defined(_KONSSATZ_HXX)
#define _KONSSATZ_HXX

#if _TRiAS_VER < 0x0400

#include <dbaddr.hxx>

class CKonsistenzTestKontext;

class CSatzKontext {
protected:
	CDBAddress m_rDBA;
	char *m_pSatz;
	long *m_pFeld;
	CKonsistenzTestKontext &m_rKTK;

	ErrCode m_RC;

public:
		CSatzKontext (short iFileNo, long lRecNo, 
			size_t iSize, CKonsistenzTestKontext &rKTK);
		virtual ~CSatzKontext (void);

	CDBAddress &GetDBA (void) const { return (CDBAddress &)m_rDBA; }
	void SetField (long *pF) { m_pFeld = pF; }
	long *GetField (void) { return m_pFeld; }
	char *GetData (void) const { return m_pSatz; }

virtual ErrCode KRead (void);
virtual ErrCode KWrite (void);

	ErrCode RC (void) { return m_RC; }

	short &FileNo (void) { return m_rDBA.FileNo(); }
	long &RecNo (void) { return m_rDBA.RecNo(); }

friend ERRHANDLERFUNC ERInvAddr;
friend ERRHANDLERFUNC ERDelRecord;
};

class COBLKontext : public CSatzKontext {
public:
		COBLKontext (CKonsistenzTestKontext &rKTK);

	operator obl &(void) const { return *(struct obl *)m_pSatz; }
};


class CSICHTKontext : public CSatzKontext {
public:
		CSICHTKontext (CKonsistenzTestKontext &rKTK);

	operator sicht &(void) const { return *(struct sicht *)m_pSatz; }
};


class CPOLKontext : public CSatzKontext {
public:
		CPOLKontext (long lRecNo, CKonsistenzTestKontext &rKTK);

	operator pol &(void) const { return *(struct pol *)m_pSatz; }

friend ERRHANDLERFUNC ERBadZVGO;
friend ERRHANDLERFUNC ERBadZKFK;
};

class CIDLKontext : public CSatzKontext {
public:
		CIDLKontext (long lRecNo, CKonsistenzTestKontext &rKTK);
		CIDLKontext (CKonsistenzTestKontext &rKTK);

	operator idl &(void) const { return *(struct idl *)m_pSatz; }

friend ERRHANDLERFUNC ERBadZVIO;
};

class CMKLKontext : public CSatzKontext {
public:
		CMKLKontext (long lRecNo, CKonsistenzTestKontext &rKTK);

	operator mkl &(void) { return *(struct mkl *)m_pSatz; }

friend ERRHANDLERFUNC ERBadZVOM;
friend ERRHANDLERFUNC ERBadZVMO;
friend ERRHANDLERFUNC ERBadZDBT;
friend ERRHANDLERFUNC ERBadZNMI;
};

class CVerbKontext : public CSatzKontext {
public:
		CVerbKontext (short iFileNo, long lRecNo, CKonsistenzTestKontext &rKTK);
};

#endif // _TRiAS_VER < 0x0400

#endif // _KONSSATZ_HXX
