/* Deklaration der Datenbasisstruktur fuer ris */

struct kal {
	long zap;
	long zep;
	long zlm;
	long zrm;
	long zkvgo;
	long zksp;
	long asp;
	long wi;
	struct {
		long kxmin;
		long kxmax;
		long kymin;
		long kymax;
	} kcont;
};
struct kpl {
	long zkpvgo;
	long zkpkfk;
	struct {
		long kpx;
		long kpy;
	} pkrd;
	long zkpma;
};
struct spl {
	long spx;
	long spy;
	long znsp;
};
struct mal {
	long zmkfm;
	long zmvgo;
	struct {
		long mxmin;
		long mxmax;
		long mymin;
		long mymax;
	} mcont;
	long zmvzo;
};
struct kfk {
	long zkfkk;
	long znkfk;
};
struct kfm {
	long zkfmk;
	long znkfm;
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
};
struct rel {
	long zrera;
	long zol1;
	long zol2;
};
struct idl {
	long idn;
	long zvio;
	long zmerki;
	long zrelid;
};
struct mkl {
	long mk;
	long typ;
	long zmkvmo;
};
struct mi {
	long znmi;
	long mw[2];
};
struct fdbt {
	char infof[44];
	long zndbtf;
};
struct vgo {
	long zvgoo;
	long znvgo;
};
struct vzo {
	long zvzoo;
	long znvzo;
};
struct vol {
	long zvolk;
	long znvol;
};
struct voa {
	long zvomam;
	long znvoma;
};
struct vom {
	long zvommk;
	long znmk;
	long zvommi;
	long zvomo;
};
struct vmo {
	long zvmoo;
	long znvmo;
};
struct vor {
	long zvorel;
	long znvor;
};
struct vio {
	long zvioo;
	long znvio;
};
struct vre {
	long zvrere;
	long znvre;
};
struct ral {
	long rat;
	long zravre;
	short maske;
};
struct pol {
	long zpvgo;
	long zpkfk;
	struct {
		long px;
		long py;
	} kpkrd;
	long zpma;
};
struct head {
	long hdidn[4];
	char text[60];
	long hdrflags;
	long zntext;
};
struct fhead {
	char textf[80];
	long ztextf;
};
struct sicht {
	char sichtname[40];
	short idnum;
	short idset;
	short onnum;
	short onset;
	long objrgn;
	long zmerkm;
	long zrelat;
};
struct pattribs {
	long ptarget;
	short npset;
	short pprio;
	short pstyle;
	long pcolor;
	char pflag;
	char pattrex;
	short sizex;
	short sizey;
	char pname[32];
	short prot;
	short pdummy2;
	long p2color;
};
struct lattribs {
	long ltarget;
	short lnset;
	short lprio;
	short lstyle;
	long lcolor;
	char lflag;
	char lattrex;
	short width;
	short ldummy;
	char lname[32];
	long ldummy2[2];
};
struct fattribs {
	long ftarget;
	short fnset;
	short fprio;
	short fstyle;
	long fcolor;
	char fflag;
	char fattrex;
	long bcolor;
	char fname[32];
	long fdummy[2];
};
struct reltyp {
	long zhrel;
	long zvrelo;
	long zvrelu;
	long zbrela;
	long zbrelp;
};
struct tattribs {
	long ttarget;
	short tnset;
	short tprio;
	short tstyle;
	long tcolor;
	char tflag;
	char tattrex;
	char tsizex;
	char tsizey;
	char ttype;
	char trot;
	char tname[32];
	long tdummy[2];
};
struct kdbt {
	long llen;
	long zmivom;
	char info[36];
	long zndbt;
};

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
#define PATTRIBS 26
#define LATTRIBS 27
#define FATTRIBS 28
#define RELTYP 29
#define TATTRIBS 30
#define KDBT 31

/* Konstanten fuer Schluesselfelder */
#define KCONT 0
#define MCONT 1
#define IDN 2
#define MK 3
#define RAT 4
#define KPKRD 5
#define HDIDN 6
#define SICHTNAME 7
#define INFO 8
