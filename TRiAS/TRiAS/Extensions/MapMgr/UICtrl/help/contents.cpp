/*
@doc
@contents1 Inhaltsverzeichnis |
@subindex Objekte
@subindex Interfaces
@subindex Methoden
@subindex Properties
@subindex Datenstrukturen
@subindex Enumerationen
@subindex Konstanten
@subindex Beispiele

@normal Diese Hilfedatei wurde erzeugt am: <date>

@subindex Über diese Hilfedatei

***********************************************************************
@contents2 Objekte |
@normal TRiAS - Userinterfaceobjekte
@index object | (OBJECT & TRiASUI)
***********************************************************************
@contents2 Interfaces |
@normal Interfaces der TRiAS - Userinterfaceobjekte
@index interface | (INTERFACE & TRiASUI)
***********************************************************************
@contents2 Methoden |
@normal Alle Methoden auf einen Blick
@index method | (METHOD & TRiASUI)
***********************************************************************
@contents2 Properties |
@normal Alle Properties auf einen Blick
@index property | (PROPERTY & TRiASUI)
***********************************************************************
@contents2 Datenstrukturen |
@normal Datenstrukturen
@index struct | (STRUCT & TRiASUI)
***********************************************************************
@contents2 Enumerationen |
@normal Aufzählungstypen
@index enum | (ENUM & TRiASUI)
***********************************************************************
@contents2 Konstanten |
@normal Konstanten
@index constv | 
***********************************************************************
@contents2 Beispiele |
@index | EXAMPLES
***********************************************************************
@topic Setzen / Lesen von Parametern |
kann man auch machen...
***********************************************************************
@contents2 Über diese Hilfedatei | 

Copyright<csign> 1991-1998 <company>, #<copyright> V<version>
<nl>For more information about TRiASDB, contact Hartmut Kaiser (H.Kaiser@intertrias.com)

<nl>The sources for this Help file were generated
by Autoduck, the source code documentation tool that generates Print or
Help files from tagged comments in C, C++, Assembly, and Basic source
files.
<nl>For more information about Autoduck, contact Eric Artzt (erica@microsoft.com).
***********************************************************************/
#include <olectl.h>
// MaskEditX.idl : IDL source for MaskEditX.dll
//

// This file will be processed by the MIDL tool to
// produce the type library (MaskEditX.tlb) and marshalling code.

import "oaidl.idl";
import "ocidl.idl";

	

[
	uuid(51BB3DD1-0C38-11D2-8F6B-0060085FC1CE),
	version(1.0),
	helpstring("TRiAS UserInterface Controls")
]
library UICtrlLib
{
	importlib("stdole32.tlb");
	importlib("stdole2.tlb");

	[
		object,
		uuid(51BB3DDE-0C38-11D2-8F6B-0060085FC1CE),
		dual,
		helpstring("IMaskEdit Interface"),
		pointer_default(unique)
	]
	interface IMaskEdit : IDispatch
	{
		[propput, id(DISPID_BACKCOLOR)]
		HRESULT BackColor([in]OLE_COLOR clr);
		[propget, id(DISPID_BACKCOLOR)]
		HRESULT BackColor([out,retval]OLE_COLOR* pclr);
		[propput, id(DISPID_BORDERCOLOR)]
		HRESULT BorderColor([in]OLE_COLOR clr);
		[propget, id(DISPID_BORDERCOLOR)]
		HRESULT BorderColor([out, retval]OLE_COLOR* pclr);
		[propput, id(DISPID_BORDERSTYLE)]
		HRESULT BorderStyle([in]long style);
		[propget, id(DISPID_BORDERSTYLE)]
		HRESULT BorderStyle([out, retval]long* pstyle);
		[propputref, id(DISPID_FONT)]
		HRESULT Font([in]IFontDisp* pFont);
		[propput, id(DISPID_FONT)]
		HRESULT Font([in]IFontDisp* pFont);
		[propget, id(DISPID_FONT)]
		HRESULT Font([out, retval]IFontDisp** ppFont);
		[propput, id(DISPID_BORDERVISIBLE)]
		HRESULT BorderVisible([in]VARIANT_BOOL vbool);
		[propget, id(DISPID_BORDERVISIBLE)]
		HRESULT BorderVisible([out, retval]VARIANT_BOOL* pbool);
		[propget, id(1), helpstring("property Mask")] HRESULT Mask([out, retval] BSTR *pVal);
		[propput, id(1), helpstring("property Mask")] HRESULT Mask([in] BSTR newVal);
		[propget, id(2), helpstring("property PromptChar")] HRESULT PromptChar([out, retval] BSTR *pVal);
		[propput, id(2), helpstring("property PromptChar")] HRESULT PromptChar([in] BSTR newVal);
		[propget, id(3), helpstring("property EscapeChar")] HRESULT EscapeChar([out, retval] BSTR *pVal);
		[propget, id(4), helpstring("property Text")] HRESULT Text(short DelimterCharacter, [out, retval] BSTR *pVal);
		[propput, id(4), helpstring("property Text")] HRESULT Text(short DelimterCharacter, [in] BSTR newVal);
	};

	[
		uuid(6F7B7340-0F97-11d2-8F6D-0060085FC1CE)
		, helpstring("Event interface for MaskEdit Control")
	]
	dispinterface _DMaskEditEvents
	{
		properties:
			//  Event interface has no properties

		methods:
			[id(1)] void TextChange();
		[id(2), helpstring("method AdvanceFocusNext")] void AdvanceFocusNext();
		[id(3), helpstring("method AdvanceFocusPrevious")] void AdvanceFocusPrevious();
	};

	[
		uuid(51BB3DDF-0C38-11D2-8F6B-0060085FC1CE),
		helpstring("MaskEdit Class")
	]
	coclass MaskEdit
	{
		[default] interface IMaskEdit;
		[default, source] dispinterface _DMaskEditEvents;
	};
	

	[
		uuid(51BB3DE2-0C38-11D2-8F6B-0060085FC1CE),
		helpstring("PpgMaskEdit Class")
	]
	coclass PpgMaskEdit
	{
		interface IUnknown;
	};
};

/***********************************************************************

***********************************************************************
***********************************************************************/
