@echo off
c:\msdev\bin\dumpbin /exports .\debug4\trias32d.dll > trias32d.exp
awk -f exp32.awk trias32d.exp > obj32\trias32d.tpl
