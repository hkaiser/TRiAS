
TRiASHPps.dll: dlldata.obj TRiASHP_p.obj TRiASHP_i.obj
	link /dll /out:TRiASHPps.dll /def:TRiASHPps.def /entry:DllMain dlldata.obj TRiASHP_p.obj TRiASHP_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TRiASHPps.dll
	@del TRiASHPps.lib
	@del TRiASHPps.exp
	@del dlldata.obj
	@del TRiASHP_p.obj
	@del TRiASHP_i.obj
