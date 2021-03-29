# char-module specifications
This module is fairly basic, however it is the first more complex of the series.
It allows a process in user-space to send messages to the module, which will answer back with a message telling how many characters it received.

## What do we implement
In this module four operations are implemented:
1. read
2. write
3. open
4. release

## Init function
The module's init function attempts to dynamically obtain a major number by calling *register_chrdev*, which is defined under linux/fs.h

## Notes on the syntax
1. C99 structure syntax is fancy, it allows to initialize only the important parts of the struct, leaving the rest initialized to 0. A variable is initialized just by prepending a "." to its name.
