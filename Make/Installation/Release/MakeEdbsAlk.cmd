@echo off
rem
echo Landesspezifischen EDBS/ALK-Import (%2) erzeugen ...
echo _LAND_=%2> %2.txt
%1 /D=%2.txt /c /s ".\EDBS_ALK_Land.wse" 
del /Q /F %2.txt > nul 2> nul
