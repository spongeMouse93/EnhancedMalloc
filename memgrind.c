#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mymalloc.h"

void testOne(){
    srand(time(NULL));
    clock_t start = clock();
    printf("=== Test: Insufficient Memory ===\n");
    char *ptr = (char *)mymalloc(1000 * sizeof(char), __FILE__, __LINE__);
    if (!ptr)
        printf("Memory allocation failed as expected.\n");
    else {
        printf("Unexpected memory allocation success.\n");
        myfree(ptr, __FILE__, __LINE__);
    }
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("This task took roughly %.5f seconds to complete.\n\n", time);
}

void testTwo(){
    srand(time(NULL));
    clock_t start = clock();
    printf("=== Test: Simple Allocation and Free ===\n");
    char *ptr = (char *)mymalloc(120, __FILE__, __LINE__);
    if (ptr) {
        for (int i = 0; i < 120; i++)
            ptr[i] = 'a' + i;
        printf("Allocated memory contains: %.*s\n", 120, ptr);
        myfree(ptr, __FILE__, __LINE__);
        printf("Memory freed successfully.\n");
    }
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("This task took roughly %.5f seconds to complete.\n\n", time);
}

void testThree(){
    srand(time(NULL));
    clock_t start = clock();
    printf("=== Test: Double Free ===\n");
    char *ptr = (char *)mymalloc(120, __FILE__, __LINE__);
    if (ptr) {
        myfree(ptr, __FILE__, __LINE__);
        myfree(ptr, __FILE__, __LINE__); 
    }
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("This task took roughly %.5f seconds to complete.\n\n", time);
}

void testFour(){
    srand(time(NULL));
    clock_t start = clock();
    printf("=== Test: Fragmentation ===\n");
    char *ptr1 = (char *)mymalloc(120, __FILE__, __LINE__), ptr2 = (char *)mymalloc(10, __FILE__, __LINE__);
    char *ptr3 = (char *)mymalloc(120, __FILE__, __LINE__);
    if (ptr1 && ptr2 && ptr3) {
        myfree(ptr1, __FILE__, __LINE__);
        myfree(ptr3, __FILE__, __LINE__);
        char *ptr4 = (char *)mymalloc(120, __FILE__, __LINE__);
        if (ptr4) {
            printf("Memory allocated successfully post fragmentation.\n");
            myfree(ptr2, __FILE__, __LINE__);
            myfree(ptr4, __FILE__, __LINE__);
        } else 
            printf("Memory allocation failed post fragmentation.\n");
        clock_t end = clock();
        double time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("This task took roughly %.5f seconds to complete.\n\n", time);
    }
}

void testFive(){
    srand(time(NULL));
    clock_t start = clock();
    printf("=== Test: Multiple Allocations ===\n");
    char *ptr1 = (char *)mymalloc(120, __FILE__, __LINE__), *ptr2 = (char *)mymalloc(20, __FILE__, __LINE__);
    char *ptr3 = (char *)mymalloc(60, __FILE__, __LINE__);
    if (ptr1 && ptr2 && ptr3) {
        sprintf(ptr1, "Systems");
        sprintf(ptr2, "Project");
        sprintf(ptr3, "One");
        printf("Allocated memory contains: %s, %s, %s\n", ptr1, ptr2, ptr3);
        myfree(ptr1, __FILE__, __LINE__);
        myfree(ptr2, __FILE__, __LINE__);
        myfree(ptr3, __FILE__, __LINE__);
        printf("Memory freed successfully.\n");
    }
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("This task took roughly %.5f seconds to complete.\n\n", time);
}

int main(){
    testOne();
    testTwo();
    testThree();
    testFour();
    testFive();
    return 0;
}
