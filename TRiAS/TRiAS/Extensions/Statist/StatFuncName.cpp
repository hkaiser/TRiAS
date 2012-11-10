// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.02.2001 18:27:38 
//
// @doc
// @module StatFuncName.cpp | Definition of the <c CStatFuncName> class

#include "stdafx.h"
#include "StatFuncName.h"

CStatFuncName::CStatFuncName (void)
{
	m_rgType = UNKNOWN_STATFUNC_ROOT;
	m_fhasGroup = false;
	m_fhasSubGroup = false;
	m_fHasFullName = false;
}

CStatFuncName::CStatFuncName (LPCSTR pcFullName)
{
	m_fHasFullName = false;
	ParseName (pcFullName);
}

CStatFuncName::CStatFuncName (IGenericStatistics *pIStatFunc)
{
	USES_CONVERSION;
	m_fHasFullName = false;

CComBSTR bstrName;
HRESULT hr = pIStatFunc -> get_Name(&bstrName);
os_string strFullName (OLE2A(bstrName));

	if (SUCCEEDED(hr)) 
		ParseName (strFullName.c_str());
	else 
		m_rgType = UNKNOWN_STATFUNC_ROOT;
}

CStatFuncName::CStatFuncName (STATFUNCTYPE rgType, LPCSTR pcGroup, LPCSTR pcSubGroup, LPCSTR pcName)
	: m_rgType(rgType)
{
	m_fHasFullName = false;
	try {
		m_strGroup = pcGroup;
		m_fhasGroup = true;
		m_strName = pcName;

		if (pcSubGroup) {
			m_strSubGroup = pcSubGroup;
			m_fhasSubGroup = true;
		}

	} catch (...) {
		m_rgType = UNKNOWN_STATFUNC_ROOT;
		m_fhasGroup = false;
		m_fhasSubGroup = false;
	}
}

bool CStatFuncName::ParseName (LPCSTR pcName)
{
	m_fHasFullName = false;
	try {
	os_string str (pcName);
	size_t pos = str.find ("\\");

		m_strGroup.remove();
		m_fhasGroup = false;
		m_strSubGroup.remove();
		m_fhasSubGroup = false;
		m_rgType = UNKNOWN_STATFUNC_ROOT;

		if (os_npos == pos) {
		// nur Name gegeben
			m_rgType = STATFUNC_ROOT;
			m_strName = pcName;
			return true;
		}

	// Wurzel feststellen
	os_string sstr = str.substr (0, pos);
	 
		if (sstr == "STATFUNC_ROOT")
			m_rgType = STATFUNC_ROOT;
		else {
			m_rgType = STATFUNC_ROOT;
			return SetName (pcName);	// nur Name/SubGruppe gegeben
		}

	// Gruppe feststellen
	size_t posn = str.find ("\\", pos+1);

		if (os_npos == posn)
			m_strName = str.substr (pos+1);	// keine Gruppe gegeben
		else {
			m_strGroup = str.substr (pos+1, posn-pos-1);
			m_fhasGroup = true;

		size_t posn2 = str.find ("\\", posn+1);

			if (os_npos == posn2) // keine Sub-Gruppe
				m_strName = str.substr (posn+1);
			else {
				m_strSubGroup = str.substr (posn+1, posn2-posn-1);
				m_fhasSubGroup = true;
				m_strName = str.substr (posn2+1);
			}
		}
		return true;

	} catch (...) {
		m_rgType = UNKNOWN_STATFUNC_ROOT;
		return false;
	}
}


bool CStatFuncName::GetFullName (os_string &str)
{
	if (UNKNOWN_STATFUNC_ROOT == m_rgType)
		return false;

	try {
		if (!m_fHasFullName) {
			if (0 < m_strGroup.length()) {
				m_strFullName = "STATFUNC_ROOT\\";
				if (m_fhasGroup) {
					m_strFullName += m_strGroup;
					m_strFullName += "\\";
				}
				if (m_fhasSubGroup) {
					m_strFullName += m_strSubGroup;
					m_strFullName += "\\";
				}
				m_strFullName += m_strName;
			} else
				m_strFullName = m_strName;

			m_fHasFullName = true;
		}
		str = m_strFullName;

	} catch (...) {
		m_fHasFullName = false;
		return false;
	}
	return true;
}

bool CStatFuncName::GetFullName (LPSTR pBuffer, WORD wLen)
{
os_string str;

	if (!GetFullName (str)) return false;

unsigned int iLen = min ((unsigned int)(wLen-1), str.length());

	strncpy (pBuffer, str.c_str(), iLen);
	pBuffer[iLen] = '\0';
	return true;
}

bool CStatFuncName::SetType (STATFUNCTYPE rgType)
{
	switch (rgType) {
	case STATFUNC_ROOT:
	case UNKNOWN_STATFUNC_ROOT:
		m_rgType = rgType;
		return true;

	default:
		_ASSERTE(UNKNOWN_STATFUNC_ROOT != rgType && STATFUNC_ROOT != rgType);
		break;
	}
	return false;
}

bool CStatFuncName::SetGroup (LPCSTR pcGroup)
{
	try {
		if (pcGroup) {
			m_strGroup = pcGroup;
			m_fhasGroup = true;
		} else {
			m_strGroup.remove();
			m_fhasGroup = false;
		}
		m_fHasFullName = false;

	} catch (...) {
		return false;
	}
	return true;
}

bool CStatFuncName::SetSubGroup (LPCSTR pcSubGroup)
{
	try {
		if (pcSubGroup) {
			m_strSubGroup = pcSubGroup;
			m_fhasSubGroup = true;
		} else {
			m_strSubGroup.remove();
			m_fhasSubGroup = false;
		}
		m_fHasFullName = false;

	} catch (...) {
		return false;
	}
	return true;
}

bool CStatFuncName::SetName (LPCSTR pcName)
{
	try {
	os_string str (pcName);
	size_t pos = str.find ("\\");

		if (pos != os_npos) {
			m_strSubGroup = str.substr (0, pos);
			m_fhasSubGroup = true;

			m_strName = str.substr (pos+1);
		} else
			m_strName = pcName;

		m_fHasFullName = false;

	} catch (...) {
		return false;
	}
	return true;
}

bool CStatFuncName::operator== (CStatFuncName &rP)
{
	return 0 == Compare(*this, rP);
}

int Compare (CStatFuncName &rP1, CStatFuncName &rP2)
{
// Bezeichner vergleichen
int iCmp = strcmp (rP1.GetName().c_str(), rP2.GetName().c_str());

	if (iCmp != 0) return iCmp;

// Bezeichner sind identisch, Gruppen vergleichen
	if (rP1.hasGroup() && rP2.hasGroup()) {
		if (iCmp = strcmp (rP1.GetGroup().c_str(), rP2.GetGroup().c_str()))
			return iCmp;
	}

	if (rP1.hasSubGroup() && rP2.hasSubGroup()) {
		if (iCmp = strcmp (rP1.GetSubGroup().c_str(), rP2.GetSubGroup().c_str()))
			return iCmp;
	}

// Typen vergleichen
	if (rP1.GetType() < rP2.GetType())
		return -1;
	if (rP1.GetType() > rP2.GetType())
		return 1;

	return 0;	// alles identisch
}

