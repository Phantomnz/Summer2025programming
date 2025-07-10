#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* categorytostring(Category c) {
    switch (c) {
        case ELECTRONICS: return "Electronics";
        case CLOTHING: return "Clothing";
        case FOOD: return "Food";
        case OTHER: return "Other";
        default: return "Unknown";
    }
}

void printItem(const Item *item){
    if (item == NULL) {
        printf("Item is NULL\n");
    } else{
    printf("ID: %d\n", item->id);
    printf("Name: %s\n", item->name);
    printf("Quantity: %d\n", item->quantity);
    printf("Price: %.2f\n", item->price);
    printf("Category: %s\n", categorytostring(item->category));
    }
}