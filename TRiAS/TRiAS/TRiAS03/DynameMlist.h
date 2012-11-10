// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 15.03.2002 13:29:43 
//
// @doc
// @module DynameMlist.h | Declaration of the <c CDynameMlist> class

#if !defined(_DYNAMEMLIST_H__D87B803C_95ED_465E_BBDD_7002E1ABEF34__INCLUDED_)
#define _DYNAMEMLIST_H__D87B803C_95ED_465E_BBDD_7002E1ABEF34__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/vector>

/////////////////////////////////////////////////////////////////////////////
// CDynamicMemberList

class CDynamicMemberList
{
public:
    CDynamicMemberList();

    // Should be called only once before any members are added
    HRESULT ExcludeDispIDs(ITypeInfo* pInfo);

    size_t  Count();
    HRESULT AddMember(BSTR bstrName, DWORD grfdex, const VARIANT& varValue, DISPID* pid);
    HRESULT PreDefineMember(BSTR bstrName, DWORD grfdex, const VARIANT& varValue, DISPID id);
    HRESULT GetDispID(BSTR bstrName, DWORD grfdex, DISPID* pid);
    HRESULT GetProperty(DISPID id, VARIANT* pvarRes);
    HRESULT PutProperty(DISPID id, const VARIANT& var);
    HRESULT InvokeEx(DISPID id, LCID lcid, WORD wFlags, DISPPARAMS* pdp, VARIANT* pvarRes,	EXCEPINFO* pei, IServiceProvider* pspCaller);
    HRESULT DeleteMember(BSTR bstrName, DWORD grfdex);
    HRESULT DeleteMember(DISPID id);
    HRESULT GetMemberProperties(DISPID id, BSTR* pbstrName, VARTYPE* pvt, DWORD* pgrfdex);
    HRESULT GetNextDispID(DWORD grfdex, DISPID id, DISPID* pid);
    HRESULT GetNewEnum(IUnknown** punkEnum);

private:
    class CMember;
    typedef vector<CMember> CMemberVector;
    typedef CMemberVector::iterator CMemberIterator;

    class FindMemberByName
    {
    public:
        FindMemberByName(const BSTR bstrName, DWORD grfdex);
        bool operator()(const CMember& member);

    private:
        const BSTR  m_bstrName;
        DWORD       m_grfdex;
    };

    class FindMemberByID
    {
    public:
        FindMemberByID(DISPID id);
        bool operator()(const CMember& member);

    private:
        DISPID  m_id;
    };

    CMemberIterator FindMember(BSTR bstrName, DWORD grfdex, bool bFindDeleted = false);
    CMemberIterator FindMember(DISPID id, bool bFindDeleted = false);

    DISPID GetNextDispID();

    class CMember
    {
    public:
        CMember(DISPID id, BSTR bstrName, DWORD grfdex, const VARIANT& varValue, DISPID baseid = 0);

        DISPID          ID() const;
        DISPID          BaseID() const;
        BSTR            Name() const;
        DWORD           Flags() const;
        const VARIANT&  Value() const;
        bool            Deleted() const;

        void SetID(DISPID id);
        void SetBaseID(DISPID id);
        void SetName(BSTR bstrName);
        void SetFlags(DWORD grfdex);
        void SetValue(const VARIANT& var);
        void SetDeleted(bool bDeleted);

    private:
        DISPID          m_id;
        DISPID          m_baseid;
        CComBSTR        m_bstrName;
        DWORD           m_grfdex;
        CComVariant     m_varValue;
        bool            m_bDeleted;
    };

	HRESULT CalcBaseName (BSTR bstrName, BSTR *pbstrBaseName, INT_PTR *plONr = NULL);

private:
    CMemberVector   m_vecMembers;
    DISPID          m_idNext;
};

#endif // !defined(_DYNAMEMLIST_H__D87B803C_95ED_465E_BBDD_7002E1ABEF34__INCLUDED_)
