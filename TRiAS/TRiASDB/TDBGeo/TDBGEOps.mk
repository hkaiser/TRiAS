
TDBGEOps.dll: dlldata.obj TDBGEO_p.obj TDBGEO_i.obj
	link /dll /out:TDBGEOps.dll /def:TDBGEOps.def /entry:DllMain dlldata.obj TDBGEO_p.obj TDBGEO_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del TDBGEOps.dll
	@del TDBGEOps.lib
	@del TDBGEOps.exp
	@del dlldata.obj
	@del TDBGEO_p.obj
	@del TDBGEO_i.obj
