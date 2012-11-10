// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.10.2000 07:36:49 
//
// @doc
// @module ObjPropDestWindow.h | Declaration of the <c CObjPropDestWindow> class

#if !defined(_OBJPROPDESTWINDOW_H__EAE46096_903E_42A5_AACE_212DB214CF7B__INCLUDED_)
#define _OBJPROPDESTWINDOW_H__EAE46096_903E_42A5_AACE_212DB214CF7B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CObjPropDestWindow : 
	public DialogWindow 
{
private:
	CListViewCtrl m_Result;
	PushButton m_pbCopy;
	PushButton m_pbOk;
	LPCSTR m_pcText;		// Verweis auf angezeigten Text

	Rectangle m_rcCanvas;
	
	Dimension m_dimOk;
	Dimension m_dimCopy;
	Dimension m_dimResult;
	Point m_ptOk;
	Point m_ptCopy;
	Point m_ptResult;

protected:
	void ButtonClick (ControlEvt);
	void ReSize (ReSizeEvt e);
	void Expose (ExposeEvt e);
	LRESULT Dispatch (Event e);

	virtual void GetMinMaxInfo (MINMAXINFO *pMinMaxInfo);
	virtual BOOL NcHitTest (Point pt, LRESULT *pResult);
	
	bool InitListViewCtrl (LPCSTR pcText, bool fHeadline);

public:
		CObjPropDestWindow (pWindow pParent, ResID uiResID, LPCSTR pcText, bool fHeadline = true);
		~CObjPropDestWindow (void) {}
};

#endif // !defined(_OBJPROPDESTWINDOW_H__EAE46096_903E_42A5_AACE_212DB214CF7B__INCLUDED_)
