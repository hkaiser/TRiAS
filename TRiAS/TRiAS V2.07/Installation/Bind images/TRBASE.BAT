@echo off
del trias32.bas > nul
rebase -v -d -b 68000000 -C trias32.bas -R ..\trias200.rel -G trias32.fil -O coords.fil -O exports.fil -O import.fil
c:\bin\tools\fd ..\trias200.rel\*.* /d:06-30-98 /z:2:10
