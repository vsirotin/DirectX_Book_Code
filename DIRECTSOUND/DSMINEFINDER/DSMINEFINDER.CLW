; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CDSMineFinderView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DSMineFinder.h"
LastPage=0

ClassCount=6
Class1=CDSMineFinderApp
Class2=CDSMineFinderDoc
Class3=CDSMineFinderView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CSet3DSourceDlg
Resource3=IDD_3DSOURCE

[CLS:CDSMineFinderApp]
Type=0
HeaderFile=DSMineFinder.h
ImplementationFile=DSMineFinder.cpp
Filter=N

[CLS:CDSMineFinderDoc]
Type=0
HeaderFile=DSMineFinderDoc.h
ImplementationFile=DSMineFinderDoc.cpp
Filter=N

[CLS:CDSMineFinderView]
Type=0
HeaderFile=DSMineFinderView.h
ImplementationFile=DSMineFinderView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CDSMineFinderView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=DSMineFinder.cpp
ImplementationFile=DSMineFinder.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_3DSOURCE]
Type=1
Class=CSet3DSourceDlg
ControlCount=31
Control1=IDC_FILE,edit,1350631552
Control2=IDC_FILEOPEN,button,1342242816
Control3=IDC_VISIBLE,button,1342242819
Control4=IDC_RANDSET,button,1342373897
Control5=IDC_USERSET,button,1342177289
Control6=IDC_X,edit,1350770816
Control7=IDC_Y,edit,1350639744
Control8=IDC_ANGLE,edit,1350639744
Control9=IDC_ANGL_INN,edit,1350639744
Control10=IDC_ANGL_OUT,edit,1350639744
Control11=IDC_DIST_MIN,edit,1350639744
Control12=IDC_DIST_MAX,edit,1350639744
Control13=IDOK,button,1342242817
Control14=IDCANCEL,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352

[CLS:CSet3DSourceDlg]
Type=0
HeaderFile=Set3DSourceDlg.h
ImplementationFile=Set3DSourceDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSet3DSourceDlg

