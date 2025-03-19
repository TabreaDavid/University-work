#include <stdio.h>

void printMenu() {
    printf("\n1. Generate prime numbers smaller or equal than n\n");
    printf("2. Longest increasing contiguous subsequence, such that the sum of any 2 consecutive elements is a prime number\n");
    printf("3. Count zero digits in product of input numbers\n");
    printf("0. Exit\n");
}

void readArray(int n, int v[]) {
	//reads an array of n numbers from the keyboard
	//:param n: natural number, length of the array
	//:param v: array in which we read elements
    for (int i = 0; i < n; ++i) {
        scanf("%d", &v[i]);
    }
}

int isPrime(int n) {
	//checks if a number is prime
   //:param n: natural number of which we check the primality
   //:return: returns 1 if the number is prime and 0 otherwise
	if (n <= 1) 
		return 0;
    if (n == 2) 
		return 1;
    if (n % 2 == 0) 
		return 0;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void longestContiguousPrimeNeighborSumSubsequence() {
	//prints on the screen the longest contigious subsequence in which every 2 elements' sum are prime numbers
    int v[200], n;
    printf("Enter array size: ");
    scanf("%d", &n);
    printf("Enter array elements: ");
    readArray(n, v);

    int maxLen = 1, start = 0, max_start = 0, len = 1;
    for (int i = 1; i < n; i++) {
        if (v[i] > v[i - 1] && isPrime(v[i] + v[i - 1])) {
            len++;
        } else {
            if (len > maxLen) {
                maxLen = len;
                max_start = start;
            }
            start = i;
            len = 1;
        }
    }
    if (len > maxLen) {
        maxLen = len;
        max_start = start;
    }
    if (maxLen > 1) {
        printf("Longest increasing subsequence with prime consecutive sums: ");
        for (int i = max_start; i < max_start + maxLen; i++)
            printf("%d ", v[i]);
        printf("\n");
    } else {
        printf("No valid subsequence found\n");
    }
}

int numberOfZeroDigits() {
    int x, prod = 1, k = 0;
    while (1) {
        scanf("%d", &x);
        if (x == 0)
            break;
        prod *= x;
    }
    while (prod) {
        if (prod % 10 == 0)
            k++;
        prod /= 10;
    }
    return k;
}

void generatePrimeNumbersSmallerThanInput() {
	//generates prime numbers smaller than an input from the keyboard
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    if (n < 2) {
        printf("There are no prime numbers smaller than that!\n");
        return;
    }
    for (int i = 2; i <= n; ++i) {
        if (isPrime(i)) printf("%d ", i);
    }
    printf("\n");
}

void runUi() {
	//runs ui for the requeqsted commands
    int userChoice;
    while (1) {
        printMenu();
        printf("Enter your  choice: ");
        scanf("%d", &userChoice);
        if (userChoice == 1)
            generatePrimeNumbersSmallerThanInput();
        else if (userChoice == 2)
            longestContiguousPrimeNeighborSumSubsequence();
        else if (userChoice == 3)
            printf("Zero digits in product: %d\n", numberOfZeroDigits());
        else if (userChoice == 0) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Invalid choice! Try again.\n");
        }
    }
}

int main() {
    runUi();
    return 0;
}
