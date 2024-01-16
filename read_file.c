// read_file.c
#include "types.h"
#include "user.h"
#include "fcntl.h"

#define MAX_BUF 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(2, "Usage: %s filename\n", argv[0]);
        exit();
    }

    char *filename = argv[1];
    int fd;

    // Open the file for reading
    if ((fd = open(filename, O_RDONLY)) < 0) {
        printf(2, "Error: Cannot open file %s for reading\n", filename);
        exit();
    }

    // Read and display content from the file
    char buf[MAX_BUF];
    int n;

    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        write(1, buf, n); // write to stdout (console)
    }

    // Close the file
    close(fd);

    printf(1, "\n");

    exit();
}
