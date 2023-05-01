ImageJ Launcher
===============
Simple setup for building the original [ImageJ launcher](https://imagej.nih.gov/ij/download/tools/Launcher.cpp) for Windows.


Intallation
-----------
Download `ImageJ.exe` from the [Releases](https://github.com/ij-plugins/ImageJ-Launcher/releases) page, replace your standard `ImageJ.exe` with this one.


Why Another Launcher?
---------------------
Really it is the [old launcher](https://imagej.nih.gov/ij/download/tools/Launcher.cpp), unmodified source code, just rebuild with recent tools to works with new versions of Java, properly setting DPI configuration, and most importantly to read "ImageJ.cfg" as it was originally intended.

Neither the launcher currently provided with [ImageJ Download](https://imagej.nih.gov/ij/download.html) nor the [FIJI/ImageJ2 Lanuncher](https://imagej.net/learn/launcher) worked correctly when tried to use ImageJ with custom "ImageJ.cfg". 

Needed to customize the class path in "ImageJ.cfg". The standard [ImageJ launcher](https://imagej.nih.gov/ij/download.html) was quiting with error "Without ij-launcher, '--ijcp' cannot be handled". [FIJI/ImageJ2 Lanuncher](https://imagej.net/learn/launcher) did not want to correctly accept custom classpath settings, modifying it incorrectly. Looks that both are a variants of the FIJI launcher.


How to Build
------------
Assumes that you have [CMake](https://cmake.org/) and Visual Studio 2019 installed.
1. Download the source code and unpack to directory `ImageJ-Launcher`
2. Next to it create directory `ImageJ-Launcher-build`
3. Open en command prompt and chage directory to `ImageJ-Launcher-build`
4. Type `cmake ..\ImageJ-Launcher`
5. Open `ImageJ-Launcher.sln` with Visual Studio and rebuild the solution


License
-------
Public domain see [ImageJ Disclaimer](https://imagej.nih.gov/ij/disclaimer.html)