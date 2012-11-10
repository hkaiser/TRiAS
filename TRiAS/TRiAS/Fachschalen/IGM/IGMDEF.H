// Konstantendefinitionen für ErweiterungsRessourcen
// File: IGMDEF.H

#if !defined(_IGMDEF_H)
#define _IGMDEF_H

///////////////////////////////////////////////////////////////////////////

#include <pshpack1.h>

#define FK_SOURCE	2000

#define TK_INFER	1

#define TK_INFOR	9

#define		TKT _SYSTEMTIME 
typedef TKT *lpT;

#define GetSys(lpT )       GetLocalTime(lpT )
#define TEFAL CKIOPTION_KOMPAKT

void TeSys(void);
WORD * ToSys(void *);

//------------------------------------------------------------
//------------------------------------------------------------
void TeSys(void)
{
    lpT lp = new TKT;

	GetSys(lp);

	WORD * pE = ToSys(lp);

	if ( *pE >= FK_SOURCE+TK_INFER  && *(pE+1) >= TK_INFOR ) {
		((CKompiasExtension *)g_pTE)->SetWork();
		((CKompiasExtension *)g_pTE)->SetActive();
	}

}

///////////////////////////////////////////////////////////////////////

WORD * ToSys(void *ll) {

	return (WORD *)ll;

}



#include <poppack.h>

///////////////////////////////////////////////////////////////////////////

#endif 	// _IGMDEF_H
