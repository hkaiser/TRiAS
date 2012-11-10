///////////////////////////////////////////////////////////////////////////
// @doc 
// @module DrawingStatusWrapper.h | Definition of the <c CDrawingStatus> class

#if !defined(_DRAWINGSTATUSWRAPPER_H__DC193483_E585_11D1_8612_00600875138A__INCLUDED_)
#define _DRAWINGSTATUSWRAPPER_H__DC193483_E585_11D1_8612_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <DToolbar.h>
#include "Strings.h"

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(StatusProgress);		// WStatusProgress

/////////////////////////////////////////////////////////////////////////////
// CDrawingStatus
class CDrawingStatus
{
private:
	WStatusProgress m_Status;

public:
	CDrawingStatus(long lCount, bool fEnable)
	{
		if (!fEnable || lCount <= 1)
			return;

	// jetzt wirklich was machen
		m_Status.CreateInstance(__uuidof(StatusProgress));	// Fehler ignorieren
		if (lCount > 0 && m_Status.IsValid()) {
		char cbView[MAXVIEWNAMESIZE+1];

			if (DEX_GetActiveSight(cbView)) {
			ResString resView (IDS_VIEW, 32);
			CComBSTR bstr (resView);
			VARIANT_BOOL fSuccess = VARIANT_FALSE;

				bstr += cbView;
				bstr += g_cbSpace;
				m_Status -> InitializeProgressControl(bstr, 0, lCount, VARIANT_TRUE, &fSuccess);
				_ASSERTE(fSuccess);
			}
		}
	}
	~CDrawingStatus()
	{
	// StatusAnzeige rücksetzen
		if (m_Status.IsValid()) {
			m_Status -> UninitializeProgressControl();
			m_Status.Assign(NULL);
		}
	}
	void StepIt()
	{
	// Status weitersetzen
		if (m_Status.IsValid()) {
//		string str;
//		char cbBuffer[64];
//
//			if (rId.GetKurzText (cbBuffer, sizeof(cbBuffer)))
//				str = cbBuffer;
//			if (pP -> GetObjType (cbBuffer, sizeof(cbBuffer)))
//				str += cbBuffer;
//			
//			m_Status -> put_ProgressText (CComBSTR(str.c_str()));
			m_Status -> StepProgress();
		}
	}
};

#endif // !defined(_DRAWINGSTATUSWRAPPER_H__DC193483_E585_11D1_8612_00600875138A__INCLUDED_)
