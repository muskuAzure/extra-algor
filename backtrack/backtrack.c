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

void printSubset(int subset[], int size) {
    printf("Set = { ");
    for (int i = 0; i < size; i++) {
        printf("%d ", subset[i]);
    }
    printf("} -> Sum = %d\n", calculateSum(subset, size));
}

void findValidSubsets(int input[], int size, int subset[], int subsetSize, int index) {
    if (index == size) {
        if (subsetSize >= 2 && 
            isPrime(calculateSum(subset, subsetSize)) && 
            noCommonDivisors(subset, subsetSize)) {
            printSubset(subset, subsetSize);
        }
        return;
    }
    
    findValidSubsets(input, size, subset, subsetSize, index + 1);
    
    subset[subsetSize] = input[index];
    
    bool canInclude = true;
    if (subsetSize > 0) {
        if (gcd(subset[subsetSize - 1], input[index]) != 1) {
            canInclude = false;
        }
    }
    
    if (canInclude) {
        findValidSubsets(input, size, subset, subsetSize + 1, index + 1);
    }
}

int main() {
    int size = 0;
    scanf("%d", &size);
    int* numbers = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        scanf("%d", &numbers[i]);
    }
    
    int* subset = (int*)malloc(size * sizeof(int));

    findValidSubsets(numbers, size, subset, 0, 0); 
    
    free(numbers);
    free(subset);
    
    return 0;
}