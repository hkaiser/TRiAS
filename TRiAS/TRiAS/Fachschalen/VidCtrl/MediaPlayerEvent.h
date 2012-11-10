// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 02.07.2002 11:09:36 
//
// @doc
// @module MediaPlayerEvent.h | Declaration of the <c CMediaPlayerEvent> class

#if !defined(_MEDIAPLAYEREVENT_H__F557FE04_7ACC_4B6F_959C_9F007966DC23__INCLUDED_)
#define _MEDIAPLAYEREVENT_H__F557FE04_7ACC_4B6F_959C_9F007966DC23__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// _MediaPlayerEvent dispinterface
//dispinterface _MediaPlayerEvents {
//    properties:
//    methods:
//        [id(0x000005e1), helpstring("DVD related notifications")]
//        void DVDNotify(
//                        [in] long EventCode, 
//                        [in] long EventParam1, 
//                        [in] long EventParam2);
//        [id(0x00000bba), helpstring("Sent when the end of file is reached")]
//        void EndOfStream([in] long Result);
//        [id(0xfffffda6), helpstring("Sent when a key is pressed")]
//        void KeyDown(
//                        [in] short KeyCode, 
//                        [in] short ShiftState);
//        [id(0xfffffda4), helpstring("Sent when a key is released")]
//        void KeyUp(
//                        [in] short KeyCode, 
//                        [in] short ShiftState);
//        [id(0xfffffda5), helpstring("Sent when a character is entered")]
//        void KeyPress([in] short CharacterCode);
//        [id(0xfffffda2), helpstring("Sent when the mouse is moved")]
//        void MouseMove(
//                        [in] short Button, 
//                        [in] short ShiftState, 
//                        [in] OLE_XPOS_PIXELS x, 
//                        [in] OLE_YPOS_PIXELS y);
//        [id(0xfffffda3), helpstring("Sent when a mouse button is pressed")]
//        void MouseDown(
//                        [in] short Button, 
//                        [in] short ShiftState, 
//                        [in] OLE_XPOS_PIXELS x, 
//                        [in] OLE_YPOS_PIXELS y);
//        [id(0xfffffda1), helpstring("Sent when a mouse button is released")]
//        void MouseUp(
//                        [in] short Button, 
//                        [in] short ShiftState, 
//                        [in] OLE_XPOS_PIXELS x, 
//                        [in] OLE_YPOS_PIXELS y);
//        [id(0xfffffda8), helpstring("Sent when a mouse button is clicked")]
//        void Click(
//                        [in] short Button, 
//                        [in] short ShiftState, 
//                        [in] OLE_XPOS_PIXELS x, 
//                        [in] OLE_YPOS_PIXELS y);
//        [id(0xfffffda7), helpstring("Sent when a mouse button is double clicked")]
//        void DblClick(
//                        [in] short Button, 
//                        [in] short ShiftState, 
//                        [in] OLE_XPOS_PIXELS x, 
//                        [in] OLE_YPOS_PIXELS y);
//        [id(0x00000bc3), helpstring("Sent when the control changes OpenState")]
//        void OpenStateChange(
//                        [in] long OldState, 
//                        [in] long NewState);
//        [id(0x00000bc4), helpstring("Sent when the control changes PlayState")]
//        void PlayStateChange(
//                        [in] long OldState, 
//                        [in] long NewState);
//        [id(0x00000bb9), helpstring("Sent when a synchronized command or URL is received")]
//        void ScriptCommand(
//                        [in] BSTR scType, 
//                        [in] BSTR Param);
//        [id(0x00000bbb), helpstring("Sent when the control begins or ends buffering")]
//        void Buffering([in] VARIANT_BOOL Start);
//        [id(0x00000bc2), helpstring("Sent when the control has an error condition")]
//        void Error();
//        [id(0x00000bbe), helpstring("Sent when a marker is reached")]
//        void MarkerHit([in] long MarkerNum);
//        [id(0x00000bc1), helpstring("Sent when the control encounters a problem")]
//        void Warning(
//                        [in] long WarningType, 
//                        [in] long Param, 
//                        [in] BSTR Description);
//        [id(0x00000bc0), helpstring("Sent when a new stream is started in a channel")]
//        void NewStream();
//        [id(0x00000bbc), helpstring("Sent when the control is disconnected from the server")]
//        void Disconnect([in] long Result);
//        [id(0x00000002), helpstring("Indicates that the current position of the movie has changed")]
//        void PositionChange(
//                        [in] double oldPosition, 
//                        [in] double newPosition);
//        [id(0x00000033), helpstring("Indicates that the display mode of the movie has changed")]
//        void DisplayModeChange();
//        [id(0xfffffd9f), helpstring("Reports that the ReadyState property of the ActiveMovie Control has changed")]
//        void ReadyStateChange([in] ReadyStateConstants ReadyState);
//};

///////////////////////////////////////////////////////////////////////////////
// DISPID's für _MediaPlayerEvent
#define DISPID_WMP_BUFFERING				3003	// Sent when the control begins or ends buffering
#define DISPID_WMP_CLICK					-600	// Sent when a mouse button is clicked
#define DISPID_WMP_DBLCLICK					-601	// Sent when a mouse button is double clicked
#define DISPID_WMP_DISCONNECT				3004	// Sent when the control is disconnected from the server
#define DISPID_WMP_DISPLAYMODECHANGE		51		// Indicates that the display mode of the movie has changed
#define DISPID_WMP_DVDNOTIFY				1505	// DVD related notifications
#define DISPID_WMP_ENDOFSTREAM				3002	// Sent when the end of file is reached
#define DISPID_WMP_ERROR					3010	// Sent when the control has an error condition
#define DISPID_WMP_KEYDOWN					-602	// Sent when a key is pressed
#define DISPID_WMP_KEYPRESS					-603	// Sent when a character is entered
#define DISPID_WMP_KEYUP					-604	// Sent when a key is released
#define DISPID_WMP_MARKERHIT				3006	// Sent when a marker is reached
#define DISPID_WMP_MOUSEDOWN				-605	// Sent when a mouse button is pressed
#define DISPID_WMP_MOUSEMOVE				-606	// Sent when the mouse is moved
#define DISPID_WMP_MOUSEUP					-607	// Sent when a mouse button is released
#define DISPID_WMP_NEWSTREAM				3008	// Sent when a new stream is started in a channel
#define DISPID_WMP_OPENSTATECHANGE			3011	// Sent when the control changes OpenState
#define DISPID_WMP_PLAYSTATECHANGE			3012	// Sent when the control changes PlayState
#define DISPID_WMP_POSITIONCHANGE			2		// Indicates that the current position of the movie has changed
#define DISPID_WMP_READYSTATECHANGE			-609	// Reports that the ReadyState property of the ActiveMovie Control has changed
#define DISPID_WMP_SCRIPTCOMMAND			3001	// Sent when a synchronized command or URL is received
#define DISPID_WMP_WARNING					3009	// Sent when the control encounters a problem

///////////////////////////////////////////////////////////////////////////////
// ButtonState in Click, DblClick etc.
#define WMP_BUTTON_LEFT		0x01
#define WMP_BUTTON_MIDDLE	0x02
#define WMP_BUTTON_RIGHT	0x04

#endif // !defined(_MEDIAPLAYEREVENT_H__F557FE04_7ACC_4B6F_959C_9F007966DC23__INCLUDED_)
