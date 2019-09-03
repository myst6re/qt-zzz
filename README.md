qt-zzz
======

Simple command-line tool to extract/create ZZZ archives (used in Final Fantasy VIII Remaster).

Usage
-----

~~~
zzz [-e] [-h] [-q] [files...] [output directory]
unzzz [-h] [-q] [files...] [output directory]
Options
    -e --extract
        Extract.

    -h --help
        Show this help and quit.

    -q --quiet
        Suppress all outputs
~~~

Compilation
-----------

qt-zzz is a Qt project, use these commands to build it:

    qmake
    make

To compile the unzzz executable, run:

    qmake "CONFIG+=configUNZZZ"
    make
