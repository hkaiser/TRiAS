#ifndef __DAOTRANSACTION_H__
#define __DAOTRANSACTION_H__
// JG 981007
// Implementierung einer exceptionsicheren Dao-Datenbanktransaktion

#include <afxDao.h>

class CDaoTransaction
{
protected:
	CDaoWorkspace * m_pWorkspace;

	void BeginTrans(CDaoWorkspace * pWorkspace)
	{
		if (NULL != m_pWorkspace)
		{
			m_pWorkspace -> BeginTrans();
			m_pWorkspace = pWorkspace;	// will not be executed on exceptions
		}
	}
public:
	CDaoTransaction(CDaoWorkspace& Workspace) 
	{
		BeginTrans(&Workspace);
	}

	CDaoTransaction(CDaoDatabase& Database) 
	{
		BeginTrans(Database.m_pWorkspace);
	}
	
	~CDaoTransaction()
	{
		// need to RollBack
		if (NULL != m_pWorkspace)
		{
			m_pWorkspace -> Rollback();
			m_pWorkspace = NULL;
		}
	}

	void Commit()
	{
		if (NULL != m_pWorkspace)
		{
			m_pWorkspace -> CommitTrans();
			m_pWorkspace = NULL;
		}
	}
};

#endif //__DAOTRANSACTION_H__