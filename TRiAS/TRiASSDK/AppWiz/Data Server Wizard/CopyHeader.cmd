rem
rem Kopieren aller Header, die für das TRiASDB-SDK benötigt werden
rem 

rem Ospace header
xcopy /F D:\ToolKit\ospace\COM\ComErrorMacros.h %TRIASDBSDK%\Com
xcopy /F D:\ToolKit\ospace\COM\Iterenum.h %TRIASDBSDK%\Com
xcopy /F D:\ToolKit\ospace\COM\Smartif.Debug.h %TRIASDBSDK%\Com
xcopy /F D:\ToolKit\ospace\COM\Smartif.h %TRIASDBSDK%\Com
xcopy /F D:\ToolKit\ospace\COM\Smartif.Nodebug.h %TRIASDBSDK%\Com

rem Sonstige Com-Header
xcopy /F D:\TRiASDev.MVC\Include\com\ErrorMacros2.h %TRIASDBSDK%\Com
xcopy /F D:\TRiASDev.MVC\Include\com\ErrorMacros2Impl.cpp %TRIASDBSDK%\Com
xcopy /F D:\TRiASDev.MVC\Include\com\BSTRHelpers.h %TRIASDBSDK%\Com
xcopy /F D:\TRiASDev.MVC\Include\com\VariantHelpers.h %TRIASDBSDK%\Com
xcopy /F D:\TRiASDev.MVC\Include\com\PropertyHelper.h %TRIASDBSDK%\Com
xcopy /F D:\TRiASDev.MVC\Include\com\SafeArray.h %TRIASDBSDK%\Com
xcopy /F D:\TRiASDev.MVC\Include\com\OleItemContainerSupport.h %TRIASDBSDK%\Com

rem Atl-Header
xcopy /F D:\TRiASDev.MVC\Include\Atl\Ciid.h %TRIASDBSDK%\Atl
xcopy /F D:\TRiASDev.MVC\Include\Atl\atlbasex.h %TRIASDBSDK%\Atl

rem Sonstiges
xcopy /F D:\TRiASDev.MVC\Include\DBMSG.hmc %TRIASDBSDK%
xcopy /F D:\TRiASDev.MVC\Include\WinVersion.h %TRIASDBSDK%
xcopy /F D:\TRiASDev.MVC\Include\TRiASVer.mak %TRIASDBSDK%
xcopy /F D:\TRiASDev.MVC\Include\TRiASConfig.h %TRIASDBSDK%
xcopy /F D:\TRiASDev.MVC\Include\Pragmas.h %TRIASDBSDK%
xcopy /F D:\TRiASDev.MVC\Include\TRiASDBModuleStrings.h %TRIASDBSDK%
xcopy /F D:\TRiASDev.MVC\Include\TRiASDBGuids.h %TRIASDBSDK%
xcopy /F D:\TRiASDev.MVC\Include\EnumProperty.h %TRIASDBSDK%

rem Typelibraries 
xcopy /F D:\TRiASDev.MVC\Include\Tlb\TErrTrk.tlb %TRIASDBSDK%\Tlb
xcopy /F D:\TRiASDev.MVC\Include\Tlb\TRiASDB.tlb %TRIASDBSDK%\Tlb
xcopy /F D:\TRiASDev.MVC\Include\Tlb\TRiASCS.tlb %TRIASDBSDK%\Tlb
xcopy /F D:\TRiASDev.MVC\Include\Tlb\TDBGeo.tlb %TRIASDBSDK%\Tlb

rem Geomedia Objekte
xcopy /F D:\TRiASDev.MVC\Include\GMObjects\*.tlh %TRIASDBSDK%\GMObjects


