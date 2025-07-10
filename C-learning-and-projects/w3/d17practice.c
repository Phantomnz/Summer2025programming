#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Original struct buffer was defined inside func; move it to file scope so it can be reused:
struct buffer {
    size_t length; // size_t is an unsigned integer type used for sizes and counts
    char data[];   // flexible array member (FAM)
    // Flexible array members allow the last member of a struct to be an array with no specified size, enabling dynamic allocation.
};

// Comparator for qsort/bsearch on array of strings.
// ADDED: must be at file scope (C does not support nested functions in standard C).
static int cmp_str(const void *a, const void *b) {
    const char *const *sa = a;
    const char *const *sb = b;
    return strcmp(*sa, *sb);
}

void func(int n){
    int arr[n]; // variable length array (VLA)
    // Variable length arrays are arrays whose size is determined at runtime, not compile time.

    // ADDED: Example usage of arr to avoid unused-warning and demonstrate functionality:
    for(int i = 0; i < n; i++){
        arr[i] = i * i; // initialize arr with some values
    }
    // ADDED: print the VLA contents:
    printf("func: VLA contents:");
    for(int i = 0; i < n; i++){
        printf(" %d", arr[i]);
    }
    printf("\n");

    // ADDED: Example usage of flexible array member struct:
    size_t needed = n * sizeof(int);
    struct buffer *bufp = malloc(sizeof(*bufp) + needed);
    if (!bufp) {
        perror("malloc in func"); // handle allocation failure
        return;
    }
    bufp->length = needed;
    // Initialize data (for example, zero it):
    memset(bufp->data, 0, needed);
    // ... you could fill bufp->data with meaningful bytes here ...
    // ADDED: free when done
    free(bufp);
}

int main(void) {
    // ORIGINAL: char buf[10];
    // NOTE: increased size to safely hold "value: 42" plus NUL. If you keep 10, it's enough for "value: 42" (9 chars + NUL),
    // but giving a bit more headroom is often safer if you change the format later.
    char buf[32];
    snprintf(buf, sizeof(buf), "value: %d", 42); // snprintf formats and stores a string in buf
    // sprintf(buf) writes formatted output into a buffer without bounds checking (risk of buffer overflow).
    // snprintf() is safer as it limits the number of characters written to the buffer, using a size parameter.

    // ADDED: print the formatted buffer so that something appears on stdout:
    printf("Formatted buffer: %s\n", buf);

    // ORIGINAL demonstration of qsort/bsearch on buf is not meaningful; instead, show a meaningful example on strings.
    // For reference, here are the original lines (commented out):
    #if 0
    qsort(buf, sizeof(buf), sizeof(buf[0]), (int (*)(const void *, const void *))strcmp); // qsort sorts the buffer using strcmp as the comparison function
    bsearch("value: 42", buf, sizeof(buf), sizeof(buf[0]), (int (*)(const void *, const void *))strcmp); // bsearch performs a binary search on the buffer
    #endif
    // qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) for generic array sorting.
    // bsearch(void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) for binary searching in sorted arrays.
    // NOTE: Above is left commented to preserve your example, but this usage is invalid (strcmp expects NUL-terminated strings, not single chars).

    // ADDED: Meaningful example: sort/search an array of strings
    const char *arr[] = {"banana", "apple", "cherry"};
    size_t n_str = sizeof(arr) / sizeof(arr[0]);
    printf("Before qsort:\n");
    for (size_t i = 0; i < n_str; i++) {
        printf("  %s\n", arr[i]);
    }
    qsort(arr, n_str, sizeof(arr[0]), cmp_str); // sort array of strings
    printf("After qsort:\n");
    for (size_t i = 0; i < n_str; i++) {
        printf("  %s\n", arr[i]);
    }
    // ADDED: bsearch example:
    const char *key = "apple";
    char * const *res = bsearch(&key, arr, n_str, sizeof(arr[0]), cmp_str);
    if (res) {
        printf("Found '%s' in sorted array.\n", *res);
    } else {
        printf("Did not find '%s'.\n", key);
    }

    // ORIGINAL had:
    // FILE *fp = NULL;
    // fseek(fp, 0, SEEK_END); // go to file end
    // long sz = ftell(fp); // get file size
    // fseek(fp, 0, SEEK_SET); // go back to start
    // char *buffer = malloc(sz + 1); // allocate memory for the buffer
    // if (buffer == NULL) {
    //     perror("Failed to allocate memory");
    //     return EXIT_FAILURE; // handle memory allocation failure
    // }
    // NOTE: Above is invalid because fp is NULL. We must fopen first.

    // ADDED: Open a real file. Change "input.txt" to whatever file you want to read.
    const char *filename = "input.txt";
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("fopen"); // handle file open error
    } else {
        // fseek(fp, 0, SEEK_END); // go to file end
        if (fseek(fp, 0, SEEK_END) != 0) {
            perror("fseek to end");
        } else {
            long sz = ftell(fp); // get file size
            if (sz < 0) {
                perror("ftell");
            } else {
                // fseek(fp, 0, SEEK_SET); // go back to start
                if (fseek(fp, 0, SEEK_SET) != 0) {
                    perror("fseek to start");
                } else {
                    char *filebuf = malloc(sz + 1); // allocate memory for the buffer
                    if (filebuf == NULL) {
                        perror("Failed to allocate memory");
                        fclose(fp);
                        return EXIT_FAILURE; // handle memory allocation failure
                    }
                    size_t nread = fread(filebuf, 1, sz, fp); // read file contents
                    if (nread != (size_t)sz) {
                        if (ferror(fp)) {
                            perror("fread");
                        }
                        // We can still proceed with what was read
                    }
                    filebuf[nread] = '\0'; // null-terminate if treating as string
                    // ADDED: print file content
                    printf("Read %zu bytes from '%s':\n", nread, filename);
                    // To avoid huge output if file is large, you might want to limit printing:
                    printf("%s\n", filebuf);
                    free(filebuf);
                }
            }
        }
        fclose(fp);
    }

    // ADDED: demonstrate calling func to show VLA and flexible array member usage:
    func(5);

    return 0; // ADDED: explicit return from main
}
