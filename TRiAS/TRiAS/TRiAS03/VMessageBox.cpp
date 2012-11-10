// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.12.2000 21:45:23 
//
// @doc
// @module VMessageBox.cpp | globale Funktionen, die bequem eine Messagebox anzeigen

#include "trias03p.hxx"

#include <funcs03.h>
#include <FormatString.h>

StdMessBoxReply VMessageBox (
	Window *pW, LPCSTR pcCaption, StdMessBox rgType, ResID uiText, ...)
{
ResString resFormat (uiText, 2*_MAX_PATH); 
va_list params;
string strRes;

	va_start (params, uiText);
	FormatV (strRes, resFormat, params);
	va_end (params);

MessBox mb (pcCaption, strRes.c_str(), pW);

	mb.SetType (rgType);
	return mb.Show();
}

StdMessBoxReply VMessageBox (
	Window *pW, ResID uiCaption, StdMessBox rgType, ResID uiText, ...)
{
ResString resCaption (uiCaption, _MAX_PATH);
ResString resFormat (uiText, 2*_MAX_PATH); 
va_list params;
string strRes;

	_ASSERTE(resCaption.Len() > 0);
	_ASSERTE(resFormat.Len() > 0);

	va_start (params, uiText);
	FormatV (strRes, resFormat, params);
	va_end (params);

MessBox mb (resCaption, strRes.c_str(), pW);

	mb.SetType (rgType);
	return mb.Show();
}

StdMessBoxReply VMessageBox (
	Window *pW, LPCSTR pcCaption, StdMessBox rgType, LPCSTR pcText, ...)
{
va_list params;
string strRes;

	va_start (params, pcText);
	FormatV (strRes, pcText, params);
	va_end (params);

MessBox mb (pcCaption, strRes.c_str(), pW);

	mb.SetType (rgType);
	return mb.Show();
}

StdMessBoxReply VMessageBox (
	Window *pW, ResID uiCaption, StdMessBox rgType, LPCSTR pcText, ...)
{
ResString resCaption (uiCaption, _MAX_PATH);
va_list params;
string strRes;

	_ASSERTE(resCaption.Len() > 0);

	va_start (params, pcText);
	FormatV (strRes, pcText, params);
	va_end (params);

MessBox mb (resCaption, strRes.c_str(), pW);

	mb.SetType (rgType);
	return mb.Show();
}

string FakeTRiASName (UINT resID, ...)
{
	try {
	ResString resTempl (resID, _MAX_PATH);
	va_list params;
	string strRes;

		va_start (params, resID);
		FormatV (strRes, resTempl, params);
		va_end (params);
		return strRes;
	
	} catch (...) {
	// irgendein Fehler
		return string("");
	}
}

string FakeTRiASName (LPCSTR pcTempl, ...)
{
	try {
	va_list params;
	string strRes;

		va_start (params, pcTempl);
		FormatV (strRes, pcTempl, params);
		va_end (params);
		return strRes;
	
	} catch (...) {
	// irgendein Fehler
		return string("");
	}
}

