// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.09.2000 22:22:54 
//
// @doc
// @module MatchLastComboBox.h | Declaration of the <c CMatchLastComboBox> class

#if !defined(_MATCHLASTCOMBOBOX_H__11B93D45_F9CA_4E9C_AFC9_507A9EA14948__INCLUDED_)
#define _MATCHLASTCOMBOBOX_H__11B93D45_F9CA_4E9C_AFC9_507A9EA14948__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#ifdef _DEBUG
#undef THIS_FILE
#define THIS_FILE __FILE__
#endif

#include <bmpbtn.hxx>

#include "DataHelp.h"
#include "ComboEditWnd.h"

///////////////////////////////////////////////////////////////////////////////
// 
class CMatchLastComboBox 
{
public:
	typedef list<os_string> CSearchList;
	enum {
		LASTITEMSMAX = 20,		// Anzahl der gespeicherten letzten Suchstrings
	};

public:
	CMatchLastComboBox(DialogWindow *pParent, ResID resCB, ResID resBttn) :  
		m_cbSelect(pParent, resCB), m_SelExpr(pParent, resBttn)
	{
		m_pEdit = NULL;
		m_pParent = pParent;
	}
	~CMatchLastComboBox() 
	{
		DELETE_OBJ(m_pEdit);
	}

	bool FInit() 
	{ 
		if (!m_cbSelect.FInit() || !m_SelExpr.FInit() || 
			!m_SelExpr.LoadBitmaps (IDB_ARROW_DOWN, IDB_ARROW_DOWN_SEL, IDB_ARROW_DOWN_FOCUS, IDB_ARROW_DOWN_DISABLED))
		{
			return false;
		}
		m_SelExpr.SizeToContent(); 

		TX_TRY(m_pEdit = new CComboEditWnd (m_pParent, m_cbSelect));
		return (NULL != m_pEdit) ? true : false;
	}

// operators
	bool InitFromData (os_string &rstrLastItem, CSearchList &rItems)
	{
	// ggf. letzte Einstellung wieder einstellen
		if (rstrLastItem.size() > 0) {
		int iIndex = m_cbSelect.AddString (rstrLastItem.c_str());

			if (iIndex >= 0) 
				m_cbSelect.ChangeCurrentIndex(iIndex);
		}

	// Liste auch noch auf den letzten Stand bringen
		for (CSearchList::iterator it = rItems.begin(); it != rItems.end(); ++it)
		{
			if (!(*it == rstrLastItem))
				m_cbSelect.AddString ((*it).c_str());
		}
		return TRUE;
	}

	bool AddToExprString (LPCSTR pcAdd, int iMoveCursor)
	{
		_ASSERTE(NULL != pcAdd);
			
	Selection s (m_pEdit -> GetLastSelection());
	int iLen = m_cbSelect.GetTextLen();

		try {
		int iAddLen = strlen(pcAdd);
		char cbBuffer[_MAX_PATH];

			m_cbSelect.GetText (cbBuffer, iLen+1);
			cbBuffer[iLen] = '\0';

		string str (cbBuffer);

			if (iLen > 0)
				str.replace (s.Start(), s.End()-s.Start(), pcAdd);
			else 
				str = pcAdd;

		// Control während der Änderungen nicht zeichnen
		HWND hCtrl = m_cbSelect.Handle();

			SendMessage (hCtrl, WM_SETREDRAW, false, 0);
			m_cbSelect.SetFocus();
			m_cbSelect.SetText (str.c_str());
			s.Start() = s.End() = s.Start()+iAddLen+iMoveCursor;
			m_cbSelect.ChangeEditSelection (s);

		// jetzt alles mit einem mal zeichnen
			SendMessage (hCtrl, WM_SETREDRAW, true, 0);
			InvalidateRect (hCtrl, NULL, true);

		} catch (...) {
			return false;
		}
		return true;
	}

	bool SaveData (os_string &rLastItem, CSearchList &rItems)
	{
	char cbBuffer[_MAX_PATH];
	int iMax = m_cbSelect.GetCount();

		for (int i = 0; i < iMax && i < LASTITEMSMAX; i++) {
			if (m_cbSelect.GetString (cbBuffer, i, sizeof(cbBuffer)-1))
				rItems.push_back(os_string(cbBuffer));
		}

		m_cbSelect.GetText(cbBuffer, _MAX_PATH);
		rLastItem = cbBuffer;
		return true;
	}
	bool hasSelection() { return (-1 != m_cbSelect.GetCurrentIndex() || 0 < m_cbSelect.GetTextLen()); }
	os_string GetSelection() 
	{
	char cbBuffer[_MAX_PATH] = { '\0' };

		m_cbSelect.GetText(cbBuffer, sizeof(cbBuffer));
		if ('\0' != cbBuffer[0])
			return os_string(cbBuffer);
		return os_string("");
	}
	Point GetMenuPos() 
	{ 
	Rectangle rc;

		GetWindowRect(m_SelExpr.Handle(API_WINDOW_HWND), (RECT *)&rc); 
		return rc.LowerRight();
	}

// Persistenz
	static HRESULT Load (IStream *pStm, os_string &rLastItem, CSearchList &rItems)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(LoadString(pStm, rLastItem));

		CSearchList::size_type lCnt = 0;

			THROW_FAILED_HRESULT(LoadLong(pStm, (long &)lCnt));
			for (CSearchList::size_type i = 0; i < lCnt; i++) {
			os_string str;

				THROW_FAILED_HRESULT(LoadString(pStm, str));
				rItems.push_back(str);
			}

		} COM_CATCH;
		return S_OK;
	}
	static HRESULT Save (IStream *pStm, os_string &rLastItem, CSearchList &rItems)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(SaveString(pStm, rLastItem));
			THROW_FAILED_HRESULT(SaveLong(pStm, rItems.size()));
			for (CSearchList::iterator it = rItems.begin(); it != rItems.end(); ++it)
			{
				THROW_FAILED_HRESULT(SaveString(pStm, *it));
			}
		} COM_CATCH;
		return S_OK;
	}
	static __int64 GetSizeMax(os_string &rLastItem, CSearchList &rItems)
	{
	__int64 liOwnSize = sizeof(CSearchList::size_type) + ::GetSizeMax (rLastItem);

		for (CSearchList::iterator it = rItems.begin(); it != rItems.end(); ++it)
			liOwnSize += ::GetSizeMax (*it);

		return liOwnSize;
	}

private:
	ComboBox m_cbSelect;
	CComboEditWnd *m_pEdit;		// Editcontrol der Combobox
	CBmpButton m_SelExpr;		// Button neben ComboBox

	DialogWindow *m_pParent;
};

#endif // !defined(_MATCHLASTCOMBOBOX_H__11B93D45_F9CA_4E9C_AFC9_507A9EA14948__INCLUDED_)
