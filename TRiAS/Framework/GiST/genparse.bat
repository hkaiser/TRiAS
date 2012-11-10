cd RTree
del gram.tab.cpp
bison -dv gram.y
ren gram.tab.c gram.tab.cpp
flex -It scan.l > scan.cpp

cd ..\RSTree
del gram.tab.cpp
bison -dv gram.y
ren gram.tab.c gram.tab.cpp
flex -It scan.l > scan.cpp

cd ..\BTree
del gram.tab.cpp
bison -dv gram.y
ren gram.tab.c gram.tab.cpp
flex -It scan.l > scan.cpp

cd ..
