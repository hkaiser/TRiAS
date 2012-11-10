// DropSource für LegendenInfo ------------------------------------------------
// File: LDROPSRC.CXX

#include "triaspre.hxx"

#include "legdinfo.hxx"
#include "legwind.hxx"
#include "ldropsrc.hxx"

/*
 * CLegWindDropSource :: CLegWindDropSource
 * CLegWindDropSource :: ~CLegWindDropSource
 *
 * Constructor Parameters:
 *  pObj	CLegendeWindow *back pointer to whatever we live with.
 */
CLegWindDropSource :: CLegWindDropSource(CLegendeClientWindow *pBack)
{
	m_cRef = 0;
	m_pBack = pBack;
}


CLegWindDropSource :: ~CLegWindDropSource(void)
{
	// nothing to do
}

/*
 * CLegWindDropSource :: QueryInterface
 * CLegWindDropSource :: AddRef
 * CLegWindDropSource :: Release
 *
 * Purpose:
 *  Non-delegating IUnknown members for CLegWindDropSource.
 */
STDMETHODIMP CLegWindDropSource :: QueryInterface (REFIID riid, LPVOID FAR *ppv)
{
	*ppv=NULL;

// Any interface on this object is the object pointer.
	if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IDropSource))
		*ppv=(LPVOID)this;

/*
 * If we actually assign an interface to ppv we need to AddRef
 * it since we're returning a new pointer.
 */
	if (*ppv != NULL) {
		((LPUNKNOWN)*ppv)->AddRef();
		return NOERROR;
	}

return ResultFromScode(E_NOINTERFACE);
}


STDMETHODIMP_(ULONG) CLegWindDropSource :: AddRef(void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CLegWindDropSource :: Release(void)
{
ULONG cRefT = --m_cRef;

	if (m_cRef == 0L)
		delete this;

return cRefT;
}


/*
 * CLegWindDropSource :: QueryDragContinue
 *
 * Purpose:
 *  Determines whether to continue a drag operation or cancel it.
 *
 * Parameters:
 *  fEsc            bool indicating that the ESC key was pressed.
 *  grfKeyState     DWORD providing states of keys and mouse buttons
 *
 * Return Value:
 *  HRESULT         DRAGDROP_S_CANCEL to stop the drag,
 *                  DRAGDROP_S_DROP to drop the data where it is,
 *                  or NOERROR to continue.
 */
STDMETHODIMP CLegWindDropSource :: QueryContinueDrag (BOOL fEsc, DWORD grfKeyState)
{
	if (fEsc) return ResultFromScode (DRAGDROP_S_CANCEL);

	if (!(grfKeyState & MK_LBUTTON)) {
		if (m_pBack -> FQueryDrop()) 
			return ResultFromScode (DRAGDROP_S_DROP);
		else
			return ResultFromScode (DRAGDROP_S_CANCEL);
	}

return NOERROR;
}

/*
 * CLegWindDropSource :: GiveFeedback
 *
 * Purpose:
 *  Provides cursor feedback to the user since the source task
 *  always has the mouse capture.  We can also provide any other
 *  type of feedback above cursors if we so desire.
 *
 * Parameters:
 *  dwEffect        DWORD effect flags returned from the last target
 *
 * Return Value:
 *  HRESULT         NOERROR if you set a cursor yourself or
 *                  DRAGDROP_S_USEDEFAULTCURSORS to let OLE do
 *                  the work.
 */
STDMETHODIMP CLegWindDropSource :: GiveFeedback (DWORD dwEffect)
{
	return ResultFromScode (DRAGDROP_S_USEDEFAULTCURSORS);
}
