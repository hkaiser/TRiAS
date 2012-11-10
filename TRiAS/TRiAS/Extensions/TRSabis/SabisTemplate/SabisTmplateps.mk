
SabisTmplateps.dll: dlldata.obj SabisTmplate_p.obj SabisTmplate_i.obj
	link /dll /out:SabisTmplateps.dll /def:SabisTmplateps.def /entry:DllMain dlldata.obj SabisTmplate_p.obj SabisTmplate_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del SabisTmplateps.dll
	@del SabisTmplateps.lib
	@del SabisTmplateps.exp
	@del dlldata.obj
	@del SabisTmplate_p.obj
	@del SabisTmplate_i.obj
