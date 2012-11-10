// Basisklasse für den Progress-Indikator
// File: PROGSTAT.H
// W. Mörtl

#if !defined(_PROGSTAT_H)
#define _PROGSTAT_H

class BaseProgressStatus
{
public:
// rein virtuelle Funktionen
	virtual HRESULT InitNew (HWND hWndParent, ulong dwReserved, HWND* phWnd) = 0;
	virtual HRESULT Restart (ulong ulMinPos, ulong ulMaxPos,
							 tagPIFLAGS rgFlags) = 0;
	virtual HRESULT ChangeText (tagPIFLAGS rgWhichText, BSTR bstrNewText) = 0;
//	virtual HRESULT SetPosition (ulong ulNewPos, int* piPercent) = 0;	// wird nicht genutzt
	virtual HRESULT IncrementPosition(int* piPercent) = 0;
	virtual HRESULT IsCanceled (void) = 0;
	virtual HRESULT SetObjNr (long lONr) = 0;
};

#endif  // _PROGSTAT_H
