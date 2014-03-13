@ECHO OFF
set TERM=msys
set NSISDIR=C:\Program Files (x86)\NSIS
set GIT="C:\Program Files (x86)\Git\bin\git.exe" "log" "-1"

%GIT% | find "commit" > REVISION
FOR /f "tokens=1,2,3,4 delims=/ " %%a in (REVISION) do (set revision=%%b)

echo Revision: %revision%

echo Create installer using nsis in: "%NSISDIR%\makensis.exe"
"%NSISDIR%\makensis.exe" installers/ctrlr.nsi /V4

echo "Copy output to ctrlr.org"
ren installers\Ctrlr.exe Ctrlr_%revision%.exe
pscp.exe -i private.ppk installers\Ctrlr_%revision%.exe ctrlrorg@ctrlr.org:/home/ctrlrorg/public_html/nightly/

echo "Update changelog and revisions"
plink.exe -v -i private.ppk ctrlrorg@ctrlr.org "nohup /home/ctrlrorg/crons/update_changelog.sh &"
plink.exe -v -i private.ppk ctrlrorg@ctrlr.org "nohup /home/ctrlrorg/crons/update_revisions.sh &"

del REVISION