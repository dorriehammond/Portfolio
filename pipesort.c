/*
pipesort.c
Student: Dorrie Hammond
Student ID: 2284917
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - DORRIE HAMMOND
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>
#include <getopt.h>


// function to parse through stdin and remove all
// non-alpha characters
// words will not be printed unless they are more
// than s characters long (achieved with short buffer)
// words are also truncated to l characters (achieved with counter)
void parse(int pipefd, int l, int s) {
        FILE *file;
        file = fdopen(pipefd,"w");
	char word[s];
	int c,j,i=0,nl=0;

	while ((c=getchar())!=EOF) {
		c=tolower(c);
		if (isalpha(c)!=0) {
			if (i<s) { word[i]=c; }
			else if (i==s) {
				for (j=0;j<s;j++) {
					fputc(word[j],file);
				}
				fputc(c,file);
			} else if (i<l) { fputc(c,file); }
			i++;nl=1;
		} else if (nl==1) {
			fputc(10,file);
			i=0; nl=0;
		}
	}
      fclose(file);
}

// reads through sorted words, compares to find duplicates
// if there is more than one of the same word, count++
// if a new word is found, prints compare and count
void suppress(int pipefd, int l) {
    FILE *file = fdopen(pipefd,"r");
    char word[l+2];
    char compare[l+2];
    word[l+1]=0;compare[l+1]=0;
    int count=1;

    if (fgets(compare,sizeof(compare),file)==NULL) {
            exit(0);
    }
    while (fgets(word,sizeof(word),file)!=NULL) {
            if (strcmp(compare,word)==0) {
                    count++;
            } else {
		    if (compare[0]!=10) {
		    	printf("%-10d%s",count,compare); }
                    strcpy(compare,word);
                    count=1;
            }
    }
    if (compare[0]!=10) {
    	printf("%-10d%s",count,compare); }
    fclose(file);
}

int main (int argc, char *argv[]) {

	// Processes summary:
	// stdin-> parse -> sort -> suppress -> stdout
	// pipe1 write -> pipe1 read -> pipe2 write -> pipe2 read
        int option,ida,idb,c,status,alpha=0,l,s;
        int pipefd1[2];
        int pipefd2[2];

	// getopt to get the s and l
	// I didn't do bonus, so n is always 1 regardless
	// (not really needed for input)
        while ( (option = getopt(argc,argv,"n:s:l:")) != -1) {
                switch(option) {
			case 'n': break;
			case 's': s=atoi(optarg); break;
			case 'l': l=atoi(optarg); break;
                }
        }

	if (s>=l) { exit(0); }

	// pipe and fork error messages
        if (pipe(pipefd1)==-1) {
            perror("pipe1\n");
            return 1;
        }
        if (pipe(pipefd2)==-1) {
            perror("pipe2\n");
            return 1;
        }
        ida=fork();
        if (ida==-1) {
            perror("fork1\n");
            return 1;
        }

        if (ida==0) {
            	// child A process
		// exec's sort
                // parse(new stdin) -> sort -> suppress(new stdout)
		dup2(pipefd1[0],0);
                dup2(pipefd2[1],1);

                close(pipefd2[0]);
                close(pipefd2[1]);
                close(pipefd1[0]);
                close(pipefd1[1]);

                execl("/usr/bin/sort","sort",NULL);
                exit(1);

        } else {
            idb=fork();
            if (idb==-1) {
                perror("fork2\n");
            }
            
            if (idb==0) {
                // child B process
		// used to suppress the sorted list
                // sort -> suppress -> stdout
                close(pipefd1[0]);
                close(pipefd1[1]);
                close(pipefd2[1]);

                suppress(pipefd2[0],l);
            } else {
		// parent process
		// used to parse the stdin
                // stdin -> parse -> pipefd[1](which will redirect to sort)
                close(pipefd2[0]);
                close(pipefd2[1]);
                close(pipefd1[0]);

                parse(pipefd1[1],l,s);
            }
            
        }
    	
	// three waits is for the three processes
        wait(&status);
        wait(&status);
        wait(&status);
        return 0;
}


