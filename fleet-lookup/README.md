# fleet-lookup

A CLI tool written in C that parses a space-delimited device inventory file, displays all devices, and provides case-insensitive search by CHID.

## Compile

```bash
gcc -o fleet-lookup fleet-lookup.c
```

## Usage

```bash
./fleet-lookup <filename>
```

## Example

```
./fleet-lookup sample-fleet.ips
MJID: 4201  CHID: TH80  IP: 10.5.22.101
MJID: 4202  CHID: TH79  IP: 10.5.22.103
MJID: 4203  CHID: TH77  IP: 10.5.23.45
...
Want to search for CHID? (y or n): y
Enter CHID: h450
MJID: 4210  CHID: H450  IP: 10.5.22.200
```

## Sample data

`sample-fleet.ips` is included with 20 rows of generated test data.

## What I learned

Concepts applied:

- Structs and arrays of structs
- Pointers, malloc, and free (heap memory management)
- File I/O with fopen, fgets, fclose
- String parsing with strtok
- Command line arguments with argc/argv
- Case-insensitive string comparison with strcasecmp
