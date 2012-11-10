// Wrapper für Parser, der IdentsDBenEintragsInfo interpretiert -----------------
// File: LEGMERKM.HXX

#if !defined(_LEGMERKM_HXX)
#define _LEGMERKM_HXX

class CIdentsDBImportParser {
private:
	class yy_err_identsdb_obj	*m_pYYErr;		// Fehlerausgabe
	class yy_inp_identsdb_obj	*m_pYYInp;		// Eingabe
	class yy_lex_identsdb_obj 	*m_pYYLexer;	// Scanner
	class yy_psr_identsdb_obj	*m_pYYParser;	// Parser
	
public:
		CIdentsDBImportParser (void);
		~CIdentsDBImportParser (void);

	bool FInit (bool fKeep, bool fReject);
	
static CIdentsDBImportParser *CreateInstance (bool fKeep, bool fReject);

	int ParseFile (LPCSTR pcFName, LPPROGRESSINDICATOR pIStatus, HPROJECT hPr,
		yy_psr_identsdb_obj::yy_psr_class_enum rgPsrClass,
		yy_lex_identsdb_obj::yy_lex_class_enum rglexStart);
};

#endif // _LEGMERKM_HXX
