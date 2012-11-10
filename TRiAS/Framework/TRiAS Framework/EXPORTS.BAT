@echo off
c:\msdev\bin\dumpbin /exports .\debug4\tfrm32d.dll > tfrm32d.exp
awk -f exp32.awk tfrm32d.exp > tfrm32d.tpl
