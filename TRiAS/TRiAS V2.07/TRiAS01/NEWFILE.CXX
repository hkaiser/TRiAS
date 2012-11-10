// Anlegen verschiedener DB-Dateien -------------------------------------------
// File: NEWFILE.CXX


#include "trias01p.hxx"

// lokale DatenStrukturen -----------------------------------------------------
// Struktur eine Page ---------------------------------------------------------
#pragma pack(1)

typedef union tagPAGE {
	INT lPage [MAXPAGESIZE/sizeof(INT)];
	struct {	// allgemeine Page 1
		char Copyright[80];	/* Copyright */
		INT lDelChain;		/* Freikettenzeiger */
		INT lNext;		/* naechste freie Record im File */
		time_t BackupDate;	/* Datum/Zeit des letzten Backup */
		time_t CreationDate;	/* Datum/Zeit der Filegenerierung */
	} Page1;
	struct {	// Page 2 für KeyDateien
		time_t ChangeDate;        /* Datum der letzten Änderung dieser Page */
		INT dummy;
		INT iBytes[3];
	} Page2;
	struct {
		char Copyright[80];
		PGZERO pzBackup;
		PGZERO pzTable[1];
	} Page3;
} PAGE;

#pragma pack()

// Anlegen der GeometrieBaumDatei ---------------------------------------------
extern "C" short FUNCTYPE EXPORT01 CreateTreeKeyFile (char *pFName, const char *pCopyright, 
				   long TimeVal, short iPageSize)
{
PAGE *pPage = new PAGE;

	if (pPage == NULL) 
		return db_error (S_NOMEMORY, CREATETREEKEYFILE);

OFSTRUCT of;
int fh;

	if ((fh = OpenFile (pFName, &of, OF_CREATE | OF_READWRITE)) < 0)
		return db_error (S_NOFILE, CREATETREEKEYFILE);

	if (TimeVal == 0) time (&TimeVal);

	memset (pPage, '\0', sizeof(PAGE));
	strcpy (pPage -> Page1.Copyright, pCopyright);	
	pPage -> Page1.lDelChain = -1;
	pPage -> Page1.lNext = 1;
	pPage -> Page1.BackupDate = pPage -> Page1.CreationDate = TimeVal;

	if (_lwrite (fh, (LPCSTR)pPage, UINT(iPageSize)) != UINT(iPageSize)) {
		DELETE (pPage);		// Speicher freigeben
		_lclose (fh);
		return db_error (S_NOSPACE, CREATETREEKEYFILE);
	}

	memset (pPage, '\0', sizeof(PAGE));
	pPage -> Page2.ChangeDate = TimeVal;

short iEC = S_OKAY;

	if (_lwrite (fh, (LPCSTR)pPage, UINT(iPageSize)) != UINT(iPageSize)) 
		iEC = db_error (S_NOSPACE, CREATETREEKEYFILE);
		
	_lclose (fh);
	DELETE (pPage);		// Speicher freigeben

return iEC;
}

// Anlegen der GeometrieSchlüsselDatei ----------------------------------------
extern "C" short FUNCTYPE EXPORT01 CreateGeoTreeFile (char *pFName, const char *pCopyright, 
				   long TimeVal, short iPageSize)
{
PAGE *pPage = new PAGE;

	if (pPage == NULL) 
		return db_error (S_NOMEMORY, CREATEGEOTREEFILE);

OFSTRUCT of;
int fh;

	if ((fh = OpenFile (pFName, &of, OF_CREATE | OF_READWRITE)) < 0)
		return db_error (S_NOFILE, CREATEGEOTREEFILE);

	if (TimeVal == 0) time (&TimeVal);

	memset (pPage, '\0', sizeof(PAGE));
	strcpy (pPage -> Page1.Copyright, pCopyright);	
	pPage -> Page1.lDelChain = 0;
	pPage -> Page1.lNext = 2;
	pPage -> Page1.BackupDate = pPage -> Page1.CreationDate = TimeVal;

	if (_lwrite (fh, (LPCSTR)pPage, UINT(iPageSize)) != UINT(iPageSize)) {
		DELETE (pPage);		// Speicher freigeben
		_lclose (fh);
		return db_error (S_NOSPACE, CREATEGEOTREEFILE);
	}

	memset (pPage, '\0', sizeof(PAGE));
	pPage -> Page2.ChangeDate = TimeVal;

short iEC = S_OKAY;

	if (_lwrite (fh, (LPCSTR)pPage, UINT(iPageSize)) != UINT(iPageSize)) 
		iEC = db_error (S_NOSPACE, CREATEGEOTREEFILE);
		
	_lclose (fh);
	DELETE (pPage);		// Speicher freigeben

return S_OKAY;
}


// Anlegen einer ordinären Schlüsseldatei -------------------------------------
extern "C" short FUNCTYPE EXPORT01 CreateKeyFile (char *pFName, const char *pCopyright, 
				   long TimeVal, short iPageSize)
{
PAGE *pPage = new PAGE;

	if (pPage == NULL) 
		return db_error (S_NOMEMORY, CREATEKEYFILE);

OFSTRUCT of;
int fh;

	if ((fh = OpenFile (pFName, &of, OF_CREATE | OF_READWRITE)) < 0)
		return db_error (S_NOFILE, CREATEKEYFILE);

	if (TimeVal == 0) time (&TimeVal);

	memset (pPage, '\0', sizeof(PAGE));
	strcpy (pPage -> Page1.Copyright, pCopyright);	
	pPage -> Page1.lDelChain = -1;
	pPage -> Page1.lNext = 2;
	pPage -> Page1.BackupDate = pPage -> Page1.CreationDate = TimeVal;

	if (_lwrite (fh, (LPCSTR)pPage, UINT(iPageSize)) != UINT(iPageSize)) {
		DELETE (pPage);		// Speicher freigeben
		_lclose (fh);
		return db_error (S_NOSPACE, CREATEKEYFILE);
	}

	memset (pPage, '\0', sizeof(PAGE));
	pPage -> Page2.ChangeDate = TimeVal;
	pPage -> Page2.iBytes[0] = -1;

short iEC = S_OKAY;

	if (_lwrite (fh, (LPCSTR)pPage, UINT(iPageSize)) != UINT(iPageSize)) 
		iEC = db_error (S_NOSPACE, CREATEKEYFILE);
		
	_lclose (fh);
	DELETE (pPage);		// Speicher freigeben

return S_OKAY;
}


// Anlegen einer ordinären Datendatei -----------------------------------------
extern "C" short FUNCTYPE EXPORT01 CreateDataFile (char *pFName, const char *pCopyright, 
				   long TimeVal, short iPageSize)
{
PAGE *pPage = new PAGE;

	if (pPage == NULL) 
		return db_error (S_NOMEMORY, CREATEDATAFILE);

OFSTRUCT of;
int fh;

	if ((fh = OpenFile (pFName, &of, OF_CREATE | OF_READWRITE)) < 0)
		return db_error (S_NOFILE, CREATEDATAFILE);

	if (TimeVal == 0) time (&TimeVal);

	memset (pPage, '\0', sizeof(PAGE));
	strcpy (pPage -> Page1.Copyright, pCopyright);	
	pPage -> Page1.lDelChain = 0;
	pPage -> Page1.lNext = 1;
	pPage -> Page1.BackupDate = pPage -> Page1.CreationDate = TimeVal;

short iEC = S_OKAY;

	if (_lwrite (fh, (LPCSTR)pPage, UINT(iPageSize)) != UINT(iPageSize)) 
		iEC = db_error (S_NOSPACE, CREATEDATAFILE);
		
	_lclose (fh);
	DELETE (pPage);		// Speicher freigeben

return S_OKAY;
}


extern "C" short FUNCTYPE EXPORT01 CreateBackupFile (char *pFName, const char *pCopyright, 
				   long TimeVal, PGZERO *pPZTable, 
				   short iFiles, short iPageSize)
{
PAGE *pPage = new PAGE;

	if (pPage == NULL) 
		return db_error (S_NOMEMORY, CREATEBACKUPFILE);

OFSTRUCT of;
int fh;

	if ((fh = OpenFile (pFName, &of, OF_CREATE | OF_READWRITE)) < 0)
		return db_error (S_NOFILE, CREATEBACKUPFILE);

	if (TimeVal == 0) time (&TimeVal);

	memset (pPage, '\0', sizeof(PAGE));

	strcpy (pPage -> Page3.Copyright, pCopyright);	
	pPage -> Page3.pzBackup.pz_dchain = -1;
	pPage -> Page3.pzBackup.pz_next = -1;
	memcpy (pPage -> Page3.pzTable, pPZTable, iFiles*sizeof(PGZERO));

short iEC = S_OKAY;

	if (_lwrite (fh, (LPCSTR)pPage, UINT(iPageSize)) != UINT(iPageSize)) 
		iEC = db_error (S_NOSPACE, CREATEBACKUPFILE);
		
	_lclose (fh);
	DELETE (pPage);		// Speicher freigeben

return S_OKAY;
}


// Das gleiche noch mal für die Streams ---------------------------------------
extern "C" short FUNCTYPE EXPORT01 CreateDataStream (LPSTREAM pIStream, 
				   const char *pCopyright, 
				   long TimeVal, short iPageSize)
{
PAGE *pPage = new PAGE;

	if (pPage == NULL) 
		return db_error (S_NOMEMORY, CREATEDATAFILE);

	if (TimeVal == 0) time (&TimeVal);

	memset (pPage, '\0', sizeof(PAGE));
	strcpy (pPage -> Page1.Copyright, pCopyright);	
	pPage -> Page1.lDelChain = 0;
	pPage -> Page1.lNext = 1;
	pPage -> Page1.BackupDate = pPage -> Page1.CreationDate = TimeVal;

ULONG ulWritten = 0;
short iEC = S_OKAY;

	pIStream -> Write (pPage, UINT(iPageSize), &ulWritten);
	if (ulWritten != UINT(iPageSize))
		iEC = db_error (S_NOSPACE, CREATEDATAFILE);
	DELETE (pPage);		// Speicher freigeben

return S_OKAY;
}


// Anlegen der GeometrieBaumDatei ---------------------------------------------
extern "C" short FUNCTYPE EXPORT01 CreateTreeKeyStream (LPSTREAM pIStream, 
				   const char *pCopyright, 
				   long TimeVal, short iPageSize)
{
PAGE *pPage = new PAGE;

	if (pPage == NULL) 
		return db_error (S_NOMEMORY, CREATETREEKEYFILE);

	if (TimeVal == 0) time (&TimeVal);

	memset (pPage, '\0', sizeof(PAGE));
	strcpy (pPage -> Page1.Copyright, pCopyright);	
	pPage -> Page1.lDelChain = -1;
	pPage -> Page1.lNext = 1;
	pPage -> Page1.BackupDate = pPage -> Page1.CreationDate = TimeVal;

ULONG ulWritten = 0;

	pIStream -> Write (pPage, UINT(iPageSize), &ulWritten);
	if (ulWritten != UINT(iPageSize)) {
		DELETE (pPage);		// Speicher freigeben
		return db_error (S_NOSPACE, CREATETREEKEYFILE);
	}

	memset (pPage, '\0', sizeof(PAGE));
	pPage -> Page2.ChangeDate = TimeVal;

short iEC = S_OKAY;

	pIStream -> Write (pPage, UINT(iPageSize), &ulWritten);
	if (ulWritten != UINT(iPageSize))
		iEC = db_error (S_NOSPACE, CREATETREEKEYFILE);
	DELETE (pPage);		// Speicher freigeben

return S_OKAY;
}

// Anlegen der GeometrieSchlüsselDatei ----------------------------------------
extern "C" short FUNCTYPE EXPORT01 CreateGeoTreeStream (LPSTREAM pIStream, 
				   const char *pCopyright, 
				   long TimeVal, short iPageSize)
{
PAGE *pPage = new PAGE;

	if (pPage == NULL) 
		return db_error (S_NOMEMORY, CREATEGEOTREEFILE);

	if (TimeVal == 0) time (&TimeVal);

	memset (pPage, '\0', sizeof(PAGE));
	strcpy (pPage -> Page1.Copyright, pCopyright);	
	pPage -> Page1.lDelChain = 0;
	pPage -> Page1.lNext = 2;
	pPage -> Page1.BackupDate = pPage -> Page1.CreationDate = TimeVal;

ULONG ulWritten = 0;

	pIStream -> Write (pPage, UINT(iPageSize), &ulWritten);
	if (ulWritten != UINT(iPageSize)) {
		DELETE (pPage);		// Speicher freigeben
		return db_error (S_NOSPACE, CREATEGEOTREEFILE);
	}

	memset (pPage, '\0', sizeof(PAGE));
	pPage -> Page2.ChangeDate = TimeVal;

short iEC = S_OKAY;

	pIStream -> Write (pPage, UINT(iPageSize), &ulWritten);
	if (ulWritten != UINT(iPageSize))
		iEC = db_error (S_NOSPACE, CREATEGEOTREEFILE);
	DELETE (pPage);		// Speicher freigeben

return S_OKAY;
}


// Anlegen einer ordinären Schlüsseldatei -------------------------------------
extern "C" short FUNCTYPE EXPORT01 CreateKeyStream (LPSTREAM pIStream, 
				   const char *pCopyright, 
				   long TimeVal, short iPageSize)
{
PAGE *pPage = new PAGE;

	if (pPage == NULL) 
		return db_error (S_NOMEMORY, CREATEKEYFILE);

	if (TimeVal == 0) time (&TimeVal);

	memset (pPage, '\0', sizeof(PAGE));
	strcpy (pPage -> Page1.Copyright, pCopyright);	
	pPage -> Page1.lDelChain = -1;
	pPage -> Page1.lNext = 2;
	pPage -> Page1.BackupDate = pPage -> Page1.CreationDate = TimeVal;

ULONG ulWritten = 0;

	pIStream -> Write (pPage, UINT(iPageSize), &ulWritten);
	if (ulWritten != UINT(iPageSize)) {
		DELETE (pPage);		// Speicher freigeben
		return db_error (S_NOSPACE, CREATEKEYFILE);
	}

	memset (pPage, '\0', sizeof(PAGE));
	pPage -> Page2.ChangeDate = TimeVal;
	pPage -> Page2.iBytes[0] = -1;

short iEC = S_OKAY;

	pIStream -> Write (pPage, UINT(iPageSize), &ulWritten);
	if (ulWritten != UINT(iPageSize))
		iEC = db_error (S_NOSPACE, CREATEKEYFILE);
	DELETE (pPage);		// Speicher freigeben

return S_OKAY;
}


extern "C" short FUNCTYPE EXPORT01 CreateBackupStream (LPSTREAM pIStream, 
				   const char *pCopyright, 
				   long TimeVal, PGZERO *pPZTable, 
				   short iFiles, short iPageSize)
{
PAGE *pPage = new PAGE;

	if (pPage == NULL) 
		return db_error (S_NOMEMORY, CREATEBACKUPFILE);

	if (TimeVal == 0) time (&TimeVal);

	memset (pPage, '\0', sizeof(PAGE));

	strcpy (pPage -> Page3.Copyright, pCopyright);	
	pPage -> Page3.pzBackup.pz_dchain = -1;
	pPage -> Page3.pzBackup.pz_next = -1;
	memcpy (pPage -> Page3.pzTable, pPZTable, iFiles*sizeof(PGZERO));

ULONG ulWritten = 0;
short iEC = S_OKAY;

	pIStream -> Write (pPage, UINT(iPageSize), &ulWritten);
	if (ulWritten != UINT(iPageSize))
		iEC = db_error (S_NOSPACE, CREATEKEYFILE);
	DELETE (pPage);		// Speicher freigeben

return S_OKAY;
}


