
// ImportInterface-Implementation für den Import von PolyGIS-BNA-Daten/ Modi PolyGIS-DAT -----------
// File: DatLayer.CPP

#include "bnaimpp.hpp"

#include <errinstx.hxx>
#include <xtensnn.h>
#include <fnamestr.h>
#include <eonrguid.h>
#include <hdrentrx.hxx>
#include <REGISTRX.HXX>

#include <ospace/std/vector>
#include <ospace/string/tokenize.h>

#include <fnamestr.h>

#include "BNAProgressDlg.h"
#include "BNAImportConfig.h"



#include "relkey.hxx"

#include "bnaimp.h"
#include "status.hxx"
#include "result.hxx"
#include "bnaimp.hpp"
#include "bnapars.h"
#include "input.h"
//#include "bnaimpif.hpp"


UINT GCAFELD [GCAFIELDCOUNT] = { IDS_GCACODE,IDS_GCASTRASSE,IDS_GCAHAUSNUMMER,IDS_GCAHAUSNRZUSATZ,IDS_GCABISHAUSNR,IDS_GCABISHAUSNRZUSATZ,IDS_GCAPLZ,IDS_GCAORT,IDS_GCAORTSTEIL};


static LPCTSTR g_cbLocal	= TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\%s\\%s\\%s");

HFEATURE GetGCACode ( UINT ID);

short DatLayer( char const*);

char VLayer[50];
char VTime[6];

///////////////////////////////////////////////////////////////////////////////
// Eine Datei Parsen
class CCloseFileOnExit
{
public:
	CCloseFileOnExit(FILE *pFile) : m_pFile(pFile) {}
	~CCloseFileOnExit() { if (NULL != m_pFile) fclose(m_pFile); }

	bool IsOpen() { return NULL != m_pFile; }
	FILE *Ptr() { return m_pFile; }

private:
	FILE *m_pFile;
};

/////////////////////////////////////////////////////////////////////////////////

int end_previous_object (FILE *);	/* Objekt bearbeiten */
void init_new_object (void);	/* Naechstes Objekt initialisieren */
//void EnsureUIdentMCodes(void);
void EnsurePolyMCodes(void);
void EnsurePolyDATMCodes(long);

HFEATURE EnsurePolyMCode(char const *pName);
void DefinePolyDatMCodes(long);

void SetTextField(char const *pText, HFEATURE lMCode);
void PolyInit(void);
HRESULT RestoreRegistryKey (void);
bool MemoIdentifikator(HOBJECTS lIdent); 
ErrCode MCodeIsDefined (long lMCode, char const *rs);
// Informationsfelder ---------------------------------------------------------


extern TR_LayerTree *g_OKSTree;			// globaler Baum der OKS

//////////////////////////////////////////////////////////////////////////////
// MerkmalsCodes für Objektklassenabgleich

extern bool fFirstIdent;
extern bool fFirstMCode;

// Verwalten des lIdent für PolyGIS-Klassen ---------------------------------
extern unsigned long g_ulPolyId;
extern unsigned long g_ulPolyIdTyp;

// Verwalten des MCodes für den Unique Ident ---------------------------------
extern unsigned long g_ulUniqueId;
extern unsigned long g_ulOrgUniqueId;
extern unsigned long g_ulOldUniqueId;


// Verwalten des MCodes für den PolyGIS-BNA ---------------------------------
extern unsigned long g_ulName1;
extern unsigned long g_ulName2;
extern unsigned long g_ulID;

extern unsigned long g_ulMemo;
extern unsigned long g_ulOrdnung;

// Verwalten der Koordinatenparameter ---------------------------------
extern double g_dOffsetX;
extern double g_dOffsetY;
extern double g_dScaling;

// DAT-Struktur
extern char g_cKey01[BNAKEYLEN];
extern char g_cKey02[BNAKEYLEN];
extern char g_cKey03[BNAKEYLEN];
extern char g_cKey01P[BNAKEYLEN];
extern char g_cKey02P[BNAKEYLEN];
extern char g_cKey03P[BNAKEYLEN];



extern char g_cName1Buff[BNAKEYLEN];
extern char g_cName2Buff[BNAKEYLEN];
extern char g_cIDBuff[BNAKEYLEN];
extern char g_cSuffix[BNAKEYLEN];
extern char g_cMemo[BNAKEYLEN];
extern char g_cOrdnung[BNAKEYLEN];

extern char g_cBNALayer[_MAX_PATH];
extern char g_cMemoKlasse[_MAX_PATH];
extern char g_cMemoKlasseReplace[_MAX_PATH];
extern char g_cMemoRef[_MAX_PATH];
///////////////////////////////////////////////////////////////////////////////
// aktuelle Datenquelle
extern HPROJECT g_hPr;

//////////////////////////////////////////////////////////////////////////////
//-------------------------ImportRegistry-------------------------------------
HRESULT CImpBnaExtension::DATImportRegistry (int iTyp)
{
// Registry-Einträge
	switch (iTyp) {

// 
	case IMPORTSTANDARDDAT:
		return ImportRegistryDATType(IMPORTSTANDARDDAT, IDS_IMPORT, IDS_IMPORTSTANDARDDAT);

	case IMPORTPUNKTDAT:
		return ImportRegistryDATType(IMPORTPUNKTDAT, IDS_IMPORT, IDS_IMPORTPUNKTDAT);

//

	default:
		_ASSERTE(FALSE);
		break;
	}
	return EC_OKAY;
}
///////////////////////////////////////////////////////////////////////////////
HRESULT CImpBnaExtension::ImportRegistryDATType (int iTyp, UINT uiThemaId, UINT uiDefaultId)
{
	_ASSERTE(NULL != g_pTE);

TCHAR szKey[_MAX_PATH];
ResString Projekt (ResID(IDS_PROJEKTLAYER, &g_pTE->RF()), 80);
ResString Thema (ResID(uiThemaId, &g_pTE->RF()), 80);
ResString Default (ResID(uiDefaultId, &g_pTE->RF()), 80);

	wsprintf(szKey, g_cbLocal, Projekt.Addr(), Thema.Addr(), Default.Addr());
	return ImportRegistryDATStandard(iTyp, szKey);
}

//////////////////////////////////////////////////////////////////////////////
//-------------------------ImportRegistryStandard-------------------------------------
HRESULT CImpBnaExtension::ImportRegistryDATStandard (int iTyp, char const *pcKey)
{
	_ASSERTE(NULL != g_pTE);

// Registry-Einträge
		char *pID = NULL;
		char *pName1 = NULL;
		char *pName2 = NULL;

	if ( iTyp == IMPORTSTANDARDDAT) {
		g_cKey01[0] = '\0';
		pID = &g_cKey01[0];
		g_cKey02[0] = '\0';
		pName1 = &g_cKey02[0];
		g_cKey03[0] = '\0';
		pName2 = &g_cKey03[0];
	} else {

		pID = &g_cKey01P[0];
		g_cKey01P[0] = '\0';
		pName1 = &g_cKey02P[0];
		g_cKey02P[0] = '\0';
		pName2 = &g_cKey03P[0];
		g_cKey03P[0] = '\0';
	}

CCurrentUser rgMass(pcKey, true);

ResString Key1 (ResID(IDS_DATKEY02, &g_pTE->RF()), 80);
ResString Key2 (ResID(IDS_DATKEY03, &g_pTE->RF()), 80);
ResString KeyID (ResID(IDS_DATKEY01, &g_pTE->RF()), 80);

// Merkmal Name1
DWORD dKeyLen = BNAKEYLEN;

	if (rgMass.GetSubSZ (Key1.Addr(), pName1, dKeyLen)) {
		if (0 == dKeyLen)
			*pName1 = 0;
		StoreInKeyTree (Key1.Addr(), pName1);
	}

// Merkmal Name2
	dKeyLen = BNAKEYLEN;
	if (rgMass.GetSubSZ (Key2.Addr(), pName2, dKeyLen)) {
		if (0 == dKeyLen)
			*pName2 = 0;
		StoreInKeyTree (Key2.Addr(), pName2);
	}

// Merkmal ID
	dKeyLen = BNAKEYLEN;
	if (rgMass.GetSubSZ (KeyID.Addr(), pID, dKeyLen)) {
		if (0 == dKeyLen)
			*pID = 0;
		StoreInKeyTree (KeyID.Addr(), pID);
	}


	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
void EnsurePolyDATMCodes(long lTyp)
{
	char *pID = NULL;
	char *pName1 = NULL;
	char *pName2 = NULL;

	if  (lTyp == O_PUNKT) {
		pID = &g_cKey01P[0];
		pName1 = &g_cKey02P[0];
		pName2 = &g_cKey03P[0];
	} else {
		pID = &g_cKey01[0];
		pName1 = &g_cKey02[0];
		pName2 = &g_cKey03[0];
	}

	g_ulName1 = EnsurePolyMCode(pName1);

	g_ulName2 = EnsurePolyMCode(pName2);

	g_ulID = EnsurePolyMCode(pID);

	if (INVALID_HFEATURE == g_ulMemo) 
		g_ulMemo = EnsurePolyMCode(g_cMemo);

	if (INVALID_HFEATURE == g_ulOrdnung) 
		g_ulOrdnung = EnsurePolyMCode(g_cOrdnung);

	// UniqueIdent besorgen !!!

	g_ulUniqueId = DEX_GetUniqueIdentMCodeEx(g_hPr);
}

//////////////////////////////////////////////////////////////////////////////
//KK020904
///////////////////////////////////////////////////////////////////////////////
HRESULT CImpBnaExtension::PolyParseDat (FILE *pActFile)
{
	if (pActFile == NULL)
		return S_FALSE;  

// Registry-Eintrag prüfen

	RETURN_FAILED_HRESULT(DATImportRegistry (IMPORTSTANDARDDAT));
	RETURN_FAILED_HRESULT(DATImportRegistry (IMPORTPUNKTDAT));


	long lIndex = 0L;
	HRESULT hr = E_FAIL;

	char cbLine[4*_MAX_PATH];                       // 1 Zeile

	try {
   	// aktive Datenquelle bsorgen
      	g_hPr = DEX_GetDataSourceHandle();
      	_ASSERTE(NULL != g_hPr);
      
	// Flag initialisieren
   		fFirstIdent = true;
   		fFirstMCode = true;


		satz_nr = 0;
		lIndex = 0;

		bool fObjectWasSkipped = false;

		App::Exec(ExecWhileEvent);

		while (fgets (cbLine, sizeof(cbLine)-1, pActFile)) {

			yylineno++;		/* Zeilennummer */

			if ( strncmp (cbLine,"POINT",5) != 0 && 
				strncmp (cbLine,"POLY",4) != 0 &&
				strncmp (cbLine,"SEG",3) != 0 &&
				strncmp (cbLine,"PP",2) != 0 &&
				strncmp (cbLine,"END",3) != 0 )
				continue;


			if ( strncmp (cbLine,"POINT",5) == 0 || 
				strncmp (cbLine,"POLY",4) == 0 ||
				strncmp (cbLine,"SEG",3) == 0 )		{		// Header

				lIndex = 0;

  			// Vorhergehendes EO bearbeiten
				if (!fObjectWasSkipped && satz_nr > 0) {
					if (end_previous_object (pActFile))
						return S_OK;
				}

    		// Nächstes Objekt beginnen 
				fObjectWasSkipped = false;
				++satz_nr;
	      		init_new_object ();


			// tokenizer zerteilt die Kopfzeile in Tokens:
			// token 0: POINT
			// token 1: LAYER
			// token 2: RW
			// token 3: HW
			// token 4: 0.000
			// token 5: 0
			// token 6: GCO bzw.tab
			// token 7: N
			// token 8: 0.000
			// token 9: 0.000
			// token 10: HNR

				os_tokenizer token("\t", true, "", "\n", "", false);

				vector<string> tokens = token.tokenize(cbLine);

//				if (5 > tokens.size()) 
//					continue;

				short iTokenSize = tokens.size() -1;

				DWORD dwObjTyp;
				short iID;
				short iName1;
				short iName2;

			// Layer behandeln
				CTable t (*g_OKSTree);

				if (!t.Find((void *)tokens[1].c_str())) {
					_ASSERTE(FALSE);		// should exist
					SkipObject(pActFile);
					fObjectWasSkipped = true;
					continue;
				}

				TR_LayerLock l(t);

				if (!l) {
					_ASSERTE(FALSE);		// snh
					SkipObject(pActFile);
					fObjectWasSkipped = true;
					continue;
				}



				if ( strncmp (cbLine,"POINT",5) == 0) {		// Headereinträge - Objektdefinition Punkt

//				if (5 > iTokenSize) 
//					continue;

			// hier ist der neue Ident
					dwObjTyp = OTPunkt;
					koord_paare = 1;

//					iName1 = iName2 = iID = POLYDATLAYER;
					iName1 = iName2 = iID = POLYDATNOTHING;
// Alte Punktstruktur
					
					if ( iTokenSize >= POLYDATPOINTID )
					iID = POLYDATPOINTID;

					if ( iTokenSize >= POLYDATPOINTNAME1 )
						iName1 = POLYDATPOINTNAME1;

					if ( iTokenSize >= POLYDATPOINTNAME2 )
						iName2 = POLYDATPOINTNAME2;

// Alte MW-Punktstruktur
					/*
					if ( iTokenSize >= 6 )
					iID = 6;
					if ( iTokenSize >= 10 )
						iName1 = 10;
					else
						iName1 = iTokenSize;

					if ( iTokenSize >= 7 )
						iName2 = 7;
----------------------------------------------------*/

				}


			// Linien
				if ( strncmp (cbLine,"SEG",3) == 0) {		// Headereinträge - Objektdefinition Linie


			// hier ist der neue Ident
				// GCO-Reihenfolge = LAYER,NAME1;NAME2,ID
					dwObjTyp = OTLinie;
					koord_paare = -10;
					iName1 = iName2 = iID = POLYDATNOTHING;

					if ( iTokenSize >=  POLYDATNAME1)
						iName1 = POLYDATNAME1;
					if ( iTokenSize >= POLYDATNAME2 )
						iName2 = POLYDATNAME2;
					if ( iTokenSize >= POLYDATID)
						iID = POLYDATID;

				}
				if ( strncmp (cbLine,"POLY",4) == 0) {		// Headereinträge - Objektdefinition Fläche


			// hier ist der neue Ident
					dwObjTyp = OTFlaeche;
					koord_paare = 10;

					iName1 = iName2 = iID = POLYDATNOTHING;

					if ( iTokenSize >=  POLYDATNAME1)
						iName1 = POLYDATNAME1;
					if ( iTokenSize >= POLYDATNAME2 )
						iName2 = POLYDATNAME2;
					if ( iTokenSize >= POLYDATID)
						iID = POLYDATID;

				}

			// Objekttyp und Stützpunktanzahl
				if (1 == koord_paare)
					sta[1] = O_PUNKT;
				else if (koord_paare < 0) {
					sta[1] = O_LINIE;
					koord_paare = -koord_paare;
				}
				else {
					_ASSERTE(2 < koord_paare);
					sta[1] = O_FLAECHE;
				}

				ULONG lIdent = l -> Ident(dwObjTyp);

				if (0 == lIdent) {
			// Objekte dieses Layers/Objekttyps sollen nicht importiert werden
					fObjectWasSkipped = true;
					continue;
				}


				if (lIdent != g_ulPolyId || sta[1] != g_ulPolyIdTyp) {
					EnsurePolyDATMCodes(sta[1]);
					g_ulPolyId = lIdent;
					g_ulPolyIdTyp = sta[1];
					DefinePolyDatMCodes(sta[1]);
				}
		   		id = lIdent;

	

				// Name1, Name2 und Id behandlen
				if (l -> GetImportAttributes(dwObjTyp)) {
					ResourceFile RF (g_pDLLName);

				// Name 1
					if ( iName1 >= 0 ) {
						if (INVALID_HFEATURE == g_ulName1) {
							ResString resName1 (ResID(IDS_POLYNAME1, &RF), 64);
							HFEATURE hFeat = EnsurePolyMCode(resName1);

							if (INVALID_HFEATURE != hFeat && 
								EC_OKAY == MCodeIsDefined(hFeat, resName1))
							{
								if ( tokens[iName1].size() > 0)
									SetTextField(tokens[iName1].c_str(), hFeat);
							}
						}
						else {
	
							if ( tokens[iName1].size() > 0)
								SetTextField(tokens[iName1].c_str(), g_ulName1);
						}
					}	// Name1

				// Name 2

					if ( iName2 >= 0) {
						if (INVALID_HFEATURE == g_ulName2) {
							ResString resName2 (ResID(IDS_POLYNAME2, &RF), 64);
							HFEATURE hFeat = EnsurePolyMCode(resName2);

						if (INVALID_HFEATURE != hFeat && 
							EC_OKAY == MCodeIsDefined(hFeat, resName2))
							{
								if ( tokens[iName2].size() > 0)

									SetTextField(tokens[iName2].c_str(), hFeat);
							}
						}
						else {
							if ( tokens[iName2].size() > 0)

								SetTextField(tokens[iName2].c_str(), g_ulName2);
						}
					}		// Name 2

					// ID
					if ( iID >= 0 ) {

						if (INVALID_HFEATURE == g_ulID) {
							ResString resID (ResID(IDS_POLYID, &RF), 64);
							HFEATURE hFeat = EnsurePolyMCode(resID);

							if (INVALID_HFEATURE != hFeat && 
								EC_OKAY == MCodeIsDefined(hFeat, resID))
							{
								if ( tokens[iID].size() > 0)

									SetTextField(tokens[iID].c_str(), hFeat);
							}
						}

						else {

							if ( tokens[iID].size() > 0)
								SetTextField(tokens[iID].c_str(), g_ulID);
						}

					}		// iID
				} 
				else {
					
					if ( iName1 >= 0 ) {
						if (  tokens[iName1].size() > 0)
							SetTextField(tokens[iName1].c_str(), g_ulName1);
					}
					
					if ( iName2 >= 0 ) {
		 				if (  tokens[iName2].size() > 0)
							SetTextField(tokens[iName2].c_str(), g_ulName2);
					}

					if ( iID <= 0 ) {
		 				if (  tokens[iID].size() > 0)
							SetTextField(tokens[iID].c_str(), g_ulID);
					}
				}

			// UniqueIdent
				char cbBuffer[_MAX_PATH];

				wsprintf (cbBuffer, "%s_%ld", tokens[1].c_str(), satz_nr);
				if (MemoIdentifikator(lIdent))
					SetTextField(g_cMemoRef, g_ulMemo);
				SetTextField(cbBuffer, g_ulUniqueId);


				if ( strncmp (cbLine,"POINT",5) == 0) {		// Headereinträge - Objektdefinition

			//	POINT-Koordinaten
					lgi = 1;

					char oLine[_MAX_PATH];
					int irc = 0;

					double xref,yref;

					wsprintf (oLine,"%s,%s",tokens[2].c_str(),tokens[3].c_str());
					irc = sscanf (oLine, "%lf,%lf", &xref, &yref);

					gxi[lIndex] = (xref + g_dOffsetX) * g_dScaling;
					gyi[lIndex] = (yref + g_dOffsetY) * g_dScaling;

					lIndex++;

			}	// Header POLY,SEG,POINT
			} 
			else 
			{	
			// Koordinaten !!!

			if ( strncmp (cbLine,"PP",2) == 0) {		// Koordinaten

				if ( fObjectWasSkipped )
					continue;


				os_tokenizer token("\t", true, "", "\n", "", false);

				vector<string> tokens = token.tokenize(cbLine);


				char oLine[_MAX_PATH];
				int irc = 0;
				double xref,yref;

				lgi++;				// Koordinatenanzahl
				wsprintf (oLine,"%s,%s",tokens[1].c_str(),tokens[2].c_str());
				irc = sscanf (oLine, "%lf,%lf", &xref, &yref);

				gxi[lIndex] = (xref + g_dOffsetX) * g_dScaling;
				gyi[lIndex] = (yref + g_dOffsetY) * g_dScaling;

				koord_paare = lgi;

				lIndex++;

			}
			}
		}

	// Vorhergehendes EO bearbeiten
		if (!fObjectWasSkipped && satz_nr > 0) {
			if (end_previous_object (pActFile))
				return S_OK;
		}
		hr = S_FALSE;
	} 
	catch(...) {
		hr = E_UNEXPECTED;
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// PolyMCodes in PBD definieren
void DefinePolyDatMCodes(long lTyp)
{
	char *pID = NULL;
	char *pName1 = NULL;
	char *pName2 = NULL;

	if  (lTyp == O_PUNKT) {
		pID = &g_cKey01P[0];
		pName1 = &g_cKey02P[0];
		pName2 = &g_cKey03P[0];
	} else {
		pID = &g_cKey01[0];
		pName1 = &g_cKey02[0];
		pName2 = &g_cKey03[0];
	}



	if (0L != g_ulName1)	//Key02
		MCodeIsDefined (g_ulName1, pName1);

	if (0L != g_ulName2)	//Key03
		MCodeIsDefined (g_ulName2, pName2);


	strcpy (g_cKey01, ResString (ResID(IDS_DATIMPORTGCO, &g_pTE->RF()), 50).Addr());
	g_ulID = EnsurePolyMCode(g_cKey01);
	
	if (0L != g_ulID)		//Key01
		MCodeIsDefined (g_ulID, pID);

///////////// aus BNA-Import //////////////////////////////////////////////
	if (0L != g_ulMemo) 
		MCodeIsDefined (g_ulMemo, g_cMemo);

	if (0L != g_ulOrdnung) 
		MCodeIsDefined (g_ulOrdnung, g_cOrdnung);
}


///////////////////////////////////////////////////////////////////////////////////////////////

//KK020904

//////////////////////////////////////////////////////////////////////////////
HRESULT CBNAProgressDlg::ParseFileDat(LPCSTR pcFile, ULONG ulAct, ULONG ulCount)
{
// gg. globalen Status weitersetzen
	if (ulCount > 1) {
	ResourceFile RF (g_pDLLName);
	ResString resPrompt (ResID(IDS_FILES_PROMPT, &RF), 64);
	char cbBuffer[_MAX_PATH];

		wsprintf (cbBuffer, resPrompt, ulAct, ulCount);
		m_ftFilesPrompt.SetText(cbBuffer);
		m_FilesStatus.StepIt();
	}

// Datei untersuchen
	CCloseFileOnExit File (fopen (pcFile, "r"));

	if (!File.IsOpen())
		return STG_E_PATHNOTFOUND;

	fseek (File.Ptr(), 0L, SEEK_END);		// Dateilänge bestimmen

	long lLen = ftell (File.Ptr());
	int iToShift = 0;

	while (lLen > SHRT_MAX) {
		lLen >>= 1;
		++iToShift;
	}

	char cbLine[4*_MAX_PATH];

	m_Status.SetRange(0, lLen);
	m_Status.SetPos(0);
	m_ftFileName.SetText(pcFile);

	fseek (File.Ptr(), 0L, SEEK_SET);			// wieder am Anfang
	while (fgets (cbLine, sizeof(cbLine)-1, File.Ptr())) {
		long lPos = ftell(File.Ptr());

		lPos >>= iToShift;
		m_Status.SetPos (lPos);		// nächste Zeile gelesen
		App::Exec(ExecWhileEvent);			// ggf. Cancel bearbeiten

		if (strncmp (cbLine,"POINT",5) != 0 && strncmp (cbLine,"SEG",3) != 0 && strncmp (cbLine,"POLY",4) != 0 )
			continue;			// nur Kopfzeilen auswerten


			// tokenizer zerteilt die Kopfzeile in Tokens:
			// token 0: POINT,SEG,POLY
			// token 1: LAYER
			// token 2: RW
			// token 3: HW
			// token 4: 0
			// token 5: 0
			// token 6: GCO
			// token 7: N
			// token 8: 0
			// token 9: 0.0
			// token 10: HNR



		os_tokenizer token("\t", true, "", "\n", "", false);
		vector<string> tokens = token.tokenize(cbLine);

		short iTyp = OTPunkt;

		if ( strncmp (cbLine,"SEG",3) == 0 )
			iTyp = OTLinie;
	
		if ( strncmp (cbLine,"POLY",4) == 0 )
			iTyp = OTFlaeche;


		if ( tokens[1].size() > 0)
			m_pBack -> StoreLayer(tokens[1],iTyp);

	}

// einmal geparst müßte reichen
	m_pBack -> SetFilesParsed(true);
	return S_OK;
}
//////////////////////////////////////////////////////////////////////////////////
// KK020904-NOT ===========================================================
short DatLayer(const char * poleString)
{

	char *pPath = new char [_MAX_PATH];
	strcpy (pPath,poleString);

	if (pPath)
		strlwr(pPath);

	char *cptr = strrchr (pPath,'.');
	short iMode = BNAIMPORT;			// Ist Standard


	ResString NewExt (ResID(IDS_NEXTEXTENSION, &g_pTE->RF()), 80);
	// oder
	ResString GpsExt (ResID(IDS_GPSEXTENSION, &g_pTE->RF()), 80);

	ResString GCAExt (ResID(IDS_GCAEXTENSION, &g_pTE->RF()), 80);

	if ( cptr )  {

		cptr++;

		if ( strcmp(cptr,NewExt.Addr()) == 0)
			iMode = DATIMPORT;

	////////////////////////////////VIDEO////////////////////////////////////////////////

		if ( strcmp(cptr,GpsExt.Addr()) == 0)
			iMode = GPSIMPORT;

	////////////////////////////////GCA////////////////////////////////////////////////
		if ( strcmp(cptr,GCAExt.Addr()) == 0)
			iMode = GCAIMPORT;


	}
		
	DELETE_OBJ(pPath);

	return iMode;
}
//////////////////////////////////////////////////////////////////////////////////////////////
//Tricks
////////////////////////////////VIDEO////////////////////////////////////////////////

//
HOBJECTS IdentDefined (char const *pIdent)
{

ErrInstall EI (WC_NOIDENT);
PBDDATA pbdData;		// Nun mit Text definieren

	ulong ulIdent = (ULONG)DEX_GetUniqueICodeEx (g_hPr); // neuer Ident von TRIAS

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = ulIdent;
	pbdData.pbdKText = (LPSTR)pIdent;
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = _MAX_PATH;
	pbdData.pbdLTextLen = 0;
	DEX_ModPBDDataEx (g_hPr, pbdData);		// PBD-Info setzen
	return ulIdent;
}


//////////////////////////////////////////////////////////////////////////////
HRESULT CBNAProgressDlg::VideoFileDat(LPCSTR pcFile, ULONG ulAct, ULONG ulCount)
{
// gg. globalen Status weitersetzen
	if (ulCount > 1) {
	ResourceFile RF (g_pDLLName);
	ResString resPrompt (ResID(IDS_FILES_PROMPT, &RF), 64);
	char cbBuffer[_MAX_PATH];

		wsprintf (cbBuffer, resPrompt, ulAct, ulCount);
		m_ftFilesPrompt.SetText(cbBuffer);
		m_FilesStatus.StepIt();
	}

// Datei untersuchen
	CCloseFileOnExit File (fopen (pcFile, "r"));

	if (!File.IsOpen())
		return STG_E_PATHNOTFOUND;

// Layer = Dateiname !

	_splitpath (pcFile, NULL, NULL, VLayer, NULL);

	short iTyp = OTLinie;
	m_pBack -> StoreLayer(VLayer,iTyp);

// einmal geparst müßte reichen
	m_pBack -> SetFilesParsed(true);
	return S_OK;
}
////////////////////////////////VIDEO////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
HRESULT CImpBnaExtension::VideoParseDat (FILE *pActFile, LPCSTR pcFile)
{
	if (pActFile == NULL)
		return S_FALSE;  

	long lIndex = 0L;
	HRESULT hr = E_FAIL;

	char cbLine[4*_MAX_PATH];                       // 1 Zeile

// Layer = Dateiname !

	_splitpath (pcFile, NULL, NULL, VLayer, NULL);


	try {
   	// aktive Datenquelle bsorgen
      	g_hPr = DEX_GetDataSourceHandle();
      	_ASSERTE(NULL != g_hPr);
      
	// Flag initialisieren
   		fFirstIdent = true;
   		fFirstMCode = true;

		EnsurePolyMCodes();

		satz_nr = 0;
		lIndex = 0;

		bool fObjectWasSkipped = false;

		App::Exec(ExecWhileEvent);

		DWORD dwObjTyp;
		short iID;
		short iName1;
		short iName2;

		char VName1[13];
		char VName2[7];
		char VID[18];

		VName1[0] = '\0';
		VName2[0] = '\0';
		VID[0] = '\0';

		double dAussSatz = 10.0;
		double dXRef = 0.0;
		double dYRef = 0.0;


		while (fgets (cbLine, sizeof(cbLine)-1, pActFile)) {

			yylineno++;		/* Zeilennummer */

			if ( strncmp (cbLine,"@",1) != 0 )
				continue;

			char *ptr = strchr (&cbLine[1] , '@');
			if ( ptr)
				continue;

			if ( cbLine[13] != 'N')
				continue;

			if ( cbLine[21] != 'E')
				continue;

			if ( lIndex == 0 )		{		// Header


  			// Vorhergehendes EO bearbeiten
				if (!fObjectWasSkipped && satz_nr > 0) {
					if (end_previous_object (pActFile))
						return S_OK;
				}

    		// Nächstes Objekt beginnen 
				fObjectWasSkipped = false;
				++satz_nr;
	      		init_new_object ();



			// Layer behandeln
				CTable t (*g_OKSTree);

				char *cptr = &cbLine[0];
				cptr++;


				if (!t.Find((void *)VLayer)) {
					_ASSERTE(FALSE);		// should exist
					SkipObject(pActFile);
					fObjectWasSkipped = true;
					continue;
				}

				TR_LayerLock l(t);

				if (!l) {
					_ASSERTE(FALSE);		// snh
					SkipObject(pActFile);
					fObjectWasSkipped = true;
					continue;
				}



				if ( strncmp (cbLine,"@",1) == 0) {		// Headereinträge - Objektdefinition 


			// hier ist der neue Ident
			//		dwObjTyp = OTPunkt;
			//		koord_paare = 1;

					dwObjTyp = OTLinie;
					koord_paare = -10;

					iName1 = iName2 = iID = 1;

				}


			// Objekttyp und Stützpunktanzahl
				if (1 == koord_paare)
					sta[1] = O_PUNKT;
				else if (koord_paare < 0) {
					sta[1] = O_LINIE;
					koord_paare = -koord_paare;
				}
				else {
					_ASSERTE(2 < koord_paare);
					sta[1] = O_FLAECHE;
				}

				ULONG lIdent = l -> Ident(dwObjTyp);

				if (0 == lIdent) {
			// Objekte dieses Layers/Objekttyps sollen nicht importiert werden
			//		fObjectWasSkipped = true;
			//		continue;
					lIdent = IdentDefined (VLayer);

				}


				if (lIdent != g_ulPolyId) {
					g_ulPolyId = lIdent;
					DefinePolyDatMCodes(sta[1]);
				}
		   		id = lIdent;

	
//////////////////////////////////////////////////////////////////////////////
// @020903084436N5050598E01203664G006+00306E0000N0000D0000


				strncpy (VName1,cptr,12);		//Datum + Startzeit
				VName1[12] = '\0';

	//			strncpy (VName2,cptr+6,6);		//Zeit
	//			VName2[6] = '\0';

				strncpy (VID,cptr+12,17);		//Koord
				VID[17] = '\0';

				// Name1, Name2 und Id behandlen
				if (l -> GetImportAttributes(dwObjTyp)) {
					ResourceFile RF (g_pDLLName);

				// Name 1
					if ( iName1 >= 0 ) {
						if (INVALID_HFEATURE == g_ulName1) {
							ResString resName1 (ResID(IDS_POLYNAME1, &RF), 64);
							HFEATURE hFeat = EnsurePolyMCode(resName1);

							if (INVALID_HFEATURE != hFeat && 
								EC_OKAY == MCodeIsDefined(hFeat, resName1))
							{
								SetTextField(VName1, hFeat);
							}
						}
						else {
	
							SetTextField(VName1, g_ulName1);
						}
					}	// Name1

				// Name 2
				/*---------------
					if ( iName2 >= 0) {
						if (INVALID_HFEATURE == g_ulName2) {
							ResString resName2 (ResID(IDS_POLYNAME2, &RF), 64);
							HFEATURE hFeat = EnsurePolyMCode(resName2);

						if (INVALID_HFEATURE != hFeat && 
							EC_OKAY == MCodeIsDefined(hFeat, resName2))
							{
								SetTextField(VName2, hFeat);
							}
						}
						else {
							SetTextField(VName2, g_ulName2);
						}
					}		// Name 2
--------------------------------------------------------------------*/

					// ID
					if ( iID >= 0 ) {

						if (INVALID_HFEATURE == g_ulID) {
							ResString resID (ResID(IDS_POLYID, &RF), 64);
							HFEATURE hFeat = EnsurePolyMCode(resID);

							if (INVALID_HFEATURE != hFeat && 
								EC_OKAY == MCodeIsDefined(hFeat, resID))
							{
								SetTextField(VID, hFeat);
							}
						}

						else {

							SetTextField(VID, g_ulID);
						}

					}		// iID
				} 
				else {
					
					if ( iName1 >= 0 ) {
						SetTextField(VName1, g_ulName1);
					}
					/*-----
					if ( iName2 >= 0 ) {
		 				SetTextField(VName2, g_ulName2);
					}
------------------------------------------------------------*/
					if ( iID <= 0 ) {
		 				SetTextField(VID, g_ulID);
					}
				}

			// UniqueIdent
				char cbBuffer[_MAX_PATH];

				wsprintf (cbBuffer, "%s_%ld", VLayer, satz_nr);
				if (MemoIdentifikator(lIdent))
					SetTextField(g_cMemoRef, g_ulMemo);
				SetTextField(cbBuffer, g_ulUniqueId);


				if ( strncmp (cbLine,"@",1) == 0) {		// Headereinträge - Objektdefinition

			//	POINT-Koordinaten
// @020903084436  N5050598 E01203664  G006+00306E0000N0000D0000

//					lgi = 1;
					lgi = 0;
					char XH[3];
					char XM[3];
					char XR[4];

					char YH[3];
					char YM[3];
					char YR[4];

					cptr = &cbLine[0];
					

					strncpy(YH,cptr+14,2);
					YH[2] = '\0';
					strncpy(YM,cptr+16,2);
					YM[2] = '\0';

					strncpy(YR,cptr+18,3);
					YR[3] = '\0';


					strncpy(XH,cptr+23,2);
					XH[2] = '\0';

					strncpy(XM,cptr+25,2);
					XM[2] = '\0';

					strncpy(XR,cptr+27,3);
					XR[3] = '\0';


					long yh = atol(YH);
					long ym = atol(YM);
					long yr = atol(YR);

					long xh = atol(XH);
					long xm = atol(XM);
					long xr = atol(XR);


					double x = ((double)xr/1000.0 * 60.0) + ((double)xm * 60.0) + ((double)xh * 3600.0);	
					double y = ((double)yr/1000.0 * 60.0) + ((double)ym * 60.0) + ((double)yh * 3600.0);	


					int irc = 0;

					gxi[lIndex] = x;
					gyi[lIndex] = y;

					dXRef = x;
					dYRef = y;

					lIndex++;
				}

			} else {	// Header POLY,SEG,POINT

			// Koordinaten !!!

			// Layer behandeln
					CTable t (*g_OKSTree);

					char *cptr = &cbLine[0];


					if (!t.Find((void *)VLayer)) {
						_ASSERTE(FALSE);		// should exist
						SkipObject(pActFile);
						fObjectWasSkipped = true;
						continue;
					}

					TR_LayerLock l(t);


					char XH[3];
					char XM[3];
					char XR[4];

					char YH[3];
					char YM[3];
					char YR[4];


					strncpy(YH,cptr+14,2);
					YH[2] = '\0';
					strncpy(YM,cptr+16,2);
					YM[2] = '\0';

					strncpy(YR,cptr+18,3);
					YR[3] = '\0';


					strncpy(XH,cptr+23,2);
					XH[2] = '\0';

					strncpy(XM,cptr+25,2);
					XM[2] = '\0';

					strncpy(XR,cptr+27,3);
					XR[3] = '\0';


					long yh = atol(YH);
					long ym = atol(YM);
					long yr = atol(YR);

					long xh = atol(XH);
					long xm = atol(XM);
					long xr = atol(XR);


					double x = ((double)xr/1000.0 * 60.0) + ((double)xm * 60.0) + ((double)xh * 3600.0);	
					double y = ((double)yr/1000.0 * 60.0) + ((double)ym * 60.0) + ((double)yh * 3600.0);	

					if ( fObjectWasSkipped )
						continue;

					if ( abs ( x-dXRef) > dAussSatz || abs ( y-dYRef) > dAussSatz)
						continue;

					dXRef = x;
					dYRef = y;


					gxi[lIndex] = x;
					gyi[lIndex] = y;

					lgi++;				// Koordinatenanzahl

					koord_paare = lgi;

					lIndex++;

					cptr++;

					// Endzeit
					VName2[0] = '\0';
					strncpy (VName2,cptr+6,6);		//Zeit

					VName2[6] = '\0';


			}



		}

	// Vorhergehendes EO bearbeiten
		if (!fObjectWasSkipped && satz_nr > 0) {

			// Layer behandeln
			CTable t (*g_OKSTree);

			if (!t.Find((void *)VLayer)) {
				_ASSERTE(FALSE);		// should exist
				return S_FALSE;
			}


			TR_LayerLock l(t);

			if (l -> GetImportAttributes(dwObjTyp)) {
				ResourceFile RF (g_pDLLName);



			// Name 2

				if ( iName2 >= 0) {
					if (INVALID_HFEATURE == g_ulName2) {
						ResString resName2 (ResID(IDS_POLYNAME2, &RF), 64);
						HFEATURE hFeat = EnsurePolyMCode(resName2);

						if (INVALID_HFEATURE != hFeat && 
								EC_OKAY == MCodeIsDefined(hFeat, resName2))
						{
							SetTextField(VName2, hFeat);
						}
					}
					else {
						SetTextField(VName2, g_ulName2);
					}
				}		// Name 2

			} 
			else {
					
					
				if ( iName2 >= 0 ) {
						SetTextField(VName2, g_ulName2);
				}

			}


			if (end_previous_object (pActFile))
				return S_OK;
		}
		hr = S_FALSE;
	} 
	catch(...) {
		hr = E_UNEXPECTED;
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////VIDEO////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////GCA////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
HRESULT CBNAProgressDlg::GCAFileDat(LPCSTR pcFile, ULONG ulAct, ULONG ulCount)
{

// gg. globalen Status weitersetzen
	if (ulCount > 1) {
	ResourceFile RF (g_pDLLName);
	ResString resPrompt (ResID(IDS_FILES_PROMPT, &RF), 64);
	char cbBuffer[_MAX_PATH];

		wsprintf (cbBuffer, resPrompt, ulAct, ulCount);
		m_ftFilesPrompt.SetText(cbBuffer);
		m_FilesStatus.StepIt();
	}

// Datei untersuchen
	CCloseFileOnExit File (fopen (pcFile, "r"));

	if (!File.IsOpen())
		return STG_E_PATHNOTFOUND;

	fseek (File.Ptr(), 0L, SEEK_END);		// Dateilänge bestimmen

	long lLen = ftell (File.Ptr());
	int iToShift = 0;

	while (lLen > SHRT_MAX) {
		lLen >>= 1;
		++iToShift;
	}

	char cbLine[4*_MAX_PATH];

	m_Status.SetRange(0, lLen);
	m_Status.SetPos(0);
	m_ftFileName.SetText(pcFile);

	fseek (File.Ptr(), 0L, SEEK_SET);			// wieder am Anfang
	while (fgets (cbLine, sizeof(cbLine)-1, File.Ptr())) {
		long lPos = ftell(File.Ptr());

		lPos >>= iToShift;
		m_Status.SetPos (lPos);		// nächste Zeile gelesen
		App::Exec(ExecWhileEvent);			// ggf. Cancel bearbeiten


		short iTyp = OTPunkt;
		// 08_2_22_000_001
		char Layer[15];
		strncpy (Layer,cbLine,sizeof(Layer));
		Layer[15] = '\0';

		m_pBack -> StoreLayer(Layer,iTyp);

	}

// einmal geparst müßte reichen
	m_pBack -> SetFilesParsed(true);

	return S_OK;

}

///////////////////////////////////////////////////////////////////////////////////////////////
HFEATURE GetGCACode ( UINT ID)
{

	ResourceFile RF (g_pDLLName);
	ResString resName (ResID(ID, &RF), 64);
	HFEATURE hFeat = EnsurePolyMCode(resName);

	if (INVALID_HFEATURE != hFeat)
		MCodeIsDefined(hFeat, resName);

	return hFeat;
}

///////////////////////////////////////////////////////////////////////////////
HRESULT CImpBnaExtension::GCAParseDat (FILE *pActFile, LPCSTR pcFile)
{
	if (pActFile == NULL)
		return S_FALSE;  

// Registry-Eintrag prüfen

	RETURN_FAILED_HRESULT(DATImportRegistry (IMPORTSTANDARDDAT));
	RETURN_FAILED_HRESULT(DATImportRegistry (IMPORTPUNKTDAT));


	long lIndex = 0L;
	HRESULT hr = E_FAIL;

// Layer 
	// 08_2_22_000_001
	char Layer[15];


	char cbLine[4*_MAX_PATH];                       // 1 Zeile

	try {
   	// aktive Datenquelle bsorgen
      	g_hPr = DEX_GetDataSourceHandle();
      	_ASSERTE(NULL != g_hPr);
      
	// Flag initialisieren
   		fFirstIdent = true;
   		fFirstMCode = true;


		satz_nr = 0;
		lIndex = 0;

		bool fObjectWasSkipped = false;

		App::Exec(ExecWhileEvent);

		while (fgets (cbLine, sizeof(cbLine)-1, pActFile)) {

			yylineno++;		/* Zeilennummer */

			lIndex = 0;

  			// Vorhergehendes EO bearbeiten
			if (!fObjectWasSkipped && satz_nr > 0) {
				if (end_previous_object (pActFile))
					return S_OK;
			}

    		// Nächstes Objekt beginnen 
			fObjectWasSkipped = false;
			++satz_nr;
	      	init_new_object ();

			strncpy (Layer,cbLine,sizeof(Layer));
			Layer[15] = '\0';

			// tokenizer zerteilt die Kopfzeile in Tokens:
			// token 0: GCO
			// token 1: Strasse
			// token 2: Hausnummer
			// token 3: Hausnr. Zusatz
			// token 4: Bis-HausNr.
			// token 5: Bis-HausNr.-Zusatz
			// token 6: PLZ
			// token 7: Ort
			// token 8: Ortsteil
			// token 9: Rechtswert
			// token 10: Hochwert

			os_tokenizer token(";", true, "", "\n", "", false);

			vector<string> tokens = token.tokenize(cbLine);

			if (GCAFIELDCOUNT + 2 > tokens.size()) 
				continue;

			short iTokenSize = tokens.size() -1;

			DWORD dwObjTyp;
			short iID;
			short iName1;
			short iName2;

			// Layer behandeln

			CTable t (*g_OKSTree);
			if (!t.Find((void *)Layer)) {
				_ASSERTE(FALSE);		// should exist
				SkipObject(pActFile);
				fObjectWasSkipped = true;
				continue;
			}

			TR_LayerLock l(t);

			if (!l) {
				_ASSERTE(FALSE);		// snh
				SkipObject(pActFile);
				fObjectWasSkipped = true;
				continue;
			}



			// hier ist der neue Ident
			dwObjTyp = OTPunkt;
			koord_paare = 1;

			iName1 = iName2 = iID = POLYDATNOTHING;

			// Objekttyp und Stützpunktanzahl
			if (1 == koord_paare)
				sta[1] = O_PUNKT;

			ULONG lIdent = l -> Ident(dwObjTyp);

			if (0 == lIdent) {
			// Objekte dieses Layers/Objekttyps sollen nicht importiert werden
				fObjectWasSkipped = true;
				continue;
			}


			if (lIdent != g_ulPolyId || sta[1] != g_ulPolyIdTyp) {
				EnsurePolyDATMCodes(sta[1]);
				g_ulPolyId = lIdent;
				g_ulPolyIdTyp = sta[1];
				DefinePolyDatMCodes(sta[1]);
			}
		   	id = lIdent;

	

			for ( long lCount = 0; lCount < GCAFIELDCOUNT; lCount++) {


				HFEATURE hFeat = GetGCACode ( GCAFELD[lCount]);

				if (INVALID_HFEATURE != hFeat) {

					if ( tokens[lCount].size() > 0)
						SetTextField(tokens[lCount].c_str(), hFeat);
				}

			}



//-------------------------------------------------------------------------------------
			// UniqueIdent
			char cbBuffer[_MAX_PATH];

			wsprintf (cbBuffer, "%s_%ld", tokens[7].c_str(), satz_nr);
			if (MemoIdentifikator(lIdent))
				SetTextField(g_cMemoRef, g_ulMemo);
			SetTextField(cbBuffer, g_ulUniqueId);



			//	POINT-Koordinaten
			lgi = 1;

			char oLine[_MAX_PATH];
			int irc = 0;

			double xref,yref;

			wsprintf (oLine,"%s,%s",tokens[GCAFIELDCOUNT].c_str(),tokens[GCAFIELDCOUNT+1].c_str());
			irc = sscanf (oLine, "%lf,%lf", &xref, &yref);

			gxi[lIndex] = (xref + g_dOffsetX) * g_dScaling;
			gyi[lIndex] = (yref + g_dOffsetY) * g_dScaling;

			lIndex++;


		}

	// Vorhergehendes EO bearbeiten
		if (!fObjectWasSkipped && satz_nr > 0) {
			if (end_previous_object (pActFile))
				return S_OK;
		}
		hr = S_FALSE;
	} 
	catch(...) {
		hr = E_UNEXPECTED;
	}
	return hr;
}




////////////////////////////////GCA////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////