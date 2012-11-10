// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/18/1998 02:21:32 PM
//
// @doc
// @module PropNamex.h | Klasse für lange Objekteigenschaftsnamen

#if !defined(_PROPNAMEX_H__89B26764_4EC2_11D2_9EC9_006008447800__INCLUDED_)
#define _PROPNAMEX_H__89B26764_4EC2_11D2_9EC9_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
//
typedef enum tagPROPTYPE {
	UNKNOWN_ROOT = 0,
	OBJPROP_ROOT = 1,
	CLSPROP_ROOT = 2,
} PROPTYPE;

class CPropertyName 
{
private:
	PROPTYPE m_rgType;
	os_string m_strGroup;
	os_string m_strSubGroup;
	os_string m_strName;
	os_string m_strFullName;

	bool m_fhasGroup;
	bool m_fhasSubGroup;
	bool m_fHasFullName;

protected:
	bool ParseName (LPCSTR pcName);

public:
	CPropertyName (void);
	CPropertyName (LPCSTR pcFullName);
	CPropertyName (struct IObjectProperty *pIObjProp);
	CPropertyName (PROPTYPE rgType, LPCSTR pcGroup, 
					   LPCSTR pcSubGroup, LPCSTR pcName);
	inline ~CPropertyName (void) {}

inline	PROPTYPE GetType (void) { return m_rgType; }
inline	os_string &GetGroup (void) { return m_strGroup; }
inline	os_string &GetSubGroup (void) { return m_strSubGroup; }
inline	os_string &GetName (void) { return m_strName; }

inline bool hasGroup() { return m_fhasGroup ? true : false; }
inline bool hasSubGroup() { return m_fhasSubGroup ? true : false; }

	bool GetFullName (os_string &);
	bool GetFullName (LPSTR pBuffer, WORD wLen);
	bool SetType (PROPTYPE rgType);
	bool SetGroup (LPCSTR pcGroup);
	bool SetSubGroup (LPCSTR pcGroup);
	bool SetName (LPCSTR pcName);

	bool operator== (CPropertyName &rP);

friend int Compare (CPropertyName &rP1, CPropertyName &rP2);
};

#endif // !defined(_PROPNAMEX_H__89B26764_4EC2_11D2_9EC9_006008447800__INCLUDED_)
