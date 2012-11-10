///////////////////////////////////////////////////////////////////////////
// @doc 
// @module LockCS.h | Declaration and definition of <c CLockCS> class

#if !defined(_LOCKCS_H__298A1A64_8FDF_11D1_B9FA_080036D63803__INCLUDED_)
#define _LOCKCS_H__298A1A64_8FDF_11D1_B9FA_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

template<class T>
class CLockCS 
{
public:
		CLockCS(T &rCS) : m_rCS(rCS) 
		{
			m_rCS.Lock(); 
		}
		~CLockCS() 
		{ 
			m_rCS.Unlock(); 
		}

private:
	T &m_rCS;
};

#endif // !defined(_LOCKCS_H__298A1A64_8FDF_11D1_B9FA_080036D63803__INCLUDED_)
