@echo off
c:\msdev\bin\dumpbin /exports .\debug\ospace5d.dll > ospac50d.exp
gawk -f exp50.awk ospac50d.exp > ospac50d.tpl
c:\msdev\bin\dumpbin /exports .\Release\ospace5r.dll > ospac50r.exp
gawk -f exp50.awk ospac50r.exp > ospac50r.tpl
