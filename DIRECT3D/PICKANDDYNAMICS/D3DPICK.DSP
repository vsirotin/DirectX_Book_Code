# Microsoft Developer Studio Project File - Name="d3dPick" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=d3dPick - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "d3dPick.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "d3dPick.mak" CFG="d3dPick - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "d3dPick - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "d3dPick - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "d3dPick - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\dxCommon" /I ".\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 d3drm.lib ddraw.lib dxguid.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "d3dPick - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\dxCommon" /I ".\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 d3drm.lib ddraw.lib dxguid.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "d3dPick - Win32 Release"
# Name "d3dPick - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\dxCommon\d3dAnimation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dCameraFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dConeFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dCubeFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dCylinderFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dDecalFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dDirectionalLight.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dDiskFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dFlowerApp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dGeomArsenal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dHalfsphereFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dLightFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dMainObj.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dMaterial.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dParallelPointLight.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dPick.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dPick.rc
# End Source File
# Begin Source File

SOURCE=.\d3dPickDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dPickObj.cpp
# End Source File
# Begin Source File

SOURCE=.\d3dPickView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dPointLight.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dPolygonFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dPyramidFrame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dSpotLight.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dTexture.cpp
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\ddMainObj.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\dxCommon\d3dAnimation.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dCameraFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dConeFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dCubeFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dCylinderFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dDecalFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dDirectionalLight.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dDiskFrame.h
# End Source File
# Begin Source File

SOURCE=.\d3dFlowerApp.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dGeomArsenal.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dHalfsphereFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dLightFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dMainObj.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dMaterial.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dParallelPointLight.h
# End Source File
# Begin Source File

SOURCE=.\d3dPick.h
# End Source File
# Begin Source File

SOURCE=.\d3dPickDoc.h
# End Source File
# Begin Source File

SOURCE=.\d3dPickObj.h
# End Source File
# Begin Source File

SOURCE=.\d3dPickView.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dPointLight.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dPolygonFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dPyramidFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dSpotLight.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\d3dTexture.h
# End Source File
# Begin Source File

SOURCE=..\..\dxCommon\ddMainObj.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\d3dPick.ico
# End Source File
# Begin Source File

SOURCE=.\res\d3dPick.rc2
# End Source File
# Begin Source File

SOURCE=.\res\d3dPickDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
