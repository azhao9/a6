/* ppmIO.c
 *
 * Aleck Zhao azhao9
 * Noah Halpern nhalper1
 * 16 October, 2016
 *
 * Functions for reading and writing images.
 */

#include "pixel_image.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// reads an image from a file into an image struct
Image* readImage(FILE *fp) {

	char header[10];
	char rows[10];
	char cols[10];
	char colors[10];

	fscanf(fp,"%s", header);

	// read header, skip lines that begin with #
	while (header[0] == '#') {
		while (fgetc(fp) != '\n');
		fscanf(fp, "%s", header);
	}

	if (strcmp("P6", header)) {
		// not a PPM file
		printf("not a ppm file");
		return 0;
	}

	// reads number of cols 
	fscanf(fp, "%s", cols);
	while (rows[0] == '#') {
		while (fgetc(fp) != '\n');
		fscanf(fp, "%s", cols);
	}

	// reads number of rows
	fscanf(fp, "%s", rows);
	while (cols[0] == '#') {
		while (fgetc(fp) != '\n');
		fscanf(fp, "%s", rows);
	}

	// reads color value
	fscanf(fp, "%s", colors);
	while (colors[0] == '#') {
		while (fgetc(fp) != '\n');
		fscanf(fp, "%s", colors);
	}

	while (fgetc(fp) != '\n');


	// convert read values into ints
	int r = atoi(rows);
	int c = atoi(cols);
	int colors_2 = atoi(colors);

	if (colors_2 != 255) {
		// not regular image
		fprintf(stderr, "not a regular image\n");
		return 0;
	}

	Pixel *pix = malloc(sizeof(Pixel) * r * c);

	int reads = fread(pix, sizeof(Pixel), r * c, fp);

	if (reads != r * c) {
		// error writing file
		fprintf(stderr, "not same number of elements\n");
		return 0;
	}

	Image *im = malloc(sizeof(Image));
	(*im).pixels = pix;
	(*im).rows = r;
	(*im).cols = c;

	return im;

}

// writes an image to a file
void writeImage(FILE *out, Image *im) {
	Image pic = *im;
	Pixel *pix = pic.pixels;
	int r = pic.rows;
	int c = pic.cols;

	fprintf(out, "P6\n");
	fprintf(out, "%d %d ", c, r);
	fprintf(out, "255\n");

	fwrite(pix, sizeof(Pixel), r * c, out);	

}
