# get_next_line

## Project Description

The **get_next_line** project is a fundamental exercise in the 42 curriculum that aims to implement a function capable of reading a line from a file descriptor. The `get_next_line` function returns a string containing a complete line, including the newline character (`\n`) if present, or `NULL` if the end of the file is reached or an error occurs.

This project teaches how to work with dynamic memory management, file descriptors, and string manipulation in C.

---

## Features

- Reads one line at a time from a file descriptor.
- Supports partial reads by using a static buffer to store leftover data between calls.
- Properly handles memory, freeing resources in case of errors or at the end of the reading process.

---

## Function Prototype

```c
char *get_next_line(int fd);
```

## Parameters
**fd**: The file descriptor to read from.

## Return Value

	A string containing the line read, including the newline character (\n) if present.
	NULL if the end of the file is reached or an error occurs.

## How It Works

**Static Buffer**: The function uses a static variable to store leftover data between successive calls.
**Block Reading**: Data is read from the file descriptor in chunks of size BUFFER_SIZE.
**Line Handling**:
	If a newline (\n) is found in the static buffer or the newly read block, the function returns the complete line.
	Otherwise, the data is concatenated to the static buffer, and the reading continues.
**End of File or Error**: If the read operation returns 0 (EOF) or -1 (error), the function properly handles memory and returns NULL.

## Included Files

get_next_line.c

Contains the implementation of the get_next_line function and its helper functions:

	ft_bytes: Handles memory and return values in case of EOF or error.
	ft_nl_tmp: Extracts a line from the static buffer when it contains a newline.
	ft_nl_buf: Extracts a line from the read buffer when it contains a newline.
	ft_append: Concatenates data to the static buffer.

get_next_line.h

Contains the prototype of the get_next_line function and declarations of the helper functions.

## How to Compile

To compile the project, include the get_next_line.c file along with a test file or the main program. For example:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 [get_next_line.c](http://_vscodecontentref_/0) main.c -o get_next_line
```

## Example Usage
```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Important Notes

- The buffer size (`BUFFER_SIZE`) can be defined at compile time using the `-D BUFFER_SIZE=<value>` flag.
- The function is designed to work only with **valid file descriptors**. It does not handle invalid or closed file descriptors.
- Always ensure to **free the memory** returned by `get_next_line` to prevent memory leaks.

---

## Learning Objectives

- Understand the use of **static variables** in C to maintain state between function calls.
- Learn how to **safely and efficiently manage dynamic memory** in C.
- Gain experience in implementing a **robust function** that interacts with the operating system through low-level system calls like `read`.

[Documentation for read] (https://man7.org/linux/man-pages/man2/read.2.html)