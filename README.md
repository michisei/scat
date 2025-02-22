# Scat
A very small project that dumps file contents, character by character, with a specified delay in between them. 

This is mainly created to slow down the output speed for writing into devices.

## Compiling
### Prerequisites
This project requires `gcc` and `make` to be installed. 

On Windows, compiling with [Msys2](https://www.msys2.org/) is the most ideal, though not strictly necessary.
However, you do need to at least have [mingw-64](https://www.mingw-w64.org/) to compile the program. For mingw-64, you may need to replace `make` with `mingw32-make` for the build instructions using `make`.
### Building (Make)
To build, simply run 
```
make
```
After building, the executable should be inside the newly created `bin` folder.
**Hint**: You can clean the project with `make clean` or `mingw32-make -f makefile.mw clean`
### Building (Manual)
**Note**: This method is not recommended as it involves compiling each source file, and the information may be outdated as I may not be able to update the instructions here.
To build using `gcc` (without `make`), 
```
mkdir bin
gcc -O2 -Wall -Wpedantic -o bin/scat src/options.c src/os_utils.c src/slow_cat.c
```
Interestingly, this command works for both Windows and bash by coincidence, provided the `gcc` files are in your `PATH` environment variables.
## Usage
The usage of this tool is similar to how one typically use the `cat` command, just that this prints characters slower.

Unlike the `cat` tool, it has very little features other than customising the delay for each character printing.

## License
Since this is a tool that one can implement easily, there is no strict need to include license notices.

If your own implementation happen to exactly function like mine, you don't have to include the copyright notice.

If you want to use this specific work for derivative works, do have the courtesy to credit and include the copyright notice.
