; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CDSStreamView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DSStream.h"
LastPage=0

ClassCount=5
Class1=CDSStreamApp
Class2=CDSStreamDoc
Class3=CDSStreamView
Class4=CMainFrame

ResourceCount=2
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME

[CLS:CDSStreamApp]
Type=0
HeaderFile=DSStream.h
ImplementationFile=DSStream.cpp
Filter=N

[CLS:CDSStreamDoc]
Type=0
HeaderFile=DSStreamDoc.h
ImplementationFile=DSStreamDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_EDIT_STOP

[CLS:CDSStreamView]
Type=0
HeaderFile=DSStreamView.h
ImplementationFile=DSStreamView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CDSStreamView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=DSStream.cpp
ImplementationFile=DSStream.cpp
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
Command1=ID_FILE_MRU_FILE1
Command2=ID_APP_EXIT
Command3=ID_EDIT_PLAY
Command4=ID_EDIT_STOP
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

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
Command1=ID_EDIT_PLAY
Command2=ID_EDIT_STOP
CommandCount=2

