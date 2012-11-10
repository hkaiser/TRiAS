// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.10.2000 19:33:13 
//
// @doc
// @module HotKey.cpp | Definition of the <c CHotKey> class

#include "tfrmpre.hxx"

CHotKeyCtrl::CHotKeyCtrl (pDialogWindow parent, ResID UsrID)
{
	control_Imp = new CHotKeyCtrl_Imp (this, (pDWind_Imp)CV_RunTime::pWindow_to_pImp(parent), UsrID);
}

CHotKeyCtrl::CHotKeyCtrl (pWindow parent, CvID UsrID, Point where, Dimension size, DWORD dwInitStyle)
{
	control_Imp = new CHotKeyCtrl_Imp (this, 
				CV_RunTime::pWindow_to_pImp(parent), 
				UsrID, where, size, 
				dwInitStyle|WS_CHILD|WS_CLIPSIBLINGS);
}

CHotKeyCtrl::~CHotKeyCtrl()
{
}

CHotKeyCtrl_Imp :: CHotKeyCtrl_Imp (pControl req, pWind_Imp parent, CvID UsrID, 
			Point where, Dimension size, DWORD dwInitStyle)
		   : Control_Imp (req, parent, UsrID, where, size, 
		   		  (const char*)CTRL_HotkeyCtrl, dwInitStyle)
{
}

CHotKeyCtrl_Imp :: CHotKeyCtrl_Imp (pControl req, pDWind_Imp pW, ResID RscID)
		   : Control_Imp (req, pW, RscID, (const char*)CTRL_AnimateCtrl)
{
}

CHotKeyCtrl_Imp :: ~CHotKeyCtrl_Imp (void)
{
}

