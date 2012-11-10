// StatPage.h: GeoDB Statistik als PropPage anzeigen

#if !defined(_STATPAGE_H)
#define _STATPAGE_H

class CStatistikPage : public CPropertyPage {
private:
	FixedText m_ftObjCnt;
	FixedText m_ftClsCnt;
	FixedText m_ftViewCnt;
	FixedText m_ftName;

protected:
	void WindowInit (Event);

public:
		CStatistikPage (ResID uiID, LPCSTR pcCaption);
		~CStatistikPage (void);

	HPROPSHEETPAGE CreatePropPage (void)
		{ return CreatePage(); }
};

class CStatistikPageExt : 
	public ITriasExtInit,
	public ITriasPropSheetExt,
	public CComObjectRoot,
	public CComCoClass<CStatistikPageExt, &CLSID_StatistikPropPage>
{
private:
	CStatistikPage *m_pDlgPage;

public:
		CStatistikPageExt (void);
		~CStatistikPageExt (void);

	BEGIN_COM_MAP(CStatistikPageExt)
		COM_INTERFACE_ENTRY(ITriasPropSheetExt)
		COM_INTERFACE_ENTRY(ITriasExtInit)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CStatistikPageExt)		// class factory
	DECLARE_REGISTRY_RESOURCEID(IDR_STATPROPPAGE_REG)	// registry

// *** ITriasExtInit methods 
	STDMETHOD(Initialize) (THIS_ LPCITEMIDLIST pidl, LPDATAOBJECT lpdobj, HKEY hkeyProgID);

// *** ITriasPropSheetExt
	STDMETHOD(AddPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam);
	STDMETHOD(ReplacePage) (THIS_ UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplacePage, LPARAM lParam);
};

#endif // _STATPAGE_H
