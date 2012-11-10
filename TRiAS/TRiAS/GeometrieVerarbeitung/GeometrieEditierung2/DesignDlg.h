// Deklarationen: PropertySheet für Bildung von Hilfslinien
// File: DesignDlg.h
// W. Mörtl
      

      
#ifndef _DESIGNDLG_H
#define _DESIGNDLG_H


#include "PropExt.h"		// CEditObjectSheet


///////////////////////////////////////////////////////////////////////////////////////////////
class CDesignDlg : public CEditObjectSheet
{
private:
	PushButton m_OK/*, m_Cancel*/;
	Point m_FixPt;

protected:
	void WindowInit (Event e);	
	void ButtonClick (ControlEvt e);

public:
	// Konstruktor/Destruktor
		CDesignDlg (Point FixPt);
		~CDesignDlg (void);

	// Zugriff auf Member
	void SetOKButton (bool bEnable = true) { bEnable ? m_OK.Enable() : m_OK.Disable(); }

};

#endif  // _DESIGNDLG_H
