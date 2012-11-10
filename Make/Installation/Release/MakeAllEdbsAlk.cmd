@echo off
rem Pfad des Installationsgenerators
set INSTALL_CMD="C:\Programme\Wise Installmaster 8.1\wise32.exe"
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
rem call MakeEdbsAlk %INSTALL_CMD% Sachsen-Anhalt_(LVermA)
