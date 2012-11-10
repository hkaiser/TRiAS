/*
File: DATABASE.HPP
- Modul zur Verwaltung eines CDataBase-Objekts.

Erarbeitet: J.Benkenstein						Stand vom: 19.März 1994
*/


#ifndef _DATABASE_HPP
#define _DATABASE_HPP

class CDataBaseEx : public CDatabase
{ 
protected:
	DataSourceType m_tType;

public:
	CDataBaseEx (void);
	~CDataBaseEx (void);
	
    BOOL OpenAlias (const char *pAliasName);
    BOOL OpenDSN   (const char *pDataSourceName, DataSourceType tType);
	DataSourceType GetType (void) { return m_tType; }
	void Close (void);	
};  

class CDataBaseExt : public CDataBaseEx
{   
private:
	CString m_strDSN;
	
public:
	CDataBaseExt (const char *pDSN, DataSourceType tType);		
	~ CDataBaseExt (void) {}

	BOOL Open (void);
	const char *DataSourceName (void) { return m_strDSN; }
	
	friend void __export *GetDSN (void *pObj);
};     

class CDataBaseExtTree : public CTree
{                                      
private:
	long m_lRefCnt;

protected:
	void __export UserDelete (void *pObj);
	
public:
	CDataBaseExtTree (void);
	~ CDataBaseExtTree (void);				// alle Einträge löschen	
	                                            
// 	zum geg. AiasNamen das DSN-Objekt lesen (ggf. erzeugen und öffnen)	                                            
	CDataBaseExt *GetDataSource (const char *pAliasName);
	CDataBaseExt *GetDataSourceDSN (const char *pDSN, DataSourceType tType);
	void RemoveDataSource (CDataBaseExt *pDataBase);

        BOOL HasReferences (void);
        void RemoveAllDataSources (void);

	long RefCnt (void) { return m_lRefCnt; }
};
DeclareLock (CDataBaseExtTree, CDataBaseExt);    
                    
#endif // _DATABASE_HPP
