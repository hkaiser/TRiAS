@echo off
c:\msdnsmpl\untools\autoduck\autoduck /s TRiASDB.Fmt /rh /t4 /o contents.rtf *.d *.h *.cpp  *.idl e:\triasdev.mvc\include\idl\*.idl
hcrtf /a /o triasdb.hlp /xn contents.hpj
start triasdb.hlp
