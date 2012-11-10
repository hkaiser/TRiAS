echo off
if not "%1" == "" goto %1
for %%A in (amdbgist libbtree libgist libnptree librtree) do call %0 doit %%A
call %0 doit2
goto end

:doit
cd %2
ren *.cpp *.cc
cd ..
goto end

:doit2
cd cmdline
ren cmdline.cpp cmdline.cc
ren cmdline_gram.tab.cpp cmdline_gram.tab.cc
ren cmdline_scan.cpp cmdline_scan.cc
cd ..
goto end

:end
