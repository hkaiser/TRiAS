// recset.hpp : header file
//
// Stand vom 16.Mai 1994
/////////////////////////////////////////////////////////////////////////////
// CRecSet recordset

#ifndef _REC_SET
#define _REC_SET

class CColumnObjArray;

class CRecSet : public CRecordset
{
private:
	CColumnObjArray *m_pCA;	            // Spalten-Infos                     
	BOOL m_bReadAll;					// Leseflag
	short m_sLastRow;					// zuletzt gelesene Satz-Nummer
	
public:          
	BOOL m_bForwardOnly;				// Lese-Richtungs-Flag

	CRecSet(CDatabase &Database, CColumnObjArray &CA, CString strSQL);
	~CRecSet(void);		// ggf. zuvor schlieﬂen
	
	// void Close (void);		

// Field/Param Data
	//{{AFX_FIELD(CRecSet, CRecordset)
	//}}AFX_FIELD
	
	long GetRecordCount (); 				// lese Anz. aller im Set enth. S‰tze
											// (vom aktuellen Satz an)
											// geht dann wieder auf den 1. Satz
											
		//	aktuellen Satz mit LongBinary-Feldern lesen											
	BOOL RefreshAllFields (short sActRowNr);

		// 	Recordset schlieﬂen
	void Close (void);

// Implementation
protected:
	virtual CString GetDefaultConnect();				// Default connection string
	virtual CString GetDefaultSQL(); 					// Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support  
};

#endif 	// _REC_SET

