// KeyContext umschalten -- Definition der Datenstrukturen --------------------
// File: SWITCHKC.H

#if !defined(_SWITCHKC_H)
#define _SWITCHKC_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

// ----------------------------------------------------------------------------
// Datenstruktur, welche alle Verbindungsinformationen für eine first/next 
// Schlüsselsuche enthält

#if !defined(MAXLEVEL)
#define MAXLEVEL	20
#endif

typedef struct tagKEYCONTEXT {
	short ikcWorkingFile;
	short ikcFindField;
	long pkcParent[MAXLEVEL];
	short pkcSlots[MAXLEVEL];
	short ikcLevel;
} KEYCONTEXT;

// Funktionsprototypen --------------------------------------------------------
_TRIAS01_ENTRY void FUNCTYPE GetKeyContext (KEYCONTEXT *);
_TRIAS01_ENTRY void FUNCTYPE SetKeyContext (KEYCONTEXT *);

#if defined(__cplusplus)

class CKeyContext :
	public KEYCONTEXT
{
public:
	CKeyContext()
	{
		GetKeyContext (this);
	}
	~CKeyContext()
	{
		SetKeyContext (this);
	}
};

#endif // defined(__cplusplus)

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif

