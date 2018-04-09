# System Info Tool

This is a C++ command-line utility for displaying system information, similar to `htop` or `neofetch`.
It supports both normal and interactive ncurses display modes and includes some fun features like an ASCII cat.

## Features
- Display system hostname
- Display current time information
- Display CPU information
- Display RAM information
- Display network information
- Display operating system information
- Optional ncurses mode for dynamic display
- Display an ASCII cat

## Usage
```
./sys_info [-lhtcrnao]
```

### Flags
- `-l` : Enable ncurses mode
- `-h` : Display hostname
- `-t` : Display time information
- `-c` : Display CPU information
- `-r` : Display RAM information
- `-n` : Display network information
- `-a` : Display ASCII cat
- `-o` : Display OS information
- `--help` : Print usage information

If no flags are provided, the program displays all information by default.
If `-l` is used alone, it enables ncurses mode and displays all information.
