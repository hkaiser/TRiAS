// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.09.2000 19:27:31 
//
// @doc
// @module TRiASDropTarget.h | Declaration of the <c CTRiASDropTarget> class

#if !defined(_TRIASDROPTARGET_H__F074102A_16E9_44EC_A864_8F44825934AF__INCLUDED_)
#define _TRIASDROPTARGET_H__F074102A_16E9_44EC_A864_8F44825934AF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/map>

#include "ConnectParams.h"

///////////////////////////////////////////////////////////////////////////////
// special droptarget which accepts CF_HDROP's from shell

class CTRiASDropTarget 
{
public:
	typedef map<os_string, CConnectParams, less<os_string> > CExtensions;

public:
	CTRiASDropTarget() : 
		m_rgDropEffect(DROPEFFECT_NONE), m_fHasExts(false)
	{
	}
	~CTRiASDropTarget() {}

	DROPEFFECT OnDragEnter(IDataObject *pDataObj, DWORD dwKeyState, CPoint point);
	DROPEFFECT OnDragOver(DWORD dwKeyState, CPoint point);
	BOOL OnDrop(DROPEFFECT dropEffect, CPoint point);
	void OnDragLeave();

protected:
	HRESULT EnsureFileExtensionList();
	HRESULT InitFileExtensionList(REFGUID rGuid);

private:
	DROPEFFECT m_rgDropEffect;
	CExtensions m_lstExts;
	bool m_fHasExts;
};

#endif // !defined(_TRIASDROPTARGET_H__F074102A_16E9_44EC_A864_8F44825934AF__INCLUDED_)
