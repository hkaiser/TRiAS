// LizenzDialog ---------------------------------------------------------------
// File: LICENSE.CXX

#include "triaspre.hxx"

#include "triasres.h"
#include "strings.h"

#if defined(WIN16)
#include <dispatch.h>	// BSTR etc.
#endif 

#include "license.hxx"

#pragma warning (disable:4355)

CLicenseDlg :: CLicenseDlg (pWindow pW, string &strName)
	     : DialogWindow (pW, IDD_LICENSE),
	       m_pbOK (this, IDOK),
	       m_ftLicenseText (this, IDC_LICENSETEXT),
	       m_sleLicenseKey (this, IDC_LICENSEKEY)
{
char cbBuffer[_MAX_PATH];

	m_ftLicenseText.GetText (cbBuffer, sizeof(cbBuffer));
	m_ftLicenseText.SetText (FakeTRiASName(cbBuffer, g_cbTRiAS, strName.c_str()).c_str());

	m_sleLicenseKey.SetText ("");
	m_sleLicenseKey.SetTextLimit(63);

	m_pbOK.Disable();
}

#pragma warning (default:4355)

CLicenseDlg :: ~CLicenseDlg (void)
{
	// nothing to do
}

void CLicenseDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);
		break;

	case IDCANCEL:
		EndDlg (0);
		break;
	}
}

void CLicenseDlg :: EditChange (ControlEvt)
{
	if (m_ftLicenseText.GetTextLen() > 0)
		m_pbOK.Enable();
	else
		m_pbOK.Disable();
}

BSTR CLicenseDlg :: GetKey (void)
{
char cbBuffer[64];

	m_sleLicenseKey.GetText (cbBuffer, 64);

return SysAllocString (WideString(cbBuffer));
}

