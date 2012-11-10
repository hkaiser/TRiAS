// Special document template for subclassed View/Document
// File: TRiASDocTempl.h

#if !defined(TRIASDOCTEMPL_H)
#define TRIASDOCTEMPL_H

class CTRiASView;

class CTRiASDocTemplate :
	public CSingleDocTemplate
{
	DECLARE_DYNAMIC(CTRiASDocTemplate)

// Constructors
public:
	CTRiASDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);

// Implementation
public:
	virtual ~CTRiASDocTemplate();

	virtual CTRiASView* SubclassView (HWND hWndView);
	virtual CTRiASView* CreateSubclassedView (CDocument* pDoc, HWND hWndView);

#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

protected:  // standard implementation
};

#endif // TRIASDOCTEMPL_H
