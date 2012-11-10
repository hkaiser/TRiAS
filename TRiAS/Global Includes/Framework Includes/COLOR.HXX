//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992
#ifndef COLORHXX
#define COLORHXX

#include <commonvu.hxx>
#include <drawobj.hxx>

class StdColorDlg
{
protected:
	void * implementor;
public:
	  		StdColorDlg ( ) ;

	Color	GetColor ();
	void 	Show();
			~StdColorDlg ();
};

class SelectWindow : public StdColorDlg
{
public:
					SelectWindow ( pWindow, Color );
					~SelectWindow ();
};


class PaletteWindow : public StdColorDlg
{
public :
						PaletteWindow ( pWindow, Color );
						~PaletteWindow ();
};

#endif

