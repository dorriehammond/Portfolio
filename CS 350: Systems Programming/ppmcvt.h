/*
 ppmcvt.h
 Student: Dorrie Hammond
 Student ID: 2284917
 THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
 A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - DORRIE HAMMOND
 */


#ifndef ppmcvt_h
#define ppmcvt_h

// These are all the functions defined in transform.c

PBMImage * bitmap( PPMImage * ppm);

PGMImage * grayscale( PPMImage * ppm, long int gmax);

PPMImage * isolateRGB( PPMImage * ppm, const char * color);

PPMImage * removeRGB( PPMImage * ppm, const char * color);

PPMImage * sepia( PPMImage * ppm);

PPMImage * mirror( PPMImage * ppm);

PPMImage * thumbnail( PPMImage * ppm, long int scale);

PPMImage * nup( PPMImage * ppm, long int scale);

#endif
