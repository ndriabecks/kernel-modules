# Rootkit
This is a toy rootkit to better understand what can be done with kernel modules, and how malicious users can gain control over the machine.

## Features
- The rootkit's process is hidden
- Hide other processes
- Create/Delete files
- Exfiltrate data over the network

## Architecture
The rootkit is constituted by a kernel module which can be loaded and unloaded with the shell commands insmod and rmmod. It is completely harmless, since it acts on your will.

## Implementation details