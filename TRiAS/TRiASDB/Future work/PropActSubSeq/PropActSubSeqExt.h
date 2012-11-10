// @doc 
// @module PropActSubSeq.h | Declaration of the <c CPropActSubSeqExtension> class

#if !defined(_PROPACTSUBSEQ_H__83728725_01F3_11D3_94CB_0080C786297B__INCLUDED_)
#define _PROPACTSUBSEQ_H__83728725_01F3_11D3_94CB_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPropActSubSeqExtension
class ATL_NO_VTABLE CPropActSubSeqExtension : 
	public CComCoClass<CPropActSubSeqExtension, &CLSID_PropActSubSeq>,
	public CTriasExtension 
{
public:
	CPropActSubSeqExtension()
	{
	}

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(CPropActSubSeqExtension, g_pTE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CPropActSubSeqExtension)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

// ITriasXtension
public:
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (void);
};

#endif // !defined(_PROPACTSUBSEQ_H__83728725_01F3_11D3_94CB_0080C786297B__INCLUDED_)
