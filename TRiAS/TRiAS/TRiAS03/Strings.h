///////////////////////////////////////////////////////////////////////////
// @doc
// @module Strings.h | StringKonstanten 

#if !defined(_STRINGS_H__3DD94694_796B_11D1_9761_00A024D6F582__INCLUDED_)
#define _STRINGS_H__3DD94694_796B_11D1_9761_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// StringKonstanten
extern const TCHAR g_cbParameters[];		// TEXT("Parameters");
extern const TCHAR g_cbNumExtensions32[];	// TEXT("NumExtensions32");
extern const TCHAR g_cbExtensions32[];		// TEXT("Extensions32");
extern const TCHAR g_cbINI[];				// TEXT("ini");

extern const TCHAR g_cbExtensions[];		// TEXT("Software\\TRiAS\\InterTRiAS\\Extensions");
extern const TCHAR g_cbConfig[];			// TEXT("Config");
extern const TCHAR g_cbClsId[];				// TEXT("CLSID");
extern const TCHAR g_cbNotPrimary[];		// TEXT("NotPrimary");
extern const TCHAR g_cbInprocServer[];		// TEXT("InprocServer32");

extern const TCHAR g_cbNil[];				// TEXT("");
extern const TCHAR g_cbDel[];				// TEXT("\\");

extern const TCHAR g_cbPattern[];			// TEXT("%1=%2;");

extern const TCHAR g_cbRegConfig[];		// TEXT("Software\\TRiAS\\InterTRiAS\\Config");
extern const TCHAR g_cbImportFormat[];		// TEXT("ImportFormat");
extern const TCHAR g_cbDescription[];		// TEXT("Description");
extern const TCHAR g_cbFileExt[];			// TEXT("FileExtension");
extern const TCHAR g_cbConfigPage[];		// TEXT("ConfigPage");

extern const TCHAR g_cbWarnBeforeDelObj[];    // TEXT("WarnBeforeDelObj");

extern const TCHAR g_cbTransaktion[];		// TEXT("Transaktion %d");

extern const TCHAR g_cbFeatureMap[];		// TEXT("FeatureMap");

///////////////////////////////////////////////////////////////////////////////
// Monikersupport
extern const TCHAR g_cbMkPropSeq[];				// TEXT("MkPropSeq");
extern const TCHAR g_cbMkPropAct[];				// TEXT("MkPropAct");

/////////////////////////////////////////////////////////////////////////////
// Feststehende PropertyBag-Keys für PropertyActions
extern const OLECHAR g_cbPAPrefix[];		// L"PropActData";		// Prefix für PropActDaten
extern const OLECHAR g_cbPAName[];			// L"Name";				// Name der propertyAction
extern const OLECHAR g_cbPANoShow[];		// L"NoShow";			// Dialog _nicht_ anzeigen

extern const OLECHAR g_cbProgID[];			// L"ProgID";			// ProgID für ImportData
extern const OLECHAR g_cbFlags[];			// L"Flags";			// Flags für ImportData
extern const OLECHAR g_cbFiles[];			// L"Files";			// Files für ImportData
extern const OLECHAR g_cbShowErrors[];		// L"ShowErrors";		// Importfehler anzeigen

extern const OLECHAR g_cbObjProp[];			// L"ObjProp";			// aus Objekteigenschaft ... generieren
extern const OLECHAR g_cbDirect[];			// L"Direct";			// aus gegebenem Text erzeugen
extern const OLECHAR g_cbDependend[];		// L"Dependend";		// abhängige Texte erzeugen
extern const OLECHAR g_cbDynamic[];			// L"Dynamic";			// dynamische Texte erzeugen (nur bei ObjProp und Dependend)
extern const OLECHAR g_cbDelete[];			// L"Delete";			// evtl. existierende Texte vorher löschen (nur bei Dependend)
extern const OLECHAR g_cbDoNotMove[];		// L"DoNotMove";		// an Punktobjekte nicht verschieben
extern const OLECHAR g_cbRotate[];			// L"Rotate";			// an Linienobjekten drehen (nur bei Dependend)
extern const OLECHAR g_cbDeleteTarget[];	// L"DeleteTarget";		// Bezugsobjekte nach Texterzeugen löschen (nur bei !Depenend)
extern const OLECHAR g_cbExistantOnly[];	// L"ExistantOnly";		// nur für existierende Objekteigenschaften

extern const OLECHAR g_cbDesc[];			// L"Desc";				// Beschreibungsinfo 
extern const OLECHAR g_cbHelpDesc[];		// L"HelpDesc";			// Lange Beschreibungsinfo 
extern const OLECHAR g_cbDataSource[];		// L"DataSource";		// Zieldatenquelle
extern const OLECHAR g_cbModifyTo[];		// L"ModifyTo";			// Objektklasse modifizieren
extern const OLECHAR g_cbAddToClass[];		// L"AddToClass";		// als Objektklasse speichern

extern const OLECHAR g_cbCheckMode[];		// L"CheckMode";		// Idents selektieren zuschaltbar
extern const OLECHAR g_cbCheckModeChecked[];		// L"Checked";	// Idents selektieren zugeschaltet (bei CheckMode=1)

extern const OLECHAR g_cbOperation[];		// L"Operation";		// Operationen von PropOp
extern const OLECHAR g_cbA_Or_B[];			// L"A_Or_B";			// Vereinigungsmenge 
extern const OLECHAR g_cbA_And_B[];			// L"A_And_B";			// Schnittmenge
extern const OLECHAR g_cbA_And_NotB[];		// L"A_And_NotB";		// Komplementärmenge zu A aus B
extern const OLECHAR g_cbNotA_And_B[];		// L"NotA_And_B";		// Komplementärmenge zu B aus A
extern const OLECHAR g_cbA_Xor_B[];			// L"A_Xor_B";			// Exklusives Oder

extern const OLECHAR g_cbDeleteSrcObjs[];	// L"DeleteSrcObjs";	// Ausgangsobjekte löschen
extern const OLECHAR g_cbMarkSrcObjs[];		// L"MarkSrcObjs";		// Ausgangsobjekte markieren
extern const OLECHAR g_cbCopySrcObjs[];		// L"CopySrcObjs";		// alleinstehende Ausgangsobjekte kopieren

extern const OLECHAR g_cbSelectObjs[];		// L"SelectObjs";		// Objekte aus ORWnds benutzen
extern const OLECHAR g_cbActivated[];		// L"Activated";		// ... alle aktivierten (blinkenden)
extern const OLECHAR g_cbSelected[];		// L"Selected";			// ... alle selektierten
extern const OLECHAR g_cbAll[];				// L"All";				// ... alle Objekte
extern const OLECHAR g_cbCloseWhenReady[];	// L"CloseWhenReady";		// ORWnds nach erfolgreichem Abarbeiten schließen
extern const OLECHAR g_cbShowConfigAlways[];	// L"ShowConfigAlways";	// Config-Fenster immer anzeigen (auch bei einem ORWnd)
extern const OLECHAR g_cbDisableCloseWhenReady[];	// L"DisableCloseWhenReady";	// passivieren von 'ORWnds nach erfolgreichem Abarbeiten schließen'

extern const OLECHAR g_cbInitData[];		// L"InitData";			// Daten für externe GeoComp's

extern const OLECHAR g_cbLimitORWndCount[];	// L"LimitORWndCount";	// LimitPackets
extern const OLECHAR g_cbLimitObjCount[];	// L"LimitObjCount";
extern const OLECHAR g_cbLimitOperation[];	// L"LimitOperation";
extern const OLECHAR g_cbLimitGE[];			// L"LimitGE";	// >=
extern const OLECHAR g_cbLimitGT[];			// L"LimitGT";	// >
extern const OLECHAR g_cbLimitEQ[];			// L"LimitEQ";	// ==
extern const OLECHAR g_cbLimitLT[];			// L"LimitLT";	// <
extern const OLECHAR g_cbLimitLE[];			// L"LimitLE";	// <

// Bezeichner der PropActScripte
extern const OLECHAR g_cbObjekteDoppeln[];	// L"ObjekteDoppeln";
extern const OLECHAR g_cbObjekteVereinigen[];	// L"ObjekteVereinigen";

#if defined(_USE_XML_GEOCOMPONENTS)

///////////////////////////////////////////////////////////////////////////////
// XmlPropertySequence
extern const OLECHAR g_cbGeoComponentSequence[];	// L"GeoComponentSequence";
extern const OLECHAR g_cbGeoComponent[];	// L"GeoComponent";
extern const OLECHAR g_cbName[];			// L"Name";
extern const OLECHAR g_cbSaveAs[];			// L"SaveAs";
extern const OLECHAR g_cbLoad[];			// L"Load";
extern const OLECHAR g_cbType[];			// L"Type";
extern const OLECHAR g_cbLoadInfo[];		// L"LoadInfo";
extern const OLECHAR g_cbInitInfo[];		// L"InitInfo";
extern const OLECHAR g_cbExpandName[];		// L"ExpandName";
extern const OLECHAR g_cbRegistry[];		// L"Registry";
extern const OLECHAR g_cbDirectL[];			// L"Direct";
extern const OLECHAR g_cbAction[];			// L"Action";
extern const OLECHAR g_cbProperty[];		// L"Property";
extern const OLECHAR g_cbSequence[];		// L"Sequence";
extern const OLECHAR g_cbLevel[];			// L"Level";
extern const OLECHAR g_cbRegistryRoot[];	// L"RegistryRoot";
extern const OLECHAR g_cbHKCR[];			// L"HKCR";
extern const OLECHAR g_cbHKCU[];			// L"HKCU";
extern const OLECHAR g_cbHKLM[];			// L"HKLM";
extern const OLECHAR g_cbRegistryPath[];	// L"RegistryPath";
extern const OLECHAR g_cbErrorInfo[];		// L"ErrorInfo";
extern const OLECHAR g_cbCaption[];			// L"Caption";
extern const OLECHAR g_cbPrompt[];			// L"Prompt";
extern const OLECHAR g_cbInitPattern[];		// L";%1=%2";
extern const OLECHAR g_cbVBInitPattern[];	// L",%1(%2)";
extern const OLECHAR g_cbDescriptionL[];	// L"Description";
extern const OLECHAR g_cbMayFail[];			// L"MayFail";			// darf fehlschlagen
extern const OLECHAR g_cbMonikerData[];		// L"MonikerData";
extern const OLECHAR g_cbVersion[];			// L"Version";
extern const OLECHAR g_cbHeaderTitle[];		// L"HeaderTitle";
extern const OLECHAR g_cbHeaderSubTitle[];	// L"HeaderSubTitle";
extern const OLECHAR g_cbIsWizard97[];		// L"IsWizard97";

extern const char g_cbTRiAS[];				// "TRiAS®";

#endif // defined(_USE_XML_GEOCOMPONENTS)

#endif // !defined(_STRINGS_H__3DD94694_796B_11D1_9761_00A024D6F582__INCLUDED_)
