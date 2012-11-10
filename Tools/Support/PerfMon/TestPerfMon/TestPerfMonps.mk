
TestPerfMonps.dll: dlldata.obj TestPerfMon_p.obj TestPerfMon_i.obj
	link /dll /out:TestPerfMonps.dll /def:TestPerfMonps.def /entry:DllMain dlldata.obj TestPerfMon_p.obj TestPerfMon_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del TestPerfMonps.dll
	@del TestPerfMonps.lib
	@del TestPerfMonps.exp
	@del dlldata.obj
	@del TestPerfMon_p.obj
	@del TestPerfMon_i.obj
