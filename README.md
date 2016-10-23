# Bride of ROMPUT
Bride of ROMPUT is a command-line utility designed for re-inserting modified internal files into the ROM image from which they were extracted.

Its name comes from the program ROMPUT, a GUI utility that served the same purpose and of which this utility is a clone.

## Compilation
To compile Bride of ROMPUT, navigate into the "source" directory and run the `make` command.  Similarly, a static binary can be compiled if needed by running the `make static` command in the "source" directory.

The Makefile doesn't currently include a target for building Windows executables.  A pre-compiled Windows binary can be found, however, in the "binaries" directory, along with pre-compiled dynamic and static Linux binaries.

## Usage
To use Bride of ROMPUT, run it with the following command structure:
```
bride_of_romput /path/to/ROM /path/to/file/to/insert insertion_offset
```

Note that the program is expecting the offset to be in hexadecimal.
