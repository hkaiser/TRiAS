; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCoolBtn
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "triasui.h"
LastPage=0

ClassCount=5
Class1=CCoolBtn
Class2=CEditFeatureDlg
Class3=CEditFeatureParamDlg
Class4=CEditRO
Class5=CStdCtrlDlg

ResourceCount=4
Resource1=IDD_STDCTRLDLG
Resource2=IDD_EDITFEATUREPARAMDLG
Resource3=IDD_EDITFEATUREDLG
Resource4=IDR_TREE_POPUPMENU

[CLS:CCoolBtn]
Type=0
BaseClass=CButton
HeaderFile=CoolBtn.h
ImplementationFile=CoolBtn.cpp
LastObject=CCoolBtn
Filter=W
VirtualFilter=BWC

[CLS:CEditFeatureDlg]
Type=0
BaseClass=COlePropertyPage
HeaderFile=editfeaturedlg.h
ImplementationFile=EditFeatureDlg.cpp

[CLS:CEditFeatureParamDlg]
Type=0
BaseClass=COlePropertyPage
HeaderFile=EditFeatureParamDlg.h
ImplementationFile=EditFeatureParamDlg.cpp

[CLS:CEditRO]
Type=0
BaseClass=CEdit
HeaderFile=EditRO.h
ImplementationFile=EditRO.cpp

[CLS:CStdCtrlDlg]
Type=0
BaseClass=CDialog
HeaderFile=StdCtrlDlg.h
ImplementationFile=StdCtrlDlg.cpp
Filter=D
VirtualFilter=dWC

[DLG:IDD_EDITFEATUREDLG]
Type=1
Class=CEditFeatureDlg
ControlCount=4
Control1=IDC_PROPERTY_NAME,static,1342308352
Control2=IDC_PROPERTY_RO,button,1073807363
Control3=IDC_EDIT_FEATUREVALUE,edit,1352728644
Control4=IDC_PROPERTY_LONGNAME,static,1342312448

[DLG:IDD_EDITFEATUREPARAMDLG]
Type=1
Class=CEditFeatureParamDlg
ControlCount=0

[DLG:IDD_STDCTRLDLG]
Type=1
Class=CStdCtrlDlg
ControlCount=11
Control1=IDC_STATIC,static,1476526080
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TREE,SysTreeView32,1350631463
Control4=IDC_TAB,SysTabControl32,1342373888
Control5=IDC_STATIC_RECTANGLE,static,1208090624
Control6=IDC_STATIC_FRAME,button,1073741831
Control7=IDC_STATIC_TEXT,static,1073872897
Control8=IDB_ACTIONS,button,1342373899
Control9=IDOK,button,1342373889
Control10=IDCANCEL,button,1342242816
Control11=IDAPPLY,button,1342373888

[MNU:IDR_TREE_POPUPMENU]
Type=1
Class=?
Command1=ID_DUMMY
CommandCount=1

