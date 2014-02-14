!define MUI_PRODUCT "Ctrlr MIDI Editor"
!define MUI_FILE "savefile"
!define MUI_BRANDINGTEXT "Ctrlr v5.0"
# REFS
!define REG_UNINSTALL "Software\Microsoft\Windows\CurrentVersion\Uninstall\Ctrlr"
!define START_LINK_DIR "$STARTMENU\Programs\Ctrlr"
!define START_LINK_RUN "$STARTMENU\Programs\Ctrlr\Ctrlr.lnk"
!define START_LINK_UNINSTALLER "$STARTMENU\Programs\OnTopReplica\Uninstall Ctrlr.lnk"
!define UNINSTALLER_NAME "Ctrlr-Uninstall.exe"
!define WEBSITE_LINK "http://ctrlr.org"

CRCCheck On
SetCompressor /SOLID lzma
Name "Ctrlr MIDI Editor"
OutFile "Ctrlr.exe"
RequestExecutionLevel user

!include MUI2.nsh
!include Sections.nsh
!include "x64.nsh"
 
##===========================================================================
## Modern UI Pages
##===========================================================================
!define MUI_ICON 			"..\..\Scripts\Installers\icon.ico"
!define MUI_UNICON 			"..\..\Scripts\Installers\icon.ico"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "ctrlr_header.bmp" ; optional
!define MUI_ABORTWARNING
 
!define MUI_PAGE_CUSTOMFUNCTION_PRE SelectFilesCheck
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE ComponentsLeave
!insertmacro MUI_PAGE_COMPONENTS
 
## This is the title on the first Directory page
!define MUI_DIRECTORYPAGE_TEXT_TOP "$(MUI_DIRECTORYPAGE_TEXT_TOP_A)"
 
!define MUI_PAGE_CUSTOMFUNCTION_PRE SelectFilesA
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
 
## This is the title on the second Directory page
!define MUI_DIRECTORYPAGE_TEXT_TOP "$(MUI_DIRECTORYPAGE_TEXT_TOP_B)"
 
!define MUI_PAGE_CUSTOMFUNCTION_PRE SelectFilesB
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
 
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!define MUI_PAGE_CUSTOMFUNCTION_LEAVE DeleteSectionsINI
!insertmacro MUI_PAGE_FINISH
  
!insertmacro MUI_LANGUAGE "English"
 
##===========================================================================
## Language strings
##===========================================================================
 
LangString NoSectionsSelected ${LANG_ENGLSH} "You haven't selected any sections!"
LangString MUI_DIRECTORYPAGE_TEXT_TOP_A ${LANG_ENGLSH} "Setup will install Ctrlr Standalone files in the following folder..."
LangString MUI_DIRECTORYPAGE_TEXT_TOP_B ${LANG_ENGLSH} "Setup will install Ctrlr VST Files in the following folder..."
 
# CALLBACKS
Function RegisterApplication
    ;Register uninstaller into Add/Remove panel (for local user only)
    WriteRegStr HKCU "${REG_UNINSTALL}" "DisplayName" "Ctrlr"
    WriteRegStr HKCU "${REG_UNINSTALL}" "DisplayIcon" "$\"$INSTDIR\Ctrlr.exe$\""
    WriteRegStr HKCU "${REG_UNINSTALL}" "Publisher" "Instigator"
    WriteRegStr HKCU "${REG_UNINSTALL}" "DisplayVersion" "5.1.2"
    WriteRegDWord HKCU "${REG_UNINSTALL}" "EstimatedSize" 20480 ;KB
    WriteRegStr HKCU "${REG_UNINSTALL}" "HelpLink" "${WEBSITE_LINK}"
    WriteRegStr HKCU "${REG_UNINSTALL}" "URLInfoAbout" "${WEBSITE_LINK}"
    WriteRegStr HKCU "${REG_UNINSTALL}" "InstallLocation" "$\"$INSTDIR$\""
    WriteRegStr HKCU "${REG_UNINSTALL}" "InstallSource" "$\"$EXEDIR$\""
    WriteRegDWord HKCU "${REG_UNINSTALL}" "NoModify" 1
    WriteRegDWord HKCU "${REG_UNINSTALL}" "NoRepair" 1
    WriteRegStr HKCU "${REG_UNINSTALL}" "UninstallString" "$\"$INSTDIR\Uninstall.exe$\""
    WriteRegStr HKCU "${REG_UNINSTALL}" "Comments" "Uninstalls Ctrlr."
    
    ;Links
    SetShellVarContext current
    CreateDirectory "${START_LINK_DIR}"
    CreateShortCut "${START_LINK_RUN}" "$INSTDIR\Ctrlr-Win32.exe"
    CreateShortCut "${START_LINK_UNINSTALLER}" "$INSTDIR\Uninstall.exe"
FunctionEnd

Function un.DeregisterApplication
    ;Deregister uninstaller from Add/Remove panel
    DeleteRegKey HKCU "${REG_UNINSTALL}"
    
    ;Start menu links
    SetShellVarContext current
    RMDir /r "${START_LINK_DIR}"
FunctionEnd

##===========================================================================
## Start sections
##===========================================================================
 
## Sections Group 1
SectionGroup /e "Standalone" PROG1

	Section "32bit binary" SEC1
		SetOutPath 	"$INSTDIR"
		File			"..\..\Bin\Ctrlr-Win32.exe"
		WriteUninstaller	"$INSTDIR\Uninstall.exe"
		Call RegisterApplication
	SectionEnd
	
	Section "64bit binary" SEC2
		SetOutPath 	"$INSTDIR"
		File			"..\..\Bin\Ctrlr-x64.exe"
		WriteUninstaller	"$INSTDIR\Uninstall.exe"
		Call RegisterApplication
	SectionEnd
 
	Section "Docs and examples" SEC3
		SetOutPath 	"$INSTDIR"
		File			/r "..\..\Doc"
		File			/r "..\..\Panels"
		WriteUninstaller 	"$INSTDIR\Uninstall.exe"
	SectionEnd
  
	Section "Desktop shortcut" SEC4
		${If} ${RunningX64}
			CreateShortCut 	"$DESKTOP\Ctrlr.lnk" 				"$INSTDIR\Ctrlr-x64.exe" ""
		${Else}
			CreateShortCut 	"$DESKTOP\Ctrlr.lnk" 				"$INSTDIR\Ctrlr-Win32.exe" ""
		${EndIf}
	SectionEnd
		
SectionGroupEnd
 
SectionGroup /e "VST" PROG2

	Section "Executables Win32" SEC5
		SetOutPath 	"$INSTDIR"
		File			"..\..\Bin\Ctrlr-VST-Win32.dll"		
	SectionEnd
	
	Section "Executables x64" SEC6
		SetOutPath 	"$INSTDIR"
		File			"..\..\Bin\Ctrlr-VST-x64.dll"
	SectionEnd
	
SectionGroupEnd
 
Section "Uninstall"
	;Remove whole directory (no data is stored there anyway)
	RMDir /r "$INSTDIR"
    
	;Remove uninstaller
	Call un.DeregisterApplication
SectionEnd

##===========================================================================
## Settings
##===========================================================================
 
!define PROG1_InstDir    	"$PROGRAMFILES\Ctrlr"
!define PROG1_StartIndex 	${PROG1}
!define PROG1_EndIndex   	${SEC4}
 
!define PROG2_InstDir 		"$PROGRAMFILES\VstPlugins"
!define PROG2_StartIndex 	${PROG2}
!define PROG2_EndIndex   	${SEC6}
 
##===========================================================================
## Please don't modify below here unless you're a NSIS 'wiz-kid'
##===========================================================================
 
## Create $PLUGINSDIR
Function .onInit
	InitPluginsDir
FunctionEnd
 
## If user goes back to this page from 1st Directory page
## we need to put the sections back to how they were before
Var IfBack

Function SelectFilesCheck
	StrCmp $IfBack 1 0 NoCheck
	Call ResetFiles
	NoCheck:
FunctionEnd
 
## Also if no sections are selected, warn the user!
Function ComponentsLeave
	Push $R0
	Push $R1
 
	Call IsPROG1Selected
	Pop $R0
	Call IsPROG2Selected
	Pop $R1
	StrCmp $R0 1 End
	StrCmp $R1 1 End
	Pop $R1
	Pop $R0
	MessageBox MB_OK|MB_ICONEXCLAMATION "$(NoSectionsSelected)"
	Abort
	End:
	Pop $R1
	Pop $R0
FunctionEnd
 
Function IsPROG1Selected
	Push $R0
	Push $R1

	StrCpy $R0 ${PROG1_StartIndex} # Group 1 start
 
	Loop:
		IntOp $R0 $R0 + 1
		SectionGetFlags $R0 $R1			# Get section flags
		IntOp $R1 $R1 & ${SF_SELECTED}
		StrCmp $R1 ${SF_SELECTED} 0 +3		# If section is selected, done
		StrCpy $R0 1
		Goto Done
		StrCmp $R0 ${PROG1_EndIndex} 0 Loop
 
	Done:
	Pop $R1
	Exch $R0
	FunctionEnd
 
Function IsPROG2Selected
	Push $R0
	Push $R1
 
	StrCpy $R0 ${PROG2_StartIndex}    # Group 2 start
 
	Loop:
		IntOp $R0 $R0 + 1
		SectionGetFlags $R0 $R1			# Get section flags
		IntOp $R1 $R1 & ${SF_SELECTED}
		StrCmp $R1 ${SF_SELECTED} 0 +3		# If section is selected, done
		StrCpy $R0 1
		Goto Done
		StrCmp $R0 ${PROG2_EndIndex} 0 Loop
 
	Done:
	Pop $R1
	Exch $R0
FunctionEnd
 
## Here we are selecting first sections to install
## by unselecting all the others!
Function SelectFilesA
 
	# If user clicks Back now, we will know to reselect Group 2's sections for
	# Components page
	StrCpy $IfBack 1
 
	# We need to save the state of the Group 2 Sections
	# for the next InstFiles page
	Push $R0
	Push $R1
 
	StrCpy $R0 ${PROG2_StartIndex} # Group 2 start
 
	Loop:
		IntOp $R0 $R0 + 1
		SectionGetFlags $R0 $R1				    # Get section flags
		WriteINIStr "$PLUGINSDIR\sections.ini" Sections $R0 $R1 # Save state
		!insertmacro UnselectSection $R0			    # Then unselect it
		StrCmp $R0 ${PROG2_EndIndex} 0 Loop
 
		# Don't install prog 1?
		Call IsPROG1Selected
		Pop $R0
		StrCmp $R0 1 +4
		Pop $R1
		Pop $R0
	Abort
 
	# Set current $INSTDIR to PROG1_InstDir define
	StrCpy $INSTDIR "${PROG1_InstDir}"
 
	Pop $R1
	Pop $R0
FunctionEnd
 
## Here we need to unselect all Group 1 sections
## and then re-select those in Group 2 (that the user had selected on
## Components page)
Function SelectFilesB
	Push $R0
	Push $R1
 
	StrCpy $R0 ${PROG1_StartIndex}    # Group 1 start
 
	Loop:
		IntOp $R0 $R0 + 1
		!insertmacro UnselectSection $R0		# Unselect it
		StrCmp $R0 ${PROG1_EndIndex} 0 Loop
 
		Call ResetFiles
 
		# Don't install prog 2?
		Call IsPROG2Selected
		Pop $R0
		StrCmp $R0 1 +4
		Pop $R1
		Pop $R0
		Abort
 
		# Set current $INSTDIR to PROG2_InstDir define
		StrCpy $INSTDIR "${PROG2_InstDir}"
 
		Pop $R1
		Pop $R0
FunctionEnd
 
## This will set all sections to how they were on the components page
## originally
Function ResetFiles
	Push $R0
	Push $R1
	StrCpy $R0 ${PROG2_StartIndex}    # Group 2 start
 
	Loop:
		IntOp $R0 $R0 + 1
		ReadINIStr "$R1" "$PLUGINSDIR\sections.ini" Sections $R0 # Get sec flags
		SectionSetFlags $R0 $R1				  # Re-set flags for this sec
		StrCmp $R0 ${PROG2_EndIndex} 0 Loop
 
		Pop $R1
		Pop $R0
FunctionEnd
 
## Here we are deleting the temp INI file at the end of installation
Function DeleteSectionsINI
	FlushINI "$PLUGINSDIR\Sections.ini"
	Delete "$PLUGINSDIR\Sections.ini"
FunctionEnd