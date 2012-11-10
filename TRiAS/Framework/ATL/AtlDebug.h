///////////////////////////////////////////////////////////////////////////
// @doc 
// @module atldebug.h | Debug-HilfsMacros und Debug-HilfsKlaasen

#if !defined(_ATLDEBUG_H__5425EF26_D5D6_11D1_85EF_00600875138A__INCLUDED_)
#define _ATLDEBUG_H__5425EF26_D5D6_11D1_85EF_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef ATL_NO_NAMESPACE
namespace ATL
{
#endif

#if defined(_ATLX_DEBUG_REFCOUNT_WALKSTACK)

#include <PE_Debug.h>
#include <ospace/std/list>
#include <ospace/std/map>
#include <ospace/std/vector>

ATLAPI_(void) AtlWalkStackOnAddRefX (class CStackProbeLists &Lists, DWORD dwCookie, REFIID riid, bool fNotFatal = false);
ATLAPI_(void) AtlWalkStackOnReleaseX (class CStackProbeLists &Lists, DWORD dwCookie, REFIID riid);
ATLAPI_(void) AtlDumpPendingReleasesX (class CStackProbeLists &Lists, REFIID riid);

/////////////////////////////////////////////////////////////////////////////
// Liste von StackWalks, die zu einem Interface/Objekt gehören
class CStackProbeList :
	public vector<BYTE *> 
{
private:
	ULONG m_ulRefCnt;
	bool m_fNotFatal;

public:
	CStackProbeList(bool fNotFatal) : m_fNotFatal(fNotFatal) { m_ulRefCnt = 1; }
	CStackProbeList(const CStackProbeList &rhs)
		: vector<BYTE *>(rhs), m_ulRefCnt(rhs.RefCnt()), m_fNotFatal(rhs.Status()) {}
	~CStackProbeList() {}

	CStackProbeList operator= (const CStackProbeList &rhs)
	{
		if (&rhs != this) {
			(vector<BYTE *> &)(*this) = (vector<BYTE *> &)rhs;
			m_ulRefCnt = rhs.RefCnt();
			m_fNotFatal = rhs.Status();
		}
		return *this;
	}

	ULONG AddRef() { return ++m_ulRefCnt; }
	ULONG Release() { return --m_ulRefCnt; }
	ULONG RefCnt() const { return m_ulRefCnt; }
	bool Status() const { return m_fNotFatal; }
	void SetStatus() { m_fNotFatal = true; }
};

/////////////////////////////////////////////////////////////////////////////
// alle StackWalks aller Interfaces eines Types
class CStackProbeLists :
	public map<DWORD, CStackProbeList *, less<DWORD> >
{
private:
	REFIID m_riid;

public:
	CStackProbeLists(REFIID riid) : m_riid(riid) {}
	~CStackProbeLists()
	{
		AtlDumpPendingReleasesX(*this, m_riid);
	}
};

///////////////////////////////////////////////////////////////////////////////
// special class as replacement for CComPtr<>
template <class T, class ID>
class CComPtrDebug : 
	public CComPtr<T>
{
public:
	typedef T _PtrClass;
	CComPtrDebug() {}
	CComPtrDebug(T* lp) : CComPtr<T>(lp) { if (p) WalkStackOnAddRef(); }
	CComPtrDebug(const CComPtrDebug<T, ID>& lp) : CComPtr<T>(lp)
		{ if (p) WalkStackOnAddRef(); }
	~CComPtrDebug() { if (p) WalkStackOnRelease(); }
	void Release() { if (p) WalkStackOnRelease(); CComPtr<T>::Release(); }

	T* operator=(T* lp){return (T*)AtlComPtrAssignStackWalk((IUnknown**)&p, lp);}
	T* operator=(const CComPtrDebug<T, ID>& lp)
		{ return (T*)AtlComPtrAssignStackWalk((IUnknown**)&p, lp.p); }
	IUnknown* AtlComPtrAssignStackWalk (IUnknown** pp, IUnknown* lp)
	{
		if (*pp) 
			WalkStackOnRelease();
		if (lp != NULL) {
			WalkStackOnAddRef();
			lp->AddRef();
		}
		if (*pp) 
			(*pp)->Release();
		*pp = lp;
		return lp;
	}

	void WalkStackOnAddRef(bool fNotFatal = false) 
		{ AtlWalkStackOnAddRefX(m_StackProbeLists, reinterpret_cast<DWORD>(&p), ID::iid(), fNotFatal); }
	void WalkStackOnRelease()
		{ AtlWalkStackOnReleaseX(m_StackProbeLists, reinterpret_cast<DWORD>(&p), ID::iid()); }
	static CStackProbeLists m_StackProbeLists;
};

template<class T, class ID> 
CStackProbeLists CComPtrDebug<T, ID>::m_StackProbeLists = CStackProbeLists(ID::iid());

/////////////////////////////////////////////////////////////////////////////
// Globale Funktionen, die Member von 'CComPtrDebug' doppeln, damit auch Objekte, 
// die nicht auf dem CComPtrDebug basieren happy gemacht werden können.
inline IUnknown* AtlComPtrAssignStackWalk (IUnknown** pp, IUnknown* lp)
{
	return AtlComPtrAssign (pp, lp);
}
inline void WalkStackOnAddRef(bool fNotFatal = false) {}
inline void WalkStackOnRelease() {}

/////////////////////////////////////////////////////////////////////////////
// Zu analysierende IID's
class CIIDsToAnalyse :
	public list<const IID *>
{
private:
	bool m_fAnalyseAll;

public:
	CIIDsToAnalyse();
	virtual ~CIIDsToAnalyse();

	void Refresh();
	bool Analyse (REFIID riid, bool fRefresh);
	virtual const IID **GetIIDsToAnalyse();
};

/////////////////////////////////////////////////////////////////////////////
// Globale Liste der zu untersuchenden InterfaceID's
#define BEGIN_DEBUGSUPPORT_MAP()	static const IID *_atl_debugsupport_IIDsToAnalyse[] = {
#define DEBUGSUPPORT_ENTRY(riid)	{&(riid)},
#define END_DEBUGSUPPORT_MAP()		{&IID_NULL}};

#endif // _ATLX_DEBUG_REFCOUNT_WALKSTACK

#ifndef ATL_NO_NAMESPACE
}; //namespace ATL
#endif

#endif // !defined(_ATLDEBUG_H__5425EF26_D5D6_11D1_85EF_00600875138A__INCLUDED_)
