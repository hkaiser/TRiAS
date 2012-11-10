@echo off
del trias32d.bas > nul
rebase -b 400000 -C trias32d.bas -R .\trias200 -G trias32d.fil -O coordsd.fil -O exportsd.fil
rem
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\trias31d.dll
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\trias32d.dll
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\trias33d.dll
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\muscrl32.dll
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\containd.dll
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\tfrm32d.dll
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\lold.dll
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\trias32d.exe
rem
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\identdbd.ext
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\visobjd.ext
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\fakemfcd.ext
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\default.ctf
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\georeind.ext
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\geoeditd.ext
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32;c:\msdev\sysdll .\trias200\oleautod.ext
rem
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\default.ctf
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\krgeod.ctf
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\begeod.ctf
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\krassgk.ctf
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\besselgk.ctf
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\etrsgeod.ctf
rem
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\dirisasc.flt
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\dirismkl.flt
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\triasarc.flt
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\acaddxf.flt
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\atlasbna.flt
c:\msdev\bin\bind -u -p .\trias200;c:\winnt\system32 .\trias200\caddyasc.flt
