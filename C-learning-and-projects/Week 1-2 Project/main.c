#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "fileio.h"

int main(int argc, char *argv[]) {
    const char *filename = (argc >= 2) ? argv[1] : "items.dat"; // Default filename for items
    Item *items = NULL; // Pointer to dynamically allocated array of items
    int count = 0; // Number of items loaded
    // Example usage of the item and fileio functions
    int result = loadItems(filename, &items, &count); // Load items from file and store in items array
    if (result == 1){
        printf("No file found, starting with %d items.\n", count); // If no file is found, we start with a count of 2 items
    } else if (result == 0){
        printf("Loaded %d items successfully. \n", count); // If items are loaded successfully, print the count
    } else {
        printf("Error %d loading items\n", result); // If there is an error loading items, print the error code
    }

    while(1){
        int choice;
        printf("Inventory Menu:\n"); // Display the inventory menu
        printf("1. List all items\n"); // Placeholder for listing all items
        printf("2. Add new item\n"); // Placeholder for adding new item
        printf("3. Search by ID\n"); // Placeholder for other options
        printf("4. Update quantity\n");
        printf("5. Delete item\n");
        printf("Enter choice (1-5, 6 to exit): ");
        if (scanf("%d", &choice) != 1){ // Get user choice
            printf("Invalid input. Please enter a number between 1 and 6.\n"); //handle invalid input
            int c; while ((c = getchar()) != '\n' && c != EOF); // Clear the input buffer
            continue; // Skip to the next iteration
        } 
        switch (choice){
            case 1: // List all items
                if (count == 0){
                    printf("No items to display.\n"); // If no items are loaded, display this message
                    break; // Break out of the switch case
                 } else {
                    for (int i = 0; i < count; ++i){
                        printItem(&items[i]);
                    }
                 }
                break; // Break out of the switch case
            // Add new item
            case 2:
                Item newItem; // Declare a new item to be added
                printf("Enter new item details:\n"); // Prompt user for new item details
                printf("ID: "); // Prompt for item ID
                scanf("%d", &newItem.id); // Read item ID
                if (newItem.id <= 0) { // Validate item ID
                    printf("Invalid ID. Please enter a positive integer.\n"); // If ID is invalid, display this message
                    int c; while ((c = getchar()) != '\n' && c != EOF); // Clear the input buffer
                    break; // Break out of the switch case
                }
                getchar(); // Clear the newline character left in the input buffer after reading ID

                printf("Name: "); // Prompt for item name
                if (!fgets(newItem.name, sizeof newItem.name, stdin)) { perror("Error reading item name"); break; } // Handle error reading item name
                if (newItem.name[0] == '\n') { // Check if name is empty
                    printf("Name cannot be empty. Please enter a valid name.\n"); // If name is empty, display this message
                    break; // Break out of the switch case
                }
                newItem.name[strcspn(newItem.name, "\n")] = 0; // Remove trailing newline character


                printf("Quantity: "); // Prompt for item quantity
                scanf("%d", &newItem.quantity); // Read item quantity
                if (newItem.quantity <= 0) { // Validate item quantity
                    printf("Invalid quantity. Please enter a positive integer.\n"); // If quantity is invalid, display this message
                    int c; while ((c = getchar()) != '\n' && c != EOF); // Clear the input buffer
                    break; // Break out of the switch case
                }
                getchar(); // Clear the newline character left in the input buffer after reading quantity

                printf("Price: "); // Prompt for item price
                scanf("%f", &newItem.price); // Read item price
                if (newItem.price <= 0) { // Validate item price
                    printf("Invalid price. Please enter a positive value.\n"); // If price is invalid, display this message
                    int c; while ((c = getchar()) != '\n' && c != EOF); // Clear the input buffer
                    break; // Break out of the switch case
                }
                getchar(); // Clear the newline character left in the input buffer after reading price

                printf("Category (0: Electronics, 1: Clothing, 2: Food, 3: Other): "); // Prompt for item category
                int cat;
                scanf("%d", &cat); // Read item category
                newItem.category = (cat >= 0 && cat <= 3) ? (Category)cat : OTHER; // Validate category input
                
                //Expand the items array to accommodate the new item
                Item *temp = realloc(items, (count + 1) * sizeof *temp); // Reallocate memory for items array
                if (!temp){ perror("realloc failed"); break; } // Handle memory allocation failure
                items = temp; // Update items pointer to the newly allocated memory

                // Assign and save the new item
                items[count++] = newItem; // Add the new item to the items array
                if (saveItems("items.dat", items, count) != 0) { // Save items to file
                    printf("Error saving items to file.\n"); // If saving fails, display this message
                } else {
                    printf("Item added successfully.\n"); // If saving is successful, display this message
                }
                break; // Break out of the switch case

            case 3:
                int targetId;
                printf("Enter item ID to search: "); // Prompt user for item ID to search
                if (scanf("%d", &targetId) != 1) { // Read item ID
                    printf("Invalid input. Please enter a valid ID.\n"); // If input is invalid, display this message
                    int c; while ((c = getchar()) != '\n'&& c != EOF); // Clear the input buffer
                    break; // Break out of the switch case
                }

                //search loop
                int found = 0; // Flag to indicate if item is found
                for (int i =0; i < count; ++i){
                    if (items[i].id == targetId) { // Check if item ID matches
                        printf("Item found:\n"); // If item is found, display this message
                        printItem(&items[i]); // Print the found item
                        found = 1; // Set found flag to true
                        break; // Break out of the loop
                    }
                }
                if (!found) { // If item is not found
                    printf("Item with ID %d not found.\n", targetId); // Display this message
                }
                break; // Break out of the switch case

            case 4:
                // Update quantity of an item
                printf("Enter item ID to update quantity: "); // Prompt user for item ID to update quantity
                if (scanf("%d", &targetId)!= 1){ // Read item ID
                    printf("Invalid input. Please enter a valid ID.\n"); // If input is invalid, display this message
                    int c; while ((c = getchar()) != '\n'&& c != EOF); // Clear the input buffer
                    break; // Break out of the switch case
                }
                
                //find item to update
                int foundIndex = -1; // Initialize found index to -1
                for (int i = 0; i < count; ++i) { // Loop through items to find the item with the given ID
                    if (items[i].id == targetId) { // Check if item ID matches
                        foundIndex = i; // Set found index to current index
                        break; // Break out of the loop
                    }
                }
                if (foundIndex < 0) { // If item is not found
                    printf("No Item with ID %d exists.\n", targetId); // Display this message
                    break; // Break out of the switch case
                }

                // If item is found, prompt user for new quantity
                int newQty;
                printf("Enter new quantity for item ID %d: ", targetId); // Prompt user for new quantity
                if (scanf("%d", &newQty) != 1) { // Read new quantity
                    printf("Invalid input. Please enter a valid quantity.\n"); // If input is invalid, display this message
                    int c; while ((c = getchar()) != '\n'&& c != EOF); // Clear the input buffer
                    break; // Break out of the switch case
                }

                // Update and save the new quantity
                items[foundIndex].quantity = newQty; // Update the quantity of the found item
                if(saveItems("items.dat", items, count) != 0) { // Save items to file
                    printf("Error saving items to file.\n"); // If saving fails, display this message
                } else {
                    printf("Quantity updated successfully.\n"); // If saving is successful, display this message
                }
                break; // Break out of the switch case

            case 5:
                printf("Enter item ID to delete: "); // Prompt user for item ID to delete
                if (scanf("%d", &targetId) != 1) { // Read item ID
                    printf("Invalid input. Please enter a valid ID.\n"); // If input is invalid, display this message
                    int c; while ((c = getchar()) != '\n'&& c != EOF); // Clear the input buffer
                    break; // Break out of the switch case
                }

                int idx = -1; // Initialize index to -1
                for(int i = 0; i < count; ++i) { // Loop through items to find the item with the given ID
                    if (items[i].id == targetId) { // Check if item ID matches
                        idx = i; // Set index to current index
                        break; // Break out of the loop
                    }
                }
                if (idx < 0) { // If item is not found
                    printf("No Item with ID %d exists.\n", targetId); // Display this message
                    break; // Break out of the switch case
                }

                // shift items to delete the found item
                memmove(&items[idx], &items[idx + 1], (count - idx - 1) * sizeof(Item)); // Shift items to delete the found item
                count--; // Decrease the count of items

                // Shrink the items array
                Item *tmpd = realloc(items, count * sizeof *tmpd); // Reallocate memory for items array
                if (tmpd || count == 0) items = tmpd; // Update items pointer to the newly allocated memory if successful
                if (!tmpd && count > 0) { // If memory allocation fails and count is greater than 0
                    perror("realloc failed"); // Handle memory allocation failure
                    break; // Break out of the switch case
                }

                //persist the changes
                if(saveItems("items.dat", items, count) == 0){ // Save items to file
                    printf("Item with ID %d deleted successfully.\n", targetId); // If saving is successful, display this message
                } else {
                    printf("Error saving after deleting.\n"); // If saving fails, display this message
                }
                break;
            
            case 6: // Exit the program
                 // save items to file before exiting
                 saveItems("items.dat", items, count); // Save items to file
                 free(items); // Free the dynamically allocated memory for items
                    printf("Exiting program.\n");
                    return 0; // Exit the program
            
            default: // Handle invalid choice
                printf("Invalid choice. Please enter a number between 1 and 6.\n"); // If the choice is invalid, display this message
                break; // Break out of the switch case
        }
    }

    free(items); // Free the dynamically allocated memory for items

    return 0;
}
// End of main function
