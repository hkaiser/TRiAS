@echo off
c:\msdev5\vc\bin\dumpbin /exports .\release\vassert.dll > vassert.exp
gawk -f exp50.awk vassert.exp > vassert.tpl
