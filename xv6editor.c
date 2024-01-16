// xv6editor.c
#include "types.h"
#include "user.h"
#include "fcntl.h"

#define MAX_BUF 1024

void read_file(int fd) {
    char buf[MAX_BUF];
    int n;

    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        write(1, buf, n);  // write to stdout (console)
    }
}

void write_file(int fd, char *content, int size) {
    write(fd, content, size);
}

void backspace(char *input, int *len) {
    if (*len > 0) {
        (*len)--;
        // Move the cursor back on the console
        write(1, "\b", 1);
        // Print a space to erase the character on the console
        write(1, " ", 1);
        // Move the cursor back again to the original position
        write(1, "\b", 1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(2, "Usage: %s filename\n", argv[0]);
        exit();
    }

    char *filename = argv[1];
    int fd;

    // Open the file for reading and writing
    if ((fd = open(filename, O_RDWR)) < 0) {
        // If the file doesn't exist, create it
        fd = open(filename, O_CREATE | O_RDWR);
        if (fd < 0) {
            printf(2, "Error: Cannot open or create file %s\n", filename);
            exit();
        }
    }

    // Display the current content of the file
    read_file(fd);

    // Allow the user to input text
    char input[MAX_BUF];
    int len = 0;
    char c;
    printf(1, "\n-- Start typing (Ctrl+D to save and exit) --\n");
    while (1) {
        if (read(0, &c, 1) == 0) {
            // End of file (Ctrl+D)
            break;
        }

        // Check for the backspace key (ASCII value 127)
        if (c == 127) {
            backspace(input, &len);
        } else if (c == 9) {
            // Insert a tab character
            if (len < MAX_BUF - 1) {
                input[len++] = c;
                write(1, "\t", 1); // Display the tab on the console
            }
        } else {
            // Insert the character
            if (len < MAX_BUF - 1) {
                input[len++] = c;
            }
        }
    }
    input[len] = '\0'; // Null-terminate the string

    // Write the input to the file
    write_file(fd, input, len);

    // Close the file
    close(fd);

    printf(1, "\n");

    exit();
}
