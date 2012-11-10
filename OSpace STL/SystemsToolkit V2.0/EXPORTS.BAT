@echo off
c:\msdev\bin\dumpbin /exports .\debug\ospaced.dll > ospaced.exp
gawk -f exp32.awk ospaced.exp > ospaced.tpl
