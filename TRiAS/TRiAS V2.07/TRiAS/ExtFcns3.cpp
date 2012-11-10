// $Header: /TRiAS/TRiAS V2.07/TRiAS/ExtFcns3.cpp 2     15.06.98 22:18 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 05/27/1998 07:55:46 PM
//
// @doc
// @module ExtFcns3.cpp | Fuktionen, die bei externen Messages gerufen werden

#include "triaspre.hxx"

#include <dirisole.h>

#include "obj32/TRiASVersion.h"
#include "extmain3.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// DEX_ENUMEXTENSIONS
LRESULT ExtDirisWindow::OnEnumExtensions (HPROJECT, LPARAM lParam)
{
ENUMNOKEY *pK = (ENUMNOKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMNOKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
	return EnumExtensions (pK);
}

// DEX_QUERYEXTENSIONINFO
LRESULT ExtDirisWindow::OnGetExtensionInfo (HPROJECT, LPARAM lParam)
{
EXTENSIONINFO *pInfo = (EXTENSIONINFO *)lParam;

	TX_ASSERT_POINTER(pInfo, EXTENSIONINFO);
	TX_ASSERT(sizeof(EXTENSIONINFO) == pInfo -> dwSize);
	TX_ASSERT(TIsValidString(pInfo -> pcDLLName));
	TX_ASSERT(TIsValidAddress(pInfo -> pName, pInfo -> iLen, true));
	return GetExtensionInfo (pInfo);
}

// DEX_QUERYEXTENSIONPTR
LRESULT ExtDirisWindow::OnGetExtensionPtr (HPROJECT, LPARAM lParam)
{
EXTENSIONPTR *pInfo = (EXTENSIONPTR *)lParam;

	TX_ASSERT_POINTER(pInfo, EXTENSIONPTR);
	TX_ASSERT(sizeof(EXTENSIONPTR) == pInfo -> dwSize);
	TX_ASSERT(TIsValidString(pInfo -> pcDLLName));
	return GetExtensionPtr (pInfo);
}

// DEX_QUERYPREVENTREPAINT
LRESULT ExtDirisWindow::OnQueryPreventRepaint (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);

	return LRESULT(m_pView -> GetPreventRepaint());
}

// DEX_PREVENTREPAINT
LRESULT ExtDirisWindow::OnPreventRepaint (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(FALSE);

	m_pView -> SetPreventRepaint(bool(lParam));
	return LRESULT(TRUE);
}


// DEX_QUERYACTASPECTRATIO
LRESULT ExtDirisWindow::OnGetActiveAspect (HPROJECT, LPARAM lParam)
{
	TX_ASSERT_POINTER((double *)lParam, double);
	if (!IsValidActiveView() || 0 == lParam)
		return LPARAM(FALSE);

	*(double *)lParam = DBO().GetAspectRatio();
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// DEX_MODIFYIDENTSCALEDATA
LRESULT ExtDirisWindow::OnModifyIdentScaleData (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView() || 0 == lParam)
		return LPARAM(FALSE);

IDENTSCALEDATA *pISD = (IDENTSCALEDATA *)lParam;

#if defined(_DEBUG)
	TX_ASSERT_POINTER(pISD, IDENTSCALEDATA);
	TX_ASSERT(pISD -> pcView == NULL || TIsValidString(pISD -> pcView));
	TX_ASSERT(IsValidIdent(pISD -> lIdent));
#endif // _DEBUG

	return DBO().SetIdentScaleData(
			pISD -> pcView, pISD -> lIdent, VisType(pISD -> iVTyp), 
			pISD -> lUpperScale, pISD -> lLowerScale) ? TRUE : FALSE;
}

// DEX_QUERYIDENTSCALEDATA
LRESULT ExtDirisWindow::OnGetIdentScaleData (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView() || 0 == lParam)
		return LPARAM(FALSE);

IDENTSCALEDATA *pISD = (IDENTSCALEDATA *)lParam;

#if defined(_DEBUG)
	TX_ASSERT_POINTER(pISD, IDENTSCALEDATA);
	TX_ASSERT(pISD -> pcView == NULL || TIsValidString(pISD -> pcView));
	TX_ASSERT(IsValidIdent(pISD -> lIdent));
#endif // _DEBUG

	return DBO().RetrieveIdentScaleData (
				pISD -> pcView, pISD -> lIdent, VisType(pISD -> iVTyp), 
				&pISD -> lUpperScale, &pISD -> lLowerScale) ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Maﬂstabsbereich testen (nur, wenn Bereich gegeben ist
namespace {
inline 
bool FMatchScales (long lActScale, long lUpperScale, long lLowerScale)
{
	if (0 != lUpperScale && lActScale < lUpperScale)
		return false;

	if (0 != lLowerScale && lActScale > lLowerScale)
		return false;

	return true;
}
}

// DEX_TESTIDENTSCALETOPAINT
LRESULT ExtDirisWindow::OnTestIdentScaleToPaint (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView() || 0 == lParam)
		return LPARAM(FALSE);

IDENTSCALEDATA *pISD = (IDENTSCALEDATA *)lParam;

#if defined(_DEBUG)
	TX_ASSERT_POINTER(pISD, IDENTSCALEDATA);
	TX_ASSERT(pISD -> pcView == NULL || TIsValidString(pISD -> pcView));
	TX_ASSERT(IsValidIdent(pISD -> lIdent));
#endif // _DEBUG

LONG lUpperScale = 0, lLowerScale = 0;

	if (DBO().RetrieveIdentScaleData (pISD -> pcView, pISD -> lIdent, VisType(pISD -> iVTyp), &lUpperScale, &lLowerScale))
		return FMatchScales (DBO().GetActScale(), lUpperScale, lLowerScale) ? TRUE : FALSE;
	return TRUE;
}

// #HK980921
// DEX_SETHAVETOINITOPFS
LRESULT ExtDirisWindow::OnMustInitOPFs (HPROJECT, LPARAM lParam)
{
BOOL fMustInit = m_fMustInitOPFs;

	m_fMustInitOPFs = lParam ? true : false;
	return fMustInit;
}

// DEX_QUERYMUSTINITOPFS
LRESULT ExtDirisWindow::OnGetMustInitOPFs(HPROJECT, LPARAM)
{
	return m_fMustInitOPFs ? TRUE : FALSE;
}

// DEX_QUERYTRIASVERSIONLONG
LRESULT ExtDirisWindow::OnGetTRiASVersionLong (HPROJECT hPr, LPARAM lParam)
{
	return MAKELONG(TRIASVERSION_BUILD, MAKEWORD(TRIASVERSION_RELEASE, TRIASVERSION_VERSION));
}

///////////////////////////////////////////////////////////////////////////////
// DEX_LOADEXTENSION2: Erweiterung mit Optionen laden 
LRESULT ExtDirisWindow::OnLoadExtension2 (HPROJECT hPr, LPARAM lParam)
{
LOADEXTENSION2 *pLE = (LOADEXTENSION2 *)lParam;

	TX_ASSERT_POINTER(pLE, LOADEXTENSION2);
	TX_ASSERT(sizeof(LOADEXTENSION2) == pLE -> dwSize);
	TX_ASSERT(NULL == pLE -> m_pDesc || TIsValidString(pLE -> m_pDesc));
	TX_ASSERT(TIsValidString(pLE -> m_pName));

	return (LRESULT)(void *)LoadExtension (
				pLE -> m_pDesc, pLE -> m_pName, 
				pLE -> m_iMode, (EXTENSIONFLAG)pLE -> m_fGlobal,
				NULL, pLE -> m_pIUnk
			);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_UNLOADEXTENSION2: Erweiterung mit Optionen entladen 
LRESULT ExtDirisWindow::OnUnLoadExtension2 (HPROJECT hPr, LPARAM lParam)
{
LOADEXTENSION2 *pLE = (LOADEXTENSION2 *)lParam;
bool iResult = false;

	TX_ASSERT_POINTER(pLE, LOADEXTENSION2);
	TX_ASSERT(sizeof(LOADEXTENSION2) == pLE -> dwSize);
	TX_ASSERT(NULL == pLE -> m_pDesc || TIsValidString(pLE -> m_pDesc));
	TX_ASSERT(TIsValidString(pLE -> m_pName));

	if (pLE -> m_iMode & LEFullLoad)	// hier FullUnload
		iResult = UnLoadExtension (pLE -> m_pName, true);
	else {		// nur entladen
		if (pLE -> m_pDesc == NULL) {
		char *pExtName = m_pEL -> RetrieveExtName (pLE -> m_pName);

			iResult = ReUnLoadExtension (pExtName, pLE -> m_pName);
			DELETE_OBJ (pExtName);
		} else
			iResult = ReUnLoadExtension (pLE -> m_pDesc, pLE -> m_pName);
	}
	return (LRESULT)iResult;
}
