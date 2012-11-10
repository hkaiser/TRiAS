/*
File: OPTPRDLG.HPP
Das Module realisiert die Eingabe optionaler Parameter-Eingabe im Dialog.

Erarbeitet: J.Benkenstein                       Stand vom 01.09.1994
*/

#ifndef _OPTPRDLG_HPP
#define _OPTPRDLG_HPP

class ResourceFile;
class Params;
class OptParamsDlg : public DialogWindow 
{
private:
//  Attribute
	Bool _OpFlag;			// Konstrukor-Flag
    Params *_pParams;
    ResourceFile *_pRF;

    RealEdit _XOffset, _YOffset;
    CheckBox _CloseLines, m_ImpTextHoehe, m_ImpTextDrehWi, m_ImpSymDrehWi,
			 m_ImpComment, m_ImpBlocks, m_ImpSystemBlocks;
	MultiLineEdit m_edEbenen;
    CHelpText _Description;

// KK991007
	CheckBox m_NoShow;
	FixedText _OffsetXText,_OffsetYText;
	PushButton OKButton;

protected:      
	void __export EditFocusChg (EditFocusChgEvt e);
    Bool __export QueryClose (Event) { _OpFlag = False; return True; }
    void __export ButtonClick (ControlEvt);
    Bool _CheckAllParams (void);    // alle Parameter prüfen
public:
//  Konstruktor/Destruktor
    OptParamsDlg (pWindow pParent, ResourceFile *pRF, Params *pOP);
    ~ OptParamsDlg (void) {}
    
    Bool OpFlag (void) { return _OpFlag; }
};

#endif  // _OPTPRDLG_HPP

