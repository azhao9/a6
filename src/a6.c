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
#include "imageManip.h"

int main () {
	display();

	FILE *in = fopen("../data/nika.ppm", "r");

	Image *img;
	img = readImage(in);
	
	FILE *out = fopen("test.ppm", "wb");
	
	// Image* new = crop(img);
	
	//invert(img);
	swap(img);
	swap(img);
	writeImage(out, img);
	// close files
	fclose(in);
	fclose(out);

	return 0;
	
}
