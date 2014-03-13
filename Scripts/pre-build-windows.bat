@ECHO OFF
set PROJECT_DIR=%1
set REVISTION_T=%PROJECT_DIR%\..\..\..\..\Source\Core\CtrlrRevision.template
set REVISION_H=%PROJECT_DIR%\..\..\..\..\Source\Core\CtrlrRevision.h
set TERM=msys
set GIT="C:\Program Files (x86)\Git\bin\git.exe" "log" "-1"

%GIT% | find "commit" > REVISION
FOR /f "tokens=1,2,3,4 delims=/ " %%a in (REVISION) do (set revision=%%b)

echo #ifndef __CTRLR_REVISION__ > %REVISION_H%
echo #define __CTRLR_REVISION__ >> %REVISION_H%
echo /* Generated */ >> %REVISION_H%
echo static const char *ctrlrRevision              	= "%revision%"; >> %REVISION_H%
echo static const char *ctrlrRevisionBuildDate   	= "%date%"; >> %REVISION_H%
echo /* Generated */ >> %REVISION_H%
echo #endif >> %REVISION_H%
