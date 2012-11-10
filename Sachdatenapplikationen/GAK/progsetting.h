// Allgemeine Einstellungen des Programmmes

UINT GetEntsorgerPage()
{
	// default
	UINT retval = 0;

	CWinApp* pApp = AfxGetApp();
	if (NULL == pApp)
		return retval;

	return pApp->GetProfileInt("Config", "EntsorgerPageType", retval);
}