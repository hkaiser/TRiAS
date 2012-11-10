// Rahmen, in dem eine Bitmap gezeichnet werden soll --------------------------
// File: CBMPBOX.HXX

#if !defined(_CBMPBOX_HXX)
#define _CBMPBOX_HXX

class CBitmapBox : public ControlWindow {
private:
	Bitmap *m_pBM;
	ResID m_uiLogo;
	
protected:
	void Expose (ExposeEvt e);
	
public:
		CBitmapBox (pDialogWindow pDW, ResID uiID, ResID uiLogo);
		~CBitmapBox (void);
		
	BOOL FInit (ResID uiLogo);
	BOOL FInit (void);
};


#endif // _CBMPBOX_HXX
