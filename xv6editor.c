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

void write_file(int fd, char *content) {
    write(fd, content, strlen(content));
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
    printf(1, "\n-- Start typing (Ctrl+D to save and exit) --\n");
    int len = 0;
    while ((input[len++] = getchar()) != -1 && len < MAX_BUF) {}

    // Write the input to the file
    write_file(fd, input);

    // Close the file
    close(fd);

    exit();
}
