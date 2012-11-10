// myhelper.cpp
// Autor   : JG
// Erstelt : 990310

#include "pheader.h"
#include "myhelper.h"

//forwards
extern "C"  BOOL PASCAL _XTENSN_EXPORT SucheDatenQuellen (char *pName, Bool , void *pData);

//helpers
bool InvalidIdent(ulong id)
{
	return ((id == 0) || (id == -1));
}

HRESULT EnumAllProjects(list<HPROJECT>& cont)	//JG enumeriert alle Datenquellen
{
	ENUMNOKEY EN;
//	Bestimmen der Anzahl der Datenquellen

	EN.eFcn = ( ENUMNOKEYPROC) SucheDatenQuellen;
	EN.ePtr = &cont;
	DEX_EnumDataSources(EN);

	return true;
}

//---------------------------------------------------------------------

extern "C"  BOOL PASCAL _XTENSN_EXPORT SucheDatenQuellen (char *pName, Bool , void *pData)
{
	if (NULL == pData)
		return TRUE;
	
#if _MSC_VER >= 1100
	
	list<HPROJECT>& handlelist = *(list<HPROJECT>*) pData;
	HPROJECT hPr = DEX_GetDataSourceHandleEx(pName);
	handlelist.push_back(hPr);

/*	TX_ASSERT(NULL != hPr);
	if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {

		// Ident am jeweiligen Item speichern
		int iIndex = ((ListBox *)pData) -> AddString (cbBuffer);

	}*/
#endif

	return TRUE;

}
