// recset.h : interface of the CRecordsetExt class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _RECSET_H
#define _RECSET_H

class CRecordsetExt : public CRecordset
{
DECLARE_DYNAMIC(CRecordsetExt)

public:
	CString m_strTableName;

	CRecordsetExt(CDatabase* pDatabase);
	~CRecordsetExt ();      
	
// 	lese Anz. aller im Set enth. Sätze    
// 	lese ab aktueller Position im Set
//	gehe dann wieder auf 1. Satz
	long GetRecordCount (BOOL bMoveToFirstRecord = TRUE);
	
	virtual void SetFieldCnt (BOOL bSet) = 0;

//	alle Datensätze im Set löschen
	void DeleteAll (const CString &strWhere);
};

#endif 		// 	_RECSET_H

