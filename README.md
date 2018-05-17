# TAlg

Templated C++ Linear Algebra Library (C++11/14)

## Overview

This library is intended to compensate for the lack of standardized linear algebra library for C++.

It is targeted to basic computational, graphics and game programming use-case rather than full blown numerical library.


## Design Goals

* support of oppaque types for easy integration with C code (e.g. OpenGL/OpenCL)
* expressive
* rich type safety
* performant/efficient as well as safe (exception) interfaces
* pragmatic first, math'pure' second (e.g. 4x4 * 3x1 is allowed)
* support only modern C++11/14/17 (NOT C++98 compatible)

## Other alternatives

GLM : https://github.com/g-truc/glm

## Other full-blown Numerical templated libraries:

Armadilo: http://arma.sourceforge.net/docs.html#syntax
Blaze : https://bitbucket.org/blaze-lib/blaze
