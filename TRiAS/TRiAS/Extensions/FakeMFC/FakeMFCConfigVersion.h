// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.03.2001 21:06:13 
//
// @doc
// @module FakeMFCConfigVersion.h | Declaration of the <c CFakeMFCConfigVersion> class

#if !defined(_FAKEMFCCONFIGVERSION_H__B42D848E_2F6A_4601_B5B3_77778914A883__INCLUDED_)
#define _FAKEMFCCONFIGVERSION_H__B42D848E_2F6A_4601_B5B3_77778914A883__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// angedockte Tabs verwenden
#if _TRiAS_VER >= 0x0410
#define _USE_DOCKEDTABWINDOW
#endif // _TRiAS_VER >= 0x0410

///////////////////////////////////////////////////////////////////////////////
// ProjektValues-Fenster etc. implementieren (war nur in 0x0410 hier)
#if defined(_USE_DOCKEDTABWINDOW) && defined(_DEBUG) && _TRiAS_VER < 0x0420
#define _USE_PROJECTVALUES
#endif // defined(_USE_DOCKEDTABWINDOW) && defined(_DEBUG)

#endif // !defined(_FAKEMFCCONFIGVERSION_H__B42D848E_2F6A_4601_B5B3_77778914A883__INCLUDED_)
