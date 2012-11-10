echo off
REM These are variables that need to be set in order to
REM compile libgist and run amdb.

REM Location of JDK and Swing
set JDKINSTALL=f:\jdk1.1.8
set JFCINSTALL=f:\swing1.1.1

REM and their libraries ...
set CLASSPATH=%JDKINSTALL%\lib\classes.zip;%JFCINSTALL%\swingall.jar;.;%CLASSPATH%

REM Root of the libgist/amdb distribution.
set LIBGISTHOME=f:\blahj\libgist

REM Need to adjust the path variable so we can run amdb.
set PATH=%PATH%;%JDKINSTALL%\bin;%LIBGISTHOME%\bin;%LIBGISTHOME%\lib
