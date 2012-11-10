// Fenster, welches das ImportErgebnis anzeigt.
// File: IMPRESLT.CXX

#include "pheader.h"

#include "arctrias.hr"                   // Resourcen-Defines
#define NOOPTPARAM
#include "optparam.hxx"          	// Params
#include "impreslt.hxx"          	// zugeh. Header

//  externe Variablen
extern Params *pParams;          	// Parameter-Feld

#pragma warning (disable:4355)

ImportResult :: ImportResult (pWindow pW, ResourceFile *pRF, DWORD dwParseTime,
							  char *pCoverName)
	      	  : DialogWindow (pW, ResID (IDD_IMPORTRESULT, pRF)),
TextCnt (this, ResID (IDT_TEXTCNT, pRF)),
LineCnt (this, ResID (IDT_LINCNT, pRF)),
PointCnt (this, ResID (IDT_PKTCNT, pRF)),
AreaCnt (this, ResID (IDT_FLCNT, pRF)),
SumCnt (this, ResID (IDT_SUMME, pRF)),
TimeText (this, ResID (IDT_IMPORTTIME, pRF)),
ReducedImported (this, ResID (IDT_REDIMPORTED, pRF)),
BugImported (this, ResID (IDT_GEO_ERROR, pRF)),
NotImported (this, ResID (IDT_NOTIMPORTED, pRF)),    
TableCnt (this, ResID (IDT_TABLECNT, pRF))  
{
	char Buffer [40] = "";
     
	TableCnt.SetText (ltoa (pParams -> TableCnt, Buffer, 10));     
	TextCnt.SetText (ltoa (pParams -> TextCnt, Buffer, 10));
	LineCnt.SetText (ltoa (pParams -> LineCnt, Buffer, 10));
	PointCnt.SetText (ltoa (pParams -> PointCnt, Buffer, 10));
	AreaCnt.SetText (ltoa (pParams -> AreaCnt, Buffer, 10));
	BugImported.SetText (ltoa (pParams -> BugCnt, Buffer, 10));	
	long Summe = pParams -> TextCnt + pParams -> LineCnt + pParams -> TableCnt + 
				 pParams -> AreaCnt + pParams -> PointCnt + pParams -> SubImported +
				 pParams -> BugCnt;

	SumCnt.SetText (ltoa (Summe, Buffer, 10));              
	NotImported.SetText (ltoa (pParams -> NotImported, Buffer, 10));
	ReducedImported.SetText (ltoa (pParams -> SubImported, Buffer, 10));	
	
//	Übersetzungszeit ausgeben                      
	dwParseTime /= 1000;		// in Sekunden konvertieren       
	wsprintf (Buffer, "%02d:%02d:%02d", (short) (dwParseTime / 3600),
									    (short) ((dwParseTime % 3600) / 60),
										(short) ((dwParseTime % 3600) % 60));
	TimeText.SetText (Buffer);									    	

	if (pCoverName)
	{
		ResString Caption (ResID (IDS_RESULTCAPT, pRF), 30);
		wsprintf (Buffer, Caption.Addr (), pCoverName);
		SetCaption (Buffer);
	}
}
                              
#pragma warning (default:4355)                              
