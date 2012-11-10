/*
File: STSCRIPT.HXX
Standard-Script für die Komplex-Recherche erstellen.

erarbeitet : J. Benkenstein                 Begonnen am 20.09.1993
											Stand vom 14.11.1995
*/

#ifndef _STSCRIPT_HXX
#define _STSCRIPT_HXX

#ifndef NOSTANDSCRIPTDIALOG
class CodeBase;
class DBaseFiles;
class StandScriptDialog : public DialogWindow {
private:
//  Attribute
    Bool _OpFlag;                       // Operation-Flag

    pchar _pScript;                     // generierter Script
    CheckBox _UniqueCheck, _ExprCheck;
    SingleLineEdit _CommentLine;
    ComboBox _dBaseExprList;
    RadioButton _OutListButton, _OutClassifyButton;
    PushButton _AusfButton, _EntryExprButton, _SelFileButton;
    FixedText _FileName;

protected:
//  Event-Handler-Funktionen
    Bool QueryClose (Event E);
    void ButtonClick (ControlEvt CE);
    void ListBoxSel (ControlEvt CE);

//  Kommentar-Zeile init.
    void _SetComment (void);

//  Standard-Script erzeugen
    Bool _GenerateScript (void);

//  alten dBase-Expression lesen/speichern
    void _ReadExpression (void);
    void _SaveExpression (void);

	//  Alias-Namen in Textfeld ausgeben
    Bool _OutputAliasNames (void);

public:
//  Konstruktor/Destruktor
    StandScriptDialog (pWindow pParent);
    ~StandScriptDialog (void);

    pchar GetScript (void) { return _pScript; }
    Bool OpFlag (void) { return _OpFlag; }

    enum ScriptAction { Abbruch, Start, Modify, Error };
};
#endif  //  NOSTANDSCRIPTDIALOG

#endif  //  _STSCRIPT_HXX
