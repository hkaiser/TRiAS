// Memberfunktionen für Export von Teilen der internen DB
// File: EXPORT.CXX

#include "triaspre.hxx"

#if !defined(_FORCE_LEGACY_CODE)
ErrCode DatenBasisObjekt::doExport (pWindow pPW, ObjContainer *OC, ObjFeld *pObjs, pWindow pWaitParent, bool fExportAll) 
{
	return EC_OKAY;
}
#else

#include <locale.h>
#include <ospace/time/timedate.h>
#include <impexp.hxx>

#include "triasres.h"
#include "copystr.h"
#include "Strings.h"

#if !defined(WIN16)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include "export.hxx"
#include "expdlg.hxx"
#include "exptrans.hxx"
#include "expstat.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


#define MAXPOSLONG      2147483647L     /* 2^31 -1 */ 

#undef HUGELIMIT
#define HUGELIMIT (64000/sizeof(double))

// globale Daten
extern ExtDirisWindow *CurrActDirisW;

/////////////////////////////////////////////////////////////////////////////
// externe Funktionen
short OTypToBits (ObjTyp iOTyp);
long RetrieveObjNameMCodeIdent (DatenBasisObjekt &rDBO, long lIdent, bool *pfForce = NULL);

// lokale statische Funktionen
static void *GetMerkmalsWert (PBD_Merkmal *pM);

// Funktionen für Export ------------------------------------------------------
// Konstruktor
Export::Export (HWND hWnd, LPCSTR FormatName, LPCSTR DLLName, 
				  LPCSTR OutName, DatenBasisObjekt &rDBO, OutMode OutFlag) 
	: DLLBind (DLLName),
	  _DB (rDBO.DB()), m_rDBO(rDBO), m_pCTF(rDBO.pCT())
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
	if (hLib() == NULL) {
	// DLL nicht gefunden
		db_error (WC_NOLIBRARY, RC_ctExport);
		return;
	}

	{
	ErrInstall EI (WC_NOTFOUND); // Fehlermeldung unterdrücken

	// Koeffizienten aus DB-Header lesen, evtl. Defaultwerte verwenden
		K11 = HeaderEntry (_DB, IDS_KOEFF11).EntryDouble(1.0);
		K12 = HeaderEntry (_DB, IDS_KOEFF12).EntryDouble(0.0);
		K21 = HeaderEntry (_DB, IDS_KOEFF21).EntryDouble(0.0);
		K22 = HeaderEntry (_DB, IDS_KOEFF22).EntryDouble(1.0);
		OX = HeaderEntry (_DB, IDS_OFFSETX).EntryDouble(0.0);
		OY = HeaderEntry (_DB, IDS_OFFSETY).EntryDouble(0.0);
	}

// Ausgabe initialisieren
	ExportBegin (hWnd, (char *)OutName, OutFlag);       	// Datei anlegen

// Koordinaten nicht konvertieren
	m_fConvert = GetExportCaps (EC_NoConvertCoords) ? false : true;
}

// Destruktor
Export::~Export (void) 
{
	if (hLib() != NULL) 
		ExportEnd ();                   // alles beenden
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
ErrCode Export::ExportBegin (HWND hWnd, char *FileName, OutMode OutFlag) 
{
EXPBEGFUNC ExpBegin = (EXPBEGFUNC)GetProcAddress (ExpName (IDS_EXPBEGIN));
int EC = EC_OKAY;

	if (ExpBegin) {
	// DLL-Funktion rufen
		if ((EC = (*ExpBegin)(FileName, _of, OutFlag, hWnd)) != EC_OKAY) {
			db_error (EC, RC_ExportBegin);
			if (EC < 0)	return (ErrCode)EC;
			else		return EC_OKAY;
		}
	} else
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportBegin);

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
	} else
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportTrailer);

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
	} else
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportEnd);

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
	} else
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportBreak);

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
	} else
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportHeader);

	return EC_OKAY;
}

ErrCode Export::ExportDescription (LPCSTR lpKeyInfo, LPCSTR lpDescInfo, DWORD dwStyle) 
{
int EC = EC_OKAY;

#if !defined(WIN16)
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
#endif // WIN16

EXPDESCFUNC ExpDesc = (EXPDESCFUNC)GetProcAddress (ExpName (IDS_EXPDESC));

	if (ExpDesc) {
	// DLL-Funktion rufen
		if ((EC = (*ExpDesc)(_of, lpKeyInfo, lpDescInfo)) != EC_OKAY) {
			db_error (EC, RC_ExportDescription);
			if (EC < 0)	return (ErrCode)EC;
			else		return EC_OKAY;
		}
	} else
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportDescription);

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
	} else
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportComment);

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
	} else
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportIdentDescription);

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
	} else
		return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportMerkmalDescription);

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

ErrCode Export::ExportData (GeoObjekt &GO, MerkmalsListe &ML, char *pModUId, bool fForceText) 
{
// evtl. Funktionspointer anfordern
	if (_ExpData == NULL) {
		_ExpData = (EXPDATAFUNC)GetProcAddress (ExpName (IDS_EXPDATA));
		if (_ExpData == NULL)
		// Funktion nicht vorhanden
			return (ErrCode)db_error (EC_NODLLFUNCTION, RC_ExportData);
	}

// MerkmalsFeld anfordern
ulong MCnt = ML.Count();
	
	if (GO.isA() == OT_TEXT || GO.isA() == OT_LABEL) 
		MCnt++;		// zusätzliches Merkmal bei OT_TEXTIND

MFELD *pMF = NULL;

	TX_TRY(pMF = new MFELD [MCnt +2]);	// Reserve für evtl. nicht existierenden Objektnamen
	if (pMF == NULL) 
		return (ErrCode)db_error (EC_NOMEMORY, RC_ExportData);

	memset (pMF, '\0', (size_t)(MCnt+2)*sizeof(MFELD));

long i = 0;
short j = 0;
CTable t(ML);

// Nachfragen, wieviele Merkmale überhaupt unterstützt werden
short numMerkmale = GetExportCaps (EC_Merkmale);
long writtenCode = -1L;

	if (t.First() && numMerkmale > 0) {
	// normales GeoObjekt und hat mind ein Merkmal
		if (GO.isA() == OT_TEXT || GO.isA() == OT_LABEL) {
		// Textobjekt: Text lesen
		char *tmpPtr = ((BasicGeoText *)&GO) -> TextBase();

			pMF[0].MTyp = 't';
			pMF[0].MWert = NULL;
			if (tmpPtr != NULL) {
				pMF[0].MText = ConvertFromNL (tmpPtr);
				if (pMF[0].MText != NULL) {
					if (TOT_TEXTINDOBJPROP == ((BasicGeoText *)&GO) -> isText()) {
					os_string str = g_cbIndText;

						str += pMF[0].MText;
						strcpy (pMF[0].MText, str.c_str());
					}
					AnsiToOem (pMF[0].MText, pMF[0].MText);
				}
			} else {
				pMF[0].MText = new char [2];
				if (pMF[0].MText != NULL) strcpy (pMF[0].MText, g_cbSpace);
			}			

		TextObjTyp ToTyp = ((BasicGeoText *)&GO) -> isText();

			if (TOT_TEXT == ToTyp || fForceText) {
				pMF[0].MCode = -1L;
				writtenCode = DBO().DB().TOMCode();
			} else if (TOT_TEXTIND == ToTyp) {
			// indirektes Textobjekt
				pMF[0].MCode = ((GeoTextInd &)GO).FMCode();
				writtenCode = -1L;

			// Unique Ident modifizieren
				if (pModUId && !strcmp (pModUId, "[B]"))
					pModUId = "[P]";
			} else {
				TX_ASSERT(TOT_TEXTINDOBJPROP == ToTyp);

				pMF[0].MCode = -1L;
				writtenCode = DBO().DB().TOMCode();

			// Unique Ident modifizieren
				if (pModUId && !strcmp (pModUId, "[B]"))
					pModUId = "[P]";
			}
			j = 1;
		} 
		else if (numMerkmale != SHRT_MAX) {		// nicht uneingeschränkt
//		ProFile PF (DBO().DB().GetDBName());
//		char outBuff[MAX_OKS_LEN];
//
//			ClassFromIdent (GO.Id(), outBuff, sizeof(outBuff));

//		long ObjNameCode = PF.GetObjNameCode (outBuff, &fForceMCode);

		bool fForceMCode = false;
		long ObjNameCode = RetrieveObjNameMCodeIdent (DBO(), GO.Id(), &fForceMCode);

			if (t.Find (&ObjNameCode)) {
			PBD_MerkmalLock l(t);
				if (l) {	// MerkmalsCode gefunden
				// wichtigsten MerkmalsCode zuerst
					pMF[j].MCode = l -> GetCode();

				char *tmpPtr = l -> GetMerkmalsText();

					pMF[j].MText = ConvertFromNL (tmpPtr);
					DELETE_OBJ (tmpPtr);
					if (pMF[j].MText)
						AnsiToOem (pMF[j].MText, pMF[j].MText);
					pMF[j].MTyp = l -> MTyp();
					writtenCode = l -> GetCode();

				// eigentlichen Merkmalswert merken
					pMF[j].MWert = GetMerkmalsWert (l);
					j++;
				}
			} else if (fForceMCode) {
				pMF[j].MCode = ObjNameCode;
				pMF[j].MText = NULL;
				pMF[j].MTyp = 'A';
				pMF[j].MWert = NULL;

				writtenCode = ObjNameCode;
				j++;
			}
		}
		for (t.First(); t.Valid(); t.Next()) {
		PBD_MerkmalLock l(t);
		
			if (l) {
				if (!ML.isSystem() && l -> isSystem()) 
					continue;	// Systemmerkmal

				if ('a' != tolower(l -> isA()))
					continue;	// kein Objektmerkmal
				if (l -> GetCode() == writtenCode)
					continue;	// war schon

				pMF[j].MCode = l -> GetCode();

			char *tmpPtr = l -> GetMerkmalsText();

				pMF[j].MText = ConvertFromNL (tmpPtr);
				DELETE_OBJ (tmpPtr);
				if (NULL != pMF[j].MText)
					AnsiToOem (pMF[j].MText, pMF[j].MText);

				pMF[j].MTyp = l -> MTyp();

			// eigentlichen Merkmalswert merken
				pMF[j].MWert = GetMerkmalsWert (l);
				j++;	// nächstes Element
			}
		}
	} 
	else if (GO.isA() == OT_TEXT || GO.isA() == OT_LABEL) {
	// Textobjekt: Text lesen (alte Textobjekte haben keine Merkmale)
	char *tmpPtr = ((BasicGeoText *)&GO) -> TextBase();

		pMF[0].MCode = -1L;
		if (tmpPtr != NULL) {
			pMF[0].MText = ConvertFromNL (tmpPtr);
			if (pMF[0].MText != NULL) {
				if (TOT_TEXTINDOBJPROP == ((BasicGeoText *)&GO) -> isText()) {
				os_string str = g_cbIndText;

					str += pMF[0].MText;
					strcpy (pMF[0].MText, str.c_str());
				}
				AnsiToOem (pMF[0].MText, pMF[0].MText);
			}
		} else {
			pMF[0].MText = new char [2];
			if (pMF[0].MText != NULL) strcpy (pMF[0].MText, g_cbSpace);
		}			

		pMF[0].MTyp = 't';
		pMF[0].MWert = NULL;

		if (((BasicGeoText *)&GO) -> isText() == TOT_TEXTIND && !fForceText) {
		// indirektes Textobjekt
			pMF[0].MCode = ((GeoTextInd &)GO).FMCode();

		// Unique Ident modifizieren
			if (pModUId && !strcmp (pModUId, "[B]"))
				pModUId = "[P]";
		}

		j = 1;
	}

	pMF[j].MCode = 0;       // letzter Satz
	pMF[j].MText = NULL;
	pMF[j].MWert = NULL;

// Geometrie umsetzen
GSTRUCT GS;						// Geometrie-Struktur
KoOrd *x = NULL, *y = NULL;		// HilfsFelder für Geometrie
long *cnt = NULL;
BOOL fHuge = FALSE;

	GS.Id = GO.Id();
	GS.ON = GO.ObjNr();
	switch (GS.Typ = GO.isA()) {
	case OT_LABEL:
	case OT_TEXT:
		GS.Typ = OT_TEXT;		// als normalen Text exportieren
		if (pModUId == NULL) 
			pModUId = "[T]";
	// hier durchfallen
	// ...
	case OT_PUNKT:
		GS.GSize = 1;
		GS.x = new double [1];
		GS.y = new double [1];
		x = new KoOrd [1];
		y = new KoOrd [1];
		cnt = new long [2];
		if (GS.x == NULL || GS.y == NULL || 
		    x == NULL || y == NULL || cnt == NULL) {
			if (GS.x) delete GS.x;
			if (GS.y) delete GS.y;
			DELETE_OBJ (x);
			DELETE_OBJ (y);
			DELETE_OBJ (cnt);
			return (ErrCode)db_error (EC_NOMEMORY, RC_ExportData);
		}
		if (GS.Typ == OT_PUNKT) {
			x[0] = ((GeoPunkt *)&GO) -> GetX();
			y[0] = ((GeoPunkt *)&GO) -> GetY();
		} else {
			x[0] = ((BasicGeoText *)&GO) -> GetX();
			y[0] = ((BasicGeoText *)&GO) -> GetY();
		}
		cnt[0] = 1;	// ein Stützpunkt
		cnt[1] = 0;	// Feldende
		break;

	case OT_KANTE:
		{
		GeoKante *KO = (GeoKante *)&GO;

			GS.GSize = KO -> ASP();
			GS.x = new __huge double [GS.GSize];
			GS.y = new __huge double [GS.GSize];
			x = new __huge KoOrd [GS.GSize];
			y = new __huge KoOrd [GS.GSize];
			fHuge = TRUE;
			cnt = new long [2];
			if (GS.x == NULL || GS.y == NULL || 
			    x == NULL || y == NULL || cnt == NULL) {
				if (GS.x) delete (double __huge *)GS.x;
				if (GS.y) delete (double __huge *)GS.y;	
				if (x) delete (long __huge *)x;
				if (y) delete (long __huge *)y;
				DELETE_OBJ (cnt);
				return (ErrCode)db_error (EC_NOMEMORY, RC_ExportData);
			}
			KO -> GetKante (x, y, GS.GSize);
			cnt[0] = GS.GSize;
			cnt[1] = 0;		// Ende des Feldes
		}
		break;

	case OT_FLAECHE:
		{
		GeoFlaeche *FO = (GeoFlaeche *)&GO;
		long j = 0;

			cnt = new long [FO -> KantenAnz() +1];
			if (cnt == NULL)
				return (ErrCode)db_error (EC_NOMEMORY, RC_ExportData);
			GS.GSize = 0;
			for (i = 0; i < FO -> KantenAnz(); i++) {
				GS.GSize += FO -> KA((short)i).ASP();
				cnt[i] = FO -> KA((short)i).ASP();
			}
			cnt[i] = 0;	// FeldEnde
			GS.x = new __huge double [GS.GSize];
			GS.y = new __huge double [GS.GSize];
			x = new __huge KoOrd [GS.GSize];
			y = new __huge KoOrd [GS.GSize];
			fHuge = TRUE;
			if (GS.x == NULL || GS.y == NULL || 
			    x == NULL || y == NULL) {
				if (GS.x) delete (double __huge *)GS.x;
				if (GS.y) delete (double __huge *)GS.y;
				if (x) delete (long __huge *)x;
				if (y) delete (long __huge *)y;
				DELETE_OBJ (cnt);
				return (ErrCode)db_error (EC_NOMEMORY, RC_ExportData);
			}
		// Geometrie lesen
			for (i = 0, j = 0; i < FO -> KantenAnz(); i++) {
			long actSize = GS.GSize - j;
				
				FO -> KA((short)i).GetKante (&x[j], &y[j], actSize);
				j += actSize;
			}
		}
		break;
	}

// Geometrie konvertieren
	ConvertDCtoRC (x, y, GS);
	GS.cnt = cnt;

// Relationen setzen
char *pUIdent = GetUniqueIdent (GO, ML);  // evtl. Unique Ident setzen

	if (pModUId != NULL && pUIdent != NULL) {
	// Unique Ident für Begleitobjekt modifizieren
	char *pTmp = new char [strlen(pUIdent)+strlen(pModUId)+3];

		if (pTmp != NULL) {
			strcpy (pTmp, pModUId);
			if (pModUId[strlen(pModUId)-1] == '$' && *pUIdent == '$')
				strcat (pTmp, pUIdent+1);	// nur ein '$'
			else
				strcat (pTmp, pUIdent);
			delete pUIdent;
			pUIdent = pTmp;
		}
	}

RSTRUCT *pRS = NULL;
long AssocON = GS.ON != SHRT_MAX ? AssociatedObjekt (GO.DB().DBDesc(), GS.ON) : 0;

	if (AssocON < 0) {	// zur Zeit nur Begleitobjekte
		pRS = new RSTRUCT [2];
		if (pRS != NULL) {
			pRS[0].RCode = 0;	// Kein RCode
			pRS[0].RON = -AssocON;	// abhängiges TextObjekt
			pRS[0].RTyp = RT_BEGLEIT;
			pRS[1].RCode = -1;	// EndeKennzeichen
		}
	} else {		// z.Zt. keine anderen Relationen
		pRS = new RSTRUCT [1];
		if (pRS != NULL) 
			pRS[0].RCode = -1;
	}

// Daten ausgeben
ErrCode EC = EC_OKAY;

	if (_ExpData) {
	// DLL-Funktion rufen
		if ((EC = (*_ExpData)(_of, GS, pMF, pRS, pUIdent)) != EC_OKAY) {
			if (EC > 0) 
				EC = EC_OKAY;
		}
	}
	DELETE_OBJ (pUIdent);		// Unique Ident wieder freigeben
	DELETE_OBJ (pRS);			// RelationsFeld wieder freigeben

// MerkmalsFeld wieder freigeben
	for (ulong uli = 0; uli < MCnt; uli++) {
//		if (pMF[uli].MCode == 0)
//			break;		// letzter Satz
		DELETE_OBJ (pMF[uli].MText);
		DELETE_OBJ (pMF[uli].MWert);
	}
	DELETE_OBJ (pMF);

// Geometriefelder wieder freigeben
	if (fHuge) {
		if (GS.x) delete (double __huge *)GS.x;
		if (GS.y) delete (double __huge *)GS.y;
		if (x) delete (long __huge *)x;
		if (y) delete (long __huge *)y;
	} else {
		if (GS.x) delete GS.x;
		if (GS.y) delete GS.y;
		DELETE_OBJ (x);
		DELETE_OBJ (y);
	}
	DELETE_OBJ (cnt);

return EC;
}

// Geometrie in Weltkoordinaten transformieren --------------------------------
void Export::ConvertDCtoRC (KoOrd *x, KoOrd *y, GSTRUCT &GS) 
{
// Koordinaten transformieren (incl. rausrechnen der internen Skalierung)
	if (x == NULL || y == NULL) return;

	if (m_fConvert) {
	// vollständig in Weltkoordinaten konvertieren
		TX_ASSERT(NULL != m_pCTF);
		TX_ASSERT(GS.GSize > 0);

	LPVOID pData = NULL;

#if defined(_KOORD_ISDOUBLE)
		GS.x[0] = x[0];
		GS.y[0] = y[0];
#else
		m_pCTF -> UnScale (x[0], y[0], &GS.x[0], &GS.y[0]);
#endif // _KOORD_ISDOUBLE
		m_pCTF -> GetTransformParam (GS.x[0], GS.y[0], &pData);
		m_pCTF -> TransformEx (&GS.x[0], &GS.y[0], pData);

		for (long i = 1; i < GS.GSize; i++) {
#if defined(_KOORD_ISDOUBLE)
			GS.x[i] = x[i];
			GS.y[i] = y[i];
#else
			m_pCTF -> UnScale (x[i], y[i], &GS.x[i], &GS.y[i]);
#endif // _KOORD_ISDOUBLE
			m_pCTF -> TransformEx (&GS.x[i], &GS.y[i], pData);
		}
		m_pCTF -> FreeTransformParam (pData);
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
char *Export::ExpName (unsigned int Res) 
{
	strcpy (&_ExportName[_NameLen], 
		ResString (Res, sizeof(_ExportName)-_NameLen-1));

	return _ExportName;
}

// ---------------------------------------------------------------------------
// Aufbau des ExportDlgFensters, Abfrage der Parameter und Export der ObjListe
ErrCode DatenBasisObjekt::doExport (
	pWindow pPW, ObjContainer *OC, ObjFeld *pObjs, pWindow pWaitParent, bool fExportAll) 
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
EXPORTIDENT *pEI = (EXPORTIDENT *)pData;
CIdentifikator *pID = (CIdentifikator *)pObj;
long lIndex;

// nur testen, wenn nicht alles exportiert werden soll
	if (NULL != pEI -> m_pActSightIDs &&
		(lIndex = FindLong (pEI -> m_pActSightIDs, pEI -> m_iActSightNumIDs, pID -> Id())) == -1L)
	{
	// gehört nicht zur exportierten Sicht
		return true;
	}

VisInfo *pVI = NULL;
//CPbdIdent pbdID (pEI -> m_pDBO -> DBDesc(), pID -> Id()); // KurzText holen
HPALETTE hPal = pID -> hPal();
LPSTR pcKurzText = (LPSTR)pID -> GetKurzText();

// VisInfo's holen und exportieren
	if (!pID -> hasVI(VT_Default)) {	// keinerlei VisInfo
	IdentDescription IdDesc (pID -> Id(), pcKurzText, NULL, NULL);

		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
		return true;
	}

bool fExported = false;

// Punkte
	if (pID -> hasVI (VT_Punkt)) {	// PVisInfo
		pVI = (VisInfo *)pID -> PVI().Copy();
		ConvertColor (hPal, pVI -> PrimColor());

	IdentDescription IdDesc (pID -> Id(), pcKurzText, pVI, pID -> hPal());

		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
		DELETE_OBJ (pVI);

	} else if (NULL == pEI -> m_pActSightIDs && pID -> GetOTypes (TPPunkt)) {
	// Punkte in GeoDB, aber nicht in Ansicht
	IdentDescription IdDesc (pID -> Id(), pcKurzText, NULL, NULL);

		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
		fExported = true;
	}

// Linien
	if (pID -> hasVI (VT_Linie)) {	// LVisInfo
		pVI = (VisInfo *)pID -> LVI().Copy();

	IdentDescription IdDesc (pID -> Id(), pcKurzText, pVI, pID -> hPal());

		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
		DELETE_OBJ (pVI);

	} else if (NULL == pEI -> m_pActSightIDs && pID -> GetOTypes (TPLinie) && !fExported) {
	// Linien in GeoDB, aber nicht in Ansicht
	IdentDescription IdDesc (pID -> Id(), pcKurzText, NULL, NULL);

		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
		fExported = true;
	}

// Flächen
	if (pID -> hasVI (VT_Flaeche)) { 	// FVisInfo
		pVI = (VisInfo *)pID -> FVI().Copy();
		ConvertColor (hPal, pVI -> PrimColor());
		ConvertColor (hPal, ((FVisInfo *)pVI) -> SecColor());

	IdentDescription IdDesc (pID -> Id(), pcKurzText, pVI, pID -> hPal());

		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
		DELETE_OBJ (pVI);

	} else if (NULL == pEI -> m_pActSightIDs && pID -> GetOTypes (TPFlaeche) && !fExported) {
	// Flächen in GeoDB, aber nicht in Ansicht
	IdentDescription IdDesc (pID -> Id(), pcKurzText, NULL, NULL);

		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
		fExported = true;
	}

// Texte
	if (pID -> hasVI (VT_Text)) {	// TVisInfo
		pVI = (VisInfo *)pID -> TVI().Copy();

		((TVisInfo *)pVI) -> Rotation() /= 10;

	IdentDescription IdDesc (pID -> Id(), pcKurzText, pVI, pID -> hPal());

		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
		DELETE_OBJ (pVI);

	} else if (NULL == pEI -> m_pActSightIDs && pID -> GetOTypes (TPText) && !fExported) {
	// Texte in GeoDB, aber nicht in Ansicht
	IdentDescription IdDesc (pID -> Id(), pcKurzText, NULL, NULL);

		pEI -> m_pExp -> ExportIdentDescription (IdDesc);	// eigentliche Aktion
		fExported = true;
	}

	return true;
}

// Exportieren der Beschreibung eines Merkmales -------------------------------
BOOL EXPORTTRIAS ExportMerkmal (void *pObj, void *pData) 
{
PBD_Merkmal *pMK = (PBD_Merkmal *)pObj;

	if (pMK -> isSystem()) return true;		// keine Systemmerkmale

MerkmalDescription MKDesc (pMK -> GetCode(), pMK -> GetKurzText(), 
			   pMK -> MTyp(), pMK -> GetMLen());

	if (pData) ((Export *)pData) -> ExportMerkmalDescription (MKDesc);

return true;
}


// MerkmalsWert als Poiner auf Wert liefern -----------------------------------
static void *GetMerkmalsWert (PBD_Merkmal *pM) 
{
	switch (pM -> MTyp()) {
	case 'a':	// TextMerkmal
		return NULL;

	case 'i':	// IntegerMerkmal
		{
		IntMerkmal *pIM = (IntMerkmal *)pM;
		long *tmpLong = new long;

			if (tmpLong)
				*tmpLong = pIM -> GetMerkmalsInt();
			return tmpLong;
		}

	case 'f':
		{
		DoubleMerkmal *pDM = (DoubleMerkmal *)pM;
		double *tmpDouble = new double;

			if (tmpDouble)
				*tmpDouble = pDM -> GetMerkmalsDouble();
			return tmpDouble;
		}

	default:
		return NULL;
	}
}

ErrCode EvalKoeffs (double *, double *, double *, double *);

// Alle Informationen aus Header der GeoDB exportieren ------------------------
ErrCode Export::ExportGeoDBHeader (void) 
{
char outBuff[80];
char tBuff[20];
char *dFormat = "%15.5f";
ErrCode RC; 

// 1. ScalingParameter ausgeben, Matrix invertieren
double tK11 = K11, tK12 = K12, tK21 = K21, tK22 = K22;

	DBASSERT (EvalKoeffs (&tK11, &tK12, &tK21, &tK22));
	strcpy (outBuff, DtoA (tBuff, dFormat, tK11));
	strcat (outBuff, g_cbSpace);
	strcat (outBuff, DtoA (tBuff, dFormat, tK12));
	strcat (outBuff, g_cbSpace);
	strcat (outBuff, DtoA (tBuff, dFormat, tK21));
	strcat (outBuff, g_cbSpace);
	strcat (outBuff, DtoA (tBuff, dFormat, tK22));
	DBASSERT (ExportDescription (ResString (IDS_SCALEKEY, 20), outBuff, HEADER_SYSTEMRO));

// 2. OffsetParameter ausgeben
	strcpy (outBuff, DtoA (tBuff, dFormat, OX));
	strcat (outBuff, g_cbSpace);
	strcat (outBuff, DtoA (tBuff, dFormat, OY));
	DBASSERT (ExportDescription (ResString (IDS_OFFSETKEY, 20), outBuff, HEADER_SYSTEMRO));

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
		DBASSERT (ExportDescription (ResString (IDS_IDENTBASE, 20), fNewProject ? "16" : "10", 
									 HEADER_SYSTEMRO));
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
ErrInstall EI (WC_NOTFOUND);	// Fehlermeldung unterdrücken

	{
	ResString rsHE (resID, 17);
	HeaderEntry hdrT (_DB, rsHE);
	char *pT = hdrT.EntryText();

		if (HE_INVALID != hdrT.Status() && NULL != pT)	
			return ExportDescription (rsHE, pT, dwStyle);
	}

return WC_RETURN;
}


// Ausgeben eines Objektes ----------------------------------------------------
ErrCode Export::ExportObjekt (DatenBasisObjekt &rDBO, CTable &t, 
				long ON, char *pModUId, bool fForceText)
{
GeoObjekt *pGO = NULL;	// gesuchtes GeometrieObjekt
ErrCode RC = EC_OKAY;
MerkmalsListe ML (&rDBO.DB(), &(rDBO.PbdDB()), ON, OBL_OLD, FALSE);
			// keine Systemmerkmale exportieren

	if (t.Find(&ON)) {
	// Objekt ist im Speicher
	ExtShapeObjectLock l1(t);

		if (l1) pGO = l1 -> operator GeoObjekt *();
		else 	// Fehler
			return (ErrCode)db_error (EC_NOON, RC_doExport);
		if (pGO -> isA() == OT_KO) 
			return EC_OKAY;
		DBASSERT (ExportData (*pGO, ML, pModUId));
	} else {
	// Objekt muß geladen werden
	HRESULT hr = rDBO.GetGI (ON, NULL, &pGO);

		if (S_OK != hr) {
		char cbOut[80];

			wsprintf (cbOut, "Error %lx loading object %ld.", hr, ON);
			ExportComment (cbOut);
			return EC_OKAY;
		}

	// Objekt exportieren
		if (pGO -> isA() != OT_KO)
			RC = ExportData (*pGO, ML, pModUId, fForceText);
		
	// Speicher wieder freigeben
		delete pGO;
/*		switch (pGO -> isA()) {
		case OT_PUNKT:		delete (GeoPunkt *)pGO; break;
		case OT_KANTE: 		delete (GeoKante *)pGO; break;
		case OT_FLAECHE:	delete (GeoFlaeche *)pGO; break;
		case OT_KREIS:		delete (GeoKreis *)pGO; break;
		case OT_TEXT:		delete (BasicGeoText *)pGO; break;
		case OT_KO:		delete (KomplexObjekt *)pGO; break;
		case OT_UNKNOWN:
		default:		break;
		}
*/
	}

return RC;
}

// Unique Ident lesen ---------------------------------------------------------
char *Export::GetUniqueIdent (GeoObjekt &GO, MerkmalsListe &ML)
{
long lUIdent = -1L;
ErrInstall EI (WC_NOTFOUND);

	lUIdent = HeaderEntry (_DB, IDS_UNIQUEIDENT).EntryLong (-1L);
	if (lUIdent != -1L) {		// Unique Ident existiert
		if (GO.isA() == OT_TEXT || GO.isA() == OT_LABEL) {	// Ist TextObjekt
		long AssocON = AssociatedObjekt (GO.DB().DBDesc(), GO.ObjNr());

			if (AssocON > 0) {	// Textobjekt ist abhängig
			char *pUIdent = NULL;

			// Unique Ident aus übergeordnetem Objekt holen
				if (GetMiText (GO.DB().DBDesc(), lUIdent, AssocON, OBL_OLD, &pUIdent) != EC_OKAY)
					return NULL;
				AnsiToOem (pUIdent, pUIdent);
				return pUIdent;
			} else
				return ML.GetMerkmalsText (lUIdent);
		} else 				// normales Objekt
		// Unique Ident aus ML holen
			return ML.GetMerkmalsText (lUIdent);
	}

return NULL;
}

// Wegschreiben des DB-Containers um Schichtweise Skalierung zu ermöglichen
ErrCode Export::ExportDBContainer (GeoDB &rDB, long Ident, ObjContainer &OC) 
{
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
	TX_ASSERT(FALSE);
	return EC_OKAY;
}

#endif // !defined(_FORCE_LEGACY_CODE)