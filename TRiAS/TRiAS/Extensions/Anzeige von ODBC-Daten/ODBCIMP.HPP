// ImportInterface-Implementation für den Import von ODBC-Daten -----------
// File: ODBCIMP.HPP

#if !defined(_ODBCIMP_HPP)
#define _ODBCIMP_HPP

class CImportSheet;
class CImportParams;
class CDataBaseExt;
class CColumnObjArray;
class CRecSet;

class CImportOdbcData
{
private:
	CImportParams *m_pCImportParams;		// speichert Ergebnisse des Config-Dialogs
	CImportSheet *m_pCConfigDialog;

protected:
//	lese Tabellensätze
	BOOL GetTableRecords (CDataBaseExt *, CColumnObjArray *&, CRecSet *&, 
						  long &lMaxCnt);
	 
public:
	CImportOdbcData (void);
    ~CImportOdbcData (void);

  	void ImportData (void);				// Daten importieren
	BOOL Configure (void);				// Nutzer-Konfig
	BOOL CanImport (void); 				// Import möglich ?
};

#endif // _ODBCIMP_HPP

