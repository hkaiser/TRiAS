// EnumObjektGeometrie.h : Declaration of the CEnumObjektGeometrie

#ifndef __ENUMOBJEKTGEOMETRIE_H_
#define __ENUMOBJEKTGEOMETRIE_H_


#include "SmartInterfaces.h"



/////////////////////////////////////////////////////////////////////////////
// CEnumObjektGeometrie
class CEnumObjektGeometrie : 
	public CComObjectRoot,
	public CComCoClass<CEnumObjektGeometrie, &CLSID_EnumObjektGeometrie>,
	public IEnumObjektGeometrie
{
public:
	typedef list<WObjektGeometrie> cont_t;
	typedef WObjektGeometrie item_t;
	typedef cont_t::iterator iterator;
	typedef cont_t::const_iterator const_iterator;
	typedef CComObjectThreadModel::AutoCriticalSection sync_t;
	
	CEnumObjektGeometrie()
	{
		setdirty(false);
		Reset();
	}

	CEnumObjektGeometrie(const CEnumObjektGeometrie& rhs) :
		m_data(rhs.m_data)
	{
		setdirty(false);	// entgegen allen Regeln wird das aktuelle Element nicht nachgezogen !
		Reset();
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_ENUMOBJEKTGEOMETRIE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CEnumObjektGeometrie)
		COM_INTERFACE_ENTRY(IEnumObjektGeometrie)
		COM_INTERFACE_ENTRY2(IEnumUnknown, IEnumObjektGeometrie)
	END_COM_MAP()

// IEnumObjektGeometrie
public:
	STDMETHOD(Next)(ULONG celt, IUnknown **ppIObj, ULONG *pCeltFetched);

	STDMETHOD(Skip)(ULONG celt);
	STDMETHOD(Reset)(void);
	STDMETHOD(Clone)(IEnumObjektGeometrie **ppenum);

// erweiterte Funktionalität
	STDMETHOD(GetCount) (ULONG *pclCount);
	STDMETHOD(AddItem)(IUnknown *item);
	STDMETHOD(Clear)(void);

protected:
	CEnumObjektGeometrie *Construct (void) throw() 
	{
	CLockEnum<CComObjectThreadModel> SyncMe(m_sync); 
	CComObject<CEnumObjektGeometrie> *p = NULL; 
	
		CComObject<CEnumObjektGeometrie>::CreateInstance(&p);
		return p;
	}

	bool eoi_reached (void) throw() { return m_itcur == m_data.end(); }
	bool isempty (void) throw() { return m_data.size() == 0; }
	bool isdirty (void) throw() { return m_fIsDirty ? true : false; }
	void setdirty (bool fFlag) throw() { m_fIsDirty = fFlag ? true : false; }

	cont_t m_data;
	iterator m_itcur;
	sync_t m_sync;
	bool m_fIsDirty;
};

#endif //__ENUMOBJEKTGEOMETRIE_H_
