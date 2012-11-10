@echo off
rem 
rem ben”tigte TRiAS-Version setzen
rem (uncomment)
rem
rem TRiAS V3.xx
rem set TRiAS_VER=0x0300
rem
rem TRiAS V4.00
rem set TRiAS_VER=0x0400
rem
rem TRiAS V4.1x
rem set TRiAS_VER=0x0410
rem
rem TRiAS V5.00
set TRiAS_VER=0x0500
rem
rem build starten
@set TRiAS_VER
call MakeDebug.cmd
rem call MakeRelease.cmd
