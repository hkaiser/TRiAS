
TriasDBps.dll: dlldata.obj TriasDB_p.obj TriasDB_i.obj
	link /dll /out:TriasDBps.dll /def:TriasDBps.def /entry:DllMain dlldata.obj TriasDB_p.obj TriasDB_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del TriasDBps.dll
	@del TriasDBps.lib
	@del TriasDBps.exp
	@del dlldata.obj
	@del TriasDB_p.obj
	@del TriasDB_i.obj
