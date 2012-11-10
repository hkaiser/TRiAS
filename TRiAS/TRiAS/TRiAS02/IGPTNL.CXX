/*Translated by FOR_C, v3.1, on 02/25/91 at 10:13:24 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *                                                       ### IGPTNL  ###
 *       *****************************************************************
 *       *        Inzidenztest Testpunkt - Polygon  mit Nachladen        *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, Bereich 2
 *       Dokumentationsnummer: AD-610-A64519
 *       Autor:                Dr. Oppitz, K.        
 *       Version:              30-6/14-8/29-9-89/17-5-90-IGPTNL
 *       Modulname:            *** IGPTNL ***
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       SYSLIB.OLB:           
 *       DBN.OLB:              IGLAGE
 *       -----------------------------------------------------------------
 *       Aufruf:               I=IGPTNL(XP,YP,X,Y,L,IST)
 *
 *       Aufrufparameter:      
 *         XP,YP -- Koordinaten des Testpunkts, I*4
 *         IST   -- Steuerparameter, I*4
 *
 *         IST>0   -- Inzidenztest ohne Nachladen des Polygonzugs:
 *         (X(1),Y(1),...,(X(L-1),Y(L-1)) -- Koordinaten der Eckpunkte des
 *                                           Polygonzugs in mathematisch
 *                                           positiver Orientierung, I*4
 *         X(L)=X(1), Y(L)=Y(1)
 *
 *         IST<=0  -- Inzidenztest mit Nachladen des Polygonzugs: 
 *                    (geschlossener Polygonzug, mathematisch positiv
 *                    orientiert)
 *         IST= 0  -- (X(1),Y(1),...,X(L),Y(L)) -- Koordinaten der Eck-
 *                    punkte P1,...,Pl des ersten Segments des Polygonzugs
 *                    (erster IGPTNL-Aufruf)
 *         IST=-1  -- (X(1),Y(1),...,X(L'),Y(L')) -- Koordinaten der Eck-
 *                    punkte Pl+1,...,Pl+l' des folgenden Segments des 
 *                    Polygonzugs (und falls erforderlich, weiterer Folge-
 *                    segmente), aber nicht des letzten Segments
 *                    (Folgeaufruf von IGPTNL, weiteres Nachladen 
 *                    erforderlich)
 *         IST=-2  -- (X(1),Y(1),...,X(L"),Y(L")) -- Koordinaten der Eck-
 *                    punkte Pn+1,...,Pn+l" des letzten Segments des 
 *                    Polygonzugs, dabei muss Pn+l" = (X(L"),Y(L")) = P1 
 *                    gelten (Polygonzuganfangspunkt = -endpunkt),
 *                    (Folgeaufruf von IGPTNL, kein weiteres Nachladen
 *                    erforderlich)
 *
 *         L     -- aktuelle Laenge der Felder X(*),Y(*), I*4
 *
 *       Rueckkehrparameter:
 *         IGPTNL = -1 -- Testpunkt liegt nicht im vom Polygonzug umschlos-
 *                        senen Gebiet und inzidiert nicht den Polygonzug
 *         IGPTNL =  0 -- Testpunkt inzidiert Polygonzug
 *         IGPTNL = +1 -- Testpunkt liegt im vom Polygonzug umschlossenen
 *                        Gebiet
 *         IST    = -1 -- nach IGPTNL-Aufruf mit IST =  0
 *         IST    =  0 -- nach IGPTNL-Aufruf mit IST = -2
 *
 *       Aufgabenstellung:
 *         IGPTNL ermittelt die Inzidenzcharakteristik des Testpunkts P
 *         bezueglich eines von einem geschlossenen, mathematisch positiv
 *         orientierten Polygonzugs umschlossenen Gebiets
 *         Voraussetzung: der Polygonzug ist eine geschlossene, doppel-
 *         punktfreie und orientierbare Kurve in einem ## Rechtssystem ##
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

long FUNCTYPE igptnl (long *xp, long *yp, long *x, long *y, long *l, long *ist)
{
long int i = 0, idi, igptnl_v, j, nx, f_l_;
static long int idf = 0,
		idx = 0,
		igpth = 0,
		x0 = 0,
		xs0 = 0,
		xs1 = 0,
		xs2 = 0,
		xv = 0,
		y0 = 0,
		ys0 = 0,
		ys1 = 0, 
		ys2 = 0,
		yv = 0;

	if (*ist >= 0L) {
		igptnl_v = -1L;		// X-Komponente naechstgelegener SP
		idx = 0x7FFFFFFF;	// Index naechstgelegener SP 
		idi = 0L;		// Index aktueller SP 
	}
		
	if (*ist < 0L) {
	// Polygonzug nachgeladen
		igptnl_v = igpth;
		if (y0 - *yp < 0L)  goto L_100;
		if (y0 - *yp > 0L)  goto L_300;
		if (x0 - *xp < 0L)  goto L_600;
		if (x0 - *xp == 0L) goto L_700;
		if (x0 >= idx)      goto L_600;

	// P0 neuer naechstliegender SP
		idx = x0;

	// Flag SP ermittelt setzen 
		idf = 1L;
		xs0 = xv;
		ys0 = yv;
		xs1 = x0;
		ys1 = y0;
		xs2 = x[0L];
		ys2 = y[0L];
	}

L_600:
	if (++i > *l) goto L_500;	// Endetest 
	
// Lagetest EP(I) zur x-achsenparallelen Geraden gx 
L_601:
	switch (IARITHIF(y[i - 1L] - *yp)){
	case -1: goto L_100;
	case  0: goto L_200;
	case  1: goto L_300;
	}


/* -- unterhalb gx */
L_100:
	if (++i > *l) goto L_500;	// Endetest

// Lagetest EP(I) zu gx 
	switch (IARITHIF(y[i - 1L] - *yp)){
	case -1: goto L_100;
	case  0: goto L_200;
	case  1: goto L_400;
	}

// EP(I) auf gx, Lagetest EP(I) auf Strahl, Lagetest EP(I) zu XP 
L_200:
	switch (IARITHIF(x[i - 1L] - *xp)){
	case -1: goto L_600;
	case  0: goto L_700;
	case  1: goto L_201;
	}

// SP rechts von IDI
L_201:
	if (x[i - 1L] >= idx) goto L_600;
	if (*ist <= 0L) {
		idf = 1L;	// Flag SP gefunden setzen
		if (i <= 1L) {
			if(*ist >= 0L)
				idf = 2L;	// XS0, YS0 nicht belegt
			else {
				xs0 = x0;
				ys0 = y0;
			}
		}
		else {
			xs0 = x[i - 2L];
			ys0 = y[i - 2L];
		}
		xs1 = x[i - 1L];
		ys1 = y[i - 1L];
		xs2 = x[i];
		ys2 = y[i];
	}

// SP(I) neuer naechstgelegener SP
	idx = x[i - 1L];
	idi = i;
	goto L_600;

// oberhalb gx
L_300:
	if (++i > *l) goto L_500;	// Endetest

// Lagetest EP(I) zu gx
	switch (IARITHIF (y[i - 1L] - *yp)) {
	case -1: goto L_400;
	case  0: goto L_200;
	case  1: goto L_300;
	}

// Schnitt mit gx, Lagetest SP auf Strahl, Y(I-1)#YP#Y(I)
L_400:
	if (i > 1) {
		if (x[i - 2L] < x[i - 1L]) {
		// SP nicht naechstgel.
			if (x[i - 1L] <= *xp || x[i - 2L] >= idx)
				goto L_601;
		}
		else {
		///  SP nicht naechstgel.
			if (x[i - 2L] < *xp || x[i - 1L] > idx)
				goto L_601;
		}

	// SP berechnen und Lagetest, Y(I)#Y(I-1)
		nx = long((double(x[i - 2L]) * double(y[i - 1L] - *yp) - 
			   double(x[i - 1L]) * double(y[i - 2L] - *yp)) / 
			  (double(y[i - 1L] - y[i - 2L])));
	}
	else {
		if (x0 < x[0L]) {
		// SP nicht naechstgel.
			if (x[0L] <= *xp || x0 >= idx)
				goto L_601;
		}
		else {
		// SP nicht naechstgel.
			if (x0 < *xp || x[0L] > idx)
				goto L_601;
		}

	// SP berechnen und Lagetest, Y(1)#Y0 
		nx = long ((double(x0) * double(y[0L] - *yp) - 
			    double(x[0L]) * double(y0 - *yp)) /
			   (double(y[0L] - y0)));
	}
	switch (IARITHIF(nx - *xp)) {
	case -1: goto L_601;
	case  0: goto L_700;
	case  1: goto L_401;
	}

// SP rechts von IDI
L_401:
	if (nx >= idx) goto L_601;
	if (*ist <= 0L) {
		idf = 1L;	// Flag SP gefunden setzen
		if (i <= 1L) {
			if (*ist >= 0L)
				idf = 2L;	// XS0,YS0 nicht belegt
			else {
				xs0 = x0;
				ys0 = y0;
			}
		}
		else {
			xs0 = x[i - 2L];
			ys0 = y[i - 2L];
		}
		xs1 = x[i - 1L];
		ys1 = y[i - 1L];
		xs2 = x[i];
		ys2 = y[i];
	}

// SP ist neuer naechstgelegener SP
	idx = nx;
	idi = i;
	goto L_601;

// abschlieﬂender Inzidenztest
L_500:
	if (*ist <= -2L) {
		*ist = 0L;
	
		if(idf <= 0L)	goto L_799;	// kein SP
		if(idf >= 2L) {
		// PS belegen 
			xs0 = x[*l - 2L];
			ys0 = y[*l - 2L];
		}
	
		if (ys1 != *yp) {
		// SP kein Polygoneckpunkt
			igptnl_v = iglage (xp, yp, &xs0, &ys0, &xs1, &ys1);
			goto L_799;
		}

	// Lage P zu STR(I-1,I)
		i = iglage (xp, yp, &xs0, &ys0, &xs1, yp);

	// Lage P zu STR(I,I+1)
		igptnl_v = iglage (xp, yp, &xs1, yp, &xs2, &ys2);
		if (iglage (&xs2, &ys2, &xs0, &ys0, &xs1, yp) >= 0L) {
		// konvexe Ecke
			if (i < igptnl_v) igptnl_v = i;
		}
		else {
		// konkave Ecke */
			if (i > igptnl_v) igptnl_v = i;
		}
		goto L_799;
	}
	if (*ist <= 0L) {
		*ist = -1L;
		xv = x[*l - 2L];
		yv = y[*l - 2L];
		x0 = x[*l - 1L];
		y0 = y[*l - 1L];
		goto L_799;
	}

// keine Inzidenz Strahl - Polygonflaeche 
	if (idi <= 0L) goto L_799;

// SP kein Polygoneckpunkt
	if (y[idi - 1L] != *yp) {
		igptnl_v = iglage (xp, yp, &x[idi - 2L], &y[idi - 2L], 
				   &x[idi - 1L], &y[idi - 1L]);
		goto L_799;
	}
	j = idi - 1L;

// SP ist Polygonendpunkt
	if (j <= 0L) j = *l - 1;

// Lage P zu STR(I-1,I)
	i = iglage (xp, yp, &x[j - 1L], &y[j - 1L], &x[idi - 1L], yp);

// Lage P zu STR(I,I+1)
	igptnl_v = iglage (xp, yp, &x[idi - 1L], yp, &x[idi], &y[idi]);

	if(iglage (&x[idi], &y[idi], &x[j - 1L], &y[j - 1L], 
		   &x[idi - 1L], yp) >= 0L) 
	{
	// konvexe Ecke
		if (i < igptnl_v) igptnl_v = i;
	}
	else {
	// konkave Ecke 
		if (i > igptnl_v) igptnl_v = i;
	}
	goto L_799;

// SP auf Polygonzug
L_700:
	igptnl_v = 0L;
	if (*ist < 0L) *ist = 0L;

L_799:
	igpth = igptnl_v;
	return( igptnl_v );
}


