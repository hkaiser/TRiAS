///////////////////////////////////////////////////////////////////////////
// Risdb.h | Deklaration der Datenbasisstruktur für ris

#if !defined(_RISDB_H__D2BEE714_7A21_11D1_9763_00A024D6F582__INCLUDED_)
#define _RISDB_H__D2BEE714_7A21_11D1_9763_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <pshpack1.h>

#include <Versions.h>

#if !defined(STRUCTS_ONLY)
/* Record- und Feld-Tabelleneintraege */

#include <errcodes.hxx>
#include <DateTime.h>

/* Konstanten fuer Recordnamen */
#define KAL 0
#define KPL 1
// ab Version 5.00.00.016 gibt es eine neu SPL
#define SPL_OLD 2
#define SPL_NEW	35
//#define SPL ((VERSION05000010 <= GetDBVersion()) ? SPL_NEW : SPL_OLD)
#define MAL 3
#define KFK 4
#define KFM 5
// ab Version 5.00.00.014 gibt es den Typ struct db_addr_OBL
#define OBL_OLD	6
#define OBL_NEW	32
//#define OBL ((VERSION0500000E <= GetDBVersion()) ? OBL_NEW : OBL_OLD)
#define REL 7
#define IDL_OLD 8
#define IDL_NEW 36
//#define IDL ((VERSION05000013 <= GetDBVersion()) ? IDL_NEW : IDL_OLD)
#define MKL 9
#define MI 10
#define FDBT 11
#define VGO 12
#define VZO 13
#define VOL 14
#define VOA 15
#define VOM 16
// ab Version 5.00.00.015 gibt's eine neue VMO
#define VMO_OLD 17
#define VMO_NEW 33
//#define VMO ((VERSION0500000F <= GetDBVersion()) ? VMO_NEW : VMO_OLD)
#define VOR 18
// ab Version 5.00.00.015 gibt's eine neue VIO
#define VIO_OLD 19
#define VIO_NEW 34
//#define VIO ((VERSION0500000F <= GetDBVersion()) ? VIO_NEW : VIO_OLD)
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

/* Konstanten für Schlüsselfelder */
#define KCONT 0
#define MCONT 1
#define IDN_OLD 2		// ab Version 5.00.00.019
#define MK 3
#define RAT 4
#define KPKRD 5
#define HDIDN 6
#define SICHTNAME 7
#define INFO 8			// ab Version 5.00.00.011
#define GUIDKEY 9		// ab Version 5.00.00.014
#define MCODEB 10		// ab Version 5.00.00.015
#define IDENTB 11		// ab Version 5.00.00.015
#define MCODEX 10		// ab Version 5.00.00.017
#define IDENTX 11		// ab Version 5.00.00.017
#define IDN_NEW	12		// ab Version 5.00.00.019
// #define IDN ((VERSION05000013 <= GetDBVersion()) ? IDN_NEW : IDN_OLD)
#define IDGUID 13

#endif // STRUCTS_ONLY

///////////////////////////////////////////////////////////////////////////////
// Helpermakros
#define DBASSERT(f)				{ if((RC=(ErrCode)(f))!=0) return RC; }
#define DBASSERTM(f)			{ if(long(f)<0L) return (RC=(ErrCode)(f)); }
#define DBASSERTHR(f)			{ if((RC=(ErrCode)(f))!=0) return HRESULT_FROM_ERRCODE(RC); }
#define THROW_FAILED_ERRCODE(f)	{ ErrCode RC=(ErrCode)(f); if(0!=RC) _com_issue_error(HRESULT_FROM_ERRCODE(RC)); }

#if !defined(_RISDB_NO_STRUCTS)

///////////////////////////////////////////////////////////////////////////////
// Zugriffsfunktionen
template<typename T>
struct db_access 
{
public:
	void INITRECORD() 
	{
#if !defined(_NO_INITRECORD)
		memset(static_cast<T *>(this), '\0', sizeof(T));
#endif // _NO_INITRECORD
	}
 
// get associated filenumber, overload, when ReadRecord et.al. are overloaded
	static int GetFileNo(HPROJECT hPr) { return 0; }		// generic file number

	ErrCode ReadRecord (struct db_addr *pDba)
	{
		_ASSERTE(0 == T::GetFileNo(pDba->db_no) || pDba->file_no == T::GetFileNo(pDba->db_no));
		return (ErrCode)z_readrec (pDba, static_cast<T *>(this));
	}
	ErrCode WriteRecord (struct db_addr *pDba)
	{
		_ASSERTE(0 == T::GetFileNo(pDba->db_no) || pDba->file_no == T::GetFileNo(pDba->db_no));
		return (ErrCode)z_writerec(pDba, static_cast<T *>(this));
	}
	ErrCode FillNewRecord (struct db_addr *pDba)
	{
		_ASSERTE(0 == T::GetFileNo(pDba->db_no) || pDba->file_no == T::GetFileNo(pDba->db_no));
		return (ErrCode)z_fillnew(pDba, static_cast<T *>(this));
	}
	static ErrCode DisposeRecord (struct db_addr *pDba)
	{
		_ASSERTE(0 == T::GetFileNo(pDba->db_no) || pDba->file_no == T::GetFileNo(pDba->db_no));
		return (ErrCode)z_dispose(pDba);
	}
};

///////////////////////////////////////////////////////////////////////////////
// Zugriffs-Makros liefern ErrCode
#define __Read(dba,Satz)		DBASSERT(Satz.ReadRecord((struct db_addr *)&(dba)))
#define __Write(dba,Satz)		DBASSERT(Satz.WriteRecord((struct db_addr *)&(dba)))
#define __Dispose(dba, Satz)	DBASSERT(Satz.DisposeRecord((struct db_addr *)&(dba)))
#define __New(dba,Satz) 		DBASSERT(Satz.FillNewRecord((struct db_addr *)&(dba)))

///////////////////////////////////////////////////////////////////////////////
// Zugriffs-Makros liefern HRESULT
#define __ReadHR(dba,Satz)		DBASSERTHR(Satz.ReadRecord((struct db_addr *)&(dba)))
#define __WriteHR(dba,Satz)		DBASSERTHR(Satz.WriteRecord((struct db_addr *)&(dba)))
#define __DisposeHR(dba,Satz)	DBASSERTHR(Satz.DisposeRecord((struct db_addr *)&(dba)))
#define __NewHR(dba,Satz) 		DBASSERTHR(Satz.FillNewRecord((struct db_addr *)&(dba)))

#define __ReadHREx(dba,Satz)	DBASSERTHR(z_readrec((struct db_addr *)&(dba),(char *)&(Satz)))
#define __WriteHREx(dba,Satz)	DBASSERTHR(z_writerec((struct db_addr *)&(dba),(char *)&(Satz)))
#define __DisposeHREx(dba)		DBASSERTHR(z_dispose((struct db_addr *)&(dba)))
#define __NewHREx(dba,Satz) 	DBASSERTHR(z_fillnew((struct db_addr *)&(dba),(char *)&(Satz)))

///////////////////////////////////////////////////////////////////////////////
// Datensatzstrukturen
struct kcont {
	long kxmin;
	long kxmax;
	long kymin;
	long kymax;
};
	
struct kal : 
	public db_access<kal> 
{
public:
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

struct kpl : 
	public db_access<kpl>
{
public:
	long zkpvgo;
	long zkpkfk;
	struct {
		long kpx;
		long kpy;
	} pkrd;
	long zkpma;

	kpl() { INITRECORD(); }
};

struct spl : 
	public db_access<spl>
{
public:
	long spx;
	long spy;
	long znsp;
	long dummy[10];		// #HK971226: ab V5.00.00.016 mit 'longspl'

	spl() { INITRECORD(); }
};
// #HK971226: ab V5.00.00.016 mit 'longspl'
#define NUMSPLCOORDS	6
struct longspl : 
	public db_access<longspl>
{
public:
	long spxl[NUMSPLCOORDS];
	long spyl[NUMSPLCOORDS];
	long znspl;

	longspl() { INITRECORD(); }
};

struct mal : 
	public db_access<mal>
{
public:
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

struct kfk : 
	public db_access<kfk>
{
public:
	long zkfkk;
	long znkfk;

	kfk() { INITRECORD(); }
};

struct kfm : 
	public db_access<kfm>
{
public:
	long zkfmk;
	long znkfm;

	kfm() { INITRECORD(); }
};

struct obl : 
	public db_access<obl>
{
public:
	long zovor;
	long zoid;
	long zovom;
	long zokp;
	long zovol;
	long zovoma;
	char rmaske;
	char status;
	struct _GUID guid;		// #HK970908: ab V5.00.00.014 mit UniqueID
	double oblcreate;		// #HK010704: ab V5.00.00.019 creation date
	double oblmodify;		// #HK010704: ab V5.00.00.019 modification date

	obl() { INITRECORD(); }

// get associated filenumber, overload, when ReadRecord et.al. are overloaded
#if defined(__TRIAS01DLL__)
	static int GetFileNo(HPROJECT hPr) { return VERSION0500000E <= LocGetDBVersion(hPr) ? OBL_NEW : OBL_OLD; }
#else
	static int GetFileNo(HPROJECT hPr) { return VERSION0500000E <= GetDBVersion(hPr) ? OBL_NEW : OBL_OLD; }
#endif // defined(__TRIAS01DLL__)

	ErrCode WriteRecord (struct db_addr *pDba)
	{
		oblmodify = GetCurrentTimeAsDATE();
		return db_access<obl>::WriteRecord(pDba);
	}
	ErrCode FillNewRecord (struct db_addr *pDba)
	{
		::CoCreateGuid(&guid);
		oblcreate = oblmodify = GetCurrentTimeAsDATE();
		return db_access<obl>::FillNewRecord(pDba);
	}
};

struct rel : 
	public db_access<rel>
{
public:
	long zrera;
	long zol1;
	long zol2;

	rel() { INITRECORD(); }
};

struct idl : 
	public db_access<idl>
{
public:
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

	struct _GUID idguid;	// #HK010704: ab V5.00.00.019 mit UniqueID
	double idcreate;		// #HK010704: ab V5.00.00.019 mit creation date
	double idmodify;		// #HK010704: ab V5.00.00.019 mit modification date

	idl() { INITRECORD(); }

// get associated filenumber, overload, when ReadRecord et.al. are overloaded
#if defined(__TRIAS01DLL__)
	static int GetFileNo(HPROJECT hPr) { return VERSION05000013 <= LocGetDBVersion(hPr) ? IDL_NEW : IDL_OLD; }
#else
	static int GetFileNo(HPROJECT hPr) { return VERSION05000013 <= GetDBVersion(hPr) ? IDL_NEW : IDL_OLD; }
#endif // defined(__TRIAS01DLL__)

	ErrCode WriteRecord (struct db_addr *pDba)
	{
		idmodify = GetCurrentTimeAsDATE();
		return db_access<idl>::WriteRecord(pDba);
	}
	ErrCode FillNewRecord (struct db_addr *pDba)
	{
		::CoCreateGuid(&idguid);
		idcreate = idmodify = GetCurrentTimeAsDATE();
		return db_access<idl>::FillNewRecord(pDba);
	}
};

struct mkl : 
	public db_access<mkl>
{
public:
	long mk;
	long typ;
	long zmkvmo;

	double mklcreate;		// #HK010704: ab V5.00.00.019 mit creation date
	double mklmodify;		// #HK010704: ab V5.00.00.019 mit modification date

	mkl() { INITRECORD(); }

// get associated filenumber, overload, when ReadRecord et.al. are overloaded
	static int GetFileNo(HPROJECT hPr) { return MKL; }

	ErrCode WriteRecord (struct db_addr *pDba)
	{
		mklmodify = GetCurrentTimeAsDATE();
		return db_access<mkl>::WriteRecord(pDba);
	}
	ErrCode FillNewRecord (struct db_addr *pDba)
	{
		mklcreate = mklmodify = GetCurrentTimeAsDATE();
		return db_access<mkl>::FillNewRecord(pDba);
	}
};

struct mi : 
	public db_access<mi>
{
public:
	long znmi;
	long mw[2];

	mi() { INITRECORD(); }
};

// ab Version 011 ist dbt jetzt fdbt
struct fdbt : 
	public db_access<fdbt>
{
public:
	char infof[44];
	long zndbtf;

	fdbt() { INITRECORD(); }
};

struct vgo : 
	public db_access<vgo>
{
public:
	long zvgoo;
	long znvgo;

	vgo() { INITRECORD(); }
};

struct vzo : 
	public db_access<vzo>
{
public:
	long zvzoo;
	long znvzo;

	vzo() { INITRECORD(); }
};

struct vol : 
	public db_access<vol>
{
public:
	long zvolk;
	long znvol;

	vol() { INITRECORD(); }
};

struct voa : 
	public db_access<voa>
{
public:
	long zvomam;
	long znvoma;

	voa() { INITRECORD(); }
};

struct vom : 
	public db_access<vom>
{
public:
	long zvommk;
	long znmk;
	long zvommi;
	long zvomo;		// ab Version 011

	vom() { INITRECORD(); }
};

struct vmo : 
	public db_access<vmo>
{
public:
	long zvmoo;
	long znvmo;

	vmo() { INITRECORD(); }
};

// #HK971221: äquivalent zu vmo (ab Version 015)
struct mcodeb : 
	public db_access<mcodeb>
{
public:
	struct mcodebkey {
		long mcodek;
		long zvmook;	
	} mcodebkey;
	long zvmonk;
	long zvmopk;

	mcodeb() { INITRECORD(); }
};

// #HK990622: äquivalent zu vmo (ab Version 017)
struct mcodex : 
	public db_access<mcodex>
{
public:
	struct mcodexkey {
		long zvmoox;	
		long mcodex;
	} mcodexkey;
	long zvmonk;
	long zvmopk;

	mcodex() { INITRECORD(); }
};

struct vor : 
	public db_access<vor>
{
public:
	long zvorel;
	long znvor;

	vor() { INITRECORD(); }
};

struct vio : 
	public db_access<vio>
{
public:
	long zvioo;
	long znvio;

	vio() { INITRECORD(); }
};

// #HK971221: äquivalent zu vio (ab Version 015)
struct identb : 
	public db_access<identb>
{
public:
	struct identbkey {
		long identk;
		long zviook;	// höchstwertige 3 Bits enthalten zusätzliche Infos (s. LINKTYPE_...)
	} identbkey;
	long zvionk;
	long zviopk;

	identb() { INITRECORD(); }
};

// #HK990622: äquivalent zu vio (ab Version 017)
struct identx : 
	public db_access<identx>
{
public:
	struct identxkey {
		long zvioox;	// höchstwertige 3 Bits enthalten zusätzliche Infos (s. LINKTYPE_...)
		long identx;
	} identxkey;
	long zvionk;
	long zviopk;

	identx() { INITRECORD(); }
};

struct vre : 
	public db_access<vre>
{
public:
	long zvrere;
	long znvre;

	vre() { INITRECORD(); }
};

struct ral :	
	public db_access<ral>
{
public:
	long rat;
	long zravre;
	short maske;

	ral() { INITRECORD(); }
};

struct pol : 
	public db_access<pol>
{
public:
	long zpvgo;
	long zpkfk;
	struct {
		long px;
		long py;
	} kpkrd;
	long zpma;

	pol() { INITRECORD(); }
};

struct head : 
	public db_access<head>
{
public:
	long hdidn[4];
	char text[60];		// #HK960126: nur 60 Bytes, dafür Flags
	long hdrflags;
	long zntext;

	head() { INITRECORD(); }
};

struct fhead : 
	public db_access<fhead>
{
public:
	char textf[80];
	long ztextf;

	fhead() { INITRECORD(); }
};

#define MAXVIEWNAMESIZE			_MAX_PATH
#define MAXVIEWNAMESIZE_GEODB	40
struct sicht : 
	public db_access<sicht>
{
public:
	char sichtname[MAXVIEWNAMESIZE_GEODB];
	short idnum;
	short idset;
	short onnum;
	short onset;
	long objrgn;		// ab Version 006
	long zmerkm;		// ab Version 007
	long zrelat;

	sicht() { INITRECORD(); }
};

struct attribs : 
	public db_access<attribs>
{
public:
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

struct pattribs : 
	public db_access<pattribs>
{
public:
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

struct lattribs : 
	public db_access<lattribs>
{
public:
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

struct fattribs : 
	public db_access<fattribs>
{
public:
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

struct tattribs : 
	public db_access<tattribs>
{
public:
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

struct reltyp : 
	public db_access<reltyp>
{
public:
	long zhrel;
	long zvrelo;
	long zvrelu;
	long zbrela;
	long zbrelp;

	reltyp() { INITRECORD(); }
};

// ab Version 011 ist dbt zerlegt
struct kdbt : 
	public db_access<kdbt>
{
public:
	long llen;
	long zmivom;
	char info[36];
	long zndbt;

	kdbt() { INITRECORD(); }
};
#define SIZEOF_KDBT_INFO	36		// sizeof(kdbt::info)

#endif // !defined(_RISDB_NO_STRUCTS)

///////////////////////////////////////////////////////////////////////////////
// 
typedef enum tagLINKTYPE {
	LINKTYPE_Unknown = 0x0,
	LINKTYPE_Point = 0x1,
	LINKTYPE_Line = 0x2,
	LINKTYPE_Area = 0x3,
	LINKTYPE_Text = 0x4,
	LINKTYPE_Complex = 0x5,
	LINKTYPE_DontCare = 0x6,
	LINKTYPE_Mask = 0x7,
} LINKTYPE;
#define TYPETOLINK(o,t)	(long)((((unsigned long)t) << 29) | (((unsigned long)o) & ~(LINKTYPE_Mask << 29)))
#define LINKTOTYPE(l)	(LINKTYPE)((((unsigned long)l) & (LINKTYPE_Mask << 29)) >> 29)
#define LINKTOLINK(l)	(long)(((unsigned long)l) & ~(LINKTYPE_Mask << 29))

#include <poppack.h>

#endif // !defined(_RISDB_H__D2BEE714_7A21_11D1_9763_00A024D6F582__INCLUDED_)
