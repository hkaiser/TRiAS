//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992

#ifndef	_CV_DEBUG_HXX
#define	_CV_DEBUG_HXX	1

#ifndef NODEBUGGING

struct DebugOptions {
	int 	DebugFlag;
	int	TmpFlag;
	int 	Tracking;
	int 	DebugCountOn;
	long 	DebugCount;
	};

extern DebugOptions * CVDebugOptions();
extern 	DebugOptions	Options;


void CheckDS();
#define Report( x, y, z ) if (CVDebugging) CVReport(x, y, z)
#else
#define CheckDS(x)	
#define Report( x, y, z)
#endif


#define CVTRACK_MOUSE		0x0001
#define CVTRACK_WINDOWS		0x0002
#define CVTRACK_INPUT		0x0004
#define CVTRACK_SYSTEM		0x0008
#define CVTRACK_INIT		0x0010
#define CVTRACK_CLIPBOARD 	0x0020
#define CVTRACK_DDE			0x0040
#define CVTRACK_NONCLIENT	0x0080
#define CVTRACK_NAMES		0x0100

#ifdef _DYNALINK
#ifndef NOEVENT
void CVReport(Wind_Imp*, uint, Event);
#endif
#endif
//  Defines for messages in debugging

#define	CVEVT_WindowInit		0
#define	CVEVT_MouseButtonDn		1
#define	CVEVT_MouseButtonUp		2
#define	CVEVT_MouseButtonDblClk		3
#define	CVEVT_MouseMove			4
#define	CVEVT_MouseDrag			5
#define	CVEVT_KeyDown			6
#define	CVEVT_KeyUp			7
#define	CVEVT_Activate			8
#define	CVEVT_DeActivate		9
#define	CVEVT_FocusChange		10
#define	CVEVT_ReSize			11
#define	CVEVT_Move			12
#define	CVEVT_Expose			13
#define	CVEVT_QueryClose		14
#define	CVEVT_Close			15
#define	CVEVT_MenuInit			16
#define	CVEVT_MenuSelect		17
#define	CVEVT_MenuCommand		18
#define	CVEVT_VertScroll		19
#define	CVEVT_HorizScroll		20
#define	CVEVT_ButtonClick		21
#define	CVEVT_ButtonDblClk		22
#define	CVEVT_EditChange		23
#define	CVEVT_EditScroll		24
#define	CVEVT_EditFocusChg		25
#define	CVEVT_ListBoxClk		26
#define	CVEVT_ListBoxSel		27
#define	CVEVT_Help			28

#if defined(WIN32)
#define CVEVT_NfyApply			29
#define CVEVT_NfySetActive		30
#define CVEVT_NfyKillActive		31
#define CVEVT_NfyCancel			32
#define	CVEVT_CompareItem		33
#define CVEVT_DeleteItem		34
#define CVEVT_DrawItem			35
#define CVEVT_MeasureItem		36
#define CVEVT_Strobe			37
#define CVEVT_PaletteChange		38
#define CVEVT_NfyWizFinish		39
#define CVEVT_NfyWizBack		40
#define CVEVT_NfyWizNext		41
#define CVEVT_NfyHelp			42
#define CVEVT_NfyQueryCancel		43
#define CVEVT_NfyBeginDrag		44
#define CVEVT_NfyBeginRDrag		45
#define CVEVT_NfyBeginLabelEdit		46
#define CVEVT_NfyEndLabelEdit		47
#define CVEVT_NfyDeleteItem		48
#define CVEVT_NfyGetDispInfo		49
#define CVEVT_NfySetDispInfo		50
#define CVEVT_NfyItemExpanding		51
#define CVEVT_NfyItemExpanded		52
#define CVEVT_NfySelChanging		53
#define CVEVT_NfySelChanged		54
#define CVEVT_NfyClick			55
#define CVEVT_NfyDblClick		56
#define CVEVT_NfyDeleteAllItems		57
#define CVEVT_NfyInsertItem		58
#define CVEVT_NfyItemChanging		59
#define CVEVT_NfyItemChanged		60
#define CVEVT_NfyColumnClick		61
#define CVEVT_NfyEndDrag		62
#define CVEVT_NfyReset			63
#define CVEVT_NfyQueryDelete		64
#define CVEVT_NfyQueryInsert		65
#define CVEVT_NfyBeginAdjust		66
#define CVEVT_NfyCustHelp		67
#define CVEVT_NfyEndAdjust		68
#define CVEVT_NfyGetButtonInfo		69
#define CVEVT_NfyToolBarChange		70
#define CVEVT_NfyNeedText		71
#define CVEVT_NfyHidingTip		72
#define CVEVT_NfyShowingTip		73
#define CVEVT_NfyDeltaPos		74

#define CVEVT_Last			74
#else
#define CVEVT_Last			28
#endif


#define CVEVT_UnknownEvt		1400

#include <cv_debug.hxx>

#endif		// _CV_DEBUG_HXX

