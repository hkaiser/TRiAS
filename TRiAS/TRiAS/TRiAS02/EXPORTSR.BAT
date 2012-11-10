@echo off
c:\msdev\bin\dumpbin /exports .\release\trias322.dll > trias322.exp
gawk -f exp32.awk trias322.exp > obj32\trias322.tpl
