///////////////////////////////////////////////////////////////////////////
// @doc 
// @module ChangeValueHelper.h | Description goes here

#if !defined(_CHANGEVALUEHELPER_H__4C789283_C130_11D2_9B9A_006008447800__INCLUDED_)
#define _CHANGEVALUEHELPER_H__4C789283_C130_11D2_9B9A_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <LockCS.h>

// Hält die Kopien des alten und neuen Wertes, sowie den Verweis auf
// die zu bearbeitende Variable
template<class T, class X = T>
class CChangeValueHelper
{
public:
	CChangeValueHelper (X &rValue, T NewValue) : 
		m_rTarget(rValue), m_OldValue((T)rValue), m_NewValue(NewValue), 
		m_fIsValid(false), m_fIsAssigned(false)
	{
	}
	~CChangeValueHelper () 
	{ 
		if (m_fIsAssigned && !m_fIsValid) 
			Rollback(); 
	}

	void SetValid() { m_fIsValid = true; }

	bool ShouldAssign() { return !m_fIsAssigned && m_OldValue != m_NewValue; }
	bool operator! () { return ShouldAssign(); }
	operator bool () { return !ShouldAssign(); }

	CComVariant GetOldValue() { return CComVariant(m_OldValue); }
	CComVariant GetNewValue() { return CComVariant(m_NewValue); }

	const T &OldValue() const { return m_OldValue; }
	const T &NewValue() const { return m_NewValue; }

	HRESULT Assign()
	{
		if (!m_fIsAssigned) { 
			m_rTarget = (X) m_NewValue; 
			m_fIsAssigned = true; 
			return S_OK;
		}
		return S_FALSE;
	}
	HRESULT Assign(T newVal)
	{
		if (!m_fIsAssigned) { 
			m_NewValue = newVal;
			m_rTarget = (X) m_NewValue; 
			m_fIsAssigned = true; 
			return S_OK;
		}
		return S_FALSE;
	}

protected:
	void Rollback() { m_rTarget = (X) m_OldValue; }

	X &m_rTarget;
	T m_OldValue;
	T m_NewValue;
	bool m_fIsValid;
	bool m_fIsAssigned;
};

#endif // !defined(_CHANGEVALUEHELPER_H__4C789283_C130_11D2_9B9A_006008447800__INCLUDED_)
