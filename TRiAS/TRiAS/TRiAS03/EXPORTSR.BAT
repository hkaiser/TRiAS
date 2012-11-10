@echo off
c:\msdev\bin\dumpbin /exports .\release\trias323.dll > trias323.exp
gawk -f exp32r.awk trias323.exp > obj32\trias323.tpl
