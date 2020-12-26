/*
 allocation.c
 Student: Dorrie Hammond
 Student ID: 2284917
 THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
 A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - DORRIE HAMMOND
 */


#include "pbm.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

// new functions return image struct of appropriate type

PPMImage * new_ppmimage( unsigned int width, unsigned int height, unsigned int max)
{
	PPMImage * ppm = (PPMImage *) malloc(sizeof(PPMImage));

	ppm->width = width;
	ppm->height = height;
	ppm->max = max;
	// This allocates memory for every pixel of the pixmap[3]
	for(int i = 0; i<3; i++) {
		ppm->pixmap[i] = (unsigned int**) malloc(height*sizeof(unsigned int *));
		for (int j = 0; j<height; j++) {
			ppm->pixmap[i][j] = (unsigned int*) malloc(width*sizeof(unsigned int*));
		}
	}
	return ppm;
}

PGMImage * new_pgmimage( unsigned int width, unsigned int height, unsigned int max)
{
	PGMImage * pgm = (PGMImage *) malloc(sizeof(PGMImage));

	pgm->width = width;
	pgm->height = height;
	pgm->max = max;
	// This allocates memory for every pixel of pixmap
	pgm->pixmap = (unsigned int**) malloc(height * sizeof(unsigned int*));
	for (int i = 0; i < height; i++) {
		pgm->pixmap[i] = (unsigned int *) malloc(width*sizeof(unsigned int*));
	}
	return pgm;
}

PBMImage * new_pbmimage( unsigned int width, unsigned int height)
{
	PBMImage * pbm = (PBMImage *) malloc(sizeof(PBMImage));

	pbm->width = width;
	pbm->height = height;
	// This allocates memory for every pixel of pixmap
	pbm->pixmap = (unsigned int**) malloc(height * sizeof(unsigned int*));
	for (int i = 0; i < height; i++) {
		pbm->pixmap[i] = (unsigned int *) malloc(width*sizeof(unsigned int*));
	}
	return pbm;
}

// del routines free all memory associated wiht image struct

void del_ppmimage( PPMImage *p )
{
	int width = p->width;
	int height = p->height;
	// First free pixel memory (backwards to not lose pointer)
	for (int i = 2; i>=0; i--) {
		for (int j = height-1; j>=0; j--) {
			free(p->pixmap[i][j]);
		}
		free(p->pixmap[i]);
	}
	// And then free pointer to ppmimage
	free(p);
}

void del_pgmimage( PGMImage *p )
{
	int width = p->width;
	int height = p->height;
	// first free pixel memory (backwards)
	for (int i = height-1; i>=0; i--) {
		free(p->pixmap[i]);
	}
	// free pointer to pixmap
	free(p->pixmap);
	// free pointer to pgmimage
	free(p);
}

void del_pbmimage( PBMImage *p )
{
	int width = p->width;
        int height = p->height;
	// first free pixel memory (backwards)
        for (int i = height-1; i>=0; i--) {
                free(p->pixmap[i]);
        }
	// free pointer to pixmap
        free(p->pixmap);
	// free pointer to pbmimage
        free(p);
}
