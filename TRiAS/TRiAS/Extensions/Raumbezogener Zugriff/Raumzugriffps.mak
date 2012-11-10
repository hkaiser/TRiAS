
Raumzugriffps.dll: dlldata.obj Raumzugriff_p.obj Raumzugriff_i.obj
	link /dll /out:Raumzugriffps.dll /def:Raumzugriffps.def /entry:DllMain dlldata.obj Raumzugriff_p.obj Raumzugriff_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /DREGISTER_PROXY_DLL $<

clean:
	@del Raumzugriffps.dll
	@del Raumzugriffps.lib
	@del Raumzugriffps.exp
	@del dlldata.obj
	@del Raumzugriff_p.obj
	@del Raumzugriff_i.obj
