#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int x = 5;
int *p = &x; //p is a pointer to x
int arr[5] = {1,3,5,7,9}; //an array of integers
int *q = arr; //q is a pointer to the first element of arr
int *t = NULL; //t is a pointer to nothing (NULL)
// a pointer not initialized should be NULL to avoid undefined behavior
//an array name can be used as a pointer to its first element
int array[5] = {1,3,5,7,9}; //another array of integers
array[2] == *(array + 2); //this is equivalent to accessing the third element of the array

int main(){
    printf("p and x = %d\n", *p); //print the value pointed to by p, which is x = 5
    printf("q and arr[0] = %d\n", *q); //print the value pointed to by q, which is arr[0] = 1
    q++; //increment q to point to the next element in arr
    printf("q and arr[1] = %d\n", *q); //print the value pointed to by q, which is arr[1] = 3
    q++;
    q++;
    printf("q and arr[3] = %d\n", *q); //print the value pointed to by q, which is arr[3] = 7
    printf("array[2] = %d\n", array[2]); //print the third element of array, which is 5
    return 0;
}