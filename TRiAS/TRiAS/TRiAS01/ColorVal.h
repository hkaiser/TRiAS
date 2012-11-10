// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/08/1998 01:14:57 PM
//
// @doc
// @module ColorVal.h | Color/ColorVal aus CommonVu ersetzen

#if !defined(_COLORVAL_H__7AEE4866_8E6C_11D2_9EFC_006008447800__INCLUDED_)
#define _COLORVAL_H__7AEE4866_8E6C_11D2_9EFC_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
//
typedef unsigned char ColorVal;

enum Colors { BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE };

class Color
{
private:
	ColorVal		R;
	ColorVal		G;
	ColorVal		B;
	ColorVal		_reserved;

public:
	Color (void) 
		{ R = G = B = _reserved = 0; }
	Color (ColorVal r, ColorVal g, ColorVal b) 
		{ R = r; G = g; B = b; _reserved = 0; }

	Color (Colors c)
	{
		R = G = B = _reserved = 0;
		switch (c) {	//	Select for Red
		case RED:
		case MAGENTA:
		case YELLOW:
		case WHITE:
			R = 255;
			break;
		}
		switch (c) {	//	Select for Green
		case GREEN:
		case CYAN:
		case YELLOW:
		case WHITE:
			G = 255;
			break;
		}
		switch (c) {	//	Select for Blue
		case BLUE:
		case CYAN:
		case MAGENTA:
		case WHITE:
			B = 255;
			break;
		}
		_reserved = 0;
	}

	ColorVal &	Red (void) { return R; }
	ColorVal &	Green (void) { return G; }
	ColorVal &	Blue (void) { return B; }
	ColorVal &	Reserved (void) { return _reserved; }	// #HK920730
};

#endif // !defined(_COLORVAL_H__7AEE4866_8E6C_11D2_9EFC_006008447800__INCLUDED_)
