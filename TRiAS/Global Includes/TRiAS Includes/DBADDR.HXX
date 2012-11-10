// Datenbankadresse (als Klasse)
// File: DBADDR.HXX

#if !defined(_DBADDR_HXX)
#define _DBADDR_HXX

typedef struct db_addr DB_ADDR;

class CDBAddress {
private:
	DB_ADDR m_dba;

public:
// Konstruktor
		CDBAddress (short lFNo = 0, long lRNo = 0, HPROJECT hPr = NULL) 
			: m_dba (hPr) { m_dba.file_no = lFNo; m_dba.rec_no = lRNo; }

	HPROJECT Project (void) { return m_dba.db_no; }
	short &FileNo (void) { return m_dba.file_no; }
	long &RecNo (void) { return m_dba.rec_no; }
};

#endif // _DBADDR_HXX

