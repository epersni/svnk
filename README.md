# svnk
This is a clone of the famous gitk application. But this runs in a ncurses based TUI (much better than a window application if you ask me!) and it browses subersion commits instead of git commits.

![Alt text](screenshot.png?raw=true "Screenshot of svnk")

Svnk was created to be compliant with old computers, since if you are stuck with subversion, you are likely to be stuck with old an old Linux system). This version compiles perfectly with on a Fedora 12 system! Here are the antique dependencies I used:

* g++ 4.4.4
* Boost 1.39
* scons v2.0.1

# Compile
Just run
``` 
scons
```
and the binary result is in the out/ directory.

# Usage
Start the svnk application in a subersion directory of your choice. It might take a while to load all the commits and then you can browse the commits. The TUI is three frames: a code browser-, commits list-, modified files frame. You browse with the vim key bindings H,J,K,L. You select an item with ENTER and you change active frame with the TAB key.
