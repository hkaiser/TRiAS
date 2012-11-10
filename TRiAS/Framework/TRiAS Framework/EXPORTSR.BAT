@echo off
c:\msdev\bin\dumpbin /exports .\release\tfrmwork.dll > tfrm32.exp
awk -f exp32.awk tfrm32.exp > tfrm32.tpl
