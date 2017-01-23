; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CDSSimplyPlayDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DSSimplyPlay.h"

ClassCount=3
Class1=CDSSimplyPlayApp
Class2=CDSSimplyPlayDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DSSIMPLYPLAY_DIALOG
Resource4=IDR_MENU1

[CLS:CDSSimplyPlayApp]
Type=0
HeaderFile=DSSimplyPlay.h
ImplementationFile=DSSimplyPlay.cpp
Filter=N

[CLS:CDSSimplyPlayDlg]
Type=0
HeaderFile=DSSimplyPlayDlg.h
ImplementationFile=DSSimplyPlayDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_STOP

[CLS:CAboutDlg]
Type=0
HeaderFile=DSSimplyPlayDlg.h
ImplementationFile=DSSimplyPlayDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DSSIMPLYPLAY_DIALOG]
Type=1
Class=CDSSimplyPlayDlg
ControlCount=2
Control1=IDC_PLAY,button,1342242817
Control2=IDC_STOP,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=IDM_FILE_OPEN
Command2=IDM_FILE_CLOSE
CommandCount=2

