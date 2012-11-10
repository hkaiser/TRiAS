//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992

#ifndef _CVDLG_HXX
#define _CVDLG_HXX 1

class StdFileDlg
{
protected:
	void * implementor;
public:
	  		StdFileDlg ( ) ;

	char *	GetFileName();
	void 	Show();
			~StdFileDlg ();
};

class OpenDialog : public StdFileDlg
{
public:
		OpenDialog (pWindow Parent, char *TheFileSpec = "*.*");
		~OpenDialog();
};

class SaveAsDialog : public StdFileDlg
{
public:
		SaveAsDialog (pWindow Parent, char *SaveDirectory = "");
		~SaveAsDialog();
};
#endif

