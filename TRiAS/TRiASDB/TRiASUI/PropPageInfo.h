// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/09/1998 03:17:47 PM
//
// @doc
// @module PropPageInfo.h | Description goes here

#if !defined(_PROPPAGEINFO_H__3825AB64_5F4E_11D2_9ED9_006008447800__INCLUDED_)
#define _PROPPAGEINFO_H__3825AB64_5F4E_11D2_9ED9_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPropPageInfo :
	public PROPPAGEINFO
{
public:
	CPropPageInfo()
	{
		memset (this, '\0', sizeof(PROPPAGEINFO));
		cb = sizeof(PROPPAGEINFO);
	}
	~CPropPageInfo()
	{
		Tidy();
	}
	PROPPAGEINFO *operator& () { Tidy(); return this; }

protected:
	void Tidy()
	{
		if (NULL != pszTitle) {
			CoTaskMemFree(pszTitle);
			pszTitle = NULL;
		}
		if (NULL != pszDocString) {
			CoTaskMemFree(pszDocString);
			pszDocString = NULL;
		}
		if (NULL != pszHelpFile) {
			CoTaskMemFree(pszHelpFile);
			pszHelpFile = NULL;
		}
	}
};

#endif // !defined(_PROPPAGEINFO_H__3825AB64_5F4E_11D2_9ED9_006008447800__INCLUDED_)
