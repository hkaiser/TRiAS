/*
Datei: PROGRSS1.HPP

Der Module realisiert eine dialoggesteuerte Fortschrittsanzeige.

Erarbeitet: J. Benkenstein				Stand vom: 26.10.1996
Ergänzt:	W. Mörtl							   13.04.1999
*/

#ifndef _PROGRSS1_HPP
#define _PROGRSS1_HPP

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

#endif		// _PROGRSS1_HPP
