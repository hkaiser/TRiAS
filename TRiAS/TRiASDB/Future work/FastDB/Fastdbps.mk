
Fastdbps.dll: dlldata.obj Fastdb_p.obj Fastdb_i.obj
	link /dll /out:Fastdbps.dll /def:Fastdbps.def /entry:DllMain dlldata.obj Fastdb_p.obj Fastdb_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Fastdbps.dll
	@del Fastdbps.lib
	@del Fastdbps.exp
	@del dlldata.obj
	@del Fastdb_p.obj
	@del Fastdb_i.obj
