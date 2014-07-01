@ECHO OFF
set TERM=msys
set NSISDIR=C:\Program Files (x86)\NSIS
set GIT="C:\Program Files (x86)\Git\bin\git.exe" "describe" "--tags"

%GIT% > REVISION
FOR /f %%a in (REVISION) do (set revision=%%a)
echo Revision: %revision%

echo Create installer using nsis in: "%NSISDIR%\makensis.exe"
"%NSISDIR%\makensis.exe" installers/ctrlr.nsi /V4

echo "Copy output to ctrlr.org"
ren installers\Ctrlr.exe Ctrlr-%revision%.exe
pscp.exe -i private.ppk installers\Ctrlr-%revision%.exe ctrlrorg@ctrlr.org:/home/ctrlrorg/public_html/nightly/

echo "Update changelog and revisions"
plink.exe -v -i private.ppk ctrlrorg@ctrlr.org "nohup /home/ctrlrorg/crons/update_changelog.sh &"
plink.exe -v -i private.ppk ctrlrorg@ctrlr.org "nohup /home/ctrlrorg/crons/update_revisions.sh &"

del REVISION