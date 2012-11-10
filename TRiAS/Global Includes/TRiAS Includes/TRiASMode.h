///////////////////////////////////////////////////////////////////////////
// @doc 
// @module TRiASMode.h | Flags und Variable zu TRiASMode

#if !defined(_TRIASMODE_H__301D50D3_F4B9_11D1_8630_00600875138A__INCLUDED_)
#define _TRIASMODE_H__301D50D3_F4B9_11D1_8630_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Flags aus Registry, die über den Mode von FakeMFC/TRiAS entscheiden 
#define TRIASMODE_SubClassTRiAS		0x01
#define TRIASMODE_HookTRiAS			0x02
#define TRIASMODE_SubClassTRiASView	0x04

#define TRIASMODE_NativeDB			0x00	// Default
#define TRIASMODE_GDO				0x08

#define TRIASMODE_InterTRiAS		0x10
#define TRIASMODE_RollUpORWnds		0x20

extern DWORD g_dwTRiASMode;					// TRiASMode

///////////////////////////////////////////////////////////////////////////////
// Flags aus der Registry, die über ZeichenModi entscheiden
#define DRAWMODE_Default			0x00	// default
#define DRAWMODE_IdleDuringDraw		0x01

extern DWORD g_dwDrawingMode;

#define DRAWMODE_FlickerFree		0x02
#define DRAWMODE_IdleAfterDrawOnly	0x04
#define DRAWMODE_FirstObjectDraws	0x08
#define DRAWMODE_StoreCanvas		0x10
#define DRAWMODE_IdleAfterInterval	0x20

#define DRAWMODE_FlickerFreeMask	( \
			DRAWMODE_IdleDuringDraw | \
			DRAWMODE_FlickerFree | \
			DRAWMODE_IdleAfterDrawOnly | \
			DRAWMODE_FirstObjectDraws | \
			DRAWMODE_StoreCanvas | \
			DRAWMODE_IdleAfterInterval)

#define DEFAULT_DRAW_MODE ( \
			DRAWMODE_IdleDuringDraw | \
			DRAWMODE_FlickerFree | \
			DRAWMODE_StoreCanvas | \
			DRAWMODE_IdleAfterInterval)

#if defined(_USE_FLICKERFREE_DRAWING)
#define DEFAULT_TICKS_BETWEEN_PAINTS	 800		// einmal je 800 ms
#define DEFAULT_TICKS_BETWEEN_IDLELOOPS	 100		// zehmahl je Sekunde Idle'n

extern DWORD g_dwTicksBetweenPaints;
extern DWORD g_dwTicksBetweenIdleLoops;
#endif // _USE_FLICKERFREE_DRAWING

// DataTips nicht anzeigen (bei HideFlags gespeichert)
#define ROHideDataTips				0x10000L

#endif // !defined(_TRIASMODE_H__301D50D3_F4B9_11D1_8630_00600875138A__INCLUDED_)
