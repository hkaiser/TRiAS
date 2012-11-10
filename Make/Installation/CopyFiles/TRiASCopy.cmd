@echo off
echo Kopieren der TRiAS Dateien in die Setup Verzeichnisse

SET LANG=NOTHING
if "ENU" == "%1%" SET LANG=0x0409
if "GER" == "%1%" SET LANG=0x0407
if "NOTHING" == "%LANG%" goto :usage

set quelle="d:\trias\trias\v_4_0_0\%LANG%\"
set cs_quelle="d:\triasdev.mvc\triascs\res\"
set tcf_quelle="d:\triasdev.mvc\triascfg\res\"

echo
echo SPRACHVERSION    : %LANG%
echo QUELLVERZEICHNIS : %quelle%
echo

set ziel1="d:\setups\trias_v4_0\release\beispieldateien\Demoprojekt\"
set ziel2="d:\setups\trias_v4_0\release\exportmodule\"
set ziel3="d:\setups\trias_v4_0\release\hilfedateien\"
set ziel4="d:\setups\trias_v4_0\release\importmodule\"
set ziel5="d:\setups\trias_v4_0\release\koordinaten\"
set ziel6="d:\setups\trias_v4_0\release\programmdateien\" 
set ziel7="d:\setups\trias_v4_0\release\visualisierung\"
set ziel8="d:\setups\trias_v4_0\release\trias-basic\"
set ziel9="d:\setups\trias_v4_0\release\zusatzmodule\"
set ziel10="d:\setups\trias_v4_0\release\programmdateien\Rasterkarten\" 
set ziel11="d:\setups\trias_v4_0\release\programmdateien\MapMgr\" 
set ziel12="d:\setups\trias_v4_0\release\koordinatensysteme\"
set ziel13="d:\setups\trias_v4_0\release\LoadableCommands\"

echo Systemdateien
rem xcopy /F /E d:\trias\trias\System\*.dll d:\setups\trias_v4_0\release\system\
rem xcopy /F /E d:\trias\trias\runtime\*.* d:\setups\trias_v4_0\runtime\  

echo Beispieldateien
xcopy /F /E d:\trias\beispieldateien\Demoprojekt\*.* %ziel1%

echo Exportmodule
xcopy /F /E %quelle%export.ext %ziel2%
xcopy /F /E %quelle%acaddxf.flt %ziel2%
xcopy /F /E %quelle%atlasbna.flt %ziel2%
xcopy /F /E %quelle%dirisasc.flt %ziel2%
xcopy /F /E %quelle%triasarc.flt %ziel2%
xcopy /F /E %quelle%arcview.flt %ziel2%
xcopy /F /E %quelle%polygispmf.flt %ziel2%
xcopy /F /E %quelle%polygisdat.flt %ziel2%

echo Hilfedateien
xcopy /F /E %quelle%TRiAS.hlp %ziel3%
xcopy /F /E %quelle%TRiAS.cnt %ziel3%

echo Importmodule
xcopy /F /E %quelle%edbsimp.ext %ziel4%
xcopy /F /E %quelle%edbsalk.ext %ziel4%
xcopy /F /E %quelle%dxfimp.ext %ziel4%
xcopy /F /E %quelle%ascimp.ext %ziel4%
xcopy /F /E %quelle%arctrias.ext %ziel4%
xcopy /F /E %quelle%bnaimp.ext %ziel4%

echo Koordinaten
xcopy /F /E %quelle%Geodctfs.css %ziel5%
xcopy /F /E %quelle%Gkctfs.css %ziel5%

echo Programmdateien
xcopy /F /E %quelle%colors.ebn %ziel6%
xcopy /F /E %quelle%containr.dll %ziel6%
xcopy /F /E %quelle%defctfs.css %ziel6%
xcopy /F /E %quelle%fakemfc.ext %ziel6%
xcopy /F /E %quelle%geoedit.ext %ziel6%
xcopy /F /E %quelle%geometr.dll %ziel6%
xcopy /F /E %quelle%georein.ext %ziel6%
xcopy /F /E %quelle%helper.dll %ziel6%
xcopy /F /E %quelle%identsdb.ext %ziel6%
xcopy /F /E %quelle%lol.dll %ziel6%
xcopy /F /E %quelle%muscrl32.dll %ziel6%
xcopy /F /E %quelle%objman.dll %ziel6%
xcopy /F /E %quelle%ospace.dll %ziel6%
rem xcopy /F /E %quelle%mvc60as.dll %ziel6%
rem xcopy /F /E %quelle%osc60as.dll %ziel6%
rem xcopy /F /E %quelle%otp60as.dll %ziel6%
xcopy /F /E %quelle%otp701as.dll %ziel6%
xcopy /F /E %quelle%sfl103as.dll %ziel6%
xcopy /F /E %quelle%tdbgeo.dll %ziel6%
xcopy /F /E %quelle%terrtrk.dll %ziel6%
xcopy /F /E %quelle%tfrmwork.dll %ziel6%
xcopy /F /E %quelle%trias321.dll %ziel6%
xcopy /F /E %quelle%trias322.dll %ziel6%
xcopy /F /E %quelle%trias32.exe %ziel6%
xcopy /F /E %quelle%unregtrias.exe %ziel6%
xcopy /F /E %quelle%trias.tip %ziel6%
xcopy /F /E %quelle%trias323.dll %ziel6%
xcopy /F /E %quelle%triascs.dll %ziel6%
xcopy /F /E %quelle%triasdb.dll %ziel6%
xcopy /F /E %quelle%triashp.dll %ziel6%
rem xcopy /F /E %quelle%triasgdo.dll %ziel6%
xcopy /F /E %quelle%triashp.dll %ziel6%
xcopy /F /E %quelle%triasicn.dll %ziel6%
xcopy /F /E %quelle%triasmds.dll %ziel6%
xcopy /F /E %quelle%triasui.dll %ziel6%
xcopy /F /E %quelle%visobj.ext %ziel6%
xcopy /F /E %quelle%triascfg.dll %ziel6%
xcopy /F /E %quelle%triasmi.dll %ziel6%
xcopy /F /E %quelle%loadablecommands.ext %ziel6%

echo Visualisierung
xcopy /F /E %quelle%Linesig.vmd %ziel7%
xcopy /F /E %quelle%torten.vmd %ziel7%
xcopy /F /E %quelle%txtrotl.vmd %ziel7%

echo Zusatzmodule
xcopy /F /E %quelle%abstand.ext %ziel9%
xcopy /F /E %quelle%bilder.ext %ziel9%
xcopy /F /E %quelle%buffer.ext %ziel9%
xcopy /F /E %quelle%geostat.ext %ziel9%
xcopy /F /E %quelle%gitter.ext %ziel9%
xcopy /F /E %quelle%maschblr.ext %ziel9%
xcopy /F /E %quelle%objoper.ext %ziel9%
xcopy /F /E %quelle%odbcext.ext %ziel9%
xcopy /F /E %quelle%toporel.ext %ziel9%
xcopy /F /E %quelle%triasigm.ext %ziel9%
xcopy /F /E %quelle%tproject.ext %ziel9%
xcopy /F /E %quelle%trsabis.ext %ziel9%
xcopy /F /E %quelle%linetools.ext %ziel9%
xcopy /F /E %quelle%statist.ext %ziel9%

echo Trias-basic
xcopy /F /E %quelle%bscript.ext %ziel8%
xcopy /F /E %quelle%daolayer.ebn %ziel8%
xcopy /F /E %quelle%oleauto.ext %ziel8%
xcopy /F /E %quelle%sumncm22.dll %ziel8%
xcopy /F /E %quelle%sumncx22.dll %ziel8%
xcopy /F /E %quelle%sumndc22.dll %ziel8%
xcopy /F /E %quelle%sumndd22.dll %ziel8%
xcopy /F /E %quelle%sumndg22.dll %ziel8%
xcopy /F /E %quelle%sumnol22.dll %ziel8%
xcopy /F /E %quelle%sumnpb22.dll %ziel8%
xcopy /F /E %quelle%sumnrn22.dll %ziel8%

echo Rasterkarten
xcopy /F /E %quelle%karten.vmd %ziel10%
xcopy /F /E %quelle%lmfcx42.dll %ziel10%
xcopy /F /E %quelle%lpict42.dll %ziel10%

echo MapMgr
xcopy /F /E %quelle%lfcmp13n.dll %ziel11%
xcopy /F /E %quelle%lftif13n.dll %ziel11%
xcopy /F /E %quelle%lffax13n.dll %ziel11%
xcopy /F /E %quelle%lfbmp13n.dll %ziel11%
xcopy /F /E %quelle%ltclr13n.dll %ziel11%
xcopy /F /E %quelle%ltdis13n.dll %ziel11%
xcopy /F /E %quelle%ltfil13n.dll %ziel11%
xcopy /F /E %quelle%ltimg13n.dll %ziel11%
xcopy /F /E %quelle%ltefx13n.dll %ziel11%
xcopy /F /E %quelle%ltkrn13n.dll %ziel11%
xcopy /F /E %quelle%ltwvc13n.dll %ziel11%
xcopy /F /E %quelle%mapmgr.ext %ziel11%
xcopy /F /E %quelle%mmarcinf.dll %ziel11%
xcopy /F /E %quelle%mmgeopunktdlk.dll %ziel11%
xcopy /F /E %quelle%mmpolygis.dll %ziel11%

echo Koordinatensysteme
xcopy /f /e %cs_quelle%*.tcf %ziel12%

echo Loadable Commands
copy /y %tcf_quelle%AreasToLines.xml "%ziel13%Fl„chen zu Linien umwandeln.tlc"
copy /y %tcf_quelle%LinesToAreas.xml "%ziel13%Linien zu Fl„chen umwandeln.tlc"

rem echo Lizenzierung
rem xcopy /F /E %quelle%trias.lic %ziel6%

goto :end_of_script

:usage
echo Aufruf: TRiASCopy LANGUAGE
echo         wobei Language [ENU,GER] sein kann.

:end_of_script
