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

	FILE *fp = fopen("../data/nika.ppm", "r");

	Image *im = read(fp);
	Image pic = *im;
	
	fclose(fp);

	FILE *out = fopen("test.ppm", "wb");

	write(out, im);

	fclose(out);	

	printf("%d %d\n", pic.rows, pic.cols);
	
	return 0;
	
}
