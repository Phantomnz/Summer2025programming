#ifndef ITEM_H
#define ITEM_H
#include <stdlib.h>
#include <stdio.h>
typedef enum { // Category enum to represent different item categories
    ELECTRONICS,
    CLOTHING,
    FOOD,
    OTHER
} Category;

typedef struct { // Item struct to represent an Item with its properties
    int id;
    char name[51];
    int quantity;
    float price;
    Category category;
} Item;

const char *categorytostring(Category c); // Function to convert Category enum to string representation
void printItem(const Item *item); // Function to print the details of an Item

#endif // ITEM_H

