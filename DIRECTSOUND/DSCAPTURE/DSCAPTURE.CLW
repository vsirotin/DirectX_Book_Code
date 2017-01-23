; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CDSCaptureDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DSCapture.h"

ClassCount=3
Class1=CDSCaptureApp
Class2=CDSCaptureDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DSCAPTURE_DIALOG

[CLS:CDSCaptureApp]
Type=0
HeaderFile=DSCapture.h
ImplementationFile=DSCapture.cpp
Filter=N

[CLS:CDSCaptureDlg]
Type=0
HeaderFile=DSCaptureDlg.h
ImplementationFile=DSCaptureDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_STOP

[CLS:CAboutDlg]
Type=0
HeaderFile=DSCaptureDlg.h
ImplementationFile=DSCaptureDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DSCAPTURE_DIALOG]
Type=1
Class=CDSCaptureDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDC_FILEOPEN,button,1342242816
Control3=IDC_ORIGINAL,button,1342308361
Control4=IDC_PLAY_AND_CAPTURE,button,1342177289
Control5=IDC_ONLY_CAPTURE,button,1342177289
Control6=IDC_PLAY_CAPTURED_RES,button,1342177289
Control7=IDC_RADIO5,button,1342177289
Control8=IDC_START,button,1342373888
Control9=IDC_STOP,button,1342242816
Control10=IDC_FILE,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287

