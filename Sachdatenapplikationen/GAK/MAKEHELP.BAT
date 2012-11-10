REM @echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by GAK.HPJ. >"hlp\gak.hm"
echo. >>"hlp\gak.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\gak.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\gak.hm"
echo. >>"hlp\gak.hm"
echo // Prompts (IDP_*) >>"hlp\gak.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\gak.hm"
echo. >>"hlp\gak.hm"
echo // Resources (IDR_*) >>"hlp\gak.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\gak.hm"
echo. >>"hlp\gak.hm"
echo // Dialogs (IDD_*) >>"hlp\gak.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\gak.hm"
echo. >>"hlp\gak.hm"
echo // Frame Controls (IDW_*) >>"hlp\gak.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\gak.hm"
REM -- Make help for Project GAK


echo Building Win32 Help files
start /wait hcrtf -x "hlp\gak.hpj"
echo.
if exist Debug\nul copy "hlp\gak.hlp" Debug
if exist Debug\nul copy "hlp\gak.cnt" Debug
if exist Release\nul copy "hlp\gak.hlp" Release
if exist Release\nul copy "hlp\gak.cnt" Release
echo.


