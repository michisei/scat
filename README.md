# Scat
A very small project that dumps file contents, character by character, with a specified delay in between them. 

This is mainly created to slow down the output speed for writing into devices.

## Compiling
### Prerequisites
This project requires `gcc` and `make` to be installed. 

On Windows, you may need Msys2 for now, or, if you know how, edit the makefile to allow it to compile with MinGW64.
### Building
To build, simply run 
```
make
```
After building, the executable should be inside the newly created `bin` folder.

## Usage
The usage of this tool is similar to how one typically use the `cat` command, just that this prints characters slower.

Unlike the `cat` tool, it has very little features other than customising the delay for each character printing.

## Licence
Since this is a tool that one can implement easily, there is no strict need to include licence notices.

If your own implementation happen to exactly function like mine, you don't have to include the copyright notice.

If you want to use this specific work for derivative works, do have the courtesy to credit and include the copyright notice.
