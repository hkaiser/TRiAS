// RegProg.h: Dialog für RegistrierungsFortschrittsanzeige

#if !defined(_REGPROG_H)
#define _REGPROG_H

#pragma warning (disable: 4355)

string FakeTRiASName (LPCSTR pcTempl, ...);

class CRegistryProgressEnd : 
	public DialogWindow 
{
private:
	FixedText m_ftText;

protected:
	void Activate (Event) { GetParent() -> Hide(); }
	void ButtonClick (ControlEvt) { EndDlg(); }

public:
		CRegistryProgressEnd (Window *pW, UINT uiID)
			: DialogWindow (pW, ResID (IDD_REGISTRYPROGRESSEND)),
			  m_ftText (this, IDC_REGISTERENDTEXT)
			{
			ResString resStr (uiID, 128);
			char cbBuffer[_MAX_PATH];

				m_ftText.SetText (FakeTRiASName (resStr.Addr(), g_cbTRiAS).c_str());

				GetCaption (cbBuffer, sizeof(cbBuffer));
				SetCaption (FakeTRiASName (cbBuffer, g_cbTRiAS).c_str());

				Update();
			}
		~CRegistryProgressEnd (void) {}
};

class CRegistryProgress : 
	public DialogWindow 
{
private:
	CProgressCtrl m_Progress;
	UINT m_uiMsg;
	FixedText m_ftFile;
	FixedText m_ftInfo;
	CAnimateCtrl m_aviAction;
	bool m_fFullReg;
	bool m_fAVIStarted;

public:
		CRegistryProgress (LONG lMax, UINT uiMsg, bool fFullReg)
			: DialogWindow (NULL, ResID (IDD_REGISTRYPROGRESS_AVI), false),
			  m_Progress (this, IDC_PROGRESS), m_uiMsg(uiMsg), 
			  m_ftFile (this, IDC_ACTFILENAME),
			  m_ftInfo (this, IDC_REGISTERTEXT),
			  m_aviAction (this, IDC_ANIMATE_GLOBE),
			  m_fFullReg(fFullReg)
			{
#if defined(ListView_GetExtendedListViewStyle)
				m_Progress.SetStyle (PBS_SMOOTH);
#endif
				m_Progress.SetRange(0, lMax);
				m_Progress.SetStep(1);
				m_Progress.SetPos(0);

			char cbBuffer[_MAX_PATH];

				m_ftInfo.GetText (cbBuffer, sizeof(cbBuffer));
				m_ftInfo.SetText (FakeTRiASName (cbBuffer, g_cbTRiAS).c_str());

				GetCaption (cbBuffer, sizeof(cbBuffer));
				SetCaption (FakeTRiASName (cbBuffer, g_cbTRiAS).c_str());

				m_fAVIStarted = m_aviAction.Open (IDR_AVI_REGISTER) ? true : false;
				Update();
			}
		~CRegistryProgress (void) 
			{
				if (m_fAVIStarted) {
					m_aviAction.Stop();
					m_aviAction.Open ((LPCSTR)NULL);
				}
				if (0 != m_uiMsg) {
				CRegistryProgressEnd Dlg (this, m_uiMsg);

					Dlg.Show (ShowState(Centre|NoQuitOnHide));
				}
			}

	LRESULT Dispatch (Event e)		// Hintergrund Transparent
	{
		if (WM_CTLCOLORSTATIC == e.Msg()) {
			if ((HWND)e.LParam() == m_aviAction.Handle()) {
				::SetBkColor ((HDC)e.WParam(), ::GetSysColor (COLOR_3DFACE));
				return (LRESULT)::GetSysColorBrush(COLOR_3DFACE);
			}
		}
		return DialogWindow::Dispatch(e);
	}

	int IncPos (void) { App::Exec(ExecWhileEvent); Update(); return m_Progress.StepIt(); }
	void SetText (LPCSTR pcText) 
	{ 
#if !defined(_DEBUG)
		if (m_fFullReg)		// in Release nur bei FullReg
#endif // !_DEBUG
			m_ftFile.SetText(pcText); 
	}
};

#pragma warning (default: 4355)

#endif // _REGPROG_H
