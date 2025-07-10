#include <stdlib.h> // for memory allocation functions like malloc, calloc, free, etc.
#include <stdio.h> // for standard input/output functions like printf, scanf, fopen, fclose, fread, fwrite, etc.
#include <string.h> // for string manipulation functions like strcpy, strlen, etc.
#include <ctype.h> // for character handling functions like isalpha, isdigit, etc.
#include <stdbool.h> // for bool type, true/false values
#include <fcntl.h> // for open, read, write, close
#include <unistd.h> // for read, write, close

// the c library provides FILE* streams for file operations. You open a file with fopen, and get a FILE* pointer.

// fwrite/fread are used for binary file operations. They read/write raw bytes from/to files.
// fprintf/fscanf are used for formatted text file operations. These will be showcased in main

// open/read/write/close are used for low-level file operations using file descriptors. They have finer control over file I/O and are more suitable for system-level programming.
// They are more efficient for large files or binary data, but less convenient for text files.
// abbreviations: fd = file descriptor, fp = file pointer, n = number of bytes read/written
// These functions are called POSIX functions, and are part of the POSIX standard for operating systems.

int main() {
    char buffer[1024]; // Buffer to hold file data

    FILE *fp = fopen("d16practice.txt", "r"); // Open the file for reading
    if (!fp){ // on failure, fopen returns NULL. You can inspect errno (from <errno.h>) for the error code/cause.
        perror("fopen failed");  // perror prints a descriptive error message to stderr based on the current value of errno
        return EXIT_FAILURE;
    }

    FILE *fp_out = fopen("output.txt", "w"); // Open another file for writing
    if (!fp_out) {
        perror("fopen output failed"); // If fopen fails, it returns NULL. We handle the error here.
        fclose(fp);
        return EXIT_FAILURE;
    }

    // Example of reading and writing using FILE* streams
    size_t n = fread(buffer, sizeof(char), sizeof(buffer), fp); // Read the file into a buffer
    if (n > 0) {
        fwrite(buffer, sizeof(char), n, fp_out); // Write the buffer to another file
    }

    fclose(fp); // Close the input file
    fclose(fp_out); // Close the output file

    // Example of POSIX file operations
    int fd = open("data.bin", O_RDONLY); // Open a file descriptor for reading
    if (fd == -1) { // on failure, open returns -1. You can inspect errno (from <errno.h>) for the error code/cause.
        perror("open failed");
        return EXIT_FAILURE;
    }
    ssize_t n_read = read(fd, buffer, sizeof(buffer)); // Read data from the file descriptor into a buffer
    // int fd_out = open("output2.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644); // Uncomment and use if you want to write to another file descriptor
    // if (fd_out != -1 && n_read > 0) {
    //     write(fd_out, buffer, n_read); // Write the buffer to another file descriptor
    //     close(fd_out);
    // }
    close(fd); // Close the file descriptor, always do this to release resources

    return EXIT_SUCCESS;
}
