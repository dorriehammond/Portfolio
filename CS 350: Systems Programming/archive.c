/*
 archive.c
 Student: Dorrie Hammond
 Student ID: 2284917
 THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
 A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - DORRIE HAMMOND
 */

#include "archive.h"
#include <ar.h>
#include <time.h>
#include <utime.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// fill ar_hdr by looking at stat info, make sure file is there
// us sprintf to get ascii data for hdr struct
// and then add in appropriate spaces for writing (for loop)
int fill_ar_hdr(char *filename, struct ar_hdr *hdr) {	
    struct stat *statbuf = (struct stat *)malloc(sizeof(struct stat *));
    int check = stat(filename,statbuf);
    if (check<0) { 
	    printf("ar: %s: No such file or directory\n",filename);
	    exit(1); }
    sprintf(hdr->ar_name,"%s%s",filename,"/");
    sprintf(hdr->ar_date,"%ld",statbuf->st_mtime);
    sprintf(hdr->ar_uid,"%d",statbuf->st_uid);
    sprintf(hdr->ar_gid,"%d",statbuf->st_gid);
    sprintf(hdr->ar_mode,"%o",statbuf->st_mode);
    sprintf(hdr->ar_size,"%ld",statbuf->st_size);
    sprintf(hdr->ar_fmag,"%s",ARFMAG);
    int space=0;
    for (int i = 0; i < 16; i++) {
        if (hdr->ar_name[i]==0||space==1) {hdr->ar_name[i]=32;}
        if (i<12) {
            if (hdr->ar_date[i]==0) {hdr->ar_date[i]=32;}
        }
        if (i<10) {
            if (hdr->ar_size[i]==0||hdr->ar_size[i]==-127||hdr->ar_size[i]==-92) {
                    hdr->ar_size[i]=32; }
        }
        if (i<8) {
                if (hdr->ar_mode[i]==0) {hdr->ar_mode[i]=32;}
        }
        if (i<6) {
            if (hdr->ar_uid[i]==0) {hdr->ar_uid[i]=32;}
            if (hdr->ar_gid[i]==0) {hdr->ar_gid[i]=32;}
        }
	if (hdr->ar_name[i]==47) { space=1;}
    }
    return 0;
}

// fill meta struct using filled hdr struct
// take out '/' and spaces in name for comparing
// convert rest from chars to appropriate variable types
int fill_meta(struct ar_hdr hdr, struct meta *meta) {
    snprintf(meta->name,16,"%s",hdr.ar_name);
    for (int i=0; i<16; i++) {
            if (meta->name[i]==47|meta->name[i]==32) {
                    meta->name[i]=0;
            }
    }
    meta->size = atoi(hdr.ar_size);
    meta->mode = strtoul(hdr.ar_mode,NULL,8);//octal
    meta->mtime = (time_t)strtol(hdr.ar_date,NULL,0);
    return 0;
}

// Reads 60 characters of archive to find hdr data
// also checks if it is at the end of the archive list (filename not in ar)
int read_file(int fd,int t, struct ar_hdr *hdr) {
    int check = read(fd,hdr,60);
    if (check<1&&t==1) {
            return 1;
    } else if (check<1)  {
            return 2;
    } else {
    	return 0;
    }
}

// Checks whether archive exists or is in the write format
// This use ARMAG for comparison
int new_archive(char *archive) {
	int fd = open(archive,O_RDONLY);
	char bf[SARMAG];
	read(fd,bf,SARMAG);
	if (strncmp(bf,ARMAG,SARMAG)==0) {
		close(fd);
		return 0;
	} else if (bf[0]==0) { 
		close(fd);
		return 1;
	} else {
		close(fd);
		return -1;
	}
}

// checks if archive exists or is in the right format
// very similar to new_archive, but I was too afraid of 
// messing up errors to merge the two
int check_archive(int fd,char *archive) {
        // if doesn't exist, return -1
        if (fd<0) {
                return fd;
        } else {
                char bf[SARMAG];
                char armag[SARMAG]=ARMAG;
                read(fd,bf,SARMAG);
                if (strncmp(bf,armag,SARMAG)==0) {
                        return fd;
                } else {
			return -2;
                }
        }
}

// compares if the filename and meta->name is the same
int compare_names(char * filename, struct meta *meta) {
    if (strncmp(filename,meta->name,16)==0) { return 1; }
    else { return 0; }
}

// checks if size is odd or even
// returns size+1 if odd
int return_size(struct meta *meta) {
        int size = meta->size;
        if (size%2==0) {
                return size;
        } else {
                return size+1;
        }
}

// repositions fd to next ar_hdr past the size of file
int next_file(int fd, int size) {
        int check = lseek(fd,size,SEEK_CUR);
        return fd;
}

// Used for multiple filenames with -t and -x (and -o)
// Basically traverses through ar list to see if filename exists in it
// If it does, then it either prints it out or extracts it
// If it doesn't, then sends an error message and continues to next filename
void search_name(int fd,char *filename,int t,int x,int o) {
	// allocate memory for hdr and meta
        struct ar_hdr *hdr = (struct ar_hdr *) malloc(sizeof(struct ar_hdr *));
        struct meta *meta = (struct meta *) malloc(sizeof(struct meta *));
	int check = read_file(fd,1,hdr); // to fill hdr
        int size;// for going to next header
	// while loop that only stops when match is found or reached end of ar list
        while(check==0&&hdr!=NULL) {
		// fill meta so that we can compare with filename
                fill_meta(*hdr,meta);
                int compare = 0;
                compare = compare_names(filename,meta);
		// if there is a match, then follow -t or -xo rules
                if (compare==1) {
			// print if -t
			if (t==1) {
                        	printf("%s\n",filename);
				break;
			// write new truncated file out to directory, may need to create new
			// If -o is specified, then restore mtime stored in meta with utime
			} else if (x==1) {
        			int fd2=open(filename,O_TRUNC|O_CREAT|O_WRONLY,0666);
				char buffer[meta->size];
				read(fd,buffer,meta->size);
        			write(fd2,buffer,meta->size);
        			if (o>0) {
                			struct utimbuf newt;
                			time_t tim=meta->mtime;
					newt.actime=tim;
                			newt.modtime=tim;
                			utime(filename,&newt);
        			}
				close(fd2);
				break;
			}
		// move to the next ar hdr
                } else {
                        size = return_size(meta);
                        fd = next_file(fd,size);
                        check = read_file(fd,1,hdr);
                }
        }
	// error if file does not exist
        if (check==1) {
                printf("no entry %s in archive\n",filename);
        }
        return;
}

// used to print full ar list, create hdr and meta for first on list,
// then print out name from meta, then reposition to next header and 
// repeat until end of list
void print_list(int fd) {
        struct ar_hdr *hdr = (struct ar_hdr *) malloc(sizeof(struct ar_hdr *));
        struct meta *meta = (struct meta *) malloc(sizeof(struct meta *));
        int check = read_file(fd,0,hdr);
        int size;
        while(check==0) {
                fill_meta(*hdr,meta);
                printf("%s\n",meta->name);
                size = return_size(meta);
                fd = next_file(fd,size);
                check = read_file(fd,0,hdr);
        }
        return;
}

// If archive doesn't exist, in -q or -A, then creat one and add ARMAG
// If archive does exist, then we'll just append the end
// BUT if archive is not in the right format, then error
int create_archive(char * archive) {
	int fd = open(archive,O_APPEND|O_CREAT|O_WRONLY,0666);
        int new = new_archive(archive);
        if (new==1) {
		printf("ar: creating %s\n",archive);
                write(fd,ARMAG,SARMAG);
        } else if (new==-1) {
		printf("ar: %s: File format not recognized\n",archive);
                exit(1);
	}
	return fd;
}

// This writes a new ar hdr + file contents into the archive.
// First fill hdr, then write out those 60 characters accordingly
// then fill meta and use the size to write the file contents (have to read from file)
// IF size is odd, then an addtional "/n" is added to end
void add_file(char * filename,int fd) {
	struct ar_hdr *hdr = (struct ar_hdr *)malloc(sizeof(struct ar_hdr *));
        fill_ar_hdr(filename,hdr);
        write(fd,hdr->ar_name,16);
        write(fd,hdr->ar_date,12);
        write(fd,hdr->ar_uid,6);
        write(fd,hdr->ar_gid,6);
        write(fd,hdr->ar_mode,8);
        write(fd,hdr->ar_size,10);
        write(fd,hdr->ar_fmag,2);
        struct meta *meta = (struct meta *)malloc(sizeof(struct meta *));
        fill_meta(*hdr,meta);
        int size = return_size(meta);
        char file[meta->size];
        int fd2=open(filename,O_RDONLY);
        read(fd2,file,meta->size);
        write(fd,file,meta->size);
        if (size>meta->size) {
		write(fd,"\n",1);
        }
	close(fd2);
}

