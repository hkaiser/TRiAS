

All:
!IF "$(CPU)" == "IA64"
!IFDEF NODEBUG
   nmake /f dcomperm64.mak CFG="dcomperm - Win64 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f dcomperm64.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ELSE
!IFDEF NODEBUG
   nmake /f dcomperm.mak CFG="dcomperm - Win32 Release" -nologo /$(MAKEFLAGS) $(makeopts)
!ELSE
   nmake /f dcomperm.mak -nologo /$(MAKEFLAGS) $(makeopts)
!ENDIF
!ENDIF