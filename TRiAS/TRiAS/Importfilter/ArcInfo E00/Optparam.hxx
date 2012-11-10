/*
File: OPTPARAM.HXX
Das Modul dient zur Eingabe und Verwaltung optionaler Parameter.

Erarbeitet: J.Benkenstein                       Stand vom 6.1.1994
*/

#ifndef _OPTPARAM_HXX
#define _OPTPARAM_HXX

//  Konstanten
const short MaxFileSize = 8;     // max. Größe eines Dateinamens

#ifndef NOPARAMS                                             
//  Definition aller möglichen Parameter
class Params {
public:  
	short sMCode, sIdCode;
    double XOffset, YOffset, Scaling;
    ulong ID, TextMK, UnID;
    long MaxLineNr, TextCnt, LineCnt, PointCnt,
	 	 AreaCnt, TableCnt, LineNr, NotImported, SubImported, BugCnt;
    Bool UserID, PalExist, CrUnID, ImpFlaechen, ImpLinien, ImpPunkte, ImpTexte, 
    	 ImpTabellen, AatExist, AatFields, DoublePrec, DebugOutput, bAnsiiText;
// KK000328
	Bool IsCompressed;

	Bool m_bAllCover;
    pchar pCoverName;                   		// "kurzer" Dateiname (8 Zeichen)

    Params (void);
    ~ Params (void);

    void Reset (void);							// alle Werte auf Standardwerte setzen
    Bool SetCoverName (pchar pNewCoverName);  	// neuen CoverNamen setzen
	Bool HasImported (void);					// irgendwelche Objekt imp. ?
	void ResetCounter (void);					// alle Zähler zurücksetzen
};
#endif // NOPARAMS

#ifndef NOOPTPARAM 

class ResourceFile;

class OptParams : public DialogWindow {
private:
//  Attribute
	BOOL m_bMultFiles;		// verarbeite mehrere Dateien
	Bool _OpFlag;			// Konstrukor-Flag
    Params *_pParams;
    ResourceFile *_pRF;

    NumEdit _ID;
    RealEdit _XOffset, _YOffset, _Scaling;
    CheckBox _UserID, _UnID, _ImpFlaechen, _ImpLinien, _ImpPunkte, _ImpTexte, 
			 _ImpTabellen, _AllCover;	//, _AllImport;
    CHelpText _Description;

protected:      
	void __export EditFocusChg (EditFocusChgEvt e);
    Bool __export QueryClose (Event) { _OpFlag = False; return True; }
    void __export ButtonClick (ControlEvt);
    Bool _CheckAllParams (void);    // alle Parameter prüfen

public:
//  Konstruktor/Destruktor
    OptParams (pWindow pParent, ResourceFile *pRF, BOOL bMultFiles = FALSE);
    ~ OptParams (void) {}
    
    Bool OpFlag (void) { return _OpFlag; }
};
#endif  // NOOPTPARAM

#endif  // _OPTPARAM_HXX
