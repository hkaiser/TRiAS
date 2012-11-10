// Modifikation des Identifikators --------------------------------------------
// File: NEWID.HXX

#if !defined(_NEWID_HXX)
#define _NEWID_HXX

class CHelpText;
class CNewIdentDlg : public DialogWindow {
private:
        PushButton m_pbOK;
        PushButton m_pbCancel;
#if defined(WIN16)
        PushButton m_pbHelp;
#endif // WIN16
        CheckBox m_bxOldId;
        ComboBox m_cbOldId;
        ComboBox m_cbNewId;
        class CHelpText *m_pHelpText;
        
        short m_iIdBase;
        char *m_pOutBuff;
        
        long m_lOldIdent;
        long m_lNewIdent;
        long m_lLastIdent;      // zuletzt eingestellter OldId
                
        long GetIdent (ComboBox *pCB, BOOL fEdit = FALSE);
        void AdjustOK (BOOL fIndex = TRUE);

protected:
        void ButtonClick (ControlEvt e);
        void ListBoxSel (ControlEvt e);
        void EditFocusChg (EditFocusChgEvt e);  // für ComboBoxen
        void EditChange (ControlEvt e);
        
        BOOL FillOldIdents (long lOldIdent);
friend  BOOL FillNewIdents (ComboBox &, CHelpText *, short, char *);

public:
                CNewIdentDlg (pWindow pW);
                ~CNewIdentDlg (void);
                
        BOOL FInit (long lOldIdent);
        
static CNewIdentDlg *CreateInstance (pWindow pW, long lOldIdent);

        long GetNewIdent (void) { return m_lNewIdent; }
        long GetOldIdent (void) { return m_lOldIdent; }
};


#endif // _NEWID_HXX

