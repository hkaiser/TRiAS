/*
Datei: DAOTOOLS.HPP

Das Modul beinhaltet allgmeine Funktionen zur Arbeit mit den DAO-Klassen.

Erarbeitet: J. Benkenstein			Stand vom 26.7.1996
*/

#ifndef _DAO_TOOLS_HPP

//	gebe Abfragetyp als Text zurück
CString GetQueryType (short sType);

//	gebe DaoFeldTyp als Text zurück
CString GetFieldType (short sType);

//	Fehler-Behandlung realisieren
void DisplayDaoException(CDaoException* e);

#endif	// _DAO_TOOLS_HPP