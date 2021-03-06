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
Resource2=IDD_ABOUTBOX
Resource3=IDD_GAGE_DIALOG
Resource4=IDD_CONFIG_DIALOG

[CLS:CACE400GageApp]
Type=0
BaseClass=CWinApp
HeaderFile=ACE400Gage.h
ImplementationFile=ACE400Gage.cpp
LastObject=CACE400GageApp

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
LastObject=CConfigDialog

[CLS:CGageDialog]
Type=0
BaseClass=CDialog
HeaderFile=GageDialog.h
ImplementationFile=GageDialog.cpp
LastObject=IDC_BUTTON_DO_STUDY
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
ControlCount=33
Control1=IDC_STATIC,static,1342308352
Control2=IDC_GRID_GAGE,MFCGridCtrl,1342242816
Control3=IDC_EDIT_4W_FILE_PATH,edit,1350633600
Control4=IDC_COMBO_MEAS_TYPE,combobox,1344340226
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_REF_INPUT,edit,1350633600
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_TOL_INPUT,edit,1350639744
Control10=IDC_CHART_GAGE,static,1342177294
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308364
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,button,1342177287
Control17=IDC_GRID_GAGE_STAT,MFCGridCtrl,1342242816
Control18=IDC_GRID_BIAS,MFCGridCtrl,1342242816
Control19=IDC_GRID_CAPABILITY,MFCGridCtrl,1342242816
Control20=IDC_LIST_MSG,listbox,1353777411
Control21=IDC_BUTTON_LOAD_MEASDATA,button,1342242816
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_EDIT_MEASDATA_CNT,edit,1350633600
Control25=IDC_GRID_REPT,MFCGridCtrl,1342242816
Control26=IDC_STATIC,static,1342308352
Control27=IDC_EDIT_STUDY_CNT,edit,1350639744
Control28=IDC_BUTTON_DO_STUDY,button,1342242816
Control29=IDC_BUTTON_SAVE_FILE,button,1342242816
Control30=IDC_BUTTON_VIEW_FILE,button,1342242816
Control31=IDC_BUTTON_GAGE_SAVE_ALL,button,1342251008
Control32=IDC_STATIC,static,1342308352
Control33=IDC_EDIT_SAVED_PATH,edit,1350633476

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

