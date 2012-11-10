// Ausgabe der Felder des AascParsers als BNA-File ----------------------------
// File: PUTBNA.C

#include "StdAfx.h"

#include "ascbna.h"
#include "ascerrs.h"

#include "input.h"

#include "CoordSystems.h"

static long iObjCnt = 0;

char *GetMText (long *, char *, long, short *);
void OutputGIPunkt (double *gxi, double *gyi);
void OutputGIText (double *gxi, double *gyi);
void OutputGILinie (long lgi, double *gxi, double *gyi);
long CorrectGIFlaeche (long lgi, double *gxi, double *gyi);
long InsertToField (long, long, double *, double *, double, double);
void OutputMKL (char *, long *);
char *FindMWert (long *, long, short *);

extern int d_flag;

void putbna (char *cbOKS, long *sta, long *mi, long lgi, double *gxi, double *gyi)
{
// ggf. Koordinatentransformation durchführen
	if (g_CoordSys.IsValid()) 
		g_CoordSys.Transform (lgi, gxi, gyi);

// Ausgabe des BNA Objektes
char cUIdent[512];
char pMText[512];
char pName4[512];

char s;
char *cptr;
short iLen;

char pIdent[40];

	++iObjCnt;
	if (lUIdent != -1L && (cptr = FindMWert (mi, lUIdent, &iLen))) {
 	// MCode und MWert gegeben 
		strncpy (cUIdent, cptr, iLen);
		cUIdent[iLen] = '\0';
	} else
		sprintf (cUIdent, "%s_%d", UIdent, iObjCnt);
	
	if (sta[1] == O_TEXTOBJEKT || sta[1] == O_TEXTOBJIND) 
	// Text unter TEXTOBJMCODE suchen
		cptr = GetMText (mi, cUIdent, -1 == lMCode ? TEXTOBJMCODE : lMCode, &iLen);
	else 
		cptr = GetMText (mi, cUIdent, lMCode, &iLen);

// evtl. Name4 setzen
LPCSTR pcName4 = NULL;

	if (Name4Code != -1L && (pcName4 = FindMWert (mi, Name4Code, &iLen))) {
		strncpy (pName4, pcName4, iLen);
		pName4[iLen] = '\0';
	} else if (i_flag) {
//		ultoa (id, pName4, d_flag ? 10 : 16);
		strcpy (pName4, cbOKS);
	} else
		pName4[0] = '\0';

	s = strchr (pMText, '\"') ? '\'' : '\"';

	if (-iLen == sizeof(long)) 	// O_TEXTOBJIND
		ltoa (*(long *)cptr, pMText, 10);
	else {
		strncpy (pMText, cptr, iLen);
		pMText[iLen] = '\0';
	}
	
// evtl. MerkmalsDatei ausgeben
	if (fpmkl && mi[1] > 0)
		OutputMKL (cUIdent, mi);

	if (!s_flag) {
		fprintf (stderr, "Objekt:    %ld\r", iObjCnt);
		fflush (stderr);
	}

//	if (d_flag) 
//		ltoa (id, pIdent, 10);
//	else {
//		strcpy (pIdent, "0x");
//		ultoa (id, &pIdent[2], 16);
//	}

	if (!d_flag)
		strcpy (pIdent, "0x");
	else	
		pIdent[0] = '\0';
	strcat (pIdent, cbOKS);

	switch (sta[1]) {
	case O_PUNKT:
		if (pName4[0]) {		// Name4 existiert
		char s4 = strchr (pName4, '\"') ? '\'' : '\"';
		
			fprintf (fpout, "\"%s\",%c%s%c,\"%s\",%c%s%c,1\n", 
					pIdent, s, pMText, s, 
					cUIdent, s4, pName4, s4);
		} else {
			fprintf (fpout, "\"%s\",%c%s%c,\"%s\",1\n", pIdent, 
					s, pMText, s, cUIdent);
		} 
		OutputGIPunkt (gxi, gyi);
		break;

	case O_TEXTOBJEKT:
		if (!t_flag) break;
		if (pName4[0]) {		// Name4 existiert
		char s4 = strchr (pName4, '\"') ? '\'' : '\"';
		
			fprintf (fpout, "\"%s\",%c%s%c,\"%s%s\",%c%s%c,1\n", 
					pIdent, s, pMText, s, b_flag ? "[B]" : "[T]",
					cUIdent, s4, pName4, s4);
		} else {
			fprintf (fpout, "\"%s\",%c%s%c,\"%s%s\",1\n", 
					pIdent, s, pMText, s, 
					b_flag ? "[B]" : "[T]", cUIdent);
		}
		OutputGIText (gxi, gyi);
		break;

	case O_TEXTOBJIND:
		if (!t_flag) break;
		if (pName4[0]) {		// Name4 existiert
		char s4 = strchr (pName4, '\"') ? '\'' : '\"';
		
			fprintf (fpout, "\"%s\",%c%s%c,\"[P]%s\",%c%s%c,1\n", 
					pIdent, s, pMText, s, 
					cUIdent, s4, pName4, s4);
		} else {
			fprintf (fpout, "\"%s\",%c%s%c,\"[P]%s\",1\n", 
					pIdent, s, pMText, s, cUIdent);		
		}
		OutputGIText (gxi, gyi);
		break;

	case O_LINIE:
		if (pName4[0]) {		// Name4 existiert
		char s4 = strchr (pName4, '\"') ? '\'' : '\"';
		
			fprintf (fpout, "\"%s\",%c%s%c,\"%s\",%c%s%c,-%ld\n", 
					pIdent, s, pMText, s, 
					cUIdent, s4, pName4, s4, lgi);
		} else {
			fprintf (fpout, "\"%s\",%c%s%c,\"%s\",-%ld\n", 
					pIdent, s, pMText, s, cUIdent, lgi);
		}
		OutputGILinie (lgi, gxi, gyi);
		break;

	case O_FLAECHE:
		lgi = CorrectGIFlaeche (lgi, gxi, gyi);
		if (pName4[0]) {		// Name4 existiert
		char s4 = strchr (pName4, '\"') ? '\'' : '\"';
		
			fprintf (fpout, "\"%s\",%c%s%c,\"%s\",%c%s%c,%ld\n", 
					pIdent, s, pMText, s, 
					cUIdent, s4, pName4, s4, lgi);
		} else {
			fprintf (fpout, "\"%s\",%c%s%c,\"%s\",%ld\n", 
					pIdent, s, pMText, s, cUIdent, lgi);
		}
		OutputGILinie (lgi, gxi, gyi);
		break;
	}
}

char *GetMText (long *MInfo, char *pUIdent, long lMCode, short *iLen)
{
char *cptr;
long *pMK = &MInfo[2];	// erstes Merkmal

	if (lMCode != -1L && (cptr = FindMWert (MInfo, lMCode, iLen)))
		return cptr;

	*iLen = 0;
	while (pMK < &MInfo[MInfo[1] + 2]) {	// alle Merkmale ausgeben
		if (pMK[0] != 0) { 	// erstes Merkmal gefunden
			if (!a_flag) pMK[0] = 0;
			*iLen = (short)(pMK[2]*sizeof(long));
			return (char *)&pMK[3];
		}
		if (pMK[2] == -1)	// O_TEXTOBJIND
			pMK = &pMK[4];
		else
			pMK = &pMK[pMK[2] + 3];
	}
	*iLen = strlen (pUIdent);

return pUIdent;
}

void OutputGIPunkt (double *gxi, double *gyi)
{
	fprintf (fpout, "%lf,%lf\n", *gxi, *gyi);
}

void OutputGIText (double *gxi, double *gyi)
{
	fprintf (fpout, "%lf,%lf\n", *gxi, *gyi);
}

void OutputGILinie (long lgi, double *gxi, double *gyi)
{
long i;

	for (i = 0; i < lgi; i++)
		fprintf (fpout, "%lf,%lf\n", gxi[i], gyi[i]);
}

// korrigieren der InnenKonturen für BNA-Format -------------------------------
long CorrectGIFlaeche (long lgi, double *gxi, double *gyi)
{
double ExtX = -1.0, ExtY = -1.0;
double IntX = -1.0, IntY = -1.0;
long i;

	ExtX = gxi[0];
	ExtY = gyi[0];
	for (i = 0; i < lgi; i++) {
		if (i > 0 && i < lgi -1 && gxi[i] == ExtX && gyi[i] == ExtY) {
		// Beginn einer InnerKontur
			IntX = gxi[++i];
			IntY = gyi[i];
		} else if (gxi[i] == IntX && gyi[i] == IntY) {
		// Ende einer InnenKontur
			lgi = InsertToField (i + 1, lgi, gxi, gyi, ExtX, ExtY);
			IntX = 0.0; 	// keine InnenKontur mehr
			IntY = 0.0;
		}
	}

return lgi;
}

long InsertToField (long iIndex, long lgi,
		    double *gxi, double *gyi, 
		    double newX, double newY) 
{
long i;

	for (i = lgi; i > iIndex; i--) {
		gxi[i] = gxi[i - 1];
		gyi[i] = gyi[i - 1];
	}
	gxi[iIndex] = newX;
	gyi[iIndex] = newY;

return lgi + 1;
}

char myOutBuff[512];

void OutputMKL (char *pUIdent, long *MInfo)
{
long *pMK = &MInfo[2];	// erstes Merkmal

	while (pMK < &MInfo[MInfo[1] + 2]) {	// alle Merkmale ausgeben
		if (pMK[0] != 0) {	// noch nicht ausgegeben
			memset (myOutBuff, '\0', sizeof(myOutBuff));
			strncpy (myOutBuff, (char *)&pMK[3], (short)(pMK[2]*sizeof(long)));
			myOutBuff[pMK[2]*sizeof(long)] = '\0';
			fprintf (fpmkl, "%s,%d,A,%s\n", pUIdent, pMK[0], myOutBuff);
		}
		pMK = &pMK[pMK[2] + 3];
	}
}

char *FindMWert (long *MInfo, long MCode, short *iLen)
{
long *pMK = &MInfo[2];	// erstes Merkmal

	*iLen = 0;
	while (pMK < &MInfo[MInfo[1] + 2]) {	// alle Merkmale ausgeben
		if (pMK[0] == MCode) {	// MCode gefunden
			if (!a_flag) pMK[0] = 0;	// MWert bereits ausgegeben
			*iLen = (short)(pMK[2]*sizeof(long));
			return (char *)&pMK[3];
		}
		if (pMK[2] == -1) // O_TEXTOBJIND
			pMK = &pMK[4];
		else
			pMK = &pMK[pMK[2] + 3];
	}

return NULL;
}
