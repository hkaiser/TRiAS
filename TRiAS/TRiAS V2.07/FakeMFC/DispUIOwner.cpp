// DispUIOwner.cpp : Implementation of the CDispUIOwner

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <itoolbar.h>
#include <dtoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#include "Wrapper.h"		// SmartInterfaces
#include "fakemfc.hxx"

#include "DispUIOwner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Achtung: Dieses Objekt wird je einmal für jeden installierten Button erzeugt.
// Daher ist keine Unterscheidung nach Button notwendig, sondern diese ergibt sich 
// 'von selbst'.

DefineSmartInterface2(DTRiASCmdUI, IID_DTRiASCmdUI);

///////////////////////////////////////////////////////////////////////////////
// Dynamische Daten initialisieren

HRESULT CDispUIOwner::SetTargetUIOwner (DToolBarUIOwner *pIDispUI)
{
	m_TargetUIOwner = pIDispUI;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// *** ITRiASUIOwner specific functions ***

HRESULT CDispUIOwner::OnUpdateUI (ITRiASBar *pIBar, ITRiASCmdUI *pICmdUI)
{
	if (NULL == pIBar) return E_POINTER;

	try {
	WDTRiASCmdUI DispUI (pICmdUI);		// throws hr

		return m_TargetUIOwner -> UpdateUI(DispUI);
	
	} catch (...) {
		return S_FALSE;
	}
}

HRESULT CDispUIOwner::OnSelect (ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (NULL == pIBar || NULL == pBuffer || 0 == ulLen) 
		return E_POINTER;

BSTR bstrDesc = NULL;
HRESULT hr = m_TargetUIOwner -> GetDescription (uiID, &bstrDesc);

	if (SUCCEEDED(hr)) {
		USES_CONVERSION;

	string strDesc (OLE2A(bstrDesc));

		if (NPOS == strDesc.find('\n'))
			strDesc += "\n" + strDesc;

		strcpy (pBuffer, strDesc.c_str());
		SysFreeString (bstrDesc);
		if (pulWritten)	
			*pulWritten = strlen (pBuffer);
		return NOERROR;
	}

return hr;
}

HRESULT CDispUIOwner::OnCommand (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (NULL == pIBar) return E_POINTER;

	return m_TargetUIOwner -> FireCommand (uiID, nCode);
}

