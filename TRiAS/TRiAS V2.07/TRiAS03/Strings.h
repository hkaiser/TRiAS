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

extern const TCHAR g_cbExtensions[];		// TEXT("Software\\uve\\TRiAS\\Extensions");
extern const TCHAR g_cbConfig[];			// TEXT("Config");
extern const TCHAR g_cbClsId[];				// TEXT("CLSID");
extern const TCHAR g_cbNotPrimary[];		// TEXT("NotPrimary");
extern const TCHAR g_cbInprocServer[];		// TEXT("InprocServer32");

extern const TCHAR g_cbNil[];				// TEXT("");
extern const TCHAR g_cbDel[];				// TEXT("\\");

extern const TCHAR g_cbPattern[];			// TEXT("%1=%2;");

extern const TCHAR g_cbRegExtensions[];		// TEXT("Software\\uve\\TRiAS\\Extensions");
extern const TCHAR g_cbImportFormat[];		// TEXT("ImportFormat");
extern const TCHAR g_cbDescription[];		// TEXT("Description");
extern const TCHAR g_cbFileExt[];			// TEXT("FileExtension");

extern const TCHAR g_cbTransaktion[];		// TEXT("Transaktion %d");

extern const TCHAR g_cbFeatureMap[];		// TEXT("FeatureMap");

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

extern const OLECHAR g_cbDesc[];			// L"Desc";				// Beschreibungsinfo 
extern const OLECHAR g_cbHelpDesc[];		// L"HelpDesc";			// Lange Beschreibungsinfo 

extern const OLECHAR g_cbCheckMode[];		// L"CheckMode";		// Idents selektieren zuschaltbar
extern const OLECHAR g_cbCheckModeChecked[];		// L"Checked";	// Idents selektieren zugeschaltet (bei CheckMode=1)

///////////////////////////////////////////////////////////////////////////////
// Bezeichner der PropActScripte
extern const OLECHAR g_cbObjekteDoppeln[];	// L"ObjekteDoppeln";
extern const OLECHAR g_cbObjekteVereinigen[];	// L"ObjekteVereinigen";

#endif // !defined(_STRINGS_H__3DD94694_796B_11D1_9761_00A024D6F582__INCLUDED_)
