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

const TCHAR g_cbExtensions[] = TEXT("Software\\uve\\TRiAS\\Extensions");
const TCHAR g_cbConfig[] = TEXT("Config");
const TCHAR g_cbClsId[] = TEXT("CLSID");
const TCHAR g_cbNotPrimary[] = TEXT("NotPrimary");
const TCHAR g_cbInprocServer[] = TEXT("InprocServer32");

const TCHAR g_cbNil[] = TEXT("");
const TCHAR g_cbDel[] = TEXT("\\");

const TCHAR g_cbPattern[] = TEXT(";%1=%2");

const TCHAR g_cbRegExtensions[] = TEXT("Software\\uve\\TRiAS\\Extensions");
const TCHAR g_cbImportFormat[] = TEXT("ImportFormat");
const TCHAR g_cbDescription[] = TEXT("Description");
const TCHAR g_cbFileExt[] = TEXT("FileExtension");

const TCHAR g_cbTransaktion[] = TEXT("Transaktion %d");

const TCHAR g_cbFeatureMap[] = TEXT("FeatureMap");

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

const OLECHAR g_cbDesc[] = L"Desc";					// Beschreibungsinfo 
const OLECHAR g_cbHelpDesc[] = L"HelpDesc";			// Lange Beschreibungsinfo 

const OLECHAR g_cbCheckMode[] = L"CheckMode";		// Idents selektieren zuschaltbar
const OLECHAR g_cbCheckModeChecked[] = L"Checked";	// Idents selektieren zugeschaltet (bei CheckMode=1)

///////////////////////////////////////////////////////////////////////////////
// Bezeichner der PropActScripte
const OLECHAR g_cbObjekteDoppeln[] = L"ObjekteDoppeln";
const OLECHAR g_cbObjekteVereinigen[] = L"ObjekteVereinigen";

