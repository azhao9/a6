/* pixel_image.h
 *
 * Aleck Zhao azhao9
 * Noah Halpern nhalper1
 * 14 October, 2016
 *
 * Defines structs for Pixels and Images
 */

struct Pixel_t {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

typedef struct Pixel_t Pixel;

struct Image_t {
	Pixel* pixels;
	int rows;
	int cols;
};

typedef struct Image_t Image;
