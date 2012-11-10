// Parsen einer LegendenEintragsBeschreibung ----------------------------------
// File: LEGMERKM.CXX

#include "triaspre.hxx"

#pragma warning (disable: 4251)		// string needs dll-interface

#define yy_user_config_

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_bool.h"
#include "yy_errgn.h"
#include "yy_inp.h"

#include "legmerka.hxx"

#include "legdinfo.hxx"
#include "legdinfo.inl"

#include "legmerkm.hxx"
#include "legmerkl.hxx"
#include "legmerky.hxx"

#include "yy_trace.h"
#include "yy_err.tbl"

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CLegEntryParser::CLegEntryParser (void)
{
	m_pYYErr = NULL;	// Fehlerausgabe
	m_pYYInp = NULL;	// Eingabe
	m_pYYLexer = NULL;	// Scanner
	m_pYYParser = NULL;	// Parser
}

CLegEntryParser::~CLegEntryParser (void)
{
	DELETE (m_pYYParser);
	DELETE (m_pYYLexer);
	DELETE (m_pYYInp);
	DELETE (m_pYYErr);
}

CLegEntryParser *CLegEntryParser::CreateInstance (void)
{
CLegEntryParser *pParser = new CLegEntryParser;

	if (pParser == NULL || !pParser -> FInit()) {
		DELETE (pParser);
		return NULL;
	}
	
return pParser;
}

BOOL CLegEntryParser::FInit (void)
{
//  create an error object, the default is to report errors to a C++ stream
	m_pYYErr = new yy_err_LegendProc_obj(
			NULL,		// no error output
			yy_err_tbl, yy_err_tbl_max_, 
			NULL, 0		// no synas
        	);
	if (m_pYYErr == NULL) return FALSE;
	
//  create an input object which processes input from a string
	m_pYYInp = new yy_inp_LegendString_obj(m_pYYErr);
	if (m_pYYInp == NULL) return FALSE;

//  create a lexer object
	m_pYYLexer = new yy_lex_dflt_obj(m_pYYInp, NULL, // no symtab needed
				yy_lex_obj::yy_lex_dflt_class_);
	if (m_pYYLexer == NULL) return FALSE;

//  create a parser object
	m_pYYParser = new yy_psr_dflt_obj(m_pYYLexer, 
				yy_psr_obj::yy_psr_dflt_class_, 
				yy_psr_obj::yy_psr_dflt_start_);

	return (NULL != m_pYYParser) ? TRUE : FALSE;
}

int CLegEntryParser::ParseString (
	short iTTyp, INT_PTR lTarget, INT_PTR lMCode,
	char *pLegEntryText, CLegendInfoEntry *pLIE[LEGENTRYTYPE_CNT])
{
int iRet = 0;

#if defined(_DUMP)
char *pOut = new char [strlen(pLegEntryText)+64];

	if (pOut) {
		wsprintf (pOut, "Target: %ld, LegInfo: %s\r\n", lTarget, pLegEntryText);
		OutputDebugString (pOut);
	}
#endif

// Parser in StartState setzen
	m_pYYParser -> yy_psr_start (yy_psr_obj::yy_psr_dflt_class_, yy_psr_obj::yy_psr_dflt_start_);
	m_pYYInp -> yy_inp_is_string (pLegEntryText, strlen (pLegEntryText));
	iRet = yy_psr (m_pYYParser);		// lex and parse the input
	m_pYYParser -> yy_psr_rewind();		// reset parser
	m_pYYInp -> yy_inp_close (yy_true);	// close the input object

#if defined(_DUMP)
	if (pOut) {
		wsprintf (pOut, "Parser returns: %d\r\n", iRet);
		OutputDebugString (pOut);
		delete pOut;
	}
#endif
	
// wenn Fehlerhafte Eingabe gelesen wurde, dann hier raus
	if (iRet) return -1;		// Fehler aufgetreten
		
// Generieren der LegendenEntryStrukturen
short iMode = 0;

	for (int i = 0; i < m_pYYParser -> FCnt(); ++i) {
	short iIndex = -1;
	VisType rgTyp = VT_Default;
	WORD iOrder = USHRT_MAX;
	BOOL fShow = TRUE;
	char *pText = NULL;
						
	// Typ feststellen
		switch (yy_ast_ptr(m_pYYParser -> FEntry(i)) -> yy_type()) {
		case yy_psr_LegendMerkmal_obj::PEntryInfo_:
			{
			PEntryInfo *pP = (PEntryInfo *)m_pYYParser -> FEntry(i);

				iIndex = 0;	// PunktInfo
				rgTyp = VT_Punkt;
				iMode =  ((INTEGER *)(yy_ast_ptr(pP -> yy_operand(0)))) -> yy_integer();
				iOrder = ((INTEGER *)(yy_ast_ptr(pP -> yy_operand(1)))) -> yy_integer(); 
				if (pP -> yy_num_operands() == 3)
					pText = ((STRING *)(yy_ast_ptr(pP -> yy_operand(2)))) -> yy_string();
			}
			break;

		case yy_psr_LegendMerkmal_obj::LEntryInfo_:
			{
			LEntryInfo *pL = (LEntryInfo *)m_pYYParser -> FEntry(i);

				iIndex = 1;	// LinienInfo
				rgTyp = VT_Linie;
				iMode =  ((INTEGER *)(yy_ast_ptr(pL -> yy_operand(0)))) -> yy_integer();
				iOrder = ((INTEGER *)(yy_ast_ptr(pL -> yy_operand(1)))) -> yy_integer(); 
				if (pL -> yy_num_operands() == 3)
					pText = ((STRING *)(yy_ast_ptr(pL -> yy_operand(2)))) -> yy_string();
			}
			break;

		case yy_psr_LegendMerkmal_obj::FEntryInfo_:
			{
			FEntryInfo *pF = (FEntryInfo *)m_pYYParser -> FEntry(i);

				iIndex = 2;	// FlächenInfo
				rgTyp = VT_Flaeche;
				iMode =  ((INTEGER *)(yy_ast_ptr(pF -> yy_operand(0)))) -> yy_integer();
				iOrder = ((INTEGER *)(yy_ast_ptr(pF -> yy_operand(1)))) -> yy_integer(); 
				if (pF -> yy_num_operands() == 3)
					pText = ((STRING *)(yy_ast_ptr(pF -> yy_operand(2)))) -> yy_string();
			}
			break;

		case yy_psr_LegendMerkmal_obj::TEntryInfo_:
			{
			TEntryInfo *pT = (TEntryInfo *)m_pYYParser -> FEntry(i);

				iIndex = 3;	// TextInfo
				rgTyp = VT_Text;
				iMode =  ((INTEGER *)(yy_ast_ptr(pT -> yy_operand(0)))) -> yy_integer();
				iOrder = ((INTEGER *)(yy_ast_ptr(pT -> yy_operand(1)))) -> yy_integer(); 
				if (pT -> yy_num_operands() == 3)
					pText = ((STRING *)(yy_ast_ptr(pT -> yy_operand(2)))) -> yy_string();
			}
			break;

		case yy_psr_LegendMerkmal_obj::HEntryInfo_:
			{
			HEntryInfo *pT = (HEntryInfo *)m_pYYParser -> FEntry(i);

				iIndex = 4;	// Zwischenüberschrift
				rgTyp = VT_Text;
				iMode =  ((INTEGER *)(yy_ast_ptr(pT -> yy_operand(0)))) -> yy_integer();
				iOrder = ((INTEGER *)(yy_ast_ptr(pT -> yy_operand(1)))) -> yy_integer(); 
				if (pT -> yy_num_operands() == 3)
					pText = ((STRING *)(yy_ast_ptr(pT -> yy_operand(2)))) -> yy_string();
			}
			break;
		}
		iRet = iIndex;
			
	// neuen Eintrag generieren
		DELETE(pLIE[iIndex]);
		if (iTTyp == TT_Identifikator)
			pLIE[iIndex] = new CLegendInfoIdent (iOrder, iMode & LEShown, iMode & LESpace, rgTyp, lTarget);
		if (iTTyp == TT_Objekt)
			pLIE[iIndex] = new CLegendInfoObject (iOrder, iMode & LEShown, iMode & LESpace, rgTyp, lTarget);
		if (iTTyp == TT_Sicht) {
			if (NULL == pText)
				pLIE[iIndex] = new CLegendInfoSpaceLine (iOrder, (LPCSTR)lTarget, lMCode);
			else
				pLIE[iIndex] = new CLegendInfoText (iOrder, iMode & LESpace, (LPCSTR)lTarget, lMCode);
		}

		if (NULL != pText && NULL != pLIE[iIndex])		// eigener Text
			pLIE[iIndex] -> SetText (pText);

		if (NULL == pLIE[iIndex])
			iIndex = -1;			// Fehler
	}
	return iRet;
}


