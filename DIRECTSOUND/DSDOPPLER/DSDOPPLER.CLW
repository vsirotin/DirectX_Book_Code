; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CDSDopplerView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DSDoppler.h"
LastPage=0

ClassCount=5
Class1=CDSDopplerApp
Class2=CDSDopplerDoc
Class3=CDSDopplerView
Class4=CMainFrame

ResourceCount=8
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Resource8=IDD_3DSOURCE

[CLS:CDSDopplerApp]
Type=0
HeaderFile=DSDoppler.h
ImplementationFile=DSDoppler.cpp
Filter=N

[CLS:CDSDopplerDoc]
Type=0
HeaderFile=DSDopplerDoc.h
ImplementationFile=DSDopplerDoc.cpp
Filter=N

[CLS:CDSDopplerView]
Type=0
HeaderFile=DSDopplerView.h
ImplementationFile=DSDopplerView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CDSDopplerView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=DSDoppler.cpp
ImplementationFile=DSDoppler.cpp
Filter=D

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
Class=?
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_FILE,edit,1350631552
Control4=65535,static,1342308352
Control5=IDC_FILEOPEN,button,1342242816
Control6=65535,button,1342177287
Control7=65535,button,1342177287
Control8=65535,static,1342308352
Control9=IDC_DIST_MIN,edit,1350639744
Control10=65535,static,1342308352
Control11=IDC_DIST_MAX,edit,1350639744
Control12=65535,static,1342308352
Control13=65535,static,1342308352
Control14=65535,static,1342308352

