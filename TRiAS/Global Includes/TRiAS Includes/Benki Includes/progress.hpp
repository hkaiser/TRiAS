/*	FILE: PROGRESS.HPP
  
	Das Modul realisiert ein Fortschritts-Anzeige  (Resource: GaugeBox, 0x2)

	Erarbeitet: J.Benkenstein					Stand vom 02.02.1995	
*/	
    
#ifndef _PROGRESS_HPP
#define _PROGRESS_HPP
     
// #ifndef WIN32
class CProgressCtrl : public CStatic
{ 
private:
	UINT m_iStart, m_iEnd, m_iPos, m_iDrawPos;
	CRect rc;     
	double m_dFaktor;
	
protected:
	void DrawPosition (UINT iPos);
		
public:
	CProgressCtrl (void);
	~CProgressCtrl (void) {}			
			
	void SetRange (UINT iStart, UINT iEnd);
	void SetPos (UINT iNewPos);
};    
// #endif

#endif		// _PROGRESS_HPP	                 
