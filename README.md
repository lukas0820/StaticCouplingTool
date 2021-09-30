## Using the analyser
### Requirements
Following packages have to be installed:
- cmake
- clang-12
- libclang-12-dev
- qt5-default
- make
### Build Project
Example build with make:

    $ mkdir build && cd build
    $ cmake -G "Unix Makefiles" .. && make
### Execute
The analyser can be executed within the build folder with:

    $ ./StaticCouplingTool

For help with configuration options use:

    $ ./StaticCouplingTool --help
