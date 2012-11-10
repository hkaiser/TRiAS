// ImageList ----------------------------------------------------------------
// File: IMAGECTL.CXX

#include "tfrmpre.hxx"

CImageList::CImageList (HIMAGELIST hIML, BOOL fAutoDetach)
{
	m_fAutoDetach = fAutoDetach;
	m_hImageList = NULL;
	Attach (hIML);
}

CImageList::CImageList (void)
{
	m_hImageList = NULL;
	m_fAutoDetach = false;
}

CImageList::~CImageList (void)
{
	if (m_fAutoDetach) Detach();
	DeleteImageList();
}

HIMAGELIST CImageList::Detach()
{
HIMAGELIST hImageList = m_hImageList;

	m_hImageList = NULL;
	return hImageList;
}

BOOL CImageList::DeleteImageList()
{
	if (m_hImageList == NULL)
		return FALSE;

HIMAGELIST hImageList = Detach();

	_AppImpFind() -> ImagesList() -> Delete ((HANDLE)hImageList);

return ImageList_Destroy(hImageList);
}

BOOL CImageList::CreateList(int cx, int cy, BOOL bMask, int nInitial, int nGrow)
{
	if (!Attach(ImageList_Create(cx, cy, bMask, nInitial, nGrow)))
		return false;

	if (NULL != m_hImageList && !m_fAutoDetach) {
		_AppImpFind() -> ImagesList() -> Insert ((HANDLE)m_hImageList, this);
		return true;
	}

return false;
}

BOOL CImageList::CreateList(ResID RscID, int cx, int nGrow, COLORREF crMask)
{
pApp_Imp pAppImpInst = _AppImpFind();

	if (!Attach(ImageList_LoadBitmap(
		CV_RunTime::ResID_handle (RscID, pAppImpInst, RT_BITMAP),
		(LPCSTR)((ulong)((uint)RscID)), cx, nGrow, crMask)))
	{
		return false;
	}

	if (NULL != m_hImageList && !m_fAutoDetach) {
		pAppImpInst -> ImagesList() -> Insert ((HANDLE)m_hImageList, this);
		return true;
	}

return false;
}

BOOL CImageList::CreateList(CImageList& imagelist1, int nImage1, 
	CImageList& imagelist2, int nImage2, int dx, int dy)
{
	if (!Attach(ImageList_Merge(imagelist1.m_hImageList, nImage1, 
				    imagelist2.m_hImageList, nImage2, dx, dy)))
	{
		return false;
	}
	if (NULL != m_hImageList && !m_fAutoDetach) {
		_AppImpFind() -> ImagesList() -> Insert ((HANDLE)m_hImageList, this);
		return true;
	}

return false;
}

BOOL CImageList::Attach(HIMAGELIST hImageList)
{
	if (hImageList == NULL || m_hImageList != NULL)
		return false;

	m_hImageList = hImageList;

return true;
}

