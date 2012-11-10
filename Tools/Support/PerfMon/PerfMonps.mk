
PerfMonps.dll: dlldata.obj PerfMon_p.obj PerfMon_i.obj
	link /dll /out:PerfMonps.dll /def:PerfMonps.def /entry:DllMain dlldata.obj PerfMon_p.obj PerfMon_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del PerfMonps.dll
	@del PerfMonps.lib
	@del PerfMonps.exp
	@del dlldata.obj
	@del PerfMon_p.obj
	@del PerfMon_i.obj
