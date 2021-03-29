# char-module specifications
This module is fairly basic, however it is the first more complex of the series.
It allows a process in user-space to send messages to the module, which will answer back with a message telling how many characters it received.

Check yourself! After loading the module, in dmesg, succes/failure messages will appear.
Furthermore, a new device will be created under /dev/chrdev.

## Testing the module
```sh
make
./mount.sh
ls /dev/AAchardev
./umount.sh
dmesg
```
With ls the existence of the module can be verified, while with dmesg the debug messages can be read in the kernel message buffer.

After that run `gcc -o test chartest.c & ./test` to send a message to the module and see it at work!

## What do we implement
In this module four operations are implemented:
1. read
2. write
3. open
4. release

### Open()


## Init function
The module's init function attempts to dynamically obtain a major number by calling *register_chrdev*, which is defined under linux/fs.h

## Notes on used functions
1. The printing functions are defined under linux/printk.h, usage of pr_*level* is preferred because occupies less columns and augments code readability.
2. Error handling has been done through goto statements. It is clearer and reduces code duplication. However, more attention had to be taken wrt the variables containing the errors.

## Notes on the syntax
1. C99 structure syntax is fancy, it allows to initialize only the important parts of the struct, leaving the rest initialized to 0. A variable is initialized just by prepending a "." to its name.
2. 