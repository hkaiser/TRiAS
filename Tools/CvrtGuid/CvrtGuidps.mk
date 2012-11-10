
CvrtGuidps.dll: dlldata.obj CvrtGuid_p.obj CvrtGuid_i.obj
	link /dll /out:CvrtGuidps.dll /def:CvrtGuidps.def /entry:DllMain dlldata.obj CvrtGuid_p.obj CvrtGuid_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del CvrtGuidps.dll
	@del CvrtGuidps.lib
	@del CvrtGuidps.exp
	@del dlldata.obj
	@del CvrtGuid_p.obj
	@del CvrtGuid_i.obj
