// DropSource für LegendenInfo ------------------------------------------------
// File: LDROPSRC.HXX

#if !defined(_LDROPSRC_HXX)
#define _LDROPSRC_HXX

class CLegWindDropSource;
typedef class CLegWindDropSource FAR *LPCLegWindDropSource;

class CLegWindDropSource : 
	public IDropSource 
{
protected:
    ULONG m_cRef;			// Interface reference count
    CLegendeClientWindow *m_pBack;	// Back pointer

public:
    CLegWindDropSource (CLegendeClientWindow *);
    ~CLegWindDropSource (void);

// IDropSource interface members
    STDMETHODIMP QueryInterface (REFIID, LPVOID FAR *);
    STDMETHODIMP_(ULONG) AddRef (void);
    STDMETHODIMP_(ULONG) Release (void);

    STDMETHODIMP QueryContinueDrag (BOOL, DWORD);
    STDMETHODIMP GiveFeedback (DWORD);
};


#endif //_LDROPSRC_HXX
