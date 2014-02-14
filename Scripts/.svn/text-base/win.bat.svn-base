@ECHO OFF
set NSISDIR=C:\Program Files (x86)\NSIS
set TEXT_T="REVISION"
"C:\Program Files\TortoiseSVN\bin\SubWCRev.exe" ..\ REVISION.t REVISION
for /f "eol= tokens=* delims= usebackq" %%i in (%TEXT_T%) do (

echo "Creating build revision: %%i"

echo Create installer using nsis in: "%NSISDIR%\makensis.exe"
"%NSISDIR%\makensis.exe" installers/ctrlr.nsi /V4

echo "Copy output to ctrlr.org"
ren installers\Ctrlr.exe Ctrlr_%%i.exe
pscp.exe -i private.ppk installers\Ctrlr_%%i.exe ctrlrorg@ctrlr.org:/home/ctrlrorg/public_html/nightly/

echo "Update changelog and revisions"
plink.exe -v -i private.ppk ctrlrorg@ctrlr.org "nohup /home/ctrlrorg/crons/update_changelog.sh &"
plink.exe -v -i private.ppk ctrlrorg@ctrlr.org "nohup /home/ctrlrorg/crons/update_revisions.sh &"
)