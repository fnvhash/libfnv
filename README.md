libfnv
======

C language FNV hash function library supporting 32, 64, 128, 256-1024 bit lengths.

Compilation instructions

Clone from repo:
    git clone https://github.com/fnvhash/libfnv.git
or download a release and extract it.
    tar xvfz libfnv*tar*
cd into the extracted directory:
    cd libfnv*
Use ls to find out if there is a configure script.
    ls -l configure
If not, run:
    ./autogen
Once the configure script is available, compilation is as normal for all
autoconf enabled projects:
    ./configure
    make
    sudo make install

Once the package is installed, it may easily be compiled and linked with:

    gcc my_prog.c -o my_prog `pkg-config --libs --cflags libfnv`

In C, the library follows standard conventions. my_prog.c can be as simple as:

    #include <stdio.h>
    #include <fnv.h>
    
    int main(int argc, char **argv) {
      const char *test_string = "foobar";
      uint64_t hval;
      char result[17];
      fnv64Init(&hval);
      fnv64UpdateBuffer(&hval, test_string, 6);
      fnv64ResultHex(result, &hval);
      printf("%s\n", result);
      return 0;
    }

To use, select a bit size from 32, 64, 128, 256, 512, or 1024 and enter a command:

    fnv64sum [FILE]

All four bit sizes are supported with the corresponding command names.

To test or verify your own FNV implementation, you may use this library or
another one such as
this [online FNV hash calculator](http://find.fnvhash.com/).

On a modern consumer-grade computer, this library is able to process about a
gigabyte of data per second using fnv32sum and fnv64sum, or about
100 megabytes per second using fnv128sum or fnv256sum.

[Downloads of Releases](http://fnvhashdl.s3-website-us-west-2.amazonaws.com/)

