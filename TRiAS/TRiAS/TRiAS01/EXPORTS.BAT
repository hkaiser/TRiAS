@echo off
rem c:\msdev\bin\dumpbin /exports .\debug\trias31d.dll > trias31d.exp
rem "awk.exe" -f exp32.awk trias31d.exp > trias31d.tpl
c:\msdev5\vc\bin\dumpbin /exports .\Release\trias321.dll > trias321.exp
c:\bin\gawk.exe -f exp32.awk trias321.exp > trias321.tpl
