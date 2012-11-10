///////////////////////////////////////////////////////////////////////////
// @doc 
// @module Minitpbd.hxx | Initialisieren diverser Systemeintraege in einer PBD 

#if !defined(_MINITPBD_HXX__A1F2FA73_B2B2_11D1_85AA_00600875138A__INCLUDED_)
#define _MINITPBD_HXX__A1F2FA73_B2B2_11D1_85AA_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Struktur enthält ResID's für verschiedene PBD-Einträge, die automatisch
// vergeben werden
typedef struct tagINITPBDRESID {
	short iTyp;				// Target und Zugehörigkeit
	unsigned int uiHeaderKey;	// ResID vom HeaderKey
	unsigned int uiKurzText;	// ResID vom KurzText
	unsigned int uiLangText;	// ResID vom LangText
	DWORD dwHdrFlags;			// Flags für HeaderEintrag
	long m_lMCode;				// evtl. zu verwendender MCode
} INITPBDRESID;

#define MITypIdentifikator	0x01
#define MITypMerkmal		0x02
#define MITypRelation		0x04 
#define MITyp				0x07	// Maske für alle

#define MISystemMerkmal		0x08	// systeminternes Merkmal
#define MIReadOnlyMerkmal	0x10	// schreibgeschütztes Merkmal

#define ObjTarget		0x100
#define SichtTarget		0x200
#define IdentTarget		0x400
#define TargetTyp		0x700	// Maske für alle

#endif // !defined(_MINITPBD_HXX__A1F2FA73_B2B2_11D1_85AA_00600875138A__INCLUDED_)
