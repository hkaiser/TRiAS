/*
DATEI:	importty.h

Definition der Typen und Datenstrukturen für den Import.

Erarbeitet: J.Benkenstein		Stand vom 27. Juni 1996
*/

#ifndef _IMPORTTY_H
#define _IMPORTTY_H

//	Typen zur Importparameter-Struktur
typedef enum { NoFormat = 0,  MdbTable, FoxProTable, MdbTableOld, FoxProTableOld } ImportType;

typedef enum { NoTable = 0, Abfall, Erzeuger, Branchen, Gemeinden, Abfallarten,
			   Transporteure, Entsorger, Kreise, Verbringung, Verfahren } TableType;			 

//	Typen für Tabellen-Importparameter-Struktur
class CImportParams;
typedef BOOL (*KonvertFunctionPtr)(CImportParams*);
typedef enum { AllRecords = 1, OnlyRefRecords = 2, OnlyNotRefRecords = 4} DatensatzMenge;
typedef enum { Always = 1, Never = 2, Index = 4, CheckImportFlag = 8 } DatensatzActual;

typedef struct 
{
	char *pFieldName;					// Name des Feldes
	short sType;						// FeldTyp --> dbText ...
	short sLen;							// -1: keine Angabe	
	KonvertFunctionPtr pfFieldKonvert;	// spezielle Konvertierungsfunktion
} FieldKonvert;	

//	Felder zusammenfügen
FieldKonvert *ConcatFields (FieldKonvert *FieldKonvert1, int iLen1, 
							FieldKonvert *FieldKonvert2, int iLen2);


class CTableInfo;
class CImportParams 
{
public:
//	Konstruktor/Destruktor
	CImportParams (void);
	~CImportParams (void);

//	Attribute: Tabellenspezifikationen
	ImportType m_tImportType;		
	TableType m_tTableType;

//	Quell/Ziel-Database
	CDaoDatabase m_SourceDatabase,
				 m_DestDatabase;

//	Quelle/Ziel-Recordset
	CDaoRecordset m_SourceSet,
				  m_DestSet;
	CDaoRecordset *m_pParamSet;

//	beinhaltet alle Infos für den Konvertierungstyp
	CTableInfo *m_pTableInfo;		

//	Tabellen-Namen
	CString m_strInputTableName,
			m_strOutputTableName;

//	Konvertierungszähler
	long m_lUpdateCnt, m_lAppendCnt, m_lUpdateErrCnt, m_lAppendErrCnt;

//	Als neue Tabelle verwenden
	BOOL m_bAsNewTable;

//	ReportFile
	CStdioFile m_ReportFile;

//	Name des HelpFiles
	CString m_strHelpFileName;
};

class CTableInfo
{
public:
//	Konstruktor/Destruktor
	CTableInfo (FieldKonvert *pInput, FieldKonvert *pOutput,
				DatensatzMenge tMenge, DatensatzActual tActual,
				UINT uiRecordSelectFlag, UINT uiRecordActFlag, UINT uiTableName, UINT uiDDL, 
				BOOL bCreateNumberIndex = FALSE, IndexFieldInfo *pInfo = NULL);
	virtual ~CTableInfo (void) {}

protected:
	UINT m_uiRecordSelect;				// Flags für Datensatz-Auswahl
	UINT m_uiRecordActual;				// und Aktualisierung
	UINT m_uiDDL;						// DDL-Id zum erzeugen der Tabelle

	BOOL m_bCreateNumberIndex;			// non unique index für Nummer erzeugen

//	Feldkonvertierungsfeld
	FieldKonvert *m_pFieldKonvertInput;	
	FieldKonvert *m_pFieldKonvertOutput;

//	opt. Konvertierungs-Funktionen
	KonvertFunctionPtr pfBeginImport;
	KonvertFunctionPtr pfEndImport;

//	opt. Suchschlüssel
	CString m_strKeyInpName1,				
			m_strKeyInpName2,
			m_strKeyOutName1,				
			m_strKeyOutName2,				
			m_strPrimaryKey,
			m_strTableName;

	IndexFieldInfo *m_pIndexFieldInfo;	// Namen mit zu erzeugenden Indizes
public:
//	Datensatzmenge- und Auswahl
	DatensatzMenge m_tMenge;
	DatensatzActual m_tActual;

//	lese-Funktionen
	FieldKonvert *InputTable () { return m_pFieldKonvertInput; }
	FieldKonvert *OutputTable () { return m_pFieldKonvertOutput; }

	const CString &KeyInpName1 () { return m_strKeyInpName1; }
	const CString &KeyInpName2 () { return m_strKeyInpName2; }
	const CString &KeyOutName1 () { return m_strKeyOutName1; }
	const CString &KeyOutName2 () { return m_strKeyOutName2; }
	const CString &PrimaryKey ()  { return m_strPrimaryKey; }

	UINT SelectFlag ()	{ return m_uiRecordSelect; }
	UINT ActFlag ()		{ return m_uiRecordActual; }
	UINT DDLId ()		{ return m_uiDDL; }
	BOOL CreateNumberIndex () { return m_bCreateNumberIndex; }
	IndexFieldInfo *GetIndexFieldInfo () { return m_pIndexFieldInfo; }	

	KonvertFunctionPtr BeginImport () { return pfBeginImport; }
	KonvertFunctionPtr EndImport () { return pfEndImport; }

	const CString& TableName () { return m_strTableName; }

	BOOL m_bDeleteInputTable;
};

class CAbfallTableInfo : public CTableInfo
{
protected:
	FieldKonvert *m_pFieldKonvertInputDyn,
				 *m_pFieldKonvertOutputDyn;
public:
//	Konstruktor/Destruktor
	CAbfallTableInfo (ImportType tKonvertType);
	virtual ~CAbfallTableInfo (void);
};

class CErzeugerTableInfo : public CTableInfo
{
protected:
	FieldKonvert *m_pFieldKonvertInputDyn,
				 *m_pFieldKonvertOutputDyn;
public:
//	Konstruktor/Destruktor
	CErzeugerTableInfo (ImportType tKonvertType);
	virtual ~CErzeugerTableInfo (void);
};

class CGemeindenTableInfo : public CTableInfo
{
public:
//	Konstruktor/Destruktor
	CGemeindenTableInfo (ImportType tKonvertType);
	virtual ~CGemeindenTableInfo (void) {}
};

class CBranchenTableInfo : public CTableInfo
{
public:
//	Konstruktor/Destruktor
	CBranchenTableInfo (ImportType tKonvertType);
	virtual ~CBranchenTableInfo (void) {}
};

class CAbfallArtenTableInfo : public CTableInfo
{
public:
//	Konstruktor/Destruktor
	CAbfallArtenTableInfo (ImportType tKonvertType);
	virtual ~CAbfallArtenTableInfo (void) {}
};

class CEntsorgerTableInfo : public CTableInfo
{
public:
//	Konstruktor/Destruktor
	CEntsorgerTableInfo (ImportType tKonvertType);
	virtual ~CEntsorgerTableInfo (void) {}
};

class CTransporteureTableInfo : public CTableInfo
{
public:
//	Konstruktor/Destruktor
	CTransporteureTableInfo (ImportType tKonvertType);
	virtual ~CTransporteureTableInfo (void) {}
};

class CKreisTableInfo : public CTableInfo
{
public:
//	Konstruktor/Destruktor
	CKreisTableInfo (ImportType tKonvertType);
	virtual ~CKreisTableInfo (void) {}
};

class CVerfahrenTableInfo : public CTableInfo
{
public:
//	Konstruktor/Destruktor
	CVerfahrenTableInfo (ImportType tKonvertType);
	virtual ~CVerfahrenTableInfo (void) {}
};

class CVerbringungTableInfo : public CTableInfo
{
public:
//	Konstruktor/Destruktor
	CVerbringungTableInfo (ImportType tKonvertType);
	virtual ~CVerbringungTableInfo (void) {}
};

#endif	// _IMPORTTY_H


