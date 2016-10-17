/* imageManip.h
 *
 * Aleck Zhao azhao9
 * Noah Halpern nhalper1
 * 16 October, 2016
 *
 * Function headers for image manipulation.
 */


// crops an image
Image* crop(void *old);

// inverts an image
void invert(void *old);

// swaps color channels of an image
void swap(void *old);

// converts an image to grayscale
void grayscale(void *old);

// changes the brightness of an image
void* brightness(void *old);

// changes the contrast of an image
void* contrast(void *old);

// blurs an image
void* blur(void *old);

// sharpens an image
void* sharpen(void *old);
