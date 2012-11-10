// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.06.2002 09:13:54 
//
// @doc
// @module VideoPaneWindowImpl.h | Declaration of the <c CVideoPaneWindowImpl> class

#if !defined(_VIDEOPANEWINDOWIMPL_H__F3B2A9C7_77C5_49CF_895C_9C17F37B30D7__INCLUDED_)
#define _VIDEOPANEWINDOWIMPL_H__F3B2A9C7_77C5_49CF_895C_9C17F37B30D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"
#include "DialogView.h"
#include "MediaPlayer.h"
#include "MediaPlayerEvent.h"
#include "LayoutMgr.h"

///////////////////////////////////////////////////////////////////////////////
// CVideoPaneWindowImpl Class
class CVidCtrlExtension;

class CVideoPaneWindowImpl :
	public CDialogView<CVideoPaneWindowImpl, CAxResizableDialogImpl<CVideoPaneWindowImpl> >,
	public IDispEventImpl<IDC_LEFTCHANNEL, CVideoPaneWindowImpl, 
		&DIID__MediaPlayerEvents, &LIBID_MediaPlayer, 1, 0>,
	public IDispEventImpl<IDC_MIDDLECHANNEL, CVideoPaneWindowImpl, 
		&DIID__MediaPlayerEvents, &LIBID_MediaPlayer, 1, 0>,
	public IDispEventImpl<IDC_RIGHTCHANNEL, CVideoPaneWindowImpl, 
		&DIID__MediaPlayerEvents, &LIBID_MediaPlayer, 1, 0>
{
public:
	enum { IDD = IDD_VIDEOPANE };
	
	enum LAYOUTTYPE {
		LAYOUTTYPE_Left = 1,
		LAYOUTTYPE_Middle = 2,
		LAYOUTTYPE_Right = 3,
	};

// Construction
	CVideoPaneWindowImpl();
	~CVideoPaneWindowImpl();

	typedef CDialogView<CVideoPaneWindowImpl, CAxResizableDialogImpl<CVideoPaneWindowImpl> > dialogbase_t;

	BEGIN_MSG_MAP_EX(CVideoPaneWindowImpl)
		MSG_WM_INITDIALOG(OnInitDialog)
		CHAIN_MSG_MAP(CAxResizableDialogImpl<CVideoPaneWindowImpl>)
		CHAIN_MSG_MAP(dialogbase_t)
		MSG_WM_DESTROY(OnDestroy)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BEGIN_SINK_MAP(CVideoPaneWindowImpl)
	   SINK_ENTRY_EX(IDC_LEFTCHANNEL, DIID__MediaPlayerEvents, DISPID_WMP_MOUSEUP, OnLeftMouseUp)
	   SINK_ENTRY_EX(IDC_MIDDLECHANNEL, DIID__MediaPlayerEvents, DISPID_WMP_MOUSEUP, OnMiddleMouseUp)
	   SINK_ENTRY_EX(IDC_RIGHTCHANNEL, DIID__MediaPlayerEvents, DISPID_WMP_MOUSEUP, OnRightMouseUp)
	END_SINK_MAP()

	virtual void DefineLayout();
	static const UINT _controlsToClip[];

	LRESULT OnInitDialog(HWND /*hWnd*/, LPARAM /*lParam*/);
	void OnDestroy();

// Event handlers
	void __stdcall OnLeftMouseUp(short Button, short ShiftState, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	void __stdcall OnMiddleMouseUp(short Button, short ShiftState, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	void __stdcall OnRightMouseUp(short Button, short ShiftState, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);

// Attributes

// Operations
	static HRESULT RegisterTabWindow(CVidCtrlExtension *pXtsn);
	static CVideoPaneWindowImpl *CreateInstance(CVidCtrlExtension *pXtsn);
	bool ReShow(CVidCtrlExtension *pXtsn);
	static void DeleteInstance(CVidCtrlExtension *pXtsn, CVideoPaneWindowImpl *&pValues);

	CComVariant GetIcon() 
	{ 
		EnsureIcon();
		return CComVariant(reinterpret_cast<INT_PTR>(m_hIcon), VT_I4); 
	}

// Implementation
protected:
// Attributes

// Operations
	bool EnsureIcon();
	void DefineLayout(LAYOUTTYPE rgLayoutType);
	void RecalcLayout(LAYOUTTYPE rgLayoutType);
	void RepositionLayout(LAYOUTTYPE rgLayoutType);

private:
	CMediaPlayer m_axLeft;
	CMediaPlayer m_axMiddle;
	CMediaPlayer m_axRight;

	HICON m_hIcon;
	LAYOUTTYPE m_rgLayoutType;
};

#endif // !defined(_VIDEOPANEWINDOWIMPL_H__F3B2A9C7_77C5_49CF_895C_9C17F37B30D7__INCLUDED_)
