
XtensionTemplateps.dll: dlldata.obj XtensionTemplate_p.obj XtensionTemplate_i.obj
	link /dll /out:XtensionTemplateps.dll /def:XtensionTemplateps.def /entry:DllMain dlldata.obj XtensionTemplate_p.obj XtensionTemplate_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del XtensionTemplateps.dll
	@del XtensionTemplateps.lib
	@del XtensionTemplateps.exp
	@del dlldata.obj
	@del XtensionTemplate_p.obj
	@del XtensionTemplate_i.obj
