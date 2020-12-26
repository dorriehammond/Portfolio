/*
 archive.h
 Student: Dorrie Hammond
 Student ID: 2284917
 THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
 A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - DORRIE HAMMOND
 */


#ifndef archive_h
#define archive_h

#include <stdio.h>
#include <time.h>
#include <ar.h>

struct meta {
        char name[16]; // room for null
        int mode;
        int size;
        time_t mtime; // a time_t is a long
};

int fill_ar_hdr(char *filename, struct ar_hdr *hdr);

int fill_meta(struct ar_hdr hdr, struct meta *meta);

int read_file(int fd,int t, struct ar_hdr *hdr);

int new_archive(char *archive);

int check_archive(int fd,char *archive);

void print_name(struct ar_hdr *hdr);

int return_size(struct meta *meta);

int next_file(int fd, int size);

void search_name(int fd,char *filename,int t,int x,int o);

void print_list(int fd);

void deformat_name(struct ar_hdr *hdr);

int compare_names(char * filename, struct meta *meta);

int create_archive(char * archive);

void add_file(char * filename,int fd);

#endif /* archive_h */
