/* Steuerung der Zugriffsrechte auf eine Datenbasis			*/
/* File: ZACCESS.C							*/

#include "trias01p.hxx"

#include "syncdb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static void corr_access (FILE_ENTRY *, short);

extern "C" 
int FUNCTYPE EXPORT01 z_access (HPROJECT hPr, long flags) 
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

register int i;

	TX_ASSERT(file_table);

	if (flags & O_ALL) {
	// Zugriffsrechte für alle Dateien setzen
		for (i = 0; i < size_ft; i++)
			corr_access (&file_table[i], (short)LOWORD(flags));
	} else {
	// Zugriffsrechte nur einer Datei verändern
	register short num;
	
		num = (short)HIWORD(flags);		// Dateinummer
		TX_ASSERT(num >= 0 && num < size_ft);
//		if (num < 0 || num >= size_ft)
//			return (db_error (S_INVADDR, ZACCESS));
		corr_access (&file_table[num], (short)LOWORD(flags));
	}	

return S_OKAY;
}

extern "C" int FUNCTYPE EXPORT01 z_raccess (HPROJECT hPr, long flags) 
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

register int i;
FILE_ENTRY *ft_p;

	TX_ASSERT(file_table);

	if (flags & O_ALL) {
	// Zugriffsrechte für alle Dateien rücksetzen
		for (i = 0; i < size_ft; i++) {
			ft_p = &file_table[i];
			TX_ASSERT(ft_p);
			ft_p->ft_access = ft_p->ft_oldaccess;
		}
	} else {
	// Zugriffsrechte nur für eine Datei rücksetzen
	register short num = (short)HIWORD(flags);	// DateiNummer

		TX_ASSERT(num >= 0 && num < size_ft);
//		if (num < 0 || num >= size_ft)
//			return (db_error (S_INVADDR, ZACCESS));

		ft_p = &file_table[num];
		TX_ASSERT(ft_p);
		ft_p->ft_access = ft_p->ft_oldaccess;
	}	

return S_OKAY;
}

static void corr_access (register FILE_ENTRY *ft_p, short flags) 
{
	TX_ASSERT(ft_p);

	switch (flags) {
	case O_NOACC:		// Zugriff sperren
		if (ft_p->ft_access != O_NOACC) {
			ft_p->ft_oldaccess = ft_p->ft_access;
			ft_p->ft_access = O_NOACC;
		}
		break;

	case O_RDONLY:		// Schreibschutz setzen
		if (ft_p->ft_access == O_RDWR) {
			ft_p->ft_oldaccess = ft_p->ft_access;
			ft_p->ft_access = O_RDONLY;
		}
		break;

	case O_RDWR:		// volle Zugriffsrechte geben
		ft_p->ft_oldaccess = ft_p->ft_access;
		ft_p->ft_access = O_RDWR;
		break;

	default:
		TX_ASSERT(false);
		break;
	}
}


