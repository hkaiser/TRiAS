
//////////////////////////////////////////////////////////////////////////////
//
//  FILENAME:          idntsdby.hxx
//
//  FILE DESCRIPTION:  Header file with derived parser class declarations
//
//  Input file:        \TRIASDEV.MVC\XTENSION\IDENTSDB\IDNTSDBM.YXX
//  Options:           -no_debug -table fast -no_line -no_far 
//  Include Paths:     current directory
//
//  Automatically generated by Yacc++ Revision 2.0 (94 May 6)
//  on Mon Aug  5 21:29:23 1996
//
//////////////////////////////////////////////////////////////////////////////

#include "yy_ansi.h"
#include "yy_ast.h"
#include "yy_err.h"
#include "yy_sym.h"
class yy_export yy_psr_identsdb_obj;
class TXISatz;
class TXMType;
class TXMSatz;
class TXRType;
class TXRSatz;
#include "yy_myref.h"
#ifndef yy_decl_TXISatz
#define yy_decl_TXISatz 1
class TXISatz : public yy_ast_obj {
 public:
    TXISatz(yy_psr_identsdb_obj *yy_this_psr_ptr);
    virtual ~TXISatz();
    virtual void yy_dump(
        yy_err_ptr yy_this_err_obj,
        const char *yy_dump_title);
    inline int yy_type();
    int yy_type(int);
    inline int yy_num_operands();
    int yy_num_operands(int);
    inline yy_ref_obj &yy_operand(int);
    yy_ref_obj &yy_operand(int, yy_ref_obj);
 protected:
    int yy_this_type;
    int                 yy_this_num_operands;
    yy_ref_ptr          yy_this_operand;  // variable length array
};
#endif /* yy_decl_TXISatz */

#ifndef yy_decl_TXMType
#define yy_decl_TXMType 1
class TXMType : public yy_ast_obj {
 public:
    TXMType(yy_psr_identsdb_obj *yy_this_psr_ptr);
    virtual ~TXMType();
    virtual void yy_dump(
        yy_err_ptr yy_this_err_obj,
        const char *yy_dump_title);
    inline int yy_type();
    int yy_type(int);
 protected:
    int yy_this_type;

		public:
		inline int Type (void) { return m_iType; }
		
		private:
			int m_iType;
	};
#endif /* yy_decl_TXMType */

#ifndef yy_decl_TXMSatz
#define yy_decl_TXMSatz 1
class TXMSatz : public yy_ast_obj {
 public:
    TXMSatz(yy_psr_identsdb_obj *yy_this_psr_ptr);
    virtual ~TXMSatz();
    virtual void yy_dump(
        yy_err_ptr yy_this_err_obj,
        const char *yy_dump_title);
    inline int yy_type();
    int yy_type(int);
    inline int yy_num_operands();
    int yy_num_operands(int);
    inline yy_ref_obj &yy_operand(int);
    yy_ref_obj &yy_operand(int, yy_ref_obj);
 protected:
    int yy_this_type;
    int                 yy_this_num_operands;
    yy_ref_ptr          yy_this_operand;  // variable length array
};
#endif /* yy_decl_TXMSatz */

#ifndef yy_decl_TXRType
#define yy_decl_TXRType 1
class TXRType : public yy_ast_obj {
 public:
    TXRType(yy_psr_identsdb_obj *yy_this_psr_ptr);
    virtual ~TXRType();
    virtual void yy_dump(
        yy_err_ptr yy_this_err_obj,
        const char *yy_dump_title);
    inline int yy_type();
    int yy_type(int);
 protected:
    int yy_this_type;

		public:
		inline int Type (void) { return toupper(m_iType); }
		
		private:
			int m_iType;
	};
#endif /* yy_decl_TXRType */

#ifndef yy_decl_TXRSatz
#define yy_decl_TXRSatz 1
class TXRSatz : public yy_ast_obj {
 public:
    TXRSatz(yy_psr_identsdb_obj *yy_this_psr_ptr);
    virtual ~TXRSatz();
    virtual void yy_dump(
        yy_err_ptr yy_this_err_obj,
        const char *yy_dump_title);
    inline int yy_type();
    int yy_type(int);
    inline int yy_num_operands();
    int yy_num_operands(int);
    inline yy_ref_obj &yy_operand(int);
    yy_ref_obj &yy_operand(int, yy_ref_obj);
 protected:
    int yy_this_type;
    int                 yy_this_num_operands;
    yy_ref_ptr          yy_this_operand;  // variable length array
};
#endif /* yy_decl_TXRSatz */


#include "yy_psrfa.h"

#ifndef yy_psr_identsdb_obj_h_
#define yy_psr_identsdb_obj_h_ 1

typedef class yy_export yy_psr_identsdb_obj *yy_psr_identsdb_obj_ptr;

/////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_psr_identsdb_obj
//
//  The yy_psr_identsdb_obj is the derived class which provides your application
//  specific parser classes.
// 
/////////////////////////////////////////////////////////////////////////////

class yy_export yy_psr_identsdb_obj : public yy_psr_obj_fast {

 public:

    enum yy_psr_cmd_max_enum { yy_psr_cmd_max_ = 3253 };

    enum yy_psr_num_states_enum { yy_psr_num_states_ = 29 };

    enum yy_psr_pmin_enum { yy_pmin_ = -2 };

    enum yy_psr_pmax_enum { yy_pmax_ = 33 };

    enum yy_psr_tkn_max_enum { yy_ptknmax_ = 15 };

    enum yy_psr_numbers_enum {
        SPACES_ = yy_psr_obj::yy_discard_type_,
        yy_eof_ = 0,
        INTEGER_ = 1,
        KURZTEXT_ = 2,
        LANGTEXT_ = 3,
        HEXIDENT_ = 4,
        HEXMCODE_ = 5,
        // "A" = 6,
        // "B" = 7,
        // "C" = 8,
        // "�" = 9,
        // "�" = 10,
        // "�" = 11,
        // "R" = 12,
        // "I" = 13,
        // "K" = 14,
        // "H" = 15,
        yy_error_ = -2,
        HRel_ = 16,
        KRel_ = 17,
        TXRDatei_ = 18,
        TXRType_ = 19,
        TXRSatz_ = 20,
        I_ = 21,
        R_ = 22,
        CS_ = 23,
        BS_ = 24,
        AS_ = 25,
        C_ = 26,
        B_ = 27,
        A_ = 28,
        TXMDatei_ = 29,
        TXMType_ = 30,
        TXMSatz_ = 31,
        TXIDatei_ = 32,
        TXISatz_ = 33
        };

    enum yy_psr_class_enum {
        yy_psr_class_icodedesc_ = 0,
        yy_psr_class_mcodedesc_ = 1,
        yy_psr_class_rcodedesc_ = 2,
        yy_psr_max_class_ = 3
        };

    yy_psr_identsdb_obj(
        yy_lex_ptr      yy_this_lex_obj_ptr,
        int             yy_psr_new_class = yy_psr_dflt_class_,
        int             yy_psr_new_start = yy_psr_dflt_start_,
        int             yy_psr_new_left_max = yy_psr_left_max_,
        int             yy_psr_new_rt_max = yy_psr_rt_max_,
        int             yy_psr_new_rdc_max = yy_psr_rdc_max_
        );

    virtual ~yy_psr_identsdb_obj();

    virtual void yy_psr_do_action(
        int                     yy_psr_action_index
        );


		public:
			typedef set<long, less<long> > MCodeSet;
			bool isMCodeUsed (long lMCode)
			{
				if (!m_fMCodesFilled) {
				ENUMNOKEYLONGEX ENK;

					ENK.eFcn = (ENUMNOKEYLONGEXPROC)FillAllMCodeParserList;
					ENK.ePtr = &m_setMCodes;
					ENK.eData = (MPSystemFeatures|MPAllFeatures);
					DEX_EnumMCodesEx (ENK);		// mit allen MCodes f�llen

					m_fMCodesFilled = true;
				}

			return m_setMCodes.find (lMCode) != m_setMCodes.end();
			}

		private:
			bool m_fMCodesFilled;
			MCodeSet m_setMCodes;		// alle existierenden MerkmalCodes 

		public:
			enum IMPORTMODE {
				IMPORTMODE_OverWrite = 1,	// der neue Eintrag gilt
				IMPORTMODE_KeepEntry = 2,	// der alte Eintrag gilt
				IMPORTMODE_AdjustManually = 3,	// manuell abgleichen
			};
			IMPORTMODE &IMode (void) { return m_rgIMode; }

			enum REJECTMODE {
				REJECTMODE_RejectUnused = 1,	// nur benutzte importieren
				REJECTMODE_ImportAll = 2,	// alle importieren
			};
			REJECTMODE &RMode (void) { return m_rgRMode; }

		// eigentliche ImportFunktionen
			bool WriteTXI (TXISatz *pTXI);
			bool WriteTXM (TXMSatz *pTXM);
			bool WriteTXR (TXRSatz *pTXR);

		// StatusFenster setzen
			void SetStatus (LPPROGRESSINDICATOR pIStatus)
			{
				if (m_pIStatus) m_pIStatus -> Release();
				m_pIStatus = pIStatus;
				if (m_pIStatus) m_pIStatus -> AddRef();
			}
			HRESULT GetStatus (LPPROGRESSINDICATOR *ppIStatus) 
			{ 
				if (m_pIStatus) {
					*ppIStatus = m_pIStatus; 
					m_pIStatus -> AddRef();
					return NOERROR;
				}

			return ResultFromScode (E_FAIL);
			}

		private:
			IMPORTMODE m_rgIMode;	// ImportModus
			REJECTMODE m_rgRMode;	// RejectModus
			LPPROGRESSINDICATOR m_pIStatus;
	
    };  // yy_psr_identsdb_obj

#endif /* yy_psr_identsdb_obj_h_ */
#ifndef yy_inline_TXISatz
#define yy_inline_TXISatz 1
inline int TXISatz::yy_type() { return (yy_this_type); }
inline int TXISatz::yy_num_operands() { return (yy_this_num_operands); }
inline yy_ref_obj &TXISatz::yy_operand(int yy_operand_num) { return (yy_this_operand[yy_operand_num]); }
#endif /* yy_inline_TXISatz */

#ifndef yy_inline_TXMType
#define yy_inline_TXMType 1
inline int TXMType::yy_type() { return (yy_this_type); }
#endif /* yy_inline_TXMType */

#ifndef yy_inline_TXMSatz
#define yy_inline_TXMSatz 1
inline int TXMSatz::yy_type() { return (yy_this_type); }
inline int TXMSatz::yy_num_operands() { return (yy_this_num_operands); }
inline yy_ref_obj &TXMSatz::yy_operand(int yy_operand_num) { return (yy_this_operand[yy_operand_num]); }
#endif /* yy_inline_TXMSatz */

#ifndef yy_inline_TXRType
#define yy_inline_TXRType 1
inline int TXRType::yy_type() { return (yy_this_type); }
#endif /* yy_inline_TXRType */

#ifndef yy_inline_TXRSatz
#define yy_inline_TXRSatz 1
inline int TXRSatz::yy_type() { return (yy_this_type); }
inline int TXRSatz::yy_num_operands() { return (yy_this_num_operands); }
inline yy_ref_obj &TXRSatz::yy_operand(int yy_operand_num) { return (yy_this_operand[yy_operand_num]); }
#endif /* yy_inline_TXRSatz */

#ifndef yy_psr_dflt_obj

#define yy_psr_dflt_obj yy_psr_identsdb_obj

typedef class yy_export yy_psr_dflt_obj       *yy_psr_dflt_ptr;

#endif /* yy_psr_dflt_obj */

