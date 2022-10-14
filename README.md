# copesh

> **Note**
> Make sure you run `copesh` from its source directory. You can consider shifting all the binaries to `/bin` and changing the value of permaPath in `copesh.c` to `/bin`. This will allow you to run copesh from anywhere.

## Setup
```bash
git clone https://github.com/sociallyencrypted/copesh.git
cd copesh
make
```

## Usage
```bash
copesh
```

## Commands
- `cd` - Change directory
  - Options:
    - `-L` - Follow symbolic links
    - `-P` - Do not follow symbolic links
  - Usage:
    - `cd [-l|-P] <directory>`
- `pwd` - Print working directory
  - Options:
    - `-L` - Follow symbolic links
    - `-P` - Do not follow symbolic links
  - Usage:
    - `pwd [-l|-P] <directory>`
- `date` - Print date
  - Options:
    - `-u` - Print UTC time
    - `-r <seconds>` - Print the time after the given number of seconds since the epoch
  - Usage:
    - `date [-u] [-r <seconds>]`
- `ls` - List files
  - Options:
    - `-a` - List all files
    - `-R` - List files recursively
  - Usage:
    - `ls [-a] [-R] <directory>`
- `mkdir` - Make directory
  - Options:
    - `-p` - Create parent directories as needed
    - `-m <mode>` - Set permissions of the directory
  - Usage:
    - `mkdir [(-m/--mode)=<mode>] [-p] <directory>`
- `rm` - Remove file
  - Options:
    - `d` - Remove directories
    - `-r` - Remove directories recursively
  - Usage:
    - `rm [-d] [-r] <file>`
- `echo` - Print text
  - Options:
    - `--help` - Print help
    - `-n` - Do not print a newline at the end
  - Usage:
    - `echo [-n] <text>`
- `cat` - Concatenate files
  - Options:
    - `-s` - Remove repeated empty lines
    - `-n` - Print line numbers
  - Usage:
    - `cat [-s] [-n] <file>`
- `help` - Print help
- `exit` - Exit shell

## Errors Handled
- Invalid command
- Fork Error
- Invalid Options passed to commands
- Invalid number of arguments passed to commands