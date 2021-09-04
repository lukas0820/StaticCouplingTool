## Using the analyser
### Requirements
Following packages have to be installed:
- cmake
- clang
- libclang-dev
- qt5-default
- ninja-build
### Build Project
Example build with Ninja:

    $ mkdir build && cd build
    $ cmake -G Ninja .. && ninja
Alternatively, the project can also be build with another cmake generator than Ninja, then Ninja has to be replaced in the command above and ninja-build is not a requirement any more
### Execute
The analyser can be executed within the build folder with:

    $ ./static-coupling-analyser

For help with configuration options use:

    $ ./static-coupling-analyser --help