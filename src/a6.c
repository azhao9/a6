/* a6.c
 *
 * Aleck Zhao azhao9
 * Noah Halpern nhalper1
 * 14 October, 2016
 *
 * Main for image manipulation.
 */

#include "menuUtil.h"
#include "ppmIO.h"

int main () {
	display();
	readOption();

	FILE *in = fopen("../data/nika.ppm", "r");

	Image *img;
	img = readImage(in);
	
	FILE *out = fopen("test.ppm", "wb");
	writeImage(out, img);
	
	// close files
	fclose(in);
	fclose(out);

	// free dynamically allocted memory
	free((*img).pixels);
	free(img);
	img = NULL;

	return 0;
	
}
