// PVisInfoObj.cpp : Implementation of CPVisInfoObject

#include "visobjp.hxx"
#include "visobj.h"
#include "resource.h"

#include <dirisole.h>

#include "helper.h"
#include "VisInfoObj.h"
#if defined(__IRawVisInfo_INTERFACE_DEFINED__)
#include "Array.h"
#endif // __IRawVisInfo_INTERFACE_DEFINED__

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
//DefineSmartInterface2(DVisInfo, IID_DVisInfo);
DefineSmartInterface2(DPointVisInfo, IID_DPointVisInfo);
DefineSmartInterface2(DLineVisInfo, IID_DLineVisInfo);
DefineSmartInterface2(DAreaVisInfo, IID_DAreaVisInfo);
DefineSmartInterface2(DTextVisInfo, IID_DTextVisInfo);

/////////////////////////////////////////////////////////////////////////////
// ClassFactory etc.
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ObjVisInfoExtension, CVisObjExtension)

#if defined(__DefaultVisInfo_DEFINED__)
	OBJECT_ENTRY(CLSID_DefaultVisInfo, CVisInfoObject)
#endif // __DefaultVisInfo_DEFINED__
	OBJECT_ENTRY(CLSID_PointVisInfo, CPVisInfoObject)
	OBJECT_ENTRY(CLSID_LineVisInfo, CLVisInfoObject)
	OBJECT_ENTRY(CLSID_AreaVisInfo, CFVisInfoObject)
	OBJECT_ENTRY(CLSID_TextVisInfo, CTVisInfoObject)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap dieses Modules
}

/////////////////////////////////////////////////////////////////////////////
// CVisInfo<T> (IVisInfo)

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::get_isA (long *plRTTI)
{
	if (NULL == plRTTI)
		return E_POINTER;

	*plRTTI = GetVisTypeRTTI();

return NOERROR;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::get_Priority (int *piPrio)
{
	if (NULL == piPrio) return E_POINTER;
	*piPrio = GetVisInfo()->Priority();

	return NOERROR;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::put_Priority (int iPrio)
{
	GetVisInfo()->Priority() = iPrio;
	Changed() |= DO_PriorityChanged;
	return NOERROR;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::get_Style (int *piStyle)
{
	if (NULL == piStyle) return E_POINTER;
	*piStyle = GetVisInfo()->Style();

	return NOERROR;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::put_Style (int iStyle)
{
	GetVisInfo()->Style() = iStyle;
	Changed() |= DO_StyleChanged;
	return NOERROR;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::get_Name (BSTR *pbstrDesc)
{
	USES_CONVERSION;

	if (NULL == pbstrDesc) return E_POINTER;
	*pbstrDesc = SysAllocString(A2OLE(GetVisInfo()->VisName()));

	return NOERROR;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::put_Name (BSTR bstrDesc)
{
	USES_CONVERSION;

	GetVisInfo()->SetVisName(OLE2A(bstrDesc));
	Changed() |= DO_NameChanged;
	return NOERROR;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::get_MainColor (TRIASCOLOR *pocMain)
{
	if (NULL == pocMain) return E_POINTER;
	*pocMain = (COLORREF &)GetVisInfo()->PrimColor();

	return NOERROR;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::put_MainColor (TRIASCOLOR ocMain)
{
	GetVisInfo()->PrimColor() = (Color &)ocMain;
	Changed() |= DO_PrimColorChanged;
	return NOERROR;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::get_Changed (int *pfFlags)
{
	TEST_E_POINTER("CVisInfo<T, D, piid>::get_Changed", pfFlags);

	*pfFlags = Changed();
	return NOERROR;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::put_Changed (int fFlags)
{
	Changed() = fFlags;
	return NOERROR;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::get_VisString (BSTR *pbstrDesc)
{
	TEST_E_POINTER("CVisInfo<T, D, piid>::get_VisString", pbstrDesc);

HANDLEVISINFO *pHVI = NULL;
char *pVisString = NULL;

	RETURN_FAILED_HRESULT(CreateHANDLEVISINFO (this, GetVisType(), true, &pHVI));
	pVisString = VisInfoToString (pHVI);
	if (NULL == pVisString) 
		return (E_OUTOFMEMORY);

CComBSTR bstrVis (pVisString);

	if (!bstrVis)
		return (E_OUTOFMEMORY);

	*pbstrDesc = bstrVis.Detach();
	DELETE_OBJ(pVisString);
	dtHANDLEVISINFO(pHVI);

	return S_OK;
}

#if defined(__DefaultVisInfo_DEFINED__)
/////////////////////////////////////////////////////////////////////////////
// CVisInfoObject (ISupportErrorInfo)
STDMETHODIMP CVisInfoObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_DVisInfo,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
#endif // __DefaultVisInfo_DEFINED__

/////////////////////////////////////////////////////////////////////////////
// CPVisInfoObject (ISupportErrorInfo)

STDMETHODIMP CPVisInfoObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_DPointVisInfo,
		&IID_DVisInfo,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CPVisInfoObject (IPointVisInfo)

STDMETHODIMP CPVisInfoObject::get_BkColor (TRIASCOLOR *pocBack)
{
	if (NULL == pocBack) return E_POINTER;
	*pocBack = (COLORREF &)m_PVI.SecColor();

	return NOERROR;
}

STDMETHODIMP CPVisInfoObject::put_BkColor (TRIASCOLOR ocBack)
{
	m_PVI.SecColor() = (Color &)ocBack;
	Changed() |= DO_SecColorChanged;
	return NOERROR;
}

STDMETHODIMP CPVisInfoObject::get_SizeX (int *piX)
{
	if (NULL == piX) return E_POINTER;
	*piX = m_PVI.Size().Width();

	return NOERROR;
}

STDMETHODIMP CPVisInfoObject::put_SizeX (int iX)
{
	m_PVI.Size().Width() = iX;
	Changed() |= DO_SizeChanged;
	return NOERROR;
}

STDMETHODIMP CPVisInfoObject::get_SizeY (int *piY)
{
	if (NULL == piY) return E_POINTER;
	*piY = m_PVI.Size().Height();

	return NOERROR;
}

STDMETHODIMP CPVisInfoObject::put_SizeY (int iY)
{
	m_PVI.Size().Height() = iY;
	Changed() |= DO_SizeChanged;
	return NOERROR;
}

STDMETHODIMP CPVisInfoObject::get_Rotate (int *piRot)
{
	if (NULL == piRot) return E_POINTER;
	*piRot = m_PVI.Rotation();

	return NOERROR;
}

STDMETHODIMP CPVisInfoObject::put_Rotate (int iRot)
{
	m_PVI.Rotation() = iRot;
	Changed() |= DO_OthersChanged;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// CLVisInfoObject (ISupportErrorInfo)

STDMETHODIMP CLVisInfoObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_DLineVisInfo,
		&IID_DVisInfo,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CLVisInfoObject (ILineVisInfo)

STDMETHODIMP CLVisInfoObject::get_Width (int *piWidth)
{
	if (NULL == piWidth) return E_POINTER;
	*piWidth = m_LVI.Width();

	return NOERROR;
}

STDMETHODIMP CLVisInfoObject::put_Width (int iWidth)
{
	m_LVI.Width() = iWidth;
	Changed() |= DO_SizeChanged;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// CFVisInfoObject (ISupportErrorInfo)

STDMETHODIMP CFVisInfoObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_DAreaVisInfo,
		&IID_DVisInfo,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CFVisInfoObject (IAreaVisInfo)

STDMETHODIMP CFVisInfoObject::get_Width (int *piWidth)
{
	if (NULL == piWidth) return E_POINTER;
	*piWidth = m_FVI.Width();

	return NOERROR;
}

STDMETHODIMP CFVisInfoObject::put_Width (int iWidth)
{
	m_FVI.SetWidth (iWidth);
	Changed() |= DO_SizeChanged;
	return NOERROR;
}

STDMETHODIMP CFVisInfoObject::get_Opaque (int *pfOpaque)
{
	if (NULL == pfOpaque) return E_POINTER;
	*pfOpaque = m_FVI.isOpaque();

	return NOERROR;
}

STDMETHODIMP CFVisInfoObject::put_Opaque (int fOpaque)
{
short iAttrEx = m_FVI.AttrEx() & ~BMOpaque;

	if (fOpaque)
		iAttrEx |= BMOpaque;
	m_FVI.SetAttrEx (iAttrEx);
	Changed() |= DO_StyleChanged;
	return NOERROR;
}

STDMETHODIMP CFVisInfoObject::get_BkContour (int *pfBkContour)
{
	if (NULL == pfBkContour) return E_POINTER;
	*pfBkContour = m_FVI.isBkConture();

	return NOERROR;
}

STDMETHODIMP CFVisInfoObject::put_BkContour (int fBkContour)
{
short iAttrEx = m_FVI.AttrEx() & ~BMBkConture;

	if (fBkContour)
		iAttrEx |= BMBkConture;
	m_FVI.SetAttrEx (iAttrEx);
	Changed() |= DO_StyleChanged;
	return NOERROR;
}

STDMETHODIMP CFVisInfoObject::get_BkColor (TRIASCOLOR *pocBack)
{
	if (NULL == pocBack) return E_POINTER;
	*pocBack = (COLORREF &)m_FVI.SecColor();

	return NOERROR;
}

STDMETHODIMP CFVisInfoObject::put_BkColor (TRIASCOLOR ocBack)
{
	m_FVI.SecColor() = (Color &)ocBack;
	Changed() |= DO_SecColorChanged;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// CTVisInfoObject (ISupportErrorInfo)

STDMETHODIMP CTVisInfoObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_DTextVisInfo,
		&IID_DVisInfo,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CTVisInfoObject (ITextVisInfo)

STDMETHODIMP CTVisInfoObject::get_SizeX (int *piX)
{
	if (NULL == piX) return E_POINTER;
	*piX = m_TVI.Size().Width();

	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::put_SizeX (int iX)
{
	m_TVI.Size().Width() = iX;
	Changed() |= DO_SizeChanged;
	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::get_SizeY (int *piY)
{
	if (NULL == piY) return E_POINTER;
	*piY = m_TVI.Size().Height();

	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::put_SizeY (int iY)
{
	m_TVI.Size().Height() = iY;
	Changed() |= DO_SizeChanged;
	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::get_Bold (int *pfBold)
{
	if (NULL == pfBold) return E_POINTER;
	*pfBold = m_TVI.isBold();

	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::put_Bold (int fBold)
{
short iType = m_TVI.Type() & ~TV_Bold;

	if (fBold) iType |= TV_Bold;
	m_TVI.Type() = iType;
	Changed() |= DO_OthersChanged;
	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::get_Italic (int *pfItalic)
{
	if (NULL == pfItalic) return E_POINTER;
	*pfItalic = m_TVI.isItalic();

	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::put_Italic (int fItalic)
{
short iType = m_TVI.Type() & ~TV_Italic;

	if (fItalic) iType |= TV_Italic;
	m_TVI.Type() = iType;
	Changed() |= DO_OthersChanged;
	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::get_Underline (int *pfUnderline)
{
	if (NULL == pfUnderline) return E_POINTER;
	*pfUnderline = m_TVI.isUnderlined();

	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::put_Underline (int fUnderline)
{
short iType = m_TVI.Type() & ~TV_Underlined;

	if (fUnderline) iType |= TV_Underlined;
	m_TVI.Type() = iType;
	Changed() |= DO_OthersChanged;
	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::get_StrikeThrough (int *pfStrikeThrough)
{
	if (NULL == pfStrikeThrough) return E_POINTER;
	*pfStrikeThrough = m_TVI.isStrikedthru();

	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::put_StrikeThrough (int fStrikeThrough)
{
short iType = m_TVI.Type() & ~TV_StrikedThru;

	if (fStrikeThrough) iType |= TV_StrikedThru;
	m_TVI.Type() = iType;
	Changed() |= DO_OthersChanged;
	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::get_FrameStyle (FRAMESTYLE *prgFrameStyle)
{
	if (NULL == prgFrameStyle) return E_POINTER;

int rgStyle = FRAMESTYLE_NoFrame;

	if (m_TVI.FrameMode()) rgStyle |= FRAMESTYLE_SimpleFrame;
	if (m_TVI.RoundFrame()) rgStyle |= FRAMESTYLE_Rounded;
	if (!m_TVI.BKMode()) rgStyle |= FRAMESTYLE_TargetColor;

	*prgFrameStyle = (FRAMESTYLE)rgStyle;
	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::put_FrameStyle (FRAMESTYLE rgFrameStyle)
{
short iType = m_TVI.Type() & ~(TV_Frame|TV_RoundFrame|TV_BKMode);

	switch (rgFrameStyle) {
	case FRAMESTYLE_NoFrame:
		break;

	case FRAMESTYLE_SimpleFrame:
		iType |= TV_Frame;
		break;

	case FRAMESTYLE_Rounded:
		iType |= (TV_Frame|TV_RoundFrame);
		break;

	case FRAMESTYLE_TargetColor:
		iType |= TV_BKMode;
		break;
	}
	m_TVI.Type() = iType;
	Changed() |= DO_OthersChanged;
	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::get_AlignStyle (ALIGNSTYLE *prgAlign)
{
	if (NULL == prgAlign) return E_POINTER;
	*prgAlign = ALIGNSTYLE_Left;

	if (m_TVI.RightAlign()) 
		*prgAlign = ALIGNSTYLE_Right;
	else if (m_TVI.CentreAlign())
		*prgAlign = ALIGNSTYLE_Centre;
	else if (m_TVI.Justified())
		*prgAlign = ALIGNSTYLE_Full;

	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::put_AlignStyle (ALIGNSTYLE rgAlign)
{
short iType = m_TVI.Type() & ~TV_AlignStyle;

	switch (rgAlign) {
	case ALIGNSTYLE_Left:
		break;

	case ALIGNSTYLE_Right:
		iType |= TV_RightAlign;
		break;

	case ALIGNSTYLE_Centre:
		iType |= TV_CentreAlign;
		break;

	case ALIGNSTYLE_Full:
		iType |= TV_Justified;
		break;
	}
	m_TVI.Type() = iType;
	Changed() |= DO_OthersChanged;
	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::get_Rotate (int *piRot)
{
	if (NULL == piRot) return E_POINTER;
	*piRot = m_TVI.Rotation();

	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::put_Rotate (int iRot)
{
	m_TVI.Rotation() = iRot;
	Changed() |= DO_OthersChanged;
	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::get_Slant (int *piSlant)
{
	if (NULL == piSlant) return E_POINTER;
	*piSlant = m_TVI.Orientation();

	return NOERROR;
}

STDMETHODIMP CTVisInfoObject::put_Slant (int iSlant)
{
	m_TVI.Orientation() = iSlant;
	Changed() |= DO_OthersChanged;
	return NOERROR;
}


///////////////////////////////////////////////////////////////////////////////
// Erzeugen eines VisInfo-Objektes aus einer VISINFO
HRESULT FillBaseVisInfo (VISINFO *pVI, DVisInfo *pIVis)
{
	USES_CONVERSION;

	RETURN_FAILED_HRESULT(pIVis -> put_Priority (pVI -> m_Priority));
	RETURN_FAILED_HRESULT(pIVis -> put_Style (pVI -> m_Style));
	RETURN_FAILED_HRESULT(pIVis -> put_Name (CComBSTR(A2OLE(pVI -> m_VisName))));
	RETURN_FAILED_HRESULT(pIVis -> put_MainColor ((TRIASCOLOR &)pVI -> m_C));

	return S_OK;
}

#if defined(__DefaultVisInfo_DEFINED__)
HRESULT CreateVisInfo (VISINFO *pPVI, DVisInfo **ppIVis)
{
	TEST_E_POINTER("CreateVisInfo", ppIVis);
	*ppIVis = NULL;

	try {
	WDVisInfo Vis (CLSID_DefaultVisInfo);

		THROW_FAILED_HRESULT(FillBaseVisInfo ((VISINFO *)pPVI, Vis));
		*ppIVis = Vis.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}
#endif // __DefaultVisInfo_DEFINED__

HRESULT CreatePVisInfo (PVISINFO *pPVI, DVisInfo **ppIVis)
{
	TEST_E_POINTER("CreatePVisInfo", ppIVis);
	*ppIVis = NULL;

	try {
	WDPointVisInfo Vis (CLSID_PointVisInfo);

		THROW_FAILED_HRESULT(FillBaseVisInfo ((VISINFO *)pPVI, Vis));
		THROW_FAILED_HRESULT(Vis -> put_SizeX (pPVI -> m_Size.cx));
		THROW_FAILED_HRESULT(Vis -> put_SizeY (pPVI -> m_Size.cy));
		THROW_FAILED_HRESULT(Vis -> put_Rotate (pPVI -> m_iRot));
		THROW_FAILED_HRESULT(Vis -> put_BkColor ((TRIASCOLOR &)pPVI -> m_SecC));
	
		*ppIVis = Vis.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CreateLVisInfo (LVISINFO *pLVI, DVisInfo **ppIVis)
{
	TEST_E_POINTER("CreateLVisInfo", ppIVis);
	*ppIVis = NULL;

	try {
	WDLineVisInfo Vis (CLSID_LineVisInfo);

		THROW_FAILED_HRESULT(FillBaseVisInfo ((VISINFO *)pLVI, Vis));
		THROW_FAILED_HRESULT(Vis -> put_Width (pLVI -> m_Width));
	
		*ppIVis = Vis.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CreateFVisInfo (FVISINFO *pFVI, DVisInfo **ppIVis)
{
	TEST_E_POINTER("CreateFVisInfo", ppIVis);
	*ppIVis = NULL;

	try {
	WDAreaVisInfo Vis (CLSID_AreaVisInfo);

		THROW_FAILED_HRESULT(FillBaseVisInfo ((VISINFO *)pFVI, Vis));
		THROW_FAILED_HRESULT(Vis -> put_Width (pFVI -> m_iWidth));
		THROW_FAILED_HRESULT(Vis -> put_Opaque ((pFVI -> m_iAttrEx & BMOpaque) ? -1 : 0));
		THROW_FAILED_HRESULT(Vis -> put_BkContour ((pFVI -> m_iAttrEx & BMBkConture) ? -1 : 0));
		THROW_FAILED_HRESULT(Vis -> put_BkColor ((TRIASCOLOR &)pFVI -> m_FC));
	
		*ppIVis = Vis.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

inline FRAMESTYLE GetFrameStyle (TVISINFO *pTVI)
{
int iStyle = 0;

	if (pTVI -> m_Type & TV_Frame)
		iStyle |= FRAMESTYLE_SimpleFrame;
	if (pTVI -> m_Type & TV_RoundFrame)
		iStyle |= FRAMESTYLE_Rounded;
	if (pTVI -> m_Type & TV_BKMode)
		iStyle |= FRAMESTYLE_TargetColor;

	return (FRAMESTYLE)iStyle;
}

inline ALIGNSTYLE GetAlignStyle (TVISINFO *pTVI)
{
int iStyle = 0;

	if (pTVI -> m_Type & TV_CentreAlign)
		iStyle = ALIGNSTYLE_Centre;
	else if (pTVI -> m_Type & TV_RightAlign)
		iStyle = ALIGNSTYLE_Right;
	else if (pTVI -> m_Type & TV_Justified)
		iStyle = ALIGNSTYLE_Full;

	return (ALIGNSTYLE)iStyle;
}

HRESULT CreateTVisInfo (TVISINFO *pTVI, DVisInfo **ppIVis)
{
	TEST_E_POINTER("CreateTVisInfo", ppIVis);
	*ppIVis = NULL;

	try {
	WDTextVisInfo Vis (CLSID_TextVisInfo);

		THROW_FAILED_HRESULT(FillBaseVisInfo ((VISINFO *)pTVI, Vis));
		THROW_FAILED_HRESULT(Vis -> put_SizeX (pTVI -> m_Size.cx));
		THROW_FAILED_HRESULT(Vis -> put_SizeY (pTVI -> m_Size.cy));
		THROW_FAILED_HRESULT(Vis -> put_Bold ((pTVI -> m_Type & TV_Bold) ? -1 : 0));
		THROW_FAILED_HRESULT(Vis -> put_Italic ((pTVI -> m_Type & TV_Italic) ? -1 : 0));
		THROW_FAILED_HRESULT(Vis -> put_Underline ((pTVI -> m_Type & TV_Underlined) ? -1 : 0));
		THROW_FAILED_HRESULT(Vis -> put_StrikeThrough ((pTVI -> m_Type & TV_StrikedThru) ? -1 : 0));
		THROW_FAILED_HRESULT(Vis -> put_FrameStyle (GetFrameStyle(pTVI)));
		THROW_FAILED_HRESULT(Vis -> put_AlignStyle (GetAlignStyle(pTVI)));
		THROW_FAILED_HRESULT(Vis -> put_Rotate (pTVI -> m_Rot));
		THROW_FAILED_HRESULT(Vis -> put_Slant (pTVI -> m_Orient));

		*ppIVis = Vis.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CreateVisInfo (HANDLEVISINFO *pHVI, DVisInfo **ppIVis)
{
	TEST_E_POINTER("CreateVisInfo", ppIVis);
	TX_ASSERT(NULL != pHVI);

HRESULT hr = S_OK;

	switch (pHVI -> m_iVTyp) {
	case VTPunkt:
		{
			hr = CreatePVisInfo ((PVISINFO *)pHVI -> m_pVI, ppIVis);
			if (FAILED(hr)) return hr;
		}
		break;

	case VTLinie:	
		{
			hr = CreateLVisInfo ((LVISINFO *)pHVI -> m_pVI, ppIVis);
			if (FAILED(hr)) return hr;
		}
		break;

	case VTFlaeche:	
		{
			hr = CreateFVisInfo ((FVISINFO *)pHVI -> m_pVI, ppIVis);
			if (FAILED(hr)) return hr;
		}
		break;

	case VTText:	
		{
			hr = CreateTVisInfo ((TVISINFO *)pHVI -> m_pVI, ppIVis);
			if (FAILED(hr)) return hr;
		}
		break;

	case VTDefault:
#if defined(__DefaultVisInfo_DEFINED__)
		{
			hr = CreateVisInfo (pHVI -> m_pVI, ppIVis);
			if (FAILED(hr)) return hr;
		}
		break;
#else
	// hier durchfallen ...
	//
#endif // __DefaultVisInfo_DEFINED__
		
	default:
		return E_INVALIDARG;
	}

// für objektbezogene Visualisierung den objektbezogenen Anteil merken
	return (*ppIVis) -> put_Changed (pHVI -> m_fFlags);
}

///////////////////////////////////////////////////////////////////////////////
// Typrichtiges Generieren einer HANDLEVISINFO aus einem VisInfo-Objekt
HRESULT FillVisInfo (DVisInfo *pIVis, VISINFO *pVI)
{
int iData = 0;

	RETURN_FAILED_HRESULT(pIVis -> get_MainColor ((TRIASCOLOR *)&pVI -> m_C));

	RETURN_FAILED_HRESULT(pIVis -> get_Priority (&iData));
	pVI -> m_Priority = iData;
	RETURN_FAILED_HRESULT(pIVis -> get_Style (&iData));
	pVI -> m_Style = iData;

CComBSTR bstrName;

	USES_CONVERSION;
	RETURN_FAILED_HRESULT(pIVis -> get_Name (&bstrName));
	strcpy(pVI -> m_VisName, OLE2A(bstrName));

	return S_OK;
}

HRESULT FillPVisInfo (DPointVisInfo *pIVis, PVISINFO *pPVI)
{
int iData = 0;

	TX_ASSERT(sizeof(long) == sizeof(int));		// (int *) cast s.u.
	RETURN_FAILED_HRESULT(FillVisInfo (pIVis, (VISINFO *)pPVI));
	RETURN_FAILED_HRESULT(pIVis -> get_SizeX ((int *)&pPVI -> m_Size.cx));
	RETURN_FAILED_HRESULT(pIVis -> get_SizeY ((int *)&pPVI -> m_Size.cy));
	RETURN_FAILED_HRESULT(pIVis -> get_BkColor ((TRIASCOLOR *)&pPVI -> m_SecC));

	RETURN_FAILED_HRESULT(pIVis -> get_Rotate (&iData));
	pPVI -> m_iRot = iData;

	return S_OK;
}

HRESULT FillLVisInfo (DLineVisInfo *pIVis, LVISINFO *pLVI)
{
int iData = 0;

	RETURN_FAILED_HRESULT(FillVisInfo (pIVis, (VISINFO *)pLVI));
	RETURN_FAILED_HRESULT(pIVis -> get_Width (&iData));
	pLVI -> m_Width = iData;
		
	return S_OK;
}

inline void HandleBits (int fFlag, int &iData, int iBits)
{
	if (fFlag)  iData |= iBits;
	else		iData &= ~iBits;
}

HRESULT FillFVisInfo (DAreaVisInfo *pIVis, FVISINFO *pFVI)
{
int iData = 0;
int iAttrEx = pFVI -> m_iAttrEx;

	RETURN_FAILED_HRESULT(FillVisInfo (pIVis, (VISINFO *)pFVI));
	RETURN_FAILED_HRESULT(pIVis -> get_BkColor ((TRIASCOLOR *)&pFVI -> m_FC));

	RETURN_FAILED_HRESULT(pIVis -> get_Width (&iData));
	pFVI -> m_iWidth = iData;

	RETURN_FAILED_HRESULT(pIVis -> get_Opaque (&iData));
	HandleBits (iData, iAttrEx, BMOpaque);

	RETURN_FAILED_HRESULT(pIVis -> get_BkContour (&iData));
	HandleBits (iData, iAttrEx, BMBkConture);

	pFVI -> m_iAttrEx = iAttrEx;

	return S_OK;
}

HRESULT FillTVisInfo (DTextVisInfo *pIVis, TVISINFO *pTVI)
{
int iData = 0;

	TX_ASSERT(sizeof(long) == sizeof(int));		// (int *) cast s.u.

	RETURN_FAILED_HRESULT(FillVisInfo (pIVis, (VISINFO *)pTVI));
	RETURN_FAILED_HRESULT(pIVis -> get_SizeX ((int *)&pTVI -> m_Size.cx));
	RETURN_FAILED_HRESULT(pIVis -> get_SizeY ((int *)&pTVI -> m_Size.cy));
	RETURN_FAILED_HRESULT(pIVis -> get_Rotate (&iData));
	pTVI -> m_Rot = iData;
	RETURN_FAILED_HRESULT(pIVis -> get_Slant (&iData));
	pTVI -> m_Orient = iData;

int iType = pTVI -> m_Type;

	RETURN_FAILED_HRESULT(pIVis -> get_Bold (&iData));
	HandleBits (iData, iType, TV_Bold);

	RETURN_FAILED_HRESULT(pIVis -> get_Italic (&iData));
	HandleBits (iData, iType, TV_Italic);

	RETURN_FAILED_HRESULT(pIVis -> get_Underline (&iData));
	HandleBits (iData, iType, TV_Underlined);

	RETURN_FAILED_HRESULT(pIVis -> get_StrikeThrough (&iData));
	HandleBits (iData, iType, TV_StrikedThru);

FRAMESTYLE rgFrame;

	RETURN_FAILED_HRESULT(pIVis -> get_FrameStyle (&rgFrame));
	HandleBits (rgFrame & FRAMESTYLE_SimpleFrame, iType, TV_Frame);
	HandleBits (rgFrame & FRAMESTYLE_Rounded, iType, TV_RoundFrame);
	HandleBits (rgFrame & FRAMESTYLE_TargetColor, iType, TV_BKMode);

ALIGNSTYLE rgAlign;

	RETURN_FAILED_HRESULT(pIVis -> get_AlignStyle (&rgAlign));
	HandleBits (rgAlign == ALIGNSTYLE_Centre, iType, TV_CentreAlign);
	HandleBits (rgAlign == ALIGNSTYLE_Right, iType, TV_RightAlign);
	HandleBits (rgAlign == ALIGNSTYLE_Full, iType, TV_Justified);

	pTVI -> m_Type = iType;

	return S_OK;
}

short VTypeFromVISINFOTYPE (VISINFOTYPE rgType)
{
	switch (rgType) {
	case VISINFOTYPE_Point:
		return VTPunkt;

	case VISINFOTYPE_Line:
		return VTLinie;

	case VISINFOTYPE_Area:
		return VTFlaeche;

	case VISINFOTYPE_Text:
		return VTText;

	case VISINFOTYPE_Unknown:
	default:
		return VTDefault;
    }
}

HRESULT CreateHANDLEVISINFO (
	DVisInfo *pIVisInfo, VISINFOTYPE rgType, bool fFullSave, 
	HANDLEVISINFO **ppHVI)
{
	TEST_E_POINTER("CreateHANDLEVISINFO", ppHVI);
	TX_ASSERT(NULL != pIVisInfo);

HANDLEVISINFO *pHVI = NULL;

	COM_TRY {
		pHVI = ctHANDLEVISINFO(VTypeFromVISINFOTYPE(rgType));
		if (NULL == pHVI) _com_issue_error(E_OUTOFMEMORY);

		switch (pHVI -> m_iVTyp) {
		case VTPunkt:	
			THROW_FAILED_HRESULT(FillPVisInfo (WDPointVisInfo(pIVisInfo), (PVISINFO *)pHVI -> m_pVI));
			break;

		case VTLinie:
			THROW_FAILED_HRESULT(FillLVisInfo (WDLineVisInfo(pIVisInfo), (LVISINFO *)pHVI -> m_pVI));
			break;

		case VTFlaeche:
			THROW_FAILED_HRESULT(FillFVisInfo (WDAreaVisInfo(pIVisInfo), (FVISINFO *)pHVI -> m_pVI));
			break;

		case VTText:
			THROW_FAILED_HRESULT(FillTVisInfo (WDTextVisInfo(pIVisInfo), (TVISINFO *)pHVI -> m_pVI));
			break;

		case VTDefault:
			THROW_FAILED_HRESULT(FillVisInfo (WDVisInfo(pIVisInfo), pHVI -> m_pVI));
			break;

		default:
			_com_issue_error(E_INVALIDARG);
			TX_ASSERT(false);	// snh
			break;
		}

	// objektbezogenen Anteil bzw. geänderte Werte lesen
	int fFlags = DO_VisInfoChanged;

		if (fFullSave)
			pIVisInfo -> get_Changed (&fFlags);
		pHVI -> m_fFlags = fFlags;

		*ppHVI = pHVI;

	} COM_CATCH_OP(dtHANDLEVISINFO(pHVI));

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IVisObjExt
STDMETHODIMP CVisObjExtension::SetVisInfoClass (
	long lIdent, VISINFOTYPE rgType, DVisInfo *pIVisInfo, VARIANT vViewName)
{
// Erweiterung muß geladen sein
	if (!isLoaded()) return E_UNEXPECTED;

	USES_CONVERSION;

HANDLEVISINFO *pHVI;
CComVariant vView; 
bool fResult = false;

	try {
		THROW_FAILED_HRESULT(CreateHANDLEVISINFO(pIVisInfo, rgType, false, &pHVI));

		TX_ASSERT(pHVI -> m_iVTyp == (short)rgType);

		pHVI -> m_lIdent = lIdent;
		pHVI -> m_fFlags |= DF_ForceImport;

		if (SUCCEEDED(vView.ChangeType (VT_BSTR, &vViewName))) 
		{
		// Länge des Ansichtnamens gleich Null ist äquvalent zu keiner Ansicht
			if (SysStringLen(V_BSTR(&vView)) > 0)
				pHVI -> m_pView = OLE2A(V_BSTR(&vView));
		}

		fResult = DEX_ModIdentVisInfo(*pHVI);
		dtHANDLEVISINFO(pHVI);

	} catch (_com_error &e) {
		dtHANDLEVISINFO(pHVI);
		return _COM_ERROR(e);
	} 

	return fResult ? NOERROR : E_FAIL;
}

STDMETHODIMP CVisObjExtension::GetVisInfoClass (
	long lIdent, VISINFOTYPE rgType, VARIANT vViewName, DVisInfo **ppIVisInfo)
{
// Erweiterung muß geladen sein
	if (!isLoaded()) return E_UNEXPECTED;
	TEST_E_POINTER("CVisObjExtension::GetVisInfoClass", ppIVisInfo);

	*ppIVisInfo = NULL;
	USES_CONVERSION;

CComVariant vView; 
HANDLEVISINFO *pHVI = NULL;

	try {
		ATLTRY(pHVI = ctHANDLEVISINFO(VTypeFromVISINFOTYPE(rgType)));
		if (NULL == pHVI) _com_issue_error(E_OUTOFMEMORY);

		TX_ASSERT(pHVI -> m_iVTyp == VTypeFromVISINFOTYPE(rgType));
		pHVI -> m_lIdent = lIdent;

		if (SUCCEEDED(vView.ChangeType (VT_BSTR, &vViewName)))
		{
		// Länge des Ansichtnamens gleich Null ist äquvalent zu keiner Ansicht
			if (SysStringLen(V_BSTR(&vView)) > 0)
				pHVI -> m_pView = OLE2A(V_BSTR(&vView));
		}

		if (!DEX_GetIdentVisInfo(*pHVI))
			_com_issue_error(E_FAIL);

	// gelesene Info besorgen
	WDVisInfo Vis;

		THROW_FAILED_HRESULT(CreateVisInfo (pHVI, Vis.ppi()));
	
		*ppIVisInfo = Vis.detach();
		dtHANDLEVISINFO(pHVI);

	} catch (_com_error &e) {
		dtHANDLEVISINFO(pHVI);
		return _COM_ERROR(e);
	}

	return NOERROR;
}

STDMETHODIMP CVisObjExtension::ResetVisInfoClass (
	long lIdent, VISINFOTYPE rgType, VARIANT vView)
{
	ATLTRACENOTIMPL("CVisObjExtension::ResetVisInfoClass");
}

STDMETHODIMP CVisObjExtension::SetVisInfoObject (
	long lONr, VISINFOTYPE rgType, DVisInfo *pIVisInfo, VARIANT_BOOL fSameAsSource, VARIANT vViewName)
{
// Erweiterung muß geladen sein
	if (!isLoaded()) return E_UNEXPECTED;

	USES_CONVERSION;

bool fFirst = false;
HANDLEVISINFO *pHVI = NULL;
bool fResult = false;

	try {
		THROW_FAILED_HRESULT(CreateHANDLEVISINFO(pIVisInfo, rgType, fSameAsSource && !SaveFullVisInfo(), &pHVI));

		TX_ASSERT(pHVI -> m_iVTyp == VTypeFromVISINFOTYPE(rgType));

		pHVI -> m_lONr = lONr;
		pHVI -> m_lIdent = DEX_GetObjIdent (lONr);	// Ident wird gebraucht

	CComVariant vView; 

		if (SUCCEEDED(vView.ChangeType(VT_BSTR, &vViewName)))
		{
		// Länge des Ansichtnamens gleich Null ist äquvalent zu keiner Ansicht
			if (SysStringLen(V_BSTR(&vView)) > 0)
				pHVI -> m_pView = OLE2A(V_BSTR(&vView));
		}

		fResult = ModObjectVisInfo (pHVI, fFirst);
		dtHANDLEVISINFO(pHVI);

	} catch (_com_error &e) {
		dtHANDLEVISINFO(pHVI);
		return _COM_ERROR(e);
	} 

	return fResult ? NOERROR : E_FAIL;
}

STDMETHODIMP CVisObjExtension::GetVisInfoObject (
	long lONr, VISINFOTYPE rgType, VARIANT vViewName, DVisInfo **ppIVisInfo)
{
// Erweiterung muß geladen sein
	if (!isLoaded()) return E_UNEXPECTED;
	TEST_E_POINTER("CVisObjExtension::GetVisInfoObject", ppIVisInfo);

	*ppIVisInfo = NULL;

	USES_CONVERSION;

// VisInfo dieses Objektes besorgen
LPSTR pView = NULL;
CComVariant vView;

	if (SUCCEEDED(vView.ChangeType (VT_BSTR, &vViewName))) {
	// Länge des Ansichtnamens gleich Null ist äquvalent zu keiner Ansicht
		if (SysStringLen(V_BSTR(&vView)) > 0)
			pView = OLE2A(V_BSTR(&vView));
	}

HANDLEVISINFO *pHVI = GetObjectVisInfo (lONr, pView);

	if (NULL != pHVI) {
	WDVisInfo Vis;
	HRESULT hr = CreateVisInfo (pHVI, Vis.ppi());

		if (SUCCEEDED(hr))
			*ppIVisInfo = Vis.detach();
		dtHANDLEVISINFO (pHVI);		// Speicher freigeben
		return hr;
	}

	return E_OUTOFMEMORY;
}

STDMETHODIMP CVisObjExtension::ResetVisInfoObject (
	long lONr, VISINFOTYPE, VARIANT vView)
{
	USES_CONVERSION;

LPCSTR pView = NULL;
CComVariant vViewName;

	if (SUCCEEDED(vViewName.ChangeType (VT_BSTR, &vView)))
	{
	// Länge des Ansichtnamens gleich Null ist äquvalent zu keiner Ansicht
		if (SysStringLen(V_BSTR(&vView)) > 0)
			pView = OLE2A(V_BSTR(&vView));
	}
	return ResetObjectVisInfo (lONr, pView);
}

STDMETHODIMP CVisObjExtension::GetObjectHiddenStatus (long lONr, VARIANT vView, VARIANT_BOOL *pfShow)
{
	if (NULL == pfShow) return E_POINTER;

	USES_CONVERSION;

LPCSTR pView = NULL;
CComVariant vViewName;

	if (SUCCEEDED(vViewName.ChangeType (VT_BSTR, &vView)))
	{
	// Länge des Ansichtnamens gleich Null ist äquvalent zu keiner Ansicht
		if (SysStringLen(V_BSTR(&vView)) > 0)
			pView = OLE2A(V_BSTR(&vView));
	}

bool fShown = true;

	if (!GetHiddenFlag (lONr, fShown, pView))
		return E_FAIL;

	*pfShow = fShown ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CVisObjExtension::SetObjectHiddenStatus (long lONr, VARIANT_BOOL fShow, VARIANT vView)
{
	USES_CONVERSION;

LPCSTR pView = NULL;
CComVariant vViewName;

	if (SUCCEEDED(vViewName.ChangeType (VT_BSTR, &vView)))
	{
	// Länge des Ansichtnamens gleich Null ist äquvalent zu keiner Ansicht
		if (SysStringLen(V_BSTR(&vView)) > 0)
			pView = OLE2A(V_BSTR(&vView));
	}

bool fFirst = false;

	return HandleHiddenFlag (lONr, fShow ? true : false, fFirst, pView);
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::IsDirty (void)
{
	return m_fChanged == 0 ? S_FALSE : S_OK;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::Load (LPSTREAM pStm, VisInfo *pVI)
{
	if (m_fInitialized)
		return E_UNEXPECTED;

short iData = 0;
long lData = 0;

	TX_ASSERT(sizeof(int) == sizeof(long));
	RETURN_FAILED_HRESULT(LoadLong (pStm, (long &)m_fChanged));
	RETURN_FAILED_HRESULT(LoadShort (pStm, iData));
	pVI -> Priority() = iData;

	RETURN_FAILED_HRESULT(LoadShort (pStm, iData));
	pVI -> Style() = iData;

	RETURN_FAILED_HRESULT(LoadChunk (pStm, pVI -> VisName(), VISNAMESIZE+1));

	RETURN_FAILED_HRESULT(LoadLong (pStm, lData));
	pVI -> PrimColor() = (Color &)lData;

	m_fInitialized = true;
	return S_OK;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::Save (LPSTREAM pStm, BOOL fClearDirty, VisInfo *pVI)
{
	RETURN_FAILED_HRESULT(SaveLong (pStm, m_fChanged));
	RETURN_FAILED_HRESULT(SaveShort (pStm, pVI -> Priority()));
	RETURN_FAILED_HRESULT(SaveShort (pStm, pVI -> Style()));
	RETURN_FAILED_HRESULT(SaveChunk (pStm, pVI -> VisName(), VISNAMESIZE+1));
	RETURN_FAILED_HRESULT(SaveLong (pStm, (long &)pVI -> PrimColor()));

	if (fClearDirty)
		m_fChanged = 0;
	return S_OK;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::GetSizeMax (ULARGE_INTEGER *pCbSize)
{
	TEST_E_POINTER("CVisInfo<T, D, piid>::GetSizeMax", pCbSize);
	pCbSize -> QuadPart = 2*sizeof(long) + 2*sizeof(short) + (VISNAMESIZE+1);
	return S_OK;
}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::InitNew (void)
{
	if (m_fInitialized)
		return E_UNEXPECTED;
	m_fInitialized = true;
	return S_OK;
}

#if defined(__DefaultVisInfo_DEFINED__)
///////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CVisInfoObject::GetClassID (GUID *pClsId)
{
	TEST_E_POINTER("CVisInfoObject::GetClassID", pClsId);
	*pClsId = CLSID_DefaultVisInfo;
	return S_OK;
}

STDMETHODIMP CVisInfoObject::Load (LPSTREAM pStm)
{
	return visinfo_t::Load (pStm, &m_VI);
}

STDMETHODIMP CVisInfoObject::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	return visinfo_t::Save (pStm, fClearDirty, &m_VI);
}

STDMETHODIMP CVisInfoObject::GetSizeMax (ULARGE_INTEGER *pCbSize)
{
	return visinfo_t::GetSizeMax (pCbSize);
}
#endif // __DefaultVisInfo_DEFINED__

///////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CPVisInfoObject::GetClassID (GUID *pClsId)
{
	TEST_E_POINTER("CPVisInfoObject::GetClassID", pClsId);
	*pClsId = CLSID_PointVisInfo;
	return S_OK;
}

STDMETHODIMP CPVisInfoObject::Load (LPSTREAM pStm)
{
	RETURN_FAILED_HRESULT(visinfo_t::Load (pStm, &m_PVI));
	RETURN_FAILED_HRESULT(LoadLong (pStm, m_PVI.Size().Width()));
	RETURN_FAILED_HRESULT(LoadLong (pStm, m_PVI.Size().Height()));
	RETURN_FAILED_HRESULT(LoadLong (pStm, (long &)m_PVI.SecColor()));
	RETURN_FAILED_HRESULT(LoadShort (pStm, m_PVI.Rotation()));
	return S_OK;
}

STDMETHODIMP CPVisInfoObject::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(visinfo_t::Save (pStm, fClearDirty, &m_PVI));
	RETURN_FAILED_HRESULT(SaveLong (pStm, m_PVI.Size().Width()));
	RETURN_FAILED_HRESULT(SaveLong (pStm, m_PVI.Size().Height()));
	RETURN_FAILED_HRESULT(SaveLong (pStm, (long &)m_PVI.SecColor()));
	RETURN_FAILED_HRESULT(SaveShort (pStm, m_PVI.Rotation()));
	return S_OK;
}

STDMETHODIMP CPVisInfoObject::GetSizeMax (ULARGE_INTEGER *pCbSize)
{
	RETURN_FAILED_HRESULT(visinfo_t::GetSizeMax (pCbSize));
	pCbSize -> QuadPart += 3*sizeof(long) + sizeof(short);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CLVisInfoObject::GetClassID (GUID *pClsId)
{
	TEST_E_POINTER("CLVisInfoObject::GetClassID", pClsId);
	*pClsId = CLSID_LineVisInfo;
	return S_OK;
}

STDMETHODIMP CLVisInfoObject::Load (LPSTREAM pStm)
{
	RETURN_FAILED_HRESULT(visinfo_t::Load (pStm, &m_LVI));
	RETURN_FAILED_HRESULT(LoadShort (pStm, m_LVI.Width()));
	return S_OK;
}

STDMETHODIMP CLVisInfoObject::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(visinfo_t::Save (pStm, fClearDirty, &m_LVI));
	RETURN_FAILED_HRESULT(SaveShort (pStm, m_LVI.Width()));
	return S_OK;
}

STDMETHODIMP CLVisInfoObject::GetSizeMax (ULARGE_INTEGER *pCbSize)
{
	RETURN_FAILED_HRESULT(visinfo_t::GetSizeMax (pCbSize));
	pCbSize -> QuadPart += sizeof(short);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CFVisInfoObject::GetClassID (GUID *pClsId)
{
	TEST_E_POINTER("CFVisInfoObject::GetClassID", pClsId);
	*pClsId = CLSID_AreaVisInfo;
	return S_OK;
}

STDMETHODIMP CFVisInfoObject::Load (LPSTREAM pStm)
{
	RETURN_FAILED_HRESULT(visinfo_t::Load (pStm, &m_FVI));
	RETURN_FAILED_HRESULT(LoadLong (pStm, (long &)m_FVI.SecColor()));
	return S_OK;
}

STDMETHODIMP CFVisInfoObject::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(visinfo_t::Save (pStm, fClearDirty, &m_FVI));
	RETURN_FAILED_HRESULT(SaveLong (pStm, (long &)m_FVI.SecColor()));
	return S_OK;
}

STDMETHODIMP CFVisInfoObject::GetSizeMax (ULARGE_INTEGER *pCbSize)
{
	RETURN_FAILED_HRESULT(visinfo_t::GetSizeMax (pCbSize));
	pCbSize -> QuadPart += sizeof(long);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CTVisInfoObject::GetClassID (GUID *pClsId)
{
	TEST_E_POINTER("CTVisInfoObject::GetClassID", pClsId);
	*pClsId = CLSID_TextVisInfo;
	return S_OK;
}

STDMETHODIMP CTVisInfoObject::Load (LPSTREAM pStm)
{
	RETURN_FAILED_HRESULT(visinfo_t::Load (pStm, &m_TVI));
	RETURN_FAILED_HRESULT(LoadShort (pStm, m_TVI.Type()));
	RETURN_FAILED_HRESULT(LoadLong (pStm, m_TVI.Size().Width()));
	RETURN_FAILED_HRESULT(LoadLong (pStm, m_TVI.Size().Height()));
	RETURN_FAILED_HRESULT(LoadShort (pStm, m_TVI.Rotation()));
	RETURN_FAILED_HRESULT(LoadShort (pStm, m_TVI.Orientation()));
	return S_OK;
}

STDMETHODIMP CTVisInfoObject::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(visinfo_t::Save (pStm, fClearDirty, &m_TVI));
	RETURN_FAILED_HRESULT(SaveShort (pStm, m_TVI.Type()));
	RETURN_FAILED_HRESULT(SaveLong (pStm, m_TVI.Size().Width()));
	RETURN_FAILED_HRESULT(SaveLong (pStm, m_TVI.Size().Height()));
	RETURN_FAILED_HRESULT(SaveShort (pStm, m_TVI.Rotation()));
	RETURN_FAILED_HRESULT(SaveShort (pStm, m_TVI.Orientation()));
	return S_OK;
}

STDMETHODIMP CTVisInfoObject::GetSizeMax (ULARGE_INTEGER *pCbSize)
{
	RETURN_FAILED_HRESULT(visinfo_t::GetSizeMax (pCbSize));
	pCbSize -> QuadPart += 2*sizeof(long) + 3*sizeof(short);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IMergeVisInfo 
#define MERGEVIS(flag,type,attr,vis)					\
	if (!fOnlyChanged || (Changed() & (flag))) {		\
	type T;												\
														\
		RETURN_FAILED_HRESULT(get_##attr(&T));			\
		RETURN_FAILED_HRESULT((vis) -> put_##attr(T));	\
	}

template<class T, class D, const GUID *piid>
STDMETHODIMP CVisInfo<T, D, piid>::MergeVisInfo (VARIANT_BOOL fOnlyChanged, DVisInfo **ppIVisInfo)
{
	MERGEVIS(DO_StyleChanged, int, Style, *ppIVisInfo);
	MERGEVIS(DO_NameChanged, CComBSTR, Name, *ppIVisInfo);
	MERGEVIS(DO_PrimColorChanged, TRIASCOLOR, MainColor, *ppIVisInfo);

	return S_OK;
}

#if defined(__DefaultVisInfo_DEFINED__)
STDMETHODIMP CVisInfoObject::MergeVisInfo (VARIANT_BOOL fOnlyChanged, DVisInfo **ppIVisInfo)
{
	TEST_E_POINTER("CVisInfoObject::MergeVisInfo", ppIVisInfo);
	TEST_E_POINTER("CVisInfoObject::MergeVisInfo", *ppIVisInfo);

// DVisInfo behandlen
	return visinfo_t::MergeVisInfo (fOnlyChanged, ppIVisInfo);
}
#endif // __DefaultVisInfo_DEFINED__

STDMETHODIMP CPVisInfoObject::MergeVisInfo (VARIANT_BOOL fOnlyChanged, DVisInfo **ppIVisInfo)
{
	TEST_E_POINTER("CPVisInfoObject::MergeVisInfo", ppIVisInfo);
	TEST_E_POINTER("CPVisInfoObject::MergeVisInfo", *ppIVisInfo);

// DVisInfo behandlen
	RETURN_FAILED_HRESULT(visinfo_t::MergeVisInfo (fOnlyChanged, ppIVisInfo));

WDPointVisInfo PVis;

	if (SUCCEEDED((*ppIVisInfo) -> QueryInterface(IID_DPointVisInfo, PVis.ppv()))) {
	// wenn die Typen passen, dann den Rest mergen
		MERGEVIS(DO_SecColorChanged, TRIASCOLOR, BkColor, PVis);
		MERGEVIS(DO_SizeChanged, int, SizeX, PVis);
		MERGEVIS(DO_SizeChanged, int, SizeY, PVis);
		MERGEVIS(DO_OthersChanged, int, Rotate, PVis);
	}

	return S_OK;
}

STDMETHODIMP CLVisInfoObject::MergeVisInfo (VARIANT_BOOL fOnlyChanged, DVisInfo **ppIVisInfo)
{
	TEST_E_POINTER("CLVisInfoObject::MergeVisInfo", ppIVisInfo);
	TEST_E_POINTER("CLVisInfoObject::MergeVisInfo", *ppIVisInfo);

// DVisInfo behandlen
	RETURN_FAILED_HRESULT(visinfo_t::MergeVisInfo (fOnlyChanged, ppIVisInfo));

WDLineVisInfo LVis;

	if (SUCCEEDED((*ppIVisInfo) -> QueryInterface(IID_DLineVisInfo, LVis.ppv()))) {
	// wenn die Typen passen, dann den Rest mergen
		MERGEVIS(DO_SizeChanged, int, Width, LVis);
	}

	return S_OK;
}

STDMETHODIMP CFVisInfoObject::MergeVisInfo (VARIANT_BOOL fOnlyChanged, DVisInfo **ppIVisInfo)
{
	TEST_E_POINTER("CFVisInfoObject::MergeVisInfo", ppIVisInfo);
	TEST_E_POINTER("CFVisInfoObject::MergeVisInfo", *ppIVisInfo);

// DVisInfo behandlen
	RETURN_FAILED_HRESULT(visinfo_t::MergeVisInfo (fOnlyChanged, ppIVisInfo));

WDAreaVisInfo FVis;

	if (SUCCEEDED((*ppIVisInfo) -> QueryInterface(IID_DAreaVisInfo, FVis.ppv()))) {
	// wenn die Typen passen, dann den Rest mergen
		MERGEVIS(DO_SizeChanged, int, Width, FVis);
		MERGEVIS(DO_StyleChanged, int, Opaque, FVis);
		MERGEVIS(DO_StyleChanged, int, BkContour, FVis);
		MERGEVIS(DO_SecColorChanged, TRIASCOLOR, BkColor, FVis);
	}

	return S_OK;
}

STDMETHODIMP CTVisInfoObject::MergeVisInfo (VARIANT_BOOL fOnlyChanged, DVisInfo **ppIVisInfo)
{
	TEST_E_POINTER("CTVisInfoObject::MergeVisInfo", ppIVisInfo);
	TEST_E_POINTER("CTVisInfoObject::MergeVisInfo", *ppIVisInfo);

// DVisInfo behandlen
	RETURN_FAILED_HRESULT(visinfo_t::MergeVisInfo (fOnlyChanged, ppIVisInfo));

WDTextVisInfo TVis;

	if (SUCCEEDED((*ppIVisInfo) -> QueryInterface(IID_DTextVisInfo, TVis.ppv()))) {
	// wenn die Typen passen, dann den Rest mergen
		MERGEVIS(DO_SizeChanged, int, SizeX, TVis);
		MERGEVIS(DO_SizeChanged, int, SizeY, TVis);
		MERGEVIS(DO_OthersChanged, int, Bold, TVis);
		MERGEVIS(DO_OthersChanged, int, Italic, TVis);
		MERGEVIS(DO_OthersChanged, int, Underline, TVis);
		MERGEVIS(DO_OthersChanged, int, StrikeThrough, TVis);
		MERGEVIS(DO_OthersChanged, FRAMESTYLE, FrameStyle, TVis);
		MERGEVIS(DO_OthersChanged, ALIGNSTYLE, AlignStyle, TVis);
		MERGEVIS(DO_OthersChanged, int, Rotate, TVis);
		MERGEVIS(DO_OthersChanged, int, Slant, TVis);
	}

	return S_OK;
}

#if defined(__IRawVisInfo_INTERFACE_DEFINED__)
///////////////////////////////////////////////////////////////////////////////
// ZugriffsFunktionen auf interne VisInfo-Objekte
// IRawVisInfo
HRESULT CVisInfoInterfaceBase::SetRawData (BSTR bstrData)
{
SAFEARRAY *psa = NULL;

	RETURN_FAILED_HRESULT(VectorFromBstr (bstrData, &psa));

CSafeArray sa (VT_UI1, psa);
CSafeArrayLock<unsigned char> lock (sa);

	TX_ASSERT(lock.Size() == sizeof(VisInfo) - sizeof(void *));		// vtable
	memcpy (((unsigned char *)GetVisInfo()) + sizeof(void *), lock, lock.Size());
	return S_OK;
}

HRESULT CVisInfoInterfaceBase::RetrieveRawData (BSTR *pData)
{
CSafeArray sa (VT_UI1, sizeof(VisInfo)-sizeof(void *));		// vtable

	{
	CSafeArrayLock<unsigned char> lock (sa);

		memcpy (lock, ((unsigned char *)GetVisInfo()) + sizeof(void *), lock.Size());
	}
	return BstrFromVector (sa, pData);
}

#if defined(__DefaultVisInfo_DEFINED__)
///////////////////////////////////////////////////////////////////////////////
// CVisInfoObject
STDMETHODIMP CVisInfoObject::SetRawData (VISINFOTYPE rgType, BSTR bstrData)
{
	if (VISINFOTYPE_Default != rgType)
		return E_INVALIDARG;

HRESULT hr = CVisInfoInterfaceBase::SetRawData (bstrData);

	Changed() = DO_VisInfoChanged;		// alles geändert
	return hr;
}

STDMETHODIMP CVisInfoObject::RetrieveRawData (VISINFOTYPE rgType, BSTR *pData)
{
	if (VISINFOTYPE_Default != rgType)
		return E_INVALIDARG;
	return CVisInfoInterfaceBase::RetrieveRawData (pData);
}
#endif // __DefaultVisInfo_DEFINED__

///////////////////////////////////////////////////////////////////////////////
// CPVisInfoObject
STDMETHODIMP CPVisInfoObject::SetRawData (VISINFOTYPE rgType, BSTR bstrData)
{
	if (VISINFOTYPE_Default == rgType)
		return CVisInfoInterfaceBase::SetRawData (bstrData);

	if (VISINFOTYPE_Point != rgType)
		return E_INVALIDARG;

SAFEARRAY *psa = NULL;

	RETURN_FAILED_HRESULT(VectorFromBstr (bstrData, &psa));

CSafeArray sa (VT_UI1, psa);
CSafeArrayLock<unsigned char> lock (sa);

	TX_ASSERT(lock.Size() == sizeof(PVisInfo) - sizeof(void *));		// vtable
	memcpy (((unsigned char *)GetVisInfo()) + sizeof(void *), lock, lock.Size());

	Changed() = DO_VisInfoChanged;		// alles geändert
	return S_OK;
}

STDMETHODIMP CPVisInfoObject::RetrieveRawData (VISINFOTYPE rgType, BSTR *pData)
{
	if (VISINFOTYPE_Default == rgType)
		return CVisInfoInterfaceBase::RetrieveRawData (pData);

	if (VISINFOTYPE_Point != rgType)
		return E_INVALIDARG;

CSafeArray sa (VT_UI1, sizeof(PVisInfo)-sizeof(void *));		// vtable

	{
	CSafeArrayLock<unsigned char> lock (sa);

		memcpy (lock, ((unsigned char *)&m_PVI) + sizeof(void *), lock.Size());
	}
	return BstrFromVector (sa, pData);
}

///////////////////////////////////////////////////////////////////////////////
// CLVisInfoObject
STDMETHODIMP CLVisInfoObject::SetRawData (VISINFOTYPE rgType, BSTR bstrData)
{
	if (VISINFOTYPE_Default == rgType)
		return CVisInfoInterfaceBase::SetRawData (bstrData);

	if (VISINFOTYPE_Line != rgType)
		return E_INVALIDARG;

SAFEARRAY *psa = NULL;

	RETURN_FAILED_HRESULT(VectorFromBstr (bstrData, &psa));

CSafeArray sa (VT_UI1, psa);
CSafeArrayLock<unsigned char> lock (sa);

	TX_ASSERT(lock.Size() == sizeof(LVisInfo) - sizeof(void *));		// vtable
	memcpy (((unsigned char *)GetVisInfo()) + sizeof(void *), lock, lock.Size());

	Changed() = DO_VisInfoChanged;		// alles geändert
	return S_OK;
}

STDMETHODIMP CLVisInfoObject::RetrieveRawData (VISINFOTYPE rgType, BSTR *pData)
{
	if (VISINFOTYPE_Default == rgType)
		return CVisInfoInterfaceBase::RetrieveRawData (pData);

	if (VISINFOTYPE_Line != rgType)
		return E_INVALIDARG;

CSafeArray sa (VT_UI1, sizeof(LVisInfo)-sizeof(void *));		// vtable

	{
	CSafeArrayLock<unsigned char> lock (sa);

		memcpy (lock, ((unsigned char *)&m_LVI) + sizeof(void *), lock.Size());
	}
	return BstrFromVector (sa, pData);
}

///////////////////////////////////////////////////////////////////////////////
// CFVisInfoObject
STDMETHODIMP CFVisInfoObject::SetRawData (VISINFOTYPE rgType, BSTR bstrData)
{
	if (VISINFOTYPE_Default == rgType)
		return CVisInfoInterfaceBase::SetRawData (bstrData);

	if (VISINFOTYPE_Area != rgType)
		return E_INVALIDARG;

SAFEARRAY *psa = NULL;

	RETURN_FAILED_HRESULT(VectorFromBstr (bstrData, &psa));

CSafeArray sa (VT_UI1, psa);
CSafeArrayLock<unsigned char> lock (sa);

	TX_ASSERT(lock.Size() == sizeof(FVisInfo) - sizeof(void *));		// vtable
	memcpy (((unsigned char *)GetVisInfo()) + sizeof(void *), lock, lock.Size());

	Changed() = DO_VisInfoChanged;		// alles geändert
	return S_OK;
}

STDMETHODIMP CFVisInfoObject::RetrieveRawData (VISINFOTYPE rgType, BSTR *pData)
{
	if (VISINFOTYPE_Default == rgType)
		return CVisInfoInterfaceBase::RetrieveRawData (pData);

	if (VISINFOTYPE_Area != rgType)
		return E_INVALIDARG;

CSafeArray sa (VT_UI1, sizeof(FVisInfo)-sizeof(void *));		// vtable

	{
	CSafeArrayLock<unsigned char> lock (sa);

		memcpy (lock, ((unsigned char *)&m_FVI) + sizeof(void *), lock.Size());
	}
	return BstrFromVector (sa, pData);
}

///////////////////////////////////////////////////////////////////////////////
// CTVisInfoObject
STDMETHODIMP CTVisInfoObject::SetRawData (VISINFOTYPE rgType, BSTR bstrData)
{
	if (VISINFOTYPE_Default == rgType)
		return CVisInfoInterfaceBase::SetRawData (bstrData);

	if (VISINFOTYPE_Text != rgType)
		return E_INVALIDARG;

SAFEARRAY *psa = NULL;

	RETURN_FAILED_HRESULT(VectorFromBstr (bstrData, &psa));

CSafeArray sa (VT_UI1, psa);
CSafeArrayLock<unsigned char> lock (sa);

	TX_ASSERT(lock.Size() == sizeof(TVisInfo) - sizeof(void *));		// vtable
	memcpy (((unsigned char *)GetVisInfo()) + sizeof(void *), lock, lock.Size());

	Changed() = DO_VisInfoChanged;		// alles geändert
	return S_OK;
}

STDMETHODIMP CTVisInfoObject::RetrieveRawData (VISINFOTYPE rgType, BSTR *pData)
{
	if (VISINFOTYPE_Default == rgType)
		return CVisInfoInterfaceBase::RetrieveRawData (pData);

	if (VISINFOTYPE_Text != rgType)
		return E_INVALIDARG;

CSafeArray sa (VT_UI1, sizeof(TVisInfo)-sizeof(void *));		// vtable

	{
	CSafeArrayLock<unsigned char> lock (sa);

		memcpy (lock, ((unsigned char *)&m_TVI) + sizeof(void *), lock.Size());
	}
	return BstrFromVector (sa, pData);
}
#endif // __IRawVisInfo_INTERFACE_DEFINED__
