// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 29.12.2000 15:17:10 
//
// @doc
// @module MathOperationPropertyDlg.h | Declaration of the <c CMathOperationPropertyDlg> class

#if !defined(_MATHOPERATIONPROPERTYDLG_H__5753A46E_8E5E_40F6_92FC_7E844C8CE727__INCLUDED_)
#define _MATHOPERATIONPROPERTYDLG_H__5753A46E_8E5E_40F6_92FC_7E844C8CE727__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// CMathOperationPropertyDlg dialog

enum MATHOPERATION;

class CMathOperationPropertyDlg : 
	public CPropertyPage<IDD_MATHOP_CONFIG>
{
// Construction
public:
	CMathOperationPropertyDlg();   // standard constructor

// Dialog Data
	enum { IDD = IDD_MATHOP_CONFIG };

// Overrides
public:
	BOOL OnSetActive();
	BOOL OnWizardFinish();

public:
	MATHOPERATION GetMathOp() { return m_rgMathOp; }
	os_string &GetObjProp1() { return m_strObjProp1; }
	os_string &GetObjProp2() { return m_strObjProp2; }
	bool InitFromData (MATHOPERATION rgMathOp, LPCSTR pcName1, LPCSTR pcName2)
	{
		m_rgMathOp = rgMathOp;
		m_strObjProp1 = pcName1;
		m_strObjProp2 = pcName2;
		return true;
	}

// Implementation
protected:

private:
	MATHOPERATION m_rgMathOp;
	os_string m_strObjProp1;
	os_string m_strObjProp2;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_MATHOPERATIONPROPERTYDLG_H__5753A46E_8E5E_40F6_92FC_7E844C8CE727__INCLUDED_)
