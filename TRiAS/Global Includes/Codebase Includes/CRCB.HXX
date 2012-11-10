/*-----------------------------------------------------------------------

File: CRCB.HXX (Implementation)

CRCB -
beihaltet globale Funktionen fÅr die Initialisierung von CodeBase.

Erarbeitet: J. Benkenstein			   Stand am: 6. Juni 1992
------------------------------------------------------------------------*/

// Die Funktion liefert einen Zeiger auf ein erzeugtes CodeBase-Objekt und
// setzt das Applikation-Handle.
// Bei einem Fehler ist der Zeiger gleich NULL.
#if defined(__cplusplus)
extern "C" {
#endif

	E4EXPORT_FCT CodeBase* CreateCodeBaseObj (HINSTANCE hInst);
	E4EXPORT_FCT CodeBase* GetCodeBaseObj (void);
	E4EXPORT_FCT void DeleteCodeBaseObj (void);
	E4EXPORT_FCT void ResetCodeBaseCnt (void);

#if defined(__cplusplus)
}
#endif


