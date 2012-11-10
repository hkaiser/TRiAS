; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CObjFeatScriptDlg
LastTemplate=CDialog
NewFileInclude1=#include "bscriptp.hxx"
NewFileInclude2=#include "bscript.h"
VbxHeaderFile=bscript.h
VbxImplementationFile=bscript.cpp
LastPage=0

ClassCount=14
Class1=CBScriptDebug

ResourceCount=16
Resource1=IDD_DEBUGGERDLG
Resource2=IDD_FILTERDLG
Resource3=IDD_CUSTOMIZEDLG
Class2=CDummyParent
Resource4=IDR_DLGMENU
Resource5=IDD_CUSTOMIZE
Resource6=IDD_PROPPAGE_SMALL (English (U.S.))
Resource7=IDD_DIALOGBAR (English (U.S.))
Resource8=IDD_FORMVIEW (English (U.S.))
Class3=CScriptDlg
Resource9=IDD_OBJECTFEATURESCRIPTDLG
Class4=CCustPropSheet
Class5=CCustPSh
Class6=CCustDlg
Class7=CCustomizeMenuPPExt
Resource10=IDR_RBUTTONDEBUGGER
Resource11=IDR_DEBUGFRAME
Resource12=IDD_DUMMYPARENT
Class8=CFilterScriptDlg
Resource13=IDR_MENU1
Resource14=IDR_RBUTTONFILTER
Class9=CSheetDlg
Class10=CSheet
Class11=Cver
Class12=CStopDlg
Class13=CScriptName
Resource15=IDD_SCRIPTDLG
Class14=CObjFeatScriptDlg
Resource16=IDR_MACRO

[CLS:CBScriptDebug]
Type=0
HeaderFile=\triasdev.mvc\xtension\bscript\bscripta.h
ImplementationFile=\triasdev.mvc\xtension\bscript\bscripta.cpp
BaseClass=CDialog
LastObject=CBScriptDebug
Filter=D
VirtualFilter=dWC

[DLG:IDD_DEBUGGERDLG]
Type=1
Class=CBScriptDebug
ControlCount=0

[MNU:IDR_DLGMENU]
Type=1
Class=?
Command1=ID_DEBUG_NEW
Command2=ID_DEBUG_OPEN
Command3=ID_DEBUG_SAVE
Command4=ID_DEBUG_SAVEAS
Command5=IDM_CLOSE
Command6=ID_DEBUG_UNDO
Command7=ID_DEBUG_CUT
Command8=ID_DEBUG_COPY
Command9=ID_DEBUG_PASTE
Command10=ID_DEBUG_DELETE
Command11=ID_DEBUG_FIND
Command12=ID_DEBUG_FINDNEXT
Command13=ID_DEBUG_REPLACE
Command14=ID_DEBUG_GOTOLINE
Command15=ID_DEBUG_NEWDIALOG
Command16=ID_DEBUG_EDITDIALOG
Command17=ID_DEBUG_FONTS
Command18=ID_DEBUG_GO
Command19=ID_DEBUG_SUSPEND
Command20=ID_DEBUG_TRACEIN
Command21=ID_DEBUG_TRACEOVER
Command22=ID_DEBUG_ADDWATCH
Command23=ID_DEBUG_DELETEWATCH
Command24=ID_DEBUG_BREAKPOINT
Command25=ID_DEBUG_CALLSTACK
Command26=ID_DEBUG_SYNTAX
Command27=ID_DEBUG_EDITORHELP
Command28=ID_DEBUG_TRIASHELP
Command29=ID_DEBUG_GETHELPON
CommandCount=29

[MNU:IDR_MACRO]
Type=1
Class=?
Command1=IDM_TEST
Command2=IDM_DBSCRIPT
Command3=IDM_FILTERSCRIPT
CommandCount=3

[CLS:CDummyParent]
Type=0
HeaderFile=..\dummypar.h
ImplementationFile=..\dummypar.cpp
LastObject=CDummyParent

[DLG:IDD_DUMMYPARENT]
Type=1
Class=?
ControlCount=0

[DLG:IDD_SCRIPTDLG]
Type=1
Class=CScriptDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_MACRONAME,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_MAKROLIST,listbox,1352728835
Control5=IDC_RUN,button,1342373888
Control6=IDOK,button,1342373889
Control7=IDC_ENTFERNEN,button,1342242816
Control8=IDCANCEL,button,1342373888
Control9=IDC_AUTOSTART,button,1342242819

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_FORMVIEW (English (U.S.))]
Type=1
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_SMALL (English (U.S.))]
Type=1
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CScriptDlg]
Type=0
HeaderFile=\Triasdev.mvc\Xtension\Bscript\scrptdlg.h
ImplementationFile=\Triasdev.mvc\Xtension\Bscript\scrptdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CScriptDlg

[CLS:CCustPropSheet]
Type=0
HeaderFile=CstPSh.h
ImplementationFile=CstPSh.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CCustPropSheet

[CLS:CCustPSh]
Type=0
HeaderFile=..\custpsh.h
ImplementationFile=..\custpsh.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CCustPSh

[CLS:CCustDlg]
Type=0
HeaderFile=..\custdlg.h
ImplementationFile=..\custdlg.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_MENUTREE
VirtualFilter=idWC

[DLG:IDD_CUSTOMIZE]
Type=1
Class=CCustDlg
ControlCount=8
Control1=IDC_STATICMACROS,static,1342308352
Control2=IDC_MENUTREE,SysTreeView32,1350631487
Control3=IDC_MACROLIST,combobox,1344340227
Control4=IDC_EINFUEGEN,button,1342242816
Control5=IDC_LOESCHEN,button,1342242816
Control6=IDC_LINKS,button,1073807360
Control7=IDC_RECHTS,button,1073807360
Control8=IDOK,button,1073807360

[CLS:CCustomizeMenuPPExt]
Type=0
HeaderFile=CustPPxt.h
ImplementationFile=CustPPxt.cpp
BaseClass=CCmdTarget
Filter=N
LastObject=CCustomizeMenuPPExt

[TB:IDR_DEBUGFRAME]
Type=1
Class=?
Command1=ID_BUTTON2753
Command2=ID_BUTTON2754
Command3=ID_BUTTON2755
Command4=ID_BUTTON2756
Command5=ID_BUTTON2757
Command6=ID_BUTTON2758
Command7=ID_BUTTON2759
Command8=ID_BUTTON2760
Command9=ID_BUTTON2761
Command10=ID_BUTTON2762
Command11=ID_BUTTON2763
CommandCount=11

[CLS:CFilterScriptDlg]
Type=0
HeaderFile=..\filtdlg.h
ImplementationFile=..\filtdlg.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CFilterScriptDlg
VirtualFilter=idWC

[DLG:IDD_CUSTOMIZEDLG]
Type=1
Class=?
ControlCount=8
Control1=IDC_STATICMACROS,static,1342308352
Control2=IDC_MENUTREE,SysTreeView32,1350631487
Control3=IDC_MACROLIST,combobox,1344340227
Control4=IDC_EINFUEGEN,button,1342242816
Control5=IDC_LOESCHEN,button,1342242816
Control6=IDC_LINKS,button,1073807360
Control7=IDC_RECHTS,button,1073807360
Control8=IDOK,button,1073807360

[DLG:IDD_FILTERDLG]
Type=1
Class=CFilterScriptDlg
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COMBOOPATESCRIPTS,combobox,1344340226
Control3=IDC_ENTFERNEN,button,1342373888
Control4=IDC_SYNTAXTEST,button,1342242816
Control5=IDC_DEBUGGERSIZE,static,1342308352

[MNU:IDR_MENU1]
Type=1
CommandCount=0

[CLS:CSheetDlg]
Type=0
HeaderFile=..\shdlg.h
ImplementationFile=..\shdlg.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CSheetDlg

[CLS:CSheet]
Type=0
HeaderFile=..\sheet.h
ImplementationFile=..\Sheet.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CSheet

[CLS:Cver]
Type=0
HeaderFile=\Triasdev.mvc\Xtension\Bscript\ver.h
ImplementationFile=\Triasdev.mvc\Xtension\Bscript\ver.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Cver

[CLS:CStopDlg]
Type=0
HeaderFile=..\stopdlg.h
ImplementationFile=..\StopDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CStopDlg
VirtualFilter=dWC

[MNU:IDR_RBUTTONDEBUGGER]
Type=1
Class=CBScriptDebug
Command1=ID_DEBUG_GETHELPON
Command2=ID_DEBUG_UNDO
Command3=ID_DEBUG_CUT
Command4=ID_DEBUG_COPY
Command5=ID_DEBUG_PASTE
Command6=ID_DEBUG_DELETE
Command7=ID_DEBUG_NEWDIALOG
Command8=ID_DEBUG_EDITDIALOG
Command9=ID_DEBUG_BREAKPOINT
Command10=ID_DEBUG_ADDWATCH
Command11=ID_DEBUG_DELETEWATCH
Command12=ID_DEBUG_MODIFYDLG
Command13=ID_DEBUG_HEX
CommandCount=13

[CLS:CScriptName]
Type=0
HeaderFile=..\scrname.h
ImplementationFile=..\scrname.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CScriptName

[MNU:IDR_RBUTTONFILTER]
Type=1
Class=CFilterScriptDlg
Command1=ID_DEBUG_GETHELPON
Command2=ID_DEBUG_UNDO
Command3=ID_DEBUG_CUT
Command4=ID_DEBUG_COPY
Command5=ID_DEBUG_PASTE
Command6=ID_DEBUG_DELETE
Command7=ID_DEBUG_NEWDIALOG
Command8=ID_DEBUG_EDITDIALOG
Command9=ID_DEBUG_BREAKPOINT
Command10=ID_DEBUG_SAVE
Command11=ID_DEBUG_IMPORT
Command12=ID_DEBUG_EXPORT
CommandCount=12

[DLG:IDD_OBJECTFEATURESCRIPTDLG]
Type=1
Class=CObjFeatScriptDlg
ControlCount=6
Control1=IDC_INSTALL,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_UNINSTALL,button,1342242816
Control4=IDC_MACROLIST,SysListView32,1350648199
Control5=IDC_STATIC,static,1342308352
Control6=IDC_BUTTON2,button,1342242816

[CLS:CObjFeatScriptDlg]
Type=0
HeaderFile=..\ofeatdlg.h
ImplementationFile=..\ofeatdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CObjFeatScriptDlg

