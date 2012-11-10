// Wrapper zum Zwischenspeichern eines Wertes
// File: ScopeVar.h

#if !defined(_SCOPEVAR_H)
#define _SCOPEVAR_H

template<class T>
class CScopeVar : 
	public CComAutoCriticalSection 
{
private:
	T &m_rVar;
	T m_oldValue;

public:
	CScopeVar (T &rVar, T newValue) : m_rVar(rVar) 
		{ Lock(); m_oldValue = rVar; rVar = newValue; Unlock(); }
	~CScopeVar (void) { Lock(); m_rVar = m_oldValue; Unlock(); }

	T GetOldValue() { return m_oldValue; }
};

#endif // _SCOPEVAR_H
