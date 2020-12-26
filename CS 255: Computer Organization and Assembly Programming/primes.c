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
 Task 1: Helper method setAll
 sets all elements of array prime[] to 1
 Based on class notes
*/
void setAll()
{
    int size = sizeof(prime)/sizeof(prime[0]);  // size of prime[]
    size = size * 32;                           // prepare for bits
    for (int i = 0; i < size; i++)              // for loop from 0 to size
        prime[i/32] |= 1 << (i%32);             // Set bit t 1
}

/*
 Task 2: Helper method clearBit
 clears bit in index i of prime[i] that is equal to n
 Taken directly from class notes
*/
void clearBit(int n)
{
    prime[n/32] &= ~(1 << (n%32));
}

/*
 Task 3: Helper Method testBitIs1
 will return 1 if prime[i] = n = 1
 otherwise return 0
 Taken directly from class notes
*/
int testBitIs1(int n)
{
    if ( (prime[n/32] & (1 << (n%32) )) != 0 )
        // n-th bit is 1
        return 1;
    else
        // n-th bit is 0
        return 0;
}

/*
 Task 4: Sieve of Eratosthenes Algorithm
 identifies prime numbers
 Implements setAll(), clearBit(), and testBitIs1()
*/
void sieveOfE(int N)
{
    int i, j, k;
    // initialize prime[]
    setAll();       // all numbers are possible candidates
    clearBit(0);    // 0 is not prime
    clearBit(1);    // 1 is not prime
    
    // perform the sieve of E
    k = 2;          // Start with 2 to find all primes
    while (k <= N)
    {
        // Starting from k, find next
        // prime number i
        // a prime number is detected by:
        // prime[i] == 1
        for ( i = k; i <= N; i++)
            if (testBitIs1(i) == 1)
                break;  // Found!
        
        // Set: prime[2*i] = 0
        //      prime[3*i] = 0
        //      ...
        //      (upto prime[N]
        for (j = 2*i; j <= N; j = j + i)
            clearBit(j);
        
        k = i + 1;      // Set up k for next iteration!!!
    }

}

/*
 Task 5: countPrimes
 Initialize a count variable to 0
 Loop from 2 to N
 Use testBitIs1() to help you count the # of primes
*/
int countPrimes(int N)
{
    int count = 0;                          // initialize count to 0
    for (int i = 2; i <= N; i++) {          // For loop from 2 to N
        if (testBitIs1(i) == 1) {           // Use testBitIs1 to test if prime
            count++;                        // if so, add to count
        }
    }
    return count;                           // return found count
}

/*
 Task 6: printPrimes
 Loop from 2 to N
 Use testBitIs1() to help identify the prime # & print
*/
void printPrimes(int N)
{
    for (int i = 2; i <= N; i++) {          // For loop from 2 to N
        if (testBitIs1(i) == 1) {           // Use testBitIs1 to test if prime
            printf("%d\n", i);              // if so, print i (the prime)
        }
    }
}

