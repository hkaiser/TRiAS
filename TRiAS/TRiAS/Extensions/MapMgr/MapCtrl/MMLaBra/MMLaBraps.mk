
MMLaBraps.dll: dlldata.obj MMLaBra_p.obj MMLaBra_i.obj
	link /dll /out:MMLaBraps.dll /def:MMLaBraps.def /entry:DllMain dlldata.obj MMLaBra_p.obj MMLaBra_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del MMLaBraps.dll
	@del MMLaBraps.lib
	@del MMLaBraps.exp
	@del dlldata.obj
	@del MMLaBra_p.obj
	@del MMLaBra_i.obj
