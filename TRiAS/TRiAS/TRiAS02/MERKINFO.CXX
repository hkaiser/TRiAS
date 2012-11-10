// Memberfunktionen fuer MerkInfoDatenStrukturen
// File: MERKINFO.CXX

#include "trias02p.hxx"

#include "merkinfo.hxx"

// Konstruktoren/Destruktoren -------------------------------------------------
MerkInfo :: MerkInfo (long MCode, MerkInfoTyp Typ, short Len) 
{
	miMCode = MCode;
	miTyp = Typ;
	miLen = Len;
}

// Objekt, welches ein Textmerkmal repräsentiert ------------------------------
TextMerkInfo :: TextMerkInfo (long MCode, char *Text) 
	      : MerkInfo (MCode, MI_Text, 1)
{
// Text initialisieren
	if (!Text) {
		miText = NULL;
		return;
	}

// Speicher anfordern
	miText = new char [strlen(Text)+1];
	if (!miText) {
		db_error (EC_NOMEMORY, RC_ctTextMerkInfo);
		return;
	}
	strcpy (miText, Text);
}

TextMerkInfo :: ~TextMerkInfo (void) 
{
// Speicher wieder freigeben
	DELETE_OBJ (miText);
}

// Objekt, welches ein/mehrere LongMerkmalswerte repräsentiert ----------------
LongMerkInfo :: LongMerkInfo (long MCode, long *Werte, long Len) 
	      : MerkInfo (MCode, MI_Long, (short)Len)
{
// WerteFeld iinitialisieren
	if (!Werte) {
		miLong = NULL;
		return;
	}

// Speicher anfordern und Werte umkopieren
	miLong = new long [Len];
	if (!miLong) {
		db_error (EC_NOMEMORY, RC_ctLongMerkInfo);
		return;
	}
	memcpy (miLong, Werte, (uint)(Len*sizeof(long)));
}

LongMerkInfo :: ~LongMerkInfo (void) 
{
// Speicher wieder freigeben
	DELETE_OBJ (miLong);
}

// Objekt, welches ein/mehrere DoubleMerkmalswerte repräsentiert --------------
DoubleMerkInfo :: DoubleMerkInfo (long MCode, double *Werte, long Len) 
	        : MerkInfo (MCode, MI_Double, (short)Len)
{
// WerteFeld iinitialisieren
	if (!Werte) {
		miDouble = NULL;
		return;
	}

// Speicher anfordern und Werte umkopieren
	miDouble = new double [Len];
	if (!miDouble) {
		db_error (EC_NOMEMORY, RC_ctDoubleMerkInfo);
		return;
	}
	memcpy (miDouble, Werte, (uint)(Len*sizeof(double)));
}

DoubleMerkInfo :: ~DoubleMerkInfo (void) 
{
// Speicher wieder freigeben
	DELETE_OBJ (miDouble);
}

// Zugriffsfunktionen auf die dynamischen Member der Objekte ------------------
char *TextMerkInfo :: Text (char *Buffer, short iLen) 
{
	if (miText == NULL) return NULL;
	if (Buffer == NULL) {
	// kein Buffer gegeben
	char *cptr = new char [strlen (miText)+1];

		if (cptr)
			strcpy (cptr, miText);
		return cptr;
	}

// in ZielBuffer kopieren
	strncpy (Buffer, miText, iLen-1);
	Buffer[iLen-1] = '\0';

return Buffer;
}

long *LongMerkInfo :: LongWerte (long *LongFeld, short iLen) 
{
	if (miLong == NULL) return NULL;
	if (LongFeld == NULL) {
	// kein Zielfeld gegeben
	long *lptr = new long [miLen];

		if (lptr)
			memcpy (lptr, miLong, miLen*sizeof(long));
		return lptr;
	}

// in ZielFeld umkopieren
	memcpy (LongFeld, miLong, iLen*sizeof(long));

return LongFeld;
}

double *DoubleMerkInfo :: DoubleWerte (double *DoubleFeld, short iLen) 
{
	if (miDouble == NULL) return NULL;
	if (DoubleFeld == NULL) {
	// kein Zielfeld gegeben
	double *dptr = new double [miLen];

		if (dptr)
			memcpy (dptr, miDouble, miLen*sizeof(double));
		return dptr;
	}

// in ZielFeld umkopieren
	memcpy (DoubleFeld, miDouble, iLen*sizeof(double));

return DoubleFeld;
}

