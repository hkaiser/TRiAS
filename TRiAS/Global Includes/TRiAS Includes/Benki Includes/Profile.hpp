// Klassendeklarationen für lokale Profile-Dateien (DBasedaten anzeigen)
// File: PROFILE.HPP

#ifndef _PROFILE_HPP
#define _PROFILE_HPP

class DBaseRel;

// Verwaltung einer ProfileDatei
class Profile {
private:
	char *_pFullName;        // Pfadname der ProfileDatei

protected:
		//	dBASE-Entry in ODBC-Entry konvertieren
	BOOL KonvertDBaseToOdbc (ulong ulId, char *pBuffer, short BufferSize,
							 int &iEntryCnt);
public:
// Konstruktor/Destruktor
	Profile (void);
	~Profile (void);

// 	Memberfunktionen: Lesefunktionen
	int ReadOdbcCodes (long **, char ***, long Id = -1L);
	int ReadOdbcRelations (DBaseRel &, DBaseRel ***);
	BOOL RelationEntryExist (CString &strMaster);

	char *GetProFileName (void) { return _pFullName; }
	char *GetTableName (const char *pAliasName);	 // Zeiger ist explizit freizugeben
	char *GetDataSourceName (const char *pAliasName, DataSourceType &tDsn);// Zeiger ist explizit freizugeben
	char *GetFulldBaseName (const char *pAliasName); // Zeiger ist explizit freizugeben

	CString GetAliasName (const char *pDsn, DataSourceType tType, const char *pTableName);
	CString GetKoppelFeld (const char *pAliasName);
	ULONG GetMerkmalsKode (const char *pAliasName);

//	lese durch Komma getrennt alle Objklassen, die die gegebene anbindung erfüllen
	CString GetObjClasses (const char *pAliasName, const char *pKoppelField, ULONG ulMK);

//	Schreibfunktionen
		//	schreibe "normale" Anbindung in ODBC-Section
	BOOL WriteOdbcEntry (ulong ulId, const char *pAliasName, const char *pFeldName, 
						 ulong ulMKode);

		//	schreibe Klausel-Anbindung in ODBC-Section
	BOOL WriteOdbcKlausel (ulong ulId, const char *pAliasName, const char *pKlausel);

		// Tablename schreiben
	BOOL WriteTableName (const char *pAliasName, const char *pTableName);

		// DataSourcename schreiben
	BOOL WriteDataSourceName (const char *pAliasName, const char *pDSN, DataSourceType tDsn);

		// Standard-DataSourcename schreiben
	BOOL WriteStandardDataSourceName (const char *pDSN, DataSourceType tDsn);

		// Schreiben des vollständigen dBase-Dateinamens (Section dBase-AliasNames)
	BOOL WritedBaseAliasName (const char *pAliasName);

	//	schreibe normale Anbindung in DBASE-Section
	BOOL WriteDBaseEntry (ulong ulId, const char *pAliasName,
						  const char *pFeldName, ulong ulMK);
};

#endif		// _PROFILE_HPP

