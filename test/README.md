Simple shell Project:

This is an ALX collaboration project on Shell between Aregbesola Bright & Oluwafunshoalice

Written with:
C language
Shell
Betty linter
General Requirement:

*All files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
All files should end with a new line
A README.md file, at the root of the folder of the project is mandatory
Use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
Shell should not have any memory leaks
No more than 5 functions per file
All header files should be include guarded
Write a README with the description of the project

Description:
Aregbesola Bright & Oluwafunshoalice Shell is a simple UNIX command interpreter that replicates functionalities of the simple shell (sh). Additional functions are also included. This program was written entirely in C as a milestone project for ALX Africa Software Engineering.

Installation
Clone this repository into your working directory. For best results, files should be compiled with GCC and the following flags: -Wall -Wextra -Werror -pedantic -std=gnu89

Usage
After compilation, the resulting program can run stand-alone, either in interactive or non-interactive mode.

Interactive Mode
In interactive mode, simply run the program and wait for the prompt to appear. From there, you can type commands freely, exiting with either the "exit" command or ctrl-D.

Non-Interactive Mode
In non-interactive mode, echo your desired command and pipe it into the program like this:

echo "ls" | ./shell
In non-interactive mode, the program will exit after finishing your desired command(s).

Included Built-Ins
Our shell has support for the following built-in commands:

Command	Definition
exit [n]	Exit the shell, with an optional exit status, n.
env	Print the environment.
setenv [var][value]	Set an environment variable and value. If the variable exists, the value will be updated.
unsetenv [var]	Remove an environment variable.
cd [dir]	Change the directory.
help [built-in]	Read documentation for a built-in.
Credits:

All code written by Aregbesola Bright & Oluwafunshoalice

Authors
👤 Whyte_Bryte
👤 Oluwafunshoalice

Whyte_Bryte & Funshoalice @ ALX software engineering programme 2022.
