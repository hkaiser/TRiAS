[!Debug()]
[!newguid(InterfaceGUID)]
[!set(Attributes, "0001100011")]
[!set(PropActAttr, "0000000")]
[!Dialog("Names98", "ObjDlg98", "TRiASPP98")]

[!strcpy(UpperShortName, ShortName)]
[!toupper(UpperShortName)]

[!AddStringToSymbol(HeaderTemplate, GalleryPath, "PropertyAction.h")]
[!AddStringToSymbol(CPPTemplate, GalleryPath, "PropertyAction.cpp")]
[!AddStringToSymbol(RGSTemplate, GalleryPath, "PropertyAction.rgs")]

[!AddSymbolToSymbol(RGSName, ProjectDirectory, ShortName)]
[!AddStringToSymbol(RGSName, RGSName, ".rgs")]

[!target(RGSName)]
[!include(RGSTemplate)]
[!target()]

[!AddSymbolToString(IDR_REGISTRYID, "IDR_", UpperShortName)]
[!AddRegistryToRC(RGSName, IDR_REGISTRYID)]

[!AddSymbolToString(IDS_PA_DESCRIPTION, "IDS_DESCRIPTION_", UpperShortName)]
[!AddStringResource(IDS_PA_DESCRIPTION, PropActDesc)]

[if=(PropActHasUI, "TRUE")]
[!AddStringToSymbol(DlgClassName, ClassName, "Dlg")]
[!endif]

[!target(HeaderName)]
[!include(HeaderTemplate)]
[!target()]

[!target(CPPName)]
[!include(CPPTemplate)]
[!target()]

[!AddStringToSymbol(IDLCoClass, GalleryPath, "PropertyActionCo.idl")]
[!AddCoClassToIDL(IDLProject, IDLCoClass)]

[!target(IDLName)]
[!include(IDLTemplate)]
[!target()]

[!AddToObjectMap(CoClassName, ClassName)]

[!AddSymbolToString(header, "\"", HeaderName)]
[!AddStringToSymbol(header, header, "\"")]
[!AddImportFile(IDLProject, "oaidl.idl")]
[!AddImportFile(IDLProject, "ProgInd2.idl")]
[!AddIncludeFile(ProjectNameCPP,  header)]

[!AddIncludeFile(STDAFXH, "<ospace/com/smartif.h>")]
[!AddIncludeFile(STDAFXH, "<tstring>")]
[!AddIncludeFile(STDAFXCPP, "<Com/PropertyActionBase.cpp>")]

[!AddFileToProject(CPPName)]
[!AddFileToProject(HeaderName)]

[if=(PropActHasUI, "TRUE")]

[!AddStringToSymbol(DlgHeaderTemplate, GalleryPath, "PropertyActionDlg.h")]
[!AddStringToSymbol(DlgCPPTemplate, GalleryPath, "PropertyActionDlg.cpp")]

[!AddSymbolToString(IDD_DIALOGID, "IDD_", UpperShortName)]
[!AddStringToSymbol(IDD_DIALOGID, IDD_DIALOGID, "_OPTIONS")]
[!AddStringToSymbol(RCFile, GalleryPath, "PropertyAction.rc")]
[!AddResourceFromFile(RCFile, IDD_DIALOGID, "DIALOG")]

[!target(DlgHeaderName)]
[!include(DlgHeaderTemplate)]
[!target()]

[!target(DlgCPPName)]
[!include(DlgCPPTemplate)]
[!target()]

[!AddFileToProject(DlgCPPName)]
[!AddFileToProject(DlgHeaderName)]

[!if(VC)]
[!Commit()]
[!OpenDialog(IDD_DIALOGID)]
[!endif]
[!endif]

