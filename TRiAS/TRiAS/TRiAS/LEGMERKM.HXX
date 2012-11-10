// Wrapper für Parser, der LegendenEintragsInfo interpretiert -----------------
// File: LEGMERKM.HXX

#if !defined(_LEGMERKM_HXX)
#define _LEGMERKM_HXX

#undef DELETE
#define DELETE(x) {if(x){delete(x);(x)=NULL;}}

class CLegEntryParser {
private:
	class yy_err_LegendProc_obj	*m_pYYErr;	// Fehlerausgabe
	class yy_inp_LegendString_obj	*m_pYYInp;	// Eingabe
	class yy_lex_LegendMerkmal_obj 	*m_pYYLexer;	// Scanner
	class yy_psr_LegendMerkmal_obj	*m_pYYParser;	// Parser
	
public:
		CLegEntryParser (void);
		~CLegEntryParser (void);

	BOOL FInit (void);
	
static CLegEntryParser *CreateInstance (void);

	int ParseString (short iTTyp, INT_PTR lTarget, INT_PTR lMCode,
			 char *pLegEntryText, CLegendInfoEntry *[LEGENTRYTYPE_CNT]);	// workhorse
};

#endif // _LEGMERKM_HXX
