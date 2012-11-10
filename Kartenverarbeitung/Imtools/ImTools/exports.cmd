@echo off
dumpbin /exports .\debug\imtoolsd.dll > imtoolsd.exp
gawk -f exp50.awk imtoolsd.exp > imtoolsd.def
dumpbin /exports .\release\imtools.dll  > imtools.exp
gawk -f exp50.awk imtools.exp > imtools.def
