#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

bool noCommonDivisors(int subset[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (gcd(subset[i], subset[i + 1]) != 1) {
            return false;
        }
    }
    return true;
}

int calculateSum(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

void printSubset(int subset[], int size, FILE *outfile) {
    fprintf(outfile, "Set = { ");
    for (int i = 0; i < size; i++) {
        fprintf(outfile, "%d ", subset[i]);
    }
    fprintf(outfile, "} -> Sum = %d\n", calculateSum(subset, size));
}

void findValidSubsets(int input[], int size, int subset[], int subsetSize, int index, FILE *outfile) {
    if (index == size) {
        if (subsetSize >= 2 && 
            isPrime(calculateSum(subset, subsetSize)) && 
            noCommonDivisors(subset, subsetSize)) {
            printSubset(subset, subsetSize, outfile);
        }
        return;
    }
    
    findValidSubsets(input, size, subset, subsetSize, index + 1, outfile);
    
    subset[subsetSize] = input[index];
    
    bool canInclude = true;
    if (subsetSize > 0) {
        if (gcd(subset[subsetSize - 1], input[index]) != 1) {
            canInclude = false;
        }
    }
    
    if (canInclude) {
        findValidSubsets(input, size, subset, subsetSize + 1, index + 1, outfile);
    }
}

int main() {
    int num = 0;
    FILE *infile, *outfile;
    char infilename[100];
    char outfilename[100];
    
    scanf("%d", &num);
    
    // Create input filename and open for writing
    sprintf(infilename, "testCase/case%d/%d.in", num, num);
    infile = fopen(infilename, "w");

    
    // Create output filename and open for writing
    sprintf(outfilename, "testCase/case%d/%d.out", num, num);
    outfile = fopen(outfilename, "w");
    
    int size = 0;
    scanf("%d", &size);
    fprintf(infile, "%d\n", size);
    
    int* numbers = (int*)malloc(size * sizeof(int));
    if (numbers == NULL) {
        printf("Memory allocation failed\n");
        fclose(infile);
        fclose(outfile);
        return 1;
    }
    
    for (int i = 0; i < size; i++) {
        scanf("%d", &numbers[i]);
        fprintf(infile, "%d ", numbers[i]);
    }
    
    int* subset = (int*)malloc(size * sizeof(int));
    if (subset == NULL) {
        printf("Memory allocation failed\n");
        free(numbers);
        fclose(infile);
        fclose(outfile);
        return 1;
    }
    
    // Find and write valid subsets to output file
    findValidSubsets(numbers, size, subset, 0, 0, outfile);
    
    // Close files and free memory
    fclose(infile);
    fclose(outfile);
    free(numbers);
    free(subset);
    
    printf("Processing complete. Results written to %s\n", outfilename);
    
    return 0;
}