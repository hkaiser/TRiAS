// Parsen einer LegendenEintragsBeschreibung ----------------------------------
// File: LEGMERKM.CXX

#include "idntsdbp.hxx"

#include <errinstx.hxx>

#include "identres.h"		// Resourcen

#pragma warning (disable: 4251)		// string needs dll-interface

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_bool.h"
#include "yy_errgn.h"
#include "yy_inpfi.h"

#include "idntsdba.hxx"

#include "idntsdbl.hxx"		// lexer et al
#include "idntsdby.hxx"		// parser et al
#include "idntsdbm.hxx"		// Wrapper f¸r alles zusammen

#include "yy_trace.h"
#include "yy_err.tbl"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CIdentsDBImportParser :: CIdentsDBImportParser (void)
{
	m_pYYErr = NULL;	// Fehlerausgabe
	m_pYYInp = NULL;	// Eingabe
	m_pYYLexer = NULL;	// Scanner
	m_pYYParser = NULL;	// Parser
}

CIdentsDBImportParser :: ~CIdentsDBImportParser (void)
{
	DELETE_OBJ(m_pYYParser);
	DELETE_OBJ(m_pYYLexer);
	DELETE_OBJ(m_pYYInp);
	DELETE_OBJ(m_pYYErr);
}

CIdentsDBImportParser *CIdentsDBImportParser :: CreateInstance (bool fKeep, bool fReject)
{
CIdentsDBImportParser *pParser = new CIdentsDBImportParser;

	if (pParser == NULL || !pParser -> FInit (fKeep, fReject)) {
		DELETE_OBJ(pParser);
		return NULL;
	}
	
return pParser;
}

// Funktion, die im Fehlerfall gerufen wird -----------------------------------
int __stdcall ReportImportError (LPCSTR pErrorText)
{
ResString resCaption (ResID (IDS_IMPORTERROR, &g_pTE -> RF()), 64);

	return MessageBox (NULL, pErrorText, resCaption, 
			   MB_TASKMODAL|MB_OK|MB_ICONSTOP);
}

bool CIdentsDBImportParser :: FInit (bool fKeep, bool fReject)
{
//  create an error object, the default is to report errors to a C++ stream
	m_pYYErr = new yy_err_identsdb_obj(
			ReportImportError,
//			NULL,		// no error output
			yy_err_tbl, yy_err_tbl_max_, 
			NULL, 0		// no synas
        	);
	if (m_pYYErr == NULL) return FALSE;
	
	m_pYYInp = new yy_inp_identsdb_obj (m_pYYErr);
	if (m_pYYInp == NULL) return FALSE;

//  create a lexer object
	m_pYYLexer = new yy_lex_dflt_obj (m_pYYInp, NULL, // no symtab needed
				yy_lex_obj::yy_lex_dflt_class_);
	if (m_pYYLexer == NULL) return false;

//  create a parser object
	m_pYYParser = new yy_psr_dflt_obj(m_pYYLexer, 
				yy_psr_obj::yy_psr_dflt_class_, 
				yy_psr_obj::yy_psr_dflt_start_);
	if (m_pYYParser) {
		m_pYYParser -> IMode() = fKeep ? 
				yy_psr_dflt_obj::IMPORTMODE_KeepEntry :
				yy_psr_dflt_obj::IMPORTMODE_OverWrite; 
		m_pYYParser -> RMode() = fReject ?
				yy_psr_dflt_obj::REJECTMODE_RejectUnused :
				yy_psr_dflt_obj::REJECTMODE_ImportAll;
	}

return m_pYYParser != NULL;
}

int CIdentsDBImportParser :: ParseFile (LPCSTR pcFName, 
	LPPROGRESSINDICATOR pIStatus, HPROJECT hPr,
	yy_psr_identsdb_obj::yy_psr_class_enum rgPsrClass,
	yy_lex_identsdb_obj::yy_lex_class_enum rgLexStart)
{
// Parser und Lexer in StartState setzen
	m_pYYParser -> SetStatus (pIStatus);
	m_pYYParser -> yy_psr_start (rgPsrClass, yy_psr_obj::yy_psr_dflt_start_);
	m_pYYParser -> yy_psr_cur_lex() -> yy_lex_start (rgLexStart);
	m_pYYParser -> SetDataSource (hPr);

	switch (rgPsrClass) {
	case yy_psr_identsdb_obj::yy_psr_class_icodedesc_:
		m_pYYLexer -> IntBase() = DEX_GetIdBase();
		break;

	case yy_psr_identsdb_obj::yy_psr_class_mcodedesc_:
		m_pYYLexer -> IntBase() = DEX_GetMkBase();
		break;

	case yy_psr_identsdb_obj::yy_psr_class_rcodedesc_:
		m_pYYLexer -> IntBase() = 10;
		break;

	default:
		TX_ASSERT(false);
		return false;
	}

	if (!m_pYYInp -> yy_inp_is_file (pcFName, NULL))
		return yy_psr_identsdb_obj::yy_error_;

int iRet = yy_psr (m_pYYParser);		// lex and parse the input

	m_pYYInp -> yy_inp_close (yy_true);	// close the input object
	m_pYYParser -> yy_psr_rewind();		// reset parser
	m_pYYParser -> SetStatus (NULL);

#if defined(_DUMP)
char cbOut[_MAX_PATH];

	if (cbOut) {
		wsprintf (cbOut, "Parser returns: %d\r\n", iRet);
		OutputDebugString (cbOut);
	}
#endif

return iRet;
}


// Meberfunktionen des Parsers ------------------------------------------------
bool yy_psr_identsdb_obj :: WriteTXI (TXISatz *pTXI)
{
	TX_ASSERT(NULL != pTXI);
	TX_ASSERT(TXISatz_ == pTXI -> yy_type());
	TX_ASSERT(1 < pTXI -> yy_num_operands());

// Operanden isolieren
yy_ast_ptr pData0 = yy_ast_ptr(pTXI -> yy_operand(0));
yy_ast_ptr pData1 = yy_ast_ptr(pTXI -> yy_operand(1));
int iNumOps = pTXI -> yy_num_operands();

// erster Operand muﬂ ein Integer/HexInteger oder ein Objektklassenschl¸ssel sein
	if (INTEGER_ != pData0 -> yy_type() && 
		HEXIDENT_ != pData0 -> yy_type() && 
		OKS_ != pData0 -> yy_type())
	{
		return false;		// falscher Datentyp oder 'yy_error_'
	}

long lIdent = 0L;
int iNext = 1;		// normalerweise entweder OKS _oder_ Ident
HRESULT hr = S_OK;

	if (INTEGER_ == pData0 -> yy_type() || HEXIDENT_ == pData0 -> yy_type()) {
		lIdent = ((INTEGER *)pData0) -> Value();

	// dritter Operand _kann_ OKS sein
		if (OKS_ == pData1 -> yy_type()) {
		// zu bestimmtem Ident den OKS speichern
		MODOBJCLASSCODE MOCC;

			INITSTRUCT(MOCC, MODOBJCLASSCODE);
			MOCC.ulIdent = lIdent;
			MOCC.pcClass = ((OKS *)pData1) -> yy_string();
			MOCC.fOverWrite = (IMPORTMODE_KeepEntry == IMode()) ? false : true;
			hr = DEX_ModObjectClassCodeEx(m_hPr, MOCC);
			if (FAILED(hr) && GetScode(hr) != E_ACCESSDENIED)
				return false;		// Fehler
			iNext = 2;		// der n‰chste hat die Nummer 2
		} else {
		// OKS nicht gegeben, testen ob das ganze als Ident oder als OKS 
		// importiert werden soll (OKS hat Vorrang)
		char cbBuffer[32];	// Ident als OKS interpretieren und testen, ob zugehˆriger Ident 
							// verwendet ist
		long lOKSIdent = 0L;

			ultoa (lIdent, cbBuffer, DEX_GetIdBase());
			hr = IdentFromClassX (m_hPr, cbBuffer, (ULONG *)&lOKSIdent);
			if (S_OK == hr && DEX_isIdentUsedEx(m_hPr, lOKSIdent)) 
				lIdent = lOKSIdent;
		}

		if (REJECTMODE_RejectUnused == RMode() && !DEX_isIdentUsedEx(m_hPr, lIdent)) 
			return true;	// nicht benutzte nicht importieren
	}
	else if (OKS_ == pData0 -> yy_type()) {
	// nur OKS gegeben
		hr = IdentFromClassX (m_hPr, ((OKS *)pData0) -> yy_string(), (ULONG *)&lIdent);
		if (FAILED(hr)) return false;		// Fehler
		if (S_FALSE == hr && (-1 == lIdent || !DEX_isIdentUsedEx(m_hPr, lIdent))) {
		// OKS existiert noch nicht: erzeugen
			hr = IdentFromClassX (m_hPr, ((OKS *)pData0) -> yy_string(), (ULONG *)&lIdent, true);
			if (FAILED(hr)) return false;		// Fehler
		}

		if (REJECTMODE_RejectUnused == RMode() && !DEX_isIdentUsedEx(m_hPr, lIdent)) 
			return true;	// nicht benutzte nicht importieren
	} 

// n‰chster Operand ist entweder KurzText oder LangText
	pData1 = yy_ast_ptr(pTXI -> yy_operand(iNext));

string strKText;
string strLText;

	TX_ASSERT (KURZTEXT_ == pData1 -> yy_type() || LANGTEXT_ == pData1 -> yy_type());

	if (KURZTEXT_ == pData1 -> yy_type()) {
		strKText = ((KURZTEXT *)pData1) -> yy_string();
		if (iNumOps > 2) {
		yy_ast_ptr pData2 = yy_ast_ptr(pTXI -> yy_operand(iNext+1));

			TX_ASSERT (LANGTEXT_ == pData2 -> yy_type());
			if (LANGTEXT_ == pData2 -> yy_type()) 
				strLText = ((LANGTEXT *)pData2) -> yy_string();
		}
	} else if (LANGTEXT_ == pData1 -> yy_type()) {
		strLText = ((LANGTEXT *)pData1) -> yy_string();
	
	// die ersten 32 Zeichen sind gleichzeitig der Kurztext
		strKText = strLText.substr (0, 32);
	} 

// Eintrag in TRiAS setzen
PBDDATA pbdData;
ErrInstall EI (WC_NOIDENT);

	INITSTRUCT (pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;

	if (IMPORTMODE_KeepEntry == IMode()) {
	// testen, ob dieser Eintrag bereits existiert
		if (EC_OKAY == DEX_GetPBDDataEx (m_hPr, pbdData))
			return true;	// nicht ¸berschreiben
	}

// jetzt Pbd schreiben
	pbdData.pbdKText = (0 == strKText.length()) ? NULL : (char *)strKText.c_str();
	pbdData.pbdLText = (0 == strLText.length()) ? NULL : (char *)strLText.c_str();
	if (NULL == pbdData.pbdKText && NULL == pbdData.pbdLText)
		return true;	// alles gemacht

	pbdData.pbdTemp = false;
	pbdData.pbdKTextLen = strKText.length();
	pbdData.pbdLTextLen = strLText.length();

ErrCode RC = DEX_ModPBDDataEx (m_hPr, pbdData);

	return EC_OKAY == RC || WC_RETURN == RC;
}

bool yy_psr_identsdb_obj :: WriteTXM (TXMSatz *pTXM)
{
	TX_ASSERT(NULL != pTXM);
	TX_ASSERT(TXMSatz_ == pTXM -> yy_type());
	TX_ASSERT(1 < pTXM -> yy_num_operands());

// Operanden isolieren
yy_ast_ptr pData0 = yy_ast_ptr(pTXM -> yy_operand(0));
int iNumOps = pTXM -> yy_num_operands();

// erster Operand muﬂ ein Integer/HexInteger sein
	if (INTEGER_ != pData0 -> yy_type() && HEXMCODE_ != pData0 -> yy_type()) 
		return false;		// falscher Datentyp oder 'yy_error_'

long lMCode = ((INTEGER *)pData0) -> Value();

	if (REJECTMODE_RejectUnused == RMode() && !isMCodeUsed(lMCode)) 
		return true;		// nicht benutzte nicht importieren

// MerkmalsTyp lesen
short iMTyp = 'A';
yy_ast_ptr pDataTyp = yy_ast_ptr(pTXM -> yy_operand(1));

	TX_ASSERT(TXMType_ == pDataTyp -> yy_type());
	if (TXMType_ == pDataTyp -> yy_type()) 
		iMTyp = ((TXMType *)pDataTyp) -> Type();
	else
		return false;

// nochmal testen (yy_error_)
	if (iNumOps < 6) {
		TX_ASSERT(iNumOps < 6);
		return false;
	}

// KurzText und Langtext rauskriegen (letzter bzw. vorletzter Operand)
short iMLen = _MAX_PATH;

// MerkmalsL‰nge interessiert
yy_ast_ptr pDataLen = yy_ast_ptr(pTXM -> yy_operand(3));

	TX_ASSERT(INTEGER_ == pDataLen -> yy_type());
	if (INTEGER_ == pDataLen -> yy_type())
		iMLen = short(((INTEGER *)pDataLen) -> Value());

// weiterer Operand ist entweder KurzText oder LangText
string strKText;
string strLText;
yy_ast_ptr pData1 = yy_ast_ptr(pTXM -> yy_operand(5));

	TX_ASSERT (KURZTEXT_ == pData1 -> yy_type() || LANGTEXT_ == pData1 -> yy_type());

	if (KURZTEXT_ == pData1 -> yy_type()) {
		strKText = ((KURZTEXT *)pData1) -> yy_string();
		if (iNumOps > 6) {
		yy_ast_ptr pData2 = yy_ast_ptr(pTXM -> yy_operand(6));

			TX_ASSERT (LANGTEXT_ == pData2 -> yy_type());
			if (LANGTEXT_ == pData2 -> yy_type()) 
				strLText = ((LANGTEXT *)pData2) -> yy_string();
		}
	} else if (LANGTEXT_ == pData1 -> yy_type()) {
		strLText = ((LANGTEXT *)pData1) -> yy_string();
	
	// die ersten 32 Zeichen sind gleichzeitig der Kurztext
		strKText = strLText.substr (0, 32);
	} 

// Eintrag in TRiAS setzen
PBDMERKMAL pbdData;
ErrInstall EI (WC_NOMERKMAL);

	INITSTRUCT (pbdData, PBDMERKMAL);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;

	if (IMPORTMODE_KeepEntry == IMode()) {
	// testen, ob dieser Eintrag bereits existiert
		if (EC_OKAY == DEX_GetPBDData (pbdData))
			return true;	// nicht ¸berschreiben
	}

// jetzt Pbd schreiben
	pbdData.pbdKText = (0 == strKText.length()) ? NULL : (char *)strKText.c_str();
	pbdData.pbdLText = (0 == strLText.length()) ? NULL : (char *)strLText.c_str();
	pbdData.pbdKTextLen = strKText.length();
	pbdData.pbdLTextLen = strLText.length();
	pbdData.ipbdMTyp = iMTyp;
	pbdData.ipbdMLen = iMLen;
		
	return EC_OKAY == DEX_ModPBDData (pbdData);
}

bool yy_psr_identsdb_obj :: WriteTXR (TXRSatz *pTXR)
{
	TX_ASSERT(NULL != pTXR);
	TX_ASSERT(TXRSatz_ == pTXR -> yy_type());
	TX_ASSERT(1 < pTXR -> yy_num_operands());

// Operanden isolieren
yy_ast_ptr pData0 = yy_ast_ptr(pTXR -> yy_operand(0));
int iNumOps = pTXR -> yy_num_operands();

// erster Operand muﬂ ein Integer/HexInteger sein
	if (iNumOps < 3 || INTEGER_ != pData0 -> yy_type())
		return false;		// falscher Datentyp oder yy_error

long lRCode = ((INTEGER *)pData0) -> Value();

// RelationsTyp lesen
short iRTyp = 'K';
yy_ast_ptr pDataTyp = yy_ast_ptr(pTXR -> yy_operand(1));

	TX_ASSERT(TXRType_ == pDataTyp -> yy_type());
	if (TXRType_ == pDataTyp -> yy_type()) 
		iRTyp = ((TXRType *)pDataTyp) -> Type();
	else 
		return false;

// dritter Operand ist entweder KurzText oder LangText
string strKText;
string strLText;
yy_ast_ptr pData1 = yy_ast_ptr(pTXR -> yy_operand(2));

	TX_ASSERT (KURZTEXT_ == pData1 -> yy_type() || LANGTEXT_ == pData1 -> yy_type());

	if (KURZTEXT_ == pData1 -> yy_type()) {
		strKText = ((KURZTEXT *)pData1) -> yy_string();
		if (iNumOps > 3) {
		yy_ast_ptr pData2 = yy_ast_ptr(pTXR -> yy_operand(3));

			TX_ASSERT (LANGTEXT_ == pData2 -> yy_type());
			if (LANGTEXT_ == pData2 -> yy_type()) 
				strLText = ((LANGTEXT *)pData2) -> yy_string();
		}
	} else if (LANGTEXT_ == pData1 -> yy_type()) {
		strLText = ((LANGTEXT *)pData1) -> yy_string();
	
	// die ersten 32 Zeichen sind gleichzeitig der Kurztext
		strKText = strLText.substr (0, 32);
	} 

// Pbd schreiben
PBDRELATION pbdData;
ErrInstall EI (WC_NORELATION);

	INITSTRUCT (pbdData, PBDRELATION);
	pbdData.pbdTyp = 'r';
	pbdData.pbdCode = lRCode;

	if (IMPORTMODE_KeepEntry == IMode()) {
	// testen, ob dieser Eintrag bereits existiert
		if (EC_OKAY == DEX_GetPBDData (pbdData))
			return true;	// nicht ¸berschreiben
	}

// jetzt Pbd schreiben
	pbdData.pbdKText = (0 == strKText.length()) ? NULL : (char *)strKText.c_str();
	pbdData.pbdLText = (0 == strLText.length()) ? NULL : (char *)strLText.c_str();
	pbdData.pbdKTextLen = strKText.length();
	pbdData.pbdLTextLen = strLText.length();
	pbdData.ipbdRTyp = iRTyp;

	return EC_OKAY == DEX_ModPBDData (pbdData);
}

// Funktion, die alle MCodes in Set eint¸tet ----------------------------------
extern "C" 
BOOL _XTENSN_EXPORT PASCAL FillAllMCodeParserList (long lMCode, DWORD, void *pData)
{
	((yy_psr_identsdb_obj::MCodeSet *)pData) -> insert (lMCode);
	return true;
}
