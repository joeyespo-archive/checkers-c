# Microsoft Developer Studio Project File - Name="Checkers" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Checkers - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Checkers.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Checkers.mak" CFG="Checkers - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Checkers - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Checkers - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Checkers - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Checkers - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Checkers - Win32 Release"
# Name "Checkers - Win32 Debug"
# Begin Group "Entry Point"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Main.cpp
# End Source File
# Begin Source File

SOURCE=.\Main.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h,hpp,h++,hxx"
# Begin Source File

SOURCE=..\..\Include\eCheckers.h
# End Source File
# Begin Source File

SOURCE=..\..\Include\eCkWindow.h
# End Source File
# Begin Source File

SOURCE=.\frmAbout.h
# End Source File
# Begin Source File

SOURCE=.\frmGame.h
# End Source File
# Begin Source File

SOURCE=.\frmMain.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "c,cpp,c++,cxx"
# Begin Source File

SOURCE=.\frmAbout.cpp
# End Source File
# Begin Source File

SOURCE=.\frmGame.cpp
# End Source File
# Begin Source File

SOURCE=.\frmMain.cpp
# End Source File
# Begin Source File

SOURCE=.\Libraries.cpp
# End Source File
# End Group
# Begin Group "Checkers Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Include\eCheckers\eCkGame.h
# End Source File
# Begin Source File

SOURCE=..\..\Include\eCkWindow\eCkWindow.h
# End Source File
# End Group
# Begin Group "Checkers Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Include\eCheckers\eCkGame.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\Include\eCkWindow\eCkWindow.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc"
# Begin Group "Resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Res\Main.rc
# End Source File
# Begin Source File

SOURCE=.\Res\resource.h
# End Source File
# End Group
# Begin Group "Resource Data"

# PROP Default_Filter "ico,cur,bmp"
# Begin Source File

SOURCE=".\Res\Graphics\Menu\1Player (Highlight).ico"
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\1Player.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Menu\1Player.ico
# End Source File
# Begin Source File

SOURCE=".\Res\Graphics\Menu\2Player (Highlight).ico"
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Menu\2Player.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Pieces\Black.cur
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Pieces\Black.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Pieces\Black_King.cur
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Pieces\Black_King.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Checkers.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Pieces\Gold.cur
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Pieces\Gold_King.cur
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Icon.ico
# End Source File
# Begin Source File

SOURCE=".\Res\Graphics\King (Black).ico"
# End Source File
# Begin Source File

SOURCE=".\Res\Graphics\Pieces\King (Black).ico"
# End Source File
# Begin Source File

SOURCE=".\Res\Graphics\King (Red).ico"
# End Source File
# Begin Source File

SOURCE=".\Res\Graphics\Pieces\King (Red).ico"
# End Source File
# Begin Source File

SOURCE=".\Res\Graphics\Logo (Big).ico"
# End Source File
# Begin Source File

SOURCE=".\Res\Graphics\Logo (Small).ico"
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Logos\Logo.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Logo.ico
# End Source File
# Begin Source File

SOURCE=".\Res\Graphics\Menu\Online (Highlight).ico"
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Menu\Online.ico
# End Source File
# Begin Source File

SOURCE=".\Res\Graphics\Pawn (Black).ico"
# End Source File
# Begin Source File

SOURCE=".\Res\Graphics\Pieces\Pawn (Black).ico"
# End Source File
# Begin Source File

SOURCE=".\Res\Graphics\Pawn (Red).ico"
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Pieces\Red.cur
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Pieces\Red.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Pieces\Red_King.cur
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\Pieces\Red_King.ico
# End Source File
# Begin Source File

SOURCE=.\Res\Graphics\SinglePlayer.ico
# End Source File
# End Group
# End Group
# End Target
# End Project
