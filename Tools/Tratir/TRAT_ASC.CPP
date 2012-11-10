/* Routinen fuer Transformation ATLAS in DIRIS-Austauschformat  */
/* File: TRAT_ASC.C                                             */

#include "tratasp.h"

#define _TRIAS02_ENTRY 
#include <FormatString.h>

#include "ParamArray.h"

/* lokale Prototypen */
static int next_line (int);
void write_mi (short iFlag);
static void CopyHeader (void);

extern FILE    *fascii;

extern int 	m_flag;
extern int 	b_flag;
extern int	bo_flag;
extern int 	h_flag;
extern int	nomk_flag;	// StandardMerkmal nicht generieren
extern int 	y_flag;

extern char    *no_open;
extern char 	fnin[];

long lLastPos = 0L;		// Beginn des letzten Objektes
long lActPos = 0L;		// Beginn des aktuellen Objektes
long lMCode = -1L;		// letzter BezugsMerkmalsCode bei [P]

char *pTrennSatz = "; ----------------------------------------------------------------------------\n";
char *pHeaderSatz = " Headerdatei: ";
char *pInputSatz = " Eingabedatei: ";

void OutMI (short, char *, int);
int hasMCode (long lMCode);
void ReSeek (void);

extern IExtendedDataConversionPtr g_ExtConv;

/* Kopf ausgeben */
void print_hdr (long UCode)
{
char locTrennSatz[_MAX_PATH];

	USES_CONVERSION;
	if (g_ExtConv) {
	CComBSTR bstrOut("H Transformiertes Atlas*GIS-Austauschformat\n");
	VARIANT_BOOL fOutput = VARIANT_TRUE;
	CMCodeArray pars (mi_code, UCode, name4_code);

		g_ExtConv -> PreOutputHeader (pars, &bstrOut, &fOutput);
		if (!fOutput) return;		// dieses Objekt nicht ausgeben
		fprintf (fascii, OLE2A(bstrOut));

		bstrOut.Empty();
		g_ExtConv -> PostOutputHeader (&bstrOut);
		if (bstrOut.Length() > 0)
			fprintf (fascii, OLE2A(bstrOut));
	} else 
		fprintf(fascii, "H Transformiertes Atlas*GIS-Austauschformat\n");

// Header-DateiNamen ausgeben
	strcpy (locTrennSatz, pTrennSatz);
	memcpy (&locTrennSatz[5], pHeaderSatz, strlen (pHeaderSatz));
	memcpy (&locTrennSatz[19], HFile, strlen(HFile));
	fprintf (fascii, locTrennSatz);

	if (h_flag) 	// HeaderDatei rankopieren
		CopyHeader ();	
	if (m_flag)
		fprintf (fascii, "D Entry \"%-16.16s\" \"%ld\"\n", "Unique Ident", UCode);
	fprintf (fascii, "D Entry \"%-16.16s\" \"%d\"\n", "IdentBase", d_flag ? 10 : 16);

// Eingabe-DateiNamen ausgeben
	strcpy (locTrennSatz, pTrennSatz);
	memcpy (&locTrennSatz[5], pInputSatz, strlen (pInputSatz));
	memcpy (&locTrennSatz[20], fnin, strlen(fnin));
	fprintf (fascii, locTrennSatz);

	if (fascii != stdout) {
		fprintf (stderr, "Objekt:       ");
		fflush (stderr);
	}
}

// EndeSatz ausgeben
void print_trailer (void) 
{
	USES_CONVERSION;

CComBSTR bstrTrailer ("E\n");
VARIANT_BOOL fOutput = VARIANT_TRUE;

	if (g_ExtConv) {
		g_ExtConv -> PreOutputTrailer (&bstrTrailer, &fOutput);
		if (!fOutput) return;	// Trailer nicht ausgeben
	}

	fprintf (fascii, OLE2A(bstrTrailer));

	if (g_ExtConv) {
		bstrTrailer.Empty();
		g_ExtConv -> PostOutputTrailer (&bstrTrailer);
		if (bstrTrailer.Length() > 0)
			fprintf (fascii, OLE2A(bstrTrailer));
	}
}


// Header umkopieren
static void CopyHeader (void) 
{
char inBuff[256];
FILE *fpHeader;

	if ((fpHeader = fopen (HFile, "r")) == NULL) {
		fprintf (stderr, no_open, "Header-Datei", HFile);		
		fflush (stderr);
		return;
	}
	while (fgets (inBuff, sizeof(inBuff)-1, fpHeader) != NULL) 
		fputs (inBuff, fascii);
	fclose (fpHeader);
}


/* Objekt abspeichern */
void save_object(void)
{
int i;

	if (name1[0] == '\0')
		id = idst;
	
	if (y_flag) {
	// als Identifikator ausgeben
		if (d_flag) {
			sprintf (ID, "%ld", id);
			for (i = 0; ID[i] != '\0'; i++)
				if (!isdigit(ID[i])) ID[i]='0';
		} else
			sprintf (ID, "0x%lx", id);
	} else {
	// als Objektklassenschlüssel ausgeben
		sprintf (ID, "\"%s\"", IdInBuffer);
	}

	lActPos = ftell (fascii);		// aktuelle FilePosition
	if (lLastPos == 0L) lLastPos = lActPos;	// erstes mal

	if (koord_paare == 1)
		save_point();
	else if (koord_paare <= 0)
		save_line();
	else
		save_area();

	if (fascii != stdout) {
		fprintf(stderr, "\b\b\b\b\b\b%6d", on);	
		fflush (stderr);
	}

	lLastPos = lActPos;			// letzte FilePosition
	lActPos = 0L;
}

/* Punkt abspeichern */
void save_point(void)
{
register char *cptr;
CComBSTR bstrOut;
os_string strOut;

	USES_CONVERSION;

	if (b_flag && !strncmp (uident, "[B]", 3)) {
	// Textobjekt generieren
		if (g_ExtConv) {
			Format (strOut, "B %8ld %s    1\n", on, ID);
			bstrOut = strOut.c_str();

		VARIANT_BOOL fOutput = VARIANT_TRUE;
		CParamArray pars (name1, txt, uident, name4);

			g_ExtConv -> PreOutputObjectStart (on, pars, &bstrOut, &fOutput);
			if (!fOutput)
				return;		// dieses Objekt nicht ausgeben
			fprintf (fascii, OLE2A(bstrOut));

			bstrOut.Empty();
			g_ExtConv -> PostOutputObjectStart (on, &bstrOut);
			if (bstrOut.Length() > 0)
				fprintf (fascii, OLE2A(bstrOut));
		} else 
			fprintf(fascii, "B %8ld %s    1\n", on, ID);

	// Text in "..." ausgeben
		cptr = strchr (txt, '\"');
		if (cptr != NULL) 
			OutMI ('\'', txt, 'I');
		else
			OutMI ('\"', txt, 'I');

		write_mi (TRUE);
		fprintf(fascii, "G %12.5f %12.5f\n", gxi[0]*g_dKoeff, gyi[0]*g_dKoeff);
		bo_flag = TRUE;		// BO-Inf gesetzt
		Znr = on;		// Relation aufbauen

		lMCode = -1L;
	} else if (b_flag && !strncmp (uident, "[P]", 3)) {
	// Begleitobjekt schreiben
		if (g_ExtConv) {
			Format (strOut, "B %8ld %s    1\n", on, ID);
			bstrOut = strOut.c_str();

		VARIANT_BOOL fOutput = VARIANT_TRUE;
		CParamArray pars (name1, txt, uident, name4);

			g_ExtConv -> PreOutputObjectStart (on, pars, &bstrOut, &fOutput);
			if (!fOutput)
				return;		// dieses Objekt nicht ausgeben
			fprintf (fascii, OLE2A(bstrOut));

			bstrOut.Empty();
			g_ExtConv -> PostOutputObjectStart (on, &bstrOut);
			if (bstrOut.Length() > 0)
				fprintf (fascii, OLE2A(bstrOut));
		} else 
			fprintf(fascii, "B %8ld %s    1\n", on, ID);

	// Text in "..." ausgeben
		cptr = strchr (txt, '\"');
		if (cptr != NULL) 
			OutMI ('\'', txt, 'I');
		else
			OutMI ('\"', txt, 'I');

		write_mi (TRUE);
		fprintf(fascii, "G %12.5f %12.5f\n", gxi[0]*g_dKoeff, gyi[0]*g_dKoeff);
		bo_flag = TRUE;		// BO-Inf gesetzt
		Znr = on;		// Relation aufbauen

		lMCode = atol (txt);
		if (lMCode == 0L) lMCode = -1L;
	} else if (b_flag && !strncmp (uident, "[T]", 3)) {
		ReSeek();

	// alleinstehendes Textobjekt schreiben
		if (g_ExtConv) {
			Format (strOut, "B %8ld %s    1\n", on, ID);
			bstrOut = strOut.c_str();

		VARIANT_BOOL fOutput = VARIANT_TRUE;
		CParamArray pars (name1, txt, uident, name4);

			g_ExtConv -> PreOutputObjectStart (on, pars, &bstrOut, &fOutput);
			if (!fOutput)
				return;		// dieses Objekt nicht ausgeben
			fprintf (fascii, OLE2A(bstrOut));

			bstrOut.Empty();
			g_ExtConv -> PostOutputObjectStart (on, &bstrOut);
			if (bstrOut.Length() > 0)
				fprintf (fascii, OLE2A(bstrOut));
		} else 
			fprintf(fascii, "B %8ld %s    1\n", on, ID);

	// Text in "..." ausgeben
		cptr = strchr (txt, '\"');
		if (cptr != NULL) 
			OutMI ('\'', txt, 'I');
		else
			OutMI ('\"', txt, 'I');

		write_mi (TRUE);
		fprintf(fascii, "G %12.5f %12.5f\n", gxi[0]*g_dKoeff, gyi[0]*g_dKoeff);
		bo_flag = FALSE;	// BO-Inf nicht gesetzt

		lMCode = -1L;
	} else {
		ReSeek();

	// normales Punktobjekt generieren
		if (!strncmp (uident, "[S]", 3))
			strcpy (uident, uident + 3);

		if (g_ExtConv) {
			Format (strOut, "P %8ld %s    1\n", on, ID);
			bstrOut = strOut.c_str();

		VARIANT_BOOL fOutput = VARIANT_TRUE;
		CParamArray pars (name1, txt, uident, name4);

			g_ExtConv -> PreOutputObjectStart (on, pars, &bstrOut, &fOutput);
			if (!fOutput)
				return;		// dieses Objekt nicht ausgeben
			fprintf (fascii, OLE2A(bstrOut));

			bstrOut.Empty();
			g_ExtConv -> PostOutputObjectStart (on, &bstrOut);
			if (bstrOut.Length() > 0)
				fprintf (fascii, OLE2A(bstrOut));
		} else 
			fprintf(fascii, "P %8ld %s 1\n", on, ID);

		write_mi (FALSE);		// Merkmale ausgeben
		fprintf(fascii, "G %12.5f %12.5f\n", gxi[0]*g_dKoeff, gyi[0]*g_dKoeff);
		bo_flag = FALSE;

		lMCode = -1L;
	}
}

/* Linie abspeichern */
void save_line(void)
{
int i, j;
CComBSTR bstrOut;
os_string strOut;

	USES_CONVERSION;

	ReSeek();

	lgi++;			/* Geometriezaehler korrigieren */

	if (name1[0] != 'L' && name1[0] != 'l' &&
	    name1[0] != 'P' && name1[0] != 'p') 
	{
		if (g_ExtConv) {
			Format (strOut, "L %8ld %s %4ld\n", on, ID, lgi);
			bstrOut = strOut.c_str();

		VARIANT_BOOL fOutput = VARIANT_TRUE;
		CParamArray pars (name1, txt, uident, name4);

			g_ExtConv -> PreOutputObjectStart (on, pars, &bstrOut, &fOutput);
			if (!fOutput)
				return;		// dieses Objekt nicht ausgeben
			fprintf (fascii, OLE2A(bstrOut));

			bstrOut.Empty();
			g_ExtConv -> PostOutputObjectStart (on, &bstrOut);
			if (bstrOut.Length() > 0)
				fprintf (fascii, OLE2A(bstrOut));
		} else 
			fprintf(fascii, "L %8ld %s %4ld\n", on, ID, lgi);
		write_mi (FALSE);
	} else {
		fprintf(fascii, "; Warnung! \n");
		fprintf(fascii, "; %s\n; %s\n", name1, txt);
	}

	j = 0;
	for (i = 0; i <= lgi - 3; i += 3) {
		fprintf(fascii, "G %12.5f %12.5f %12.5f %12.5f %12.5f %12.5f\n",
			gxi[i]*g_dKoeff, gyi[i]*g_dKoeff, 
			gxi[i + 1]*g_dKoeff, gyi[i + 1]*g_dKoeff, 
			gxi[i + 2]*g_dKoeff, gyi[i + 2]*g_dKoeff);
		j += 3;
	}
	if (j == lgi - 2)
		fprintf(fascii, "G %12.5f %12.5f %12.5f %12.5f\n",
			gxi[j]*g_dKoeff, gyi[j]*g_dKoeff, 
			gxi[j + 1]*g_dKoeff, gyi[j + 1]*g_dKoeff);
	else if (j == lgi - 1)
		fprintf(fascii, "G %12.5f %12.5f\n", gxi[j]*g_dKoeff, gyi[j]*g_dKoeff);

	lMCode = -1L;
}

/* Fläche abspeichern */
void save_area(void)
{
long l1, l2, inz[MAXLOCH];
int i, i0, j, k, strt, cont;
double *stx[MAXLOCH];
double *sty[MAXLOCH];
double *px, *py;
double xx;
int len[MAXLOCH];

CComBSTR bstrOut;
os_string strOut;

	USES_CONVERSION;

	ReSeek();

	j = 0;
	cont = 0;
	strt = 1;
	stx[0] = &gxi[0];
	sty[0] = &gyi[0];
	inz[0] = 1;
	for (i = 1; i <= lgi; i++) {
		if ((gxi[i] == gxi[0] && gyi[i] == gyi[0]) && strt == 1) {
			strt = 0;
			len[0] = i + 1;
			l1 = 1;
			l2 = i + 1;
			cont = 1;

			xx = ginhed (gxi, gyi, &l1, &l2);
			if (xx < 0)
				igumoed (gxi, gyi, &l1, &l2);

			if (i < lgi - 1) {
				stx[cont] = &gxi[i + 1];
				sty[cont] = &gyi[i + 1];
				i0 = i + 1;
			}
		} else if (gxi[i] == gxi[0] && gyi[i] == gyi[0]) {
			len[cont] = i - i0;
			if (*stx[cont] == gxi[i - 1] &&
			    *sty[cont] == gyi[i - 1])

				inz[cont] = igppted (stx[cont], sty[cont],
						    gxi, gyi, &l1, &l2);

			else {
				yyerror("\nLoch oder Exklave ohne geschlossene Kontur\n");
				inz[cont] = -2;
			}
			cont += 1;
			if (i < lgi - 1) {
				stx[cont] = &gxi[i + 1];
				sty[cont] = &gyi[i + 1];
				i0 = i + 1;
			}
		}
	}

	lgi = 0;		/* Geometriezähler korrigieren */
	for (i = 0; i < cont; i++) {
		if (inz[i] == 1)
			lgi += len[i];
	}

	if (g_ExtConv) {
		Format (strOut, "F %8ld %s %4ld\n", on, ID, lgi);
		bstrOut = strOut.c_str();

	VARIANT_BOOL fOutput = VARIANT_TRUE;
	CParamArray pars (name1, txt, uident, name4);

		g_ExtConv -> PreOutputObjectStart (on, pars, &bstrOut, &fOutput);
		if (!fOutput)
			return;		// dieses Objekt nicht ausgeben
		fprintf (fascii, OLE2A(bstrOut));

		bstrOut.Empty();
		g_ExtConv -> PostOutputObjectStart (on, &bstrOut);
		if (bstrOut.Length() > 0)
			fprintf (fascii, OLE2A(bstrOut));
	} else 
		fprintf(fascii, "F %8ld %s %4ld\n", on, ID, lgi);

	write_mi (FALSE);		// Merkmale ausgeben

	j = 0;
	for (i = 0; i < cont; i++)
		if (i == 0 || inz[i] == 1) {
			px = stx[i];
			py = sty[i];
			for (k = 0; k < len[i]; k++) {
				if (j == 0)
					fprintf(fascii, "G");
				fprintf(fascii, " %12.5f %12.5f", (*px) * g_dKoeff, (*py) * g_dKoeff);
				px++;
				py++;
				j += 1;
				if (j == 3) {
					j = 0;
					fprintf(fascii, "\n");
				}
			}
		}
	if (j != 0)
		fprintf(fascii, "\n");

	for (i = 1; i < cont; i++) {
		if (inz[i] != 1) {
			on += 1;
			lgi = len[i];

			if (g_ExtConv) {
				Format (strOut, "F %8ld %s %4ld\n", on, ID, lgi);
				bstrOut = strOut.c_str();

			VARIANT_BOOL fOutput = VARIANT_TRUE;
			CParamArray pars (name1, txt, uident, name4);

				g_ExtConv -> PreOutputObjectStart (on, pars, &bstrOut, &fOutput);
				if (!fOutput)
					return;		// dieses Objekt nicht ausgeben
				fprintf (fascii, OLE2A(bstrOut));

				bstrOut.Empty();
				g_ExtConv -> PostOutputObjectStart (on, &bstrOut);
				if (bstrOut.Length() > 0)
					fprintf (fascii, OLE2A(bstrOut));
			} else 
				fprintf(fascii, "F %8ld %s %4ld\n", on, ID, lgi);

			write_mi (FALSE);
			j = 0;
			px = stx[i];
			py = sty[i];
			for (k = 0; k < len[i]; k++) {
				if (j == 0)
					fprintf(fascii, "G");
				fprintf(fascii, " %12.5f %12.5f", (*px) * g_dKoeff, (*py) * g_dKoeff);
				px++;
				py++;
				j += 1;
				if (j == 3) {
					j = 0;
					fprintf(fascii, "\n");
				}
			}
			if (j != 0)
				fprintf(fascii, "\n");
		}
	}

	lMCode = -1L;
}

/* Merkmalssatz, Wertsatz ausgeben */
static char MText[1025];

void write_mi (short TFlag)
{
long MCode;
short MTyp;
short iFlag = FALSE;
short iMoreMKs = FALSE;

// Unique Ident behandeln
	if (TFlag && *uident == '[') strcpy (uident, uident+3);
	if (m_flag) {
		mi_length = strlen (uident);
	// Unique Ident ausgeben
		fprintf (fascii, "M %8ld %4d %c %2d\nW \"%s\"\n", u_code, mi_werte, mi_typ, mi_length, uident);	
	}

// evtl. Name4 behandeln
	if (*name4 != '\0') {		// Name4 gegeben
		mi_length = strlen (name4);
		fprintf (fascii, "M %8ld 1 A %2d\nW \"%s\"\n", name4_code, mi_length, name4);
	}

// zusätzliche Merkmale aus Merkmalsbaum ausgeben
	for (iFlag = ExtractMI (uident, &MCode, &MTyp, MText, sizeof(MText));	// erste MI
	     iFlag;
	     iFlag = NextMI (&MCode, &MTyp, MText, sizeof(MText))	// weitere MI
	    ) 
	{
	// Flag setzen
		iMoreMKs = TRUE;

	// Testen, ob Konflikte möglich sind
		if (MCode == mi_code) {
			fprintf (stderr, "\nObjekt hat zwei Merkmale mit identischem Merkmalscode.\n");
			continue;
		}
		if (MCode == u_code) {
			fprintf (stderr, "\nUnique Ident ist doppelt belegt.\n");
			continue;
		}

	// Ausgeben des MerkmalsSatzes
		switch (MTyp) {
		case 'A':	// TextMerkmal
			{
			char ScopeChar = strchr (MText, '\"') == NULL ? '\"' : '\'';
				
				fprintf (fascii, "M %8ld 1 A %2d\n", MCode, strlen (MText));
				OutMI (ScopeChar, MText, 'W');
			}
			break;

		case 'I':
		case 'F':
			fprintf (fascii, "M %8ld 1 %c %2d\nW %s\n", MCode, MTyp, strlen (MText), MText);
			break;
		}
	}

// reguläres Merkmal ausgeben
	mi_length = strlen (txt);
	if (!TFlag && (mi_length != 0 && (!nomk_flag || (nomk_flag && !iMoreMKs)))) 
	{
		if (mi_typ == 'A') {
		// Text in "..." ausgeben
		char ScopeChar = strchr (txt, '\"') == NULL ? '\"' : '\'';

			fprintf(fascii, "M %8ld %4d %c %2d\n", mi_code, mi_werte, mi_typ, mi_length);
			OutMI (ScopeChar, txt, 'W');
		} else {
			fprintf(fascii, "M %8ld %4d %c %2d\nW %s\n", mi_code, mi_werte, mi_typ, mi_length, txt);
		}
	}

// bei Bedarf Relation zu Begleitobjekt generieren
	if (bo_flag) {		
		bo_flag = FALSE;
		fprintf (fascii, "R B %ld\n", Znr);
	}
}

/* Objekt neu initialisieren */
void init_new_object (void)
{
	if (gxi != NULL) free(gxi);
	if (gyi != NULL) free(gyi);

// Speicher anfordern
	gxi = (double *) calloc(abs(koord_paare), sizeof(double));
	gyi = (double *) calloc(abs(koord_paare), sizeof(double));

	if (gxi == NULL || gyi == NULL) {
	// Fehler - kein Speicherplatz
		yyerror("Kein Speicherplatz.");
		abort();
	}
	lgi = -1;		/* noch keine Geometrie gelesen */
}

void yyerror (char *Text)
{
	fprintf(stderr, "%s\n", Text);
}


#define MAXMILINELEN	75

void OutMI (short cScope, char *pMText, int iFrstChar)
{

	if (strlen (pMText) < MAXMILINELEN)
		fprintf (fascii, "%c %c%s%c\n", iFrstChar, cScope, pMText, cScope);
	else {
	char *cptr = pMText;
	short iRestLen = strlen (cptr);		// RestLänge des Strings
	char format[20];
	int cFChar = iFrstChar;

		while (iRestLen > 0) {
		short iCnt = __min (MAXMILINELEN, iRestLen);	// aktuelle Länge der Zeile

			sprintf (format, "%%c %%c%%-%d.%ds%%c\n", iCnt, iCnt);
			fprintf (fascii, format, cFChar, cScope, cptr, cScope);
			cFChar = 'W';	// FolgeZeilen immer 'W'

			cptr += iCnt;	// nächstes ZeilenStück
			iRestLen = strlen (cptr);
		}
	}
}


// Test, ob bestimmter MerkmalsCode an diesem Objekt vertreten ist ------------
int hasMCode (long lCode)
{
long lLocMCode;
short MTyp;
short iFlag = FALSE;

// Unique Ident testen
	if (m_flag && lCode == u_code) return TRUE;

// evtl. Name4 behandeln
	if (*name4 != '\0' && lCode == name4_code) return TRUE;

// zusätzliche Merkmale aus Merkmalsbaum ausgeben
	if (*uident == '[') strcpy (uident, uident+3);
	for (iFlag = ExtractMI (uident, &lLocMCode, &MTyp, MText, sizeof(MText));	// erste MI
	     iFlag;
	     iFlag = NextMI (&lLocMCode, &MTyp, MText, sizeof(MText))	// weitere MI
	    ) 
	{
		if (lCode == lLocMCode) return TRUE;
	}

// reguläres Merkmal testen
	if (mi_code == lCode) return TRUE;

return FALSE;
}

void ReSeek (void)
{
	if (lMCode != -1L) {
	// vorhergehendes Objekt war '[P]' (indirektes Textobjekt)
		if (!hasMCode (lMCode))	{	// zurückpositionieren
			fseek (fascii, lLastPos, SEEK_SET);
			bo_flag = FALSE;
			on--;
		}
	}
}
