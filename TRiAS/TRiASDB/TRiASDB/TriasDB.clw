; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMessageBoxEx
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "triasdb.h"
LastPage=0

ClassCount=3
Class1=CCreateNewParamWiz
Class2=CCreateNewTemplateWiz
Class3=CMessageBoxEx

ResourceCount=4
Resource1=IDD_CREATENEWWIZARD_PARAMS
Resource2=IDD_CREATENEWWIZARD_TEMPLATE (_DEBUG)
Resource3=IDD_MESSAGEBOXEX
Resource4=IDD_MESSAGEBOXEXCANCEL

[CLS:CCreateNewParamWiz]
Type=0
BaseClass=CPropertyPage
HeaderFile=CreateNewParamWiz.h
ImplementationFile=CreateNewParamWiz.cpp
LastObject=CCreateNewParamWiz

[CLS:CCreateNewTemplateWiz]
Type=0
BaseClass=CPropertyPage
HeaderFile=CreateNewTemplateWiz.h
ImplementationFile=CreateNewTemplateWiz.cpp

[CLS:CMessageBoxEx]
Type=0
BaseClass=CDialog
HeaderFile=MessageBoxEx.h
ImplementationFile=MessageBoxEx.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_PROMPT_STATIC

[DLG:IDD_CREATENEWWIZARD_PARAMS]
Type=1
Class=CCreateNewParamWiz
ControlCount=5
Control1=IDC_CREATENEW_BMP,static,1350566414
Control2=IDC_DESCTEXT,static,1342308352
Control3=IDC_COMPATIBLE_WITH_V2,button,1342373891
Control4=IDC_COMPATIBLE_WITH_V4,button,1342373891
Control5=IDC_COMPRESS_STREAMS,button,1342373891

[DLG:IDD_CREATENEWWIZARD_TEMPLATE]
Type=1
Class=CCreateNewTemplateWiz

[DLG:IDD_MESSAGEBOXEXCANCEL]
Type=1
Class=?
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_PROMPT,edit,1073743876
Control3=IDYES,button,1342373889
Control4=IDNO,button,1342242816
Control5=IDC_YESALL,button,1342373888
Control6=IDC_NOALL,button,1342242816
Control7=IDCANCEL,button,1342242816
Control8=IDC_PROMPT_STATIC,static,1342308352

[DLG:IDD_MESSAGEBOXEX]
Type=1
Class=?
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_PROMPT,edit,1073743876
Control3=IDYES,button,1342373889
Control4=IDNO,button,1342242816
Control5=IDC_YESALL,button,1342373888
Control6=IDC_NOALL,button,1342242816
Control7=IDC_PROMPT_STATIC,static,1342308352

[DLG:IDD_CREATENEWWIZARD_TEMPLATE (_DEBUG)]
Type=1
Class=?
ControlCount=4
Control1=IDC_CREATENEW_BMP,static,1350566414
Control2=IDC_DESCTEXT,static,1342308352
Control3=IDC_DATABASE_TEMPLATE,SysListView32,1350664460
Control4=IDC_TEMPLATE_DESCRIPTION,static,1342308352

