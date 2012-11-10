@echo off
c:\msdev\bin\dumpbin /exports .\debug4\trias31d.dll > trias31d.exp
awk.exe -f exp32.awk trias31d.exp > trias31d.tpl
c:\msdev\bin\dumpbin /exports .\Release\trias321.dll > trias321.exp 
awk.exe -f exp32.awk trias321.exp > trias321.tpl
