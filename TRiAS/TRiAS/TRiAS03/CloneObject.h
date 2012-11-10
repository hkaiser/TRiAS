// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 26.09.2001 10:44:15 
//
// @doc
// @module CloneObject.h | Declaration of the <c CCloneObject> class

#if !defined(_CLONEOBJECT_H__8084F49C_7E6A_49BE_8A4E_EA11D3A589F3__INCLUDED_)
#define _CLONEOBJECT_H__8084F49C_7E6A_49BE_8A4E_EA11D3A589F3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Helperklasse zum Kopieren eines Objektes

class CCloneObject
{
public:
	CCloneObject(HPROJECT hPrDest, HOBJECT lObjToCopy, UINT uiUndoStr = IDS_UNDOCLONEOBJECT) : 
		m_hPrDest(hPrDest), m_lObjToCopy(lObjToCopy), 
        m_lNewObject(INVALID_HOBJECT), m_fIsValid(false) 
	{
        extern char g_pDLLName[_MAX_PATH];
    
    ResourceFile RF (g_pDLLName);
    ResString strUndoString(ResID(uiUndoStr, &RF), 128);

	    _ASSERTE(strUndoString.Len() > 0);
	    DEX_BeginUndoLevel(strUndoString.Addr());
	}

	~CCloneObject() 
	{
		if (m_fIsValid)
			DEX_EndUndoLevel();
		else
			DEX_CancelUndoLevel(TRUE);		// Undo existing
	}

	HRESULT Clone (HOBJECTS lNewIdent, HOBJECT *plNewObj = NULL);
    HRESULT Clone (CObjGeometrie &rObj, HOBJECTS lNewIdent,
        HOBJECT *plNewObj = NULL);

	short GetObjType() { return DEX_GetObjectType(m_lObjToCopy); }

	BOOL CALLBACK EnumAttributes(HFEATURE lMCode, BOOL, void *pData);

	HPROJECT GetSourceProject() { return DEX_GetObjectProject(m_lObjToCopy); }
	HPROJECT GetDestinationProject() { return m_hPrDest; }

protected:
	HRESULT CopyAttributes();
	HRESULT EnsureDestAttribute(HFEATURE lMCode, HFEATURE lDefMCode, HFEATURE *plNewMCode);
	HRESULT EnsureDestClass (HPROJECT hPrSrc, HOBJECTS lNewIdent, bool fNeedsOKS);
	HOBJECTS GetDestClassFromSrcClass(HPROJECT hSrc, HOBJECTS lIdentSrc);
	
private:
	HPROJECT m_hPrDest;
	HOBJECT m_lObjToCopy;
	HOBJECT m_lNewObject;
	bool m_fIsValid;
};


#endif // !defined(_CLONEOBJECT_H__8084F49C_7E6A_49BE_8A4E_EA11D3A589F3__INCLUDED_)
