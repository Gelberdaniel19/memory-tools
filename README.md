# Linux Memory Scanner

For now this is a learning experience. This is where I will try to grow and expand on a series of tests regarding reading and writing to an application's memory on Linux.

# Setup

At the current time, this program is not intended to be run on anyone else's machine. That being said, if you would like to compile and run it, follow these instructions:

- Find the process ID of an app you want to scan. This can be accomplished with the GUI based system monitor, or you can run the command `ps -A` to get a list of running processes.
- Edit `#define PID xxxx` at the top of `driver.c`, chaning the xxxx to your PID.
- Compile and run the program with `sudo make`. Sudo is necessary to attach ptrace to a PID that is not directly connected to this program.

## Short Term Goals

* [x] Get a memory region from /proc/$PID/maps in integer format
* [x] Get some sort of output from reading a memory address
* [x] Read an entire memory region from /proc/$PID/mem using a buffer
* [x] Read an entire memory region as I32
* [ ] Replace the array of values with an array of structs containing an address and value
* [ ] Read an entire memory region as I8, I16, I32, I64, float, double
* [ ] Get list of all memory regions as a struct
* [ ] Scan all memory regions for any data type