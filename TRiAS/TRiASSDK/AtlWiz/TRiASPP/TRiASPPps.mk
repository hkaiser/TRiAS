
TRiASPPps.dll: dlldata.obj TRiASPP_p.obj TRiASPP_i.obj
	link /dll /out:TRiASPPps.dll /def:TRiASPPps.def /entry:DllMain dlldata.obj TRiASPP_p.obj TRiASPP_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TRiASPPps.dll
	@del TRiASPPps.lib
	@del TRiASPPps.exp
	@del dlldata.obj
	@del TRiASPP_p.obj
	@del TRiASPP_i.obj
