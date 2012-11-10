// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.12.2000 23:02:20 
//
// @doc
// @module RechResultORWnd.h | Declaration of the <c CRechResultORWnd> class

#if !defined(_RECHRESULTORWND_H__5855C5A7_B919_4BE4_AAFB_97947A3F78F7__INCLUDED_)
#define _RECHRESULTORWND_H__5855C5A7_B919_4BE4_AAFB_97947A3F78F7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <SelectObjectProperty.h>

///////////////////////////////////////////////////////////////////////////////
// Vorgeben der anzuzeigenden Rechercheergebnisse
class CRechResultORWndDlg :
	public DialogWindow
{
public:
	CRechResultORWndDlg(pWindow pW);
	~CRechResultORWndDlg();

	HRESULT GetSelectedObjProp (IObjectProperty **ppIOP);
	HRESULT SetSelectedObjProp (IObjectProperty *pIOP);
	HRESULT SetSelectedObjPropName (LPCSTR pcName);
	int GetNewFlags();
	void SetFlags (int iFlags);

protected:
	void ButtonClick (ControlEvt e);
	
private:
	CSelectObjectProperty m_ObjPropSrc;

	CheckBox m_cbIdent;
	CheckBox m_cbObjTyp;
	CheckBox m_cbDataSource;
	CheckBox m_cbObjProp;

	DWORD m_fFlags;
	os_string m_strActOProp;	// derzeit selektierte Objekteigenschaft
};

#endif // !defined(_RECHRESULTORWND_H__5855C5A7_B919_4BE4_AAFB_97947A3F78F7__INCLUDED_)
