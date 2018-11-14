; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGageDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ace400gage.h"
LastPage=0

ClassCount=6
Class1=CACE400GageApp
Class2=CRectCtrl
Class3=CConfigDialog
Class4=CGageDialog
Class5=CAboutDlg
Class6=CMainDialog

ResourceCount=4
Resource1=IDD_MAIN_DIALOG
Resource2=IDD_GAGE_DIALOG
Resource3=IDD_ABOUTBOX
Resource4=IDD_CONFIG_DIALOG

[CLS:CACE400GageApp]
Type=0
BaseClass=CWinApp
HeaderFile=ACE400Gage.h
ImplementationFile=ACE400Gage.cpp

[CLS:CRectCtrl]
Type=0
BaseClass=CStatic
HeaderFile=ChartViewer.h
ImplementationFile=ChartViewer.cpp

[CLS:CConfigDialog]
Type=0
BaseClass=CDialog
HeaderFile=ConfigDialog.h
ImplementationFile=ConfigDialog.cpp

[CLS:CGageDialog]
Type=0
BaseClass=CDialog
HeaderFile=GageDialog.h
ImplementationFile=GageDialog.cpp
LastObject=CGageDialog
Filter=D
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MainDialog.cpp
ImplementationFile=MainDialog.cpp
LastObject=CAboutDlg

[CLS:CMainDialog]
Type=0
BaseClass=CDialog
HeaderFile=MainDialog.h
ImplementationFile=MainDialog.cpp
Filter=D
VirtualFilter=dWC
LastObject=CMainDialog

[DLG:IDD_CONFIG_DIALOG]
Type=1
Class=CConfigDialog
ControlCount=11
Control1=IDC_CHECK_PRT_BASIC,button,1342246915
Control2=IDC_STATIC,button,1342177287
Control3=IDC_CHECK_PRT_LEVEL1,button,1342246915
Control4=IDC_CHECK_PRT_Level2,button,1342246915
Control5=IDC_CHECK_PRT_LEVEL3,button,1342246915
Control6=IDC_CHECK_PRT_DEVICE,button,1342246915
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC_PRINT_STATE,static,1342308865
Control9=IDC_CHECK_PRT_DEV_D64,button,1342246915
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC_USED_MEM,static,1342308865

[DLG:IDD_GAGE_DIALOG]
Type=1
Class=CGageDialog
ControlCount=42
Control1=IDC_STATIC,static,1342308352
Control2=IDC_GRID,MFCGridCtrl,1342242816
Control3=IDC_EDIT_4W_FILE_PATH,edit,1350633600
Control4=IDC_BUTTON_LOAD_FILE,button,1342251008
Control5=IDC_COMBO_MEAS_TYPE,combobox,1344340226
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_REF_INPUT,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_TOL_INPUT,edit,1350633600
Control11=IDC_STATIC,static,1342177294
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_REF,edit,1350633600
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_MEAN,edit,1350633600
Control19=IDC_STATIC,static,1342308352
Control20=IDC_EDIT_STDEV,edit,1350633600
Control21=IDC_STATIC,static,1342308352
Control22=IDC_EDIT_TOL,edit,1350633600
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,static,1342308352
Control25=IDC_EDIT_BIAS,edit,1350633600
Control26=IDC_STATIC,static,1342308352
Control27=IDC_EDIT_T,edit,1350633600
Control28=IDC_STATIC,static,1342308352
Control29=IDC_EDIT_PVALUE,edit,1350633600
Control30=IDC_STATIC,button,1342177287
Control31=IDC_STATIC,static,1342308352
Control32=IDC_EDIT_CG,edit,1350633600
Control33=IDC_STATIC,static,1342308352
Control34=IDC_EDIT_CGK,edit,1350633600
Control35=IDC_STATIC,static,1342308352
Control36=IDC_EDIT_VAR_REPT,edit,1350633600
Control37=IDC_STATIC,static,1342308352
Control38=IDC_EDIT_VAR_REPT_BIAS,edit,1350633600
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,button,1342177287
Control41=IDC_STATIC,button,1342177287
Control42=IDC_BUTTON2,button,1342251008

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MAIN_DIALOG]
Type=1
Class=CMainDialog
ControlCount=3
Control1=IDOK,button,1342242816
Control2=IDC_CHECK_GAGE,button,1342246915
Control3=IDC_CHECK_CONFIG,button,1342246915

