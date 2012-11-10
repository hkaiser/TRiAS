// SpinControl = UpDown + Edit
// File: UPDNEDIT.H

#if !defined(_UPDNEDIT_H)
#define _UPDNEDIT_H

#include <NumEditX.hxx>

class CSpinEdit : public NumEditX 
{
protected:
	Range m_R;	// Grenzwerte für die Eingabe

public:
// Konstruktoren
		CSpinEdit (pDialogWindow pDlg, ResID uiRes, Range r)
			: NumEditX (pDlg, uiRes, 10), m_R(r)
		{}

// sonstige Member
	Range GetRange (void) { return m_R; }
	Range SetRange (Range R)
		{
		Range oldR = m_R;
			
			m_R = R;
			return oldR;
		}
	int PostValidate (int lValue)
		{
			if (lValue < m_R.Min()) return m_R.Min();
			if (lValue > m_R.Max()) return m_R.Max();
			return lValue;
		}
	bool isModified (void) { return GetEditControl() -> isModified(); }
};

class CSpinControl 
{
private:
	CSpinEdit m_sleSpinCtrlEdit;
	CSpinButtonCtrl m_udSpinButton;

public:
		CSpinControl (pDialogWindow pDlg, UINT uiEdit, UINT uiUpDn, Range r)
			: m_sleSpinCtrlEdit(pDlg, uiEdit, r), m_udSpinButton(pDlg, uiUpDn)
		{}

	bool FInit (void)
		{ 
			if (m_sleSpinCtrlEdit.FInit() && m_udSpinButton.FInit()) {
			Range r = m_sleSpinCtrlEdit.GetRange();

				m_udSpinButton.SetRange(r.Min(), r.Max()); 
				return true;
			}
			return false;
		}

// Memberfunktionen
	int SetValue (int newVal)
		{
			m_sleSpinCtrlEdit.SetValue (newVal);
			return m_udSpinButton.SetPos (newVal);
		}
	int GetValue (void) { return m_udSpinButton.GetPos(); }

// Wert aus Spin -> Edit
	void CopyToEdit (void) 
		{ m_sleSpinCtrlEdit.SetValue (m_udSpinButton.GetPos()); }

// Wert aus Edit -> Spin
	void CopyToSpin (void) 
		{ m_udSpinButton.SetPos (m_sleSpinCtrlEdit.GetValue()); }
	Range SetRange (Range R) 
		{ 
		DWORD dwOldRange = m_udSpinButton.GetRange();

			m_udSpinButton.SetRange (R.Min(), R.Max());
			return Range (HIWORD(dwOldRange), LOWORD(dwOldRange));
		}

// überprüfen, ob Edit verändert wurde
	bool isModified (void) { return m_sleSpinCtrlEdit.isModified(); }

// SpinButton verschwinden lassen/anzeigen
	void HideSpin (void) { m_udSpinButton.Hide(); }
	void ShowSpin (void) { m_udSpinButton.Show(); }

// SpinControl aktivieren/Deaktivieren
	void Disable (void) 
		{ m_sleSpinCtrlEdit.Disable(); m_udSpinButton.Disable(); }
	void Enable (void) 
		{ m_sleSpinCtrlEdit.Enable(); m_udSpinButton.Enable(); }
};

#endif // _UPDNEDIT_H
