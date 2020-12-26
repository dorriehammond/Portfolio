/*
 main.c
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

void print_free_list(FreeListNode fhead) {
	printf("freelist: ");

	if (NULL == fhead) {
		printf("NULL\n");
	}

	else
	{
		FreeListNode fnode = fhead;
		while (fnode) {
			printf("%lu ", fnode->size);
			fnode = fnode->flink;
		}
		printf("\n");
	}
}

int main(int argc, char* argv[]) {

	int size[6] = {10, 50, 100, 50, 50, 2048};
	int *p[6];
	FreeListNode fhead = free_list_begin(); //fhead should be NULL here

	for (int i = 0; i < 6; i++) {

		p[i] = (int*) my_malloc(sizeof(int) * size[i]); // chunk size is 4 * sizes[i]
		fhead = free_list_begin();
		print_free_list(fhead);

		my_free(p[i]);
		fhead = free_list_begin();
		print_free_list(fhead);
	}
	coalesce_free_list();
	print_free_list(fhead);

	/*
	 *  If your implementation is correct, you should print the following information
	 *  freelist: 8144
	 *  freelist: 48 8144
	 *  freelist: 48 7936
	 *  freelist: 48 208 7936
	 *  freelist: 48 208 7528
	 *  freelist: 48 208 408 7528
	 */

	return 0;
}


