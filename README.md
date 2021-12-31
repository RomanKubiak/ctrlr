CtrlrX
=====

CtlrX is an alternative fork of Roman Kubiak's Ctrlr.
This project is ONLY aimed at delivering updates, a wiki, documentation, tutorials or anything that the community cannot share on the original Ctrlr github due to credential restrictions. 
Let's keep the Ctrlr github alive and keep up with what we were all doing there. But for anything that deserves special credentials unavailable there, just let's do it here on CtrlrX.


Ctrlr
=====

Control any MIDI enabled hardware: synthesizers, drum machines, samplers, effects. Create custom User Interfaces. Host them as VST or AU plugins in your favorite DAWs.


Cross Platform
==============
Works on Windows (XP and up, both 64 and 32bit binaries are available), macOS (10.5 and up), Linux (any modern distro should run it).
Host in your DAW

Each platform has a VST build of Ctrlr so you can host your panels as normal VST plugins, for macOS a special AU build is available.

Customize
=========
Each Panel can be customized by the user, the panels are XML files, every panel can be Edited in Ctrlr to suite your specific needs.

Open Source
===========
Need special functionality or want to propose a patch/feature update, know a bit about C++/JUCE framework etc. You can always download the source code and build Ctrlr by yourself.

Extend
======
With the scripting possibilities inside Ctrlr you can extend you panels in various ways. The LUA scripting language gives you access to all panels elements and hooks to various events.


Building
========

Windows
=======
If you want to just build a specific version (Standalone/VST), you should open a project in
Builds\Generated\Windows (Standalone is for VS2010, the rest of the folder are named based
on the VS they correspond to). If you wish to use Codeblocks a project is there too.

If the current commit does not because it complains about precompiled headers (you can easily
see that the project is wrong if there is no x64 in the Configuration manager) you need
to exclude some files from using precompiled headers, the files are:

*.c files in Misc
*.cpp files in Juce Library Code

Also for those files you need to uncheck the option to inherit command line options
Configuration Properties - C/C++ - Command Line - "Inherit from parent or project defaults"

You need to set the creation of the precompiled header for the stdafx.cpp.

If you don't have Introjucer/Projucer built, disable the "Pre-Build Event" for the
Debug Configuration, or else it will fail. If you wish to re-create resources though
point the correct path to Projucer.exe

In order to build all configurations and all platforms, you can open the
Builds/Ctrlr_Release.sln solution, and build it, assuming that each individual solution
builds (Standalone/VST x86/x64) all versions will be built in this solution.

Linux
=====
A build.sh script is provided in Builds/Generated/Linux/Standalone, a symlink of that
script is location in Builds/Generated/Linux/VST and is used to create a precompiled header
and then to trigger the build using make. You can do that manualy if you like just have
a look at the script, it's really simple.

A more complex solution exists in Scripts/post-commit, this script will build all solutions
for the current architecture, it will also prepare the system for the build, unpack boost.zip
check some packages (on Ubuntu only for now) and start the build. At the end it will create
a self extracting Ctrlr.sh file in Packaging/Linux (create using makeself.sh), it will also
try to scp it to ctrlr.org but that will fail without the correct ssh key, you can just comment
out the scp line in post-commit.

The post-commit script takes an argument "clean" if you wish to clean all the intermididate
files before building. If you want to ignore any package errors that it reports (i assume you
know your system better then my script) then just add -f as an option when building.

macOS
=====
Unzip boost or link your own boost library e.g. from [Homebrew](https://brew.sh):

```
# use packaged boost library
cd Source/Misc/boost && unzip boost.zip
# alternatively, link your own
ln -s /opt/homebrew/Cellar/boost/BOOST_VERSION/include/boost Source/Misc/boost/boost
```

Open the Xcode project `Builds/MacOSX/Ctrlr.xcodeproj` and build it.

In case of errors it might help to refresh the project files using Projuicer.
