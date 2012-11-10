// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.11.1999 20:35:17 
//
// @doc
// @module GUIDHelpers.h | Declaration of GUID helper operators

#if !defined(__GUID_HELPERS_H_B209B6E1_B501_11d2_98E0_0060085FC1CE)
#define __GUID_HELPERS_H_B209B6E1_B501_11d2_98E0_0060085FC1CE

inline bool operator< (const GUID &g1,const GUID &g2) 
{
	return memcmp (&g1, &g2, sizeof(GUID)) < 0 ? true : false;
}

#if !defined(_OBJBASE_H_)		// <objbase.h>
inline bool operator== (const GUID &g1,const GUID &g2) 
{
	return memcmp (&g1, &g2, sizeof(GUID)) == 0 ? true : false;
}
#endif

#endif // __GUID_HELPERS_H_B209B6E1_B501_11d2_98E0_0060085FC1CE
