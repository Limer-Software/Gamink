# Gamink
A paint program written in C++ using GTK4.

## Installation

### Debian/Ubuntu based systems:

First install the dependencies:
```bash
sudo apt install build-essential libgtk-4-dev
```

Then build the project:
```bash
./build.sh
```

To build and run the project:
```bash
./test.sh
```

### Windows users:

Install [MSYS2](https://www.msys2.org/) and run the following commands in the MSYS2 terminal:
```bash
pacman -S mingw-w64-x86_64-gtk4 mingw-w64-x86_64-toolchain
```

Then build the project:
```bash
./build.sh
```

To build and run the project:
```bash
./test.sh
```
