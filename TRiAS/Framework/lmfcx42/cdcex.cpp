#include	"stdafx.h"

#ifdef LAFX_WINF_SEG
#pragma code_seg(LAFX_WINF_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: cdcex.cpp 1.1 1996/07/12 17:16:31 andy Exp $";
/* $Log: cdcex.cpp $
// Revision 1.1  1996/07/12  17:16:31  andy
// initial version
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

#define new DEBUG_NEW

//////////////////////////////////////////////////////////////////////////

UINT AFX_EXT_API LAfxMergePalette( CPalette* pPalette, COLORREF *pColor, int nColors )
{
	ASSERT_VALID( pPalette );

	PALETTEENTRY	peBuf[128], *pe, *peCurr;
	BOOL	bDynamicField = FALSE;

	if( nColors < 128 )			// nur bei vielen Farben lohnt sich 'new'
		pe = peBuf;
	else
	{
		pe = new PALETTEENTRY[nColors];
		bDynamicField = TRUE;
	}
	peCurr = pe;

	WORD			nOldEntries;
	WORD			nNewEntries = 0;
	int				idx, i;

	pPalette->GetObject( sizeof( nOldEntries ), &nOldEntries );
	for( i = 0; i < nColors; i++ )
	{
		idx = pPalette->GetNearestPaletteIndex( pColor[ i ] );
		pPalette->GetPaletteEntries( idx, 1, peCurr );
		if( peCurr->peRed != GetRValue( pColor[i] )
			|| peCurr->peGreen != GetGValue( pColor[i] )
			|| peCurr->peBlue != GetBValue( pColor[i] ) )
		{
			peCurr->peRed	= GetRValue( pColor[i] );
			peCurr->peGreen	= GetGValue( pColor[i] );
			peCurr->peBlue	= GetBValue( pColor[i] );
			peCurr->peFlags	= NULL;
			peCurr++;
			nNewEntries++;
		}
	}
	if( nNewEntries > 0 )
	{
		if( pPalette->ResizePalette( nNewEntries ) )
			nNewEntries = pPalette->SetPaletteEntries( nOldEntries, 1, pe );
	}
	if( bDynamicField )
		delete pe;

	return nNewEntries;
}
