/* imageManip.c
 *
 * Aleck Zhao azhao9
 * Noah Halpern nhalper1
 * 16 October, 2016
 *
 * Functions to manipulate images.
 */

#include "pixel_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// crops an image
Image* crop(Image *old) {
    char a[30];
    char b[30];
    char c[30];
    char d[30];

    // reads coordinates
    scanf("%s %s %s %s", a, b, c, d);

    int x1 = atoi(a);
    int y1 = atoi(b);
    int x2 = atoi(c);
    int y2 = atoi(d);

    if (x2 < x1 || y2 < y1) {
        // not properly formatted input
        fprintf(stderr, "improper order of coordinates\n");
        return NULL;
    }

    Pixel *oldPix = (*old).pixels;
    int oldCols = (*old).cols;
    int oldRows = (*old).rows;

    if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) {
        // can't be less than 0
        fprintf(stderr, "Coordinates must be positive\n");
        return NULL;
    }

    if (x1 > oldCols || x2 > oldCols || y1 > oldRows || y2 > oldRows) {
        // can't be larger than size of picture
        fprintf(stderr, "Can't be outside the picture\n");
        return NULL;
    }

    if ((strcmp(a, "0") && !x1) || (strcmp(b, "0") && !y1) || 
            (strcmp(c, "0") && !x2) || (strcmp(d, "0") && !y2)) {
        // invalid input
        fprintf(stderr, "Invalid input\n");
        return NULL;
    }	       

    int newRows = (y2 - y1);
    int newCols = (x2 - x1);

    // allocate a new pixel array
    Pixel *newPix = malloc(sizeof(Pixel) * newRows * newCols);

    int newIndex = 0;

    printf("Cropping region from (%d, %d) to (%d, %d)...\n", x1, y1, x2, y2);
    for (int r = y1; r < y2; r++) {
        for (int c = x1; c < x2; c++) {
            int oldIndex = r * oldCols + c;

            newPix[newIndex] = oldPix[oldIndex];
            newIndex++;
        }
    }

    Image* new = malloc(sizeof(Image));

    (*new).pixels = newPix;
    (*new).rows = newRows;
    (*new).cols = newCols;

    // frees old image and pixels
    free(oldPix);
    free(old);
    oldPix = NULL;
    old = NULL;

    return new;
}

// inverts an image
void invert(Image *old) {
    Pixel *pix = (*old).pixels;
    int rows = (*old).rows;
    int cols = (*old).cols;

    printf("Inverting intensity...\n");
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int index = r * cols + c;

            // bitwise inverse
            pix[index].red = ~pix[index].red;
            pix[index].green = ~pix[index].green;
            pix[index].blue = ~pix[index].blue;
        }
    }

}

// swaps color channels of an image
void swap(Image *old) {	
    Pixel *pix = (*old).pixels;
    int rows = (*old).rows;
    int cols = (*old).cols;

    printf("Swapping color channels...\n");
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int index = r * cols + c;

            unsigned char temp = pix[index].red;

            pix[index].red = pix[index].green;
            pix[index].green = pix[index].blue;
            pix[index].blue = temp;
        }
    }
}

// converts an image to grayscale
void grayscale(Image *old) {
    Pixel *pix = (*old).pixels;
    int rows= (*old).rows;
    int cols = (*old).cols;

    printf("Converting to grayscale...\n");
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int index = r * cols + c;
            unsigned char red = pix[index].red;
            unsigned char green = pix[index].green;
            unsigned char blue = pix[index].blue;

            unsigned char gray = 0.30*red + 0.59*green + 0.11*blue;

            pix[index].red = gray;
            pix[index].green = gray;
            pix[index].blue = gray;


        }
    }
}

// saturation helper function
unsigned char sat(double num){

    if(num>255){
        num = 255;
    }
    else if(num<0){
        num = 0;
    }

    return (unsigned char)num;

}


// changes the brightness of an image
void brightness(Image *old) {
    char a[30];

    scanf("%s", a);

    int adj = atoi(a);

    Pixel *pix = (*old).pixels;
    int rows= (*old).rows;
    int cols = (*old).cols;

    printf("Adjusting brightness by %s...\n", a);

    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            int index = r * cols + c;

            pix[index].red = sat(pix[index].red + adj);
            pix[index].green = sat(pix[index].green + adj);
            pix[index].blue = sat(pix[index].blue + adj);
        }
    }

}

unsigned char contrastHelper(unsigned char old, double adj){

    double temp = ((double)old)/255 - 0.5;

    temp *= adj;

    temp = temp + 0.5;
    temp = temp * 255;
    return sat(temp);

}

// changes the contrast of an image
void contrast(Image *old) {
    char a[30];

    scanf("%s", a);

    double adj = atof(a);

    Pixel *pix = (*old).pixels;
    int rows= (*old).rows;
    int cols = (*old).cols;

    printf("Adjusting contrast by %.2f...\n", adj);

    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            int index = r * cols + c;
            
            pix[index].red = contrastHelper(pix[index].red, adj);
            pix[index].green = contrastHelper(pix[index].green, adj);
            pix[index].blue = contrastHelper(pix[index].blue, adj);
        }
    }


}

// blurs an image
void blur(Image *old) {
    old = NULL;
    if (old == NULL) {
        printf("Feature not yet implemented\n");
    }
}

// sharpens an image
void sharpen(Image *old) {
    old = NULL;
    if (old == NULL) {
        printf("Feature not yet implemented\n");
    }
}



