; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPageGeometry
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "linesig32.h"
VbxHeaderFile=linesig32.h
VbxImplementationFile=linesig32.cpp
LastPage=0

ClassCount=6
Class1=CPageGeometry
Class2=CPageSelectSig
Class3=CDlgLinesigParam
Class4=CWmfShape

ResourceCount=6
Resource1=IDD_DLGPAGE_GEOMETRY
Resource2=IDD_PROPPAGE_LINESIG
Resource3=IDD_DLGPAGE_SELECT
Class5=CPageDebug
Resource4=IDD_DLG_SPECPARAM
Resource5=IDD_DLGSHEET_LINESIG
Class6=CPgError
Resource6=IDD_PROPPAGE_ERROR

[CLS:CPageGeometry]
Type=0
HeaderFile=dlglines.h
ImplementationFile=dlglines.cpp
LastObject=IDC_SPIN_SIGWIDTH
Filter=D
BaseClass=CPropertyPage
VirtualFilter=idWC

[CLS:CPageSelectSig]
Type=0
HeaderFile=dlglines.h
ImplementationFile=dlglines.cpp
Filter=D
BaseClass=CPropertyPage
VirtualFilter=idWC
LastObject=IDC_TREE_LINESIG

[CLS:CDlgLinesigParam]
Type=0
HeaderFile=dlglines.h
ImplementationFile=dlglines.cpp
LastObject=CDlgLinesigParam
Filter=W
BaseClass=CPropertySheet
VirtualFilter=hWC

[CLS:CWmfShape]
Type=0
HeaderFile=dlglines.h
ImplementationFile=dlglines.cpp
Filter=W
VirtualFilter=BWC
LastObject=CWmfShape
BaseClass=CStatic

[DLG:IDD_DLGPAGE_GEOMETRY]
Type=1
Class=CPageGeometry
ControlCount=22
Control1=IDC_STATIC,static,1342308352
Control2=IDC_CHECKSWAPX,button,1342242819
Control3=IDC_CHECKSWAPY,button,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDITSIGHEIGHT,edit,1350631424
Control6=IDC_SPIN_SIGHEIGHT,msctls_updown32,1342177430
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDITSIGWIDTH,edit,1350631424
Control9=IDC_SPIN_SIGWIDTH,msctls_updown32,1342177430
Control10=IDC_STATIC,static,1342308352
Control11=IDC_BTNFROMWIDTH,button,1342242816
Control12=IDC_BTNFROMHEIGHT,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDITSIGXOFFSET,edit,1350635520
Control15=IDC_SPIN_SIGXOFFSET,msctls_updown32,1342177430
Control16=IDC_STATIC,static,1342308352
Control17=IDC_EDITSIGYOFFSET,edit,1350635520
Control18=IDC_SPIN_SIGYOFFSET,msctls_updown32,1342177430
Control19=IDC_STATIC,button,1342177287
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,static,1342308353
Control22=IDC_STATIC,static,1342308353

[DLG:IDD_DLGPAGE_SELECT]
Type=1
Class=CPageSelectSig
ControlCount=1
Control1=IDC_TREE_LINESIG,SysTreeView32,1350631424

[DLG:IDD_DLGSHEET_LINESIG]
Type=1
Class=?
ControlCount=1
Control1=IDC_EDITPICTURE,button,1342242816

[DLG:IDD_DLG_SPECPARAM]
Type=1
Class=CPageDebug
ControlCount=9
Control1=IDC_EDITSCALE,edit,1350631424
Control2=IDC_SPIN_SCALE,msctls_updown32,1342177430
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDITARC,edit,1350631424
Control5=IDC_SPIN_ARC,msctls_updown32,1342177430
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_CHECK_CLIPEXTENDED,button,1342242819
Control9=IDC_CHECK_MARKSEGMENTS,button,1342242819

[CLS:CPageDebug]
Type=0
HeaderFile=dlglines.h
ImplementationFile=dlglines.cpp
Filter=D
LastObject=CPageDebug
VirtualFilter=dWC
BaseClass=CPropertyPage

[DLG:IDD_PROPPAGE_LINESIG]
Type=1
Class=?
ControlCount=0

[DLG:IDD_PROPPAGE_ERROR]
Type=1
Class=CPgError
ControlCount=1
Control1=IDC_LIST_ERROR,listbox,1352728833

[CLS:CPgError]
Type=0
HeaderFile=PgError.h
ImplementationFile=PgError.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CPgError

