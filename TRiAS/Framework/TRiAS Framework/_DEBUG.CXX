/* $Header:   G:/cv.win/pvcs/commonvu/src/_debug.cxv   1.12.1.0   14 Jul 1992 11:49:08   RONAN  $
 *
 *	_ D E B U G . C X X
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *  1.0	rs		25jan90	First Cut
 */

#include "tfrmpre.hxx"

#if defined(_DEBUG)

// ZORTECH
// prevent NULL re-definition
#ifdef __ZTC__
#undef NULL
#endif

START_C_FUNCTIONS
#include 	<stdarg.h>
#include 	<stdlib.h>
#include 	<string.h>
#include 	<sys\types.h>
END_C_FUNCTIONS

 /* ======================================================================= */
 /*    Debugging declarations                                               */
 /* ======================================================================= */

/* general definitions */

#define SIZENEAR	1
#define SIZEFAR		2

 /* ======================================================================= */
 /*    End of Debugging code                                                */
 /* ======================================================================= */

#ifdef MSCC8
#define LTOA _ltoa
#define ITOA _itoa
#else
#define LTOA ltoa
#define ITOA itoa
#endif

START_C_FUNCTIONS
#if !defined(MSCC8)
extern char * cdecl LTOA(long, char *, int);
extern char * cdecl ITOA(int, char *, int);
#endif
HINSTANCE WINAPI CV_LibHandle();
END_C_FUNCTIONS

 /* ======================================================================= */
 /*    Debugging code                                                       */
 /* ======================================================================= */

static int Outnum( pchar buff, long num, int radix)
{
	int count = 0;
	if (!num)
		{
		*buff++ = '0';
		return 1;
		}

	LTOA(num,(char*) buff, radix);
	while (*buff++)
		count ++;
	return count;
}

static int   OutInum( pchar buff, int num, int radix)
{
	int count = 0;
	if (!num)
		{
		*buff++ = '0';
		return 1;
		}

	ITOA(num,(char*) buff, radix);
	while (*buff++)
		count ++;
	return count;
}

static int   Outstr( pchar buff, pchar str)
{
	int count = 0;
	while (*str)
		{
		*buff++ = *str++;
		count ++;
		}
	return count;
}

static int   CVsprintf1( pchar buffer, pchar format, va_list arg_ptr)
{
	char ResFormat[128];
	App_Imp* AppImpInst = _AppImpFind();
	int count = 0;
	if (((long) format) < 30000) 
		{
		int id = (int)(long)format;
		if (!LoadString ( AppImpInst -> Handle(), id, ResFormat, 127 ))
			format = 0;
		else
			format = (pchar)ResFormat; 
		}
		
	if (format)
		{
		while (*format)
		{
		if (*format == '%')
			{
			char LibString[128];
			int size = 0;
			int radix = 16;
			int c = 0;
			pchar s;
			long l;
			format++;
			if ((*format == 'l') || (*format == 'L'))
				{
				size = 1;
				format++;
				}
			else
				size = 0;
			if (*format)
				{
				char ch = *format++;

				switch (ch) {
				case 'c':
					*buffer++ = (char)va_arg(arg_ptr, char);
					break;

				case 'r':
					{
					int id = va_arg(arg_ptr,int);
					if (!(c = LoadString ( AppImpInst -> Handle(), id, LibString, 128 )))
						{
						*buffer++ = '?';
						count++;
						break;
						}
					count += (c = Outstr(buffer, LibString));
					buffer +=c;
					break;
					}

				case 'm':	// message number
					{
					int id = va_arg(arg_ptr,int);
					if (((id > 0x400) || 
						(!(c = LoadString ( CV_LibHandle(), id, LibString, 128 ))))
						&& !(c = LoadString ( CV_LibHandle(), 0x3ff, LibString, 128 )))
							{
							*buffer++ = '?';
							count++;
							break;
							}
					count += (c = Outstr(buffer, LibString));
					buffer +=c;
					break;
					}

				case 's':	// string
					{
					// always assume  strings far in portable model
					s = (pchar)va_arg(arg_ptr, pchar);
					if (s)
						{
						count += (c = Outstr(buffer, s));
						buffer +=c;
						}
					break;
					}

				case 'p':	// pointer
					{	    // Always large in portable model
					int i = (int)va_arg(arg_ptr, int);
					int j = (int)va_arg(arg_ptr, int);

					count += ( c = wsprintf(buffer, "%.1x:%.1x", i, j));
					buffer +=c;
					break;
				 	}		

				case 'u': // decimal
				case 'd': // decimal
				case 'i': // decimal
						radix = 10;
				case 'x':	// hexadecimal 
				case 'X':	// hexadecimal 
					{
					if (size)
						{
						l = (long)va_arg(arg_ptr, long);
						count += (c = Outnum(buffer, l, radix));
						}
					else
						{
						count += (c = OutInum(buffer,(int)va_arg(arg_ptr, int), radix));
						}
					buffer +=c;
					break;
					}

				default:	
					*buffer = ch;
					buffer ++;
					count ++;
					}
				}
			}	// end of "%?"
			else
			while ((*format) && (*format != '%'))
				{
				 *buffer++ = *format++;
				 count ++;
				 }
		}
	}
	*buffer = '\0';
	return ++count;
}



/*
 * CVDebug( wCategory, Params ParmList) : bool FAR
 *
 *		wCategory		debug message classification
 *		ParmList		debug parameter list
 *
 * This function outputs a formatted message to the debug
 * utility routines.  The wCategory variable determines 
 * how the message is filtered.  The ParmList is a standard
 * printf parameter list.  A value of true is returned if
 * the message was successfully processed and not filtered.
 *
 * Note that this function CANNOT be declared of type
 * PASCAL as it uses a variable number of arguments!  Also
 * note that alternative methods are available for handling
 * a variable number of function parameters.
 *
 */
 
void  _DLLENTRY CVDebug (DebugTypes wCategory, pchar fmt, ...)
{
	/* local variables */
	char		szStatement[132];	// temporary statement 
	va_list		arg_marker;

	/* initialization */
	va_start(arg_marker, fmt);

	/* process statement if debug active */
	if (  CVDebugOptions() -> DebugFlag  ) {
		switch (wCategory)		{
			case CVD_DebugOn:
				CVDebugOptions() -> TmpFlag = 1;
				break;

			case CVD_DebugOff:
				CVDebugOptions() -> TmpFlag = 0;
				break;

			case CVD_Always:
				break;

			case CVD_Debug:
				if (!CVDebugOptions() -> TmpFlag)
					return;
				break;

			default:
				return;
		}

		if (! fmt)
			return;
		
		/* define debug statement */
		CVsprintf1( szStatement,  fmt, arg_marker );
		OutputDebugString(  szStatement );
		OutputDebugString(  "\n\r");
		} 
}	

#if defined(__ZTC__)
uint _loadds GetDLLDS() 
{
	return _getDS();
}
#endif

static void OutputName(Wind_Imp *pw, uint ename)
{
char buffer[180];
char EvtName[40];

	if ((ename > CVEVT_Last) || 
			(!LoadString ( CV_LibHandle(), ename + 0x0500, EvtName, 39 )) )
		LoadString( CV_LibHandle(), CVEVT_UnknownEvt, EvtName, 39 );

	if ((Options.Tracking & CVTRACK_NAMES) && (CV_RunTime :: Window_Capt(pw)))
		wsprintf(buffer, "[%#.1x,%-10.40s] %s  ", CV_RunTime :: Handle(pw),
			 CV_RunTime :: Window_Capt(pw), EvtName);
	else
		wsprintf(buffer, "[%#.1x] %s  ", CV_RunTime :: Handle(pw), EvtName);
	OutputDebugString(buffer);
}

void CVReport(Wind_Imp * pw, uint ename, Event e)
{
char buffer[180];
bool update = 0;

	buffer[0] = '\0';

	switch (ename) {
	case CVEVT_WindowInit:
	case CVEVT_MenuInit:
		if (Options.Tracking & CVTRACK_INIT)
			update = true;
		break;
		
	case CVEVT_MouseButtonDn:
	case CVEVT_MouseButtonUp:
	case CVEVT_MouseButtonDblClk:
	case CVEVT_MouseMove:
	case CVEVT_MouseDrag:
		{
		if (Options.Tracking & CVTRACK_MOUSE)
			{
			MouseEvt &k = (MouseEvt&)e;
			update = true;
			if (ename != CVEVT_MouseMove)
			wsprintf(buffer, "<%s%s%s%s%s> At (%d, %d)", 
				(k.isLeftButton() ? "Left " : ""), 
				(k.isRightButton() ? "Right " : ""), 
				(k.isMiddleButton() ? "Middle " : ""), 
				(k.isShiftButton() ? "Shift " : ""), 
				(k.isControlButton() ? "Control " : ""), 
				k.Where().X(), k.Where().Y()); 
			else
				wsprintf(buffer, "At (%d, %d)", 
					k.Where().X(), k.Where().Y()); 
			}
		}
		break;
			
	case CVEVT_KeyDown:
	case CVEVT_KeyUp:
		{
		if (Options.Tracking & CVTRACK_INPUT)
		{
		char ch;
		KeyEvt &k = (KeyEvt &)e;

			update = true;
			wsprintf(buffer, "%s\"%c\"  - Keycode : %u",
 						(k.isSystem() ? "<System>  " : ""),
						(((ch = k.ASCIIChar()) && ( ch < 128)) ? ch : '?'),
						k.Keycode());
			}
		}
		break;
			   
	case CVEVT_Help:
		{
		if (Options.Tracking & CVTRACK_WINDOWS)
			{
			HelpRequestEvt &k = (HelpRequestEvt&)e;
			if (k.RequestType() == HelpWindow)
				{
				char AreaName [40];
				int wa = (int) k.GetWindowArea();
				if ((wa >= 8) || 
					(!LoadString ( CV_LibHandle(), wa + 0x0700, AreaName, 39 )) )
				LoadString( CV_LibHandle(), 0x0708, AreaName, 39 );
				wsprintf(buffer, "[HelpWindow] (%s)", AreaName);
				}
			else
				{
				char RequestName [40];
				int wa = (int) k.RequestType();
				if ((wa >= 3) || 
					(!LoadString ( CV_LibHandle(), wa + 0x0710, RequestName, 39 )) )
				LoadString( CV_LibHandle(), 0x0713, RequestName, 39 );
				wsprintf(buffer, "(%s)", RequestName);
				}
			update = true;
			}
		break;
		}
	
	case CVEVT_Activate:
	case CVEVT_DeActivate:
		if (Options.Tracking & CVTRACK_WINDOWS)
			update = true;
		break;
		
	case CVEVT_FocusChange:
		{
		if (Options.Tracking & CVTRACK_WINDOWS)
			{
			FocusChangeEvt &k = (FocusChangeEvt&)e;
			wsprintf(buffer, "(%s)",
					(k.gotFocus() ? "Received Focus" : "LostFocus"));
			update = true;
			}
		}
		break;
		
	case CVEVT_ReSize:
		{
		if (Options.Tracking & CVTRACK_WINDOWS)
			{
			ReSizeEvt &k = (ReSizeEvt&)e;
			wsprintf(buffer, "Height : %u, Width : %u",
					k.GetNewHeight(), k.GetNewWidth());
			update = true;
			}
		}
		break;
			
	case CVEVT_Move:
		{
		if (Options.Tracking & CVTRACK_WINDOWS)
			{
			MoveEvt &k = (MoveEvt&)e;
			Point p = k.NewOrigin();
			wsprintf(buffer, "New origin : ( %d, %d )",
					p.X(), p.Y());
			update = true;
			}
		}
		break;
				
	case CVEVT_Expose:
		{
		if (Options.Tracking & CVTRACK_WINDOWS)
			{
			ExposeEvt &k = (ExposeEvt&)e;
			Rectangle r = k.GetExposedArea();
			wsprintf(buffer, "Exposed Area (T,L,B,R) : [%d, %d, %d, %d]",
					r.Top(), r.Left(), r.Bottom(), r.Right());
			update = true;
			}
		}
		break;
			
	case CVEVT_QueryClose:
	case CVEVT_Close:
		if (Options.Tracking & CVTRACK_WINDOWS)
			update = true;
		break;
			
	case CVEVT_MenuSelect:
		{
		if (Options.Tracking & CVTRACK_INPUT)
			{
			char MenuText[40];
			MenuText[0] = '\0';
			MenuSelectEvt &k = (MenuSelectEvt&)e;
			if (k.GetItemID() && (k.GetItemID() != (-1))
				&& k.GetMenu())
				{
				GetMenuString( k.GetMenu () -> Handle(),	// KickDown
								k.GetItemID(),
								MenuText,
								39,
								MF_BYCOMMAND);
				}
			wsprintf( buffer , "Id : %u - \"%s\"", k.GetItemID(), MenuText);
			update = true;
			}
		}
		break;

	case CVEVT_MenuCommand:
		{
		if (Options.Tracking & CVTRACK_INPUT)
			{
			char MenuText[40];
			MenuText[0] = '\0';
			MenuCommandEvt &k = (MenuCommandEvt&)e;
			if (k.GetItemID() && (k.GetItemID() != (-1))
				&& k.GetMenu())
				{
				GetMenuString( k.GetMenu () -> Handle(),	// KickDown
								k.GetItemID(),
								MenuText,
								39,
								MF_BYCOMMAND);
				}
			wsprintf(buffer , "Id : %u - \"%s\" ", k.GetItemID(), MenuText);
			update = true;
			}
		}
		break;
		
	case CVEVT_VertScroll:
	case CVEVT_HorizScroll:
		{
		if (Options.Tracking & CVTRACK_INPUT)
			{
			ScrollEvt &k = (ScrollEvt&)e;
			int sbtype = (int) k.GetScrollType();
			char ScrollTypeName [40];
			if ((sbtype >= 7) || 
					(!LoadString ( CV_LibHandle(), sbtype + 0x0600, ScrollTypeName, 39 )) )
				LoadString( CV_LibHandle(), 0x0608, ScrollTypeName, 39 );

			wsprintf(buffer, "%s[%s] Position : %d",
				(k.isWindowScroll() ? "<Window SB>  " : ""),
				ScrollTypeName,
				k.GetPos());
			update = true;
			}
		}
		break;
		
	case CVEVT_ButtonClick:
	case CVEVT_ButtonDblClk:
		{
		if (Options.Tracking & CVTRACK_INPUT)
			{
			char ControlText[40];
			ControlEvt &k = (ControlEvt&)e;
			TextControl * ptc;

			ControlText [0] = '\0';
			if (IsWindow((HWND)CV_RunTime :: Event_lParam(e)))
				GetWindowText((HWND)CV_RunTime :: Event_lParam(e),  // Kickdown
								ControlText,
								39);

			if (ptc = (TextControl*) k.GetControl())
				ptc -> GetText(ControlText, 39);

			wsprintf(buffer, "Id : %u - \"%s\" ", 
							(uint)k.GetControlID(), 
							ControlText);
			update = true;
			}
		}
		break;

	case CVEVT_EditChange:
	case CVEVT_EditScroll:
	case CVEVT_EditFocusChg:
		{
		if (Options.Tracking & CVTRACK_INPUT)
			{
			ControlEvt &k = (ControlEvt&)e;
			wsprintf(buffer, "Id : %u", (uint)k.GetControlID());
			update = true;
			}
		}
		break;

	case CVEVT_ListBoxClk:
	case CVEVT_ListBoxSel:
		{
		if (Options.Tracking & CVTRACK_INPUT)
			{
			char ControlText[120];
			ControlEvt &k = (ControlEvt&)e;
			ListBox * plb;

			ControlText [0] = '\0';

			if (plb = (ListBox*)k.GetControl())
   				plb -> GetString(ControlText, -1);

			wsprintf(buffer, "Id : %u - \"%s\"", 
							(uint)k.GetControlID(), 
							ControlText);
			update = true;
			}
		}
		break;

#if defined(WIN32)
	case CVEVT_NfyApply:
	case CVEVT_NfyCancel:
	case CVEVT_NfySetActive:
	case CVEVT_NfyKillActive:
	case CVEVT_NfyWizFinish:
	case CVEVT_NfyWizBack:
	case CVEVT_NfyWizNext:
	case CVEVT_NfyHelp:
	case CVEVT_NfyQueryCancel:
	case CVEVT_NfyClick:
	case CVEVT_NfyDblClick:
	case CVEVT_NfyBeginDrag:
	case CVEVT_NfyBeginRDrag:
	case CVEVT_NfyBeginLabelEdit:
	case CVEVT_NfyEndLabelEdit:
	case CVEVT_NfyDeleteItem:
	case CVEVT_NfyGetDispInfo:
	case CVEVT_NfySetDispInfo:
	case CVEVT_NfyItemExpanding:
	case CVEVT_NfyItemExpanded:
	case CVEVT_NfySelChanging:
	case CVEVT_NfySelChanged:
	case CVEVT_NfyDeleteAllItems:
	case CVEVT_NfyInsertItem:
	case CVEVT_NfyItemChanging:	
	case CVEVT_NfyItemChanged:	
	case CVEVT_NfyColumnClick:	
	case CVEVT_NfyEndDrag:	
	case CVEVT_NfyReset:	
	case CVEVT_NfyQueryDelete:	
	case CVEVT_NfyQueryInsert:	
	case CVEVT_NfyBeginAdjust:	
	case CVEVT_NfyCustHelp:	
	case CVEVT_NfyEndAdjust:	
	case CVEVT_NfyGetButtonInfo:	
	case CVEVT_NfyToolBarChange:	
	case CVEVT_NfyNeedText:	
	case CVEVT_NfyHidingTip:	
	case CVEVT_NfyShowingTip:	
	case CVEVT_NfyDeltaPos:	
		if (Options.Tracking & CVTRACK_WINDOWS)
			update = true;
		break;

	case CVEVT_CompareItem:
		if (Options.Tracking & CVTRACK_WINDOWS)
			update = true;
		break;

	case CVEVT_DeleteItem:
		if (Options.Tracking & CVTRACK_WINDOWS)
			update = true;
		break;

	case CVEVT_DrawItem:
		if (Options.Tracking & CVTRACK_WINDOWS)
			update = true;
		break;

	case CVEVT_MeasureItem:
		if (Options.Tracking & CVTRACK_WINDOWS)
			update = true;
		break;

	case CVEVT_Strobe:
		if (Options.Tracking & CVTRACK_WINDOWS)
			update = true;
		break;

	case CVEVT_PaletteChange:
		if (Options.Tracking & CVTRACK_WINDOWS)
			update = true;
		break;
#endif // WIN32

	default:
		OutputDebugString("Unidentified Event Tracked \n\r");
		break;
	}

	if (update) {
		OutputName(pw, ename);
		if (buffer[0])
			OutputDebugString(buffer);
		OutputDebugString("\n\r");
	}
}

 /* ======================================================================= */
 /*    End of Debugging code                                                */
 /* ======================================================================= */

#else // _DEBUG

void _DLLENTRY CVDebug (int wCategory, pchar fmt, ...) {}
void CVReport (Wind_Imp * pw, uint ename, Event e) {}

#endif // _DEBUG
