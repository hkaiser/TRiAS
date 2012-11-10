// Memberfunktionen für Export von Teilen der internen DB
// File: EXPORT.CXX

#include "stdafx.h"
#include "../resource.h"

#if defined(_USE_LEGACY_CODE)
#undef _USE_LEGACY_CODE
#endif

#pragma comment(lib, "Tfrmwork.lib")
#pragma comment(lib, "TRiAS322.lib")
#pragma comment(lib, "IxtAtd50.lib")

#define	NOPROPERTSHEET
#define	NOTOOLTIP
#define	NOTOOLBAR
#define	NOSTATUSBAR
#define	NOUPDOWN
#define	NOPROGRESS
#define	NOANIMATE
#define	NOWIN95CONTROLS
#define	__ON_COMMAND	ON_COMMAND
#undef	ON_COMMAND
#include <CommonVu.hxx>
#include <CommonVu/CTRTYPES.HXX>
#include <CommonVu/TAssert.hxx>
#undef	ON_COMMAND
#define	ON_COMMAND	__ON_COMMAND

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
//#include <xtsnaux.hxx>
#include <tstring>

#include <errcodes.hxx>
//#include <ErrInst.hxx>
#include <hdrentrx.hxx>		// Definition von HDRKEYLENGTH

typedef	char* pchar;
typedef	unsigned int uint;

#include <ImpExp.hxx>
#include <dllbind.hxx>
#include <KoOrd.h>
#include <VisInfo.hxx>

//#include <Ident.hxx>
#include "Export.hxx"
#include "Strings.h"

#undef TX_ASSERT
#define TX_ASSERT	_ASSERTE

inline int db_error( int p1, int p2 ) {
	_ASSERTE(0);
	return p1;
}

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MAXPOSLONG      2147483647L     /* 2^31 -1 */ 

#undef HUGELIMIT
#define HUGELIMIT (64000/sizeof(double))


inline HRESULT GetHeaderEntry( UINT nID, char _buf[HDRENTRYTEXTLEN+1] ) {
	USES_CONVERSION;
	CComBSTR	strEntry;
	strEntry.LoadString(nID);
	GEODBHDRENTRY	H;
	INITSTRUCT( H, H );
	memset( H.hdrKey, ' ', HDRKEYLENGTH );
	memcpy( H.hdrKey, W2A(strEntry), __min( strEntry.Length(), HDRKEYLENGTH ) );
	H.lphdrText = _buf;	// Buffer bereitstellen
	H.hdrTextLen = HDRENTRYTEXTLEN;
	memset( _buf, '\0', sizeof(_buf) );
	DEX_ReadGeoDBHdrEntry( H );
	return S_OK;
}

inline double GetHeaderEntry( UINT nID, double dDefault ) {
	char	_buf[HDRENTRYTEXTLEN+1];
	if( FAILED( GetHeaderEntry( nID, _buf ) ) ) {
		return dDefault;
	}
	return atof(_buf);
}

// globale Daten
//extern ExtDirisWindow *CurrActDirisW;

/////////////////////////////////////////////////////////////////////////////
// externe Funktionen
//short OTypToBits (ObjTyp iOTyp);
//long RetrieveObjNameMCodeIdent (DatenBasisObjekt &rDBO, long lIdent, bool *pfForce = NULL);

// lokale statische Funktionen
//static void *GetMerkmalsWert (PBD_Merkmal *pM);

// Funktionen für Export ------------------------------------------------------
// Konstruktor
//XXExport::Export (HWND hWnd, LPCSTR FormatName, LPCSTR DLLName, LPCSTR OutName, DatenBasisObjekt &rDBO, OutMode OutFlag) 
Export::Export( HWND hWnd, LPCSTR FormatName, LPCSTR DLLName, LPCSTR OutName, OutMode OutFlag )
	: DLLBind (DLLName)
//XX	, _DB (rDBO.DB())
//XX	, m_rDBO(rDBO)
//XX	, m_pCTF(rDBO.pCT())
{
// Parameter validieren
	if (FormatName == NULL || DLLName == NULL || OutName == NULL)
		return;		// Fehler

// Daten initialisieren
	_ExpData = NULL;
	strcpy (_ExportName, FormatName);       // Ausgabeformatnamen merken
	_NameLen = strlen (FormatName);         // Länge dieses Namens
	_2ndTransform = FALSE;

// DLL binden
//XX	if (hLib() == NULL) {
	// DLL nicht gefunden
		db_error (WC_NOLIBRARY, RC_ctExport);
		/*XX*/ _ASSERTE(NULL);
//XX		return;
//XX	}

	{
//XX	ErrInstall EI (WC_NOTFOUND); // Fehlermeldung unterdrücken

	// Koeffizienten aus DB-Header lesen, evtl. Defaultwerte verwenden
	//XX	K11 = HeaderEntry (_DB, IDS_KOEFF11).EntryDouble(1.0);
	//XX	K12 = HeaderEntry (_DB, IDS_KOEFF12).EntryDouble(0.0);
	//XX	K21 = HeaderEntry (_DB, IDS_KOEFF21).EntryDouble(0.0);
	//XX	K22 = HeaderEntry (_DB, IDS_KOEFF22).EntryDouble(1.0);
	//XX	OX = HeaderEntry (_DB, IDS_OFFSETX).EntryDouble(0.0);
	//XX	OY = HeaderEntry (_DB, IDS_OFFSETY).EntryDouble(0.0);

	/*XX*/	K11 = GetHeaderEntry (IDS_KOEFF11, 1.0);
	/*XX*/	K12 = GetHeaderEntry (IDS_KOEFF12, 0.0);
	/*XX*/	K21 = GetHeaderEntry (IDS_KOEFF21, 0.0);
	/*XX*/	K22 = GetHeaderEntry (IDS_KOEFF22, 1.0);
	/*XX*/	OX = GetHeaderEntry (IDS_OFFSETX, 0.0);
	/*XX*/	OY = GetHeaderEntry (IDS_OFFSETY, 0.0);
	}

// Ausgabe initialisieren
	ExportBegin (hWnd, (char *)OutName, OutFlag);       	// Datei anlegen

// Koordinaten nicht konvertieren
	m_fConvert = GetExportCaps (EC_NoConvertCoords) ? false : true;
}

// Destruktor
Export::~Export (void) 
{
//XX	if (hLib() != NULL) 
//XX		ExportEnd ();                   // alles beenden
}

// Setzen der Parameter für die zusätzliche Koordinatentransformation ---------
void Export::SetTransParams (double kx, double ky, double ox, double oy) 
{
	KX = kx;
	KY = ky;
	OffsetX = ox;
	OffsetY = oy;
	_2ndTransform = TRUE;
}


// Eigentliche Member ---------------------------------------------------------
ErrCode Export::ExportBegin (HWND hWnd, char *FileName, OutMode OutFlag) {
EXPBEGFUNC ExpBegin = (EXPBEGFUNC)GetProcAddress (ExpName (IDS_EXPBEGIN));
int EC = EC_OKAY;

	if (ExpBegin) {
	// DLL-Funktion rufen
		if ((EC = (*ExpBegin)(FileName, _of, OutFlag, hWnd)) != EC_OKAY) {
			db_error (EC, RC_ExportBegin);
			if (EC < 0)	return (ErrCode)EC;
			else		return EC_OKAY;
		}
	} else {
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportBegin);
	}

	return EC_OKAY;
}

ErrCode Export::ExportTrailer (const char *lpTrailerInfo) 
{
EXPTRAILFUNC ExpTrailer = (EXPTRAILFUNC)GetProcAddress (ExpName (IDS_EXPTRAILER));
int EC = EC_OKAY;

	if (ExpTrailer) {
	// DLL-Funktion rufen
		if ((EC = (*ExpTrailer)(_of, lpTrailerInfo)) != EC_OKAY) {
			db_error (EC, RC_ExportTrailer);
			if (EC < 0)	return (ErrCode)EC;
			else		return EC_OKAY;
		}
	} else {
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportTrailer);
	}

	return EC_OKAY;
}

ErrCode Export::ExportEnd (void) 
{
EXPENDFUNC ExpEnd = (EXPENDFUNC)GetProcAddress (ExpName (IDS_EXPEND));
int EC = EC_OKAY;

	if (ExpEnd) {
	// DLL-Funktion rufen
		if ((EC = (*ExpEnd)(_of)) != EC_OKAY) {
			db_error (EC, RC_ExportEnd);
			if (EC < 0)	return (ErrCode)EC;
			else		return EC_OKAY;
		}
	} else {
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportEnd);
	}

	return EC_OKAY;
}

ErrCode Export::ExportBreak (void) 
{
EXPENDFUNC ExpBreak = (EXPENDFUNC)GetProcAddress (ExpName (IDS_EXPBREAK));
int EC = EC_OKAY;

	if (ExpBreak) {
	// DLL-Funktion rufen
		if ((EC = (*ExpBreak)(_of)) != EC_OKAY) {
			db_error (EC, RC_ExportBreak);
			if (EC < 0)	return (ErrCode)EC;
			else		return WC_RETURN;
		}
	} else {
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportBreak);
	}

	return WC_RETURN;
}

ErrCode Export::ExportHeader (const char *lpHeaderInfo) 
{
EXPFUNC ExpHeader = (EXPFUNC)GetProcAddress (ExpName (IDS_EXPHEADER));
int EC = EC_OKAY;

	if (ExpHeader) {
	// DLL-Funktion rufen
		if ((EC = (*ExpHeader)(_of, lpHeaderInfo)) != EC_OKAY) {
			db_error (EC, RC_ExportHeader);
			if (EC < 0)	return (ErrCode)EC;
			else		return EC_OKAY;
		}
	} else {
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportHeader);
	}

	return EC_OKAY;
}

ErrCode Export::ExportDescription (LPCSTR lpKeyInfo, LPCSTR lpDescInfo, DWORD dwStyle) 
{
int EC = EC_OKAY;

#if defined(WIN32)
EXPDESCFUNCEX ExpDescEx = (EXPDESCFUNCEX)GetProcAddress (ExpName (IDS_EXPDESCEX));

	if (ExpDescEx) {
	// DLL-Funktion rufen
		if ((EC = (*ExpDescEx)(_of, lpKeyInfo, lpDescInfo, dwStyle)) != EC_OKAY) {
			db_error (EC, RC_ExportDescription);
			if (EC < 0)	
				return (ErrCode)EC;
		}
		return EC_OKAY;
	}
#endif // WIN32

EXPDESCFUNC ExpDesc = (EXPDESCFUNC)GetProcAddress (ExpName (IDS_EXPDESC));

	if (ExpDesc) {
	// DLL-Funktion rufen
		if ((EC = (*ExpDesc)(_of, lpKeyInfo, lpDescInfo)) != EC_OKAY) {
			db_error (EC, RC_ExportDescription);
			if (EC < 0)	return (ErrCode)EC;
			else		return EC_OKAY;
		}
	} else {
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportDescription);
	}

	return EC_OKAY;
}

ErrCode Export::ExportComment (const char *lpComment) 
{
EXPFUNC ExpComment = (EXPFUNC)GetProcAddress (ExpName (IDS_EXPCOMMENT));

	if (ExpComment) {
	// DLL-Funktion rufen
	int EC = EC_OKAY;

		if ((EC = (*ExpComment)(_of, lpComment)) != EC_OKAY) {
			db_error (EC, RC_ExportComment);
			if (EC < 0)	return (ErrCode)EC;
			else		return EC_OKAY;
		}
	} else {
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportComment);
	}

	return EC_OKAY;
}

ErrCode Export::ExportIdentDescription (IdentDescription &ID) 
{
EXPIDENTDESCFUNC ExpIdent = (EXPIDENTDESCFUNC)GetProcAddress (ExpName (IDS_EXPIDENTDESC));

	if (ExpIdent) {
	// DLL Funktion rufen
	int EC = EC_OKAY;

		if ((EC = (*ExpIdent)(ID)) != EC_OKAY) {
			db_error (EC, RC_ExportIdentDescription);
			if (EC < 0)	return (ErrCode)EC;
			else		return EC_OKAY;
		}
	} else {
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportIdentDescription);
	}

	return EC_OKAY;
}

ErrCode Export::ExportMerkmalDescription (MerkmalDescription &MD) 
{
EXPMERKMALDESCFUNC ExpMerkmal = (EXPMERKMALDESCFUNC)GetProcAddress (ExpName (IDS_EXPMERKMALDESC));

	if (ExpMerkmal) {
	// DLL Funktion rufen
	int EC = EC_OKAY;

		if ((EC = (*ExpMerkmal)(MD)) != EC_OKAY) {
			db_error (EC, RC_ExportMerkmalDescription);
			if (EC < 0)	return (ErrCode)EC;
			else		return EC_OKAY;
		}
	} else {
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportMerkmalDescription);
	}

	return EC_OKAY;
}

short Export::GetExportCaps (ExportCapability ExpCap) 
{
EXPCAPSFUNC ExpCapsFunc = (EXPCAPSFUNC)GetProcAddress (ExpName (IDS_EXPCAPS));

	if (ExpCapsFunc) 	// DLL rufen
		return (*ExpCapsFunc)(ExpCap);

	return -1;	// Fehler
}

// Exportieren der eigentlichen Daten -----------------------------------------
char *ConvertFromNL (char *pText);	// '\n' -> "\n"

//XXErrCode Export::ExportData (GeoObjekt &GO, MerkmalsListe &ML, char *pModUId, bool fForceText) 
/*XX*/	ErrCode Export::ExportData (long lONr, char *, bool fForceText )
{
// evtl. Funktionspointer anfordern
	if (_ExpData == NULL) {
		_ExpData = (EXPDATAFUNC)GetProcAddress (ExpName (IDS_EXPDATA));
		if (_ExpData == NULL) {
		// Funktion nicht vorhanden
			return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportData);
		}
	}

// MerkmalsFeld anfordern
//XXulong MCnt = ML.Count();
	
//XX	if (GO.isA() == OT_TEXT || GO.isA() == OT_LABEL) 
//XX		MCnt++;		// zusätzliches Merkmal bei OT_TEXTIND

//XXMFELD *pMF = NULL;

//XX	TX_TRY(pMF = new MFELD [MCnt +2]);	// Reserve für evtl. nicht existierenden Objektnamen
//XX	if (pMF == NULL) 
//XX		return (ErrCode)db_error (EC_NOMEMORY, RC_ExportData);

//XX	memset (pMF, '\0', (size_t)(MCnt+2)*sizeof(MFELD));

//XXlong i = 0;
//XXshort j = 0;
//XXCTable t(ML);

// Nachfragen, wieviele Merkmale überhaupt unterstützt werden
//XXshort numMerkmale = GetExportCaps (EC_Merkmale);
//XXlong writtenCode = -1L;

//XX	if (t.First() && numMerkmale > 0) {
	// normales GeoObjekt und hat mind ein Merkmal
//XX		if (GO.isA() == OT_TEXT || GO.isA() == OT_LABEL) {
		// Textobjekt: Text lesen
//XX		char *tmpPtr = ((BasicGeoText *)&GO) -> TextBase();

//XX			pMF[0].MTyp = 't';
//XX			pMF[0].MWert = NULL;
//XX			if (tmpPtr != NULL) {
//XX				pMF[0].MText = ConvertFromNL (tmpPtr);
//XX				if (pMF[0].MText != NULL) {
//XX					if (TOT_TEXTINDOBJPROP == ((BasicGeoText *)&GO) -> isText()) {
//XX					os_string str = g_cbIndText;

//XX						str += pMF[0].MText;
//XX						strcpy (pMF[0].MText, str.c_str());
//XX					}
//XX					AnsiToOem (pMF[0].MText, pMF[0].MText);
//XX				}
//XX			} else {
//XX				pMF[0].MText = new char [2];
//XX				if (pMF[0].MText != NULL) strcpy (pMF[0].MText, g_cbSpace);
//XX			}			

//XX		TextObjTyp ToTyp = ((BasicGeoText *)&GO) -> isText();

//XX			if (TOT_TEXT == ToTyp || fForceText) {
//XX				pMF[0].MCode = -1L;
//XX				writtenCode = DBO().DB().TOMCode();
//XX			} else if (TOT_TEXTIND == ToTyp) {
//XX			// indirektes Textobjekt
//XX				pMF[0].MCode = ((GeoTextInd &)GO).FMCode();
//XX				writtenCode = -1L;

//XX			// Unique Ident modifizieren
//XX				if (pModUId && !strcmp (pModUId, "[B]"))
//XX					pModUId = "[P]";
//XX			} else {
//XX				TX_ASSERT(TOT_TEXTINDOBJPROP == ToTyp);

//XX				pMF[0].MCode = -1L;
//XX				writtenCode = DBO().DB().TOMCode();

//XX			// Unique Ident modifizieren
//XX				if (pModUId && !strcmp (pModUId, "[B]"))
//XX					pModUId = "[P]";
//XX			}
//XX			j = 1;
//XX		} 
//XX		else if (numMerkmale != SHRT_MAX) {		// nicht uneingeschränkt
//		ProFile PF (DBO().DB().GetDBName());
//		char outBuff[MAX_OKS_LEN];
//
//			ClassFromIdent (GO.Id(), outBuff, sizeof(outBuff));

//		long ObjNameCode = PF.GetObjNameCode (outBuff, &fForceMCode);

//XX		bool fForceMCode = false;
//XX		long ObjNameCode = RetrieveObjNameMCodeIdent (DBO(), GO.Id(), &fForceMCode);

//XX			if (t.Find (&ObjNameCode)) {
//XX			PBD_MerkmalLock l(t);
//XX				if (l) {	// MerkmalsCode gefunden
//XX				// wichtigsten MerkmalsCode zuerst
//XX					pMF[j].MCode = l -> GetCode();
   //XX
//XX				char *tmpPtr = l -> GetMerkmalsText();
   //XX
//XX					pMF[j].MText = ConvertFromNL (tmpPtr);
//XX					DELETE_OBJ (tmpPtr);
//XX					if (pMF[j].MText)
//XX						AnsiToOem (pMF[j].MText, pMF[j].MText);
//XX					pMF[j].MTyp = l -> MTyp();
//XX					writtenCode = l -> GetCode();
   //XX
//XX				// eigentlichen Merkmalswert merken
//XX					pMF[j].MWert = GetMerkmalsWert (l);
//XX					j++;
//XX				}
//XX			} else if (fForceMCode) {
//XX				pMF[j].MCode = ObjNameCode;
//XX				pMF[j].MText = NULL;
//XX				pMF[j].MTyp = 'A';
//XX				pMF[j].MWert = NULL;
   //XX
//XX				writtenCode = ObjNameCode;
//XX				j++;
//XX			}
//XX		}
//XX		for (t.First(); t.Valid(); t.Next()) {
//XX		PBD_MerkmalLock l(t);
//XX		
//XX			if (l) {
//XX				if (!ML.isSystem() && l -> isSystem()) 
//XX					continue;	// Systemmerkmal
   //XX
//XX				if ('a' != tolower(l -> isA()))
//XX					continue;	// kein Objektmerkmal
//XX				if (l -> GetCode() == writtenCode)
//XX					continue;	// war schon
   //XX
//XX				pMF[j].MCode = l -> GetCode();
   //XX
//XX			char *tmpPtr = l -> GetMerkmalsText();
   //XX
//XX				pMF[j].MText = ConvertFromNL (tmpPtr);
//XX				DELETE_OBJ (tmpPtr);
//XX				if (NULL != pMF[j].MText)
//XX					AnsiToOem (pMF[j].MText, pMF[j].MText);
   //XX
//XX				pMF[j].MTyp = l -> MTyp();
   //XX
//XX			// eigentlichen Merkmalswert merken
//XX				pMF[j].MWert = GetMerkmalsWert (l);
//XX				j++;	// nächstes Element
//XX			}
//XX		}
//XX	} 
//XX	else if (GO.isA() == OT_TEXT || GO.isA() == OT_LABEL) {
//XX	// Textobjekt: Text lesen (alte Textobjekte haben keine Merkmale)
//XX	char *tmpPtr = ((BasicGeoText *)&GO) -> TextBase();
   //XX
//XX		pMF[0].MCode = -1L;
//XX		if (tmpPtr != NULL) {
//XX			pMF[0].MText = ConvertFromNL (tmpPtr);
//XX			if (pMF[0].MText != NULL) {
//XX				if (TOT_TEXTINDOBJPROP == ((BasicGeoText *)&GO) -> isText()) {
//XX				os_string str = g_cbIndText;
   //XX
//XX					str += pMF[0].MText;
//XX					strcpy (pMF[0].MText, str.c_str());
//XX				}
//XX				AnsiToOem (pMF[0].MText, pMF[0].MText);
//XX			}
//XX		} else {
//XX			pMF[0].MText = new char [2];
//XX			if (pMF[0].MText != NULL) strcpy (pMF[0].MText, g_cbSpace);
//XX		}			
   //XX
//XX		pMF[0].MTyp = 't';
//XX		pMF[0].MWert = NULL;
   //XX
//XX		if (((BasicGeoText *)&GO) -> isText() == TOT_TEXTIND && !fForceText) {
//XX		// indirektes Textobjekt
//XX			pMF[0].MCode = ((GeoTextInd &)GO).FMCode();
   //XX
//XX		// Unique Ident modifizieren
//XX			if (pModUId && !strcmp (pModUId, "[B]"))
//XX				pModUId = "[P]";
//XX		}
   //XX
//XX		j = 1;
//XX	}
//XX
//XX	pMF[j].MCode = 0;       // letzter Satz
//XX	pMF[j].MText = NULL;
//XX	pMF[j].MWert = NULL;
   //XX
// Geometrie umsetzen
//XXGSTRUCT GS;						// Geometrie-Struktur
//XXKoOrd *x = NULL, *y = NULL;		// HilfsFelder für Geometrie
//XXlong *cnt = NULL;
//XXBOOL fHuge = FALSE;

//XX	GS.Id = GO.Id();
//XX	GS.ON = GO.ObjNr();
//XX	switch (GS.Typ = GO.isA()) {
//XX	case OT_LABEL:
//XX	case OT_TEXT:
//XX		GS.Typ = OT_TEXT;		// als normalen Text exportieren
//XX		if (pModUId == NULL) 
//XX			pModUId = "[T]";
	// hier durchfallen
	// ...
//XX	case OT_PUNKT:
//XX		GS.GSize = 1;
//XX		GS.x = new double [1];
//XX		GS.y = new double [1];
//XX		x = new KoOrd [1];
//XX		y = new KoOrd [1];
//XX		cnt = new long [2];
//XX		if (GS.x == NULL || GS.y == NULL || 
//XX		    x == NULL || y == NULL || cnt == NULL) {
//XX			if (GS.x) delete GS.x;
//XX			if (GS.y) delete GS.y;
//XX			DELETE_OBJ (x);
//XX			DELETE_OBJ (y);
//XX			DELETE_OBJ (cnt);
//XX			return (ErrCode)db_error (EC_NOMEMORY, RC_ExportData);
//XX		}
//XX		if (GS.Typ == OT_PUNKT) {
//XX			x[0] = ((GeoPunkt *)&GO) -> GetX();
//XX			y[0] = ((GeoPunkt *)&GO) -> GetY();
//XX		} else {
//XX			x[0] = ((BasicGeoText *)&GO) -> GetX();
//XX			y[0] = ((BasicGeoText *)&GO) -> GetY();
//XX		}
//XX		cnt[0] = 1;	// ein Stützpunkt
//XX		cnt[1] = 0;	// Feldende
//XX		break;
   //XX
//XX	case OT_KANTE:
//XX		{
//XX		GeoKante *KO = (GeoKante *)&GO;
   //XX
//XX			GS.GSize = KO -> ASP();
//XX			GS.x = new __huge double [GS.GSize];
//XX			GS.y = new __huge double [GS.GSize];
//XX			x = new __huge KoOrd [GS.GSize];
//XX			y = new __huge KoOrd [GS.GSize];
//XX			fHuge = TRUE;
//XX			cnt = new long [2];
//XX			if (GS.x == NULL || GS.y == NULL || 
//XX			    x == NULL || y == NULL || cnt == NULL) {
//XX				if (GS.x) delete (double __huge *)GS.x;
//XX				if (GS.y) delete (double __huge *)GS.y;	
//XX				if (x) delete (long __huge *)x;
//XX				if (y) delete (long __huge *)y;
//XX				DELETE_OBJ (cnt);
//XX				return (ErrCode)db_error (EC_NOMEMORY, RC_ExportData);
//XX			}
//XX			KO -> GetKante (x, y, GS.GSize);
//XX			cnt[0] = GS.GSize;
//XX			cnt[1] = 0;		// Ende des Feldes
//XX		}
//XX		break;
   //XX
//XX	case OT_FLAECHE:
//XX		{
//XX		GeoFlaeche *FO = (GeoFlaeche *)&GO;
//XX		long j = 0;
//XX
//XX			cnt = new long [FO -> KantenAnz() +1];
//XX			if (cnt == NULL)
//XX				return (ErrCode)db_error (EC_NOMEMORY, RC_ExportData);
//XX			GS.GSize = 0;
//XX			for (i = 0; i < FO -> KantenAnz(); i++) {
//XX				GS.GSize += FO -> KA((short)i).ASP();
//XX				cnt[i] = FO -> KA((short)i).ASP();
//XX			}
//XX			cnt[i] = 0;	// FeldEnde
//XX			GS.x = new __huge double [GS.GSize];
//XX			GS.y = new __huge double [GS.GSize];
//XX			x = new __huge KoOrd [GS.GSize];
//XX			y = new __huge KoOrd [GS.GSize];
//XX			fHuge = TRUE;
//XX			if (GS.x == NULL || GS.y == NULL || 
//XX			    x == NULL || y == NULL) {
//XX				if (GS.x) delete (double __huge *)GS.x;
//XX				if (GS.y) delete (double __huge *)GS.y;
//XX				if (x) delete (long __huge *)x;
//XX				if (y) delete (long __huge *)y;
//XX				DELETE_OBJ (cnt);
//XX				return (ErrCode)db_error (EC_NOMEMORY, RC_ExportData);
//XX			}
//XX		// Geometrie lesen
//XX			for (i = 0, j = 0; i < FO -> KantenAnz(); i++) {
//XX			long actSize = GS.GSize - j;
//XX				
//XX				FO -> KA((short)i).GetKante (&x[j], &y[j], actSize);
//XX				j += actSize;
//XX			}
//XX		}
//XX		break;
//XX	}
//XX
//XX// Geometrie konvertieren
//XX	ConvertDCtoRC (x, y, GS);
//XX	GS.cnt = cnt;
//XX
//XX// Relationen setzen
//XXchar *pUIdent = GetUniqueIdent (GO, ML);  // evtl. Unique Ident setzen
//XX
//XX	if (pModUId != NULL && pUIdent != NULL) {
//XX	// Unique Ident für Begleitobjekt modifizieren
//XX	char *pTmp = new char [strlen(pUIdent)+strlen(pModUId)+3];
//XX
//XX		if (pTmp != NULL) {
//XX			strcpy (pTmp, pModUId);
//XX			if (pModUId[strlen(pModUId)-1] == '$' && *pUIdent == '$')
//XX				strcat (pTmp, pUIdent+1);	// nur ein '$'
//XX			else
//XX				strcat (pTmp, pUIdent);
//XX			delete pUIdent;
//XX			pUIdent = pTmp;
//XX		}
//XX	}
//XX
//XXRSTRUCT *pRS = NULL;
//XXlong AssocON = GS.ON != SHRT_MAX ? AssociatedObjekt (GO.DB().DBDesc(), GS.ON) : 0;
//XX
//XX	if (AssocON < 0) {	// zur Zeit nur Begleitobjekte
//XX		pRS = new RSTRUCT [2];
//XX		if (pRS != NULL) {
//XX			pRS[0].RCode = 0;	// Kein RCode
//XX			pRS[0].RON = -AssocON;	// abhängiges TextObjekt
//XX			pRS[0].RTyp = RT_BEGLEIT;
//XX			pRS[1].RCode = -1;	// EndeKennzeichen
//XX		}
//XX	} else {		// z.Zt. keine anderen Relationen
//XX		pRS = new RSTRUCT [1];
//XX		if (pRS != NULL) 
//XX			pRS[0].RCode = -1;
//XX	}
//XX
//XX// Daten ausgeben
ErrCode EC = EC_OKAY;
//XX
//XX	if (_ExpData) {
//XX	// DLL-Funktion rufen
//XX		if ((EC = (*_ExpData)(_of, GS, pMF, pRS, pUIdent)) != EC_OKAY) {
//XX			if (EC > 0) 
//XX				EC = EC_OKAY;
//XX		}
//XX	}
//XX	DELETE_OBJ (pUIdent);		// Unique Ident wieder freigeben
//XX	DELETE_OBJ (pRS);			// RelationsFeld wieder freigeben
//XX
//XX// MerkmalsFeld wieder freigeben
//XX	for (ulong uli = 0; uli < MCnt; uli++) {
//XX//		if (pMF[uli].MCode == 0)
//XX//			break;		// letzter Satz
//XX		DELETE_OBJ (pMF[uli].MText);
//XX		DELETE_OBJ (pMF[uli].MWert);
//XX	}
//XX	DELETE_OBJ (pMF);
//XX
//XX// Geometriefelder wieder freigeben
//XX	if (fHuge) {
//XX		if (GS.x) delete (double __huge *)GS.x;
//XX		if (GS.y) delete (double __huge *)GS.y;
//XX		if (x) delete (long __huge *)x;
//XX		if (y) delete (long __huge *)y;
//XX	} else {
//XX		if (GS.x) delete GS.x;
//XX		if (GS.y) delete GS.y;
//XX		DELETE_OBJ (x);
//XX		DELETE_OBJ (y);
//XX	}
//XX	DELETE_OBJ (cnt);
//XX
return EC;
}

// Geometrie in Weltkoordinaten transformieren --------------------------------
void Export::ConvertDCtoRC (KoOrd *x, KoOrd *y, GSTRUCT &GS) 
{
// Koordinaten transformieren (incl. rausrechnen der internen Skalierung)
	if (x == NULL || y == NULL) return;

	if (m_fConvert) {
	// vollständig in Weltkoordinaten konvertieren
//XX		TX_ASSERT(NULL != m_pCTF);
		TX_ASSERT(GS.GSize > 0);

	LPVOID pData = NULL;

#if defined(_KOORD_ISDOUBLE)
		GS.x[0] = x[0];
		GS.y[0] = y[0];
#else
//XX		m_pCTF -> UnScale (x[0], y[0], &GS.x[0], &GS.y[0]);
#endif // _KOORD_ISDOUBLE
//XX		m_pCTF -> GetTransformParam (GS.x[0], GS.y[0], &pData);
//XX		m_pCTF -> TransformEx (&GS.x[0], &GS.y[0], pData);

		for (long i = 1; i < GS.GSize; i++) {
#if defined(_KOORD_ISDOUBLE)
			GS.x[i] = x[i];
			GS.y[i] = y[i];
#else
//XX			m_pCTF -> UnScale (x[i], y[i], &GS.x[i], &GS.y[i]);
#endif // _KOORD_ISDOUBLE
//XX			m_pCTF -> TransformEx (&GS.x[i], &GS.y[i], pData);
		}
//XX		m_pCTF -> FreeTransformParam (pData);
//		if (NULL != pData) CoTaskMemFree (pData);
	} else {
	// bisherige (teilweise) Konvertierung der Koordinaten
		for (long i = 0; i < GS.GSize; i++) {
			GS.x[i] = (K11 * (double)x[i] + K12 * (double)y[i] + OX);
			GS.y[i] = (K21 * (double)x[i] + K22 * (double)y[i] + OY);
		}
		if (_2ndTransform) {		// zusätzliche Transformation
			for (i = 0; i < GS.GSize; i++) {
				GS.x[i] = GS.x[i]*KX - OffsetX;
				GS.y[i] = GS.y[i]*KY - OffsetY;
			}
		}
	}
}

// private Funktionen ---------------------------------------------------------
char *Export::ExpName (unsigned int Res) {
	CComBSTR	strExpname;
	if( !strExpname.LoadString(Res) ) {
		THROW_FAILED_HRESULT( E_FAIL );
	}
	USES_CONVERSION;
	strcpy(&_ExportName[_NameLen], W2A(strExpname) );
	return _ExportName;
}

// ---------------------------------------------------------------------------
// Aufbau des ExportDlgFensters, Abfrage der Parameter und Export der ObjListe
#if defined(__IS_NOT_OBSOLETE)
ErrCode DatenBasisObjekt::doExport ( pWindow pPW, ObjContainer *OC, ObjFeld *pObjs, pWindow pWaitParent, bool fExportAll) 
{
// DialogBox aufbauen und Parameter abfragen
ExportDlg EDlg (pPW, pCT(), *this, pObjs ? false : true);
short iDlgResult; 

	EDlg.Show();

	if ((iDlgResult = EDlg.Result()) == 0) 	// Resultat der DialogBox
		return EC_OKAY;		// abgebrochen: kein Export

// Sanduhr, solange Objekte aufgesammelt werden
CEierUhr Wait (NULL != pWaitParent ? pWaitParent : pPW);

// alle zu exportierenden Objekte aufsammeln
ErrCode RC;
bool fToDelete = false;

	if (pObjs == NULL) {
	// Objekte erst aus Window selektieren
		pObjs = new ObjFeld;
		if (pObjs == NULL)
			return (ErrCode)db_error (EC_NOMEMORY, RC_doExport);
		fToDelete = true;
		
		if (OC != NULL && !EDlg.FAllObjects()) {
		// Geometrierecherche durchführen
		HRESULT hr = GIWindow (*OC, *pObjs, FALSE, TRUE);	// über aktuelle Ansicht filtern

			if (FAILED(hr)) pObjs -> EveryDelete();

		// über Sicht Filtern
//			RC = DB().IdFilter (*pObjs, EDlg.GetSight());
		} else if (EDlg.FAllObjects()) {
		// alle Objekte der Datenbank
			RC = DB().IdFilterAll (*pObjs);
		} else {
		// alle Objekte der Sicht (vom scratch)
			RC = DB().IdFilterNew (*pObjs, EDlg.GetSight());
		}
	} else {
	// über Sicht Filtern
		RC = DB().IdFilter (*pObjs, EDlg.GetSight());
	}
	if (RC != EC_OKAY) pObjs -> EveryDelete();
	 
// wenn keine Objekte zu exportieren sind, dann wieder raus
	if (pObjs -> Count() == 0) {
		if (fToDelete) {
			DELETE_OBJ (pObjs);
		}
		return (ErrCode)db_error (WC_NOTFOUND, RC_doExport);
	}
	{
	// Objekt, welches die dynamische Ankopplung an die DLL vornimmt
	Export EAct (__hWndM, EDlg.GetShortName(), EDlg.GetDLLName(), 	
			     EDlg.GetFileSpec(), *this, EDlg.OMFlag());

		if (iDlgResult == 2) {
		// TransformationsParameter einstellen
		ObjContainer OC = pObjs -> CalcCont ();
						// GesamtContainer berechnen
		ExportTransDlg ETDlg (pPW, OC, pCT()); // DialogFenster

			Wait.Hide();
			ETDlg.Show();
			if (ETDlg.Result()) {
			// alle Eingaben ok
				EAct.SetTransParams (ETDlg.KX(), ETDlg.KY(),
						     ETDlg.OX(), ETDlg.OY()
						    );
			}
		} else 
			Wait.Hide();

	// für StatusBox Zähler initialisieren
	ExportStatus ESt (pPW, pObjs -> Count(), EDlg.GetFileSpec());

		ESt.Show();

	// Header exportieren	
	char outBuff[161];
	CTable t(Shapes().ObjNumTree());	// Navigator über alle geladenen Objekte
	long Cnt = 1;
	long ContIdent = 0;	// Ident für DB-Container

		CurrActDirisW -> GetCaption (outBuff, sizeof(outBuff)-1);

	// Zeichensatz konvertieren
		AnsiToOem (outBuff, outBuff);
		if (EDlg.OMFlag() == OMOverwrite) {
		// HeaderSatz (aktuelles Caption)
			if ((RC = EAct.ExportHeader (outBuff)) != EC_OKAY) 
				goto labelError;

		// Kommentarzeile mit Copyright etc. exportieren
			if ((RC = EAct.ExportComment (ResString (IDS_COPYRIGHT, 100))) != EC_OKAY) 
				goto labelError;

		// TRiAS Version, aktuelle Zeit 
		char cbBuffer[80];

			{
			string resVersion = FakeTRiASName (IDS_SIGNONVERSION_MODAL, g_cbTRiAS);
			os_time_and_date now;
			
				TX_TRY(now = os_time_and_date::now());
				strcpy (cbBuffer, resVersion.c_str());
				strcat (cbBuffer, now.to_string(ResString(IDS_EXPORTTIMEFORMAT, 32)).c_str());
				AnsiToOem (cbBuffer, cbBuffer);
				if ((RC = EAct.ExportComment (cbBuffer)) != EC_OKAY) 
					goto labelError;
			}

		// Namen der aktuellen Ansicht als Kommentar ausgeben
			{
			ResString resView (IDS_VIEWCOMMENT, 32);

				strcpy (cbBuffer, resView);
				if (EDlg.FAllObjects()) {
				ResString resAll (IDS_ALLOBJECTS, 32);

					strcat (cbBuffer, resAll);
				} else
					strcat (cbBuffer, EDlg.GetSight());
			}
			AnsiToOem (cbBuffer, cbBuffer);
			if ((RC = EAct.ExportComment (cbBuffer)) != EC_OKAY) 
				goto labelError;

		// Entry "Caption" ausgeben
		string strCap;

			TX_ASSERT(NULL != GetViewWindow());
			GetViewWindow() -> RetrieveBasicCaption(strCap, false, true);
			strcpy (outBuff, strCap.c_str());
			AnsiToOem (outBuff, outBuff);
			if ((RC = EAct.ExportDescription (ResString (IDS_CAPTIONTEXT, 20), outBuff)) != EC_OKAY) 
				goto labelError;
		} else {
		// HeaderSatz als Comment ausgeben
			if ((RC = EAct.ExportComment (outBuff)) != EC_OKAY)
				goto labelError;
		}

	// HeaderInformationen exportieren
		if ((RC = EAct.ExportGeoDBHeader()) != EC_OKAY)
			goto labelError;
		if (ESt.Break()) {
			RC = EAct.ExportBreak();
			goto labelError;
		}

	// evtl. Schicht (IdentInfo) exportieren
		if (EAct.GetExportCaps (EC_IdentDescription)) { 
		// nur IDs für aktuell zu exportierende Sicht beschreiben
		EXPORTIDENT EI;

			if (!EDlg.FAllObjects()) {
				GetViewIdents (EDlg.GetSight(), &EI.m_pActSightIDs, EI.m_iActSightNumIDs);
				if (EI.m_iActSightNumIDs > 0) 	// einen Ident für Container merken
					ContIdent = EI.m_pActSightIDs[0];
			} else
				EI.m_pActSightIDs = NULL;		// alle exportieren

		// BeschreibungsInfo der IDs exportieren
			EI.m_pDBO = this;
			EI.m_pExp = &EAct;
			Idents().IdentTree().Every (ExportIdent, &EI);
		
		// alles wieder zurücksetzen
			DELETE_OBJ (EI.m_pActSightIDs);
		}
		if (ESt.Break()) {
			RC = EAct.ExportBreak();
			goto labelError;
		}

	// evtl. Beschreibung der Merkmale exportieren
		if (EAct.GetExportCaps (EC_MerkmalDescription)) {
		// für jedes der Merkmale der GeoDB ExportFunktion rufen
		MerkmalsListe locML (FALSE);	// keine Systemmerkmale

			FillMerkmale (*this, locML);	// alle Merkmale der DB lesen

		// alle MerkmalsBeschreibungen exportieren
			locML.Every (ExportMerkmal, &EAct);	
		}
		if (ESt.Break()) {
			RC = EAct.ExportBreak();
			goto labelError;
		}

	// GeometrieObjekte exportieren
		if (EDlg.ExportPosition()) {
		// bei Anforderung Rahmen ausgeben
			if (ContIdent == 0) ContIdent = LONG_MAX-1;
			if ((RC = EAct.ExportDBContainer (DB(), 
				ContIdent, OC ? *OC : GetExtend())) != EC_OKAY)
				goto labelError;
		}
		if (ESt.Break()) {
			RC = EAct.ExportBreak();
			goto labelError;
		}

		{
		CRing r(*pObjs);	// Navigator für alle auszugebenden Objekte

			for (r.First(); r.Valid(); r.Next(), Cnt++) {
			ObjNummerLock l(r);
			long ON = l -> _ON;	// ObjektNummer
			long AssocON = AssociatedObjekt (DB().DBDesc(), ON);
			short iBits = AssocON ? OTypToBits ((ObjTyp)DEX_GetObjectType (labs(AssocON))) : 0;

			// Objekt exportieren
	// Der Bezug zwischen Objekt und zugehörigem Textobjekt wird z.Zt. nur dann
	// richtig dargestellt, wenn beide Objekte in der aktuellen Sicht angezeigt
	// sind.
				if (AssocON > 0) {
				// ist abhängiges Textobjekt 
				long lAssocONr = RetrieveIdent(AssocON);
				bool fExportDepObj = Idents().toPaint (lAssocONr, iBits);
				bool fContainsObject = false;

					if (fExportAll) 
						fContainsObject = pObjs -> ContainsObject (lAssocONr);

					if (EDlg.FAllObjects() || fExportDepObj || fContainsObject) 
					{
					// abh. Textobjekt und Bezugsobjekt wird ausgegeben
						continue;
					} else {
						if ((RC = EAct.ExportObjekt (*this, t, ON, "", true)) != EC_OKAY) {
							TX_ASSERT(false);
							break;
						}
					}
				} else if (AssocON < 0 &&
					   (EDlg.FAllObjects() || Idents().toPaint (RetrieveIdent(-AssocON), iBits))) 
				{
				// erst TextObjekt ausgeben, Unique Ident modifizieren
					if (((RC = EAct.ExportObjekt (*this, t, -AssocON, "[B]" "$")) != EC_OKAY) ||
						 (RC = EAct.ExportObjekt (*this, t, ON)) != EC_OKAY)
					{
						TX_ASSERT(false);
						break;
					}
					Cnt++;		// bereits eins mehr exportiert
				} else
					if ((RC = EAct.ExportObjekt (*this, t, ON)) != EC_OKAY) 
					{
						TX_ASSERT(false);
						break;
					}

			// ExportStatus aktualisieren
				ESt.SetValue (Cnt, ON);

			// nach jedem Objekt bei Windows nachfragen, was noch zu tun ist
				if (ESt.Break()) {
					RC = EAct.ExportBreak();
					break;
				}
			}
		}		// Ring has to go out of scope

labelError:
		if (RC != EC_OKAY && fToDelete) {
			DELETE_OBJ (pObjs);
			return RC;
		} 

	// EndeSatz schreiben (nur wenn kein Fehler)
		if (RC == EC_OKAY)
			RC = EAct.ExportTrailer ("");
	}

	if (fToDelete) {
		DELETE_OBJ (pObjs);
	}

return RC;
}
#endif // __IS_NOT_OBSOLETE

// Rufen der entsprechenden ExportFunktion für einen Identifikator ------------
// die Variablen pEAct, pActSightIDs und ActSightNumIDs sind global in dieser 
// Datei und werden vor Beginn der zu dieser Routine gehörenden Every() -
// Funktion initialisiert (in doExport())
inline void ConvertColor (HPALETTE hPal, Color &C)
{
	if (hPal && C.Reserved() != 0) {
		GetPaletteEntries (hPal, C.Red(), 1, (PALETTEENTRY *)&C);
		C.Reserved() = 0;
	}
}

BOOL EXPORTTRIAS ExportIdent (void *pObj, void *pData) 
{
//XXEXPORTIDENT *pEI = (EXPORTIDENT *)pData;
//XXCIdentifikator *pID = (CIdentifikator *)pObj;
//XXlong lIndex;
//XX
//XX// nur testen, wenn nicht alles exportiert werden soll
//XX	if (NULL != pEI -> m_pActSightIDs &&
//XX		(lIndex = FindLong (pEI -> m_pActSightIDs, pEI -> m_iActSightNumIDs, pID -> Id())) == -1L)
//XX	{
//XX	// gehört nicht zur exportierten Sicht
//XX		return true;
//XX	}
//XX
//XXVisInfo *pVI = NULL;
//XX//CPbdIdent pbdID (pEI -> m_pDBO -> DBDesc(), pID -> Id()); // KurzText holen
//XXHPALETTE hPal = pID -> hPal();
//XXLPSTR pcKurzText = (LPSTR)pID -> GetKurzText();
//XX
//XX// VisInfo's holen und exportieren
//XX	if (!pID -> hasVI(VT_Default)) {	// keinerlei VisInfo
//XX	IdentDescription IdDesc (pID -> Id(), pcKurzText, NULL, NULL);
//XX
//XX		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
//XX		return true;
//XX	}
//XX
//XXbool fExported = false;
//XX
//XX// Punkte
//XX	if (pID -> hasVI (VT_Punkt)) {	// PVisInfo
//XX		pVI = (VisInfo *)pID -> PVI().Copy();
//XX		ConvertColor (hPal, pVI -> PrimColor());
//XX
//XX	IdentDescription IdDesc (pID -> Id(), pcKurzText, pVI, pID -> hPal());
//XX
//XX		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
//XX		DELETE_OBJ (pVI);
//XX
//XX	} else if (NULL == pEI -> m_pActSightIDs && pID -> GetOTypes (TPPunkt)) {
//XX	// Punkte in GeoDB, aber nicht in Ansicht
//XX	IdentDescription IdDesc (pID -> Id(), pcKurzText, NULL, NULL);
//XX
//XX		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
//XX		fExported = true;
//XX	}
//XX
//XX// Linien
//XX	if (pID -> hasVI (VT_Linie)) {	// LVisInfo
//XX		pVI = (VisInfo *)pID -> LVI().Copy();
//XX
//XX	IdentDescription IdDesc (pID -> Id(), pcKurzText, pVI, pID -> hPal());
//XX
//XX		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
//XX		DELETE_OBJ (pVI);
//XX
//XX	} else if (NULL == pEI -> m_pActSightIDs && pID -> GetOTypes (TPLinie) && !fExported) {
//XX	// Linien in GeoDB, aber nicht in Ansicht
//XX	IdentDescription IdDesc (pID -> Id(), pcKurzText, NULL, NULL);
//XX
//XX		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
//XX		fExported = true;
//XX	}
//XX
//XX// Flächen
//XX	if (pID -> hasVI (VT_Flaeche)) { 	// FVisInfo
//XX		pVI = (VisInfo *)pID -> FVI().Copy();
//XX		ConvertColor (hPal, pVI -> PrimColor());
//XX		ConvertColor (hPal, ((FVisInfo *)pVI) -> SecColor());
//XX
//XX	IdentDescription IdDesc (pID -> Id(), pcKurzText, pVI, pID -> hPal());
//XX
//XX		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
//XX		DELETE_OBJ (pVI);
//XX
//XX	} else if (NULL == pEI -> m_pActSightIDs && pID -> GetOTypes (TPFlaeche) && !fExported) {
//XX	// Flächen in GeoDB, aber nicht in Ansicht
//XX	IdentDescription IdDesc (pID -> Id(), pcKurzText, NULL, NULL);
//XX
//XX		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
//XX		fExported = true;
//XX	}
//XX
//XX// Texte
//XX	if (pID -> hasVI (VT_Text)) {	// TVisInfo
//XX		pVI = (VisInfo *)pID -> TVI().Copy();
//XX
//XX		((TVisInfo *)pVI) -> Rotation() /= 10;
//XX
//XX	IdentDescription IdDesc (pID -> Id(), pcKurzText, pVI, pID -> hPal());
//XX
//XX		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
//XX		DELETE_OBJ (pVI);
//XX
//XX	} else if (NULL == pEI -> m_pActSightIDs && pID -> GetOTypes (TPText) && !fExported) {
//XX	// Texte in GeoDB, aber nicht in Ansicht
//XX	IdentDescription IdDesc (pID -> Id(), pcKurzText, NULL, NULL);
//XX
//XX		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
//XX		fExported = true;
//XX	}
//XX
	return true;
}

// Exportieren der Beschreibung eines Merkmales -------------------------------
BOOL EXPORTTRIAS ExportMerkmal (void *pObj, void *pData) 
{
//XXPBD_Merkmal *pMK = (PBD_Merkmal *)pObj;
//XX
//XX	if (pMK -> isSystem()) return true;		// keine Systemmerkmale
//XX
//XXMerkmalDescription MKDesc (pMK -> GetCode(), pMK -> GetKurzText(), 
//XX			   pMK -> MTyp(), pMK -> GetMLen());
//XX
//XX	if (pData) ((Export *)pData) -> ExportMerkmalDescription (MKDesc);
//XX
return true;
}


// MerkmalsWert als Poiner auf Wert liefern -----------------------------------
//XXstatic void *GetMerkmalsWert (PBD_Merkmal *pM) 
//XX{
//XX	switch (pM -> MTyp()) {
//XX	case 'a':	// TextMerkmal
//XX		return NULL;
//XX
//XX	case 'i':	// IntegerMerkmal
//XX		{
//XX		IntMerkmal *pIM = (IntMerkmal *)pM;
//XX		long *tmpLong = new long;
//XX
//XX			if (tmpLong)
//XX				*tmpLong = pIM -> GetMerkmalsInt();
//XX			return tmpLong;
//XX		}
//XX
//XX	case 'f':
//XX		{
//XX		DoubleMerkmal *pDM = (DoubleMerkmal *)pM;
//XX		double *tmpDouble = new double;
//XX
//XX			if (tmpDouble)
//XX				*tmpDouble = pDM -> GetMerkmalsDouble();
//XX			return tmpDouble;
//XX		}
//XX
//XX	default:
//XX		return NULL;
//XX	}
//XX}

ErrCode EvalKoeffs (double *, double *, double *, double *);

LPTSTR Export::DtoA( LPTSTR _buf, LPTSTR lpsFormat, double val ) {
	sprintf( _buf, lpsFormat, val );
	return _buf;
}

// Alle Informationen aus Header der GeoDB exportieren ------------------------
ErrCode Export::ExportGeoDBHeader (void) 
{
char outBuff[80];
char tBuff[20];
char *dFormat = "%15.5f";
//XXErrCode RC; 

// 1. ScalingParameter ausgeben, Matrix invertieren
double tK11 = K11, tK12 = K12, tK21 = K21, tK22 = K22;

//XX	DBASSERT (EvalKoeffs (&tK11, &tK12, &tK21, &tK22));
	strcpy (outBuff, DtoA (tBuff, dFormat, tK11));
	strcat (outBuff, g_cbSpace);
	strcat (outBuff, DtoA (tBuff, dFormat, tK12));
	strcat (outBuff, g_cbSpace);
	strcat (outBuff, DtoA (tBuff, dFormat, tK21));
	strcat (outBuff, g_cbSpace);
	strcat (outBuff, DtoA (tBuff, dFormat, tK22));
//XX	DBASSERT (ExportDescription (ResString (IDS_SCALEKEY, 20), outBuff, HEADER_SYSTEMRO));

// 2. OffsetParameter ausgeben
	strcpy (outBuff, DtoA (tBuff, dFormat, OX));
	strcat (outBuff, g_cbSpace);
	strcat (outBuff, DtoA (tBuff, dFormat, OY));
//XX	DBASSERT (ExportDescription (ResString (IDS_OFFSETKEY, 20), outBuff, HEADER_SYSTEMRO));

// 3. PBDNamen ausgeben (nur für altes Projekt)
IStorage *pIStg = NULL;
bool fNewProject = false;

	if (DEX_GetProjectStorage (pIStg)) {
		pIStg -> Release();
		fNewProject = true;
	}

	if (!fNewProject)
		ExportHeaderEntry (IDS_PBDENTRY);

// Zahlenbasis der GeoDB (Idents/MCodes)
	if (WC_RETURN == ExportHeaderEntry (IDS_IDENTBASE, HEADER_SYSTEMRO)) {
	// neue GeoDB's haben standardmäßig 16
//XX		DBASSERT (ExportDescription (ResString (IDS_IDENTBASE, 20), fNewProject ? "16" : "10", HEADER_SYSTEMRO));
	}
	ExportHeaderEntry (IDS_MCODEBASE, HEADER_SYSTEMRO);

// 4. evtl. Unique Ident ausgeben
	ExportHeaderEntry (IDS_UNIQUEIDENT, HEADER_SYSTEMRO);
	ExportHeaderEntry (IDS_OLDUNIQUEIDENT, HEADER_SYSTEMRO);

// 5. evtl. Koordinatensystem/KoordinatenParameter ausgeben
	ExportHeaderEntry (IDS_CTFHEADER, HEADER_SYSTEMRO);
	ExportHeaderEntry (IDS_CTFMERIDIAN, HEADER_SYSTEMRO);
	ExportHeaderEntry (IDS_CTFSTREIFEN, HEADER_SYSTEMRO);
	ExportHeaderEntry (IDS_CTFSCALING, HEADER_SYSTEM);
	ExportHeaderEntry (IDS_CTFPRECISION, HEADER_SYSTEM);
	ExportHeaderEntry (IDS_SHOWGKCOORDS, HEADER_SYSTEM);

// 6. MerkmalsCode der Textobjekte exportieren
	ExportHeaderEntry (IDS_TEXTOBJMCODE, HEADER_SYSTEMRO);

// 7. sonstige Informationen ausgeben
	ExportHeaderEntry (IDS_MASSTAB);	// Bezugsmaßstab
	ExportHeaderEntry (IDS_SCROLLMODE);	// RedrawOnScroll
	ExportHeaderEntry (IDS_USEOLDPOINTSTYLE, HEADER_SYSTEM);	// UseOldPointStyle
	ExportHeaderEntry (IDS_USENEWPOINTSTYLE, HEADER_SYSTEM);	// UseNewPointStyle
	ExportHeaderEntry (IDS_POSTEXTATBASELINE);	// Bezug für Textpositionierung

// 8. auf speziellen Unwillen einzelner Herren
	ExportHeaderEntry (IDS_TKINFO);		// Mr. Karten.Vmd
	ExportHeaderEntry (IDS_TKMCODE);
	ExportHeaderEntry (IDS_TKVCODE);
	
// 9. #HK980108
	ExportHeaderEntry (IDS_ALLOWLEADINGZEROS);
	return EC_OKAY;
}

// Exportieren eines HeaderEintrages ------------------------------------------
ErrCode Export::ExportHeaderEntry (uint resID, DWORD dwStyle)
{
//XXErrInstall EI (WC_NOTFOUND);	// Fehlermeldung unterdrücken

	{
	ResString rsHE (resID, 17);
//XX	HeaderEntry hdrT (_DB, rsHE);
//XX	char *pT = hdrT.EntryText();
//XX
//XX		if (HE_INVALID != hdrT.Status() && NULL != pT)	
//XX			return ExportDescription (rsHE, pT, dwStyle);
	}

return WC_RETURN;
}


// Ausgeben eines Objektes ----------------------------------------------------
//XXErrCode Export::ExportObjekt (DatenBasisObjekt &rDBO, CTable &t, long ON, char *pModUId, bool fForceText)
ErrCode ExportObjekt( long ON, char * = NULL, bool fForceText = false)
{
//XXGeoObjekt *pGO = NULL;	// gesuchtes GeometrieObjekt
ErrCode RC = EC_OKAY;
//XXMerkmalsListe ML (&rDBO.DB(), &(rDBO.PbdDB()), ON, OBL_OLD, FALSE);
			// keine Systemmerkmale exportieren

//XX	if (t.Find(&ON)) {
//XX	// Objekt ist im Speicher
//XX	ExtShapeObjectLock l1(t);
//XX
//XX		if (l1) pGO = l1 -> operator GeoObjekt *();
//XX		else 	// Fehler
//XX			return (ErrCode)db_error (EC_NOON, RC_doExport);
//XX		if (pGO -> isA() == OT_KO) 
//XX			return EC_OKAY;
//XX		DBASSERT (ExportData (*pGO, ML, pModUId));
//XX	} else {
//XX	// Objekt muß geladen werden
//XX	HRESULT hr = rDBO.GetGI (ON, NULL, &pGO);
//XX
//XX		if (S_OK != hr) {
//XX		char cbOut[80];
//XX
//XX			wsprintf (cbOut, "Error %lx loading object %ld.", hr, ON);
//XX			ExportComment (cbOut);
//XX			return EC_OKAY;
//XX		}
//XX
//XX	// Objekt exportieren
//XX		if (pGO -> isA() != OT_KO)
//XX			RC = ExportData (*pGO, ML, pModUId, fForceText);
//XX		
//XX	// Speicher wieder freigeben
//XX		delete pGO;
//XX/*		switch (pGO -> isA()) {
//XX		case OT_PUNKT:		delete (GeoPunkt *)pGO; break;
//XX		case OT_KANTE: 		delete (GeoKante *)pGO; break;
//XX		case OT_FLAECHE:	delete (GeoFlaeche *)pGO; break;
//XX		case OT_KREIS:		delete (GeoKreis *)pGO; break;
//XX		case OT_TEXT:		delete (BasicGeoText *)pGO; break;
//XX		case OT_KO:		delete (KomplexObjekt *)pGO; break;
//XX		case OT_UNKNOWN:
//XX		default:		break;
//XX		}
//XX*/
//XX	}
//XX
return RC;
}

// Unique Ident lesen ---------------------------------------------------------
//XXchar *Export::GetUniqueIdent (GeoObjekt &GO, MerkmalsListe &ML)
char *Export::GetUniqueIdent (long lONr)
{
long lUIdent = -1L;
//XXErrInstall EI (WC_NOTFOUND);
//XX
//XX	lUIdent = HeaderEntry (_DB, IDS_UNIQUEIDENT).EntryLong (-1L);
//XX	if (lUIdent != -1L) {		// Unique Ident existiert
//XX		if (GO.isA() == OT_TEXT || GO.isA() == OT_LABEL) {	// Ist TextObjekt
//XX		long AssocON = AssociatedObjekt (GO.DB().DBDesc(), GO.ObjNr());
//XX
//XX			if (AssocON > 0) {	// Textobjekt ist abhängig
//XX			char *pUIdent = NULL;
//XX
//XX			// Unique Ident aus übergeordnetem Objekt holen
//XX				if (GetMiText (GO.DB().DBDesc(), lUIdent, AssocON, OBL_OLD, &pUIdent) != EC_OKAY)
//XX					return NULL;
//XX				AnsiToOem (pUIdent, pUIdent);
//XX				return pUIdent;
//XX			} else
//XX				return ML.GetMerkmalsText (lUIdent);
//XX		} else 				// normales Objekt
//XX		// Unique Ident aus ML holen
//XX			return ML.GetMerkmalsText (lUIdent);
//XX	}

return NULL;
}

// Wegschreiben des DB-Containers um Schichtweise Skalierung zu ermöglichen
//XXErrCode Export::ExportDBContainer (GeoDB &rDB, long Ident, ObjContainer &OC) 
//XX{
// Rahmen zusammenbauen
//KoOrd x[5], y[5];
//
//	x[0] = x[1] = x[4] = OC.XMin();
//	x[2] = x[3] = OC.XMax();
//	y[0] = y[3] = y[4] = OC.YMin();
//	y[1] = y[2] = OC.YMax();
//
//GeoFlaeche *pGF = new GeoFlaeche (rDB, (long)SHRT_MAX, Ident, x, y, 5L);
//MerkmalsListe *pML = new MerkmalsListe (FALSE);
//ErrCode RC;
//
//	if (pGF == NULL || pML == NULL) 
//		db_error (EC_NOMEMORY, RC_ExportDBContainer);
//	RC = ExportData (*pGF, *pML, NULL);
//
//	DELETE_OBJ (pGF);		// wieder freigeben
//	DELETE_OBJ (pML);		// MerkmalsListe freigeben
//
//return RC;
//XX	TX_ASSERT(FALSE);
//XX	return EC_OKAY;
//XX}
