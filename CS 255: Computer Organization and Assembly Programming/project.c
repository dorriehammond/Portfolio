/*
 Dorrie Hammond
 dhammo2@emory.edu
 2284917
 
 THIS CODE WAS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING ANY
 SOURCES OUTSIDE OF THOSE APPROVED BY THE INSTRUCTOR. Dorrie Hammond
*/

#include<stdio.h>
#include "header.h"

extern int NSegs; // Linked list declaration
extern seg *head; // Head declaration

/*
 Task 1: clearAllBits()
 fills the segmented bit array with zeros
 next field in last segment has value null
*/
void clearAll()
{
    seg *p;         // initialize pointer
    p = head;       // set pointer at head
    // for loop for all number of segments
    for (p = head; p != NULL; p->next)
    {
        // for loop for accessing every bit in the linked list
        for(int j = 0; j < 256; j++)
        {
            (*p).bits[j] = 0;   // set all bits to zero
        }
    }
}


/*
 Task 3: setBit()
 */
void setBit(int n)
{
    seg *p;         // initialize pointer
    p = head;       // set pointer at head
    
    int segm = n/256;   // calculate # of segments
    int temp = n;
    int i;
    while(temp > 65) {
        temp = temp - 65;
        i++;            // add up to index
    }
    int pos = (temp - 1)/2; // calculate position of element
    for(int j = 0; j < segm; j++) {
        p = p->next;
        (*p).bits[i] = p->bits[i] | (1 << pos); // set bit at index
    }
}


/*
 Task 4: testIsBit0()
 */
int testIsBit0(int n)
{
    // following lines are same as setBit
    seg *p;         // initialize pointer
    p = head;       // set pointer at head
    
    int segm = n/256;   // calculate # of segments
    int temp = n;
    int i;
    while(temp > 65) {
        temp = temp - 65;
        i++;            // add up to index
    }
    int pos = (temp - 1)/2; // calculate position of element
    
    // test bit at pos
    if ( (p->bits[i] & (1 << pos)) != 0)
        return 1;
    else
        return 0;
}

/*
 Task 2: sieveOfE()
 Only minor changes
*/
void sieveOfE(int N)
{
    int i, j, k;
    
    // perform the sieve of E
    k = 1;          // Start with 2 to find all primes
    while (k <= N)
    {
        // Starting from k, find next
        // prime number i
        // a prime number is detected by:
        // prime[i] == 1
        for ( i = k; i <= N; i++)
            if (i % 2 == 0)
                break;  // Skipping even numbers
        if (testIsBit0(i) == 1)
            break;  // Found!
        // Set: prime[2*i] = 0
        //      prime[3*i] = 0
        //      ...
        //      (upto prime[N]
        for (j = 2*i; j <= N; j = j + i)
            setBit(j);
        
        k = i + 1;      // Set up k for next iteration!!!
    }
}

/*
 Task 5: countPrimes()
*/
int countPrimes(int N)
{
    int count = 0;                  // initialize count to 0
    for (int i = 0; i <= N; i++)        // for loop from 0 to N
        if(testIsBit0(i) == 1)      // Use testbit to test if prime
            count++;                // if so, add to count
    return count;                   // return found count
}

/*
 Task 6: printPrimes()
*/
void printPrimes(int N)
{
    int prime;                      // initialize prime
    for (int i = 0; i <= N; i++)    // for loop from 0 to N
        if(testIsBit0(i) == 1)      // use testbit to test if prime
            printf("%d\n", prime);   // print prime
}

/*
 Task 7: factor()
*/
void factor(int inp)
{

}
