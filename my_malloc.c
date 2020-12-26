 /*
 my_malloc.c
 Student: Dorrie Hammond
 Student ID: 2284917
 THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
 A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - DORRIE HAMMOND
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include "my_malloc.h"
#include "freelist.h"

// One global varible
// Node is the header of the free link list
struct freelistnode *node;

// error signaling
MyErrorNo my_errno;

// Helper Function to find the node before the first fit with specified size
FreeListNode first_fit(size_t size) {
	// Node is empty, return null
	if (node == NULL) {
		return NULL;
	} else {
		// if head of freelist is first fit
		if (node->size >= size) {
			return node;
		// search through free list for first fit
		} else {
			struct freelistnode *ptr = node;
			while (ptr->flink!=NULL) {
				if (ptr->flink->size >= size) {
					break;
				} else {
					ptr = ptr->flink;
				}
			}
			// return pointer
			return ptr;
		}
	}
}

// Helper function for allocated memory using sbrk
// while loop is for if size>8192, otherwise sbrk(8192)
FreeListNode allocate(size_t size, struct freelistnode *ptr) {
    // if size is greater than 8192, call sbrk(size)
    if (size>8192) {
        ptr = sbrk(size);
        ptr->flink = NULL;
        ptr->size = size;
    // if size is equal to or less than 8192, call sbrk(8192)
    } else {
        ptr = sbrk(8192);
        ptr->flink = NULL;
        ptr->size = 8192;
    }
    // return pointer to newly allocated free memory
    return ptr;
}

// Helper function for chunk splitting and/or chunk allocation
FreeListNode chunk_split(struct freelistnode *ptr, struct freelistnode *before, struct freelistnode *after, size_t size) {
    struct freelistnode *chunk;
    // give oversized chunk if remainder <16
    if (ptr->size-size <16) {
        if (before == NULL) { // at top of freelist
            node = ptr->flink;
        } else { // in middle or bottom of freelist
            before->flink = after;
        }
        ptr->flink = NULL;
        chunk = ptr;
    // Split chunk if big enough
    } else {
        ptr->size = ptr->size -size;
        chunk = ptr;
	ptr = ptr + size;
	ptr->size = chunk->size;
        chunk->size = size;
	// incase pointer is in first position of freelist
	if (before == NULL) {
		node = ptr;
	} else {	
		before->flink = ptr;
	}
	ptr->flink = after;
    }
    // Give chunk a 'magic number' id
    (chunk+4)->size = 7;
    return chunk;
}

//my_malloc: returns a pointer to a chunk of heap allocated memory
void *my_malloc(size_t size) {
    // adjust size to be divisible by 8 and error if size is
    // less than 16 (minimum)
    size = (size+15)&-8;
    if (size < 16) {
        my_errno = MYENOMEM;
        return NULL;
    }
    size_t count = 0;
    
    // find node before first fit with helper funtion
    // if Node is empty, then will return NULL
    // if there is no chunk of adequate size, return last
    // chunk of freelistnode
    struct freelistnode *before = first_fit(size);
    struct freelistnode *ptr;
    
    // Allocate mem and/or set pointer
    // if Node is empty
    if (before == NULL) {
        node = allocate(size,node);
        ptr = node;
    // if there is no chunk of adequate size
    } else if (before->flink==NULL) {
        ptr = allocate(size,(sbrk(0)));
        before->flink = ptr;
	ptr->flink = NULL;
    // there is an adequate chunk
    } else {
        ptr = before->flink;
    }
    
    // Chunk Splitting!
    struct freelistnode *chunk = ptr;
    chunk = chunk_split(ptr,before,ptr->flink,size);

    // No error, and set pointer past header
    my_errno = MYNOERROR;
    return chunk + CHUNKHEADERSIZE;
}

//my_free: reclaims the previously allocated chunk referenced by ptr
void my_free(void *ptr) {
	// turn ptr back into freelistnode *
	struct freelistnode *new = (struct freelistnode *) ptr;
	// if chunk doesn't belong to me
	if ((new-4)->size != 7) {
		my_errno = MYBADFREEPTR;
		return;
	} else {
		// readjust chunk to top of header
		new = new - CHUNKHEADERSIZE;
		// easy, if chunk belongs at front of free list
		if (node > new) {
			new->flink = node;
			node = new;
		} else {
			// search through free linked list for appropriate
			// position, keep track of after and before
			// stop right before comparing last free node
			struct freelistnode *after = node;
			struct freelistnode *before;
			while (after->flink != NULL) {
				if (new < after) {
					break;
				} else {
					before = after;
					after = after->flink; //go to next
				}
			}
			// compare chunk with last free node
			// add back accordingly with after and before references
			if (after->flink==NULL && new > after) {
				after->flink = new;
				new->flink = NULL;
			} else {
				before->flink = new;
				new->flink = after;
			}
		}
		// no error
		my_errno = MYNOERROR;
		return;
	}
}

//free_list_begin(): returns pointer to first chunk in free list
FreeListNode free_list_begin(void) {
	// very simple, just return global variable node, which
	// is the header of the free linked list
	// also no error
	my_errno = MYNOERROR;
	return node;
}

//coalesce_free_list(): merge adjacent chunks on the free list
void coalesce_free_list(void) {
	// I want to keep track of temp and current (maybe adjacent to temp)
	// and the size for defining purposes
	struct freelistnode *current;
	struct freelistnode *temp = node;
	size_t size;
	// search through list until reaching last node where there is 
	// nothing to compare
	while (temp->flink != NULL) {
		size = temp->size;
		current = temp->flink;
		// is current adjacent to temp?
		// If yes, combing temp and current into one free list node
		if ((temp+size)==current) {
			size = size + (current)->size;
			temp->size = size;
			temp->flink = current->flink;
			current->size = 0;
			current->flink = NULL;
		// if no, go to next node
		} else {
			temp = temp->flink;
		}
	}
	// no errors
	my_errno = MYNOERROR;	
	return;
}
