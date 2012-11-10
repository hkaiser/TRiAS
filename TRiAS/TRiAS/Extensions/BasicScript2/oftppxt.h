// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.11.1999 17:08:29 
//
// @doc
// @module oftppxt.h | Declaration of the <c CObjFeatPPExt> class

#if !defined(_OFTPPXT_H__06E4861A_1108_4DEC_BA71_47994049A044__INCLUDED_)
#define _OFTPPXT_H__06E4861A_1108_4DEC_BA71_47994049A044__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Esnecil.h>
#include <registrx.hxx>
#include "conststr.h"

#if _TRiAS_VER < 0x0400
extern DWORD g_dwVer4;
#endif // _TRiAS_VER < 0x0400

////////////////////////////////////////////////////////////////////////////
// Installation von ObjFeatScripts
class CObjFeatPPExt : 
	public CPPExt2<CObjFeatInstallDlg>,
	public CComObjectRoot,
	public CComCoClass<CObjFeatPPExt, &CLSID_ObjFeatPPExt>
{
public:
	HRESULT FinalConstruct()
	{
#if _TRiAS_VER < 0x0400
		if (0 == g_dwVer4) {
		CCurrentUser regCfg (KEY_READ, g_cbCfgKey);
		DWORD dwCfg = 0L;

			if (!regCfg.GetDWORD (g_cbFullInstall, dwCfg) || dwCfg != MAGIC_FULLINSTALL)
				return CLASS_E_NOTLICENSED;		// PP nicht anzeigen, da nur MinimalInstallation
		} else
#endif // _TRiAS_VER < 0x0400
		{
		VERIFYLICENSE VL;

			INITSTRUCT(VL, VERIFYLICENSE);
			VL.iMode = VERIFYMODE_DontShowDialog|VERIFYMODE_LessOrEqual;
			VL.lLevelOrOption = CKILEVEL_PLUS;
			if (!DEX_VerifyLicenseLevel(VL))
				return CLASS_E_NOTLICENSED;		// PP nicht anzeigen, da nur MinimalInstallation
		}
		return S_OK;
	}

	BEGIN_COM_MAP(CObjFeatPPExt)
		COM_INTERFACE_ENTRY(ITriasPropSheetExt)
		COM_INTERFACE_ENTRY(ITriasExtInit)
	END_COM_MAP()

	DECLARE_REGISTRY_RESOURCEID(IDR_OBJFEATPPEXT_REG)
};
/////////////////////////////////////////////////////////////////////////////

#endif // !defined(_OFTPPXT_H__06E4861A_1108_4DEC_BA71_47994049A044__INCLUDED_)
