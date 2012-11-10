echo off
if not "%1" == "" goto %1
for %%A in (amdbgist libbtree libgist libnptree librtree) do call %0 doit %%A
call %0 doit2
goto end

:doit
cd %2
ren *.cc *.cpp
cd ..
goto end

:doit2
cd cmdline
ren cmdline.cc cmdline.cpp
ren cmdline_gram.tab.cc cmdline_gram.tab.cpp
ren cmdline_scan.cc cmdline_scan.cpp
cd ..
goto end

:end
