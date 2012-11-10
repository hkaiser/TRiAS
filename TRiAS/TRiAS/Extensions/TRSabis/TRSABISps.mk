
TRSABISps.dll: dlldata.obj TRSABIS_p.obj TRSABIS_i.obj
	link /dll /out:TRSABISps.dll /def:TRSABISps.def /entry:DllMain dlldata.obj TRSABIS_p.obj TRSABIS_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del TRSABISps.dll
	@del TRSABISps.lib
	@del TRSABISps.exp
	@del dlldata.obj
	@del TRSABIS_p.obj
	@del TRSABIS_i.obj
