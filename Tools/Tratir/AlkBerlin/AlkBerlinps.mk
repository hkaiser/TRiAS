
AlkBerlinps.dll: dlldata.obj AlkBerlin_p.obj AlkBerlin_i.obj
	link /dll /out:AlkBerlinps.dll /def:AlkBerlinps.def /entry:DllMain dlldata.obj AlkBerlin_p.obj AlkBerlin_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del AlkBerlinps.dll
	@del AlkBerlinps.lib
	@del AlkBerlinps.exp
	@del dlldata.obj
	@del AlkBerlin_p.obj
	@del AlkBerlin_i.obj
