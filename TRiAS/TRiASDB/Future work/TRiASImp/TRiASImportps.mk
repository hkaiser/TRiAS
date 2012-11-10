
TRiASImportps.dll: dlldata.obj TRiASImport_p.obj TRiASImport_i.obj
	link /dll /out:TRiASImportps.dll /def:TRiASImportps.def /entry:DllMain dlldata.obj TRiASImport_p.obj TRiASImport_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del TRiASImportps.dll
	@del TRiASImportps.lib
	@del TRiASImportps.exp
	@del dlldata.obj
	@del TRiASImport_p.obj
	@del TRiASImport_i.obj
