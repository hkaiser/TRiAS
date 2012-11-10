/*
 * PDATAOBJ.HXX
 *
 * Copyright (c)1993 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _PDATAOBJ_HXX_
#define _PDATAOBJ_HXX_

#include <ospace/com/iterenum.h>

#if !defined(_LPFNDESTROY_DEFINED)
#define _LPFNDESTROY_DEFINED
typedef void (PASCAL * LPFNDESTROYED) (void);	// Type for an object-destroyed callback
#endif // _LPFNDESTROY_DEFINED

/*
 * Structure to describe a specific rendering that our user wants
 * us to maintain.
 */

inline bool operator == (const FORMATETC &r1, const FORMATETC &r2) 
{ 
// ptd (DVTARGETDEVIEC wird z.Zt. nicht verglichen
	return	r1.cfFormat == r2.cfFormat && r1.tymed == r2.tymed && 
			r1.dwAspect == r2.dwAspect && r1.lindex == r2.lindex;
}
inline bool operator < (const FORMATETC &r1, const FORMATETC &r2) { return false; }

class CRendering {
friend class CEnumFormatEtc;
friend class CImpIDataObject;
friend class CDataObject;

private:
	FORMATETC m_fe;		// The format
	STGMEDIUM m_stm;	// The actual data
	WUnknown m_UnkOrg;	// The real owner

public:
	CRendering (void) {}
	CRendering (FORMATETC &rFE, STGMEDIUM &rStm, IUnknown *pIUnk, IUnknown *pIUnkRel)
		{ m_fe = rFE; m_stm = rStm; m_UnkOrg = pIUnk; m_stm.pUnkForRelease = pIUnkRel; }
	CRendering (const CRendering &rR)
		{ m_fe = rR.m_fe; m_stm = rR.m_stm; m_UnkOrg = rR.m_UnkOrg; }
	~CRendering (void) {}

	CRendering &operator= (const CRendering &rR)
		{ if (this != &rR) {m_fe = rR.m_fe; m_stm = rR.m_stm; m_UnkOrg = rR.m_UnkOrg; } return *this; }

friend inline bool operator== (const CRendering &, const CRendering &) { return false; }
friend inline bool operator< (const CRendering &, const CRendering &) { return false; }
};

/*
 * The DataObject object is implemented in its own class with its
 * own IUnknown to support aggregation.  It contains one
 * CImpIDataObject object that we use to implement the externally
 * exposed interfaces.
 */
class CImpIDataObject;
typedef class CImpIDataObject *LPIMPIDATAOBJECT;

typedef vector<CRendering> CRenderData;

class CDataObject : public IUnknown
{
friend class CImpIDataObject;

protected:
	ULONG m_cRef;
	LPUNKNOWN m_pUnkOuter;
	LPFNDESTROYED m_pfnDestroy;
	IDataAdviseHolder *m_pIDataAdviseHolder;

	CRenderData m_DataList;

 // Contained interface implemetation
	CImpIDataObject *m_pIDataObject;

		CDataObject (LPUNKNOWN, LPFNDESTROYED);
		~CDataObject (void);

	bool FInit (void);

public:
static CDataObject *CreateInstance (LPUNKNOWN, LPFNDESTROYED);

	void Purge (void);

 // Non-delegating object IUnknown
	STDMETHODIMP QueryInterface (REFIID, LPVOID *);
	STDMETHODIMP_ (ULONG) AddRef (void);
	STDMETHODIMP_ (ULONG) Release (void);
};


/*
 * Interface implementations for the CDataObject object.
 */
class CImpIDataObject : public IDataObject
{
private:
	ULONG m_cRef;
	CDataObject *m_pObj;
	LPUNKNOWN m_pUnkOuter;

protected:
	HRESULT SendDataChange (LPFORMATETC pFE, STGMEDIUM *pSTM);

public:
		CImpIDataObject (CDataObject *, LPUNKNOWN);
		~CImpIDataObject (void);

 // IUnknown members that delegate to m_pUnkOuter.
	STDMETHODIMP QueryInterface (REFIID, LPVOID *);
	STDMETHODIMP_ (ULONG) AddRef (void);
	STDMETHODIMP_ (ULONG) Release (void);

 // IDataObject members
	STDMETHODIMP GetData (LPFORMATETC, LPSTGMEDIUM);
	STDMETHODIMP GetDataHere (LPFORMATETC, LPSTGMEDIUM);
	STDMETHODIMP QueryGetData (LPFORMATETC);
	STDMETHODIMP GetCanonicalFormatEtc (LPFORMATETC, LPFORMATETC);
	STDMETHODIMP SetData (LPFORMATETC, STGMEDIUM *, BOOL);
	STDMETHODIMP EnumFormatEtc (DWORD, LPENUMFORMATETC *);
	STDMETHODIMP DAdvise (FORMATETC *, DWORD,
			      LPADVISESINK, DWORD *);
	STDMETHODIMP DUnadvise (DWORD);
	STDMETHODIMP EnumDAdvise (LPENUMSTATDATA *);
};


DefineEnumerator2(FORMATETC, IID_IEnumFORMATETC);

class CEnumFormatEtc : public NEnumFORMATETC {
protected:
		CEnumFormatEtc (void);
		~CEnumFormatEtc (void);

	bool FInit (ULONG cFE, LPFORMATETC prgfe);
	bool FInit (const CRenderData &rRD);

public:
// Erzeugen nur über diese Funktionen
static CEnumFormatEtc *CreateInstance (ULONG cFE, LPFORMATETC prgfe);
static CEnumFormatEtc *CreateInstance (const CRenderData &rRD);
};

#endif //_PDATAOBJ_HXX_

