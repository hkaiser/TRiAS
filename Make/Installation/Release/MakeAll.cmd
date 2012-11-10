@echo off
rem Erzeugen aller Installationen
rem
rem Pfad des Installationsgenerators
set INSTALL_CMD="C:\Programme\Wise Installmaster 8.1\wise32.exe"
rem
echo Erzeugen der TRiAS Installationen ...
rem echo TRiAS Analyse ...
rem %INSTALL_CMD% /c /s ".\InterTRiAS_Analyse.wse"
echo TRiAS Plus ...
%INSTALL_CMD% /c /s ".\TRiAS51.wse"
rem echo TRiAS Professional ...
rem %INSTALL_CMD% /c /s ".\InterTRiAS_Professional.wse"
rem
echo Zusätzliche Installationen erzeugen ...
rem echo TRiAS DesignMode ...
rem %INSTALL_CMD% /c /s ".\DesignMode.wse"
echo TRiAS Shape Datenserver ...
%INSTALL_CMD% /c /s ".\ArcView_Shape.wse"
rem
echo EDBS-ALK Import (Standard) ...
%INSTALL_CMD% /c /s ".\EDBS_ALK_Standard.wse"
call MakeEdbsAlk %INSTALL_CMD% Berlin
call MakeEdbsAlk %INSTALL_CMD% Brandenburg
call MakeEdbsAlk %INSTALL_CMD% Hessen
call MakeEdbsAlk %INSTALL_CMD% Mecklenburg-Vorpommern
call MakeEdbsAlk %INSTALL_CMD% Nordrhein-Westfalen
call MakeEdbsAlk %INSTALL_CMD% Sachsen-Anhalt
call MakeEdbsAlk %INSTALL_CMD% Schleswig-Holstein
call MakeEdbsAlk %INSTALL_CMD% ALK_SABIS
call MakeEdbsAlk %INSTALL_CMD% Sachsen-Anhalt_(LVermA)
rem
echo EDBS-ATKIS Import (Standard) ...
%INSTALL_CMD% /c /s ".\EDBS_ATKIS.wse"
