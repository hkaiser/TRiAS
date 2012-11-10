###
### Change the following to the location of the tiff source directory. 
###
TIFF_SRC_DIR = /tmp/libtiff


VERSION = 1.1

.PHONY:  install

install:
	cp -f tif_dir.c $(TIFF_SRC_DIR)/libtiff/tif_dir.c
	cp -f tif_lzw.c $(TIFF_SRC_DIR)/libtiff/tif_lzw.c
	./mangle-src.sh $(TIFF_SRC_DIR)

tar:  	clean
	(cd ../ ; tar --create --verbose --exclude=CVS --file=libtiff-lzw-compression-kit-$(VERSION).tar libtiff-lzw-compression-kit); 
	gzip -f -9 ../libtiff-lzw-compression-kit-$(VERSION).tar

clean: 
	( rm *~ 2> /dev/null; rm \#* 2> /dev/null ; exit 0)