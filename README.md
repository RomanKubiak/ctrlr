CtrlrX
=====

CtlrX is an alternative fork of Roman Kubiak's Ctrlr.
This project is ONLY aimed at delivering updates, a wiki, documentation, tutorials or anything that the community cannot share on the original Ctrlr github due to credential restrictions. 
Let's keep the Ctrlr github alive and keep up with what we were all doing there. But for anything that deserves special credentials unavailable there, just let's do it here on CtrlrX.


TODO
----
* Scalable UI upgrade (requires container callback on resize)
* Implementation of the entire JUCE ValueTree Class


Changelog
---------
#### Version 0.0.0
* Requires unified versioning pattern



# About Ctrlr

Control any MIDI enabled hardware: synthesizers, drum machines, samplers, effects. Create custom User Interfaces. Host them as VST or AU plugins in your favorite DAWs.


Cross Platform
--------------
Works on Windows (XP and up, both 64 and 32bit binaries are available), macOS (10.5 and up), Linux (any modern distro should run it).
Host in your DAW

Each platform has a VST build of Ctrlr so you can host your panels as normal VST plugins, for macOS a special AU build is available.

Customize
---------
Each Panel can be customized by the user, the panels are XML files, every panel can be Edited in Ctrlr to suite your specific needs.

Open Source
-----------
Need special functionality or want to propose a patch/feature update, know a bit about C++/JUCE framework etc. You can always download the source code and build Ctrlr by yourself.

Extend
------
With the scripting possibilities inside Ctrlr you can extend you panels in various ways. The LUA scripting language gives you access to all panels elements and hooks to various events.


# How to build CtrlrX


## Windows

Summary will be added here in the future, links to pdf of build guides by @bijlevel can be found here

[Compiling on Windows 10](https://godlike.com.au/fileadmin/godlike/techtools/ctrlr/guides/Compiling_Ctrlr_for_Windows_10_v2.1.pdf)


## macOS

[Compiling on OSX](https://godlike.com.au/fileadmin/godlike/techtools/ctrlr/guides/My_guide_to_compiling_Ctrlr_for_macOS__Mojave__v2.pdf)


## Linux

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

# How to export plugin instances (AU, AUv3, VST & VST3)

## VST2 Support
Since Steinberg has discontinued the VST2 API we no longer distribute a VST2. If you are a licensee to the VST2SDK, though, you can still build it. 
The first thing is to be sure to check the path to the VST2 sdk (available in the VST3 sdk) in Projucer before calling any script builds.

## VST3 Support
Tutorial coming soon

## AU Support
Tutorial coming soon

## AUv3 Support
Tutorial coming soon

# Credits
* Thanks to @romankubiak for developing Ctrlr
* Links to contributors coming soon
