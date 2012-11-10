// DropTarget für Legendenfenster ---------------------------------------------
// File: LDROPTGT.HXX


#if !defined(_LDROPTGT_HXX)
#define _LDROPTGT_HXX

class CLegWindDropTarget;
typedef class CLegWindDropTarget *LPCLegWindDropTarget;

class CLegWindDropTarget : public IDropTarget {
protected:
        ULONG m_cRef;			// Interface reference count.
        CLegendeWindow *m_pBack;	// Back pointer
        LPDATAOBJECT m_pIDataObject;	// zu transportierende Daten

public:
	        CLegWindDropTarget (CLegendeWindow *);
	        ~CLegWindDropTarget (void);

// IDropTarget interface members
        STDMETHODIMP QueryInterface (REFIID, LPVOID FAR *);
        STDMETHODIMP_(ULONG) AddRef (void);
        STDMETHODIMP_(ULONG) Release (void);

        STDMETHODIMP DragEnter (LPDATAOBJECT, DWORD, POINTL, LPDWORD);
        STDMETHODIMP DragOver (DWORD, POINTL, LPDWORD);
        STDMETHODIMP DragLeave (void);
        STDMETHODIMP Drop (LPDATAOBJECT, DWORD, POINTL, LPDWORD);
};


#endif // _LDROPTGT_HXX
