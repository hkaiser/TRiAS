/*
 *
 *	_ p r i n t . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	1.0	sm		Original version
 *
 */
#include "tfrmpre.hxx"

typedef PWind_Imp * pPWind_Imp;

_DLLENTRY PrintingDevice :: PrintingDevice (const char *)
{
	pd_Imp = new PrintingDevice_Imp();
}

BOOL _DLLENTRY PrintingDevice :: SetUp (DVTARGETDEVICE **ppdvt)
{
	return pd_Imp -> Setup (false, ppdvt);
}

BOOL _DLLENTRY PrintingDevice::InitFromDefaultPrinter (DVTARGETDEVICE **ppdvt)
{
	return pd_Imp -> InitFromDefaultPrinter (ppdvt);
}

BOOL _DLLENTRY PrintingDevice::InitFromData (DVTARGETDEVICE *pdvt)
{
	return pd_Imp -> InitFromData (pdvt);
}

_DLLENTRY PrintingDevice :: ~PrintingDevice (void)
{
	delete pd_Imp;
}

BOOL _DLLENTRY PrintingDevice :: isValid (void)
{
	return (pd_Imp ? pd_Imp -> isValid() : false);
}

const char *_DLLENTRY PrintingDevice :: DeviceName (void) { return pd_Imp -> Device(); }
const char *_DLLENTRY PrintingDevice :: DriverName (void) { return pd_Imp -> Driver(); }
const char *_DLLENTRY PrintingDevice :: PortName (void) { return pd_Imp -> Port(); }
const DEVMODE *_DLLENTRY PrintingDevice :: DeviceMode (void) { return (const DEVMODE *)pd_Imp -> InitString(); }

_DLLENTRY Printer :: Printer (const char*jobname, PrintingDevice *device)
{
	if (!device) {
	PrintingDevice pd;
    	
		ec_Imp = (EC_Imp *)new PWind_Imp(this, jobname, CV_RunTime :: pPrDev_to_pImp(&pd));
	} else
		ec_Imp = (EC_Imp *)new PWind_Imp(this, jobname, CV_RunTime :: pPrDev_to_pImp(device));
}


BOOL _DLLENTRY  Printer :: isValid()
{
	return  ((PWind_Imp*)ec_Imp)->Valid() ;
}


void _DLLENTRY Printer :: Idle()
{
	pApp_Imp AppImpInst = _AppImpFind();
	AppImpInst -> Exec(0, ExecWhileEvent);
}

BOOL _DLLENTRY Printer :: PrinterError(PrinterErrorEvt pee)
{
	if (pee.GetErrorType() == PrinterErrorEvt :: NoDiskSpace)
		{
		MessBox mb("TRiAS® Framework: Printer", "Out of disk space", 0);
		mb.SetType(RetryCancel | HandIcon);
		return (mb.Show() == RetryReply);
		}
	else
		return false;
}

PrinterErrorEvt::ErrorType _DLLENTRY PrinterErrorEvt :: GetErrorType()
{
	return (PrinterErrorEvt :: ErrorType) wParam;
}


void _DLLENTRY Printer :: Abort()
{
	((pPWind_Imp)ec_Imp)->Abort();
}

_DLLENTRY Printer :: ~Printer()
{
	 if (ec_Imp)
	 {
		 delete ((pPWind_Imp)ec_Imp);
		 ec_Imp = 0;
	 }
}

BOOL _DLLENTRY Printer :: PrinterExpose(PrinterExposeEvt )
{
	return true;
}

void _DLLENTRY Printer :: Start (void)
{
int pagenum = 1;
int anotherPage = 1;
PrinterExposeEvt e;

// Check if its ok to start printing
	if ( (((pPWind_Imp)ec_Imp) -> Valid()) && 
		!(((pPWind_Imp)ec_Imp) -> Aborted()))
	{
		do {
		Rectangle r;
	
			((pPWind_Imp)ec_Imp)->NewPage();

			r = CanvasRect();
			CV_RunTime :: Event_wParam( e) = pagenum++;
			CV_RunTime :: Event_SetExtra( e, (void*)&r);
			{
			DS_fixup AppFixUp;

				anotherPage = PrinterExpose(e);
			}

			((pPWind_Imp)ec_Imp)->EndPage();
		} while (anotherPage && 
			  (((pPWind_Imp)ec_Imp) -> Valid()) && 
			  !(((pPWind_Imp)ec_Imp) -> Aborted()));
	}
}

void _DLLENTRY Printer :: Start (Range r)
{
	int pagenum = r.Min();
	int anotherPage = 1;
	PrinterExposeEvt e;
	if ( (((pPWind_Imp)ec_Imp) -> Valid()) && 
		!(((pPWind_Imp)ec_Imp) -> Aborted()))
	{
		do {
		Rectangle r;

			((pPWind_Imp)ec_Imp)->NewPage();

			r = CanvasRect();
			CV_RunTime :: Event_wParam( e) = pagenum++;
			CV_RunTime :: Event_SetExtra( e, (void*)&r);
			{
			DS_fixup AppFixUp;

				anotherPage = PrinterExpose(e);
			}
	
			((pPWind_Imp)ec_Imp)->EndPage();
		} while ((anotherPage && (pagenum <= r.Max())) && 
			  (((pPWind_Imp)ec_Imp) -> Valid()) && 
			  !(((pPWind_Imp)ec_Imp) -> Aborted()));
	}
}

HDC _DLLENTRY Printer :: Handle(Service s)
{
	switch (s) {
	case API_WINDOW_TARGETHDC:		// #HK940119
		return (HDC)Window :: Handle (API_WINDOW_TARGETHDC);

	default:
	case API_WINDOW_HDC:
		break;
	}

return (HDC)Window :: Handle (API_WINDOW_HDC);
}


