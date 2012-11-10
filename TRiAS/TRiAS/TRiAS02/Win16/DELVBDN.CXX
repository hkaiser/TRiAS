// Auf ein neues, Anne.
// File: DELVBDN.C

#if defined(MSWIND)
#include <windows.h>
#endif

#include <math.h>		// labs()

#include <dbtypes.h>
#include <errdef.h>
#include <risdb.h>
#include <zprotos.h>

long FUNCTYPE delvbd (long FileNo, long *Begin, long Wert) {
DB_ADDR dba;
long Data[3];
long Prev = 0;
long Next; 

long RC;	// FehlerCode

// ersten Satz einlesen
	dba.file_no = FileNo;
	dba.rec_no = 0;
	Next = *Begin;
// Suche des vorgegebenen Wertes
	do {
		Prev = dba.rec_no;
		if ((dba.rec_no = Next) <= 0)
		// nichts gefunden --> raus
			return S_NOTFOUND;
	// Satz aus VerbindungsDatei einlesen
		Read (dba, Data[0]);
	// n„chster Satz
		Next = Data[1];
	} while (labs (Data[0]) != Wert);

// gefundenen Satz der VerbindungsDatei freigeben
	Dispose (dba);
	if (Prev == 0) {
	// der gesuchte Wert ist der Erste
		*Begin = Data[1];	// n„chster Satz
		return S_OKAY;
	} else {
	// VerbindungsKette umh„ngen (letzter oder in der Mitte)
		dba.rec_no = Prev;
		Read (dba, Data[0]);
		Data[1] = Next;
		Write (dba, Data[0]);
	}

return S_OKAY;
}
