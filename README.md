[![Coverage Status](https://coveralls.io/repos/github/ndriabecks/kernel-modules/badge.svg?branch=main)](https://coveralls.io/github/ndriabecks/kernel-modules?branch=main)

# Kernel-modules
Kernel-modules contains several kernel modules that can be used to study the basis of modules programming.

## hello-module
Hello module is a really basic module. Learned arguments:
- Basic module structure
- Create a parameter and pass it to the module
- Obtaining the module's PID
- Print messages on the dmesg

## oops-module
This module generates a kernel oops. Not very useful, just use dmsg after to see the red lines.

## char-module
This is the first useful module, it implements a message passing mechanism between user space applications and the kernel.
It will receive messages from a user space application, count the number of characters received, and send it back as an answer to the user-space process. This module has an extra README in its folder, for it is full of details.

**Remember**:
- Character devices are identified by a prependend 'c', when listing them.
- Each character device is associated with a **Major** and a **minor** number. The first is used to know which driver must be used, the latter is used internally in the driver.
- The **file_operations** data structure must be filled with the correct values corresponding to the operations that we want to implement.

For more information, check the readme inside the char-module folder.
