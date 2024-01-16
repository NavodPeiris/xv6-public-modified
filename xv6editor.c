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

        // Check for the tab key (ASCII value 9)
        if (c == 9) {
            // Insert a tab character
            if (len < MAX_BUF - 1) {
                input[len++] = '\t';
                putchar('\t'); // Display the tab on the console
            }
        } else {
            // Insert the character
            if (len < MAX_BUF - 1) {
                input[len++] = c;
                putchar(c); // Display the character on the console
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
