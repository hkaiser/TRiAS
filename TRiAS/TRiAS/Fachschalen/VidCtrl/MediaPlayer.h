// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 28.06.2002 15:51:55 
//
// @doc
// @module MediaPlayer.h | Declaration of the <c CMediaPlayer> class

#if !defined(_MEDIAPLAYER_H__71B1D599_248A_440E_94D9_0DA06E9BD35B__INCLUDED_)
#define _MEDIAPLAYER_H__71B1D599_248A_440E_94D9_0DA06E9BD35B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

// Import MediaPlayer typelibrary
#import "msdxm.ocx" \
	raw_interfaces_only raw_native_types no_namespace named_guids \
	exclude("IServiceProvider")

// SmartIF's
DefineSmartInterface(MediaPlayer2)

// CMediaPlayer Class
class CMediaPlayer :
	public CAxWindow
{
public:
// Construction
	CMediaPlayer(HWND hWnd = NULL) : CAxWindow(hWnd) {}
	~CMediaPlayer() {}

// Attributes
	HRESULT SendMouseClickEvents(bool fSendEvents = true);

// Operations
	HRESULT Attach (HWND hWnd);

// Implementation
protected:
// Attributes

// Operations

private:
	WMediaPlayer2 m_spPlayer;
};

#endif // !defined(_MEDIAPLAYER_H__71B1D599_248A_440E_94D9_0DA06E9BD35B__INCLUDED_)
