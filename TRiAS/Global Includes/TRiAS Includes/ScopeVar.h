// Wrapper zum Zwischenspeichern eines Wertes
// File: ScopeVar.h

#if !defined(_SCOPEVAR_H)
#define _SCOPEVAR_H

#include <LockCS.h>

template<class T>
class CScopeVar : 
	public CComObjectThreadModel::AutoCriticalSection 
{
private:
	T &m_rVar;
	T m_oldValue;
	bool m_fAssigned;

public:
	CScopeVar (T &rVar, T newValue) : m_rVar(rVar), m_fAssigned(false) 
	{
	CLockCS<CComObjectThreadModel::AutoCriticalSection> lock (*this);

		m_oldValue = rVar; 
		if (newValue != rVar) { 
			rVar = newValue; 
			m_fAssigned = true; 
		} 
	}
	~CScopeVar (void) 
	{
		Reset(); 
	}

	T GetOldValue() const { return m_oldValue; }
	void Reset() 
	{ 
	CLockCS<CComObjectThreadModel::AutoCriticalSection> lock (*this);

		if (m_fAssigned) { 
			m_rVar = m_oldValue; 
			m_fAssigned = false; 
		}
	}
	bool operator! () 
		{ CLockCS<CComObjectThreadModel::AutoCriticalSection> lock (*this); return m_fAssigned ? false : true; }
	operator bool() 
		{ CLockCS<CComObjectThreadModel::AutoCriticalSection> lock (*this); return m_fAssigned; }
};

#endif // _SCOPEVAR_H
