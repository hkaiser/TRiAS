@echo off
dumpbin /exports .\debug\imjpegd.dll > imjpegd.exp
gawk -f exp50.awk imjpegd.exp > imjpegd.def
dumpbin /exports .\release\imjpeg.dll > imjpeg.exp
gawk -f exp50.awk imjpeg.exp > imjpeg.def
