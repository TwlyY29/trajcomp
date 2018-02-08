# trajcomp
Trajectory Computing Library

# Installing for R
The trajectory computing library is a set of C++ headers. Additionally, there is an R library.

The R library depedns on some packages and you can prepare your system with

    sudo R --no-save < InstallDependencies.R
    sudo make
   
This will pull all needed packages before compiling and installing the library.


# Using C++ headers
You can just copy the header directory from trajcomp/r-package/trajcomp/src/trajcomp to /usr/include
and use it in all your C++ projects.


# Compile Python Bindings
After trajcomp header directory is copied to /usr/include, you can compile bindings for python3.
At the moment, there are only bindings for trajcomp/bloomfilter.

To compile the python3 bindings, do the following:

    cd python-bindings
    sudo make python3

In python-bindings/tests are a few examples of how to use the python3-version of trajcomp.

It requires Boost and Boost.Python. Make sure to adjust installation directories at the top of the Makefile.
