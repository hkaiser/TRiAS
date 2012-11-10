
#include "stdafx.h"
#include "GPSImport.h"
#include "GPSImportDlg.h"

#include <fnamestr.h>
#include <eonrguid.h>

#include <ospace/std/vector>
#include <ospace/string/tokenize.h>
#include "GPSImportDlg.h"

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include <ospace/com/smartif.h>
#include <com/DefSmartIf.h>

#include <ospace/com/ComErrorMacros.h>
#include <com/Errormacros2.h>
#include <com/VariantHelpers.h>
#include <com/BSTRHelpers.h>
#include <com/GUIDHelpers.h>
#include <com/StreamHelpers.h>


#include "CoordSystems.h"
#include "garminFile.h"

/* Objekttypen */
#define E_OBJEKT	1

////////////////
static char outBuff[1024];
///////////////////////////////////////
int	yylineno = 0;		/* Zeilennummer */

long koord_paare = 0;	// Anzahl der einzulesenden Koordinatenpaare
long lgi = 0;				// Koordinatenanzahl

long sta[2] = { E_OBJEKT, 0 };		// Status



#define OTPunkt		0x01
#define OTLinie		0x02
#define OTFlaeche	0x04
#define OTText		0x08

//XX	#define INLINE inline
extern "C" char *PASCAL DtoAFlt (char *, char *, double);

////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
////////////////////////////////////////////////////////////////////////////////////////
// Objekttyp aus Geometriefeld des Kopfsatzes berechnen
DWORD GetObjType (string &rStr, long *pulCount = NULL)
{
size_t iPos = rStr.find_first_not_of(", \t");

	_ASSERTE(os_npos != iPos);

long iKoords = atol(rStr.substr(iPos).c_str());

	if (NULL != pulCount)
		*pulCount = iKoords;

	if (1 == iKoords)
		return OTPunkt;
	return iKoords < 0 ? OTLinie : OTFlaeche;
}

// Com initialisieren
class CInitCom
{
public:
	CInitCom() { CoInitialize(NULL); }
	~CInitCom() { CoUninitialize(); }
};
CInitCom g_InitCom;

CCoordSystems g_CoordSys;



//-----------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
// überspringen des aktuellen Objektes im BNA-File
bool CGPSImportDlg::SkipObject(FILE *pFile)
{
long lLastPos = ftell(pFile);
char cbBuffer[4*_MAX_PATH];

	while (fgets (cbBuffer, sizeof(cbBuffer)-1, pFile)) {
		if ('"' == cbBuffer[0]) {		
		// Headereinträge - Objektdefinition
			fseek(pFile, lLastPos, SEEK_SET);
			return true;						// nächstes Objekt gefunden
		}
		yylineno++;
		lLastPos = ftell(pFile);
	}
	return false;		// EOF
}
/////////////////////////////////////////////////////////////////////////////////////
bool CGPSImportDlg::InitCoordSystems (void)
{

// Koordinatensysteme initialisieren
	char cbLine[4*_MAX_PATH]; 

	TCHAR sPath[_MAX_PATH];

	sPath[0] = NULL;

	if ( m_cbTcfIn.IsEmpty()) {

		m_cbTcfIn = "BeGkAuto3";	// BeGkAuto3.tcf

		if ( m_cbTcfOut.IsEmpty()) {

			m_cbTcfOut = "WgsGeod";	// WgsGeod.tcf

			if ('\0' != m_cbTcfIn[0] && '\0' != m_cbTcfOut[0]) {

			// 1. Versuch  . CSIn

				if (FAILED(g_CoordSys.LoadCSIn(m_cbTcfIn))) {

			// Nun volle Länge der CTF aus EXE-Directory holen
					HMODULE hMod = GetModuleHandle(NULL);	//  Handle der EXE

	
					DWORD RC = GetModuleFileName(hMod, sPath, _MAX_PATH);	// Pfad der EXE

					if ( !RC) { 
						wsprintf(cbLine,"Kann Pfad der GPSImport.exe nicht finden.");
						AfxMessageBox (cbLine);
						return false;
					}

					char *pPos = strrchr ( sPath, '/');
					if ( pPos ) {
						*(pPos+1) = '\0';

						m_cbTcfIn.Empty();

						m_cbTcfIn = sPath;
						m_cbTcfIn = m_cbTcfIn + "BeGkAuto3";

					} else {
						wsprintf(cbLine,"Kann  Pfad der GPSImport.exe '%s' nicht analysieren.",sPath );
						AfxMessageBox (cbLine);
						return false;
					}
				// 2. Versuch  . CSIn
				
					if (FAILED(g_CoordSys.LoadCSIn(m_cbTcfIn))) {
						wsprintf(cbLine,"Kann (Eingabe-)Koordinatensystem '%s' nicht laden.", m_cbTcfIn);
						AfxMessageBox (cbLine);
						return false;

					}

				// Gleich 2. Versuch

					m_cbTcfOut.Empty();
					m_cbTcfOut = sPath;
					m_cbTcfOut = m_cbTcfOut + "WgsGeod";

					if (FAILED(g_CoordSys.LoadCSOut(m_cbTcfOut))) {
						wsprintf(cbLine,"Kann (Ausgabe-)Koordinatensystem '%s' nicht laden.", m_cbTcfOut);
						AfxMessageBox (cbLine);
						return false;

					}
				} else {	// Failed CSIn


			// 1. Versuch  . CSOut

					if (FAILED(g_CoordSys.LoadCSOut(m_cbTcfOut))) {

						wsprintf(cbLine,"Kann (Ausgabe-)Koordinatensystem '%s' nicht laden.", m_cbTcfOut);
						AfxMessageBox (cbLine);
						return false;

					}


				}


			} else {
					wsprintf(cbLine,"Kann (Eingabe/Ausgabe-)Koordinatensystem  nicht laden.");
					AfxMessageBox (cbLine);
					return false;

			}


		} else	{		// CSIn isEmpty - CSOut not !!!???
					wsprintf(cbLine,"Kann (Eingabe/Ausgabe-)Koordinatensystem  nicht laden.");
					AfxMessageBox (cbLine);

			return false;
		}


	}	// Beide Koord.Systeme sind definiert

	return true;

}

/////////////////////////////////////////////////////////////////////////////////////
bool CGPSImportDlg::PolyBNAParser (FILE *pActFile, const char *pOut)
{
	if (pActFile == NULL )
		return false;  

	long lIndex = 0L;
	int	satz_nr = 0;

	char cbLine[4*_MAX_PATH];                       // 1 Zeile



	if ( !InitCoordSystems())
		return false;



	{
	CGarminFile g_Garmin;


	try {
      
		satz_nr = 0;
		lIndex = 0;

		bool fObjectWasSkipped = false;


		RETURN_FAILED_HRESULT(g_Garmin.Init(pOut,m_iType));


		while (fgets (cbLine, sizeof(cbLine)-1, pActFile)) {

			yylineno++;		/* Zeilennummer */

			if ('"' == cbLine[0]) {		// Headereinträge - Objektdefinition

				if (m_fMustStop)
					return false;		// wir sollen aufhören

				lIndex = 0;

    		// Nächstes Objekt beginnen 
				++satz_nr;

			// tokenizer zerteilt die Kopfzeile in Tokens:
			// token 0: leer
			// token 1: NAME1
			// token 2: ','
			// token 3: NAME2
			// token 4: ','
			// token 5: ID
			// token 6: ','
			// token 7: LAYER
			// token 8: ",Geometrie" (Anzahl der Stützpunkte)
			os_tokenizer token("\"", true, "", "\n", "", false);
			vector<string> tokens = token.tokenize(cbLine);

				if (9 != tokens.size()) {
					_ASSERTE(9 == tokens.size());
					SkipObject(pActFile);
					fObjectWasSkipped = true;
					continue;		// unerwartetes Eingabeformat
				}

			// Name1, Name2 und Id behandlen

			// Objekttyp und Stützpunktanzahl
				DWORD dwObjTyp = GetObjType(tokens[8], &koord_paare);

				if (1 == koord_paare)
					sta[1] = dwObjTyp;
				else if (koord_paare < 0) {
					sta[1] = dwObjTyp;
					koord_paare = -koord_paare;
				}
				else
					sta[1] = dwObjTyp;

				if (dwObjTyp != OTLinie ) {
					SkipObject(pActFile);
					fObjectWasSkipped = true;
					continue;		// unerwartetes Eingabeformat
				}
//	Kopfversion - Koordinatenanzahl - koord_paare
				lgi = 0;

				if (m_iType)
					g_Garmin.WriteRTEHeader(tokens[1],tokens[3],tokens[5]);
			} 
			else {	
			// Koordinaten !!!

				int irc = 0;
				double xref,yref;

				lgi++;				// Koordinatenanzahl
				irc = sscanf (cbLine, "%lf,%lf", &xref, &yref);

				g_CoordSys.Transform (1,&xref, &yref );


			// Geometriezeile ausgeben
				
				if (m_iType)
					g_Garmin.WriteRTELine(&xref, &yref);
				else
					g_Garmin.WriteTRKLine(&xref, &yref);


				lIndex++;
			}
		}

	} 

	catch(...) {
		return false;
	}

	}		//CGarmin
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// Datei importieren
//bool CGPSImportThread::ImportBNA (char const *pFile,char const *pGarmin)
bool CGPSImportDlg::ImportBNA (char const *pFile,char const *pGarmin)
{


	FILE *yyin = fopen (pFile, "r");

	if (NULL == yyin)
		return false;


	fseek (yyin, 0L, SEEK_END);		// Dateilänge bestimmen

	long lLen = ftell (yyin);

	bool iFlag = true;

	if (lLen > 0) {
		string strFile (pFile);
		string str = get_name (strFile) + get_ext(strFile);


		fseek (yyin, 0L, SEEK_SET);	// wieder am Anfang


		iFlag = PolyBNAParser(yyin,pGarmin);
	

	}

	fclose (yyin);

	return iFlag;
}

