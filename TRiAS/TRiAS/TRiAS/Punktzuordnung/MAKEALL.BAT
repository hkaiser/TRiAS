@echo off
rem
echo Datei konvertieren ...
gawk -f tab2sem.awk zuordpkn.txt > zuordpkn.tab
rem
echo PunktIDs generieren ...
gawk -f punktids.awk zuordpkn.tab > zuordpkn.ids
rem
echo Zuordnung alte Punkte/neue Punkte erzeugen ...
gawk -f altneu.awk zuordpkn.ids | sort > altneu.srt
asc2bin ni altneu.srt altneu.bin
rem
echo Stringresource und Headerdatei erzeugen ...
del punktstr.* > nul
gawk -f punktres.awk zuordpkn.ids
del ..\punktstr.* > nul
copy punktstr.* .. > nul
rem 
echo Offset-Tabelle generieren ...
gawk -f offsetab.awk zuordpkn.ids | sort | awk -f corrtab.awk > offsetab.srt
asc2bin ni offsetab.srt offsetab.bin
rem
echo Bitmap Offsets generieren ...
gawk -f offset15.awk zuordpkn.ids | sort | gawk -f coroffst.awk > offset15.srt
asc2bin ncc offset15.srt offset15.bin
gawk -f offset23.awk zuordpkn.ids | sort | gawk -f coroffst.awk > offset23.srt
asc2bin ncc offset23.srt offset23.bin
gawk -f offset32.awk zuordpkn.ids | sort | gawk -f coroffst.awk > offset32.srt
asc2bin ncc offset32.srt offset32.bin
