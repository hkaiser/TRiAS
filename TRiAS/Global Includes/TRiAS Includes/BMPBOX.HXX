// Rahmen, in dem eine Bitmap gezeichnet werden soll --------------------------
// File: BMPBOX.HXX

#if !defined(_BMPBOX_HXX)
#define _BMPBOX_HXX

class BitmapBox : public ControlWindow {
private:
	Bitmap *m_pBM;
	ResID m_uiLogo;
	
protected:
	void Expose (ExposeEvt e);
	
public:
		BitmapBox (pDialogWindow pDW, ResID uiID, ResID uiLogo);
		~BitmapBox (void);
		
	BOOL Init (void);
};


#endif // _BMPBOX_HXX
