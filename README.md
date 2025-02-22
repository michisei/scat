# Scat
A very small project that dumps file contents, character by character, with a specified delay in between them. 

This is mainly created to slow down the output speed for writing into devices.
## Compiling
### Prerequisites
This project requires Java Development Kit (JDK) (Recommended version above 21) and `make` (yes I know `make` is not a Java thing) to be installed. 

Installing JDK can be quite a convoluted process, especially on Windows. If you're into Java projects, you should know what to do. If not, you can search online on how to install JDK 21 and include the executable into your PATH folder.

On Windows, you can download MinGW to use make, or even better, Msys2.
### Building (Make)
To build, simply run 
```
make
```
After building, the executable should be inside the newly created `bin` folder.
### Building (Manual)
You can also manually use JDK commands to manually build the project. The project only consists of two files in the `src` folder. You first run the `javac` command to compile the `.java` files:
```
mkdir build
mkdir build/SlowCat
javac -cp build -d src src/SlowCat/*
```
**NOTE**: The above commands is to mimic the behaviour of what `make` would do. Interestingly the commands work both in bash and in windows `cmd`.

After the `javac` commands are completed, you can run the following commands to create the jar file:
```
mkdir bin
jar cfe bin/scat.jar SlowCat/SlowCat -C build SlowCat/SlowCat.class -C build SlowCat/Options.class
```
(The above command may be outdated if I decided to add more files.)
### Cleanup
Simply delete the `bin` and `build` folders.
## Usage
The usage of this tool is similar to how one typically use the `cat` command, just that this prints characters slower.

Unlike the `cat` tool, it has very little features other than customising the delay for each character printing.
## Licence
Since this is a tool that one can implement easily, there is no strict need to include licence notices.

If your own implementation happen to exactly function like mine, you don't have to include the copyright notice.

If you want to use this specific work for derivative works, do have the courtesy to credit and include the copyright notice.
