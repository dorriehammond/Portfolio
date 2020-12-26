/*
 myar.c
 Student: Dorrie Hammond
 Student ID: 2284917
 THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
 A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - DORRIE HAMMOND
 */

#include <ar.h>
#include "archive.h"
#include <dirent.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	// make sure there are enough arguments
        if (argc<3) { return 1; }
	// variables for archive and file name
        char * archive;
	char * filename;

        // variables to see which commands are chosen
	int q=0,x=0,t=0,o=0,A=0,n=0,num=0,fd,check;

        // getopt
        int option;
        while ( (option = getopt(argc,argv,"qxotA:")) != -1) {
                switch(option) {
			case 'q': num++; q++; break;
			case 'x': num++; x++; break;
			case 'o': num++; o++; break;
			case 't': num++; t++; break;
			case 'A': 
				  num=num+2;
				  n=atoi(argv[num]);
				  A++; 
				  break;
                }
        }
	// check whether the user chose exactly one of these operations
	check = q + t + x + A;
	
	// errors in case they did not have check==1
	if (check>1) {
		printf("ar: two different operation options specified\n");
		exit(1);

	} else if (check=0) {
		printf("ar: no operation specified\n");
                exit(1);	

	// for -q and -A
	} else if (q==1||A==1) {
		// open/create archive
		archive=argv[num+1];
		fd = create_archive(archive);

		// -A open current directory
		// Have to do some math to figure out n days away (in seconds)
		// Open while loop to look at full directory
		// Look at stat of file to make sure it is regular
		// Filter out 'junk' in dp->name with for loop
		// And then finally append correct file
		if (A==1) {
			DIR *dirp;
			struct dirent *dp;
			struct stat buf;
			dirp=opendir("./");
			n=n*86400;
			long ndays=(long)time(NULL)-n;
			long older, compare;
			char date[12];
			char name[16];
			int erase;
			while((dp=readdir(dirp))!=NULL) {
				stat(dp->d_name,&buf);
				sprintf(date,"%ld",buf.st_mtime);
				older = strtol(date,NULL,0);
				compare = ndays-older;
				erase=0;
				for (int i=0;i<16;i++) {
					if (dp->d_name[i]==0) {
						erase=1;
					} else {
						name[i]=dp->d_name[i];
					}
					if (erase==1) {
						name[i]=0;
					}
				}
				if ((compare>0)&&(strcmp(name,archive)!=0)&&S_ISREG(buf.st_mode)) {
					add_file(name,fd);
				}
				
			}
			closedir(dirp);
		
		// -q if there is a filename, append them to the archive
		// it only appends one file because I did not do the bonus
		} else if (num+2<argc) {
			filename=argv[num+2];
			if (strcmp(filename,archive)!=0) {
				add_file(filename,fd);
			}
		}
		close(fd);
	
	// For -t and -x (and -o is included too)
	} else if (t==1||x==1) {
		// open archive for reading, check archive format
		archive=argv[num+1];
		fd=open(archive,O_RDONLY);
		fd=check_archive(fd,archive);

		// errors in case the ar doesn't exist or is wrong format
		if (fd==-1) {
			printf("ar: %s: No such file or directory\n",archive); 
			exit(1);
		} else if (fd==-2) {
	       		printf("ar: %s: File format not recognized\n",archive);
                        exit(1);

		// else, either loop through all argument files (txo) or print full ar list (t)
		} else {
			if (num+2<argc) {
				num=num+2;
				while(num<argc) {
					filename=argv[num];
					// search through ar for filename (with txo parameters)
					if (t==1) {
						search_name(fd,filename,t,0,0);
					} else if (x==1) {
						search_name(fd,filename,0,x,o);
					}
					// reposition to beginning
					lseek(fd,SARMAG,SEEK_SET);
					num++;
				}
			} else if (t==1) {
				print_list(fd);
			}
		}
		close(fd);
        }

        return 0;
}

