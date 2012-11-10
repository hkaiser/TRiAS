
TRiASMIps.dll: dlldata.obj TRiASMI_p.obj TRiASMI_i.obj
	link /dll /out:TRiASMIps.dll /def:TRiASMIps.def /entry:DllMain dlldata.obj TRiASMI_p.obj TRiASMI_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TRiASMIps.dll
	@del TRiASMIps.lib
	@del TRiASMIps.exp
	@del dlldata.obj
	@del TRiASMI_p.obj
	@del TRiASMI_i.obj
