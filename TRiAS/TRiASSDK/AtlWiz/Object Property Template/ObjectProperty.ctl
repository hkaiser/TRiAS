[!Debug()]
[!newguid(InterfaceGUID)]
[!set(Attributes, "0001100011")]
[!set(ObjPropAttr, "000")]
[!Dialog("Names98", "ObjDlg98", "TRiASOP98")]

[!strcpy(UpperShortName, ShortName)]
[!toupper(UpperShortName)]

[!AddStringToSymbol(HeaderTemplate, GalleryPath, "ObjectProperty.h")]
[!AddStringToSymbol(CPPTemplate, GalleryPath, "ObjectProperty.cpp")]
[!AddStringToSymbol(RGSTemplate, GalleryPath, "ObjectProperty.rgs")]

[!AddSymbolToSymbol(RGSName, ProjectDirectory, ShortName)]
[!AddStringToSymbol(RGSName, RGSName, ".rgs")]

[!target(RGSName)]
[!include(RGSTemplate)]
[!target()]

[!AddSymbolToString(IDR_REGISTRYID, "IDR_", UpperShortName)]
[!AddRegistryToRC(RGSName, IDR_REGISTRYID)]

[!AddSymbolToString(IDS_OP_NAME, "IDS_OP_NAME_", UpperShortName)]
[!AddStringResource(IDS_OP_NAME, ObjPropName)]
[!AddSymbolToString(IDS_OP_DESCRIPTION, "IDS_OP_DESCRIPTION_", UpperShortName)]
[!AddStringResource(IDS_OP_DESCRIPTION, ObjPropDesc)]

[!target(HeaderName)]
[!include(HeaderTemplate)]
[!target()]

[!target(CPPName)]
[!include(CPPTemplate)]
[!target()]

[!AddStringToSymbol(IDLCoClass, GalleryPath, "ObjectPropertyCo.idl")]
[!AddCoClassToIDL(IDLProject, IDLCoClass)]

[!target(IDLName)]
[!include(IDLTemplate)]
[!target()]

[!AddToObjectMap(CoClassName, ClassName)]

[!AddSymbolToString(header, "\"", HeaderName)]
[!AddStringToSymbol(header, header, "\"")]
[!AddImportFile(IDLProject, "oaidl.idl")]
[!AddIncludeFile(ProjectNameCPP,  header)]

[!AddIncludeFile(STDAFXH, "<ospace/com/smartif.h>")]
[!AddIncludeFile(STDAFXH, "<tstring>")]
[!AddIncludeFile(STDAFXH, "<xtension.h>")]
[!AddIncludeFile(STDAFXH, "<ixtensn.hxx>")]
[!AddIncludeFile(STDAFXH, "<Com/ComErrorMacros.h>")]
[!AddIncludeFile(STDAFXCPP, "<Com/ObjectPropertyBase.cpp>")]

[!AddFileToProject(CPPName)]
[!AddFileToProject(HeaderName)]

