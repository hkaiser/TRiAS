#include "stdafx.h"

#include "resource.h"
#include "helper.h"

extern CHelper *g_pHelper;
//--------------------------------------------------------------------
//Enumeration nach Ident.("Abhängen"), Hauptmenü

extern "C"
{

BOOL FAR PASCAL _XTENSN_EXPORT EnumObjAbh (long lObjNr, BOOL, void *pAbh)
{
	ASSERT (lObjNr);
	ASSERT (pAbh);

SAbh stAbh = *((SAbh*)pAbh);
OBJSTATISTIK OS;
short OTyp = 0;     
short iFounded;

    if (*stAbh.pGeo != '0')
    { 
	 	memset((void*)&OS, 0, sizeof(OBJSTATISTIK));
	 	OS.dwSize	= sizeof(OBJSTATISTIK);	// Größe dieser Struktur
		OS.lONr		= lObjNr;// ObjektNummer

		if (!DEX_GetObjStatistik(OS)) return FALSE;
// Identifikator kann mehrere OTypen haben, soll jedoch nur der selektierte Identifikator mit
// dessen eigenen OTyp abgehängt werden, Bsp. im Fenster: 0000176890 : F : Wald 
//												          000017.... : P : Wald
		if (*stAbh.pGeo == 'F') OTyp = OGFlaeche;
		else
			if (*stAbh.pGeo == 'P') OTyp = OGPunkt;
			else
				if (*stAbh.pGeo == 'L') OTyp = OGLinie;
		
		if (OS.iObjTyp != OTyp)
			return TRUE;
	}			
                                            
	if (!g_pHelper -> LoeschObjRelat ( lObjNr, stAbh.bLoesch, &iFounded)) return FALSE;

return TRUE;
}
};
