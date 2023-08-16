
Berkeley SoftFloat Release 3e for 6502 Microprocessors
======================================================

This repository contains an experimental floating-point implementation
for 6502 microprocessors based on Berkeley SoftFloat.  It is designed
to be compiled using [LLVM-MOS](https://llvm-mos.org/wiki/Welcome).

Building
--------

First, install the [LLVM-MOS SDK](https://github.com/llvm-mos/llvm-mos-sdk#getting-started) and make sure that you have the `bin` directory of the SDK
on the front of your PATH.  In particular, the following binaries must
be available to compile and test the code:

* `mos-common-clang`
* `mos-sim-clang`
* `mos-sim`
* `llvm-ar` (the LLVM-MOS version, not the generic LLVM version)

You will also need GNU make to process the Makefile's for the project.

The following commands will build the SoftFloat library with `mos-common-clang`
and install it into the `mos-platform/common/include` and
`mos-platform/common/lib` directories:

    cd build/llvm-mos
    make
    make install

Using
-----

The library uses types with names like `float32_t` and `float64_t`
instead of `float` and `double`.  To perform arithmetic you need
to use functions like `f32_add()`, `f32_mul()`, and so on.  These are
declared in the `softfloat.h` header file.

The following example computes ((1 + 2) * 3) with an expected result of 9:

    #include <stdio.h>
    #include <softfloat.h>

    int main(void)
    {
        float32_t one = i32_to_f32(1);
        float32_t two = i32_to_f32(2);
        float32_t three = i32_to_f32(3);
        float32_t sum = f32_add(one, two);
        float32_t product = f32_mul(sum, three);
        long result = f32_to_i32_r_minMag(product, false);
        printf("(1 + 2) * 3 = %ld\n", result);
        return 0;
    }

Compile and run the example as follows:

    mos-sim-clang -o example example.c -lbsoftfloat
    mos-sim example

As can be seen, it is a little awkward to use the floating-point
routines without compiler support.  Compiler support is in progress.

There are some more examples in the `examples` directory.

Original README
---------------

John R. Hauser<br>
2018 January 20


Berkeley SoftFloat is a software implementation of binary floating-point
that conforms to the IEEE Standard for Floating-Point Arithmetic.  SoftFloat
is distributed in the form of C source code.  Building the SoftFloat sources
generates a library file (typically `softfloat.a` or `libsoftfloat.a`)
containing the floating-point subroutines.


The SoftFloat package is documented in the following files in the `doc`
subdirectory:

* [SoftFloat.html](http://www.jhauser.us/arithmetic/SoftFloat-3/doc/SoftFloat.html) Documentation for using the SoftFloat functions.
* [SoftFloat-source.html](http://www.jhauser.us/arithmetic/SoftFloat-3/doc/SoftFloat-source.html) Documentation for building SoftFloat.
* [SoftFloat-history.html](http://www.jhauser.us/arithmetic/SoftFloat-3/doc/SoftFloat-history.html) History of the major changes to SoftFloat.

Other files in the package comprise the source code for SoftFloat.

