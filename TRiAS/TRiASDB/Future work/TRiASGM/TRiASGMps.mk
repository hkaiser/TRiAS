
TRiASGMps.dll: dlldata.obj TRiASGM_p.obj TRiASGM_i.obj
	link /dll /out:TRiASGMps.dll /def:TRiASGMps.def /entry:DllMain dlldata.obj TRiASGM_p.obj TRiASGM_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del TRiASGMps.dll
	@del TRiASGMps.lib
	@del TRiASGMps.exp
	@del dlldata.obj
	@del TRiASGM_p.obj
	@del TRiASGM_i.obj
