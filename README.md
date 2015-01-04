libfnv
======

C language FNV hash function library supporting bit lengths 32, 64, 128, 256, 512, and 1024

Compilation instructions:

    git clone https://github.com/fnvhash/libfnv.git
    cd libfnv
    ./autogen
    ./configure
    make
    sudo make install

Once the package is installed, it may easily be compiled and linked with:

    gcc my_prog.c -o my_prog `pkg-config --libs --cflags libfnv`

To use:

    fnv64 [FILE]

or

    fnv32 [FILE]
