// KOMPPage.h: GewKataster als PropPage anzeigen

#if !defined(_KOMPPAGE_H)
#define _KOMPPAGE_H

//#include "kompguid.h"

////// Variante 1 : Eigenschaften

class CKompaktPage : public CPropertyPage {
private:
	FixedText m_ftGewCnt;
	FixedText m_ftBauwCnt;
	FixedText m_ftName;
	FixedText m_ftVerband;
	class KompaktHeader *m_pKH;
	PushButton m_cbDefButton;
#if _MSC_VER >= 1100
	PushButton _DefQuelle;
#endif
	short _isValid;

#if _MSC_VER >= 1100
	HPROJECT m_hPr;
#endif

protected:
	void WindowInit (Event);
	void _XTENSN_EXPORT ButtonClick (ControlEvt);

public:
		CKompaktPage (ResID uiID, LPCSTR pcCaption);
		~CKompaktPage (void);

	HPROPSHEETPAGE CreatePropPage (void)
		{ return CreatePage(); }

	void InitMyPage(void);

//	int GetCheck ( void );
};

class CKompaktPageExt : 
	public ITriasExtInit,
	public ITriasPropSheetExt,
//	public CComObjectBase<&CLSID_KompaktPropPage>
	public CComObjectRoot,
	public CComCoClass<CKompaktPageExt, &CLSID_KompaktPropPage>
{
private:
	CKompaktPage *m_pDlgPage;

public:
		CKompaktPageExt (void);
		~CKompaktPageExt (void);

	BEGIN_COM_MAP(CKompaktPageExt)
		COM_INTERFACE_ENTRY(ITriasPropSheetExt)
		COM_INTERFACE_ENTRY(ITriasExtInit)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CKompaktPageExt)		// class factory
	DECLARE_REGISTRY_RESOURCEID(IDR_KOMPPROPPAGE_REG)	// registry

// *** ITriasExtInit methods 
	STDMETHOD(Initialize) (THIS_ LPCITEMIDLIST pidl, LPDATAOBJECT lpdobj, HKEY hkeyProgID);

// *** ITriasPropSheetExt
	STDMETHOD(AddPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam);
	STDMETHOD(ReplacePage) (THIS_ UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam);
};
#endif // _KOMPPAGE_H
