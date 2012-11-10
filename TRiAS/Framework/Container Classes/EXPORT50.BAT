@echo off
c:\msdev5\vc\bin\dumpbin /exports .\debug\containd.dll > cont50d.exp
awk -f exp50.awk cont50d.exp > cont50d.tpl
rem c:\msdev\bin\dumpbin /exports .\release\containr.dll > cont50r.exp
rem awk -f exp50.awk cont50r.exp > cont50r.tpl
