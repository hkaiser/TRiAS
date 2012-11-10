// EnumObjektGeometrie.cpp : Definition of the CEnumObjektGeometrie

#include "GeoEditP.h"
#include "EnumObjektGeometrie.h"

// *** IEnum<X> methods
STDMETHODIMP CEnumObjektGeometrie::Next (ULONG celt, IUnknown **rgelt, ULONG *pceltFetched) 
{
CLockEnum<CComObjectThreadModel> SyncMe(m_sync);
DWORD cReturn = 0L;

	if (pceltFetched) *pceltFetched = 0L;
	if (NULL == rgelt || m_data.end() == m_itcur) 
		return S_FALSE;
        	
	while (m_itcur != m_data.end() && 0 < celt) {
		*rgelt = *m_itcur;
		if (*rgelt)
			LPUNKNOWN(*rgelt) -> AddRef();

		rgelt++; m_itcur++;	// weiterzählen
		celt--;
		cReturn++;
	}
	if (pceltFetched) 
		*pceltFetched = (cReturn - celt);	// gelieferte Werte

	return NOERROR;
}

STDMETHODIMP CEnumObjektGeometrie::Skip (ULONG dwSkip) 
{
	if (0 == dwSkip) return NOERROR;

CLockEnum<CComObjectThreadModel> SyncMe(m_sync);
iterator it = m_itcur;

	while (it != m_data.end()) {
		++it;
		if (--dwSkip == 0) {
			m_itcur = it;
			return NOERROR;
		}
	}
	return S_FALSE;
}

STDMETHODIMP CEnumObjektGeometrie::Reset (void) 
{
	m_itcur = isempty() ? m_data.end() : m_data.begin();
	return NOERROR;
}

STDMETHODIMP CEnumObjektGeometrie::Clone (IEnumObjektGeometrie **ppenum) 
{
CLockEnum<CComObjectThreadModel> SyncMe(m_sync);

	*ppenum = NULL;		// für alle Fälle

CEnumObjektGeometrie *pEnum = Construct();		// Enumerator bilden (standalone)

	if (pEnum == NULL) return E_OUTOFMEMORY;

	*ppenum = pEnum;
	if (NULL != *ppenum)
		LPUNKNOWN(*ppenum) -> AddRef();
	return NOERROR;
}

// *** IEnum<X> methods
STDMETHODIMP CEnumObjektGeometrie::GetCount (ULONG *pulCount) 
{
CLockEnum<CComObjectThreadModel> SyncMe(m_sync); 

	if (NULL == pulCount)
		return E_POINTER;
	*pulCount = m_data.size(); 
	return S_OK;
}

STDMETHODIMP CEnumObjektGeometrie::AddItem (IUnknown *item)
{ 
CLockEnum<CComObjectThreadModel> SyncMe(m_sync); 

	try {
		m_data.insert(m_data.end(), WObjektGeometrie(item)); 
		setdirty(true); 
	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return NOERROR; 
}

STDMETHODIMP CEnumObjektGeometrie::Clear (void)
{ 
CLockEnum<CComObjectThreadModel> SyncMe(m_sync);
bool fEmpty = isempty();

	setdirty(true);
	m_data.erase (m_data.begin(), m_data.end()); 
	m_itcur = m_data.end();		// kein aktuelles Item mehr
	return fEmpty ? S_FALSE : NOERROR;
}
