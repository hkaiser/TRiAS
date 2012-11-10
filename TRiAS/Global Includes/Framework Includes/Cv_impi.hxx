//	Usage:	#include <CV_IMPI.hxx>
//
//	Implementor interface to CA-CommonView release 3.1, 
//	Inline functions for implementor 
//
//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992
//
//	Tab stops in this file are at	4 * n + 1
//
//	-------------------------------------------------------------------------
#ifndef CV_IMP_INLINE
#define CV_IMP_INLINE

#ifndef	NOAPP				
//===================================================================
// App_Imp functions
//===================================================================
inline unsigned short App_Imp  :: DS (void)	{ return DS_segment; }
inline pCVLinked_List App_Imp :: ControlList()  { return &List_of_Controls; }
inline pCVLinked_List App_Imp :: ContextList()  { return &List_of_EventContexts; }
inline pCVLinked_List App_Imp :: MenuList()  	{ return &List_of_Menus; }
inline pCVLinked_List App_Imp :: PrinterList()  { return &List_of_Printers; }
inline pCVLinked_List App_Imp :: ResourceList() { return &List_of_Resources; }
#if defined(WIN32)
inline pCVLinked_List App_Imp :: ImagesList()	{ return &List_of_ImageLists; }
// #HK960214: PreTranslateMessage-Stuff
inline PRETRANSLATEPROC App_Imp :: AttachPreTranslateMsgProc (PRETRANSLATEPROC pNewF)
{
PRETRANSLATEPROC pF = m_pPreTranslateMsgProc;

	m_pPreTranslateMsgProc = pNewF;
	return pF; 
}
inline PRETRANSLATEPROC App_Imp :: DetachPreTranslateMsgProc (void) 
{ 
PRETRANSLATEPROC pF = m_pPreTranslateMsgProc;

	m_pPreTranslateMsgProc = NULL;
	return pF; 
}
inline IDLEPROC App_Imp :: AttachIdleProc (IDLEPROC pNewF)
{
IDLEPROC pF = m_pIdleProc;

	m_pIdleProc = pNewF;
	return pF; 
}
inline IDLEPROC App_Imp :: DetachIdleProc (void) 
{ 
IDLEPROC pF = m_pIdleProc;

	m_pIdleProc = NULL;
	return pF; 
}
#endif // WIN32
inline CVTable* App_Imp :: RegClassList()  	{ return &List_of_RegClasses; }
#endif // NOAPP

#ifndef	NOACCEL
//===================================================================
// Accel_Imp functions
//===================================================================
inline HACCEL Accel_Imp :: Handle( Service) { return hAccel ; }
#endif // NOACCEL

#ifndef	NOBITMAP
//===================================================================
// Bitmap_Imp functions
//===================================================================
inline	HBITMAP	Bitmap_Imp :: Handle (Service ) { return hBitmap ; }
#endif // NOBITMAP

#ifndef	NOBRUSH
//===================================================================
// Brush_Imp functions
//===================================================================
inline	HBRUSH	Brush_Imp :: Handle (Service) { return hBrush ; }
#endif // NOBRUSH

#ifndef	NOCURSOR
//===================================================================
// Cursor_Imp functions
//===================================================================
#endif // NOCURSOR

#ifndef	NOFONT
//===================================================================
// Font_Imp functions
//===================================================================
inline HFONT	Font_Imp :: Handle (Service) { return hFont ; }
inline BOOL Font_Imp :: isLight () {	return	( lft->lfWeight == LIGHTWEIGHT );	}
inline BOOL Font_Imp :: isNormal () {	return	( lft->lfWeight == NORMALWEIGHT );	}
inline BOOL Font_Imp :: isBold () {	return	( lft->lfWeight == HEAVYWEIGHT );	}
inline BOOL Font_Imp :: isItalic () {	return	lft->lfItalic ? true : false;		}
inline BOOL Font_Imp :: isUnderline () {	return	lft->lfUnderline ? true : false;	}
inline BOOL Font_Imp :: isStrikethru () {	return	lft->lfStrikeOut ? true : false;	}
inline BOOL Font_Imp :: isPitchFixed ()	{	return	(( lft->lfPitchAndFamily & 3 ) == 1);		}
inline BOOL Font_Imp :: isPitchVariable () {	return	(( lft->lfPitchAndFamily & 3 ) == 2);		}
#endif // NOFONT

#ifndef	NOICON
//===================================================================
// Icon_Imp functions
//===================================================================
inline HICON	Icon_Imp :: Handle(Service) { return hIcon ; }
#endif // NOICON

#ifndef  NOPEN
inline HPEN Pen_Imp :: Handle (Service) { return hPen ; }
#endif // NOPEN

#ifndef	NOPOINTER
inline HCURSOR Pointer_Imp :: Handle(Service) { return hPointer ; }
#endif // NOPOINTER


#ifndef	NOMENU
inline HMENU	Menu_Imp :: Handle (Service) { return hMenu ; } ;
#endif // NOMENU

#ifndef NOCONTROL
inline BOOL	Control_Imp :: Valid() { return hControl && IsWindow(hControl); }
inline HWND	Control_Imp :: Handle (Service) { return	hControl; }
inline Point	Control_Imp :: GetPosition (void) { return ControlWhere; }
inline Dimension Control_Imp :: GetSize (void) { return ControlSize; }

#ifndef NOSCROLLBAR
inline 	uint ScrollB_Imp :: GetBlock (void) { return SBBlock; }
inline 	void ScrollB_Imp :: SetBlock (uint b) { SBBlock = b; 	}
inline 	uint ScrollB_Imp :: GetUnit  (void) { return SBUnit; }
inline 	void ScrollB_Imp :: SetUnit  (uint u) {	SBUnit = u;  }
#endif // NOSCROLLBAR

#endif // NOCONTROL

//===================================================================
// Wind_Imp functions
//===================================================================
#ifndef	NOEVENT			

inline pAccel	 Wind_Imp::    GetAccel	(  )
{
	return WndAccel;
}

inline pPen	 Wind_Imp::    GetPen	( )
{
	return WndPen;
}

inline pMenu	 Wind_Imp::    GetMenu	(  )
{
	return WndMenu;
}

inline pPointer	 Wind_Imp::    GetPointer	(  )
{
	return WndPointer;
}


inline pBrush	 Wind_Imp::    GetBackground (  )
{
	return WndBackground;
}

inline pBrush	 Wind_Imp::    GetBrush	(  )
{
	return WndBrush;
}


inline pFont	 Wind_Imp::    GetFont	(  )
{
	return WndFont;
}

inline WNDPROC *DWind_Imp::GetSuperClassProc (void)
{
	return &m_poldProc;
}

#endif // NOEVENT

#endif // CV_IMP_INLINE
