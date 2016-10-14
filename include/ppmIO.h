/* ppmIO.h
 *
 * Aleck Zhao azhao9
 * Noah Halpern nhalper1
 * 14 October 2016
 *
 * Headers for reading and writing images
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pixel_image.h"

// returns a pointer to the created image
Image* read(FILE *fp);

/* returns 0 or 1 if write is successful
 * writes to out, based on im
 */
void write(FILE *out, Image* im);


