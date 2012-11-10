; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShowOKSDlg
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ShowOKS.h"

ClassCount=4
Class1=CShowOKSApp
Class2=CShowOKSDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class3=COksTreeCtrl
Class4=CDragDropTreeCtrl
Resource2=IDD_SHOWOKS_DIALOG

[CLS:CShowOKSApp]
Type=0
HeaderFile=ShowOKS.h
ImplementationFile=ShowOKS.cpp
Filter=N

[CLS:CShowOKSDlg]
Type=0
HeaderFile=ShowOKSDlg.h
ImplementationFile=ShowOKSDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_SHOWOKS_DIALOG]
Type=1
Class=CShowOKSDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDC_OKSTREE,SysTreeView32,1350631719
Control3=IDC_STATIC,static,1342308352
Control4=IDC_GEN_TEXT,static,1342312448
Control5=IDC_STATIC,static,1342308352
Control6=IDC_OPENFILE,button,1342242816
Control7=IDC_GEN_CODE,static,1342308352
Control8=IDC_SAVECOMPILED,button,1342242816

[CLS:CDragDropTreeCtrl]
Type=0
HeaderFile=DragDropTreeCtrl.h
ImplementationFile=DragDropTreeCtrl.cpp
BaseClass=CTreeCtrl
Filter=W
LastObject=CDragDropTreeCtrl
VirtualFilter=GWC

[CLS:COksTreeCtrl]
Type=0
HeaderFile=okstreectrl.h
ImplementationFile=okstreectrl.cpp
BaseClass=CDragDropTreeCtrl
LastObject=COksTreeCtrl
Filter=W
VirtualFilter=GWC

