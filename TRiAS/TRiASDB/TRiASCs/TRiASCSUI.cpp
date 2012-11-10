// TRiASCSUI.cpp : Implementation of CTRiASCSUI
#include "stdafx.h"
#include "TRiASCsImpl.h"
#include "TRiASCSUI.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#pragma comment(lib, "comctl32")

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSUI

HRESULT CTRiASCSUI::FinalConstruct() 
{
	::InitCommonControls();
	COM_TRY {
		m_csSet = WTRiASCSSet(CLSID_TRiASCSSet);
		m_csSet->LoadFromRegistry(TCS_HKCU, CComBSTR("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\CoordinateSystems"), vtMissing);

	FONTDESC	f;

		memset(&f, PADCHAR, sizeof(f));
		f.cbSizeofstruct = sizeof(f);
		f.lpstrName = L"MS Sans Serif";
		f.cySize.Lo = 8;
		f.sWeight = FW_NORMAL;
		f.sCharset = DEFAULT_CHARSET;
		f.fItalic = false;
		f.fUnderline = false;
		f.fStrikethrough = false;

	WFontDisp pFont;

		if (!SUCCEEDED(::OleCreateFontIndirect(&f, IID_IFontDisp, pFont.ppv())))
			return S_FALSE;
		m_pFont = pFont;
	} COM_CATCH;
	return S_OK;
}

void CTRiASCSUI::FinalRelease() {}

HRESULT CTRiASCSUI::OnDraw(ATL_DRAWINFO& di) 
{
	if (m_tree.m_hWnd) {
	HFONT hOldFont = NULL;

		if (m_pFont) {
			CComPtr < IFont> pFont;
			m_pFont->QueryInterface(IID_IFont, (void**)&pFont);
			HFONT hfont;
			pFont->get_hFont(&hfont);
			m_tree.SetFont(hfont);
		}
	}
	return S_OK;
}

HRESULT CTRiASCSUI::ClearTree(CAtlTreeCursor& item) 
{
	if (!item)
		return S_FALSE;

	while (item.HasChild()) 
	{
		ClearTree(item.GetChildItem());
	}
	item.Delete();
	return S_OK;
}

DefineSmartInterface(OleObject)
DefineSmartInterface(OleClientSite)

HRESULT CTRiASCSUI::SetImage(CAtlTreeCursor& item) 
{
WTRiASCS cs((IUnknown *)item.GetData());
TRIASCSTYPE	csType;

	cs->get_CoordSystemType(&csType);
	if (tcsCS_Geographic == csType)
	{
		item.SetImage(5, 5);
	}
	else if (tcsCS_Projected == csType) {
	WTRiASCSPCS	pPCS;
	TRIASCSPROJECTIONALGORITHM pa;

		cs->get_ProjectedCS(pPCS.ppi());
		pPCS->get_ProjectionAlgorithm(&pa);
		if (tcsPA_AffineTransformation == pa)
		{
			item.SetImage(7, 7);
		}
		else {
			item.SetImage(6, 6);
		}
	}
	return S_OK;
}

HRESULT	CTRiASCSUI::FillTree(WTRiASCSSet& csSet, CAtlTreeCursor& root) 
{
WEnumVARIANT	e;
CComVariant		v;
ULONG			n;
CComBSTR		strName;
LPCTSTR			lpszName;
CAtlTreeCursor	bmk;

	USES_CONVERSION;
	csSet->_NewEnum(e.ppu());
	for (e->Reset(); S_OK == e->Next(1, &v, &n); /**/) {
	WTRiASCS cs(V_UNKNOWN(&v));

		cs->get_Category(CLEARED(strName));
		if (0 < strName.Length()) {
			lpszName = OLE2A(strName);
			bmk = root.FindItem(lpszName);
			if (!bmk)
				bmk = root.InsertItem(lpszName, TVI_LAST, 3);
		}
		else {
			bmk = root;
		}
		cs->get_Description(CLEARED(strName));
		if (0 == strName.Length())
			cs->get_GUID(CLEARED(strName));

		lpszName = OLE2A(strName); 
		bmk = bmk.InsertItem(lpszName, TVI_LAST, 6);
		bmk.SetData((DWORD) V_UNKNOWN(&v));
		SetImage(bmk);
	}
	return S_OK;
}

LRESULT CTRiASCSUI::OnDblClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) 
{
CAtlTreeCursor	item = m_tree.GetSelectedItem();
IUnknown *pUnk = (IUnknown*) item.GetData();

	if (!pUnk)
	{
		bHandled = FALSE;
		return 0;
	}

TRIASCSTYPE	cst = tcsCS_Undefined;
WTRiASCS	cs(pUnk);
CComBSTR	strCategory;

	cs->get_CoordSystemType(&cst);
	cs->get_Category(CLEARED(strCategory));

	Lock();			// CComCriticalSection

WOleObject	o(cs);

	o->SetClientSite(WOleClientSite(GetUnknown()));
	HRESULT hr = o->DoVerb(OLEIVERB_PROPERTIES, NULL, NULL, 0, m_tree.m_hWnd, NULL);
	o->SetClientSite(NULL);
	Unlock();		// CComCriticalSection
	return 0;
}

LRESULT CTRiASCSUI::OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) 
{
LPNMHDR	pnmhdr = (LPNMHDR) lParam;
NM_TREEVIEW	*pnmtv = (NM_TREEVIEW*) lParam;

	if (TVN_ITEMEXPANDED == pnmhdr->code) {
	CAtlTreeCursor	item = m_tree.GetSelectedItem();

		if (1 == pnmtv->action)
			item.SetImage(3, 3);
		else
			item.SetImage(4, 4);

	CComBSTR s = item.GetText();
	}
	return 0;
}
