/*
 *
 *	_ b p r i n t . c x x
 *
 */
#include "tfrmpre.hxx"

typedef PWind_Imp * pPWind_Imp;
typedef BPWind_Imp * pBPWind_Imp;

_DLLENTRY BandingPrinter :: BandingPrinter (const char *jobname, 
					    PrintingDevice *device)
			  : Printer (jobname, device)
{
	// nothing to do
}


_DLLENTRY BandingPrinter :: ~BandingPrinter (void)
{
	// nothing to do
}

BOOL _DLLENTRY BandingPrinter :: PrinterExpose (PrinterExposeEvt)
{
	return TRUE;
}

void _DLLENTRY BandingPrinter :: StartBanding (void)
{
int pagenum = 1;
int anotherPage = 1;
PrinterExposeEvt e;
Rectangle RcC = CanvasRect();
CoOrd iHeight = RcC.Top() - RcC.Bottom();

// Check if its ok to start printing
	if ( (((pPWind_Imp)ec_Imp) -> Valid()) && 
	     !(((pPWind_Imp)ec_Imp) -> Aborted()))
	{
		do {
		Rectangle r;

		// erstes Band anfordern, ruft StartPage
			((pBPWind_Imp)ec_Imp) -> NextBand (r, true);

			while (!IsRectEmpty ((RECT *)&r) && 
			       !(((pPWind_Imp)ec_Imp) -> Aborted())) 
			{
			// ExposeEvent verschicken
				r.Top() = iHeight - r.Top();
				r.Bottom() = iHeight - r.Bottom();

				CV_RunTime :: Event_wParam (e) = pagenum++;
				CV_RunTime :: Event_SetExtra (e, (void*)&r);
				{
				DS_fixup AppFixUp;

					anotherPage = PrinterExpose (e);
				}

			// nächstes Band anfordern
				((pBPWind_Imp)ec_Imp) -> NextBand (r);
			}
			
			((pBPWind_Imp)ec_Imp) -> EndPage();

		} while (anotherPage && 
			(((pPWind_Imp)ec_Imp) -> Valid()) && 
			!(((pPWind_Imp)ec_Imp) -> Aborted()) 
		      );
	}
}

void _DLLENTRY BandingPrinter :: StartBanding (Range r)
{
int pagenum = r.Min();
int anotherPage = 1;
PrinterExposeEvt e;
Rectangle RcC = CanvasRect();
CoOrd iHeight = RcC.Top() - RcC.Bottom();

	if ( (((pPWind_Imp)ec_Imp) -> Valid()) && 
	     !(((pPWind_Imp)ec_Imp) -> Aborted())) 
	{
		do {
		Rectangle r;

		// erstes Band anfordern, ruft StartPage
			((pBPWind_Imp)ec_Imp) -> NextBand (r, true);

			while (!IsRectEmpty ((RECT *)&r) && 
			       !(((pPWind_Imp)ec_Imp) -> Aborted())) 
			{
			// ExposeEvent verschicken
				r.Top() = iHeight - r.Top();
				r.Bottom() = iHeight - r.Bottom();

				CV_RunTime :: Event_wParam (e) = pagenum++;
				CV_RunTime :: Event_SetExtra (e, (void*)&r);
				{
				DS_fixup AppFixUp;

					anotherPage = PrinterExpose(e);
				}

			// nächstes Band anfordern
				((pBPWind_Imp)ec_Imp) -> NextBand (r);
			}

			((pBPWind_Imp)ec_Imp) -> EndPage();

		} while ((anotherPage && (pagenum <= r.Max())) && 
			(((pPWind_Imp)ec_Imp) -> Valid()) && 
			!(((pPWind_Imp)ec_Imp) -> Aborted())
		      );
	}
}

