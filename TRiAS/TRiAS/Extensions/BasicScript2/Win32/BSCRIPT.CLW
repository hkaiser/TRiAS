; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMacroIntroDlg
LastTemplate=CDialog
NewFileInclude1=#include "bscriptp.hxx"
NewFileInclude2=#include "bscript.h"
VbxHeaderFile=bscript.h
VbxImplementationFile=bscript.cpp
LastPage=0

ClassCount=44
Class1=CBScriptDebug

ResourceCount=29
Resource1=IDR_MACROMENU
Resource2=IDD_FILTERDLG
Resource3=IDD_DUMMYPARENT
Class2=CDummyParent
Resource4=IDR_RBUTTONFILTER
Resource5=IDD_CUSTOMIZE
Resource6=IDD_PROPPAGE_SMALL (English (U.S.))
Resource7=IDD_DIALOGBAR (English (U.S.))
Resource8=IDD_FORMVIEW (English (U.S.))
Class3=CScriptDlg
Resource9=IDD_ADDFUNCTION
Class4=CCustPropSheet
Class5=CCustPSh
Class6=CCustDlg
Class7=CCustomizeMenuPPExt
Resource10=IDR_MAINFRAMERB
Resource11=IDR_PROJECTMENU
Resource12=IDD_OBJFEATINSTALLPP
Class8=CFilterScriptDlg
Resource13=IDD_FILEAUTOSTART
Resource14=IDD_SCRIPTDLG
Class9=CSheetDlg
Class10=CSheet
Class11=Cver
Class12=CStopDlg
Class13=CScriptName
Resource15=IDR_DEBUGFRAME
Class14=CObjFeatScriptDlg
Class15=CMacroCheckListBox
Class16=CBasicScriptDebugger
Class17=CSplitter
Class18=CDeb
Class19=CSplitFrame
Class20=CSplitTest
Class21=CSplit
Class22=CSplitView1
Class23=CMainFrameDeb
Class24=CSplitView2
Class25=CDebuggerCtrl
Class26=CRelMacroTreeBox
Resource16="IDR_PROJECTMENU"
Class27=CBSSplitterWnd
Class28=CEditCtrl
Class29=Cbla
Class30=CBla
Resource17=IDD_TREECAPTIONDLG
Resource18=IDR_ACCELERATOR_EDITCTRL
Resource19=IDD_FILEDLG
Class31=CAddFunctionDlg
Resource20=IDD_DEBUGGERDLG
Resource21=IDR_RBUTTONTREEGENERAL
Class32=CDebFileDialog
Class33=CMyFileDialog
Class34=CObjFeatInstallDlg
Class35=CNewFrame
Class36=CFilterScriptDlg2
Class37=CCaptionView
Resource22=IDR_RBUTTONDEBUGGER
Class38=CDebFormView
Resource23=IDD_DEBUGGERCAPTIONDLG
Class39=CDebFormVw
Class40=CDebFormView2
Resource24=IDR_PROJECTTOOLBAR
Resource25=IDR_ACCELERATOR_TREECTRL
Resource26=IDD_TOOLBARNOTIFICATION
Resource27=IDB_COMBO
Class41=CTreeTabCtrl
Class42=CNotificationComboBox
Class43=CNotifBar
Resource28=IDR_ACCELERATOR_DEBCTRL
Class44=CMacroIntroDlg
Resource29=IDD_MACROINTRO

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
Class=CBasicScriptDebugger
ControlCount=0

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
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_MACRONAME,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_MAKROLIST,listbox,1352728835
Control5=IDCANCEL,button,1342373888
Control6=IDC_RUN,button,1342373888
Control7=IDOK,button,1342373889
Control8=IDC_RUNFILE,button,1342242816
Control9=IDC_OPENFILE,button,1342242816
Control10=IDC_AUTOSTART,button,1342242819
Control11=IDC_IMPORT,button,1342242816

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
ControlCount=1
Control1=IDC_STATIC,static,1342308352
Class=CNotifBar

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
HeaderFile=..\scrptdlg.h
ImplementationFile=..\scrptdlg.cpp
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
LastObject=CCustDlg
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

[CLS:CFilterScriptDlg]
Type=0
HeaderFile=..\filtdlg.h
ImplementationFile=..\filtdlg.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CFilterScriptDlg
VirtualFilter=idWC

[DLG:IDD_FILTERDLG]
Type=1
Class=CFilterScriptDlg2
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COMBOOPATESCRIPTS,combobox,1344340226
Control3=IDC_ENTFERNEN,button,1342373888
Control4=IDC_SYNTAXTEST,button,1342242816
Control5=IDC_DEBUGGERSIZE,static,1342308352

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
Command7=ID_DEBUG_NEW
Command8=ID_DEBUG_NEWDIALOG
Command9=ID_DEBUG_EDITDIALOG
Command10=ID_DEBUG_FUNCTIONINSERT
Command11=ID_DEBUG_BREAKPOINT
Command12=ID_DEBUG_ADDWATCH
Command13=ID_DEBUG_DELETEWATCH
Command14=ID_DEBUG_MODIFYDLG
Command15=ID_DEBUG_HEX
CommandCount=15

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
Command12=ID_DEBUG_SAVEAS
CommandCount=12

[CLS:CObjFeatScriptDlg]
Type=0
HeaderFile=..\ofeatdlg.h
ImplementationFile=..\ofeatdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CMacroCheckListBox]
Type=0
HeaderFile=..\ofeatdlg.h
ImplementationFile=..\ofeatdlg.cpp
BaseClass=CCheckListBox
Filter=W
LastObject=CMacroCheckListBox
VirtualFilter=bWC

[CLS:CBasicScriptDebugger]
Type=0
HeaderFile=\VC-DLLs\Bscneu\bscptdeb.h
ImplementationFile=\VC-DLLs\Bscneu\bscptdeb.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CBasicScriptDebugger

[CLS:CDeb]
Type=0
HeaderFile=Deb.h
ImplementationFile=Deb.cpp
BaseClass=CDialog
Filter=D
LastObject=CDeb

[CLS:CSplitFrame]
Type=0
HeaderFile=..\splitframe.h
ImplementationFile=..\splitframe.cpp
BaseClass=CMDIChildWnd
Filter=M
VirtualFilter=mfWC
LastObject=CSplitFrame

[CLS:CSplitTest]
Type=0
HeaderFile=..\deb.h
ImplementationFile=..\deb.cpp
BaseClass=CDialog
Filter=D
LastObject=CSplitTest
VirtualFilter=dWC

[CLS:CSplit]
Type=0
HeaderFile=..\split.h
ImplementationFile=..\split.cpp
BaseClass=CFrameWnd
Filter=T
VirtualFilter=mfWC
LastObject=CSplit

[CLS:CSplitView1]
Type=0
HeaderFile=..\splitview1.h
ImplementationFile=..\splitview1.cpp
BaseClass=CDialog
Filter=D
LastObject=CSplitView1
VirtualFilter=dWC

[CLS:CMainFrameDeb]
Type=0
HeaderFile=..\mainfr.h
ImplementationFile=..\MainFr.cpp
BaseClass=CFrameWnd
Filter=T
VirtualFilter=fWC
LastObject=CMainFrameDeb

[CLS:CSplitView2]
Type=0
HeaderFile=..\splitview2.h
ImplementationFile=..\SplitView2.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSplitView2

[CLS:CDebuggerCtrl]
Type=0
HeaderFile=\VC-DLLs\Bscneu\debctrl.h
ImplementationFile=\VC-DLLs\Bscneu\debctrl.cpp
BaseClass=CWnd
LastObject=CDebuggerCtrl
Filter=W
VirtualFilter=WC

[CLS:CRelMacroTreeBox]
Type=0
HeaderFile=\VC-DLLs\Bscneu\spltree.h
ImplementationFile=\VC-DLLs\Bscneu\spltree.cpp
BaseClass=CTreeCtrl
Filter=W
VirtualFilter=GWC
LastObject=CRelMacroTreeBox

[MNU:"IDR_PROJECTMENU"]
Type=1
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

[MNU:IDR_PROJECTMENU]
Type=1
Class=?
Command1=ID_DEBUG_NEWFILE
Command2=ID_DEBUG_OPEN
Command3=ID_DEBUG_SAVE
Command4=ID_DEBUG_INSERT
Command5=ID_DEBUG_REMOVE
Command6=ID_DEBUG_IMPORTALL
Command7=ID_DEBUG_IMPORT
Command8=ID_DEBUG_SAVEAS
Command9=IDM_CLOSE
Command10=ID_DEBUG_UNDO
Command11=ID_DEBUG_CUT
Command12=ID_DEBUG_COPY
Command13=ID_DEBUG_PASTE
Command14=ID_DEBUG_DELETE
Command15=ID_DEBUG_FIND
Command16=ID_DEBUG_FINDNEXT
Command17=ID_DEBUG_REPLACE
Command18=ID_DEBUG_GOTOLINE
Command19=ID_DEBUG_NEW
Command20=ID_DEBUG_NEWDIALOG
Command21=ID_DEBUG_EDITDIALOG
Command22=ID_DEBUG_FUNCTIONINSERT
Command23=ID_DEBUG_FONTS
Command24=ID_VIEW_PROJECTBAR
Command25=ID_VIEW_DEBUGGERBAR
Command26=ID_VIEW_NOTIFICATIONBAR
Command27=ID_VIEW_STATUSBAR
Command28=ID_DEBUG_GO
Command29=ID_DEBUG_PAUSE
Command30=ID_DEBUG_SUSPEND
Command31=ID_DEBUG_TRACEIN
Command32=ID_DEBUG_TRACEOVER
Command33=ID_DEBUG_ADDWATCH
Command34=ID_DEBUG_DELETEWATCH
Command35=ID_DEBUG_MODIFYDLG
Command36=ID_DEBUG_HEX
Command37=ID_DEBUG_BREAKPOINT
Command38=ID_DEBUG_CALLSTACK
Command39=ID_DEBUG_SYNTAX
Command40=ID_DEBUG_EDITORHELP
Command41=ID_DEBUG_TRIASHELP
Command42=ID_DEBUG_GETHELPON
CommandCount=42

[CLS:CBSSplitterWnd]
Type=0
HeaderFile=..\splitter.h
ImplementationFile=..\splitter.cpp
BaseClass=CSplitterWnd
Filter=T
LastObject=CBSSplitterWnd
VirtualFilter=pWC

[CLS:CEditCtrl]
Type=0
HeaderFile=..\editctrl.h
ImplementationFile=..\editctrl.cpp
BaseClass=CWnd
Filter=W
LastObject=CEditCtrl
VirtualFilter=WC

[CLS:Cbla]
Type=0
HeaderFile=..\bla.h
ImplementationFile=..\bla.cpp
BaseClass=CDialog
Filter=D
LastObject=Cbla

[CLS:CBla]
Type=0
HeaderFile=..\bla.h
ImplementationFile=..\bla.cpp
BaseClass=CDialog
Filter=D
LastObject=CBla

[ACL:IDR_ACCELERATOR_DEBCTRL]
Type=1
Class=?
Command1=ID_DEBUG_FIND
Command2=ID_DEBUG_GOTOLINE
Command3=ID_DEBUG_NEWFILE
Command4=ID_DEBUG_OPEN
Command5=ID_DEBUG_REPLACE
Command6=ID_DEBUG_SAVE
Command7=ID_DEBUG_DELETEWATCH
Command8=ID_DEBUG_GETHELPON
Command9=ID_DEBUG_TRACEOVER
Command10=ID_DEBUG_FINDNEXT
Command11=ID_DEBUG_GO
Command12=ID_DEBUG_SYNTAX
Command13=ID_DEBUG_TRACEIN
Command14=ID_DEBUG_ADDWATCH
CommandCount=14

[ACL:IDR_ACCELERATOR_TREECTRL]
Type=1
Class=?
Command1=ID_DEBUG_IMPORT
Command2=ID_DEBUG_NEWFILE
Command3=ID_DEBUG_OPEN
Command4=ID_DEBUG_SAVE
Command5=ID_DEBUG_REMOVE
CommandCount=5

[MNU:IDR_MACROMENU]
Type=1
Class=?
Command1=IDM_DBSCRIPT
Command2=IDM_STORAGEMACRO
Command3=IDM_FILTERSCRIPT
CommandCount=3

[DLG:IDD_ADDFUNCTION]
Type=1
Class=CAddFunctionDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_TYP,edit,1350631552
Control6=IDC_DEKLARATION,edit,1350631552
Control7=IDC_RADIOPRIVATE,button,1476395017
Control8=IDC_RADIOPUBLIC,button,1476395017
Control9=IDC_STATIC,button,1476395015
Control10=IDC_CHECKFUNCTION,button,1342242819
Control11=IDC_COMBONOTIFICATION,combobox,1344340227
Control12=IDC_CHECKNOTIFICATION,button,1342242819

[CLS:CAddFunctionDlg]
Type=0
HeaderFile=..\addfdlg.h
ImplementationFile=..\addfdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAddFunctionDlg

[ACL:IDR_ACCELERATOR_EDITCTRL]
Type=1
Class=?
Command1=ID_DEBUG_TRACEOVER
Command2=ID_DEBUG_GO
Command3=ID_DEBUG_TRACEIN
CommandCount=3

[CLS:CDebFileDialog]
Type=0
HeaderFile=..\debfdlg.h
ImplementationFile=..\debfdlg.cpp
BaseClass=CFileDialog
Filter=D
LastObject=IDC_CHECKAUTO
VirtualFilter=dWC

[DLG:IDD_FILEDLG]
Type=1
Class=CDebFileDialog
ControlCount=1
Control1=IDC_CHECKLINK,button,1342242819

[CLS:CMyFileDialog]
Type=0
HeaderFile=..\myfiledg.h
ImplementationFile=..\myfiledg.cpp
BaseClass=CFileDialog
Filter=D
LastObject=CMyFileDialog
VirtualFilter=dWC

[DLG:IDD_OBJFEATINSTALLPP]
Type=1
Class=?
ControlCount=2
Control1=IDC_MACROLIST,listbox,1352728915
Control2=IDC_STATICML,static,1342308352

[CLS:CObjFeatInstallDlg]
Type=0
HeaderFile=\VC-DLLs\Bscneu\ofeatpp.h
ImplementationFile=\VC-DLLs\Bscneu\ofeatpp.cpp
BaseClass=CPropertyPage
LastObject=IDC_STATICML
Filter=D
VirtualFilter=idWC

[CLS:CNewFrame]
Type=0
HeaderFile=NewFrame.h
ImplementationFile=NewFrame.cpp
BaseClass=splitter
Filter=T
LastObject=CNewFrame

[DLG:IDD_FILEAUTOSTART]
Type=1
Class=CDebFileDialog
ControlCount=1
Control1=IDC_CHECKAUTO,button,1342242819

[CLS:CFilterScriptDlg2]
Type=0
HeaderFile=\VC-DLLs\Bscneu\filtdlg2.h
ImplementationFile=\VC-DLLs\Bscneu\filtdlg2.cpp
BaseClass=CPropertyPage
LastObject=CFilterScriptDlg2
Filter=D
VirtualFilter=idWC

[MNU:IDR_RBUTTONTREEGENERAL]
Type=1
Class=?
Command1=ID_DEBUG_OPEN
Command2=ID_DEBUG_SAVE
Command3=ID_DEBUG_IMPORT
Command4=ID_DEBUG_INSERT
Command5=ID_DEBUG_REMOVE
Command6=ID_DEBUG_OPEN
Command7=ID_DEBUG_SAVE
Command8=ID_DEBUG_FILTERIMPORT
Command9=ID_DEBUG_FILTERINSERT
Command10=ID_DEBUG_REMOVE
Command11=ID_DEBUG_OPEN
Command12=ID_DEBUG_SAVE
Command13=ID_DEBUG_OBJFEATIMPORT
Command14=ID_DEBUG_OBJFEATINSERT
Command15=ID_DEBUG_REMOVE
Command16=ID_DEBUG_IMPORT
Command17=ID_DEBUG_INSERT
Command18=ID_DEBUG_FILTERIMPORT
Command19=ID_DEBUG_FILTERINSERT
Command20=ID_DEBUG_OBJFEATIMPORT
Command21=ID_DEBUG_OBJFEATINSERT
Command22=ID_DEBUG_IMPORT
Command23=ID_DEBUG_INSERT
Command24=ID_DEBUG_FILTERIMPORT
Command25=ID_DEBUG_FILTERINSERT
Command26=ID_DEBUG_OBJFEATIMPORT
Command27=ID_DEBUG_OBJFEATINSERT
Command28=ID_DEBUG_OPEN
Command29=ID_DEBUG_NEWFILE
Command30=ID_DEBUG_OPEN
CommandCount=30

[CLS:CCaptionView]
Type=0
HeaderFile=..\cptvw.h
ImplementationFile=..\cptvw.cpp
BaseClass=CView
Filter=C
LastObject=CCaptionView
VirtualFilter=VWC

[CLS:CDebFormView]
Type=0
HeaderFile=..\dbfrmvw.h
ImplementationFile=..\dbfrmvw.cpp
BaseClass=CFormView
Filter=D
LastObject=CDebFormView
VirtualFilter=VWC

[DLG:IDD_TREECAPTIONDLG]
Type=1
Class=CDebFormView
ControlCount=2
Control1=IDC_TREE,SysTreeView32,1342242879
Control2=IDC_TABPROJECT,SysTabControl32,1342177282

[DLG:IDD_DEBUGGERCAPTIONDLG]
Type=1
Class=CDebFormVw
ControlCount=1
Control1=IDC_DEBUGGERCAPTION,static,1342308352

[CLS:CDebFormVw]
Type=0
HeaderFile=..\DbFrmVw.h
ImplementationFile=..\DbFrmVw.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=IDC_DEBUGGERCAPTION

[CLS:CDebFormView2]
Type=0
HeaderFile=..\DbFrmVw2.h
ImplementationFile=..\DbFrmVw2.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=CDebFormView2

[DLG:IDD_TOOLBARNOTIFICATION]
Type=1
Class=?
ControlCount=2
Control1=IDC_COMBONOTIFICATION,combobox,1344340227
Control2=IDC_STATIC,static,1342308352

[TB:IDB_COMBO]
Type=1
Command1=ID_BUTTON2836
CommandCount=1

[TB:IDR_PROJECTTOOLBAR]
Type=1
Command1=ID_BUTTON2837
Command2=ID_BUTTON2838
Command3=ID_BUTTON2855
Command4=ID_BUTTON2839
Command5=ID_BUTTON2852
Command6=ID_BUTTON2853
Command7=ID_BUTTON2854
CommandCount=7

[TB:IDR_DEBUGFRAME]
Type=1
Command1=ID_BUTTON2844
Command2=ID_BUTTON2845
Command3=ID_BUTTON2846
Command4=ID_BUTTON2850
Command5=ID_BUTTON2851
Command6=ID_BUTTON2847
Command7=ID_BUTTON2848
Command8=ID_BUTTON2849
Command9=ID_BUTTON2840
Command10=ID_BUTTON2841
Command11=ID_BUTTON2842
Command12=ID_BUTTON2843
CommandCount=12

[MNU:IDR_MAINFRAMERB]
Type=1
Class=?
Command1=ID_VIEW_PROJECTBAR
Command2=ID_VIEW_DEBUGGERBAR
Command3=ID_VIEW_NOTIFICATIONBAR
Command4=ID_VIEW_STATUSBAR
CommandCount=4

[CLS:CTreeTabCtrl]
Type=0
HeaderFile=..\ttabctrl.h
ImplementationFile=..\ttabctrl.cpp
BaseClass=CTabCtrl
Filter=W
LastObject=CTreeTabCtrl

[CLS:CNotificationComboBox]
Type=0
HeaderFile=NotificationComboBox.h
ImplementationFile=NotificationComboBox.cpp
BaseClass=CComboBox
Filter=W

[CLS:CNotifBar]
Type=0
HeaderFile=NotifBar.h
ImplementationFile=NotifBar.cpp
BaseClass=CDialog
Filter=D

[DLG:IDD_MACROINTRO]
Type=1
Class=CMacroIntroDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342177294
Control3=IDC_DONOTSHOWANYFURTHER,button,1342242819
Control4=IDC_STATIC,static,1342308352

[CLS:CMacroIntroDlg]
Type=0
HeaderFile=\triasdev.mvc\xtension\bs\macrointrodlg.h
ImplementationFile=\triasdev.mvc\xtension\bs\macrointrodlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMacroIntroDlg

