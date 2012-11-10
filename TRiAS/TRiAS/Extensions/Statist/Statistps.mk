
Statistps.dll: dlldata.obj Statist_p.obj Statist_i.obj
	link /dll /out:Statistps.dll /def:Statistps.def /entry:DllMain dlldata.obj Statist_p.obj Statist_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Statistps.dll
	@del Statistps.lib
	@del Statistps.exp
	@del dlldata.obj
	@del Statist_p.obj
	@del Statist_i.obj
