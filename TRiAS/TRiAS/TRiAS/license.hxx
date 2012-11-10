// LizenzDialog ---------------------------------------------------------------
// File: LICENSE.HXX

#if !defined(_LICENSE_HXX)
#define _LICENSE_HXX

class CLicenseDlg : public DialogWindow {
private:
	SingleLineEdit m_sleLicenseKey;
	FixedText m_ftLicenseText;
	PushButton m_pbOK;

protected:
	void ButtonClick (ControlEvt);
	void EditChange (ControlEvt);

public:
		CLicenseDlg (pWindow pW, string &rStr);
		~CLicenseDlg (void);

	BSTR GetKey (void);
};

#endif // _LICENSE_HXX
