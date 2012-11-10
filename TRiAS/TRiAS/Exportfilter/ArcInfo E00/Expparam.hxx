/*
File: EXPPARAM.HXX
Eingabe der erforderlichen Export-Parameter.

erarbeitet : J. Benkenstein                 Begonnen am 21. August 1994
*/

#ifndef _EXPPARAM_HXX
#define _EXPPARAM_HXX

class ExportParamDialog : public DialogWindow 
{
private:
//  Attribute
    NumEdit _MasstabEdit;
    PushButton _CoverNames, _MerkmalNames;
    CheckBox _CreateLables, _Insel;
    RadioButton _ManyCoverages, _FourCoverages;
	RadioButton _ComprNone, _ComprPartial, _ComprFull;
    FixedText _MasstabText;
	CHelpText _Description;
	ErrCode _OpFlag;

protected:
//  Event-Handler-Funktionen
	void EXPORTFLT EditFocusChg (EditFocusChgEvt e);
    void EXPORTFLT ButtonClick (ControlEvt CE);
    Bool EXPORTFLT QueryClose (Event);

    void OutputWarnung (uint uiResId);
	// void SetOkButton (void);

public:
//  Konstruktor/Destruktor
    ExportParamDialog (pWindow pParent, BOOL bEnable);
    ~ ExportParamDialog (void) {}    
    
    ErrCode OpFlag (void) { return _OpFlag; }
};

#endif  //  _EXPPARAM_HXX
