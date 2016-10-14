/* ppmIO.c
 *
 * Aleck Zhao azhao9
 * Noah Halpern nhalper1
 * 14 October, 2016
 *
 * Functions for reading and writing images.
 */

#include "pixel_image.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// reads an image from a file into an image struct
Image* read(FILE *fp) {

	char header[10];
	char rows[10];
	char cols[10];
	char colors[10];

	fscanf(fp,"%s", header);

	if (strcmp("P6", header)) {
		// not a PPM file
		return 0;
	}

	fscanf(fp, "%s", rows);
	fscanf(fp, "%s", cols);
	fscanf(fp, "%s", colors);
	while (fgetc(fp) != '\n');


	int r = atoi(rows);
	int c = atoi(cols);
	int colors_2 = atoi(colors);

	if (colors_2 != 255) {
		// not regular image
		return 0;
	}

	Pixel *pix = malloc(sizeof(Pixel) * r * c);

	int reads = fread(pix, sizeof(Pixel), r * c, fp);

	if (reads != r * c) {
		// error writing file
		return 0;
	}

	Image im;
	im.pixels = pix;
	im.rows = r;
	im.cols = c;
	Image *ptr = &im;
	return ptr;

}

// writes an image to a file
void write(FILE *out, Image *im) {
	Image pic = *im;
	Pixel *pix = pic.pixels;
	int r = pic.rows;
	int c = pic.cols;

	printf("%d %d\n", r, c);

	fprintf(out, "P6\n");
	fprintf(out, "%d %d ", r, c);
	fprintf(out, "255\n");

	fwrite(pix, sizeof(Pixel), r * c, out);	

}
