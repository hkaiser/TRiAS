; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCopyDLKDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CopyDLK2.h"
ODLFile=CopyDLK2.odl

ClassCount=4
Class1=CCopyDLKApp
Class2=CCopyDLKDlg
Class3=CAboutDlg
Class4=CCopyDLKDlgAutoProxy

ResourceCount=2
Resource1=IDR_MAINFRAME
Resource2=IDD_COPYDLK2_DIALOG

[CLS:CCopyDLKApp]
Type=0
HeaderFile=CopyDLK2.h
ImplementationFile=CopyDLK2.cpp
Filter=N

[CLS:CCopyDLKDlg]
Type=0
HeaderFile=CopyDLKDlg.h
ImplementationFile=CopyDLKDlg.cpp
Filter=D
LastObject=IDC_INVENTAR
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=CopyDLKDlg.h
ImplementationFile=CopyDLKDlg.cpp
Filter=D

[CLS:CCopyDLKDlgAutoProxy]
Type=0
HeaderFile=DlgProxy.h
ImplementationFile=DlgProxy.cpp
BaseClass=CCmdTarget
Filter=N

[DLG:IDD_COPYDLK2_DIALOG]
Type=1
Class=CCopyDLKDlg
ControlCount=15
Control1=IDC_FILESTOCOPY,SysListView32,1350664205
Control2=IDC_STATIC,static,1342308352
Control3=IDC_SOURCEDIR,edit,1350633600
Control4=IDC_STATIC,static,1342308352
Control5=IDC_DESTINATIONDIR,edit,1350633600
Control6=IDC_PARAMETERS,static,1342308352
Control7=IDC_SOURCEDATA,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_INVENTAR_FILE,edit,1350633600
Control10=IDC_STATIC,static,1342308352
Control11=IDC_FILESTOCOPYLIST,edit,1350633600
Control12=IDC_COPY,button,1342242817
Control13=IDCANCEL,button,1342242816
Control14=IDC_PROMPT,static,1342308352
Control15=IDC_COPYPROGRESS,msctls_progress32,1342177281

