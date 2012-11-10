
TRiASPRVps.dll: dlldata.obj TRiASPRV_p.obj TRiASPRV_i.obj
	link /dll /out:TRiASPRVps.dll /def:TRiASPRVps.def /entry:DllMain dlldata.obj TRiASPRV_p.obj TRiASPRV_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TRiASPRVps.dll
	@del TRiASPRVps.lib
	@del TRiASPRVps.exp
	@del dlldata.obj
	@del TRiASPRV_p.obj
	@del TRiASPRV_i.obj
