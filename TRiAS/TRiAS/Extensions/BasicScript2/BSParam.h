// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/07/1998 03:58:11 PM
//
// @doc
// @module BSParam.h | Lokale Kopie eines BSPARAM-Feldes verwalten

#if !defined(_BSPARAM_H__B736863C_45BF_11D2_9EBE_006008447800__INCLUDED_)
#define _BSPARAM_H__B736863C_45BF_11D2_9EBE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CBSParamCopy 
{
private:
	int m_iNumPars;
	BSPARAM m_Pars;
	bool m_fIsValid;

public:
	CBSParamCopy (int iNumPars, BSPARAM *pPars)
		: m_iNumPars(iNumPars+1), m_fIsValid(false)
	{
		if (NULL != pPars) {
			ATLTRY((m_Pars.pTypes = new ebPARAM[m_iNumPars], m_Pars.pValues = new LPVOID[m_iNumPars]));
			if (NULL != m_Pars.pTypes && NULL != m_Pars.pValues) {
				memcpy (m_Pars.pTypes, pPars -> pTypes, sizeof(ebPARAM)*m_iNumPars);
				memcpy (m_Pars.pValues, pPars -> pValues, sizeof(LPVOID)*m_iNumPars);
				m_fIsValid = true;
			}
		} else {
			m_Pars.pTypes = NULL;
			m_Pars.pValues = NULL; 
		}
	}
	~CBSParamCopy ()
	{
		DELETE_OBJ(m_Pars.pTypes);
		DELETE_OBJ(m_Pars.pValues);
	}

	operator BSPARAM *() { return m_fIsValid ? &m_Pars : NULL; }

	bool RemoveModsParam()
	{
		if (NULL == m_Pars.pTypes || NULL == m_Pars.pValues) 
			return false;

		for (int i = 0; i < m_iNumPars; i++) 
		{
			if (m_Pars.pTypes[i].wType & TYP_MODSPARM)
				m_Pars.pTypes[i].wType &= ~TYP_MODSPARM;
		}
		return true;
	}
};

#endif // !defined(_BSPARAM_H__B736863C_45BF_11D2_9EBE_006008447800__INCLUDED_)
