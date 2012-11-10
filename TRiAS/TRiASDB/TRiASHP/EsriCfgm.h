// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 24.07.2000 11:56:33 
//
// @doc
// @module EsriCfgm.h | Declaration of the <c CEsriCfg> class

#if !defined(_ESRICFGM_H__69A1FA29_710C_4859_99E9_376F0413CEAC__INCLUDED_)
#define _ESRICFGM_H__69A1FA29_710C_4859_99E9_376F0413CEAC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_bool.h"
#include "yy_errgn.h"
#include "yy_inp.h"

#include <ospace/stlex/pointainer.h>
#include "NodeRef.h"

///////////////////////////////////////////////////////////////////////////////
// Die Map, in der die gesamte Konfiguration gespeichert werden soll

class CEsriCfg
{
public:
	typedef map<int, CNode *, less<int> > CNodePtrMap;
	typedef pointainer<CNodePtrMap, clean_pair_second<CNodePtrMap> > CNodeMap;		// die Gesamte Konfiguration

	CEsriCfg() : m_dVersion(0.0) {}
	~CEsriCfg() {}

	void SetVersion (double dVer) { m_dVersion = dVer; }
	double GetVersion() const { return m_dVersion; }

	HRESULT AddNode (CNode *pNode);

private:
	double m_dVersion;		// Version dieser Konfiguration (z.B. 3.1)
	CNodeMap m_NodeMap;		// die Menge aller KonfigurationsNodes
};

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
inline BYTE BinInteger (T_INTEGER *pInteger)
{
char cbBuffer[32];

	ltoa (pInteger -> yy_integer(), cbBuffer, 10);
	return strtol (cbBuffer, NULL, 2);
}

#endif // !defined(_ESRICFGM_H__69A1FA29_710C_4859_99E9_376F0413CEAC__INCLUDED_)
