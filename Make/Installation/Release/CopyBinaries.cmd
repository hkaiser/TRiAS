@echo off
rem Kopieren der erzeugten binaries ins CD Image ...
rem
echo Kopieren der TRiAS Installationen ...
xcopy /F TRiAS51.exe "%1\TRiAS51\TRiAS51\"
rem
echo Kopieren der ArcView Shape Installationen ...
xcopy /F ArcView_Shape.exe "%1\Datenserver"
rem
echo Kopieren der ATKIS Installationen ...
xcopy /F EDBS_Atkis.exe "%1\EDBS-ATKIS\"
rem 
echo Kopieren der ALK Installationen ...
xcopy /F EDBS_ALK_Sachsen-Anhalt_(LVermA).exe "%1\EDBS-Alk\"
xcopy /F EDBS_ALK_ALK_SABIS.exe  "%1\EDBS-Alk\"
xcopy /F EDBS_ALK_Schleswig-Holstein.exe  "%1\EDBS-Alk\"
xcopy /F EDBS_ALK_Sachsen-Anhalt.exe "%1\EDBS-Alk\"
xcopy /F EDBS_ALK_Nordrhein-Westfalen.exe "%1\EDBS-Alk\"
xcopy /F EDBS_ALK_Mecklenburg-Vorpommern.exe "%1\EDBS-Alk\"
xcopy /F EDBS_ALK_Hessen.exe "%1\EDBS-Alk\"
xcopy /F EDBS_ALK_Brandenburg.exe "%1\EDBS-Alk\"
xcopy /F EDBS_ALK_Berlin.exe "%1\EDBS-Alk\"
rem 
echo Kopieren der zus„tzlichen Erweiterungen
xcopy /F "..\Zusatzmodule\triasigm.ext" "%1\IGM\"
xcopy /F "..\Zusatzmodule\trsabis.ext" "%1\SABiS\"
xcopy /F "..\Zusatzmodule\linetools.ext" "%1\AddOns\"
xcopy /F "..\Zusatzmodule\statist.ext" "%1\AddOns\"
xcopy /F "..\Programmdateien\triasmi.dll" "%1\AddOns\"
rem
echo Kopieren der AutoUpdate Installation
xcopy /F AutoUpdate.exe "%1\..\AutoUpdate\"

