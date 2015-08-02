libfnv
======

C language FNV hash function library with all supported bit lengths of FNV-1a: 32, 64, 128, 256, 512, and 1024

<h2>Compilation instructions</h2>

<h3>Clone from repo:</h3>

    git clone https://github.com/fnvhash/libfnv.git

<h4>OR</h4><br/>
 download a release and extract it.

    tar xvfz libfnv*tar*

cd into the extracted directory:

    cd libfnv*

Use <i>ls</i> to find out if there is a configure script.

    ls -l configure

If not, run:

    ./autogen

Once the configure script is available, compilation is as normal for all
autoconf enabled projects:

    ./configure
    make
    sudo make install
    
<h2>Compiling and Running your Own Programs</h2>
Once the package is installed, it may easily be compiled and linked with:

    gcc my_prog.c -o my_prog --static `pkg-config --libs --cflags libfnv`

In C, the library follows standard conventions. my_prog.c can be as simple as:

```c
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
```

After you have compiled the example program above, you may try running it to
verify the results of computing the 64-bit FNV-1a hash of the 6-byte string <i>foobar</i>.

    ./my_prog

<h2>Prepackaged Command Line Tools</h2>
This library includes a set of command line tools that may be used to compute
FNV-1a hashes in any size.  Simply select a bit size from 32, 64, 128, 256, 512, or 1024 and enter a command:

    fnv64sum [FILE]

All four bit sizes are supported with the corresponding command names.

To test or verify your own FNV implementation, you may use this library or
another one such as
this [online FNV hash calculator](http://fnvhash.github.io/fnv-calculator-online/).

On a modern consumer-grade computer, this library is able to process about a
gigabyte of data per second using fnv32sum and fnv64sum, or about
100 megabytes per second using fnv128sum or fnv256sum.

[Downloads of Releases](http://fnvhashdl.s3-website-us-west-2.amazonaws.com/)

