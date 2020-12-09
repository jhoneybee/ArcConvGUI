!include "MUI.nsh"
!insertmacro MUI_LANGUAGE "SimpChinese"

Name "ArcConvGUI"
OutFile "ArcConvGUIInstall.exe"
InstallDir "$PROGRAMFILES\ArcConvGUI"	

Section
  SetOutPath "$INSTDIR\iconengines"
  File "iconengines\qsvgicon.dll"
  SetOutPath "$INSTDIR\imageformats"
  File "imageformats\qsvg.dll"
  SetOutPath "$INSTDIR\platforms"
  File "platforms\qwindows.dll"
  SetOutPath "$INSTDIR\styles"
  File "styles\qwindowsvistastyle.dll"
  SetOutPath $INSTDIR
  File "vccorlib140.dll"
  File "vcruntime140.dll"
  File "msvcp140.dll"
  File "msvcp140_1.dll"
  File "Qt5Core.dll"
  File "Qt5Gui.dll"
  File "Qt5Svg.dll"
  File "Qt5Widgets.dll"
  File "WolfDec.exe"
  File "ArcConvGUI.exe"
  WriteUninstaller "$INSTDIR\uninstaller.exe"
  Exec "$INSTDIR\ArcConvGUI.exe"
SectionEnd

Section "Uninstall"
  RMDir /r $INSTDIR
SectionEnd