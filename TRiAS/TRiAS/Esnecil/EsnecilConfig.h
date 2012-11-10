// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.11.2000 10:10:11 
//
// @doc
// @module EsnecilConfig.h | Declaration of the <c CEsnecilConfig> class

#if !defined(_ESNECILCONFIG_H__18B838A0_72D1_42D2_94EA_68EA9DCF468E__INCLUDED_)
#define _ESNECILCONFIG_H__18B838A0_72D1_42D2_94EA_68EA9DCF468E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// enable Debug output
#if defined(_DEBUG)
#define USE_DLIB
#endif // defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
// z.Zt. bin ich wohl zu blöd dazu ...
// #define _NO_DELAYLOAD_CRP32DLL

#endif // !defined(_ESNECILCONFIG_H__18B838A0_72D1_42D2_94EA_68EA9DCF468E__INCLUDED_)
