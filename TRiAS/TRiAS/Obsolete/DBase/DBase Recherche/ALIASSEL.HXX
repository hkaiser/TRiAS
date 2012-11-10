/*
File: ALIASSEL.HXX

Das Modul dient zu Auswahl der projektspezifischen Alias-Namen.

Erarbeitet: J. Benkenstein		    Stand vom: 20.01.1994
*/

#ifndef _ALIASSEL_HXX
#define _ALIASSEL_HXX

class CodeBase;
class DBaseFiles;
class SelectAliasNames : public DialogWindow {
private:
    CodeBase *_pCodeBase;
    DBaseFiles *_pDataTree;
    MultiSelListBox _List;
    PushButton _OK;
    Bool _OpFlag;

protected:
    Bool QueryClose (Event) { EndDlg (False); return True; }
    void ButtonClick (ControlEvt);
    void ListBoxSel (ControlEvt );

public:
    SelectAliasNames (pWindow pParent, ResourceFile *pRF,
		      CodeBase *pCodeBase, DBaseFiles *pData);
    ~ SelectAliasNames (void) {}

    Bool OpFlag (void) { return _OpFlag; }
};

#endif	// _ALIASSEL_HXX
