// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 07/17/1998 10:08:15 AM
//
// @doc
// @module KoOrd.h | Datentyp einer Koordinate

#if !defined(_KOORD_H__68ED7E73_1D4C_11D2_9E96_006008447800__INCLUDED_)
#define _KOORD_H__68ED7E73_1D4C_11D2_9E96_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if defined(_KOORD_ISDOUBLE)
typedef double	KoOrd;
const KoOrd MAXKOORD = 1073741824.0;	// maximal möglicher KoOrdinatenwert
#else
typedef long	KoOrd;					// Koordinate
const KoOrd MAXKOORD = 1073741824L;		// maximal möglicher KoOrdinatenwert
#endif // _KOORD_ISDOUBLE

#endif // !defined(_KOORD_H__68ED7E73_1D4C_11D2_9E96_006008447800__INCLUDED_)
