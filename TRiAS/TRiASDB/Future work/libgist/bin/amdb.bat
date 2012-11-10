set CPATH=%LIBGISTHOME%\src\gui;%LIBGISTHOME%\src\analysis;%LIBGISTHOME%\src\amdbgist;%LIBGISTHOME%\src\treeview;%CLASSPATH%

echo java -classpath "%CPATH%" MainWindow

java -classpath "%CPATH%" MainWindow
