@echo off
rem 
echo Alle ObjektFiles (*.obj) löschen
rem
@del %1 /S D:\TRiASDev.mvc\*.obj
@del %1 /S D:\VCPP\*.obj
@del %1 /S D:\Toolkit\ospace\ospace\*.obj
rem 
echo Alle sonstigen nicht benötigten Dateien (*.pch, *.?idb) löschen
rem
@del %1 /S D:\TRiASDev.mvc\*.pch 
@del %1 /S D:\VCPP\*.pch
@del %1 /S D:\Toolkit\ospace\ospace\*.pch
rem @del %1 /S D:\TRiASDev.mvc\*.?db
rem @del %1 /S D:\VCPP\*.?db
@del %1 /S D:\TRiASDev.mvc\*.exp
@del %1 /S D:\VCPP\*.exp
@del %1 /S D:\Toolkit\ospace\ospace\*.exp
@del %1 /S D:\TRiASDev.mvc\*.sbr
@del %1 /S D:\VCPP\*.sbr
@del %1 /S D:\Toolkit\ospace\ospace\*.sbr
@del %1 /S D:\TRiASDev.mvc\*.bsc
@del %1 /S D:\VCPP\*.bsc
@del %1 /S D:\Toolkit\ospace\ospace\*.bsc
@del %1 /S D:\TRiASDev.MVC\*.ebc
@del %1 /S D:\VCPP\*.ebc
@del %1 /S D:\TRiASDev.MVC\*.ncb
@del %1 /S D:\VCPP\*.ncb
@del %1 /S D:\Toolkit\ospace\ospace\*.ncb
@del %1 /S D:\TRiASDev.MVC\*.ilk
@del %1 /S D:\VCPP\*.ilk
@del %1 /S D:\Toolkit\ospace\ospace\*.ilk
@del %1 /S D:\TRiASDev.MVC\vc60.*
@del %1 /S D:\VCPP\vc60.*
@del %1 /S D:\Toolkit\ospace\ospace\vc60.*
rem
echo Alle Log-Dateien (*.log) löschen
rem
@del %1 D:\Make\Debug\Log\*.*
@del %1 D:\Make\Release\Log\*.*
@del %1 D:\Make\tmp\*.log
rem
echo Diverse Typelibs löschen
rem
@del %1 D:\TRiASDev.MVC\TerrTrk\TErrtrk.tlb
@del %1 D:\TRiASDev.MVC\TDBGeo\TDBGeo.tlb
@del %1 D:\TRiASDev.MVC\TRiASCS\TRiASCS.tlb
@del %1 D:\TRiASDev.MVC\TRiASDB\TRiASDB.tlb
@del %1 D:\TRiASDev.MVC\Coords\Default\ctf.tlb
@del %1 D:\TRiASDev.MVC\Coords\GKCtf\GKCtf_COM.tlb
@del %1 D:\TRiASDev.MVC\Coords\GeodCTF\GeodCtf_COM.tlb
