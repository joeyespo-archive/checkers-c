# Microsoft Developer Studio Project File - Name="eThemes" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=eThemes - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "eThemes.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "eThemes.mak" CFG="eThemes - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "eThemes - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "eThemes - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "eThemes - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
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

!ELSEIF  "$(CFG)" == "eThemes - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
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
# ADD LIB32 /nologo /out:"Debug\eThemesD.lib"

!ENDIF 

# Begin Target

# Name "eThemes - Win32 Release"
# Name "eThemes - Win32 Debug"
# Begin Group "Entry Point"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Main.cpp
# End Source File
# Begin Source File

SOURCE=.\Main.h
# End Source File
# End Group
# Begin Group "Internal Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Private\ColorSchemes.h
# End Source File
# Begin Source File

SOURCE=.\Private\Schemes.h
# End Source File
# Begin Source File

SOURCE=.\Private\Themes.h
# End Source File
# Begin Source File

SOURCE=.\Private\UserSchemes.h
# End Source File
# End Group
# Begin Group "Internal Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Private\ColorSchemes.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Private\Schemes.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Private\Themes.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Private\UserSchemes.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h,hpp,hxx,h++"
# Begin Source File

SOURCE=.\Public\ColorFunctions.h
# End Source File
# Begin Source File

SOURCE=.\Public\eColorScheme.h
# End Source File
# Begin Source File

SOURCE=.\Public\eScheme.h
# End Source File
# Begin Source File

SOURCE=.\Public\eTheme.h
# End Source File
# Begin Source File

SOURCE=.\Public\eUserScheme.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "c,cpp,cxx,c++"
# Begin Source File

SOURCE=.\Public\ColorFunctions.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Public\eColorScheme.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Public\eScheme.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Public\eTheme.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Public\eUserScheme.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# End Target
# End Project
