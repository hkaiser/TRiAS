// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.12.2000 23:07:42 
//
// @doc
// @module DataHelp.h | Diverse Hilfsfunktionen

#if !defined(_DATAHELP_H__6A69AE8D_236A_4465_9DC8_36010934BB08__INCLUDED_)
#define _DATAHELP_H__6A69AE8D_236A_4465_9DC8_36010934BB08__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Daten in einen Stream Schreiben/von dort lesen
template<class T>
inline HRESULT LoadData (IStream *pIStm, T &riVal)
{
	return pIStm -> Read (&riVal, sizeof(T), NULL);
}

template<class T>
inline HRESULT SaveData (IStream *pIStm, T &riVal)
{
	return pIStm -> Write (&riVal, sizeof(T), NULL);
}

// backwards compatibility functions
inline HRESULT LoadLong (IStream *pIStm, long &riVal) { return LoadData (pIStm, riVal); }
inline HRESULT SaveLong (IStream *pIStm, long iVal) { return SaveData (pIStm, iVal); }

///////////////////////////////////////////////////////////////////////////////
// strings laden/schreiben
_TRIAS03_ENTRY HRESULT LoadString (IStream *pIStm, os_string &rStr);
_TRIAS03_ENTRY HRESULT SaveString (IStream *pIStm, os_string str);
_TRIAS03_ENTRY DWORD GetSizeMax (os_string &rStr);

#endif // !defined(_DATAHELP_H__6A69AE8D_236A_4465_9DC8_36010934BB08__INCLUDED_)
