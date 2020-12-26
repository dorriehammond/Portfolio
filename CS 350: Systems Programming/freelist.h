/*
 free_list.c
 Student: Dorrie Hammond
 Student ID: 2284917
 THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
 A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - DORRIE HAMMOND
 */

#ifndef freelist_h
#define freelist_h

FreeListNode first_fit(size_t size);

FreeListNode allocate(size_t size, struct freelistnode *ptr);

FreeListNode chunk_split(struct freelistnode *ptr, struct freelistnode *before, struct freelistnode *after, size_t size);

#endif
