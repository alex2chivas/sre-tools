# log-parser

A CLI log parsing tool written in C that searches log files for keywords, similar to `grep`. Supports case-sensitive and case-insensitive search with a match count summary.

## Compile

```bash
gcc -o log-parser log-parser.c
```

## Usage

```bash
./log-parser <file> -s <keyword> [-i]
```

## Options

- `-s <keyword>` — Search for keyword in log file
- `-i` — Case insensitive search (optional)
- `-h, --help` — Show usage information

## Examples

```
sudo ./log-parser /var/log/syslog -s "warning"
Apr 26 00:00:32 jammy-venice systemd[1]: Window manager warning: ...
Apr 27 07:26:38 jammy-venice gnome-shell[4112]: Window manager warning: ...

--- 384 matches found ---

sudo ./log-parser /var/log/syslog -s "warning" -i
--- 3012 matches found ---
```

## Notes

Might need to run application as sudo to read system log files.

## What I learned

- Substring search with strstr and case-insensitive strcasestr
- GNU extensions with _GNU_SOURCE define
- Multiple flag handling with argc/argv
- File validation before processing
- Building a practical CLI tool modeled after grep
