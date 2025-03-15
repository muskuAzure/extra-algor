#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_numbers(FILE *fptr, int n) {
    for (int i = 0; i < n; i++) {
        fprintf(fptr ,"%d\n", (rand() % 100) + 1);
    }
}

int main() {
    FILE *fptr;
    fptr = fopen("temp.txt", "w");

    int ee;
    scanf("%d\n", &ee);

    int n;
    // printf("Enter how many numbers to generate: ");
    scanf("%d\n", &n);

    // Seed random number generator
    srand(time(NULL));
    
    fprintf(fptr ,"%d\n", ee);
    fprintf(fptr ,"%d\n", n);
    generate_numbers(fptr, n);

    fclose(fptr);
    
    return 0;
}
