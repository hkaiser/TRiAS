@echo off
rem Pfad des Installationsgenerators
set INSTALL_CMD="C:\Programme\Wise Installmaster 8.1\wise32.exe"
rem
echo EDBS-ATKIS Import (Standard) ...
%INSTALL_CMD% /c /s ".\EDBS_ATKIS.wse"
