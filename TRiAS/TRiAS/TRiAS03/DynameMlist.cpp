// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 15.03.2002 13:31:15 
//
// @doc
// @module DynameMlist.cpp | Definition of the <c CDynameMlist> class

// dynamemlist.cpp
// Need to be able to map DISPID->Name
// Need to be able to map DISPID->Method/Property
// Need to be able to get next DISPID based on a DISPID
// Need to be able to remove method/property based on DISPID
// Need to be able to remove method/property based on Name
// Why not just use a vector of methods? Removing a DISPID
// doesn't really remove it anyway, i.e. GetNextDispID must
// still work, the DISPID can't be reused and if a property
// of the same name is added, it must have the same DISPID.

#include "trias03p.hxx"
#include "DynameMlist.h"

#include <dispex.h>
#include <ospace/std/algorithm>

#ifndef HR
#define HR(_ex) { HRESULT _hr = _ex; if(FAILED(_hr)) return _hr; }
#endif

#ifndef SafeBSTR
#define SafeBSTR(_bstr) (_bstr ? _bstr : OLESTR(""))
#endif

// Compile-time assert
#ifndef CTASSERT
#if defined(_DEBUG) || defined(_PSEUDO_DEBUG)   // Support MFC AppWizards Pseudo-Debug mode
#define CTASSERT(_ex) { int _rg[_ex ? 1 : -1]; _rg; }
#else
#define CTASSERT(_ex)
#endif
#endif

///////////////////////////////////////////////////////////////////
// CDynamicMemberList helpers

#ifdef _DEBUG

void TracePropPut(DWORD idExpando, DISPID id, const BSTR bstrName, const VARIANT& varValue)
{
    CComVariant varBstr;
    HRESULT     hr = varBstr.ChangeType(VT_BSTR, &varValue);
    CComBSTR    bstrValue = (SUCCEEDED(hr) ? varBstr.bstrVal : OLESTR("<value>"));

    ATLTRACE2(atlTraceUser, 2, "Expando (0x%x) propput: %S (%d)= '%S'\n", idExpando, bstrName, id, SafeBSTR(static_cast<BSTR>(bstrValue)));
}

void TracePropGet(DWORD idExpando, DISPID id, const BSTR bstrName, const VARIANT& varValue)
{
    CComVariant varBstr;
    HRESULT     hr = varBstr.ChangeType(VT_BSTR, &varValue);
    CComBSTR    bstrValue = (SUCCEEDED(hr) ? varBstr.bstrVal : OLESTR("<value>"));

    ATLTRACE2(atlTraceUser, 2, "Expando (0x%x) propget: %S (%d)= '%S'\n", idExpando, bstrName, id, SafeBSTR(static_cast<BSTR>(bstrValue)));
}

#define TRACEPROPPUT(_eid, _id, _name, _val) TracePropPut(_eid, _id, _name, _val);
#define TRACEPROPGET(_eid, _id, _name, _val) TracePropGet(_eid, _id, _name, _val);
#else
#define TRACEPROPPUT(_eid, _id, _name, _val)
#define TRACEPROPGET(_eid, _id, _name, _val)
#endif

///////////////////////////////////////////////////////////////////
// CDynamicMemberList

CDynamicMemberList::CDynamicMemberList() : m_idNext(1)
{}

DISPID CDynamicMemberList::GetNextDispID()
{
    // NOTE: Depending on ExcludeDispIDs to set m_idNext
    // to beginning of large range
    return m_idNext++;
}

HRESULT CDynamicMemberList::ExcludeDispIDs(ITypeInfo* pInfo)
{
    const DISPID    DISPID_MIN = 0;
    const DISPID    DISPID_MAX = LONG_MAX; CTASSERT(sizeof(DISPID) == sizeof(long));
    size_t          nids = 0;
    DISPID*         rgids = 0;

    // Determine the number of methods on the interface
	TYPEATTR* pta = 0;
    HR(pInfo->GetTypeAttr(&pta));

    if( pta->cFuncs )
    {
        nids = pta->cFuncs + 2;
        rgids = new DISPID[nids];
        if( !rgids ) return E_OUTOFMEMORY;
        ZeroMemory(rgids, sizeof(DISPID) * nids);

		// Loop through getting the information on each member
		for( UINT i = 0; i != pta->cFuncs; ++i )
		{
			// Get the function description for this member
			FUNCDESC* pfd = 0;
			HRESULT hr = pInfo->GetFuncDesc(i, &pfd);
            if( FAILED(hr) ) continue;

            // Add DISPID to list to be excluded
            rgids[i+1] = pfd->memid;

    		// Release the memory alloced on our behalf
			pInfo->ReleaseFuncDesc(pfd);
		}

        // Add min and max
        rgids[0] = DISPID_MIN;
        rgids[nids - 1] = DISPID_MAX;
    }

	// Release the memory alloced on our behalf
	pInfo->ReleaseTypeAttr(pta);

    if( !nids ) return S_OK;

    // Sort DISPIDs to exclude so largest range can be found
    sort(&rgids[0], &rgids[nids]);

    // Find the largest range of DISPIDs not to exclude
    // and set m_idNext to beginning of the range.
    ULONG   maxIdsInRange = 0;
    for( DISPID* pid = &rgids[0]; pid != &rgids[nids-1]; ++pid )
    {
        // Exclude standard DISPIDs from search
        if( *pid < 1 ) continue;

        ULONG   nIdsInRange = (*(pid + 1) - *pid);
        if( nIdsInRange > maxIdsInRange )
        {
            maxIdsInRange = nIdsInRange;
            m_idNext = *pid + 1;
        }
    }

    delete[] rgids;

    ATLTRACE2(atlTraceUser, 2, __T("CDynamicMemberList::ExcludeDispIDs -- picked m_idNext = %d\n"), m_idNext);
    return S_OK;
}

size_t CDynamicMemberList::Count()
{
    // Count undeleted members
    long    cMembers = 0;
    for( CMemberIterator it = m_vecMembers.begin(); it != m_vecMembers.end(); ++it )
    {
        if( !it->Deleted() ) ++cMembers;
    }

    return cMembers;
}

// ein dynamischer Name muß die Form 'Name_ONr' haben (z.B. IsRO_12345678, ONr 
// ist eine HexZahl)
HRESULT CDynamicMemberList::CalcBaseName (BSTR bstrName, BSTR *pbstrBaseName, INT_PTR *plONr)
{
	_ASSERTE(NULL != pbstrBaseName);

OLECHAR *pT = bstrName;
bool found = false;

	while (0 != *pT) {
		if (L'_' == *pT++) {
			found = true;
			break;
		}
	}
	if (!found)
		return E_INVALIDARG;

// Basisname ist jetzt klar
CComBSTR bstrBaseName (pT-bstrName-1, bstrName);

	*pbstrBaseName = bstrBaseName.Detach();

// ggf. Objektnummer liefern
	if (NULL != plONr) 
		*plONr = wcstoul(pT, NULL, 16);

	return S_OK;
}

HRESULT CDynamicMemberList::AddMember(
    BSTR            bstrName,
    DWORD           grfdex,
    const VARIANT&  varValue,
    DISPID*         pid)
{
// Check for existing member (even a deleted one)
CMemberIterator it = FindMember(bstrName, grfdex, true);

    if( it != m_vecMembers.end() )
    {
        // Undelete a deleted member
        it->SetDeleted(false);
        it->SetName(bstrName);
        it->SetFlags(grfdex);
        it->SetValue(varValue);
        *pid = it->ID();
        return S_OK;
    }

// Basisnamen herauslösen und Member wiederfinden
CComBSTR bstrBaseName;

	HR(CalcBaseName(bstrName, &bstrBaseName));

CMemberIterator itbase = FindMember(bstrBaseName, grfdex);

	if (itbase == m_vecMembers.end())
		return E_INVALIDARG;

// Add a new member
DISPID id = GetNextDispID();
CMember member(id, bstrName, grfdex, varValue, itbase->ID());

    try {
        m_vecMembers.push_back(member);
        *pid = id;

        TRACEPROPPUT((DWORD)this, member.ID(), member.Name(), member.Value());
        return S_OK;
    }
    catch(...) {
		;
	}
    return E_OUTOFMEMORY;
}

HRESULT CDynamicMemberList::PreDefineMember(
    BSTR            bstrName,
    DWORD           grfdex,
    const VARIANT&  varValue,
    DISPID          id)
{
// Check for existing member (snh)
CMemberIterator it = FindMember(bstrName, grfdex, true);

    if (it != m_vecMembers.end())
		return S_FALSE;

// Add a new member
CMember member(id, bstrName, grfdex, varValue);

    try {
        m_vecMembers.push_back(member);
        TRACEPROPPUT((DWORD)this, member.ID(), member.Name(), member.Value());
        return S_OK;
    }
    catch(...) {
		;
	}
    return E_OUTOFMEMORY;
}

HRESULT CDynamicMemberList::GetDispID(
    BSTR    bstrName,
    DWORD   grfdex,
    DISPID* pid)
{
    // Check for name of DISPID_VALUE
    if( wcsicmp(bstrName, L"value") == 0 )
    {
        *pid = DISPID_VALUE;
        return S_OK;
    }

    // Find an existing member
    CMemberIterator it = FindMember(bstrName, grfdex);
    if (it != m_vecMembers.end()) 
    {
        *pid = it->ID();
        return S_OK;
    }
    return DISP_E_UNKNOWNNAME;
}

HRESULT CDynamicMemberList::GetProperty(
    DISPID      id,
    VARIANT*    pvarRes)
{
    if( !pvarRes ) return E_POINTER; VariantInit(pvarRes);

    // Find the property
    CMemberIterator it = FindMember(id);
    if( it == m_vecMembers.end() ) return DISP_E_MEMBERNOTFOUND;

    // Return the value
    HR(VariantCopy(pvarRes, const_cast<VARIANT*>(&it->Value())));

    TRACEPROPGET((DWORD)this, it->ID(), it->Name(), *pvarRes);
    return S_OK;
}

HRESULT CDynamicMemberList::PutProperty(
    DISPID          id,
    const VARIANT&  var)
{
    // Find the property
    CMemberIterator it = FindMember(id);
    if( it == m_vecMembers.end() ) return DISP_E_MEMBERNOTFOUND;

    // Cache the new value
    it->SetValue(var);

    TRACEPROPPUT((DWORD)this, it->ID(), it->Name(), var);
    return S_OK;
}

namespace {
	class CInvokeArgs
	{
	public:
		CInvokeArgs() : 
			m_pvArgs(NULL), m_cArgs(0) 
		{
		}
		
		HRESULT Init(long cArgs, VARIANTARG *pvArgs, INT_PTR lONr)
		{
			m_pvArgs = (VARIANTARG *)CoTaskMemAlloc(sizeof(VARIANTARG)*(cArgs+1));
			if (NULL == m_pvArgs)
				return E_OUTOFMEMORY;

		// Argumente sind im Feld in umgekehrter Reihenfolge, daher erstes 
		// Argument hinten dran hängen
		long i = 0;

			for (/**/; i < cArgs; ++i) {
				VariantInit(&m_pvArgs[i]);
				VariantCopy(&m_pvArgs[i], &pvArgs[i]);
			}

			V_VT(&m_pvArgs[i]) = VT_I4;
			V_I4(&m_pvArgs[i]) = lONr;

			m_cArgs = cArgs+1;
			return S_OK;
		}
		~CInvokeArgs()
		{
			if (NULL != m_pvArgs) {
				for (long i = 0; i < m_cArgs; ++i)
					VariantClear(&m_pvArgs[i]);
				CoTaskMemFree(m_pvArgs);
				m_pvArgs = NULL;
			}
		}

		VARIANTARG *operator &() { return m_pvArgs; }

	private:
		long m_cArgs;
		VARIANTARG *m_pvArgs;
	};
}

HRESULT CDynamicMemberList::InvokeEx(DISPID id, LCID lcid, WORD wFlags, 
	DISPPARAMS* pdp, VARIANT* pvarRes,	EXCEPINFO* pei, 
	IServiceProvider* pspCaller)
{
UINT uArgErr;
CComVariant var;

CMemberIterator it = FindMember(id);

	if (it == m_vecMembers.end())
		return E_INVALIDARG;

// BasisMember finden
CComBSTR bstrBaseName;
INT_PTR lONr = NULL;

	HR(CalcBaseName(it->Name(), &bstrBaseName, &lONr));

// Objektnummer als ersten Parameter einbauen
DISPPARAMS dispParams = { NULL, pdp->rgdispidNamedArgs, pdp->cArgs+1, pdp->cNamedArgs};
CInvokeArgs Args;

	HR(Args.Init(pdp->cArgs, pdp->rgvarg, lONr));
	dispParams.rgvarg = &Args;

    HR(this->GetProperty(id, &var));
    HR(var.ChangeType(VT_DISPATCH));
    HR(var.pdispVal->Invoke(it->BaseID(), IID_NULL, lcid, wFlags, &dispParams, pvarRes, pei, &uArgErr));
    return S_OK;
}

// Hand out a collection of keys
HRESULT CDynamicMemberList::GetNewEnum(IUnknown** ppunkEnum)
{
    if( !ppunkEnum ) return E_INVALIDARG;
    *ppunkEnum = 0;

    // Count members
    ULONG   cMembers = this->Count();

    // Create array of VARIANTs
    VARIANT*    rgvar = new VARIANT[cMembers];
    if( !rgvar ) return E_OUTOFMEMORY;
    ZeroMemory(rgvar, sizeof(VARIANT) * cMembers);

    ULONG   i = 0;
    for( CMemberIterator it = m_vecMembers.begin(); it != m_vecMembers.end(); ++it )
    {
        if( !it->Deleted() )
        {
            //HR(VariantCopy(&rgvar[i], const_cast<VARIANT*>(&it->Value())));
            rgvar[i].vt = VT_BSTR;
            rgvar[i].bstrVal = SysAllocString(it->Name());
            ++i;
        }
    }

    // Create enumerator
    CComObject< CComEnum<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT> > >*  pEnum = 0;
    HR(pEnum->CreateInstance(&pEnum));
    CComPtr<IUnknown>   spunkEnum = pEnum;  // Stablize the pointer
    HR(pEnum->Init(&rgvar[0], &rgvar[cMembers], 0, AtlFlagTakeOwnership));
    *ppunkEnum = spunkEnum.Detach();

    return S_OK;
}

HRESULT CDynamicMemberList::DeleteMember(
    BSTR    bstrName,
    DWORD   grfdex)
{
    // Find the dynamic property
    CMemberIterator it = FindMember(bstrName, grfdex, true);
    if( it == m_vecMembers.end() ) return S_OK;

	if (grfdex & fdexNameInternal) {
	// Löschen erzwingen
		m_vecMembers.erase(it);
	}
	else {
		// Set it "deleted"
		it->SetDeleted(true);
	}
    return S_OK;
}

HRESULT CDynamicMemberList::DeleteMember(DISPID id)
{
    // Find the dynamic property
    CMemberIterator it = FindMember(id, true);
    if( it == m_vecMembers.end() ) return S_OK;

    // Set it "deleted"
    it->SetDeleted(true);
    return S_OK;
}

HRESULT CDynamicMemberList::GetMemberProperties(
    DISPID          id,
    BSTR*           pbstrName,
    VARTYPE*        pvt,
    DWORD*          pgrfdex)
{
    // Find the dynamic property
    CMemberIterator it = FindMember(id);
    if( it == m_vecMembers.end() ) return DISP_E_MEMBERNOTFOUND;

    if( pbstrName ) *pbstrName = SysAllocString(it->Name());
    if( pvt ) *pvt = it->Value().vt;
    if( pgrfdex ) *pgrfdex = it->Flags();
    return S_OK;
}

HRESULT CDynamicMemberList::GetNextDispID(
    DWORD   grfdex,
    DISPID  id,
    DISPID* pid)
{
    if( !pid ) return E_POINTER;

    CMemberIterator it;

    // Are we starting the search?
    if( id == DISPID_STARTENUM )
    {
        // Get the first potential candidate
        it = m_vecMembers.begin();
    }
    // Are we continuing the search?
    else
    {
        // Find the current property (even if it's deleted)
        it = FindMember(id, true);
        
        // Get the next one (which is the first potential candidate
        if( it != m_vecMembers.end() ) ++it;
    }

    // Check for the next non-deleted member
    while( it != m_vecMembers.end() && it->Deleted() ) ++it;

    // Are we at the end?
    if( it == m_vecMembers.end() ) return S_FALSE;

    // Return the ID of the next one
    *pid = it->ID();
    return S_OK;
}

CDynamicMemberList::CMemberIterator CDynamicMemberList::FindMember(
    BSTR    bstrName,
    DWORD   grfdex,
    bool    bFindDeleted)
{
    CMemberIterator it = find_if(m_vecMembers.begin(), m_vecMembers.end(), FindMemberByName(bstrName, grfdex));
    if( it == m_vecMembers.end() ) return it;
    if( it->Deleted() && !bFindDeleted ) return m_vecMembers.end();
    return it;
}

CDynamicMemberList::CMemberIterator CDynamicMemberList::FindMember(
    DISPID  id,
    bool    bFindDeleted)
{
    CMemberIterator it = find_if(m_vecMembers.begin(), m_vecMembers.end(), FindMemberByID(id));
    if( it == m_vecMembers.end() ) return it;
    if( it->Deleted() && bFindDeleted ) return m_vecMembers.end();
    return it;
}

///////////////////////////////////////////////////////////////////
// FindMemberByName

CDynamicMemberList::FindMemberByName::FindMemberByName(
    const BSTR  bstrName,
    DWORD       grfdex)
:   m_bstrName(bstrName),
    m_grfdex(grfdex)
{}

bool CDynamicMemberList::FindMemberByName::operator()(const CMember& member)
{
    if( m_grfdex & fdexNameCaseSensitive )
    {
        return (wcscmp(member.Name(), m_bstrName) == 0);
    }
    else
    {
        return (wcsicmp(member.Name(), m_bstrName) == 0);
    }
}

///////////////////////////////////////////////////////////////////
// FindMemberByID

CDynamicMemberList::FindMemberByID::FindMemberByID(DISPID id)
:   m_id(id)
{}

bool CDynamicMemberList::FindMemberByID::operator()(const CMember& member)
{
    return (member.ID() == m_id);
}

///////////////////////////////////////////////////////////////////
// CMember

CDynamicMemberList::CMember::CMember(
    DISPID          id,
    BSTR            bstrName,
    DWORD           grfdex,
    const VARIANT&  varValue,
    DISPID          baseid)
:   m_id(id),
    m_bstrName(bstrName),
    m_grfdex(grfdex),
    m_varValue(varValue),
    m_bDeleted(false),
	m_baseid(baseid)
{}

DISPID CDynamicMemberList::CMember::ID() const
{ return m_id; }

DISPID CDynamicMemberList::CMember::BaseID() const
{ return m_baseid; }

BSTR CDynamicMemberList::CMember::Name() const
{ return m_bstrName; }

DWORD CDynamicMemberList::CMember::Flags() const
{ return m_grfdex; }

const VARIANT& CDynamicMemberList::CMember::Value() const
{ return m_varValue; }

bool CDynamicMemberList::CMember::Deleted() const
{ return m_bDeleted; }    

void CDynamicMemberList::CMember::SetID(DISPID id)
{ m_id = id; }

void CDynamicMemberList::CMember::SetBaseID(DISPID id)
{ m_baseid = id; }

void CDynamicMemberList::CMember::SetName(BSTR bstrName)
{ m_bstrName = bstrName; }

void CDynamicMemberList::CMember::SetFlags(DWORD grfdex)
{ m_grfdex = grfdex; }

void CDynamicMemberList::CMember::SetValue(const VARIANT& varValue)
{ m_varValue = varValue; }

void CDynamicMemberList::CMember::SetDeleted(bool bDeleted)
{
    m_varValue.Clear();
    m_bDeleted = bDeleted;
}
