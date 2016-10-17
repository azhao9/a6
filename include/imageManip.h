/* imageManip.h
 *
 * Aleck Zhao azhao9
 * Noah Halpern nhalper1
 * 16 October, 2016
 *
 * Function headers for image manipulation.
 */


// crops an image
Image* crop(Image *old);

// inverts an image
void invert(Image *old);

// swaps color channels of an image
void swap(Image *old);

// converts an image to grayscale
Image* grayscale(Image *old);

// changes the brightness of an image
Image* brightness(Image *old);

// changes the contrast of an image
Image* contrast(Image *old);

// blurs an image
Image* blur(Image *old);

// sharpens an image
Image* sharpen(Image *old);
