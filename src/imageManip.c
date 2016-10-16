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

	scanf("%s %s %s %s", a, b, c, d);

	int x1 = atoi(a);
	int y1 = atoi(b);
	int x2 = atoi(c);
	int y2 = atoi(d);

	if (x2 < x1 || y2 < y1) {
		// not properly formatted input
		fprintf(stderr, "improper order of coordinates");
		return NULL;
	}

	Pixel *oldPix = (*old).pixels;
	//int oldCols = (*old).cols;

	int newRows = (y2 - y1);
	int newCols = (x2 - x1);

	// allocate a new pixel array
	Pixel *newPix = malloc(sizeof(Pixel) * newRows * newCols);

	int newIndex = 0;

	for (int r = y1; r < y2; r++) {
		for (int c = x1; c < x2; c++) {
			int oldIndex = r * (*old).cols + c;

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
Image* invert(Image *old) {
	return NULL;
}

// swaps color channels of an image
Image* swap(Image *old) {
	return NULL;
}

// converts an image to grayscale
Image* grayscale(Image *old) {
	return NULL;
}

// changes the brightness of an image
Image* brightness(Image *old) {
	return NULL;
}

// changes the contrast of an image
Image* contrast(Image *old) {
	return NULL;
}

// blurs an image
Image* blur(Image *old) {
	return NULL;
}

// sharpens an image
Image* sharpen(Image *old) {
	return NULL;
}
