; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CDSMultiPlayDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DSMultiPlay.h"
LastPage=0

ClassCount=6
Class1=CDSMultiPlayApp
Class2=CDSMultiPlayDoc
Class3=CDSMultiPlayView
Class4=CMainFrame

ResourceCount=7
Resource1=IDR_DSMULTTYPE
Resource2=IDD_ABOUTBOX
Resource3=IDR_MAINFRAME
Class5=CChildFrame
Class6=CAboutDlg
Resource7=IDD_DSMULTIPLAY_FORM

[CLS:CDSMultiPlayApp]
Type=0
HeaderFile=DSMultiPlay.h
ImplementationFile=DSMultiPlay.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=ID_EDIT_STOP

[CLS:CDSMultiPlayDoc]
Type=0
HeaderFile=DSMultiPlayDoc.h
ImplementationFile=DSMultiPlayDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CDSMultiPlayDoc

[CLS:CDSMultiPlayView]
Type=0
HeaderFile=DSMultiPlayView.h
ImplementationFile=DSMultiPlayView.cpp
Filter=D
LastObject=CDSMultiPlayView
BaseClass=CFormView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=DSMultiPlay.cpp
ImplementationFile=DSMultiPlay.cpp
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
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_EDIT_PLAY
Command3=ID_EDIT_STOP
CommandCount=3

[MNU:IDR_DSMULTTYPE]
Type=1
Class=CDSMultiPlayView
Command1=ID_FILE_OPEN
Command2=ID_FILE_CLOSE
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_EDIT_PLAY
Command6=ID_EDIT_STOP
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=ID_WINDOW_NEW
Command10=ID_WINDOW_CASCADE
Command11=ID_WINDOW_TILE_HORZ
Command12=ID_WINDOW_ARRANGE
Command13=ID_APP_ABOUT
CommandCount=13

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

[DLG:IDD_DSMULTIPLAY_FORM]
Type=1
Class=CDSMultiPlayView
ControlCount=6
Control1=IDC_PAN,msctls_trackbar32,1342242832
Control2=IDC_VOLUME,msctls_trackbar32,1342242818
Control3=IDC_FREQUENCY,msctls_trackbar32,1342242832
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

