; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCopyDLKWDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "copydlkw.h"
LastPage=0

ClassCount=8
Class1=CCopyDLKWApp
Class2=CAboutDlg
Class3=CCopyDLKWDlg
Class4=CModifyButtonFolder
Class5=CGetFolderControl
Class6=CFindTreeView
Class7=CFileDirDialog
Class8=CCopyDLKWDlgAutoProxy

ResourceCount=3
Resource1=IDD_COPYDLKW_DIALOG
Resource2=IDD_ABOUTBOX
Resource3=1536

[CLS:CCopyDLKWApp]
Type=0
BaseClass=CWinApp
HeaderFile=CopyDLKW.h
ImplementationFile=CopyDLKW.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=CopyDLKWDlg.cpp
ImplementationFile=CopyDLKWDlg.cpp

[CLS:CCopyDLKWDlg]
Type=0
BaseClass=CDialog
HeaderFile=CopyDLKWDlg.h
ImplementationFile=CopyDLKWDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_CLOSE

[CLS:CModifyButtonFolder]
Type=0
BaseClass=CButton
HeaderFile=DDXGetFolder.h
ImplementationFile=DDXGetFolder.cpp

[CLS:CGetFolderControl]
Type=0
BaseClass=CStatic
HeaderFile=DDXGetFolder.h
ImplementationFile=DDXGetFolder.cpp

[CLS:CFindTreeView]
Type=0
BaseClass=CTreeCtrl
HeaderFile=DDXGetFolder.h
ImplementationFile=DDXGetFolder.cpp

[CLS:CFileDirDialog]
Type=0
BaseClass=CFileDialog
HeaderFile=Dlgdir.h
ImplementationFile=Dlgdir.cpp

[CLS:CCopyDLKWDlgAutoProxy]
Type=0
BaseClass=CCmdTarget
HeaderFile=DlgProxy.h
ImplementationFile=DlgProxy.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_COPYDLKW_DIALOG]
Type=1
Class=CCopyDLKWDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_SOURCEDIR,edit,1350633600
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DESTINATIONDIR,edit,1350633600
Control5=IDC_PROMPT,static,1342308352
Control6=IDC_COPYPROGRESS,msctls_progress32,1342177281
Control7=IDOK,button,1342242817
Control8=IDC_CLOSE,button,1342242816

[DLG:1536]
Type=1
Class=?
ControlCount=14
Control1=1090,static,1342308352
Control2=1152,edit,1350632576
Control3=1120,listbox,1352732755
Control4=65535,static,1342308352
Control5=1088,static,1342308480
Control6=1121,listbox,1352732755
Control7=1089,static,1342308352
Control8=1136,combobox,1352728643
Control9=1091,static,1342308352
Control10=1137,combobox,1352729427
Control11=IDOK,button,1342373889
Control12=IDCANCEL,button,1342373888
Control13=1038,button,1342373888
Control14=1040,button,1342373891

