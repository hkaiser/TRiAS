// WrapperKlasse, die Keydateie(en) eines Schluessels umbenennt ---------------
// File: BAKKEY.CXX

#include "triaspre.hxx"

#include <io.h>
#include <stdio.h>

#include <dbd.h>
#include <dbd.hxx>

#include "strfcns.hxx"
#include "bakkey.hxx"

// Konstruktor/Destruktor -----------------------------------------------------
CBackupKeyFile :: CBackupKeyFile (void)
{
	m_pKeyFile = NULL;
	m_pBackupKeyFile = NULL; 
	m_pTreeFile = NULL;
	m_pBackupTreeFile = NULL;
}

bool CBackupKeyFile :: Init (CDBDictDOSFiles &DBD, const char *pFullPath, short iKeyIndex)
{
// Temporäre DateiNamen verwenden
	m_pKeyFile = ExpandWithName (DBD.pKeyFileName (iKeyIndex), pFullPath, true);
	m_pBackupKeyFile = MakeTempName (IDS_TMPTEMPLATE1, pFullPath);
	m_pTreeFile = ExpandWithName (DBD.pTreeKeyFileName (iKeyIndex), pFullPath, true);
	m_pBackupTreeFile = MakeTempName (IDS_TMPTEMPLATE2, pFullPath);

// Dateien umbenennen
	if (m_pKeyFile && m_pBackupKeyFile) 
		rename (m_pKeyFile, m_pBackupKeyFile);
	else {
		DELETE (m_pBackupKeyFile);
		return false;
	}

	if (m_pTreeFile && m_pBackupTreeFile)
		rename (m_pTreeFile, m_pBackupTreeFile);
	else  {
		DELETE (m_pBackupTreeFile);
		return false;
	}

// Neue KeyDateien erzeugen
short iKeyType;

	if ((iKeyType = DBD.isBTreeKey (iKeyIndex)) > 0)
		DBD.CreateKeyFile (iKeyIndex, pFullPath);
	else if (iKeyType < 0) {
		DBD.CreateGeoTreeFile (iKeyIndex, pFullPath);
		DBD.CreateTreeKeyFile (iKeyIndex, pFullPath);
	}

	if (db_pzreread() != EC_OKAY)
		return false;

return true;
}

CBackupKeyFile :: ~CBackupKeyFile (void)
{
// wenn OK-Status nicht gestzt ist, dann Dateien zurück-umbenenen
	if (m_pBackupKeyFile) {
		unlink (m_pKeyFile);
		rename (m_pBackupKeyFile, m_pKeyFile);
		if (m_pBackupTreeFile) {
			unlink (m_pTreeFile);
			rename (m_pBackupTreeFile, m_pTreeFile);
		}
		db_pzreread();
	}
	DELETE (m_pKeyFile);
	DELETE (m_pTreeFile);
	DELETE (m_pBackupKeyFile);
	DELETE (m_pBackupTreeFile);
}


// Setzt den Status auf OK, d.h. Dateien sind erfolgreich generiert -----------
void CBackupKeyFile :: SetOK (void)
{
	if (m_pBackupKeyFile) {
		unlink (m_pBackupKeyFile);
		DELETE (m_pBackupKeyFile);
		if (m_pBackupTreeFile) {
			unlink (m_pBackupTreeFile);
			DELETE (m_pBackupTreeFile);
		}
	}
}


// Generiert einen Temporären DateiNamen --------------------------------------
char *MakeTempName (unsigned int resID, const char *pFullPath)
{
char *pTmp = new char [_MAX_PATH];
char *pDrive = new char [_MAX_DRIVE];
char *pPath = new char [_MAX_DIR];

	if (pTmp == NULL) return NULL;

	_splitpath (pFullPath, pDrive, pPath, NULL, NULL);
	_makepath (pTmp, pDrive, pPath, ResString (resID, _MAX_FNAME), "");
	if (tmpnam (pTmp) == NULL) 
		DELETE (pTmp);

	DELETE (pDrive);
	DELETE (pPath);

return pTmp;
}

