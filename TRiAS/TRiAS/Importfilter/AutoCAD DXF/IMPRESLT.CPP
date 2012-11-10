// Fenster, welches das ImportErgebnis anzeigt.
// File: IMPRESLT.CPP

#include "pheader.hpp"

extern "C"{
	#include <stdlib.h>           	// ultoa ()
}

#include "optparam.hpp"          	// Params
#include "impreslt.hpp"          	// zugeh. Header

//  externe Variablen
extern Params OptParams;          	// Parameter-Feld

#pragma warning (disable:4355)

ImportResult :: ImportResult (pWindow pW, ResourceFile *pRF, DWORD dwParseTime)
	      	  : DialogWindow (pW, ResID (IDD_IMPORTRESULT, pRF)),
TextCnt (this, ResID (IDT_TEXTCNT, pRF)),
LineCnt (this, ResID (IDT_LINCNT, pRF)),
PointCnt (this, ResID (IDT_PKTCNT, pRF)),
AreaCnt (this, ResID (IDT_FLCNT, pRF)),
SumCnt (this, ResID (IDT_SUMME, pRF)),
TimeText (this, ResID (IDT_IMPORTTIME, pRF)),
BugImported (this, ResID (IDT_GEO_ERROR, pRF)),
NotImported (this, ResID (IDT_NOTIMPORTED, pRF))
{
	char Buffer [80] = "";
    TextCnt.SetText (ultoa (OptParams.TextCnt, Buffer, 10));
	LineCnt.SetText (ultoa (OptParams.LineCnt, Buffer, 10));
	PointCnt.SetText (ultoa (OptParams.PointCnt, Buffer, 10));
	AreaCnt.SetText (ultoa (OptParams.AreaCnt, Buffer, 10));
	BugImported.SetText (ultoa (OptParams.BugImported, Buffer, 10));	
	ulong Summe = OptParams.TextCnt + OptParams.LineCnt + 
				  OptParams.AreaCnt + OptParams.PointCnt + OptParams.BugImported;

	SumCnt.SetText (ultoa (Summe, Buffer, 10));              
	NotImported.SetText (ultoa (OptParams.NotImported, Buffer, 10));
	
//	Übersetzungszeit ausgeben                      
	dwParseTime /= 1000;		// in Sekunden konvertieren       
	wsprintf (Buffer, "%02d:%02d:%02d", (short) (dwParseTime / 3600),
									    (short) ((dwParseTime % 3600) / 60),
										(short) ((dwParseTime % 3600) % 60));
	TimeText.SetText (Buffer);									    	

	ResString Caption (ResID (IDS_RESULTCAPT, pRF), 40);
	// wsprintf (Buffer, Caption.Addr (), OptParams.pFileName);
	SetCaption (Caption.Addr ());
}
                              
#pragma warning (default:4355)                              
