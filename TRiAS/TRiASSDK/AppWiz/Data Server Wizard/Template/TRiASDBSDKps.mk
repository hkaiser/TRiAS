
$$root$$ps.dll: dlldata.obj $$root$$_p.obj $$root$$_i.obj
	link /dll /out:$$root$$ps.dll /def:$$root$$ps.def /entry:DllMain dlldata.obj $$root$$_p.obj $$root$$_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del $$root$$ps.dll
	@del $$root$$ps.lib
	@del $$root$$ps.exp
	@del dlldata.obj
	@del $$root$$_p.obj
	@del $$root$$_i.obj
