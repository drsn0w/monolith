# Monolith
Monolith is an experimental (and probably very unsafe) monolithic binary replacement for coreutils.

## General
Monolith is a monolithic binary that can perform multiple functions. A-la busybox, Elements (applets) can be run by invoking the monolith binary, or by renaming/symlinking the monolith binary to the desired function.

## Elements
Currently the following Elements are implemented:
- `cat`: Prints the contents of a file to standard output (very basic state)
- `dir`: Lists the contents of a directory (very basic state)
- `du`: Lists files and the space they take on disk (very basic state)

## Building
Monolith is designed to only require the standard C++ libraries from C++23. To build Monolith, use cmake:
```
cmake CMakeLists.txt -B build/
cd build/
make
```
At the current stage, Monolith's build system will not install itself. It's up to you to place it where you want it and create the symlinks you want.

## Notes
- This is a project for fun, and for me to learn C++. Please don't even consider using it anywhere important!
