#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "dbversio.h"

#define MAXLINE 128
#define MAXRECORD 1024
#define TRUE (1)
#define FALSE (0)

#define UGH 5000000.0
#define OGH 6900000.0
#define UGR 1000000.0
#define OGR 6000000.0

#define FUNCTYPE _cdecl

char fnin[MAXLINE] = { '\0' };       /*BNA-Input */
char ascii[MAXLINE] = { '\0' };      /*BNA-Output */

char line[MAXRECORD];


FILE *fascii = NULL;                   /* ATLAGIS-Outputdatei */


FILE *yyin = NULL;      		/* Eingabedatei ATLAS */

static char titel[] = "Gauﬂ-Kr¸ger-Koordinatentransformation im BNA-File";

static char *usage[] = {
	"Verwendung: tragk [options] [atlas_ascii_input] [atlas_ascii_output]\n",
	"Options: -i\tInput (default=[K]rassowski) ,\n",
	"\t -o\tOutput (default=[B]essel),\n",
	"\t -mint_zahl\t[M]ittelmeridian Input (default=15),\n",
	"\t -nint_zahl\tMittelmeridia[n] Output,\n",
	"\t -sint_zahl\t[S]treifenbreite Input ( default=6),\n",
	"\t -eint_zahl\tStreifenbreit[e] Output,\n",
	"\t -g\t Ausgabe geogr. Koord. [ solo in stdout],\n",
	"\t -d\t Zwischendrucke\n",
	"\t -r\t Rohdaten\n",
	"\t -h\tKoord in Hochwert,Rechtswert (default:R,H)\n",
	NULL,
};

static char *no_open = "Kann %s \'%s\' nicht erˆffnen\n";

int s_flag = FALSE;     /* keine Ausgaben auf stdout */
int i_flag = TRUE;      /* Krassowski-Eingabe */
int ig_flag = TRUE;	/* Input nicht geodÑtisch */
int o_flag = FALSE;     /* Bessel- Ausgabe */
int og_flag = TRUE;	/* Output nicht geodÑtisch */
int t_flag = FALSE; 	/* Transf. von Krassowski in Bessel */
int h_flag = FALSE;	/* Koord.Eingabe Rechtswert,Hochwert */
int g_flag = FALSE;	// Keine geog. Koo
int r_flag = TRUE;	// Keine Rohdaten
int d_flag = FALSE;	// Keine Zwischendrucke
int u_flag = FALSE;	// Keine alten Daten mit Kz U
int k_flag = FALSE;	// Keine alten Daten mit Kz K
int y_flag = FALSE;	// Keine Differenzen

//-------------- UTM einbinden--------------------------

int utmi_flag = FALSE;
int utmo_flag = FALSE;

//-------------------------------------------------------

int Min=15,Mout,Sin=6,Sout;

static char t1[]="Krassowski";
static char t2[]="Bessel";
static char t21[]="UTM";
static char t3[]="- geod‰tisch";


//Prototypen
void FUNCTYPE gaugeo (long double, long double, int , int , long double , long double , long double *, long double *);
void FUNCTYPE geogau (long double, long double, int , int , long double , long double , long double *, long double *);
void FUNCTYPE modko_B ( long double , long double , long double *, long double *);
//void FUNCTYPE modko_K ( long double , long double , long double *, long double *);
int FUNCTYPE kootst ( int, long double , long double );
void print_usage (void);
void command_line (int argc, char **argv);
void ascii_open (void);                  /* ATLASGIS-Outputdatei eroeffnen */
void atlasgis_open (void);               /* ATLASGIS-Inputdatei eroeffnen */
void print_titel ( char*);





void main (int argc,char **argv)
{

	long double hain,hbin,haout,hbout,hab,hbb,hak,hbk;
	long NR=0L;
	long double h,r;
	long double uh,ur;
	long double kh,kr;

	char C;
	long double Hwert,Rwert,dHwert,dRwert,Laenge,Breite;
	int l0,strbr,rc;
	char *aptr;

	fascii = stdout;
	yyin = stdin;

	command_line (argc, argv);      /* Kommandozeile auswerten */
	ascii_open ();                  /* ATLASGIS-Outputdatei eroeffnen */
	atlasgis_open ();               /* ATLASGIS-Inputdatei eroeffnen */
	fprintf (stderr, "; %s - %s%s %s\n", Copyright, Version, Release, Date);
	print_titel (titel);
//-------------------------------------------------------------------------------
//	Test der Parameter

	if ( Sin != 3 && Sin != 6 )  {
		fprintf (stderr," * Falsche Eingabe-Streifenbreite \n");
		exit (1);
		}
	if ( Sout != 3 && Sout != 6 )  {
		fprintf (stderr," * Falsche Ausgabe-Streifenbreite \n");
		exit (1);
		}
	if ( Min != 6 && Min != 9 && Min != 12 && Min != 15 ) {
		fprintf (stderr," * Falscher Eingabe-Mittelmeridian \n");
		exit (1);
		}
	if ( Mout != 6 && Mout != 9 && Mout != 12 && Mout != 15 ) {
		fprintf (stderr," * Falscher Ausgabe-Mittelmeridian \n");
		exit (1);
		}

//   Umwandlung von Koordinaten


//   UTM??????
	Laenge=0.0;
	Breite=0.0;
//Halbachsen
	hab=6377397.155;
	hbb=6356078.96325;
	hak=6378245.0;
	hbk=6356863.01877;
	if (i_flag) {
		hain=hak;
		hbin=hbk;
		}
	else {
		hain=hab;
		hbin=hbb;
//		Eingabe Bessel-Ausgabe Krassowski
		if (o_flag) t_flag = TRUE ;
	}

			
	if ( o_flag ) {	// Ausgabe in Krassovski
		haout=hak;
		hbout=hbk;
	} else {
		haout=hab;	// Ausgabe in Bessel
		hbout=hbb;
	}



	while ( fgets(line, sizeof(line), yyin) != NULL ) {

		register char *cptr = line;
                switch ( *cptr ) {
// 		Doppeln uninterressanter SÑtze

		case ';': case 'T':
		case 'M': case 'W': case 'R': case 'E': 
		fprintf (fascii,"%s",line);
		break;
		case 'U':
//	Eingabe Rechtswert,Hochwert
		sscanf(line,"%c %lf,%lf",&C,&ur,&uh);
		fprintf (fascii,"%s",line);
		break;
		case 'K':
//	Eingabe Rechtswert,Hochwert
		sscanf(line,"%c %lf,%lf",&C,&kr,&kh);
		fprintf (fascii,"%s",line);
		break;
		case 'D': case 'Z':
		fprintf (fascii,"%s",line);
		break;
		case '"': case 'P': case 'L': case 'F':
		ur = 0.0;
		uh = 0.0;
		kr = 0.0;
		kh = 0.0;
		fprintf (fascii,"%s",line);
		if ( g_flag ) printf ( "%s",line);
		NR++;
		aptr = strchr(line,'\n');
		if ((aptr = strchr ( line , '\n' )) != NULL )
			*aptr = '\0' ;
		fprintf (stderr,"Objekt %6ld %-60.60s\r",NR,line);
		fflush (stderr);
		break;
//
//------------------------------------------------------------------------
//	Verarbeitung der DatensÑtze
//------------------------------------------------------------------------
		default :
		h=0.0,
		r=0.0;
		Laenge=0.0;
		Breite=0.0;

		if ( ig_flag ) {		// Angabe Hochwert,Rechtswert
			if ( h_flag )
	//	Eingabe Hochwert,Rechtswert  
				sscanf(line,"%lf,%lf",&h,&r);
			else	
	//	Eingabe Rechtswert,Hochwert
				sscanf(line,"%lf,%lf",&r,&h);
		} else {
	//	Eingabe geodÑtische Koordinaten
			sscanf(line,"%lf,%lf",&Laenge,&Breite);
		}

 //	zuordnen strbr und l0
		strbr=Sin;
		l0=Min;

		if ( u_flag ) 
			fprintf (fascii,"U %12.5lf,%12.5lf\n",r,h);

		if ( k_flag ) 
			fprintf (fascii,"K %12.5lf,%12.5lf\n",r,h);

		Hwert=h;
		Rwert=r;

		if ( ig_flag ) {
			rc = FALSE;
//	Test auf falsche Koordinaten
			if ( !utmi_flag )  {		// keine UTM-Daten
				rc=kootst ( i_flag, h , r ) ;
				if ( rc ) {
					fprintf (fascii," * Koord. falsch : %lf,%lf\n",r,h);
					break;
				}
			}		
//		Umwandlung GAU·-KrÅger in geodÑtisch !!!

//			gaugeo(hain,hbin,strbr,l0,Hwert,Rwert,&Breite,&Laenge);

//		Breite,LÑnge fÅr Absolutwerte !!!


//----------------	éNDERUNG 1.2.94	------------------------
//	Anbringen der Korrekturen an Koordinaten

		//	gilt nicht fÅr UTM-----------------------
			if ( !utmo_flag ) {

		//	Wechsel zwischen Bessel-Krassovski oder umgekehrt
				if ( i_flag != o_flag )  {
					if ( t_flag) {	// Bessel in Krassovski
					   gaugeo(hain,hbin,strbr,l0,Hwert,Rwert,&Breite,&Laenge);
					   modko_B ( Breite,Laenge,&dHwert,&dRwert);

					   if ( r_flag ) {
						Hwert=Hwert+dHwert;
						Rwert=Rwert+dRwert;
					   }

					}
				
				  	if ( d_flag ) 
						fprintf (fascii,"\t%12.5lf+%12.5lf,%12.5lf+%12.5lf\n",r,dRwert,h,dHwert);
					if ( u_flag ) 
						fprintf (fascii,"D %12.5lf,%12.5lf\n",dRwert,dHwert);

	//		Umwandlung GAU·-KrÅger in geodÑtisch !!!
	//		diesmal mit korrigierten HW,RW in Ausgabe-Ellipsoid
	//		aber gleiche Streifenbreite

					if ( t_flag ) 	// Bessel zu Krassovski
			 		  gaugeo(haout,hbout,strbr,l0,Hwert,Rwert,&Breite,&Laenge);
					else
			 		  gaugeo(hain,hbin,strbr,l0,Hwert,Rwert,&Breite,&Laenge);

				} else
					gaugeo(hain,hbin,strbr,l0,Hwert,Rwert,&Breite,&Laenge);

			}

//------------------------neu 1.2.94---------------------------------------

		}	// Ende ig_flag ( Verarbeitung HW,RW)

//
//		Ausgabe in geog.KOO
		if ( g_flag ) printf ("%12.5f,%12.5f\n",Laenge,Breite);
		strbr=Sout;
		l0=Mout;

	//	Nun von geodÑtisch in GK mit neuer Streifenbreite auf Ausgabeellipsoid
		if ( i_flag != o_flag ) {
		   if ( t_flag) 
			geogau(haout,hbout,strbr,l0,Breite,Laenge,&Hwert,&Rwert);
		   else {	// Krassovski in Bessel
			geogau(hain,hbin,strbr,l0,Breite,Laenge,&Hwert,&Rwert);
			gaugeo(haout,hbout,strbr,l0,Hwert,Rwert,&Breite,&Laenge);
		   	modko_B ( Breite,Laenge,&dHwert,&dRwert);
		   	if ( r_flag ) {
				Hwert=Hwert-dHwert;
				Rwert=Rwert-dRwert;
		   	}
		   }
		} else
			geogau(haout,hbout,strbr,l0,Breite,Laenge,&Hwert,&Rwert);

		h=Hwert;
		r=Rwert;
		if ( y_flag ) {
			if ( ur != 0.0) {
				ur = ur -r;
				uh = uh -h;
				fprintf (fascii,"Z %12.5lf,%12.5lf\n",ur,uh);
			}
			if ( kr != 0.0) {
				kr = kr -r;
				kh = kh -h;
				fprintf (fascii,"Y %12.5lf,%12.5lf\n",kr,kh);
			}
		}

		if ( og_flag )
			fprintf (fascii,"%12.5lf,%12.5lf\n",r,h);
		else {
//	zurÅck in geod.Koordinaten

			gaugeo(haout,hbout,strbr,l0,h,r,&Breite,&Laenge);
			fprintf (fascii,"%lf,%lf\n",Laenge,Breite);
		}
		break;
              }
	}
//------------------------------------------------------------------------------
	fclose (fascii);                /* ATLASGIS-Austauschdatei schliessen */


	fprintf (stderr, "\n\n--- Transformation ");
	if ( i_flag ) {
		fprintf (stderr, " %s ",t1 );
		if ( ig_flag == FALSE ) fprintf(stderr,"%s ",t3);
	} else {
		if ( utmi_flag )
			fprintf ( stderr, " %s ",t21);
		else
			fprintf ( stderr, " %s ",t2 );
		if ( ig_flag == FALSE ) fprintf(stderr,"%s ",t3);
	}
	fprintf ( stderr, "%d/%d in \n",Min,Sin );
	if ( o_flag ) {
		fprintf (stderr, "\t %s ",t1 );
		if ( og_flag == FALSE ) fprintf(stderr,"%s ",t3);
	} else {
		if ( utmo_flag )
			fprintf ( stderr, "\t %s ",t21 );
		else
			fprintf ( stderr, "\t %s ",t2 );
		if ( og_flag == FALSE ) fprintf(stderr,"%s ",t3);
	}
	fprintf ( stderr, "%d/%d ---\n--- Objektanzahl %6ld ---\n",Mout,Sout,NR);
	fflush (stderr);
exit (0);
}

void print_usage (void) {
register char **cptr;

	fprintf (stderr, "; %s - %s%s %s\n", Copyright, Version, Release, Date);

	for (cptr = usage; *cptr != NULL; ++cptr)
		fputs (*cptr, stderr);
}

void command_line (int argc, char **argv)
{
register int i,j;
register char *p;

/* Kommandozeile auswerten */
	for (i = 1; i < argc; ++i) {
		p = argv[i];
		if (*p == '/') {
			++p; switch (*p++) {
			case '?':
			case 'H':
			case 'h':
			default:
				print_usage ();
				exit(1);
			}
		} else if (*p == '-') {
			++p; switch (*p++) {

			case 'm':       /* Mittelmeridian - Input*/
			case 'M':
				Min = atoi (p);
				break;
			case 'n':       /* Mittelmeridian - Output*/
			case 'N':
				Mout = atoi (p);
				break;
			case 's':       /* Streifenbreite - Input*/
			case 'S':
				Sin = atoi (p);
				break;
			case 'e':       /* Streifenbreite - Output*/
			case 'E':
				Sout = atoi (p);
				break;
			case 'g': case 'G':
				g_flag = TRUE ;
				break;
//-------------------------------------------------------------------
			case 'd': case 'D':
				d_flag = TRUE ;
				break;
			case 'r': case 'R':
				r_flag = FALSE ;
				break;
			case 'u': case 'U':
				u_flag = TRUE ;
				break;
			case 'k': case 'K':
				k_flag = TRUE ;
				break;
			case 'y': case 'Y':
				y_flag = TRUE ;
				break;
//-------------------------------------------------------------------
			case 'o':       /* Ouput*/
			case 'O':
			// Bessel ist Standard ( FALSE )
				if (*p == 'K' || *p == 'k' ) o_flag= TRUE ;
				if (*(p+1) == 'G' || *(p+1) == 'g' ) og_flag = FALSE ;
				if (*p == 'U' || *p == 'u') {
						utmo_flag = TRUE;
						o_flag = FALSE;
				}
				break;

			case 'i':       /* Input*/
			case 'I':
		//	Krassowski ist Standard ( TRUE )
				if (*p == 'B' || *p == 'b' ) i_flag = FALSE ;
				if (*(p+1) == 'G' || *(p+1) == 'g' ) ig_flag = FALSE ;
				if (*p == 'U' || *p == 'u') {
					utmi_flag = TRUE;
					i_flag = FALSE;
				}
				break;

			case 'h':       /* Koord.Eingabe H,R */
			case 'H':
				h_flag = TRUE;
        			break;
				/* ggf. hier durchfallen */
			default:
				print_usage ();
				exit(1);
			}
		} else if (*fnin == '\0') {
		/* ATLAS-Input-Name */
			strncpy (fnin, p, 75);
		} else if (*ascii == '\0') {
		/* ATLAS-Output-Name */
			strncpy (ascii, p, 75);
		} else {
		/* ungueltiger Parameter */
			print_usage ();
			exit(1);
		}
	}
}

void atlasgis_open ( void ) {

/* ATLASGIS-ASCII-Datei eroeffnen */
	if ('\0' == fnin[0] || '-' == fnin[0])
		return;		// stdin

	if ((yyin = fopen (fnin, "r")) == NULL) {
		fprintf (stderr, no_open, "Datei", fnin);
		print_usage();
		exit(1);
	}
}


void ascii_open (void) {
/* Ausgabedatei eroeffnen */
	if ('\0' == ascii[0])
		return; // stdout

	if ((fascii = fopen (ascii, "w")) == NULL) {
		fprintf (stderr, no_open, "Datei", ascii);
		print_usage();
		exit (1);
	}
}


void print_titel (char *titel) {

	fprintf (stderr, "\n%s\n", titel);
	fprintf (stderr, "%s - %s%s %s\n\n", Copyright, Version, Release, Date);
	fflush (stderr);
}
//
//    gaugeo

/* 		Original Walter:
               Input:     HA     - grosse Halbachse des Ellips. in m R*8
                          HB     - kleine Halbachse des Ellips. in m R*8
                          STRBR  - Streifenbreite in Grad            I*4
                          L0     - Mittelmeridian in Grad            I*4
                          M      - Vergroesserungsverhaeltnis        R*8
                          X      - Gauss-Krueger-Hochwert in m       R*8
                          Y      - Gauss-Krueger-Rechtswert in m     R*8
               Output:    B      - geogr. Breite des Pkt. in "       R*8
                          L      - geogr. Laenge des Pkt. in "       R*8
       Aufgabenstellung, Hintergrund:
          Die Funktionen GAUGEO.f (Gauss-Krueger-Koordinaten zu
          geographischen Koordinaten) und GEOGAU.f (geographische
          Koordinaten zu Gauss-Krueger-Koordinaten) sind nach
          den Formeln von K. Hubeny: 'Isotherme Koordinatensysteme
          und konforme Abbildungen des Rotationsellipsoides',
          Mitteilungen der geodaetischen Institute der TU Graz,
          Folge 27, 1977, S.49 f. und S.213ff. programmiert.
          Die Meridianbogenlaengen werden durch Integration aus
          Koenig/Weise: 'Mathematische Grundlagen der hoeheren
          Geodaesie und Kartographie', Springer Verlag, 1951, S.19
          erhalten.
          Die geographischen Koordinaten werden B und L, die des
          Mittelmeridians L0 genannt. Die Gauss-Krueger-Koordinaten
          werden mit X (Hochwert) und Y (Rechtswert) bezeichnet.
          Beide Formeln liefern bei Hin- und Rueckrechnung bei
          unserer geographischen Breite bis zu 3 Grad Abstand vom
          Mittelmeridian eine Genauigkeit unter 0.00001 mm, bei
          6 Grad Abstand in X knapp 1mm.

          In GEOGAU werden die Koeffizienten der Potenzen von Delta L
          bei der Breite B gebildet (Glieder mit Potenzen von Delta B
          entfallen); die Meridinbogenlaenge G wird vom Aequator aus
          gerechnet.
          In GAUGEO wird bei der Fusspunktbreite BF (sie wird durch
          Iteration ermittelt) entwickelt.   				*/

//    Gaugeo - Gau·/KrÅger in geogr. Koordinaten

void FUNCTYPE gaugeo(long double ha, long double hb, int strbr, int l0, long double Hwert, long double Rwert, long double *Breite, long double *Laenge)
	{
	long double cor,t,t2,eta4,vc2,bh1,bh2,bh3,bh4,p2,p12,p20,p42,p360,p6;
	long double peps,v,co,e2,g,bf,eta2,hm,v2,vc,c;
	long double n,n2,n3,n4,n5;
	long double A[6];
	long double kennz,xi,yi,y2,y4,y6,rl0,m;
	long double PRO,B[7];
//-------------------------------------------------------------
	if ( utmi_flag )
		m = 0.9996;	// Vergrî·erungsverhÑltnis UTM
	else
		m=1.0;		//Vergrî·erungsverhÑltnis Bessel
//---------------------------------------------------------------
	PRO=206264.8062471;
	kennz=((l0+(strbr-3))/strbr)*1000000; 		// Streifenkennzahl
//     *** X,Y berechnen:

        xi=Hwert/m;
        yi=(Rwert-kennz-500000.0)/(m*100000.0);
        y2=yi*yi;
        y4=y2*y2;
        y6=y4*y2;
//    *** Laenge Bezugsmeridian:

        rl0=l0;
	rl0=rl0*3600.0;

//     *** Ausgangswerte berechnen:

//
//     Startwerte
//
	p2=0.5;
//
	n=(ha-hb)/(ha+hb);
	n2=n*n;
	n3=n2*n;
	n4=n3*n;
	n5=n4*n;
	A[0]=1.0+n2/4.0+n4/64.0;
	A[1]=3.0*p2*(-n+n3/8.0+n5/64.0);
	A[2]=(15.0/16.0)*(n2-n4/4.0);
	A[3]=(35.0/48.0)*(-n3+(5.0/16.0)*n5);
	A[4]=(315.0/512.0)*n4;
	A[5]=-(693.0/1280.0)*n5;

/*       *** Iteration fuer G:  				*/
//
//	Iteration fuer G
//
//       *** Iteration fuer G:
	p2=0.5;
	peps=0.00001;
/*     *** Ausgangswerte berechnen: 					*/
	c=(ha/hb)*ha;
	e2=(ha*ha-hb*hb)/(hb*hb);
/*                        fuer Meridianbogenlaenge:  			*/
	hm=(ha+hb)*p2;
//	Anfangsbedingungen
	g=0.0;
	bf=0.0;
	v2=1.0;
	vc=1.0/A[0];
	while ( (fabs(xi-g)) > peps ) {
		bf=bf+(xi-g)*vc*v2;
		co=cos (bf);
        	eta2=e2*co*co;
        	v2=1.0+eta2;
        	v=sqrt (v2);
        	vc=v/c;
        	g=A[0]*bf+A[1]*sin(2.0*bf)+A[2]*sin(4.0*bf);
        	g=g+A[3]*sin(6.0*bf)+A[4]*sin(8.0*bf)+A[5]*sin(10.0*bf);
        	g=hm*g;
	}
//      *** Anfangswerte fuer Fusspunktbreite,Koeff. berechnen
//
//	Koeffizienten
//
	p2=1.0/2.0;
	p6=1.0/6.0;
	p12=1.0/12.0;
	p20=1.0/20.0;
	p42=1.0/42.0;
	p360=1.0/360.0;
/*      *** Anfangswerte fuer Fusspunktbreite:    */
        cor=1.0/co;
        t=tan (bf);
        t2=t*t;
        eta4=eta2*eta2;
        vc2=vc*vc;
/*       *** Koeffizienten berechnen:
         --- fuer B:				*/
        bh1=10000000000.0*p2*vc2*t;
        B[1]=bh1*(-1.0-eta2);
        B[3]=5.0+3.0*t2+6.0*eta2-3.0*eta4-6.0*t2*eta2;
        B[3]=B[3]-9.0*t2*eta4;
        B[3]=p12*bh1*vc2*10000000000.0*B[3];
        B[5]=-61.0-90.0*t2-45.0*t2*t2-92.0*eta2;
        B[5]=B[5]+147.0*t2*eta2+45.0*t2*t2*eta2;
        B[5]=p360*bh1*vc2*10000000000.0*vc2*10000000000.0*B[5];
/*      --- fuer L:  				*/
        B[0]=vc*100000.0*cor;
        bh2=p6*vc2*10000000000.0*B[0];
        B[2]=bh2*(-1.0-2.0*t2-eta2);
        bh3=p20*bh2*vc2*10000000000.0;
        B[4]=5.0+28.0*t2+24.0*t2*t2+6.0*eta2+8.0*t2*eta2;
        B[4]=B[4]*bh3;
        bh4=p42*bh3*vc2*10000000000.0;
        B[6]=61.0-662.0*t2-1320.0*t2*t2-720.0*t2*t2*t2;
        B[6]=B[6]*bh4;
//       *** Hochwert berechnen:

        *Breite=(bf+B[1]*y2+B[3]*y4+B[5]*y6)*PRO;
//       *** Y berechnen:


        *Laenge=(B[0]*yi+B[2]*y2*yi+B[4]*y4*yi+B[6]*y6*yi)*PRO+rl0;
	return ;
}


void FUNCTYPE geogau (long double ha, long double hb, int strbr, int l0, long double Breite, long double Laenge, long double *Hwert, long double *Rwert)
	{
	long double t,t2,eta4,v2,bh1,bh2,bh3,bh4,p2,p12,p20,p42,p30,p6;
	long double peps,v,co,co2,e2,g,bf,eta2,hm,vc,cv,c;
	long double n,n2,n3,n4,n5;
	long double A[6];
	long double kennz,xi,yi,y2,y4,y6,rl0,m,db,dl,dl2,dl4,dl6;
	long double PRO,B[7];
//-------------------------------------------------------------------
	if ( utmo_flag )
		m = 0.9996;	//Vergrî·erungsverhÑltnis UTM
	else
		m=1.0;		//Vergrî·erungsverhÑltnis Bessl
//--------------------------------------------------------------------
	PRO=206264.8062471;
//
//	Koeffizienten
//
	p2=1.0/2.0;
	p6=1.0/6.0;
	p12=1.0/12.0;
	p20=1.0/20.0;
	p42=1.0/42.0;
	p30=1.0/30.0;
//
// *** Delta B und Delta L berechnen (im Bogenmass):
        db=Breite/PRO;
        rl0=l0;
        rl0=rl0*3600.0;
        dl=(Laenge-rl0)/PRO;
        dl2=dl*dl;
        dl4=dl2*dl2;
        dl6=dl4*dl2;

	kennz=((l0+(strbr-3))/strbr)*1000000; 		// Streifenkennzahl

/*     *** Ausgangswerte berechnen: 					*/
	c=(ha/hb)*ha;
	e2=(ha*ha-hb*hb)/(hb*hb);
/*                        fuer Meridianbogenlaenge:  			*/
	hm=(ha+hb)*p2;
//     Startwerte
	n=(ha-hb)/(ha+hb);
	n2=n*n;
	n3=n2*n;
	n4=n3*n;
	n5=n4*n;
	A[0]=1.0+n2/4.0+n4/64.0;
	A[1]=3.0*p2*(-n+n3/8.0+n5/64.0);
	A[2]=(15.0/16.0)*(n2-n4/4.0);
	A[3]=(35.0/48.0)*(-n3+(5.0/16.0)*n5);
	A[4]=(315.0/512.0)*n4;
	A[5]=-(693.0/1280.0)*n5;
//
        g=A[0]*db+A[1]*sin(2.0*db)+A[2]*sin(4.0*db);
        g=g+A[3]*sin(6.0*db)+A[4]*sin(8.0*db)+A[5]*sin(10.0*db);
        g=hm*g;
//                       ! fuer gegebene Breite
        co=cos (Breite/PRO);
        co2=co*co;
        t=tan (Breite/PRO);
        t2=t*t;
        eta2=e2*co*co;
        eta4=eta2*eta2;
        v2=1.0+eta2;
        v=sqrt (v2);
        cv=c/v;
// *** Koeffizienten berechnen:
//   --- fuer X:
        B[1]=p2*cv*t*co2;
        bh1=p12*B[1]*co2;
        B[3]=bh1*(5.0-t2+9.0*eta2+4.0*eta4);
        B[5]=p30*bh1*co2*(61.0-58.0*t2+t2*t2);
//    --- fuer Y:
        B[0]=cv*co;
        bh2=p6*B[0]*co2;
        B[2]=bh2*(1.0-t2+eta2);
        bh3=p20*bh2*co2;
        B[4]=bh3*(5.0-18.0*t2+t2*t2+14.0*eta2-58.0*t2*eta2);
        bh4=p42*bh3*co2;
        B[6]=bh4*(61.0-479.0*t2+179.0*t2*t2-t2*t2*t2);
// *** X berechnen:
	*Hwert=(g+B[1]*dl2+B[3]*dl4+B[5]*dl6)*m;
// *** Y berechnen:
	*Rwert=(B[0]*dl+B[2]*dl2*dl+B[4]*dl4*dl+B[6]*dl6*dl)*m;
	*Rwert=*Rwert+500000.0+kennz;
	return;
}
//----------------------------------------------------------------------------
void FUNCTYPE modko_B ( long double B, long double L, long double *dHwert, long double *dRwert)
	{
	int DL,DB;
	long double rDL,rDB;
	long double dlh,dlr,dbh,dbr,dH,dR,FL,FB,R,H,dDL,dDB;


	B=B/3600.0;
	L=L/3600.0;
	if ( d_flag )
		fprintf (fascii,"\tB=%12.5lf,L=%12.5lf\n",B,L);

//	Festwerte


//	Transf. Bessel/Krassowski

	FL=4.0;			// Schrittweiten
	FB=6.0;
//	Trennlinie bei L=13.5 Grad
	if ( L <= 13.5 ) {
		dH=588.1;
		dR=23.1;
		rDL = ( 13.5 - L ) * FL;
		DL=rDL;
		if ( B >= 52.0 ) {
			dlh=0.2;
			dlr=-0.1;
			dbh=0.1;
			dbr=0.2;
			rDB = ( B - 52.0 ) * FB ;
			DB=rDB;
		} else	{
			dH=588.0;
			dR=22.9;
			dlh=0.2;
			dlr=-0.1;
			dbh=-0.1;
			dbr=-0.2;
			rDB = ( 52.0 - B ) * FB ;
			DB=rDB;

		}
	} else  {
	//	L > 13.5 
		dH=587.7;
		dR=-9.8;
		rDL = ( L - 13.5 ) * FL;
		DL=rDL;
		if ( B >= 52.0 ) {
			dlh=-0.2;
			dlr=0.1;
			dbh=0.1;
			dbr=0.2;
			rDB = ( B - 52.0 ) * FB;
			DB=rDB;
		} else	{
			dH=587.6;
			dR=-10.0;
			dlh=-0.2;
			dlr=0.1;
			dbh=-0.1;
			dbr=-0.2;
			rDB = ( 52.0 - B ) * FB;
			DB=rDB;
		}
	}

	if ( d_flag )
		fprintf (fascii,"\tDL=%ld,DB=%ld,DiffL=%12.5lf,DiffB=%12.5lf\n",DL,DB,13.5-L,52.0-B);


// 1.Schritt -LÑngendifferenz
	dDL = DL ;
	H = dH + dDL*dlh ;
	R = dR + dDL*dlr ;
// 2.Schritt -Breitendifferenz
	dDB = DB ;
	H = H + dDB*dbh ;
	R = R + dDB*dbr ;
	* dRwert = R ;
	* dHwert = H ;
	return;
}
//--------------------------------------------------------------
//----------------------------------------------------------------------------
void FUNCTYPE modko_K ( long double B, long double L, long double *dHwert, long double *dRwert)
	{
	int DL,DB;
	long double rDL,rDB;
	long double dlh,dlr,dbh,dbr,dH,dR,FL,FB,R,H,dDL,dDB;


	B=B/3600.0;
	L=L/3600.0;

	if ( d_flag )
		fprintf (fascii,"\tB=%12.5lf,L=%12.5lf\n",B,L);

//	Festwerte
//	Krassowski/Bessel

	FL=4.0;			// Schrittweiten
	FB=6.0;

//	Trennlinie bei L=13.5 Grad

	if ( L <= 13.5 ) {
		dH=-589.630;
		dR=-56.094;
		rDL = ( 13.5 - L ) * FL;
		DL=rDL;
		if ( B >= 52.0 ) {
			dlh=-0.203;
			dlr=0.11;
			dbh=-0.11;
			dbr=-0.205;
			rDB = ( B - 52.0 ) * FB ;
			DB=rDB;
		} else	{
			dH=-589.520;
			dR=-55.892;
			dlh=-0.203;
			dlr=0.11;
			dbh=0.11;
			dbr=0.205;
			rDB = ( 52.0 - B ) * FB ;
			DB=rDB;

		}
	} else  {
	//	L > 13.5 
		dH=-587.861;
		dR=-23.205;
		rDL = ( L - 13.5 ) * FL;
		DL=rDL;
		if ( B >= 52.0 ) {
			dlh=0.203;
			dlr=-0.107;
			dbh=-0.107;
			dbr=-0.205;
			rDB = ( B - 52.0 ) * FB;
			DB=rDB;
		} else	{
			dH=-587.753;
			dR=-23.003;
			dlh=0.203;
			dlr=-0.107;
			dbh=0.107;
			dbr=0.205;
			rDB = ( 52.0 - B ) * FB;
			DB=rDB;
		}
	}


// 1.Schritt -LÑngendifferenz
	dDL = DL ;
	H = dH + dDL*dlh ;
	R = dR + dDL*dlr ;
// 2.Schritt -Breitendifferenz
	dDB = DB ;
	H = H + dDB*dbh ;
	R = R + dDB*dbr ;

	* dRwert =  R ;
	* dHwert =  H ;

	return;
}
//--------------------------------------------------------------
int FUNCTYPE kootst ( int flag, long double h , long double r )
	{
	int rc,hint,rint;
	rc = FALSE ;
	if ( h < UGH || h > OGH || r < UGR || r > OGR ) {
		rc = TRUE;
		return rc;
	}

	hint= (int)(h/1000000.);
	rint= (int)(r/1000000.);
	if ( flag ) {
	//	Krassowski
		if ( Sin == 6 && Min == 9 ) {
			if ( hint == 5 && rint == 2 ) return rc;
			if ( hint == 6 && rint == 2 ) return rc;
		}
		if ( Sin == 6 && Min == 15 ) {
			if ( hint == 5 && rint == 3 ) return rc;
			if ( hint == 6 && rint == 3 ) return rc;
		}
//5.3.96 : ErgÑnzen von 3 Grad-Streifen
		if ( Sin == 3 && Min == 9 ) {
			if ( hint == 5 && rint == 3 ) return rc;
			if ( hint == 6 && rint == 3 ) return rc;
		}
		if ( Sin == 3 && Min == 12 ) {
			if ( hint == 5 && rint == 4 ) return rc;
			if ( hint == 6 && rint == 4 ) return rc;
		}
		if ( Sin == 3 && Min == 15 ) {
			if ( hint == 5 && rint == 5 ) return rc;
			if ( hint == 6 && rint == 5 ) return rc;
		}

	} else 	{
	//	Bessel
		if ( Sin == 3 && Min == 3 ) {
			if ( hint == 5 && rint == 1 ) return rc;
			if ( hint == 6 && rint == 1 ) return rc;
		}
		if ( Sin == 3 && Min == 6 ) {
			if ( hint == 5 && rint == 2 ) return rc;
			if ( hint == 6 && rint == 2 ) return rc;
		}
		if ( Sin == 3 && Min == 9 ) {
			if ( hint == 5 && rint == 3 ) return rc;
			if ( hint == 6 && rint == 3 ) return rc;
		}
		if ( Sin == 3 && Min == 12 ) {
			if ( hint == 5 && rint == 4 ) return rc;
			if ( hint == 6 && rint == 4 ) return rc;
		}
		if ( Sin == 3 && Min == 15 ) {
			if ( hint == 5 && rint == 5 ) return rc;
			if ( hint == 6 && rint == 5 ) return rc;
		}
		if ( Sin == 6 && Min == 9 ) {
			if ( hint == 5 && rint == 3 ) return rc;
			if ( hint == 6 && rint == 3 ) return rc;
		}
		if ( Sin == 6 && Min == 12 ) {
			if ( hint == 5 && rint == 4 ) return rc;
			if ( hint == 6 && rint == 4 ) return rc;
		}
		if ( Sin == 6 && Min == 15 ) {
			if ( hint == 5 && rint == 5 ) return rc;
			if ( hint == 6 && rint == 5 ) return rc;
		}
	}
	rc = TRUE ;
	return rc ;

}
