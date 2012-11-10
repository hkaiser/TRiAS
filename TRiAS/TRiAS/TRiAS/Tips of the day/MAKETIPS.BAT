@echo off
@ echo Generating Tips of the Day ...
copy triastip.hdr trias.tip > nul
.\release\gentip < triastip.tpl >> trias.tip
copy trias.tip c:\trias.mvc\trias200 > nul
