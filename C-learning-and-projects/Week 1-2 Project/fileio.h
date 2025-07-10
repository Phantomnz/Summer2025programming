#ifndef FILEIO_H
#define FILEIO_H
#include <stdlib.h>
#include <stdio.h>
#include "item.h"

/*
Loads item from 'filename' into newly malloc'd array
on success: *arrayptr points to the array, *countPtr is set to, 
returns 0. On failure, returns non-zero value and *arrayptr= NULL
*/
int loadItems(const char *filename, Item **arrayPtr, int *countPtr);

/* Saves 'count' items from 'array' to 'filename'
Returns 0 on success, non-zero on failure    
*/
int saveItems(const char *filename, const Item *array, int count);

#endif // FILEIO_H