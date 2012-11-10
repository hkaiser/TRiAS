// StringKonstanten
// File: Strings.cpp

#include "trias03p.hxx"
#include "strings.h"

/////////////////////////////////////////////////////////////////////////////
// StringKonstanten
const TCHAR g_cbParameters[] = TEXT("Parameters");
const TCHAR g_cbNumExtensions32[] = TEXT("NumExtensions32");
const TCHAR g_cbExtensions32[] = TEXT("Extensions32");
const TCHAR g_cbINI[] = TEXT("ini");

const TCHAR g_cbExtensions[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions");
const TCHAR g_cbConfig[] = TEXT("Config");
const TCHAR g_cbClsId[] = TEXT("CLSID");
const TCHAR g_cbNotPrimary[] = TEXT("NotPrimary");
const TCHAR g_cbInprocServer[] = TEXT("InprocServer32");

const TCHAR g_cbNil[] = TEXT("");
const TCHAR g_cbDel[] = TEXT("\\");

const TCHAR g_cbPattern[] = TEXT(";%1=%2");

const TCHAR g_cbRegConfig[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config");
const TCHAR g_cbImportFormat[] = TEXT("ImportFormat");
const TCHAR g_cbDescription[] = TEXT("Description");
const TCHAR g_cbFileExt[] = TEXT("FileExtension");
const TCHAR g_cbConfigPage[] = TEXT("ConfigPage");

const TCHAR g_cbWarnBeforeDelObj[] = TEXT("WarnBeforeDelObj");

const TCHAR g_cbTransaktion[] = TEXT("Transaktion %d");

const TCHAR g_cbFeatureMap[] = TEXT("FeatureMap");

///////////////////////////////////////////////////////////////////////////////
// Monikersupport
const TCHAR g_cbMkPropAct[] = TEXT("MkPropAct");
const TCHAR g_cbMkPropSeq[] = TEXT("MkPropSeq");

/////////////////////////////////////////////////////////////////////////////
// Feststehende PropertyBag-Keys für PropertyActions
const OLECHAR g_cbPAPrefix[] = L";PropActData";		// Prefix für PropActDaten
const OLECHAR g_cbPAName[] = L"Name";				// Name der propertyAction
const OLECHAR g_cbPANoShow[] = L"NoShow";			// Dialog _nicht_ anzeigen

const OLECHAR g_cbProgID[] = L"ProgID";				// ProgID für ImportData
const OLECHAR g_cbFlags[] = L"Flags";				// Flags für ImportData
const OLECHAR g_cbFiles[] = L"Files";				// Files für ImportData
const OLECHAR g_cbShowErrors[] = L"ShowErrors";		// Importfehler anzeigen

const OLECHAR g_cbObjProp[] = L"ObjProp";			// aus Objekteigenschaft ... generieren
const OLECHAR g_cbDirect[] = L"Direct";				// aus gegebenem Text erzeugen
const OLECHAR g_cbDependend[] = L"Dependend";		// abhängige Texte erzeugen
const OLECHAR g_cbDynamic[] = L"Dynamic";			// dynamische Text erzeugeen (nur bei ObjProp und Dependend)
const OLECHAR g_cbDelete[] = L"Delete";				// evtl. existierende Texte vorher löschen (nur bei Dependend)
const OLECHAR g_cbDoNotMove[] = L"DoNotMove";		// an Punktobjekte nicht verschieben
const OLECHAR g_cbRotate[] = L"Rotate";				// an Linienobjekten drehen (nur bei Dependend)
const OLECHAR g_cbDeleteTarget[] = L"DeleteTarget";	// Bezugsobjekte nach Texterzeugen löschen (nur bei !Depenend)
const OLECHAR g_cbExistantOnly[] = L"ExistentOnly";	// nur für existierende Objekteigenschaften

const OLECHAR g_cbDesc[] = L"Desc";					// Beschreibungsinfo 
const OLECHAR g_cbHelpDesc[] = L"HelpDesc";			// Lange Beschreibungsinfo 
const OLECHAR g_cbDataSource[] = L"DataSource";		// Zieldatenquelle
const OLECHAR g_cbModifyTo[] = L"ModifyTo";			// Objektklasse modifizieren
const OLECHAR g_cbAddToClass[] = L"AddToClass";		// als Objektklasse speichern

const OLECHAR g_cbCheckMode[] = L"CheckMode";		// Idents selektieren zuschaltbar
const OLECHAR g_cbCheckModeChecked[] = L"Checked";	// Idents selektieren zugeschaltet (bei CheckMode=1)

const OLECHAR g_cbOperation[] = L"Operation";		// Operationen von PropOp
const OLECHAR g_cbA_Or_B[] = L"A_Or_B";				// Vereinigungsmenge 
const OLECHAR g_cbA_And_B[] = L"A_And_B";			// Schnittmenge
const OLECHAR g_cbA_And_NotB[] = L"A_And_NotB";		// Komplementärmenge zu A aus B
const OLECHAR g_cbNotA_And_B[] = L"NotA_And_B";		// Komplementärmenge zu B aus A
const OLECHAR g_cbA_Xor_B[] = L"A_Xor_B";			// Exklusives Oder

const OLECHAR g_cbDeleteSrcObjs[] = L"DeleteSrcObjs";	// Ausgangsobjekte löschen
const OLECHAR g_cbMarkSrcObjs[] = L"MarkSrcObjs";		// Ausgangsobjekte markieren
const OLECHAR g_cbCopySrcObjs[] = L"CopySrcObjs";		// alleinstehende Ausgangsobjekte kopieren

const OLECHAR g_cbSelectObjs[] = L"SelectObjs";		// Objekte aus ORWnds benutzen
const OLECHAR g_cbActivated[] = L"Activated";		// ... alle aktivierten (blinkenden)
const OLECHAR g_cbSelected[] = L"Selected";			// ... alle selektierten
const OLECHAR g_cbAll[] = L"All";					// ... alle Objekte
const OLECHAR g_cbCloseWhenReady[] = L"CloseWhenReady";		// ORWnds nach erfolgreichem Abarbeiten schließen
const OLECHAR g_cbShowConfigAlways[] = L"ShowConfigAlways";	// Config-Fenster immer anzeigen (auch bei einem ORWnd)
const OLECHAR g_cbDisableCloseWhenReady[] = L"DisableCloseWhenReady";	// passivieren von 'ORWnds nach erfolgreichem Abarbeiten schließen'

const OLECHAR g_cbInitData[] = L"InitData";			// Daten für externe GeoComp's

const OLECHAR g_cbLimitORWndCount[] = L"LimitORWndCount";	// LimitPackets
const OLECHAR g_cbLimitObjCount[] = L"LimitObjCount";
const OLECHAR g_cbLimitOperation[] = L"LimitOperation";
const OLECHAR g_cbLimitGE[] = L"LimitGE";			// >=
const OLECHAR g_cbLimitGT[] = L"LimitGT";			// >
const OLECHAR g_cbLimitEQ[] = L"LimitEQ";			// ==
const OLECHAR g_cbLimitLT[] = L"LimitLT";			// <
const OLECHAR g_cbLimitLE[] = L"LimitLE";			// <

///////////////////////////////////////////////////////////////////////////////
// Bezeichner der PropActScripte
const OLECHAR g_cbObjekteDoppeln[] = L"ObjekteDoppeln";
const OLECHAR g_cbObjekteVereinigen[] = L"ObjekteVereinigen";

#if defined(_USE_XML_GEOCOMPONENTS)

///////////////////////////////////////////////////////////////////////////////
// XmlPropertySequence
const OLECHAR g_cbGeoComponentSequence[] = L"GeoComponentSequence";
const OLECHAR g_cbGeoComponent[] = L"GeoComponent";
const OLECHAR g_cbName[] = L"Name";
const OLECHAR g_cbSaveAs[] = L"SaveAs";
const OLECHAR g_cbLoad[] = L"Load";
const OLECHAR g_cbType[] = L"Type";
const OLECHAR g_cbLoadInfo[] = L"LoadInfo";
const OLECHAR g_cbInitInfo[] = L"InitInfo";
const OLECHAR g_cbExpandName[] = L"ExpandName";
const OLECHAR g_cbRegistry[] = L"Registry";
const OLECHAR g_cbDirectL[] = L"Direct";
const OLECHAR g_cbAction[] = L"Action";
const OLECHAR g_cbProperty[] = L"Property";
const OLECHAR g_cbSequence[] = L"Sequence";
const OLECHAR g_cbLevel[] = L"Level";
const OLECHAR g_cbRegistryRoot[] = L"RegistryRoot";
const OLECHAR g_cbHKCR[] = L"HKCR";
const OLECHAR g_cbHKCU[] = L"HKCU";
const OLECHAR g_cbHKLM[] = L"HKLM";
const OLECHAR g_cbRegistryPath[] = L"RegistryPath";
const OLECHAR g_cbErrorInfo[] = L"ErrorInfo";
const OLECHAR g_cbCaption[] = L"Caption";
const OLECHAR g_cbPrompt[] = L"Prompt";
const OLECHAR g_cbInitPattern[] = L";%1=%2";
const OLECHAR g_cbVBInitPattern[] = L",%1(%2)";
const OLECHAR g_cbDescriptionL[] = L"Description";
const OLECHAR g_cbMayFail[] = L"MayFail";			// darf fehlschlagen
const OLECHAR g_cbMonikerData[] = L"MonikerData";
const OLECHAR g_cbVersion[] = L"Version";
const OLECHAR g_cbHeaderTitle[] = L"HeaderTitle";
const OLECHAR g_cbHeaderSubTitle[] = L"HeaderSubTitle";
const OLECHAR g_cbIsWizard97[] = L"IsWizard97";

const char g_cbTRiAS[] = "TRiAS®";

#endif // defined(_USE_XML_GEOCOMPONENTS)

