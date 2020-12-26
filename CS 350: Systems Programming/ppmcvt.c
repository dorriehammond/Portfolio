/*
ppmcvt.c
Student: Dorrie Hammond
Student ID: 2284917
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - DORRIE HAMMOND
*/

#include "pbm.h"
#include "ppmcvt.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

int main (int argc, char *argv[]) {
   
    // opt_tran is to determine what to do in -o
    // tran makes sure no more than two transformations are picked
    // opt_o makes sure o is always picked
    // *ptr,m,color,option all used for values needed in getopt
    char * opt_tran = "o";
    int tran = 0;
    int opt_o = 0;
    char *ptr;
    long int m;
    const char * color;
    int option;
    
    // Getopt
    while ( (option = getopt(argc,argv,"bg:i:r:smt:n:o")) != -1) {
        
        switch(option) {
             // Errors: multiple trans, Invalid grayscale, Invalid color, Invalid scale, No input, No output
	     // Convert to bitmap      
            case 'b':
                if (tran!=0) { printf("Error: Multiple transformations specified\n"); exit(1); }
                else { tran++; }
                break;
             // Convert to grayscale   
            case 'g':
                if (tran!=0) { printf("Error: Multiple transformations specified\n"); exit(1); }
                else {
                    m = strtol(argv[2],&ptr,10);
                    if (m>0 && m<=65535) {
                        tran++;
                        opt_tran = "g";
                    } else {
                        printf("Error: Invalid max grayscale pixel value: %ld; must be less than 65,536\n",m);
                        exit(1);
                    }
                }
                break;
                // isolate RGB
            case 'i':
                if (tran!=0) { printf("Error: Multiple transformations specified\n"); exit(1); }
                else {
                    color = argv[2];
                    if (strcmp(color,"red")==0 || strcmp(color,"blue")==0 || strcmp(color,"green")==0) {
                        tran++;
                        opt_tran = "i";
                    } else {
                        printf("Error: Invalid channel specification (%s); should be 'red', 'green' or 'blue'\n",color);
                        exit(1);
                    }
                }
                break;
                // Remove RGB
            case 'r':
                if (tran!=0) { printf("Error: Multiple transformations specified\n"); exit(1); }
                else {
                    color = argv[2];
                        if (strcmp(color,"red")==0 || strcmp(color,"blue")==0 || strcmp(color,"green")==0) {
                                tran++;
                                opt_tran = "r";
                        } else {
                            printf("Error: Invalid channel specification (%s); should be 'red', 'green' or 'blue'\n",color);
                            exit(1); }
                }
                break;
                // Sepia
            case 's':
                if (tran!=0) { printf("Error: Multiple transformations specified\n"); exit(1); }
                else { tran++; opt_tran = "s"; }
                break;
                // Mirror
            case 'm':
                if (tran!=0) { printf("Error: Multiple transformations specified\n"); exit(1); }
                else { tran++; opt_tran = "m"; }
                break;
                // Thumbnail
            case 't':
                if (tran!=0) { printf("Error: Multiple transformations specified\n"); exit(1); }
                else {
                    m = strtol(argv[2],&ptr,10);
                    if (m>0 && m<=8) {
                        tran++;
                        opt_tran = "t";
                    } else {
                        printf("Invalid scale factor: %ld; must be 1-8\n",m);
                        exit(1);
                    }
                }
                break;
                // NUP
            case 'n':
                if (tran!=0) { printf("Error: Multiple transformations specified\n"); exit(1); }
                else {
                    m = strtol(argv[2],&ptr,10);
                    if (m>0 && m<=8) {
                        tran++;
                        opt_tran = "n";
                    } else {
                        printf("Invalid scale factor: %ld; must be 1-8\n",m);
                        exit(1);
                    }
                }
                break;
                // -o calls to the functions to transform based on user inputs
		// bitmap is default
		// infilename and outfilename taken from argv
		// allocates memory and then deallocates memory
		case 'o':
                    opt_o++;
                    if ( (argc-optind) < 2) {
                        printf("Error: No input file specified\n");
                        exit(1);
                    } else {

                        const char * infilename = argv[optind+1];
                        const char * outfilename = argv[optind];
                        PPMImage * ppm = read_ppmfile(infilename);

                        if (strcmp(opt_tran,"o")==0) {
                            PBMImage * pbm = bitmap(ppm);
                            write_pbmfile(pbm,outfilename);
                            del_pbmimage(pbm);

                        } else if (strcmp(opt_tran,"g")==0) {
                            PGMImage * pgm = grayscale(ppm,m);
                            write_pgmfile(pgm,outfilename);
                            del_pgmimage(pgm);

                        } else if (strcmp(opt_tran,"i")==0) {
                            ppm = isolateRGB(ppm,color);
                            write_ppmfile(ppm,outfilename);

                        } else if (strcmp(opt_tran,"r")==0) {
                            ppm = removeRGB(ppm,color);
                            write_ppmfile(ppm,outfilename);

                        } else if (strcmp(opt_tran,"s")==0) {
                            ppm = sepia(ppm);
                            write_ppmfile(ppm,outfilename);

                        } else if (strcmp(opt_tran,"m")==0) {
                            ppm = mirror(ppm);
                            write_ppmfile(ppm,outfilename);

                        } else if (strcmp(opt_tran,"t")==0) {
                            ppm = thumbnail(ppm,m);
                            write_ppmfile(ppm,outfilename);

                        } else {
                            ppm = nup(ppm,m);
                            write_ppmfile(ppm,outfilename);
                        }

                        del_ppmimage(ppm);
                    }
                    break;
		// unknown command	
            case '?':
                exit(1);
                break;
        }
    }
    // if -o was not chosen
    if (opt_o==0) { printf("Error: No output file specified\n"); exit(1); }
    // SUCCESS!
    return 0;
    
}

