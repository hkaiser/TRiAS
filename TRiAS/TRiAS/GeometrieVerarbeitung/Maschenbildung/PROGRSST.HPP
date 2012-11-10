/*
Datei: PROGRSS1.HPP

Der Module realisiert eine dialoggesteuerte Fortschrittsanzeige.

Erarbeitet: J. Benkenstein				Stand vom: 26.10.1996
*/

#ifndef _PROGRSST_HPP
#define _PROGRSST_HPP

DefineSmartInterface (ProgressIndicator2);
interface IProgressIndicator2;
class CProgressIndicator
{
private:
//	Attribute
	// LPPROGRESSINDICATOR m_pIStatus;	
	WProgressIndicator2 m_wIndicator;
	
public: 
//	Konstruktor/Destruktor
	CProgressIndicator (HWND hWndParent = NULL, IProgressIndicator2 *pPI = NULL);
	
//	weitere Member
	void InitStatusDialog (ULONG MaxSize, const char *strCaption, const char *pAdjusText = NULL);
	int SetupStatus (ULONG pos);
	BOOL WasCanceled ();
	HRESULT SetObjNr (long lONr);		// #WM990413
};

#endif		// _PROGRSST_HPP
