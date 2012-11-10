@echo off
rem c:\msdev\bin\dumpbin /exports .\debug.207\trias33d.dll > trias33d207.exp
rem awk -f exp32.awk trias33d207.exp > obj32\trias33d207.tpl
c:\msdev\bin\dumpbin /exports .\release\trias323.dll > trias323207.exp
awk -f exp32.awk trias323207.exp > obj32\trias323207.tpl
