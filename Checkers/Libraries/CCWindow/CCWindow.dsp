# Microsoft Developer Studio Project File - Name="CCWindow" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CCWindow - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CCWindow.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CCWindow.mak" CFG="CCWindow - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CCWindow - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "CCWindow - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CCWindow - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CCWindow___Win32_Release"
# PROP BASE Intermediate_Dir "CCWindow___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "CCWindow - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CCWindow___Win32_Debug"
# PROP BASE Intermediate_Dir "CCWindow___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\CCWindowD.lib"

!ENDIF 

# Begin Target

# Name "CCWindow - Win32 Release"
# Name "CCWindow - Win32 Debug"
# Begin Group "Entry Point"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Main.cpp
# End Source File
# Begin Source File

SOURCE=.\Main.h
# End Source File
# End Group
# Begin Group "Private Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Private\CCCProc.h
# End Source File
# Begin Source File

SOURCE=.\Private\CCFProc.h
# End Source File
# Begin Source File

SOURCE=.\Private\CCWnd.h
# End Source File
# End Group
# Begin Group "Private Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Private\CCCProc.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Private\CCFProc.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Private\CCWnd.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h,hpp,hxx,h++"
# Begin Source File

SOURCE=.\Public\CCClient.h
# End Source File
# Begin Source File

SOURCE=.\Public\CCFrame.h
# End Source File
# Begin Source File

SOURCE=.\Public\CCWindow.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "c,cpp,cxx,c++"
# Begin Source File

SOURCE=.\Public\CCClient.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Public\CCFrame.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Public\CCWindow.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Library Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\CCWindow.h
# End Source File
# End Group
# End Target
# End Project
