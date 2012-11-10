// Dialogfenster um Selektion zu korrigieren ----------------------------------
// File: SELECTN.HXX

#if !defined(_SELECTN_HXX)
#define _SELECTN_HXX

class CSelectRectDlg : public DialogWindow {
private:
	DoubleNumEdit m_dneObenHochWert;
	DoubleNumEdit m_dneObenRechtsWert;
	DoubleNumEdit m_dneUntenHochWert;
	DoubleNumEdit m_dneUntenRechtsWert;

	CoordTrans *m_pCT;
	Rectangle m_RC;
	DragRectangleObject &m_rDRO;

	bool m_fRemoveOnEnd;

protected:
	void ButtonClick (ControlEvt);
	void EditFocusChg (EditFocusChgEvt e);

	bool ReadResults (Rectangle &rRC);
	void CorrectPosition (void);
	bool GetValue (DoubleNumEdit &dblNED, double &dbl, DoubleNumEdit &, double &);

public:
		CSelectRectDlg (pWindow pW, CoordTrans *pCT, DragRectangleObject &rDRO);
		~CSelectRectDlg (void);

	void RemoveOnEnd (bool fFlag) { m_fRemoveOnEnd = fFlag; }

friend	Point GetPt (Rectangle &rRC) { return Point (rRC.Left()-1, rRC.Top()-1); }
friend	Dimension GetDim (Rectangle &rRC) { return Dimension (rRC.Right()-rRC.Left(), rRC.Bottom()-rRC.Top()); }
};

#endif // _SELECTN_HXX

