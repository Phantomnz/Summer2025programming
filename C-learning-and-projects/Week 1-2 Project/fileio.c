#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"


int loadItems(const char *filename, Item **arrayPtr, int *countptr){ // Loads items from a file into a dynamically allocated array
    FILE *fp = fopen(filename, "rb"); // Open the file in binary read mode
    if (!fp) {
        *arrayPtr = NULL;
        return 1; // no file yet is ok
    }
    fseek(fp, 0, SEEK_END); // Move the file pointer to the end of the file
    long size = ftell(fp); // Get the size of the file
    rewind(fp); // Move the file pointer back to the beginning of the file
    int count = size / sizeof(Item); // Calculate the number of items in the file
    Item *arr = malloc(count * sizeof(Item)); // Allocate memory for the items
    if (!arr) { fclose(fp); return -1;}// Check if memory allocation was successful
    if (fread(arr, sizeof(Item), count, fp) != (size_t)count) { // Read the items from the file
        free(arr); // Free the allocated memory if reading failed
        fclose(fp); // Close the file
        return -2; // Return an error code
    }
    fclose(fp); // Close the file
    *arrayPtr = arr; // Set the output pointer to the allocated array
    *countptr = count; // Set the output count to the number of items read
    return 0; // Return success
}

int saveItems(const char *filename, const Item *array, int count) { // Saves items to a file from a dynamically allocated array
    FILE *fp = fopen(filename, "wb"); // Open the file in binary write mode
    if (!fp) {
        return -1; // Return an error code if the file could not be opened
    }
    if (fwrite(array, sizeof(Item), count, fp) != (size_t)count) { // Write the the items to the file but check if the write was successful
        fclose(fp); // Close the file
        return -2; // Return an error code if writing failed
    }
    fclose(fp); // Close the file
    return 0; // Return success
}