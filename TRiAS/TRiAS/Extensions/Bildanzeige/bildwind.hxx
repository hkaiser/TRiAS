// Fenster, welches zu Anzeige einer BildBitmap dient
// File: BILDWIND.HXX

#if !defined(_BILDWIND_HXX)
#define _BILDWIND_HXX

#if !defined(NOBILDWINDOW)
// Fenster, welches nur eine Bitmap enthält -----------------------------------
class BildWindow : public ExtChildAppWindow {
private:
	BildObjekt *_pBO;	// auszugebende BildBitmap
	Brush localBrush;	// HintergrundBrush
	WndVertScrollBar *pVertSB;	// vertikaler ScroolBalken
	WndHorzScrollBar *pHorzSB;	// horizontaler ScrollBalken
	Dimension _maxSize;	// maximale Fenstergröße

protected:
// Events
	void ReSize (ReSizeEvt);
	void Expose (ExposeEvt);
	void VertScroll (ScrollEvt);
	void HorizScroll (ScrollEvt);
	Bool QueryClose (Event);

// eigener EventHandler
	void MinMaxQuery (MinMaxEvent);

public:
// Konstruktor
		BildWindow (pWindow pParent, char *pCaption,
			    Point Org, char *pImgFile);
// Member
	Bool OK (void) { return _pBO -> OK(); }
	void SetScrollRanges (void);
	Rectangle RealCanvasRect (void);

// Destruktor
		~BildWindow (void);
};

#define BOUND(x,min,max) ((x)<(min)?(min):((x)>(max)?(max):(x)))

#endif // NOBILDWINDOW

#endif // _BILDWIND_HXX
