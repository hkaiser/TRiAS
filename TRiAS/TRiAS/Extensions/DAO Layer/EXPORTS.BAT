@echo off
c:\msdev\bin\dumpbin /exports .\Release\daolayer.ebn > daolayer.exp
gawk -f exp32.awk daolayer.exp > daolayer.tpl
