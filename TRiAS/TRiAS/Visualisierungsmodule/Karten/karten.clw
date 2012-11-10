; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CImagePropertySheet
LastTemplate=CPropertySheet
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "karten.h"
CDK=Y

ClassCount=9
Class1=CKartenCtrl
Class2=CKartenPropPage

ResourceCount=5
LastPage=0
Resource2=IDD_PAGE_VISPARAM
Resource3=IDD_PAGE_DIRECTORIES
Resource4=IDD_DLGQUERYPARAMETERS
Resource1=IDD_PAGE_COLORPARAM
Class3=CDlgPgColor
Class4=CDlgPgDirectories
Class5=CDlgPgVisparam
Class6=CDlgSheetMapParam
Class7=CDlgPgUsrCoord
Class8=CDlgPgBW
Class9=CImagePropertySheet
Resource5=IDD_PAGE_BWPARAM

[CLS:CKartenCtrl]
Type=0
HeaderFile=TKarten.h
ImplementationFile=TKarten.cpp
Filter=W
LastObject=CKartenCtrl

[CLS:CKartenPropPage]
Type=0
HeaderFile=TKPpg.h
ImplementationFile=TKPpg.cpp
Filter=D
BaseClass=COlePropertyPage
VirtualFilter=idWC
LastObject=CKartenPropPage

[DLG:IDD_DLGQUERYPARAMETERS]
Type=1
Class=?
ControlCount=17
Control1=IDC_STATIC,button,1342177287
Control2=IDC_CHKSINGLEMAP,button,1342373897
Control3=IDC_CHKALLMAPS,button,1342177289
Control4=IDC_LISTOFPALETTES,listbox,1352732675
Control5=IDC_STATIC,button,1342177287
Control6=IDC_CHKVISIBLE,button,1342242819
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342308352
Control9=IDC_FROM_SCALE,combobox,1344339971
Control10=IDC_STATIC,static,1342308352
Control11=IDC_TO_SCALE,combobox,1344339971
Control12=IDC_STATIC,button,1342177287
Control13=IDC_LIST_MAPDIRS,listbox,1352728577
Control14=IDC_STATIC,button,1342177287
Control15=IDI_VMDICON,static,1342177283
Control16=IDOK,button,1342242817
Control17=IDCANCEL,button,1342242816

[DLG:IDD_PAGE_COLORPARAM]
Type=1
Class=CDlgPgColor
ControlCount=4
Control1=IDC_LISTOFPALETTES,listbox,1352859907
Control2=IDC_CHKSINGLEMAP,button,1073938441
Control3=IDC_CHKALLMAPS,button,1073741833
Control4=IDC_TRANSPARndENT,button,1342373891

[DLG:IDD_PAGE_VISPARAM]
Type=1
Class=CDlgPgVisparam
ControlCount=7
Control1=IDC_STATIC,button,1342177287
Control2=IDC_CHKVISIBLE,button,1342242819
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_FROM_SCALE,combobox,1344339971
Control6=IDC_STATIC,static,1342308352
Control7=IDC_TO_SCALE,combobox,1344339971

[DLG:IDD_PAGE_DIRECTORIES]
Type=1
Class=CDlgPgDirectories
ControlCount=1
Control1=IDC_LIST_MAPDIRS,listbox,1352728577

[CLS:CDlgPgColor]
Type=0
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CDlgPgColor
VirtualFilter=idWC

[CLS:CDlgPgDirectories]
Type=0
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CDlgPgDirectories

[CLS:CDlgPgVisparam]
Type=0
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_TO_SCALE

[CLS:CDlgSheetMapParam]
Type=0
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CDlgSheetMapParam

[CLS:CDlgPgUsrCoord]
Type=0
HeaderFile=dialogs.h
ImplementationFile=dialogs.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CDlgPgUsrCoord

[DLG:IDD_PAGE_BWPARAM]
Type=1
Class=CDlgPgBW
ControlCount=3
Control1=IDC_CHECK_TRANSPARENT,button,1342242819
Control2=IDC_RADIO_BLACK,button,1342308361
Control3=IDC_RADIO_WHITE,button,1342177289

[CLS:CDlgPgBW]
Type=0
HeaderFile=DlgPgBW.h
ImplementationFile=DlgPgBW.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CDlgPgBW

[CLS:CImagePropertySheet]
Type=0
HeaderFile=ImagePropertySheet.h
ImplementationFile=ImagePropertySheet.cpp
BaseClass=CPropertySheet
Filter=W
VirtualFilter=hWC
LastObject=CImagePropertySheet

