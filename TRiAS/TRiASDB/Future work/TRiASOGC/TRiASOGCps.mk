
TRiASOGCps.dll: dlldata.obj TRiASOGC_p.obj TRiASOGC_i.obj
	link /dll /out:TRiASOGCps.dll /def:TRiASOGCps.def /entry:DllMain dlldata.obj TRiASOGC_p.obj TRiASOGC_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TRiASOGCps.dll
	@del TRiASOGCps.lib
	@del TRiASOGCps.exp
	@del dlldata.obj
	@del TRiASOGC_p.obj
	@del TRiASOGC_i.obj
