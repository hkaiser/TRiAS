/* $Header:   G:/cv.win/pvcs/commonvu/src/_control.cxv   3.0   25 Mar 1992 15:18:44   RONAN  $
 *
 *	_ c o n t r o l . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	1.0	hl		20jun90	A requestor form of former _control.cxx from which it has been created.
 *	1.1	rs		22jun90	tidying up and integration.
 *						Changed implementation to store control in lists as
 *						implementor.
 */

/* 0.11 Begin */

/* 0.11 End */

#include "tfrmpre.hxx"
#include	<_Link.hxx>			   				


_DLLENTRY Control::  Control( pDialogWindow parent, ResID RscID , const char * RegClass)
{
	control_Imp = new Control_Imp(this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), RscID, 0); 
}


_DLLENTRY Control::  Control	( pWindow parent, CvID UsrID, Point where, Dimension size , const char *RegClass, ulong InitStyle)
{
 	control_Imp = new Control_Imp( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size , RegClass,0);
}

#if defined(WIN32)
BOOL Control :: FInit (void)
{
	if (control_Imp) {
		control_Imp -> Create();
		return true;
	}

return false;
}
#endif


pWindow _DLLENTRY Control :: GetParent()
{
	return control_Imp->GetParent();
}

LRESULT _DLLENTRY Control::ForwardEvent (Event e)
{
	return SendMessage (Handle(), CV_RunTime::Event_wMsg(e),
		CV_RunTime::Event_wParam(e),CV_RunTime::Event_lParam(e));
}

void _DLLENTRY Control::PostEvent (Event e)		// #HK960915
{
	PostMessage (Handle(), CV_RunTime::Event_wMsg(e),
		CV_RunTime::Event_wParam(e),CV_RunTime::Event_lParam(e));
}

// #HK970903
LRESULT _DLLENTRY Control :: ForwardEvent (UINT wMsg, WPARAM wParam , LPARAM lParam)
{
	return ::SendMessage (Handle(), wMsg, wParam, lParam);
}

void _DLLENTRY Control::PostEvent (UINT wMsg, WPARAM wParam , LPARAM lParam)		// #HK970903
{
	::PostMessage (Handle(), wMsg, wParam, lParam);
}
// #HK970903

Point	 _DLLENTRY Control:: 	GetPosition()
{
	return	control_Imp->GetPosition();
}

Dimension	 _DLLENTRY Control:: 	GetSize()
{
	return	control_Imp->GetSize();
}


void	 _DLLENTRY Control::  Show	()
{
	control_Imp->Show(true);
}


void  _DLLENTRY Control ::   Hide ()
{
	control_Imp->Show(false);
}

void  _DLLENTRY Control ::   Enable ()
{
 	control_Imp->Enable(true);
}

void  _DLLENTRY Control ::   Disable ()
{
 	control_Imp->Enable(false);
}


void	 _DLLENTRY Control::  SetStyle	( ulong style )
{
 	control_Imp->SetStyle(style);
}


CvID	 _DLLENTRY Control::  GetID	()
{
	return 	control_Imp->GetID();
}


void	 _DLLENTRY Control::  SetFocus	()
{
	control_Imp->SetFocus( );
}


Dimension  _DLLENTRY Control::  ChangeSize (Dimension NewSize)
{
	return 	control_Imp->ChangeSize( NewSize);
}

Point  _DLLENTRY Control::  ChangePosition (Point p)
{
	return 	control_Imp->ChangePosition( p);
}

pBrush  _DLLENTRY Control::  ChangeBackground(pBrush pBr)
{
	return control_Imp -> ChangeBackground(pBr);
}

 _DLLENTRY Control::  ~Control	()
{
	if (control_Imp)
		delete	control_Imp;
}

// ----------------------------- FixedIcon ----------------------------------

 _DLLENTRY FixedIcon::  FixedIcon	( pWindow parent, CvID UsrID, Point where, ResID id )	// 0.12
{
	control_Imp = new FixedIcon_Imp( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, id); 
}

 _DLLENTRY FixedIcon::  FixedIcon	( pDialogWindow parent, ResID id)
{
	control_Imp = new FixedIcon_Imp( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), id);
}


// ----------------------------- ScrollBar ----------------------------------

 _DLLENTRY ScrollBar::  ScrollBar (pDialogWindow pW, ResID RscID ) 
{
	control_Imp = new ScrollB_Imp ( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(pW), RscID);

}	// End of "ScrollBar" CONSTRUCTOR "(pDialogWindow, ResID)"


 _DLLENTRY ScrollBar::  ScrollBar	( pWindow parent, CvID UsrID, Point where, Dimension size )
{
	control_Imp = new ScrollB_Imp ( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size);
	
}	// End of "ScrollBar" CONSTRUCTOR "(pWindow,uint,Point,Dimension)"


 _DLLENTRY ScrollBar::  ~ScrollBar()
{
	if (control_Imp)
		{
		delete (pScrollB_Imp)control_Imp;
		control_Imp = 0;
		}
}



uint	 _DLLENTRY ScrollBar:: 	GetBlock ()
{ 
	return ((pScrollB_Imp)control_Imp)->GetBlock(); 
	
}

void	 _DLLENTRY ScrollBar:: 	SetBlock(uint b)				
{
	((pScrollB_Imp)control_Imp)->SetBlock(b);	  
	
}

uint	 _DLLENTRY ScrollBar:: 	GetUnit  ()				
{
	return	((pScrollB_Imp)control_Imp)->GetUnit();
	
}

void	 _DLLENTRY ScrollBar:: 	SetUnit  ( uint u )		
{
	((pScrollB_Imp)control_Imp)->SetUnit(u);
	
}



int	 _DLLENTRY ScrollBar::  GetThumbPos	() 
{
	return	((pScrollB_Imp)control_Imp)->GetThumbPos( );
	
}	// End of "ScrollBar" FUNCTION "GetPos"

void	 _DLLENTRY ScrollBar::  SetThumbPos	( int where )			// * 0.5 *
{
	((pScrollB_Imp)control_Imp)->SetThumbPos(  where);

}	// End of "ScrollBar" FUNCTION "SetPos"


Range	 _DLLENTRY ScrollBar::  GetRange	()
{
	return	((pScrollB_Imp)control_Imp)->GetRange( );


}	// End of "ScrollBar" FUNCTION "GetRange"


void	 _DLLENTRY ScrollBar::  SetRange	( Range range )
{
	((pScrollB_Imp)control_Imp)->SetRange (  range);

}	// End of "ScrollBar" FUNCTION "GetRange"


uint _DLLENTRY ScrollBar::GetPageSize (void)						// #HK960411
{
	return	((pScrollB_Imp)control_Imp)->GetPageSize();
}	// End of "ScrollBar" FUNCTION "GetPageSize"

int _DLLENTRY ScrollBar::SetPageSize (uint uiSize, BOOL fRedraw)	// #HK960411
{
	return ((pScrollB_Imp)control_Imp)->SetPageSize (uiSize, fRedraw);
}	// End of "ScrollBar" FUNCTION "SetPageSize"

int	_DLLENTRY ScrollBar::GetTrackPos (void)							// #HK960411
{
	return ((pScrollB_Imp)control_Imp)->GetTrackPos();
}	// End of "ScrollBar" FUNCTION "GetTrackPos"


// ----------------------------- VertScrollBar ------------------------------

 _DLLENTRY VertScrollBar::  VertScrollBar	( pWindow parent, CvID UsrID, Point where, Dimension size )
{
	control_Imp = new VScrollB_Imp ( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where,	size);

}	// End of "VertScrollBar" CONSTRUCTOR "(pWindow,uint,Point,Dimension)"

 _DLLENTRY VertScrollBar::  VertScrollBar	(pDialogWindow pW, ResID RscID ) 
{
	control_Imp = new VScrollB_Imp (this,(pDWind_Imp)CV_RunTime :: pWindow_to_pImp(pW), RscID);

}	// End of "VertScrollBar" CONSTRUCTOR "(pDialogWindow ResID)" 

	
 _DLLENTRY WndVertScrollBar ::   WndVertScrollBar ( pWindow parent)  
{
	control_Imp = new WndVScrollB_Imp(this, CV_RunTime :: pWindow_to_pImp(parent));
}
	

// ----------------------------- HorizScrollBar -----------------------------

 _DLLENTRY HorizScrollBar::  HorizScrollBar	( pWindow parent, CvID UsrID, Point where, Dimension size )

{
	control_Imp = new HScrollB_Imp( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size);

}	// End of "HorizScrollBar" CONSTRUCTOR "(pWindow,uint,Point,Dimension)"

 _DLLENTRY HorizScrollBar::  HorizScrollBar	(pDialogWindow pW, ResID RscID ) 
{
	control_Imp = new HScrollB_Imp (this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(pW), RscID);

}	// End of "HorizScrollBar" CONSTRUCTOR "(pDialogWindow ResID)" 

 
 _DLLENTRY WndHorzScrollBar ::   WndHorzScrollBar( pWindow parent)  
{
	control_Imp = new WndHScrollB_Imp(this, CV_RunTime :: pWindow_to_pImp(parent));
	
}
 

												// * 0.7 End *

// ----------------------------- TextControl --------------------------------

 _DLLENTRY TextControl ::   TextControl ( pDialogWindow parent, ResID id )
{
 	control_Imp = new TextControl_Imp(this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), id);
}

 _DLLENTRY TextControl ::   TextControl (  pWindow parent, CvID UsrID, Point where, Dimension size )
{
 	control_Imp = new TextControl_Imp(this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size, 0);
}

void	 _DLLENTRY TextControl::  SetText	( const char* buffer )
{
	((pTextControl_Imp)control_Imp)->SetText(  buffer);
}


void	 _DLLENTRY TextControl::  GetText	( pchar buffer, uint maxlen )
{
	((pTextControl_Imp)control_Imp)->GetText( buffer, maxlen);
}


uint	 _DLLENTRY TextControl::  GetTextLen	()
{
	return	((pTextControl_Imp)control_Imp)->GetTextLen( );
}

pFont	 _DLLENTRY TextControl::  ChangeFont ( pFont font, BOOL rescale ) 
{
	return	((pTextControl_Imp)control_Imp)->ChangeFont( font, rescale );
}

Color  _DLLENTRY TextControl::  ChangeTextColor(Color c)
{
	return ((pTextControl_Imp)control_Imp) -> ChangeTextColor(c);
}


// ----------------------------- Button -------------------------------------

 _DLLENTRY Button::  Button ( pDialogWindow pW, ResID RscID )
{
	control_Imp = new Button_Imp( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(pW), RscID ); 

}

 _DLLENTRY Button::  Button	( pWindow parent, CvID UsrID, Point where, Dimension size, const char* InitText )
{
	control_Imp = new Button_Imp( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size, InitText); 

}	// End of "Button" CONSTRUCTOR "(pWindow,uint,Point,Dimension)"

// ----------------------------- RadioButton --------------------------------

 _DLLENTRY RadioButton::  RadioButton	( pWindow parent, CvID UsrID, Point where, Dimension size, const char* InitText )
{
 	control_Imp = new RadioButton_Imp(this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size, InitText);

}	// End of "RadioButton" CONSTRUCTOR "(pWindow,uint,Point,Dimension)"

 _DLLENTRY RadioButton::  RadioButton ( pDialogWindow pW, ResID RscID )
{
	control_Imp = new RadioButton_Imp( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(pW), RscID ); 

}

BOOL	 _DLLENTRY RadioButton::  GetState	()
{
 	return	((pRadioButton_Imp)control_Imp)->GetState( );

}	// End of "RadioButton" FUNCTION "GetState"


void	 _DLLENTRY RadioButton::  SetState	( BOOL onoff )
{
 	((pRadioButton_Imp)control_Imp)->SetState(  onoff);

}	// End of "RadioButton" FUNCTION "SetState"

// ----------------------------- PushButton ---------------------------------

_DLLENTRY PushButton::  PushButton	( pWindow parent, CvID UsrID, Point where, Dimension size, const char* InitText )
{
	control_Imp = new PushButton_Imp(this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size, InitText);

}	// End of "PushButton" CONSTRUCTOR "(pWindow,uint,Point,Dimension)"


 _DLLENTRY PushButton::  PushButton ( pDialogWindow pW, ResID RscID )
{
	control_Imp = new PushButton_Imp( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(pW), RscID ); 

}

HBITMAP _DLLENTRY PushButton::SetImage (HBITMAP hNewBmp)	// #HK960416
{
 	return ((pPushButton_Imp)control_Imp)->SetImage (hNewBmp);
}

HBITMAP _DLLENTRY PushButton::GetImage (void)
{
 	return ((pPushButton_Imp)control_Imp)->GetImage();
}


// ----------------------------- CheckBox -----------------------------------

 _DLLENTRY CheckBox::  CheckBox	( pWindow parent, CvID UsrID, Point where, Dimension size, const char* InitText )
{
	control_Imp = new CheckBox_Imp(this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size, InitText);

}	// End of "CheckBox" CONSTRUCTOR "(pWindow,uint,Point,Dimension)"


 _DLLENTRY CheckBox::  CheckBox ( pDialogWindow pW, ResID RscID )
{
	control_Imp = new CheckBox_Imp( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(pW), RscID ); 

}

BOOL	 _DLLENTRY CheckBox::  isChecked	()
{
 	return	((pCheckBox_Imp)control_Imp)->isChecked( );

}	// End of "CheckBox" FUNCTION "GetState"


void	 _DLLENTRY CheckBox::  SetChecked	( BOOL onoff )
{
 	((pCheckBox_Imp)control_Imp)->SetChecked( onoff);

}	// End of "CheckBox" FUNCTION "SetState"






// ----------------------------- BaseListBox ------------------------------------




 _DLLENTRY BaseListBox::  BaseListBox	( pWindow parent, CvID UsrID, Point where, Dimension size )
{
	control_Imp = new ListBox_Imp ( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size);

}	// End of "BaseListBox" CONSTRUCTOR "(pWindow,uint,Point,Dimension)"

 _DLLENTRY BaseListBox::  BaseListBox	( pDialogWindow parent, ResID UsrID )
{
	control_Imp = new ListBox_Imp ( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), UsrID);

}	// End of "BaseListBox" CONSTRUCTOR "(pDialogWindow, ResID)"



int	 _DLLENTRY BaseListBox::  AddString	( const char* String, int position )
{
	return ((pListBox_Imp)control_Imp)->AddString(  String, position);

}	// End of "BaseListBox" FUNCTION "AddString"


BOOL	 _DLLENTRY BaseListBox::  DelString	( int StrIndex )
{
	return	((pListBox_Imp)control_Imp)->DelString(  StrIndex);

}	// End of "BaseListBox" FUNCTION "DelString"


int	 _DLLENTRY BaseListBox::  GetCount	()
{
	return	((pListBox_Imp)control_Imp)->GetCount( );

}	// End of "BaseListBox" FUNCTION "GetCount"


BOOL _DLLENTRY BaseListBox:: GetString (pchar buff, int index, int length)
{
    return ((pListBox_Imp)control_Imp)->GetString (buff, index, length);
}  

int _DLLENTRY BaseListBox:: GetStringLength(int index)
{
    return ((pListBox_Imp)control_Imp)->GetLineLen (index);
}  


void _DLLENTRY BaseListBox:: SetTop (uint index)
{
    ((pListBox_Imp)control_Imp)->SetTop (index);
}

void _DLLENTRY BaseListBox:: SetStdStyle ( ListBoxStyle style )
{
    ((pListBox_Imp)control_Imp)->SetStdStyle (style );
}

// ------------------------ ListBox --------------------------------------

 _DLLENTRY ListBox::  ListBox	( pWindow parent, CvID UsrID, Point where, Dimension size )
{
	control_Imp = new SingleSelListBox_Imp ( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size);

}	// End of "Single Selection ListBox" CONSTRUCTOR "(pWindow,uint,Point,Dimension)"


 _DLLENTRY ListBox::  ListBox	( pDialogWindow parent, ResID UsrID )
{
	control_Imp = new SingleSelListBox_Imp ( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), UsrID);

}	// End of "Single Selection ListBox" CONSTRUCTOR "(pDialogWindow, ResID)"


int	 _DLLENTRY ListBox::  GetCurrentIndex	()
{
	return	((SingleSelListBox_Imp*)control_Imp)->GetCurrentIndex( );

}	// End of "BaseListBox" FUNCTION "GetCurrentIndex"


BOOL	 _DLLENTRY ListBox::  ChangeCurrentIndex ( int index )
{
	return	((SingleSelListBox_Imp*)control_Imp)->ChangeCurrentIndex(  index );

}	// End of "BaseListBox" FUNCTION "ChangeCurrentIndex"



BOOL	 _DLLENTRY ListBox::  GetCurrentString	( pchar String, int len)
{
	return	((SingleSelListBox_Imp*)control_Imp)->GetString( String, -1, len);
	
}	// End of "ListBox" FUNCTION "GetCurrentString"


void       _DLLENTRY BaseListBox::  Clear (  ) 
{
	((pListBox_Imp)control_Imp)->Clear();
}

int         _DLLENTRY BaseListBox::  FindString ( const char * str, BOOL prefix ) 
{
	return	((pListBox_Imp)control_Imp)->FindString( str, prefix );
}


// -------------------------- MultiSelListBox ---------------------------------

_DLLENTRY MultiSelListBox:: MultiSelListBox()
{
}

 _DLLENTRY MultiSelListBox::  MultiSelListBox	( pWindow parent, CvID UsrID, Point where, Dimension size )
{
	control_Imp = new MultiSelListBox_Imp ( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size);

}	// End of "Multi Selection ListBox" CONSTRUCTOR "(pWindow,uint,Point,Dimension)"



 _DLLENTRY MultiSelListBox::  MultiSelListBox	( pDialogWindow parent, ResID UsrID )
{
	control_Imp = new MultiSelListBox_Imp ( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), UsrID);

}	// End of "Multi Selection ListBox" CONSTRUCTOR "(pDialogWindow, ResID)"


int _DLLENTRY MultiSelListBox:: GetNoSelected()
{   
	return	((MultiSelListBox_Imp*)control_Imp)->GetNoSelected( );
}

BOOL _DLLENTRY MultiSelListBox:: ClearSelected ()
{
	return	((MultiSelListBox_Imp*)control_Imp)->ClearSelected( );
}
int _DLLENTRY MultiSelListBox:: GetFirstSelected ()
{
	return	((MultiSelListBox_Imp*)control_Imp)->GetFirstSelected();
}

int _DLLENTRY MultiSelListBox:: GetNextSelected()
{
	return	((MultiSelListBox_Imp*)control_Imp)->GetNextSelected( );
}

BOOL _DLLENTRY MultiSelListBox:: ChangeSelected (int index, BOOL setting)
{
	return	((MultiSelListBox_Imp*)control_Imp)->ChangeSelected(  index, setting );
}

BOOL _DLLENTRY MultiSelListBox:: ChangeSelected (Range range, BOOL setting)
{
	return	((MultiSelListBox_Imp*)control_Imp)->ChangeSelected(  range, setting );
}


short _DLLENTRY MultiSelListBox:: GetCaretIndex (void)
{
	return	((MultiSelListBox_Imp*)control_Imp)->GetCaretIndex();
}

BOOL _DLLENTRY MultiSelListBox:: SetCaretIndex (short iIndex, BOOL fScroll)
{
	return	((MultiSelListBox_Imp*)control_Imp)->SetCaretIndex(iIndex, fScroll);
}

BOOL _DLLENTRY MultiSelListBox:: GetSelection (short iIndex)
{
	return	((MultiSelListBox_Imp*)control_Imp)->GetSelection(iIndex);
}

int	 _DLLENTRY MultiSelListBox::FindString (const char *pText, BOOL fWhole, int iStart)
{
	return ((MultiSelListBox_Imp*)control_Imp)->FindString(pText, fWhole, iStart);
}

// ----------------------------- Edit ---------------------------------------

 _DLLENTRY Edit::  Edit	( pWindow parent, CvID UsrID, Point where, Dimension size )
{
	control_Imp = new Edit_Imp( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size);

}	// End of "Edit" CONSTRUCTOR "(pWindow,uint,Point,Dimension)"

 _DLLENTRY Edit::  Edit	( pDialogWindow parent, ResID UsrID )
{
	control_Imp = new Edit_Imp ( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), UsrID);

}	// End of "Edit" CONSTRUCTOR "(pDialogWindow, ResID)"

BOOL	 _DLLENTRY Edit::  isModified	()
{
	return	((pEdit_Imp)control_Imp)->isModified( );

}	// End of "Edit" FUNCTION "isModified"

void	 _DLLENTRY Edit::  SetModified	(BOOL SetTo)  // 3.0
{
	((pEdit_Imp)control_Imp)->SetModified( SetTo );

}	// End of "Edit" FUNCTION "SetModified"

Selection	 _DLLENTRY Edit::  GetSelection	( BOOL toClipBoard)
{
	return	((pEdit_Imp)control_Imp)->GetSelection( toClipBoard );

}	// End of "Edit" FUNCTION "GetSelection"


Selection	 _DLLENTRY Edit::  GetSelection	( pchar buffer, int TxtLen )
{
	return	((pEdit_Imp)control_Imp)->GetSelection( buffer, TxtLen );

}	// End of "Edit" FUNCTION "GetSelection"

void	 _DLLENTRY Edit::  ChangeSelection	( Selection select )
{
	((pEdit_Imp)control_Imp)->ChangeSelection(  select);

}	// End of "Edit" FUNCTION "ChangeSelection"


void	 _DLLENTRY Edit::  SetTextLimit ( uint nChars )
{
	((pEdit_Imp)control_Imp)->SetTextLimit( nChars);

}	// End of "Edit" FUNCTION "SetTextLimit"


BOOL	 _DLLENTRY Edit::  ReplaceSelected	( const char* text )
{ 
	return ((pEdit_Imp)control_Imp)->ReplaceSelected(  text );

}	// End of "Edit" FUNCTION "ReplaceSelected"


void	 _DLLENTRY Edit::  DeleteSelected ( BOOL toClipBoard)
{
	((pEdit_Imp)control_Imp)->DeleteSelected( toClipBoard );

}	// End of "Edit" FUNCTION "DeleteSelected"


BOOL	 _DLLENTRY Edit::  Undo	()
{
	return	((pEdit_Imp)control_Imp)->Undo( );
	
}	


BOOL	 _DLLENTRY Edit::  CanUndo ()
{
	return	((pEdit_Imp)control_Imp)->CanUndo( );
	
}	

void    _DLLENTRY Edit:: SetStdStyle( EditStyle style )
{
	((pEdit_Imp)control_Imp)->SetStdStyle( style );
}
    

// ----------------------------- MultiLineEdit ------------------------------

 _DLLENTRY MultiLineEdit::  MultiLineEdit	( pWindow parent, CvID UsrID, Point where, Dimension size )
{
	control_Imp = new MultiLineEdit_Imp(this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size);

}

 _DLLENTRY MultiLineEdit::  MultiLineEdit	( pDialogWindow parent, ResID UsrID )
{
	control_Imp = new MultiLineEdit_Imp ( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), UsrID);
}

uint	 _DLLENTRY MultiLineEdit::  GetLine	( int index, pchar buffer, uint nChars )
{
	return	((pMultiLineEdit_Imp)control_Imp)->GetLine( index, buffer, nChars);

}	// End of "MultiLineEdit" FUNCTION "GetLine"


uint	 _DLLENTRY MultiLineEdit::  GetLineLength	( int index )
{
	return ((pMultiLineEdit_Imp)control_Imp)->GetLineLength(  index);

}	// End of "Edit" FUNCTION "GetLineLength"


uint	 _DLLENTRY MultiLineEdit::  GetNumLines	()
{
	return	((pMultiLineEdit_Imp)control_Imp)->GetNumLines( );
	
}	// End of "MultiLineEdit" FUNCTION "GetNumLines"

void	 _DLLENTRY MultiLineEdit::  ScrollVertical	( int nLines )
{
	((pMultiLineEdit_Imp)control_Imp)->ScrollVertical(  nLines);

}	// End of "MultiLineEdit" FUNCTION "ScrollVertical"


void	 _DLLENTRY MultiLineEdit::  ScrollHoriz	( int nChars )
{
	((pMultiLineEdit_Imp)control_Imp)->ScrollHoriz(  nChars);

}	// End of "MultiLineEdit" FUNCTION "ScrollHoriz"


void	 _DLLENTRY MultiLineEdit::  PageUp	()
{
	((pMultiLineEdit_Imp)control_Imp)->PageUp( );

}	// End of "MultiLineEdit" FUNCTION "PageUp"


void	 _DLLENTRY MultiLineEdit::  PageDown	()
{
	((pMultiLineEdit_Imp)control_Imp)->PageDown( );

}	// End of "MultiLineEdit" FUNCTION "PageDown"

 
void	 _DLLENTRY MultiLineEdit::  LineUp	()
{
	((pMultiLineEdit_Imp)control_Imp)->LineUp( );
	
}	// End of "MultiLineEdit" FUNCTION "LineUp"


void	 _DLLENTRY MultiLineEdit::  LineDown	()
{
	((pMultiLineEdit_Imp)control_Imp)->LineDown( );

}	// End of "MultiLineEdit" FUNCTION "LineDown"

void _DLLENTRY MultiLineEdit:: SetMultiStyle ( MultiLineStyle style )
{
	((pMultiLineEdit_Imp)control_Imp)->SetMultiStyle( style );
}

// ----------------------------- SingleLineEdit -----------------------------

 _DLLENTRY SingleLineEdit::  SingleLineEdit	( pWindow parent, CvID UsrID, Point where, Dimension size )
{
	control_Imp = new SingleLineEdit_Imp(this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size);
}	

 _DLLENTRY SingleLineEdit::  SingleLineEdit	( pDialogWindow parent, ResID UsrID )
{
	control_Imp = new SingleLineEdit_Imp ( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), UsrID);

}	// End of "SingleLineEdit" CONSTRUCTOR "(pDialogWindow, ResID)"

#if defined(WIN32)
_DLLENTRY SingleLineEdit :: SingleLineEdit (pWindow parent, HWND hWnd)
{
	control_Imp = new SingleLineEdit_Imp (this, CV_RunTime :: pWindow_to_pImp(parent), hWnd); 
}
#endif

// ----------------------------- FixedText ----------------------------------

 _DLLENTRY FixedText::  FixedText	( pWindow parent, CvID UsrID, Point where, Dimension size, const char* TextName )	// 0.12
{
	control_Imp = new FixedText_Imp ( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size, TextName);

}	// End of "FixedText" CONSTRUCTOR "(pWindow,uint,Point,Dimension,const char*)"	// 0.12

 _DLLENTRY FixedText::  FixedText	( pDialogWindow parent, ResID UsrID )
{
	control_Imp = new FixedText_Imp ( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), UsrID);

}	// End of "FixedText" CONSTRUCTOR "(pDialogWindow, ResID)"


 _DLLENTRY FixedText ::  ~FixedText()	// * 1.8 start *
{
	delete (pFixedText_Imp)control_Imp;
	control_Imp = 0;		
}								// * 1.8 end *


void _DLLENTRY FixedText:: SetStdStyle( FixedTextStyle style )
{
     ((pFixedText_Imp)control_Imp)->SetStdStyle( style);
}

HWND	 _DLLENTRY Control::  Handle ( Service s_ID )
{
	if(NULL == this) return NULL;	// GetSafeHandle !!

	return control_Imp -> Handle(s_ID);
} 
					 

// ----------------------------- ComboBox ------------------------------


 _DLLENTRY ComboBox::  ComboBox	( pWindow parent, CvID UsrID, Point where, Dimension size , ComboStyle style)
{
	control_Imp = new ComboBox_Imp( this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size, (int) style);
}

 _DLLENTRY ComboBox::  ComboBox	( pDialogWindow parent, ResID UsrID )
{
	control_Imp = new ComboBox_Imp ( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), UsrID );
}

///////////////////////////////////////////////////////////////////////////////
// ADDED: #HK961031
Selection ComboBox::GetEditSelection (BOOL toClipBoard)
{
	return ((ComboBox_Imp *)control_Imp)->GetEditSelection(toClipBoard);
}

Selection ComboBox::GetEditSelection (char *pBuffer, int TextLen)
{
	return ((ComboBox_Imp *)control_Imp)->GetEditSelection (pBuffer, TextLen);
}

void ComboBox::ChangeEditSelection (Selection s)
{
	((ComboBox_Imp *)control_Imp)->ChangeEditSelection (s);
}

void ComboBox::DeleteEditSelected (BOOL toClipBoard)
{
	((ComboBox_Imp *)control_Imp)->DeleteEditSelected (toClipBoard);
}

// BEGIN:#HK030317
_DLLENTRY ComboBoxEx::ComboBoxEx(pWindow parent, CvID UsrID, Point where, 
	Dimension size, ComboStyle style)
{
	control_Imp = new ComboBoxEx_Imp(this, CV_RunTime::pWindow_to_pImp(parent), 
		UsrID, where, size, (int) style);
}

_DLLENTRY ComboBoxEx::ComboBoxEx (pDialogWindow parent, ResID UsrID)
{
	control_Imp = new ComboBoxEx_Imp (this, 
		(pDWind_Imp)CV_RunTime::pWindow_to_pImp(parent), UsrID);
}

_DLLENTRY ComboBoxEx::~ComboBoxEx()
{
}

_DLLENTRY int ComboBoxEx::DeleteItem(int iIndex)
{
	return ((ComboBoxEx_Imp *)control_Imp)->DeleteItem(iIndex);
}

_DLLENTRY BOOL ComboBoxEx::GetItem(COMBOBOXEXITEM* pCBItem)
{
	return ((ComboBoxEx_Imp *)control_Imp)->GetItem(pCBItem);
}

_DLLENTRY int ComboBoxEx::InsertItem(const COMBOBOXEXITEM* pCBItem)
{
	return ((ComboBoxEx_Imp *)control_Imp)->InsertItem(pCBItem);
}

_DLLENTRY BOOL ComboBoxEx::SetItem(const COMBOBOXEXITEM* pCBItem)
{
	return ((ComboBoxEx_Imp *)control_Imp)->SetItem(pCBItem);
}
// END: #HK030317

// ------------------------ GroupBox -----------------------------------------
_DLLENTRY GroupBox:: GroupBox (pDialogWindow parent, ResID id)
{
	control_Imp = new GroupBox_Imp ( this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), id );
}

_DLLENTRY GroupBox::GroupBox (pWindow parent , CvID id , Point where, Dimension size, const char *text)
{
	control_Imp = new GroupBox_Imp( this, CV_RunTime :: pWindow_to_pImp(parent), id, where, size, text);
}


// #HK940125: GaugeControl ----------------------------------------------------
_DLLENTRY GaugeBox :: GaugeBox (pWindow parent, CvID UsrID, Point where, Dimension size, const char *pIniText)
{
	control_Imp = new GaugeBox_Imp (this, CV_RunTime :: pWindow_to_pImp(parent), UsrID, where, size, pIniText);
}

_DLLENTRY GaugeBox :: GaugeBox (pDialogWindow parent, ResID UsrID)
{
	control_Imp = new GaugeBox_Imp (this, (pDWind_Imp)CV_RunTime :: pWindow_to_pImp(parent), UsrID);
}


void	_DLLENTRY GaugeBox :: SetRange (short iRange)
{
	((GaugeBox_Imp*)control_Imp)->SetRange (iRange);
}

void	_DLLENTRY GaugeBox :: SetPosition (short iPos)
{
	((GaugeBox_Imp*)control_Imp)->SetPosition (iPos);
}


void	_DLLENTRY GaugeBox :: SetOrientation (short iOrient)
{
	((GaugeBox_Imp*)control_Imp)->SetOrientation (iOrient);
}


void	_DLLENTRY GaugeBox :: SetDeltaPos (short iDelta)
{
	((GaugeBox_Imp*)control_Imp)->SetDeltaPos (iDelta);
}


void	_DLLENTRY GaugeBox :: SetFColor (Color C)
{
	((GaugeBox_Imp*)control_Imp)->SetFColor (C);
}


void	_DLLENTRY GaugeBox :: SetBkColor (Color C)
{
	((GaugeBox_Imp*)control_Imp)->SetBkColor (C);
}


void 	_DLLENTRY GaugeBox :: Set3DWidth (short iWidth)
{
	((GaugeBox_Imp*)control_Imp)->Set3DWidth (iWidth);
}


void 	_DLLENTRY GaugeBox :: SetBezelFace (short iWidth)
{
	((GaugeBox_Imp*)control_Imp)->SetBezelFace (iWidth);
}


	
short	_DLLENTRY GaugeBox :: GetRange (void)
{
	return ((GaugeBox_Imp*)control_Imp)->GetRange();
}


short	_DLLENTRY GaugeBox :: GetPosition (void)
{
	return ((GaugeBox_Imp*)control_Imp)->GetPosition();
}

short	_DLLENTRY GaugeBox :: GetOrientation (void)
{
	return ((GaugeBox_Imp*)control_Imp)->GetOrientation();
}

Color	_DLLENTRY GaugeBox :: GetFColor (void)
{
	return ((GaugeBox_Imp*)control_Imp)->GetFColor();
}

Color	_DLLENTRY GaugeBox :: GetBkColor (void)
{
	return ((GaugeBox_Imp*)control_Imp)->GetBkColor();
}

short	_DLLENTRY GaugeBox :: Get3DWidth (void)
{
	return ((GaugeBox_Imp*)control_Imp)->Get3DWidth();
}

short	_DLLENTRY GaugeBox :: GetBezelFace (void)
{
	return ((GaugeBox_Imp*)control_Imp)->GetBezelFace();
}

