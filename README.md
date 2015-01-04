libfnv
======

C language FNV hash function library supporting 32, 64, 128, and 256 bit lengths.

Compilation instructions:

    git clone https://github.com/fnvhash/libfnv.git
    cd libfnv
    ./autogen
    ./configure
    make
    sudo make install

Once the package is installed, it may easily be compiled and linked with:

    gcc my_prog.c -o my_prog `pkg-config --libs --cflags libfnv`

To use, select a bit size from 32, 64, 128, or 256 and enter a command:

    fnv64sum [FILE]

All four bit sizes are supported with the corresponding command names.

To test or verify your own FNV implementation, you may use this library or
another one such as
this [online FNV hash calculator](http://find.fnvhash.com/).

On a modern consumer-grade computer, this library is able to process about a
gigabyte of data per second using fnv32sum and fnv64sum, or about
100 megabytes per second using fnv128sum or fnv256sum.
