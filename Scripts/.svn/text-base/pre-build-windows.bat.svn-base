echo "Start pre-build-windows.bat"
setlocal enabledelayedexpansion
set PROJECT_DIR=%1
set REVISTION_T=%PROJECT_DIR%\..\..\..\..\Source\Core\CtrlrRevision.template
set REVISION_H=%PROJECT_DIR%\..\..\..\..\Source\Core\CtrlrRevision.h

echo "Update revision numbers via TortoiseSVN"
"C:\Program Files\TortoiseSVN\bin\SubWCRev.exe" %PROJECT_DIR%\..\..\..\..\ %REVISTION_T% %REVISION_H%