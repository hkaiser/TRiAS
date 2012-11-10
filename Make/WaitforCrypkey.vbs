' WaitFroCrypkey.vbs

Set objShell = WScript.CreateObject("WScript.Shell")
RetVal = objShell.Popup("Please wrap the generated TRiAS version with CrypKey!", 0, "Wait for CrypKey wrapping", 36)
Wscript.Quit RetVal
