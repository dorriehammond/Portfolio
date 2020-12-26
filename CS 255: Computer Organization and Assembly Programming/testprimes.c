/*
 Dorrie Hammond
 dhammo2@emory.edu
 2284917
 
 THIS CODE WAS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING ANY
 SOURCES OUTSIDE OF THOSE APPROVED BY THE INSTRUCTOR. Dorrie Hammond
*/

#include<stdio.h>
#include<stdlib.h>
#include"header.h"

extern unsigned int prime[]; // Array declaration

/*
 Task 1: Helper method setAll()
 sets all elements of array prime[] to 1
*/
void setAll()
{
    int size = sizeof(prime)/sizeof(prime[0]);  // size of prime[]
    for (int i = 0; i < size; i++)              // for loop 0 to n
        prime[i] = 1;                           // set prime[i] = 1
}

/*
 Task 2: Helper method clearBit()
 clears bit in index i of prime[i] that is equal to n
*/
void clearBit(int n)
{
    int size = sizeof(prime)/sizeof(prime[0]);  // size of prime[]
    int found = 0;                              // found variable
    int pos;                                    // position variable
    int i = 0;
    while (i < size)                            // while loop
        if (prime[i] == n) {                    // to find element n
            found = 1;                          // if found
            pos = i;                            // save position
            break;                              // and break loop
        } i++;
    
    if (found == 1)                             // if found n
        prime[pos] = prime[pos] & ~(1 << pos);  // clears bit in pos of prime[]
    
}

/*
 Task 3: Helper Method testBitIs1
 will return 1 if prime[i] = n = 1
 otherwise return 0
*/
int testBitIs1(int n)
{
    // essentially same loop as clearBit
    int size = sizeof(prime)/sizeof(prime[0]);  // size of prime[]
    int found = 0;                              // found variable
    int pos;                                    // position variable
    int i = 0;
    while (i < size)                            // while loop
        if (prime[i] == n) {                    // to find element n
            found = 1;                          // if found
            pos = i;                            // save position
            break;                              // and break loop
        } i++;
    
    if ( (prime[pos] & (1 << pos)) != 0)        // testing bit
    {
        return 1;                               // if 1, then return 1
    } else
    {
        return 0;                               // if 0, then return 0
    }
    
}

/*
 Task 4: Sieve of Eratosthenes Algorithm
 identifies prime numbers
*/

void sieveOfE(int N)
{
    int i, j, k;
    
    // initialize prime[]
    prime[0] = 0;
    prime[1] = 0;
    
    for ( i = 2; i <= N; i++)
        prime[i] = 1; // They are all candidates
    
    k = 2; // Start with 2 to find all primes
    
    while ( k <= N)
    {
        // Find the next prime number
        for (i = k; i <= N; i++)
            if (prime[i])
                break;  // Found
        // Set: prime
    }
    
    
}

int countPrimes(int N)
{
    int count = 0;
    for (int i = 2; i <= N; i++) {
        if (testBitIs1(prime[i]) == 1) {
            count++;
        }
    }
    return count;
}

void printPrimes(int N)
{
    for (int i = 2; i <= N; i++) {
        if (testBitIs1(prime[i]) == 1) {
            printf("%d", prime[i]);
        }
    }
}


/*
void clearBit(int n)
{
    int size = sizeof(prime)/sizeof(prime[0]);  // size of prime[]
    int pos;
    int *pos = (int *)bsearch(&n, prime, size, sizeof(int), cmp);
    if (pos != null)
        prime[pos] = prime[pos] & ~(1 << pos);
}*/
/*
int testBitIs1(int n)
{
    // essentially same loop as clearBit
    int size = sizeof(prime)/sizeof(prime[0]);  // size of prime[]
    int pos;
    int *pos = (int *)bsearch(&n, prime, size, sizeof(int), cmp);
    
    if ( (prime[pos] & (1 << pos)) != 0)        // testing bit
    {
        return 1;                               // if 1, then return 1
    } else
    {
        return 0;                               // if 0, then return 0
    }
    
}
 
 void setAll()
 {
 int size = sizeof(prime)/sizeof(prime[0]);  // size of prime[]
 for (int i = 0; i < size; i++)              // for loop 0 to n
 prime[i] = 1;                           // set prime[i] = 1
 }
*/
