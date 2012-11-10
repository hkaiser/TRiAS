@echo off
c:\msdev\bin\dumpbin /exports .\release\ospacer.dll > ospacer.exp
gawk -f exp32.awk ospacer.exp > ospace.tpl
