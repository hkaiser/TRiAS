/* Deklaration der Datenbasisstruktur fuer ris */

#if !defined(_RISDB_H)
#define _RISDB_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

#if !defined(_NO_INITRECORD)
#define INITRECORD() memset(this, '\0', sizeof(*this))
#else
#define INITRECORD()
#endif // _NO_INITRECORD

struct kcont {
	long kxmin;
	long kxmax;
	long kymin;
	long kymax;
};
	
struct kal {
	long zap;
	long zep;
	long zlm;
	long zrm;
	long zkvgo;
	long zksp;
	long asp;
	long wi;
	struct kcont kcont;

		kal() { INITRECORD(); }
};
struct kpl {
	long zkpvgo;
	long zkpkfk;
	struct {
		long kpx;
		long kpy;
	} pkrd;
	long zkpma;

		kpl() { INITRECORD(); }
};
struct spl {
	long spx;
	long spy;
	long znsp;

		spl() { INITRECORD(); }
};
struct mal {
	long zmkfm;
	long zmvgo;
	struct mcont {
		long mxmin;
		long mxmax;
		long mymin;
		long mymax;
	} mcont;
	long zmvzo;

		mal() { INITRECORD(); }
};
struct kfk {
	long zkfkk;
	long znkfk;

		kfk() { INITRECORD(); }
};
struct kfm {
	long zkfmk;
	long znkfm;

		kfm() { INITRECORD(); }
};
struct obl {
	long zovor;
	long zoid;
	long zovom;
	long zokp;
	long zovol;
	long zovoma;
	char rmaske;
	char status;
	struct _GUID guid;		// #HK970908: ab V5.00.00.014 mit UniqueID

		obl() { INITRECORD(); }
};
struct rel {
	long zrera;
	long zol1;
	long zol2;

		rel() { INITRECORD(); }
};
struct idl {
	long idn;
	long zvio;
	long zmerki;	// ab Version 007
	long zrelid;

// ab Version 014
	long lpvio;		/* Zähler der Punktobjekte */
	long zpvio;		/* Punktobjekte */
	long llvio;		/* Zähler der Linienobjekte */
	long zlvio;		/* Linienobjekte */
	long lfvio;		/* Zähler der Flächenobjekte */
	long zfvio;		/* Flächenobjekte */
	long ltvio;		/* Zähler der Textobjekte */
	long ztvio;		/* Texttobjekte */
	long lkvio;		/* Zähler der Komplexobjekte */
	long zkvio;		/* Komplexobjekte */

		idl() { INITRECORD(); }
};
struct mkl {
	long mk;
	long typ;
	long zmkvmo;

		mkl() { INITRECORD(); }
};
struct mi {
	long znmi;
	long mw[2];

		mi() { INITRECORD(); }
};
struct fdbt {		// ab Version 011 ist dbt jetzt fdbt
	char infof[44];
	long zndbtf;

		fdbt() { INITRECORD(); }
};
struct vgo {
	long zvgoo;
	long znvgo;

		vgo() { INITRECORD(); }
};
struct vzo {
	long zvzoo;
	long znvzo;

		vzo() { INITRECORD(); }
};
struct vol {
	long zvolk;
	long znvol;

		vol() { INITRECORD(); }
};
struct voa {
	long zvomam;
	long znvoma;

		voa() { INITRECORD(); }
};
struct vom {
	long zvommk;
	long znmk;
	long zvommi;
	long zvomo;		// ab Version 011

		vom() { INITRECORD(); }
};
struct vmo {
	long zvmoo;
	long znvmo;

		vmo() { INITRECORD(); }
};
struct vor {
	long zvorel;
	long znvor;

		vor() { INITRECORD(); }
};
struct vio {
	long zvioo;
	long znvio;

		vio() { INITRECORD(); }
};
struct vre {
	long zvrere;
	long znvre;

		vre() { INITRECORD(); }
};
struct ral {
	long rat;
	long zravre;
	short maske;

		ral() { INITRECORD(); }
};
struct pol {
	long zpvgo;
	long zpkfk;
	struct {
		long px;
		long py;
	} kpkrd;
	long zpma;

		pol() { INITRECORD(); }
};
struct head {
	long hdidn[4];
	char text[60];		// #HK960126: nur 60 Bytes, dafür Flags
	long hdrflags;
	long zntext;

		head() { INITRECORD(); }
};
struct fhead {
	char textf[80];
	long ztextf;

		fhead() { INITRECORD(); }
};
#define MAXVIEWNAMESIZE		40
struct sicht {
	char sichtname[MAXVIEWNAMESIZE];
	short idnum;
	short idset;
	short onnum;
	short onset;
	long objrgn;		// ab Version 006
	long zmerkm;		// ab Version 007
	long zrelat;

		sicht() { INITRECORD(); }
};
struct attribs {
	long attTarget;
	short attSet;
	short attPrio;
	short attStyle;
	long attPColor;
	char attFlag;
	char attAttrEx;		// #HK941218 (V5.00.00.011)
	short attDefVis;	// #HK930823
	char attDummy[2];
	char attName[32];
	long dummy[2];		// #HK951016

		attribs() { INITRECORD(); }
};
struct pattribs {
	long ptarget;
	short npset;
	short pprio;
	short pstyle;
	long pcolor;
#if !defined(OLDVISINFO)
	short pflag;
#else
	char pflag;			// V5.00.00.011
	char pattrex;
#endif
	short sizex;
	short sizey;
	char pname[32];
	short prot;			// V5.00.00.011
	char pdummy[2];		// V5.00.00.011
	long pscolor;		// V5.00.00.011

		pattribs() { INITRECORD(); }
};
struct lattribs {
	long ltarget;
	short lnset;
	short lprio;
	short lstyle;
	long lcolor;
#if !defined(OLDVISINFO)
	short lflag;
#else
	char lflag;
	char lattrex;		// V5.00.00.011
#endif
	short width;
	char ldummy[2];
	char lname[32];
	long ldummy2[2];	// V5.00.00.011

		lattribs() { INITRECORD(); }
};
struct fattribs {
	long ftarget;
	short fnset;
	short fprio;
	short fstyle;
	long fcolor;
#if !defined(OLDVISINFO)
	short fflag;
#else
	char fflag;
	char fattrex;		// V5.00.00.011
#endif
	long bcolor;
	char fname[32];
	long fdummy[2];		// V5.00.00.011

		fattribs() { INITRECORD(); }
};
struct tattribs {
	long ttarget;
	short tnset;
	short tprio;
	short tstyle;
	long tcolor;
#if !defined(OLDVISINFO)
	short tflag;
#else
	char tflag;
	char tattrex;		// V5.00.00.011
#endif
	char tsizex;
	char tsizey;
	char ttype;
	char trot;
	char tname[32];
	long tdummy[2];		// V5.00.00.011

		tattribs() { INITRECORD(); }
};
struct reltyp {
	long zhrel;
	long zvrelo;
	long zvrelu;
	long zbrela;
	long zbrelp;

		reltyp() { INITRECORD(); }
};
struct kdbt {		// ab Version 011 ist dbt zerlegt
	long llen;
	long zmivom;
	char info[36];
	long zndbt;

		kdbt() { INITRECORD(); }
};
struct binmi {			// ab Version 5.00.00.012
	long binlen;
	char bindata[246];
	long znbmi;

		binmi() { INITRECORD(); }
};
struct fbinmi {
	char bindataf[250];
	long znbmif;

		fbinmi() { INITRECORD(); }
};

#if !defined(STRUCTS_ONLY)
/* Record- und Feld-Tabelleneintraege */

/* Konstanten fuer Recordnamen */
#define KAL 0
#define KPL 1
#define SPL 2
#define MAL 3
#define KFK 4
#define KFM 5
#define OBL 6
#define REL 7
#define IDL 8
#define MKL 9
#define MI 10
#define FDBT 11
#define VGO 12
#define VZO 13
#define VOL 14
#define VOA 15
#define VOM 16
#define VMO 17
#define VOR 18
#define VIO 19
#define VRE 20
#define RAL 21
#define POL 22
#define HEAD 23
#define FHEAD 24
#define SICHT 25
#define ATTRIBS  26	// stellvertretend für alle VisInfo's
#define PATTRIBS 26
#define LATTRIBS 27
#define FATTRIBS 28
#define RELTYP 29
#define TATTRIBS 30
#define KDBT 31
#define BINMI 32
#define FBINMI 33

/* Konstanten für Schlüsselfelder */
#define KCONT 0
#define MCONT 1
#define IDN 2
#define MK 3
#define RAT 4
#define KPKRD 5
#define HDIDN 6
#define SICHTNAME 7
#define INFO 8		// ab Version 5.00.00.011
#define GUIDKEY 9		// ab Version 5.00.00.014

#endif // STRUCTS_ONLY

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif // _RISDB_H
