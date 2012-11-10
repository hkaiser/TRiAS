#!/bin/sh
##
## source mangling script to re-enble LZW compression in libtiff. 
##
## Author: Mike Welles (mike@onshore.com). 
##
## In response to suggestions (and code) from Stanislav Brabec <utx@k332.feld.cvut.cz>
##
## 
##  Usage: mange-src.sh tiff-source-dir
##

src=$1; 

for dir in `ls $src`; do
	if [ -d $src/$dir ]; then
		for file in `ls $src/$dir/*.c 2> /dev/null`; do 
			echo "Fixing warnings in $file"; 
			cat $file \
			| sed "s/no longer supported by default due to Unisys patent enforcement/needs US license from Unisys/" \
			| sed "s/is no longer implemented due to Unisys patent enforcement/needs US license from Unisys/" \
			> ${file}.1
			mv ${file}.1 $file; 
		done	
	fi
done

echo "Fixing tiff_compress.c"
cat $src/libtiff/tif_compress.c | sed  "/LZW/,/}/s/TIFFError(tif->tif_name,/fprintf(stderr, /;/LZW/,/}/s/Unisys/&\\\\n/" > $src/libtiff/tif_compress.c.1

mv $src/libtiff/tif_compress.c.1 $src/libtiff/tif_compress.c 

for file in $src/tools/*.c; do 
	echo "Re-enabling LZW default compression in $file" 
	cat $file | sed "s/\\(uint16.*compression.*=.*COMPRESSION_\\)PACKBITS/\\1LZW/" > ${file}.1; 
	mv ${file}.1 $file
done 

echo "Finished.  Please re-build and install libtiff to complete". 



