; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMathOperationPropertyDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "statist.h"
LastPage=0

ClassCount=9
Class1=CMathOperationPropertyDlg
Class2=CMeshGenerationDlg
Class3=CPopup
Class4=CPopupTreeCtrl
Class5=CSelectObjectProperties
Class6=CSelectStatisticValues
Class7=CSelectStatistValueDlg
Class8=CSeparator
Class9=CUnitsOfMeasureDlg

ResourceCount=11
Resource1=IDD_OBJPROPTREE
Resource2=IDD_SELECTSTATISTVALUE_OPTIONS
Resource3=IDD_UNITSOFMEASURE
Resource4=IDD_MATHOP_CONFIG
Resource5=IDD_OBJPROPTREEDLG
Resource6=IDD_POPUPTREECTRL
Resource7=IDD_POPUPTREEDLG
Resource8=IDD_MESHGENERATION_OPTIONS
Resource9=IDD_PROJECTVALUEPAGECTRL
Resource10=IDD_PROJECTVALUES
Resource11=IDR_STATFUNC

[CLS:CMathOperationPropertyDlg]
Type=0
BaseClass=CPropertyPage
HeaderFile=MathOperationPropertyDlg.h
ImplementationFile=MathOperationPropertyDlg.cpp
LastObject=CMathOperationPropertyDlg
Filter=D
VirtualFilter=idWC

[CLS:CMeshGenerationDlg]
Type=0
BaseClass=CPropertyPage
HeaderFile=MeshGenerationDlg.h
ImplementationFile=MeshGenerationDlg.cpp

[CLS:CPopup]
Type=0
BaseClass=CMiniFrameWnd
HeaderFile=Popup.h
ImplementationFile=Popup.cpp

[CLS:CPopupTreeCtrl]
Type=0
BaseClass=CTreeCtrl
HeaderFile=PopupTreeCtrl.h
ImplementationFile=PopupTreeCtrl.cpp

[CLS:CSelectObjectProperties]
Type=0
BaseClass=CPopupTreeCtrl
HeaderFile=SelectObjectProperties.h
ImplementationFile=SelectObjectProperties.cpp

[CLS:CSelectStatisticValues]
Type=0
BaseClass=CPopupTreeCtrl
HeaderFile=SelectStatisticValues.h
ImplementationFile=SelectStatisticValues.cpp

[CLS:CSelectStatistValueDlg]
Type=0
BaseClass=CPropertyPage
HeaderFile=SelectStatistValueDlg.h
ImplementationFile=SelectStatistValueDlg.cpp
LastObject=CSelectStatistValueDlg

[CLS:CSeparator]
Type=0
BaseClass=CStatic
HeaderFile=Separator.h
ImplementationFile=Separator.cpp

[CLS:CUnitsOfMeasureDlg]
Type=0
BaseClass=CPropertyPage
HeaderFile=UnitsOfMeasureDlg.h
ImplementationFile=UnitsOfMeasureDlg.cpp

[DLG:IDD_MATHOP_CONFIG]
Type=1
Class=CMathOperationPropertyDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PLUS,button,1342373897
Control3=IDC_MINUS,button,1342177289
Control4=IDC_MULTIPLY,button,1342177289
Control5=IDC_DIVIDE,button,1342177289
Control6=IDC_OBJPROP1,{09C04255-07E6-4EFD-8DED-F362DAE31E2B},1342177280
Control7=IDC_OBJPROP2,{09C04255-07E6-4EFD-8DED-F362DAE31E2B},1342177280
Control8=IDC_STATIC_DELIMITER,static,1342308352

[DLG:IDD_MESHGENERATION_OPTIONS]
Type=1
Class=CMeshGenerationDlg
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_CONVEXHULL,button,1342383113
Control3=IDC_VORONOI,button,1342186505
Control4=IDC_DELAUNAY,button,1342186505
Control5=IDC_OPERATION,static,1342312462
Control6=IDC_DESC_OPERATION,static,1342308352
Control7=IDC_STATIC_DESC,static,1342308352

[DLG:IDD_SELECTSTATISTVALUE_OPTIONS]
Type=1
Class=CSelectStatistValueDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC_DELIMITER,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_OBJPROPTREE,{09C04255-07E6-4EFD-8DED-F362DAE31E2B},1342177280
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATISTPROPTREE,{09C04255-07E6-4EFD-8DED-F362DAE31E2B},1342242816
Control7=IDC_STATIC_OPTIONS,static,1342308352
Control8=IDC_EVALRELATION,button,1342373891
Control9=IDC_INVERTVALUE,button,1342242819

[DLG:IDD_UNITSOFMEASURE]
Type=1
Class=CUnitsOfMeasureDlg
ControlCount=11
Control1=IDC_STATIC_UNITS,static,1342308352
Control2=IDC_AUTO_SELECT,button,1342373897
Control3=IDC_SELECT_UNITS,button,1342177289
Control4=IDC_UNIT_OF_LENGTH,combobox,1344339971
Control5=IDC_UNIT_OF_AREA,combobox,1344339971
Control6=IDC_STATIC_DESC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_APPENDUNITS,button,1342242819
Control9=IDC_STATIC_OPTIONS,static,1342308352
Control10=IDC_STATIC_LENGTH,static,1342308352
Control11=IDC_STATIC_AREA,static,1342308352

[DLG:IDD_OBJPROPTREE]
Type=1
Class=?
ControlCount=3
Control1=IDC_LABEL,static,1342308352
Control2=IDC_OBJECTPROPERTY,edit,1350633600
Control3=IDC_SELECT_OBJPROP,button,1342242955

[DLG:IDD_OBJPROPTREEDLG]
Type=1
Class=?
ControlCount=1
Control1=IDC_POPUPTREE,SysTreeView32,1342373943

[DLG:IDD_POPUPTREECTRL]
Type=1
Class=?
ControlCount=4
Control1=IDC_LABEL,static,1342308352
Control2=IDC_OBJECTPROPERTY,edit,1350633600
Control3=IDC_SELECT_OBJPROP,button,1342242955
Control4=IDC_CUSTOMIZE,button,1073807499

[DLG:IDD_POPUPTREEDLG]
Type=1
Class=?
ControlCount=1
Control1=IDC_POPUPTREE,SysTreeView32,1342373943

[DLG:IDD_PROJECTVALUES]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC_CATEGORIES,static,1342308352
Control2=IDC_CATEGORIES,ComboBoxEx32,1344340227
Control3=IDC_VALUES,static,1342177298
Control4=IDC_NOMODULES,static,1073741825

[DLG:IDD_PROJECTVALUEPAGECTRL]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATISTVALUES,SysTreeView32,1350762547

[TB:IDR_STATFUNC]
Type=1
Class=?
Command1=ID_BUTTON32770
Command2=ID_BUTTON32771
Command3=ID_TOOL_STATISTICS
Command4=ID_BUTTON32772
CommandCount=4

