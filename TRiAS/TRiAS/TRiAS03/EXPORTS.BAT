@echo off
c:\msdev\bin\dumpbin /exports .\debug4\trias33d.dll > trias33d.exp
awk -f exp32.awk trias33d.exp > obj32\trias33d.tpl
