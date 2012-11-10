// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/04/1998 02:28:50 PM
//
// @doc
// @module MouseAction.h | Declaration of the <c CMouseAction> class

#if !defined(_MOUSEACTION_H__E2054A23_4327_11D2_9EBE_006008447800__INCLUDED_)
#define _MOUSEACTION_H__E2054A23_4327_11D2_9EBE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

class CTRiASViewWindow
{
public:
	CTRiASViewWindow()
	{
	}
	virtual ~CTRiASViewWindow()
	{
	}
	operator CWnd* () const
	{
		CWnd* pWnd = g_pTE -> MWind();
		if (NULL == pWnd )
			return NULL;

		// AFX_IDW_PANE_FIRST holen
		pWnd  = pWnd  -> GetDlgItem(AFX_IDW_PANE_FIRST);
		return pWnd;
	}
	CDC*  GetDC()
	{
		// Get Window data
		CWnd * pWnd = operator CWnd* ();		
		CDC * pDC = pWnd -> GetDC();

		return pDC;
	}
	
protected:
	CWnd * m_pWnd;
	void * operator new (UINT size_t) {return NULL;}	// for temporary use only
};

/////////////////////////////////////////////////////////////////////////////
// CDrawAction
// 
// Basisklasse zur Definition eines Interfaces zum Linienzeichnen
// zeichnet garnichts

class CDrawAction
{
public:
	CDrawAction()
	{
		m_x = 0;
		m_y = 0;
		m_bShowLine = false;
	}
	virtual ~CDrawAction()	// for inheritance
	{
		Undo();
	}
	void Init()
	{
		// sucht sich das TRiAS-Hauptfenster
					
	}
	void Undo();
	void SetBase(int x,int y)
	{
		Undo();
		m_x = x;
		m_y = y;
	}
	void Draw(int x, int y)
	{
		Undo();		// alte Linie löschen
		m_xEnd = x;
		m_yEnd = y;
		Line();
		m_bShowLine = true;
	}
	virtual void Line()
	{
		// do your own work with ROP-Code XOR
	}

	CWnd* GetWindow()
	{
		return m_Wnd;
	}
	CDC*  GetDC()
	{
		return m_Wnd.GetDC();
	}	
protected:
	int m_x;
	int m_y;
	int m_xEnd;
	int m_yEnd;
	CTRiASViewWindow m_Wnd;
	bool m_bShowLine;
};

/////////////////////////////////////////////////////////////////////////////
// CRealDrawAction
// 
// zeichnet jetzt die Linie und löscht sie automatisch wieder
// 

class CRealDrawAction
	: public CDrawAction
{
public:
	virtual void Line()
	{
		CDC * pDC = GetDC();

		// prepare
		CPen pen(PS_SOLID, 1, RGB(255, 255, 255));		// schwarzer Stift
		pDC -> SetROP2(R2_XORPEN);		// XOR  -> 1.Mal zeichnen
										//	    -> 2.Mal löschen

		pDC -> MoveTo(m_x, m_y);		// set Turtle to Start
		CPen * pOldPen = pDC -> SelectObject(&pen);
		
		// just do it
		pDC -> LineTo(m_xEnd, m_yEnd); // Zeichnen (move turtle)

		// clean up
		pDC -> SelectObject(pOldPen);
	}
	virtual ~CRealDrawAction()
	{
		Undo();
	}
};

/////////////////////////////////////////////////////////////////////////////
// CMouseAction
class ATL_NO_VTABLE CMouseAction : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CMouseAction, &CLSID_MouseAction>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMouseAction, &IID_IMouseAction, &LIBID_MsgBlastLib>
{
public:
	CMouseAction()
		: m_rgLastKey(MOUSEKEY_Unknown),
			m_OldX(0),
			m_OldY(0)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MOUSEACTION)
	DECLARE_CLASSFACTORY_SINGLETON(CMouseAction)

	BEGIN_COM_MAP(CMouseAction)
		COM_INTERFACE_ENTRY(IMouseAction)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMouseAction
public:
	STDMETHOD(get_LastKey)(/*[out, retval]*/ long *pVal);
	STDMETHOD(GetPointDrag)(/*[in]*/ BSTR Prompt, /*[in, out]*/ double *pdX, /*[in, out]*/ double *pdY);
	STDMETHOD(GetPoint)(/*[in]*/ BSTR Prompt, /*[in, out]*/ double *pdX, /*[in, out]*/ double *pdY);

// Member
private:
	long m_rgLastKey;
	int m_OldX;
	int m_OldY;

// private Methoden
private:
	virtual void MsgProc(CDrawAction& action);
	HRESULT GetPoint(BSTR Prompt, double * pdX, double * pdY, CDrawAction& action);
};

#endif // !defined(_MOUSEACTION_H__E2054A23_4327_11D2_9EBE_006008447800__INCLUDED_)
