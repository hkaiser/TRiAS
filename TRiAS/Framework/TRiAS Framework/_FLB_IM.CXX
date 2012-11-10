/* $Header:   G:/cv.win/pvcs/commonvu/src/_flb_im.cxv   3.0.1.0   14 Jul 1992 11:55:34   RONAN  $
 *
 * 	_ F I L E L B . C X X
 *	
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 * 
 * Implementation of file list boxes
 *
 *	Modification log:
 *  0.1  rs     09Jan89 File list boxes 1st dynalink implementation
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	2.0 rs		??Aug90 -------Release 2.0 ship date ----------------
 *	2.1 rs		10Oct90 Allow  exclusive mask to be used for file listings
 *	2.2 pc		18Jun92 Remove LBS_NOTIFY style added in ListBox_Imp constructor.
 *				This style can alter the style (type) of ComboBox requested.
 *	2.3 pc		18Jun92 Added this function so that ComboBoxs can set the correct sorting
 *				style (LBS_SORT can alter the style (type) of ComboBox requested.
 *				Note that this is now a virtual function.
 */
#include "tfrmpre.hxx"

#if !defined(ListBox_SetCaretIndexEx)
#define ListBox_SetCaretIndexEx(hwndCtl, index, fscroll)       ((int)(DWORD)SNDMSG((hwndCtl), LB_SETCARETINDEX, (WPARAM)(int)(index), (LPARAM)(MAKELPARAM(fscroll, 0))))
#endif // !defined(ListBox_SetCaretIndexEx)

//START_C_FUNCTIONS
//static pchar PASCAL_FUNC strrchr( const char* str, int ch);
//END_C_FUNCTIONS

uint LBMessages [][2] =
{
	{ LB_ADDSTRING, CB_ADDSTRING },		
	{ LB_INSERTSTRING, CB_INSERTSTRING },	
	{ LB_DELETESTRING, CB_DELETESTRING },
	{ LB_FINDSTRING, CB_FINDSTRING },
	{ LB_FINDSTRINGEXACT, CB_FINDSTRINGEXACT },
	{ LB_GETCOUNT, CB_GETCOUNT },
	{ LB_GETCURSEL, CB_GETCURSEL },
	{ LB_GETTEXT, CB_GETLBTEXT },
	{ LB_GETTEXTLEN, CB_GETLBTEXTLEN },
	{ LB_RESETCONTENT , CB_RESETCONTENT },
	{ LB_SETCURSEL, CB_SETCURSEL },
	{ LB_SETITEMDATA, CB_SETITEMDATA },
	{ LB_GETITEMDATA, CB_GETITEMDATA },
};

enum LBM_Indices
{ lbAdd = 0, lbInsert, lbDelete, lbFind, lbFindExact,
  lbGetCount, lbGetCurSel, lbGetText, lbGetTextLen, 
  lbClear, lbSetCurSel, lbSetItemData, lbGetItemData,
};

/*
pchar PASCAL_FUNC strrchr( const char* str, int ch)
{
    const char* str1 = str + strlen(str) ;
    ch &= 0x7f;

    do 
        {
        if (ch == (*str1 & 0x7f))
            return (char*)str1;
        str1 = AnsiPrev( str, str1 );
        }
    while (str1 > str);

    return (char*)0;

}
*/
// ------------------  ListBox_Imp - Implementor for BaseListBox-----------

ListBox_Imp::  ListBox_Imp ( pControl req,  pDWind_Imp pW, ResID RscID )
	: TextControl_Imp(req,  pW, RscID)
	{
    SortDescending = false;
	MessageSet = 0;
	TabStop = 0;
	}

ListBox_Imp::  ListBox_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size )
	:	TextControl_Imp(req, parent, UsrID, where, size ,(const char *) CTRL_ListBox)
{
	SetStyle ( WS_VSCROLL | WS_BORDER );	
    SortDescending = false;
	MessageSet = 0;
	TabStop = 0;
}	// End of "ListBox_Imp" CONSTRUCTOR "(pWind_Imp,uint,Point,Dimension)"


int	ListBox_Imp::  AddString	( const char* String, int position )
{
	if (ValidateControl()) {
		if (position < 0) {
		int NoEntries = GetCount();

			if ((!SortDescending) || !NoEntries )
				return	(int) ( SendMessage ( Handle (), LBMessages[lbAdd][MessageSet], 0, (ulong)String ));
			else
				position = GetInsertPos (String);
		}
		return	(int) SendMessage ( Handle (), LBMessages[lbInsert][MessageSet], position, (ulong)String );
	}
	else
		return -1;
}	

int ListBox_Imp:: GetCurrentIndex()
{
 	return (-1);
}

int ListBox_Imp:: GetLineLen (int line)
{
int retval=(int)SendMessage( Handle(), LBMessages[lbGetTextLen][MessageSet], line, 0L);

	return ((retval == (-1)) ? 0 : retval); 
}

int ListBox_Imp:: GetInsertPos (const char * String)
{
    int NoEntries = GetCount();
	int retval = (-1);

	int count = 0;
	if (NoEntries)
	{
		do {
	    	char * buff;
	        int length = (int)SendMessage( Handle(), LBMessages[lbGetTextLen][MessageSet], count, 0L);

		        if (buff = new char[length + 1]) {
	        		GetString ( buff , count, (-1));
	        		if (lstrcmpi ( String , buff ) > 0)
	            		retval = count;
				delete buff;
			}
		}	while ( (count++ < NoEntries) && (retval == (-1)) );  
	}
	return retval;
}
  
BOOL	ListBox_Imp::  DelString	( int StrIndex )
{
	if	(( StrIndex < 0 ) && ((StrIndex	= GetCurrentIndex ()) < 0))
		return false;

	if (ValidateControl())    
    	return	( LB_ERR != ((uint)
			( SendMessage ( Handle (), LBMessages[lbDelete][MessageSet], StrIndex, 0 ))));
	else
		return 0;
}	// End of "ListBox_Imp" FUNCTION "DelString"


int	ListBox_Imp::  GetCount	()
{
	if (ValidateControl())    // RSDEBUG
		return	(int) ( SendMessage ( Handle (), LBMessages[lbGetCount][MessageSet], 0, 0 ));
	else
		return 0;

}	// End of "ListBox_Imp" FUNCTION "GetCount"

void ListBox_Imp ::SetTop ( int topIndex)
{
	if (ValidateControl())
		ListBox_SetTopIndex (Handle(), topIndex);
//		SendMessage (Handle(), LB_SETTOPINDEX, topIndex, 0L);
}

void ComboBox_Imp ::SetTop ( int )
{
}

BOOL ListBox_Imp:: GetString (pchar buff, int index, int length)
{
	int slen = 1;
	
 	// If index is current selection but no selection present
	// Do nothing and return false

	if ((index == (-1))
		&& ((index = GetCurrentIndex()) == (-1)))
		return false;

	// If a limit has been specified for the length
	// check is size of item is less than limit
	//   if so, treat it as unlimited.
	if (length != (-1))
		{
		if (!(slen = GetLineLen(index)))
			return false;
		if (slen <= length)
			length = (-1);
		}

	// If no effective size limit just use message

	if (length == (-1))
		return (SendMessage ( Handle (), LBMessages[lbGetText][MessageSet], index, (ulong)buff ) != LB_ERR);
	else {
	// Copy item to local buffer in order to enforce buffer limits
	bool retval = false;
	char *p;
		if (p = new char[slen + 1])
		{
			if (retval = ( SendMessage ( Handle (), LBMessages[lbGetText][MessageSet], index, (ulong)p ) != LB_ERR))
			CV_strncpy(buff, p, slen);
			delete p;
		}

		return retval;
	}
}

void ListBox_Imp :: Clear()
{
	if (ValidateControl())    
		SendMessage ( Handle (), LBMessages[lbClear][MessageSet], 0, 0 );
}

int ListBox_Imp::  FindString (const char * str, BOOL wholeword)
{
int slen;

	if (str && (slen=lstrlen(str))) {
	int index = GetCurrentIndex();

    	if (LB_ERR != (index = (int)SendMessage (Handle(), LBMessages[lbFind][MessageSet], index, (ulong)str ) ))
    	{
        	if (!wholeword) 
				return index;
			else
				return ((slen == GetLineLen(index)) ? index : (-1));
	    }
	}

return -1 ;
}

HDWP ListBox_Imp::  RePosition (HDWP hDefer, BOOL ReSize, BOOL ReDraw)
{
	return Control_Imp :: RePosition(hDefer, ReSize, false);
}

void ListBox_Imp :: Create ()
{
	if (!hControl)
		SetStyle(LBS_NOTIFY | LBS_NOINTEGRALHEIGHT);
	TextControl_Imp :: Create();
}

// ----------------------------- SingleSelListBox ----------------------------
SingleSelListBox_Imp::  SingleSelListBox_Imp ( pControl req,  pDWind_Imp pW, ResID RscID )
	: ListBox_Imp(req,  pW, RscID)
	{
	}

SingleSelListBox_Imp::  SingleSelListBox_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size )
	:	ListBox_Imp(req, parent, UsrID, where, size )
{
}	

int	SingleSelListBox_Imp::  GetCurrentIndex	()
{
	int i;
	
	if (ValidateControl() &&
	(LB_ERR != (i = (int) ( SendMessage ( Handle (), LBMessages[lbGetCurSel][MessageSet], 0, 0L )))))
		{
			// LB_GETCURSEL does not return -1 if the previous last line 
			// has been deleted : it returns the last index which is equal
			// to the new count . We must return -1 as no item is
			// selected .
			if( i == (int) (SendMessage ( Handle (), LBMessages[lbGetCount][MessageSet], 0, 0L )))
				return(-1);
			else
				return i;
		}
	return (-1);
}	


BOOL	SingleSelListBox_Imp::  ChangeCurrentIndex ( int index )
{
	if (ValidateControl())    
		return	( LB_ERR != ((uint)
			( SendMessage ( Handle (), LBMessages[lbSetCurSel][MessageSet], index, 0 ))));
    return 0;

}	// End of "ListBox_Imp" FUNCTION "ChangeCurrentIndex"

// --------------------------- MultiSelListBoxImp ------------------------

MultiSelListBox_Imp::  MultiSelListBox_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size )
	:	ListBox_Imp(req, parent, UsrID, where, size )
{
    	SetStyle (LBS_MULTIPLESEL);
	SelectNo = 0;
}	

MultiSelListBox_Imp::  MultiSelListBox_Imp ( pControl req,  pDWind_Imp pW, ResID RscID )
	: ListBox_Imp(req,  pW, RscID)
{
    	SetStyle (LBS_MULTIPLESEL);
	SelectNo = 0;
}

int MultiSelListBox_Imp:: GetNoSelected ()
{
int noSelected;

	if (ValidateControl())    // RSDEBUG
	{
//		if ((noSelected = (int)SendMessage ( Handle (), LB_GETSELCOUNT, 0, 0 )) != (-1))
		if ((noSelected = ListBox_GetSelCount (Handle())) != LB_ERR)
			return noSelected;
	}

return 0;
}

BOOL MultiSelListBox_Imp:: ClearSelected ()
{
	if (ValidateControl())    
	{
//		SendMessage (Handle(), LB_SETSEL, 0, 0xFFFFFFFF);
		ListBox_SetSel (Handle(), false, -1);
		return true;
	}
	else
		return false;
}


int MultiSelListBox_Imp ::GetFirstSelected ()
{
int noSelected;
int result = (-1);
	
	SelectNo = 0;
	if (ValidateControl() &&  ((noSelected = GetNoSelected()) > 0))
	{
	int * SelectedArray = new int[noSelected];

//		if (SendMessage(Handle(), LB_GETSELITEMS, noSelected, (long) SelectedArray) != LB_ERR)
		if (ListBox_GetSelItems (Handle(), noSelected, SelectedArray) != LB_ERR)
			result =  SelectedArray[SelectNo++];
		delete SelectedArray;
	}
	return result;
}


int MultiSelListBox_Imp ::GetNextSelected ()
{
int noSelected;
int result = (-1);

	if (ValidateControl() && (( noSelected = GetNoSelected())> SelectNo))
	{
	int *SelectedArray = new int[noSelected];
	
//		if (SendMessage(Handle(), LB_GETSELITEMS, noSelected, (long) SelectedArray) != LB_ERR)
		if (ListBox_GetSelItems (Handle(), noSelected, SelectedArray) != LB_ERR)
			result =  SelectedArray[SelectNo++];
		delete SelectedArray;
	}
	return result;
} 

BOOL MultiSelListBox_Imp ::ChangeSelected (int index, BOOL setting)
{
	if (ValidateControl())
//	    	return  (bool) (SendMessage(Handle(), LB_SELITEMRANGE,
//			(setting ? 1 : 0) ,MakeLong(index, index)) != LB_ERR);
		return (ListBox_SelItemRange (Handle(), setting ? true : false, index, index) != LB_ERR);

return false;
}

BOOL MultiSelListBox_Imp ::ChangeSelected ( Range r, BOOL setting)
{
	if (ValidateControl())    
//    		return  (bool)(SendMessage(Handle(), LB_SELITEMRANGE,
//			(setting ? 1 : 0) ,MakeLong ( r.Min(), r.Max())) != LB_ERR);
		return (ListBox_SelItemRange (Handle(), setting ? true : false, r.Min(), r.Max()) != LB_ERR);

return false;
}


short MultiSelListBox_Imp ::GetCaretIndex (void)
{
	if (ValidateControl())    
		return ListBox_GetCaretIndex (Handle());
//	    	return  short(SendMessage(Handle(), LB_GETCARETINDEX, 0, 0L));

return LB_ERR;
}


BOOL MultiSelListBox_Imp ::SetCaretIndex (short iIndex, BOOL fScroll)
{
	if (ValidateControl())    
//    	return  (bool)(SendMessage(Handle(), LB_SETCARETINDEX, iIndex, MakeLong(fScroll, 0)) != LB_ERR);
	    	return  (ListBox_SetCaretIndexEx (Handle(), iIndex, fScroll) != LB_ERR);
	return false;
}


BOOL MultiSelListBox_Imp :: GetSelection (short iIndex)
{
	if (ValidateControl())    
//    	return  (bool) (SendMessage(Handle(), LB_GETSEL, iIndex, 0L) > 0);
  	  	return (ListBox_GetSel (Handle(), iIndex) > 0);
	return false;
}

int MultiSelListBox_Imp::FindString (const char *str, BOOL fWhole, int iStart)
{
	if (str) {
	int iMsg = fWhole ? lbFindExact : lbFind;

    	return (int)SendMessage (Handle(), LBMessages[iMsg][MessageSet], iStart, (ulong)str);
	}

return -1;
}

// ------------------  ComboBox --------------------------

ComboBox_Imp::  ComboBox_Imp ( pControl req, pDWind_Imp pW, ResID RscID )
	: SingleSelListBox_Imp( req, pW, RscID)
{ 
	ControlName = (char *)CTRL_ComboBox ;
	MessageSet = 1;
}


ComboBox_Imp::  ComboBox_Imp	( pControl req,  pWind_Imp parent, CvID UsrID, Point where, Dimension size, int style )
	:	SingleSelListBox_Imp(req, parent, UsrID, where, size )
{
	MessageSet = 1;
    ControlStyle &= ~WS_CLIPSIBLINGS;		//2.2
    ControlStyle &= ~WS_CLIPCHILDREN;		//2.2

    switch ( style )
    {
        case 0: SetStyle ( CBS_SIMPLE |  WS_VSCROLL | WS_BORDER  ); break ;
        case 1: SetStyle ( CBS_DROPDOWN |  WS_VSCROLL | WS_BORDER  ); break ;
        case 2: SetStyle ( CBS_DROPDOWNLIST |  WS_VSCROLL | WS_BORDER  ); break ;
    }
    ControlName = (char*) CTRL_ComboBox ;
}

void ComboBox_Imp :: Create ()
{
	TextControl_Imp :: Create();
}

void ComboBox_Imp::  Erase()
{
	Rectangle rErase;
if (IsWin31() && IsWindowVisible(hControl) && GetUpdateRect(hControl, (RECT *)&rErase, false))
		{
		Rectangle R;
		GetWindowRect(hControl, (RECT *)&R);

		HDC hWndDC = GetDCEx (hControl,0,  DCX_CACHE | DCX_LOCKWINDOWUPDATE | DCX_PARENTCLIP | DCX_CLIPSIBLINGS | DCX_CLIPCHILDREN);
		IntersectClipRect(hWndDC,0,0,R.Right() + 1, (R.Bottom() - R.Top()) + 1);
		IntersectClipRect(hWndDC,rErase.Left(),rErase.Top(), rErase.Right(), rErase.Bottom());
		SendMessage(ControlParent -> Handle(), WM_ERASEBKGND, (uint)hWndDC, 0);
		ReleaseDC(hControl,hWndDC);
		}
}

HDWP ComboBox_Imp::  RePosition (HDWP hDefer, BOOL ReSize, BOOL ReDraw)
{
	 if (Valid())
	 {
	 BOOL Dropped = false;
	 BOOL IsSimple = false;

	 // Determine if the ComboBox has a dropped down list which needs to be
	 // looked after
	 ulong Style = (GetWindowLong(hControl, GWL_STYLE) & 
	 				(CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST));

	if ( IsWin31() && (Style != CBS_SIMPLE))
		Dropped = ComboBox_GetDroppedState (hControl);
//	 	Dropped = (bool) SendMessage( hControl, CB_GETDROPPEDSTATE, 0,0);
	else
		IsSimple = true;

	if (IsWin31() && Dropped)
//	    	SendMessage( hControl, CB_SHOWDROPDOWN, false,0);
	    	ComboBox_ShowDropdown (hControl, false);

		hDefer = ListBox_Imp :: RePosition(hDefer, ReSize, false);
		if (Dropped)
   			PostMessage (hControl, CB_SHOWDROPDOWN, true, 0);
	}
	return hDefer;
}

///////////////////////////////////////////////////////////////////////////////
// ADDED: #HK961031
Selection ComboBox_Imp::GetEditSelection (BOOL toClipBoard)
{
	if (ValidateControl()) {
	DWORD dwStart, dwEnd;

		SendMessage (Handle(), CB_GETEDITSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
		if (toClipBoard)
		   	SendMessage (Handle(), WM_COPY, 0, 0);
		return Selection (CoOrd(dwStart), CoOrd(dwEnd));
 	}
	return Selection(0,0);
}

Selection ComboBox_Imp::GetEditSelection (char *buffer, int CopyTxtLen)
{
pchar TxtBuffer;
short first;
short last;
short CopyLen = 0;

   	if (ValidateControl()) {
	DWORD dwStart, dwEnd;

		SendMessage (Handle(), CB_GETEDITSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
		first = short(dwStart);
		last = short(dwEnd);

		if ((last - first) < CopyTxtLen)
		   	CopyLen = (last - first);
		else
	   		CopyLen = CopyTxtLen;

		if (first != last) {
		uint TxtLen = ComboBox_GetTextLength (Handle());

			TxtBuffer = new char[TxtLen + 1];
			if (TxtBuffer == NULL)
				return Selection (0, 0);
    		
			SendMessage (Handle(), WM_GETTEXT, TxtLen + 1, (LPARAM)TxtBuffer);
			if (CopyTxtLen == -1)	{
				CV_strncpy (buffer, &TxtBuffer[first], (last - first));
				buffer[CopyLen] = '\0';
			} else {
				CV_strncpy (buffer, &TxtBuffer[first], CopyLen);
				buffer[CopyLen] = '\0';
			}
			delete [] TxtBuffer;
		}
		return Selection (first, last);
   	}
	return Selection(0,0);
}

void ComboBox_Imp::ChangeEditSelection (Selection select)
{
	if (ValidateControl()) 
		ComboBox_SetEditSel (Handle(), select.Start(), select.End());
}

void ComboBox_Imp::DeleteEditSelected (BOOL toClipBoard)
{
	if (ValidateControl())    // RSDEBUG
	{
		if (toClipBoard)
			SendMessage (Handle(), WM_CUT, 0, 0);
		else
			SendMessage (Handle(), WM_CLEAR, 0, 0);
	}
}

// BEGIN: #HK030317
ComboBoxEx_Imp::ComboBoxEx_Imp (pControl req, pDWind_Imp parent, ResID id)
:	ComboBox_Imp(req, parent, id)
{
	ControlName = (char *)CTRL_ComboBoxEx;
}

ComboBoxEx_Imp::ComboBoxEx_Imp (pControl req, pWind_Imp pW, CvID UsrId, Point pt,
		Dimension dim, int style) 
:	ComboBox_Imp(req, pW, UsrId, pt, dim, style)
{
    ControlName = (char*) CTRL_ComboBoxEx;
}

ComboBoxEx_Imp::~ComboBoxEx_Imp()
{
}

int ComboBoxEx_Imp::DeleteItem(int iIndex)
{
	return (int)::SendMessage(Handle(), CBEM_DELETEITEM, (WPARAM)iIndex, 0);
}

BOOL ComboBoxEx_Imp::GetItem(COMBOBOXEXITEM* pCBItem)
{
	return (int) ::SendMessage(Handle(), CBEM_GETITEM, 0, (LPARAM) pCBItem);
}

int ComboBoxEx_Imp::InsertItem(const COMBOBOXEXITEM* pCBItem)
{
	return (int) ::SendMessage(Handle(), CBEM_INSERTITEM, 0, (LPARAM) pCBItem);
}

BOOL ComboBoxEx_Imp::SetItem(const COMBOBOXEXITEM* pCBItem)
{
	return (int) ::SendMessage(Handle(), CBEM_SETITEM, 0, (LPARAM) pCBItem);
}
// END: #HK030317

FileListBox_Imp::  FileListBox_Imp(pControl req,  pDWind_Imp parent, ResID RscID, ResID FTId)
	: SingleSelListBox_Imp(req, parent, RscID), idpath((uint) FTId)
{
	attrib = 0;
	FileSpec [0] = '\0';
	DefExt [0] = '\0';
}

BOOL FileListBox_Imp::  List ( const char* Path, uint Attributes)
{
    pchar tmp;
    strcpy (FileSpec, Path);
	if (Attributes & 0x8000)			// Test for exclusive bit * 2.1 *
	    attrib = Attributes | 0x2000;  
	else
	    attrib = Attributes | 0x2020;  
        // If attribute 0x2000 is used then List box messages arising from 
        // this operation are queued rather than sent directly
        // to the dialog dispatcher.

	if ((tmp = strrchr(FileSpec, '.')) && (strlen(tmp) < 5))
        strcpy ( DefExt, tmp);
    return   DlgDirList( CV_RunTime :: Window_Handle(ControlParent), 
                            FileSpec, (uint)GetID(), (uint)idpath, attrib);
}

BOOL    FileListBox_Imp::  GetCurrentFile( pchar FileName, int len)
{
    char CurrString[_MAX_PATH+1];
	BOOL isDir = false;

	CurrString[0] ='\0';

	//
	//	DlgDirSelect does not give the return value as specified in 
	// the Windows SDK reference.
	// The actual return values returned are 0 for a normal file
	// and 1 for a drive or directory.
	//
#if !defined(WIN32)
    isDir = DlgDirSelect(CV_RunTime :: Window_Handle(ControlParent), 
                    CurrString, GetWindowWord(Handle(), GWW_ID));
#else    
    isDir = DlgDirSelectEx (CV_RunTime :: Window_Handle(ControlParent), 
                    CurrString, _MAX_PATH, GetWindowLong(Handle(), GWL_ID));
#endif
    CV_strncpy(FileName, CurrString,len);

	// FileName [0] will be non-zero if any selection was present.
	return (bool)(FileName[0]);
}

FlbStatus FileListBox_Imp::  Validate( pchar FileName, int len)
{
	int NameLen;
	int LastChar;
	OFSTRUCT pof;
	uint tmpID;

	NameLen = strlen(FileName);
	LastChar = *AnsiPrev( FileName, FileName + NameLen);
#if !defined(WIN32)
	tmpID = GetWindowWord(Handle(), GWW_ID);
#else
	tmpID = GetWindowLong(Handle(), GWL_ID);
#endif

	if ((LastChar == '\\') || (LastChar == ':'))
		{
		CV_strcat( FileName, FileSpec);
		LastChar = '\\';
		}

	if (CV_strchr (FileName, '*') || CV_strchr(FileName, '?'))
		{
		if ( DlgDirList( CV_RunTime :: Window_Handle(ControlParent),
							FileName, tmpID, idpath, attrib))
			{
			pchar tmp;
			if ((tmp = strrchr(FileName,'\\'))
				|| ( tmp = strrchr(FileName,':')))
				{
				strcpy(FileSpec, ++tmp);
				strcpy(FileName, FileSpec);
				}
			else
				strcpy(FileSpec, FileName);
			if ((tmp = strrchr(FileSpec, '.')) && (strlen(tmp) < 5))
				strcpy ( DefExt, tmp);
			}
		else
			MessageBeep(0);
		return FlbFileExpanded;
		}

	if (LastChar != '\\')
		{
		CV_strcat(FileName, StaticPtr("\\"));
		CV_strcat(FileName, FileSpec);
		}

	if ( DlgDirList( CV_RunTime :: Window_Handle(ControlParent),
						FileName, tmpID, idpath, attrib))
		{
		strcpy(FileName, FileSpec);
		return FlbFileExpanded;
		}

	FileName [ NameLen ] = '\0';
	if ((-1) == OpenFile( FileName, &pof, OF_PARSE))
		return FlbFileInvalid;
	if ((-1) == OpenFile( FileName, &pof, OF_READ | OF_EXIST))
		{
		CV_strcat(FileName, DefExt);
		if ((-1) == OpenFile( FileName, &pof, OF_READ | OF_EXIST))
			{
			FileName [ NameLen ] = '\0';
			return FlbFileNotFound;
			}
		}
	strcpy ( FileName, pof.szPathName);
	return FlbFileOk;
}


// ******************************** TLBox_Imp *******************

extern "C"
{  
    #include <stdarg.h>
    #include <stdio.h>
    #include <string.h>
}

TLBox_Imp :: TLBox_Imp (Control * req,pDWind_Imp parent , ResID id, int cols )
            : SingleSelListBox_Imp( req, parent, id)
{
    NoCols = cols;
    TabStop = new int[NoCols];
    TabsSet = false;
    for (int i = 0; i< NoCols; i++)
        TabStop[i] = (i+1) * 8;  // Default
}


void ListBox_Imp :: SetTabStops ()
{
int * tabs = new int[NoCols];

	if (tabs) {
		TabsSet = true;

		// Current implementation does not require getting the system metrics
		/*
	    HANDLE MyDC;
	    TEXTMETRIC MyMet;
    
	    MyDC = ::GetDC(hControl);
    	GetTextMetrics (MyDC, &MyMet);
    	ReleaseDC(hControl, MyDC); 
    	long baseUnit = GetDialogBaseUnits();
    	int width = LoWord(baseUnit);
    	int horizDialogUnit = width /4;
		*/

		for (int i = 0; i <  NoCols; i++)
// !!! LS removed to try Solution to setting tabstops as outlined in tips file
//        tabs[i] = ((TabStop[i] * MyMet.tmMaxCharWidth ) / horizDialogUnit);
//        tabs[i] = ((TabStop[i] * MyMet.tmAveCharWidth ) / horizDialogUnit);
			tabs[i] = (TabStop[i] * 4);

//	SendMessage(hControl, LB_SETTABSTOPS, NoCols, (long)tabs);
		ListBox_SetTabStops (hControl, NoCols, tabs);
    		delete tabs;
	}
} 

TLBox_Imp :: TLBox_Imp (Control* req, pWind_Imp parent , CvID id, Point p, Dimension d, int cols)
                : SingleSelListBox_Imp ( req, parent, id, p, d )
{
    SetStyle (LBS_USETABSTOPS);
    NoCols = cols;
    TabsSet = false;
    TabStop = new int[cols];
    for (int i = 0; i< NoCols; i++)
        TabStop[i] = (i+1) * 8;  // Default
}

int ListBox_Imp ::  AddRow (int row , char* arg_start)
{
va_list arg_marker;

int retval;
int  RowLen = 0;
char * Row;
int i;
char * RowToAdd;

if (ValidateControl())
{
    if (!TabsSet)
        SetTabStops();
    
    arg_marker =(va_list)arg_start;

    for (i = 0; i< NoCols; i++)
    {
        Row = (char*)va_arg (arg_marker, char *);
        RowLen =  (RowLen + strlen(Row) + 1); // Length of string + Tab
    }
        va_end(arg_marker);

    if (RowToAdd = new char [RowLen +1])
	{
//		RowToAdd[0]= '\0';
		memset(RowToAdd, '\0',(RowLen+1));

    	arg_marker =(va_list)arg_start;

    	for (i = 0; i< NoCols; i++)
    	{
        	Row = (char*)va_arg (arg_marker, char *);
    		uint field_width = (i ? (TabStop[i] - TabStop[i - 1]) : TabStop[0]);
        	if 	( strlen (Row) >= field_width)
#ifndef __BCPLUSPLUS__
            	strncat(RowToAdd,Row, field_width);
#else
			// The following section of code may be needed to solve problems
			// which were present under Borland C++ 3.0.
			// These may not be present under Borland 3.1
        	{
             tmp_str = new char[strlen(Row)+1]; 
             strcpy (tmp_str, Row);
             tmp_str[field_width] = '\0';   // hack for Borland strncat problem !!! LS
             strcat (RowtoAdd, tmp_str);
             if (tmp_str)
                delete tmp_str;
        	}
#endif
        	else
				{
            	strcat (RowToAdd, Row);
        		strcat (RowToAdd, "\t");
				}
    	}
        va_end(arg_marker);
    
    	retval = AddString (RowToAdd, row); 
    	delete RowToAdd;
		}
    return retval;
    }
return (-1);
}



BOOL ListBox_Imp ::  GetRow (int index, char *arg_start )
{ 
char * buff = 0;
char * arg_buff  = 0;
char **column_buff = 0;
int Strlen;

// Get row into buffer 'buff'

if (ValidateControl())
{
//	if ((Strlen =  (int)SendMessage ( Handle (), (UINT)LB_GETTEXTLEN, (WPARAM)index, 0L)) == LB_ERR)
	if ((Strlen = ListBox_GetTextLen (Handle(), index)) == LB_ERR)
		return false;
	arg_buff = buff = new char[Strlen +1];

//	if (SendMessage ( Handle (), LB_GETTEXT, index, (ulong)buff ) == LB_ERR) {
	if (ListBox_GetText (Handle(), index, buff) == LB_ERR) {
		delete buff;
		return false;
	}

// create array of columns
	column_buff = new char*[NoCols];

va_list arg_marker;
	
	arg_marker =(va_list)arg_start;
	for ( int i = 0; i< NoCols; i++)
	{
	        column_buff[i]  = (char*)va_arg (arg_marker, char *);
		if (column_buff[i] == NULL)	// #HK940221
			continue;
	    	column_buff[i][0] = '\0';
	}

int char_count = 0;
int col_count = 0;

	while (col_count < NoCols)
	{
	int field_len = (col_count ? (TabStop[col_count] - TabStop[col_count - 1]) : TabStop[0]);

		if (column_buff[col_count] == NULL) {
			col_count++;
			while (*arg_buff && *arg_buff != '\t')
				arg_buff++;
			if (*arg_buff == '\t') arg_buff++;
			continue;	// #HK940221
		}
		while((*arg_buff) && (char_count < field_len)
				&& (*arg_buff != '\t'))
					{
					column_buff[col_count][char_count] = (*arg_buff);
					arg_buff++;
					char_count++;
					}
		column_buff[col_count][char_count] ='\0';
		char_count = 0;
		col_count ++;
		if (*arg_buff == '\t') arg_buff++;
		}
	if (buff) delete buff;
    if (column_buff) delete column_buff;
    return true;
	}
return (false);
}

BOOL ListBox_Imp ::  SetColWidth (uint col, uint width)
{
	if (((int)col >= 0) && ((int)col < NoCols))
		{
    	int oldWidth = ((col == 0) ? TabStop[0] : (TabStop[col] - TabStop[ col - 1]));

    	int diff = width - oldWidth;


    	for ( int i = col; i<NoCols; i++ )
 	      	TabStop[i] += diff;
		return true;
		}		
	else
		return false;
}


TLMultiBox_Imp :: TLMultiBox_Imp (Control* req, pWind_Imp parent , CvID id, Point p, Dimension d, int cols)
                : MultiSelListBox_Imp ( req, parent, id, p, d )
{
    SetStyle (LBS_USETABSTOPS);
    NoCols = cols;
    TabsSet = false;
    TabStop = new int[cols];
    for (int i = 0; i< NoCols; i++)
        TabStop[i] = (i+1) * 8;  // Default
}

TLMultiBox_Imp :: TLMultiBox_Imp (Control * req,pDWind_Imp parent , ResID id, int cols )
            : MultiSelListBox_Imp( req, parent, id)
{
    NoCols = cols;
    TabStop = new int[NoCols];
    TabsSet = false;
    for (int i = 0; i< NoCols; i++)
        TabStop[i] = (i+1) * 8;  // Default
}


void ListBox_Imp:: SetStdStyle (int style)
{
	ulong sty = 0;
  	if (Valid())
       sty = GetWindowLong ( hControl, GWL_STYLE);

    switch (style)
    {
    case (int) BaseListBox::UnSorted :
          ControlStyle	&=~LBS_SORT;
          sty	&=~LBS_SORT;
          break;  

    case (int) BaseListBox::SortedAscending :
          ControlStyle	|= LBS_SORT;
          sty	|= LBS_SORT;
          SortDescending = false;  
          break;

    case (int) BaseListBox::SortedDescending :
          ControlStyle	|= LBS_SORT;
          sty	|= LBS_SORT;
          SortDescending = true;  
          break;

    default:
         break;
    }

  if (Valid())
       SetWindowLong ( hControl, GWL_STYLE, sty); 
}


void ComboBox_Imp:: SetStdStyle (int style)		//2.3
{
	ulong sty = 0;
  	if (Valid())
       sty = GetWindowLong ( hControl, GWL_STYLE);

    switch (style)
    {
    case (int) BaseListBox::UnSorted :
          ControlStyle	&=~CBS_SORT;
          sty	&=~CBS_SORT;
          break;  

    case (int) BaseListBox::SortedAscending :
          ControlStyle	|= CBS_SORT;
          sty	|= CBS_SORT;
          SortDescending = false;  
          break;

    case (int) BaseListBox::SortedDescending :
          ControlStyle	|= CBS_SORT;
          sty	|= CBS_SORT;
          SortDescending = true;  
          break;

    default:
         break;
    }

  if (Valid())
       SetWindowLong ( hControl, GWL_STYLE, sty ); 
}

ListBox_Imp :: ~ ListBox_Imp() 
{
	if (TabStop)
    	delete TabStop;
}

FileListBox_Imp :: ~ FileListBox_Imp() {}
MultiSelListBox_Imp :: ~ MultiSelListBox_Imp() {}
SingleSelListBox_Imp :: ~ SingleSelListBox_Imp() {}
ComboBox_Imp :: ~ ComboBox_Imp() {}
						    
HBRUSH ListBox_Imp :: SetColors(HDC hDC, uint type)
{ 
	return TextControl_Imp :: SetColors(hDC, type); 
}
#if _MSC_VER >= 1200		// #HK990130
DWORD ListBox_Imp::GetItemData (int iIndex)
{
	CV_ASSERT(-1 != iIndex);
	return (DWORD)SendMessage(Handle(), LBMessages[lbGetItemData][MessageSet], iIndex, 0L);
}

int ListBox_Imp::SetItemData (int iIndex, DWORD dwData)
{
	CV_ASSERT(-1 != iIndex);
	return SendMessage(Handle(), LBMessages[lbSetItemData][MessageSet], iIndex, dwData);
}
#endif // _MSC_VER >= 1200	// #HK990130
