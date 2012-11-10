#ifndef _L_OCROCX_H
#define _L_OCROCX_H
// Lead OCR definition constants
      #define OCR_MAX_REGIONS                 256
      #define DOCDEF_MAX_STRING               60

// enumeration constants
		enum  RecognitionOptionConstants{
				OCROPT_LANGUAGE			 = 0,
   			OCROPT_LEXICON				 = 1,
   			OCROPT_TRAINING			 = 2,
   			OCROPT_PP_MODE				 = 3, 
   			OCROPT_RECOGNITION_MODE		 = 4,
   			OCROPT_VERIFIER_MODE			 = 5,
   			OCROPT_VERIFIER_THRESHOLD	 = 6,
   			OCROPT_MIN_POINT_SIZE		 = 7,
   			OCROPT_MAX_POINT_SIZE		 = 8,
   			OCROPT_DOCUMENT_NAME			 = 9,        
   			OCROPT_QUESTIONABLE			 = 10,         
   			OCROPT_UNRECOGNIZED			 = 11,         
   			OCROPT_LEFT_SINGLE_QUOTE	 = 12, 
   			OCROPT_RIGHT_SINGLE_QUOTE	 = 13,   
   			OCROPT_LEFT_DOUBLE_QUOTE	 = 14,    
   			OCROPT_RIGHT_DOUBLE_QUOTE	 = 15,   
   			OCROPT_DECIMAL				    = 16,
   			OCROPT_THOUSANDS				 = 17,            
   			OCROPT_HEADER_FOOTER_PROCESS  = 18,
   			OCROPT_SLOPPY_MANUAL			 = 19,
   			OCROPT_TEXT_ORIENT_LIMIT    = 20,    
		};

		 enum PreprocessingModeConstants{
   			OCRPP_NONE               = 0x00000000,
   			OCRPP_DOT_MATRIX         = 0x00000001,  
   			OCRPP_REMOVE_HALFTONES   = 0x00000002,  
   			OCRPP_AUTO_SEGMENTATION  = 0x00000008,  
   			OCRPP_FAX                = 0x00000400,  
   			OCRPP_NEWS_PAPER         = 0x00000800,  
   			OCRPP_ORIENTATION        = 0x00004000,  
   			OCRPP_SKEW               = 0x00008000,  
   			OCRPP_DOT_MATRIX_DETECT  = 0x00020000,  
   			OCRPP_AUTO_SET_DEGRADE   = 0x00080000,  
   			OCRPP_AUTO_FAX           = 0x00100000,  
   			OCRPP_TEXT_ORIENTATION   = 0x40000000,  
		};

#define OCRPP_FULL_ORIENTATION (OCRPP_ORIENTATION |\
                                OCRPP_TEXT_ORIENTATION)  

#define OCRPP_DO_RIGHT (OCRPP_DOT_MATRIX_DETECT |\
                        OCRPP_AUTO_SEGMENTATION |\
                        OCRPP_ORIENTATION |\
                        OCRPP_TEXT_ORIENTATION |\
                        OCRPP_SKEW |\
                        OCRPP_AUTO_FAX)

		enum RecognitionModeConstants{
		      OCRREC_STANDARD = 0,
		      OCRREC_DEGRADED = 1,
		      OCRREC_UNKNOWN  = 2, 
		};

		enum VerifierModeConstants{
				OCRVER_NONE = 0,
				OCRVER_CHAR = 1,
				OCRVER_WORD = 2, 
		};

		enum LanguageConstants{
				OCRLNG_ENGLISH                = 0x00000001,
				OCRLNG_GERMAN                 = 0x00000002,
				OCRLNG_FRENCH                 = 0x00000004,
				OCRLNG_SPANISH                = 0x00000008,
				OCRLNG_ITALIAN                = 0x00000010,
				OCRLNG_DUTCH                  = 0x00000020,
				OCRLNG_SWEDISH                = 0x00000040,
				OCRLNG_NORWEGIAN              = 0x00000080,
				OCRLNG_FINNISH                = 0x00000100,
				OCRLNG_DANISH                 = 0x00000200,
				OCRLNG_PORTUGUESE             = 0x00000400,
				OCRLNG_RUSSIAN                = 0x00001000,
				OCRLNG_ENGLISH_GERMAN         = 0x00002000,
				OCRLNG_ENGLISH_FRENCH         = 0x00004000,
				OCRLNG_ENGLISH_SPANISH        = 0x00008000,
				OCRLNG_ENGLISH_ITALIAN        = 0x00010000,
				OCRLNG_GERMAN_FRENCH          = 0x00020000,
				OCRLNG_GERMAN_SPANISH         = 0x00040000,
				OCRLNG_GERMAN_ITALIAN         = 0x00080000,
				OCRLNG_FRENCH_SPANISH         = 0x00100000,
				OCRLNG_FRENCH_ITALIAN         = 0x00200000,
				OCRLNG_ITALIAN_SPANISH        = 0x00400000,
				OCRLNG_FRENCH_ITALIAN_GERMAN  = 0x00800000,
				OCRLNG_SPANISH_PORTUGUESE     = 0x01000000,
				OCRLNG_FRENCH_DUTCH           = 0x02000000,
				OCRLNG_SM_ENGLISH             = 0x04000000,
				OCRLNG_SM_FRENCH              = 0x08000000,
				OCRLNG_SM_ITALIAN             = 0x10000000,
				OCRLNG_SM_GERMAN              = 0x20000000,
				OCRLNG_SM_SPANISH             = 0x40000000,
		};

		enum RecognizeFlagConstants{
				OCRFLAG_NONE          = 0x0000,
				OCRFLAG_CALLBACK_AUTO = 0x0001,
		};

		enum StatusRecognizeEventConstants{
				OCRCMD_ACCEPT_GROUP         = 0,
				OCRCMD_ACCEPT_WORD			 = 1,
				OCRCMD_ACCEPT_WORD_LEXICON	 = 2,
				OCRCMD_ACCEPT_WORD_NOTRAINING = 3,
				OCRCMD_JOIN_LEFT				 = 4,
				OCRCMD_JOIN_RIGHT			    = 5,
				OCRCMD_MOVE_LEFT				 = 6,
				OCRCMD_MOVE_RIGHT		   	 = 7,
				OCRCMD_UNDO					    = 8,
				OCRCMD_SKIP					    = 9,
				OCRCMD_CANCEL				    = 10,
		};

		enum StatusRecognizeConstants{
				OCRSTATUS_PREPROCESS  = 0,
				OCRSTATUS_RECOGNIZE   = 1,
				OCRSTATUS_QUESTION    = 2,
				OCRSTATUS_ERROR       = 3,
				OCRSTATUS_POSTPROCESS = 4,
		};

		enum CharMaskConstants{
				OCRCHAR_BEGIN_GROUP   = 0x08,
				OCRCHAR_CURRENT_GROUP = 0x04,
				OCRCHAR_QUESTIONABLY  = 0x02,
				OCRCHAR_CURRENT_WORD  = 0x01,
		};

		enum ZoneTypeConstants{
				OCRZONE_TYPE_ANY 			= 0x0000,
				OCRZONE_TYPE_IGNORE     = 0x0001,
				OCRZONE_TYPE_TEXT			= 0x0002,
				OCRZONE_TYPE_IMAGE     	= 0x0004,
				OCRZONE_TYPE_VERTICAL_RULE   = 0x0008,
				OCRZONE_TYPE_HORIZONTAL_RULE	= 0x0010,
		};

		enum ZoneSubtypeConstants{
				OCRZONE_SUBTYPE_UNFLAVORED = 0x0000,
				OCRZONE_SUBTYPE_TABLE	  = 0x0100,
				OCRZONE_SUBTYPE_CELLTABLE  = 0x0200,
				OCRZONE_SUBTYPE_CELL		  = 0x0400,
				OCRZONE_SUBTYPE_HEADLINE	  = 0x0800,
		};

		enum ZoneLexiconModeConstants{
				OCRLEX_NO_LEXICAL = 0,
				OCRLEX_PREFERENCE = 1,
				OCRLEX_ABSOLUTE   = 2,
		};

		enum ZoneLexiconClassConstants{
				ICRLXFLG_NOCLASS				= 0x00000000,
				ICRLXFLG_MAINLEX				= 0x00000001,
				ICRLXFLG_NUMBER				= 0x00000002,
				ICRLXFLG_ROMAN_NUMERAL		= 0x00000004,
				ICRLXFLG_DATE				   = 0x00000008,
				ICRLXFLG_TIME				   = 0x00000010,
				ICRLXFLG_MONEY				   = 0x00000020,
				ICRLXFLG_ID_NUMBER			= 0x00000040,
				ICRLXFLG_TELEPHONE_NUMBER 	= 0x00000080,
				ICRLXFLG_TERMINAL_DOT		= 0x00000100,
				ICRLXFLG_NAME        		= 0x00000200,
				ICRLXFLG_STREET_NAME       = 0x00000400,
				ICRLXFLG_STREET_TYPE 		= 0x00000800,
				ICRLXFLG_CITY        		= 0x00001000,
				ICRLXFLG_STATE_PROV  		= 0x00002000,
				ICRLXFLG_COUNTRY     		= 0x00004000,
				ICRLXFLG_POSTAL_CODE 		= 0x00008000,
				ICRLXFLG_URL         		= 0x00010000,
				ICRLXFLG_EMAIL       		= 0x00020000,
				ICRLXFLG_MIXEDTYPES   	   = 0x00040000,
				ICRLXFLG_USER1				   = 0x00000001,
				ICRLXFLG_USER2				   = 0x00000002,
				ICRLXFLG_USER3				   = 0x00000004,
				ICRLXFLG_USER4				   = 0x00000008,
				ICRLXFLG_USER5				   = 0x00000010,
				ICRLXFLG_USER6				   = 0x00000020,
				ICRLXFLG_USER7				   = 0x00000040,
				ICRLXFLG_USER8				   = 0x00000080,
				ICRLXFLG_USER9				   = 0x00000100,
				ICRLXFLG_USER10			   = 0x00000200,
				ICRLXFLG_USER11			   = 0x00000400,
				ICRLXFLG_USER12			   = 0x00000800,
				ICRLXFLG_USER13			   = 0x00001000,
				ICRLXFLG_USER14			   = 0x00002000,
				ICRLXFLG_USER15			   = 0x00004000,
				ICRLXFLG_USER16			   = 0x00008000,
				ICRLXFLG_USER17			   = 0x00010000,
				ICRLXFLG_USER18			   = 0x00020000,
				ICRLXFLG_USER19			   = 0x00040000,
				ICRLXFLG_USER20			   = 0x00080000,
				ICRLXFLG_USER21			   = 0x00100000,
				ICRLXFLG_USER22			   = 0x00200000,
				ICRLXFLG_USER23			   = 0x00400000,
				ICRLXFLG_USER24			   = 0x00800000,
				ICRLXFLG_USER25			   = 0x01000000,
				ICRLXFLG_USER26			   = 0x02000000,
				ICRLXFLG_USER27			   = 0x04000000,
				ICRLXFLG_USER28			   = 0x08000000,
				ICRLXFLG_USER29			   = 0x10000000,
				ICRLXFLG_USER30			   = 0x20000000,
		};

		enum DocZoneTypeConstants{
				DOCZONE_IMAGE   = 0,
				DOCZONE_TEXT    = 1,
				DOCZONE_TABLE   = 2,
		};

// ActiveX error codes 
#include "L_OcxErr.h"

      enum  OcrFileFormatConstants{
            FILE_AMI_PRO_20              = 200,
            FILE_AMI_PRO_30              = 201,
            FILE_ASCII_SMART             = 202,
            FILE_ASCII_STANDARD          = 203,
            FILE_ASCII_STANDARD_DOS      = 204,
            FILE_ASCII_STRIPPED          = 205,
            FILE_DBASE_IV_10             = 206,
            FILE_DCA_RFT                 = 207,
            FILE_DCA_RFT_DW_5            = 208,
            FILE_EXCEL_MAC               = 209,
            FILE_EXCEL_30                = 210,
            FILE_EXCEL_40                = 211,
            FILE_EXCEL_50                = 212,
            FILE_EXCEL_OFFICE97          = 213,
            FILE_FRAMEMAKER              = 214,
            FILE_HTML_20                 = 215,
            FILE_HTML_EDITOR_20          = 216,
            FILE_HTML_NETSCAPE_20        = 217,
            FILE_INTERLEAF               = 218,
            FILE_LOTUS123                = 219,
            FILE_LOTUS_WORD_PRO          = 220,
            FILE_MULTIMATE_ADV_II        = 221,
            FILE_POSTSCRIPT              = 222,
            FILE_PROFESSIONAL_WRITE_20   = 223,
            FILE_PROFESSIONAL_WRITE_22   = 224,
            FILE_QUATTRA_PRO             = 225,
            FILE_RTF                     = 226,
            FILE_RTF_MAC                 = 227,
            FILE_RTF_WORD_60             = 228,
            FILE_WINDOWS_WRITE           = 229,
            FILE_WORD_WINDOWS_2X         = 230,
            FILE_WORD_WINDOWS_60         = 231,
            FILE_WORD_OFFICE97           = 232,
            FILE_WORDPERFECT_DOS_42      = 233,
            FILE_WORDPERFECT_WINDOWS     = 234,
            FILE_WORDPERFECT_WINDOWS_60  = 235,
            FILE_WORDPERFECT_WINDOWS_61  = 236,
            FILE_WORDPERFECT_WINDOWS_7X  = 237,
            FILE_WORDSTAR_WINDOWS_1X     = 238,
            FILE_WORKS                   = 239,
            FILE_XDOC                    = 240,
		};

#include "ltlck_.h"

#endif
