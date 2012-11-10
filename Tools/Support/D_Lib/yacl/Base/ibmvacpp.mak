!INCLUDE ..\control\ibmvacpp.ctl


# ------------------------ Names of files --------------------------

OBJECTS  = \
bitset.obj\
bytarray.obj\
bytestrm.obj\
bytstrng.obj\
clntset.obj\
date.obj\
error.obj\
gbtree.obj\
genseq.obj\
integer.obj\
intseq.obj\
intset.obj\
map.obj\
object.obj\
objseq.obj\
objset.obj\
regexpr.obj\
segseq.obj\
stream.obj\
strgseq.obj\
strgset.obj\
string.obj\
strsplit.obj\
tbtree.obj\
timeofda.obj\
tree.obj\
treewalk.obj\
version.obj


# ---------------------- Compilation rules -----------------------

all: $(BASELIB) $(MEMORYLIB)
	
$(BASELIB): $(OBJECTS) 
	$(LIBR) $(LIBOPTS) @<<
$(BASELIB) -+$(OBJECTS: = ^&^
-+);
<<
        -$(DELETE) $(YACLLIB)\$(BASE).bak > nul 2>&1

$(MEMORYLIB): memory.obj
	$(LIBR) $(LIBOPTS) $(MEMORYLIB) -+memory.obj;
	-$(DELETE) $(YACLLIB)\$(MEMORY).bak > nul 2>&1
	
# ------------------ Other targets ---------------------------

clean:
        -$(DELETE) *.obj > nul 2>&1
        -$(DELETE) *.cfg > nul 2>&1
        -$(DELETE) $(BASELIB) > nul 2>&1
        -$(DELETE) $(YACLLIB)\$(BASE).bak > nul 2>&1
        -$(DELETE) $(MEMORYLIB) > nul 2>&1
        -$(DELETE) $(YACLLIB)\$(MEMORY).bak > nul 2>&1
