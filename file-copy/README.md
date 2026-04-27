  CLI tool written in C that copies a source file to a destination, similar to the `cp` command. Includes source file validation and overwrite protection.

## Compile

```bash
gcc -o file-copy file-copy.c
```

## Usage

```bash
./file-copy <source> <destination>
./file-copy -h | --help
```

## Example

```
./file-copy sample-fleet.ips backup.ips
Copy done: backup.ips

./file-copy sample-fleet.ips backup.ips
You sure you want to over-ride the file?(y or n): y
Over-riding file....
Copy done: backup.ips
```

## Features

- Validates source file exists before copying
- Warns before overwriting an existing destination file
- Help flag support (-h, --help)

## What I learned

- File I/O with fopen, fgets, fprintf, fclose
- Error handling with NULL checks on file pointers
- Command line argument parsing with argc/argv
- String comparison with strcmp for flag detection
