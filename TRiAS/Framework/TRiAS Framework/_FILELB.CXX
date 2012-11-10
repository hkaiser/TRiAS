/* $Header:   G:/cv.win/pvcs/commonvu/src/_filelb.cxv   3.0.1.0   14 Jul 1992 11:55:32   RONAN  $
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
 *  1.2 hl		20jun90 hiding
 */
#include "tfrmpre.hxX"
#include <stdarg.h>

_DLLENTRY ListBox::   ListBox()
{
}

#if _MSC_VER >= 1200
// #HK990130
_DLLENTRY DWORD BaseListBox::GetItemData (int iIndex)
{
	return ((pListBox_Imp)control_Imp) -> GetItemData (iIndex);
}

_DLLENTRY int BaseListBox::SetItemData (int iIndex, DWORD dwData)
{
	return ((pListBox_Imp)control_Imp) -> SetItemData (iIndex, dwData);
}
// #HK990130
#endif // _MSC_VER >= 1200

_DLLENTRY FileListBox::   FileListBox( pDialogWindow parent, ResID RscID, ResID FTId) 
{
	control_Imp = new FileListBox_Imp( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), RscID, FTId);
}

BOOL  _DLLENTRY FileListBox::   List ( const char* Path, uint Attributes)
{
	return	((pFileListBox_Imp)control_Imp)->List(Path, Attributes);

}

BOOL     _DLLENTRY FileListBox::   GetCurrentFile( pchar FileName, int len)
{
	return	((pFileListBox_Imp)control_Imp)->GetCurrentFile ( FileName, len );
}

FlbStatus  _DLLENTRY FileListBox::   Validate( pchar FileName, int len)
{
	return	((pFileListBox_Imp)control_Imp)->Validate(FileName, len);
}

// ************************** TabularListBox *****************************
_DLLENTRY TabularListBox ::  TabularListBox (pDialogWindow parent, ResID UsrID, uint numcols)
{
	control_Imp = new TLBox_Imp ( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), UsrID, numcols);
}

_DLLENTRY TabularListBox :: TabularListBox (pWindow parent, CvID UsrID, Point where , Dimension size, uint numcols)
{
	control_Imp = new TLBox_Imp ( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size, numcols);
}

int _DLLENTRY TabularListBox :: AddRow ( int index , ...)
{
	int retval;
	va_list arg_marker;
	va_start ( arg_marker, index);
	retval = ((TLBox_Imp*)control_Imp)->AddRow(index,(char*)arg_marker );
	va_end(arg_marker);
	return retval;
}

BOOL _DLLENTRY TabularListBox :: GetRow (int index, ... )
{
	bool retval;
	va_list arg_marker;
	va_start ( arg_marker, index);
	retval = ((TLBox_Imp*)control_Imp)->GetRow(index,(char*)arg_marker );
	va_end(arg_marker);
	return retval;
}

void _DLLENTRY TabularListBox :: SetColWidth (uint col, uint width)
{
	((TLBox_Imp*)control_Imp)->SetColWidth(col, width );
}



 // !!! LS
// ************************** MultiSelTabularListBox *****************************

_DLLENTRY MultiSelTabularListBox ::  MultiSelTabularListBox (pDialogWindow parent, ResID UsrID, uint numcols)

{
	control_Imp = new TLMultiBox_Imp ( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), UsrID, numcols);
}
  
_DLLENTRY MultiSelTabularListBox :: MultiSelTabularListBox (pWindow parent, CvID UsrID, Point where , Dimension size, uint numcols)

{
	control_Imp = new TLMultiBox_Imp ( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size, numcols);
}

int _DLLENTRY MultiSelTabularListBox :: AddRow ( int index , ...)
{
	int retval;
	va_list arg_marker;
	va_start ( arg_marker, index);
	retval = ((TLMultiBox_Imp*)control_Imp)->AddRow(index,(char*)arg_marker );
	va_end(arg_marker);
	return retval;
}

BOOL _DLLENTRY MultiSelTabularListBox :: GetRow (int index, ... )
{
	bool retval;
	va_list arg_marker;
	va_start ( arg_marker, index);
	retval = ((TLMultiBox_Imp*)control_Imp)->GetRow(index,(char*)arg_marker );
	va_end(arg_marker);
	return retval;
}

void _DLLENTRY MultiSelTabularListBox :: SetColWidth (uint col, uint width)
{
	((TLMultiBox_Imp*)control_Imp)->SetColWidth(col, width );
}
