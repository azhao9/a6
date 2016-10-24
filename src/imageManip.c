/* imageManip.c
 *
 * Aleck Zhao azhao9
 * Noah Halpern nhalper1
 * 24 October, 2016
 *
 * Functions to manipulate images.
 */

#include "pixel_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265

// crops an image
Image* crop(Image *old) {
	char a[30];
	char b[30];
	char c[30];
	char d[30];

	// reads coordinates
	scanf("%s %s %s %s", a, b, c, d);

	int x1 = atoi(a);
	int y1 = atoi(b);
	int x2 = atoi(c);
	int y2 = atoi(d);

	if (x2 < x1 || y2 < y1) {
		// not properly formatted input
		fprintf(stderr, "improper order of coordinates\n");
		return NULL;
	}

	Pixel *oldPix = (*old).pixels;
	int oldCols = (*old).cols;
	int oldRows = (*old).rows;

	if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) {
		// can't be less than 0
		fprintf(stderr, "Coordinates must be positive\n");
		return NULL;
	}

	if (x1 > oldCols || x2 > oldCols || y1 > oldRows || y2 > oldRows) {
		// can't be larger than size of picture
		fprintf(stderr, "Can't be outside the picture\n");
		return NULL;
	}

	if ((strcmp(a, "0") && !x1) || (strcmp(b, "0") && !y1) || 
			(strcmp(c, "0") && !x2) || (strcmp(d, "0") && !y2)) {
		// invalid input
		fprintf(stderr, "Invalid input\n");
		return NULL;
	}	       

	int newRows = (y2 - y1);
	int newCols = (x2 - x1);

	// allocate a new pixel array
	Pixel *newPix = malloc(sizeof(Pixel) * newRows * newCols);

	int newIndex = 0;

	printf("Cropping region from (%d, %d) to (%d, %d)...\n", x1, y1, x2, y2);
	for (int r = y1; r < y2; r++) {
		for (int c = x1; c < x2; c++) {
			int oldIndex = r * oldCols + c;

			newPix[newIndex] = oldPix[oldIndex];
			newIndex++;
		}
	}

	Image* new = malloc(sizeof(Image));

	new->pixels = newPix;
	new->rows = newRows;
	new->cols = newCols;

	// frees old image and pixels
	free(oldPix);
	free(old);
	oldPix = NULL;
	old = NULL;

	return new;
}

// inverts an image
void invert(Image *old) {
	Pixel *pix = (*old).pixels;
	int rows = (*old).rows;
	int cols = (*old).cols;

	printf("Inverting intensity...\n");
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			int index = r * cols + c;

			// bitwise inverse
			pix[index].red = ~pix[index].red;
			pix[index].green = ~pix[index].green;
			pix[index].blue = ~pix[index].blue;
		}
	}

}

// swaps color channels of an image
void swap(Image *old) {	
	Pixel *pix = (*old).pixels;
	int rows = (*old).rows;
	int cols = (*old).cols;

	printf("Swapping color channels...\n");
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			int index = r * cols + c;

			unsigned char temp = pix[index].red;

			pix[index].red = pix[index].green;
			pix[index].green = pix[index].blue;
			pix[index].blue = temp;
		}
	}
}

// converts an image to grayscale
void grayscale(Image *old) {
	Pixel *pix = (*old).pixels;
	int rows= (*old).rows;
	int cols = (*old).cols;

	printf("Converting to grayscale...\n");
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			int index = r * cols + c;
			unsigned char red = pix[index].red;
			unsigned char green = pix[index].green;
			unsigned char blue = pix[index].blue;

			unsigned char gray = 0.30*red + 0.59*green + 0.11*blue;

			pix[index].red = gray;
			pix[index].green = gray;
			pix[index].blue = gray;


		}
	}
}

// saturation helper function
unsigned char sat(double num){

	if(num>255){
		num = 255;
	}
	else if(num<0){
		num = 0;
	}

	return (unsigned char)num;

}


// changes the brightness of an image
void brightness(Image *old) {
	char a[30];

	scanf("%s", a);

	int adj = atoi(a);

	Pixel *pix = (*old).pixels;
	int rows= (*old).rows;
	int cols = (*old).cols;

	printf("Adjusting brightness by %s...\n", a);

	for (int r = 0; r < rows; r++){
		for (int c = 0; c < cols; c++){
			int index = r * cols + c;

			pix[index].red = sat(pix[index].red + adj);
			pix[index].green = sat(pix[index].green + adj);
			pix[index].blue = sat(pix[index].blue + adj);
		}
	}

}

// helper function to adjust contrast
unsigned char contrastHelper(unsigned char old, double adj){

	double temp = ((double)old)/255 - 0.5;

	temp *= adj;

	temp = temp + 0.5;
	temp = temp * 255;
	return sat(temp);

}

// changes the contrast of an image
void contrast(Image *old) {
	char a[30];

	scanf("%s", a);

	double adj = atof(a);

	Pixel *pix = (*old).pixels;
	int rows= (*old).rows;
	int cols = (*old).cols;

	printf("Adjusting contrast by %.2f...\n", adj);

	for(int r = 0; r < rows; r++){
		for(int c = 0; c < cols; c++){
			int index = r * cols + c;

			pix[index].red = contrastHelper(pix[index].red, adj);
			pix[index].green = contrastHelper(pix[index].green, adj);
			pix[index].blue = contrastHelper(pix[index].blue, adj);
		}
	}


}

// generates a 2D symmetric Gaussian matrix 
double* gauss(double sigma) {

	int size = (int)(sigma * 10);
	if (size % 2 == 0) {
		size++;
	}

	double* mat = malloc(sizeof(double) * size * size);

	int center = (size - 1) / 2;

	// fills matrix with Gaussian values
	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			int index = size * r + c;

			int dx = c - center;
			int dy = r - center;

			mat[index] = (1.0 / (2.0 * PI * sigma*sigma)) * exp(-(dx*dx + dy*dy) / (2 * sigma*sigma));
		}
	}

	return mat;


}

// helper function to overlay Gaussian matrix on a specific pixel
Pixel* blurHelper(double* gmat, int size, int row, int col, Image* img) {
	// sum of Gaussian entries
	double gauss_sum = 0;

	// sum of pixel values
	double red_sum = 0;
	double green_sum = 0;
	double blue_sum = 0;

	// center of Gaussian matrix
	int center = (size - 1) / 2;
	
	for (int r = -center; r <= center; r++) {
		for (int c = -center; c <= center; c++) {
			// if within image boundaries
			if (r + row >= 0 && r + row < img->rows && c + col >= 0 && c + col < img->cols) {
				// Gaussian indices
				int g_r = r + center;
				int g_c = c + center;
				int g_ind = g_r * size + g_c;

				// image indices
				int i_r = r + row;
				int i_c = c + col;
				int i_ind = i_r * img->cols + i_c;

				// Gaussian value
				double g_val = gmat[g_ind];

				double red = (img->pixels)[i_ind].red * g_val;
				double green = (img->pixels)[i_ind].green * g_val;
				double blue = (img->pixels)[i_ind].blue * g_val;

				// update sums
				gauss_sum += g_val;
				red_sum += red;
				green_sum += green;
				blue_sum += blue;
			}
		}
	}

	// computes weighted average
	double new_red = red_sum / gauss_sum;
	double new_green = green_sum / gauss_sum;
	double new_blue = blue_sum / gauss_sum;

	Pixel* new_pix = malloc(sizeof(Pixel));

	new_pix->red = (unsigned char)new_red;
	new_pix->green = (unsigned char)new_green;
	new_pix->blue = (unsigned char)new_blue;

	return new_pix;
}

// blurs an image
Image* blur(Image *old) {

	char a[30];
	scanf("%s", a);
	double sigma = atof(a);
	double* mat = gauss(sigma);

	// calculates size of Gaussian matrix for local use
	int size = (int)(sigma * 10);
	if (size % 2 == 0) {
		size++;
	}

	Image* new_img = malloc(sizeof(Image));
	new_img->pixels = malloc(sizeof(Pixel) * old->rows * old->cols);

	printf("Applying blur filter, sigma %.2f...\n", sigma);
	for (int r = 0; r < old->rows; r++) {
		for (int c = 0; c < old->cols; c++) {
			int index = r * old->cols + c;
			Pixel* temp = blurHelper(mat, size, r, c, old);

			(new_img->pixels)[index].red = temp->red;
			(new_img->pixels)[index].green = temp->green;
			(new_img->pixels)[index].blue = temp->blue;

			free(temp);
		}
	}

	new_img->rows = old->rows;
	new_img->cols = old->cols;

	free(mat);

	return new_img;

}


// sharpens an image
void sharpen(Image *old) {

	char a[30];
	char b[30];

	scanf("%s %s", a, b);

	double sigma = atof(a);
	double i = atof(b);

	///////////////////////////////////////////////////////////////////////////
	// blur function
	///////////////////////////////////////////////////////////////////////////
	double* mat = gauss(sigma);

	// calculates size of Gaussian matrix for local use
	int size = (int)(sigma * 10);
	if (size % 2 == 0) {
		size++;
	}

	Image* new_img = malloc(sizeof(Image));
	new_img->pixels = malloc(sizeof(Pixel) * old->rows * old->cols);

	for (int r = 0; r < old->rows; r++) {
		for (int c = 0; c < old->cols; c++) {
			int index = r * old->cols + c;
			Pixel* temp = blurHelper(mat, size, r, c, old);

			(new_img->pixels)[index].red = temp->red;
			(new_img->pixels)[index].green = temp->green;
			(new_img->pixels)[index].blue = temp->blue;

			free(temp);
		}
	}

	new_img->rows = old->rows;
	new_img->cols = old->cols;

	free(mat);
	//////////////////////////////////////////////////////////////////////////
	
	Pixel* old_pix = old->pixels;
	Pixel* new_pix = new_img->pixels;

	printf("Applying sharpen filter, sigma %.2f, intensity %.2f...\n", sigma, i);
	for (int r = 0; r < old->rows; r++) {
		for (int c = 0; c < old->cols; c++) {
			int index = r * old->cols + c;
			int red_diff = old_pix[index].red - new_pix[index].red;
			int green_diff = old_pix[index].green - new_pix[index].green;
			int blue_diff = old_pix[index].blue - new_pix[index].blue;

			old_pix[index].red = sat(old_pix[index].red + i * red_diff);
			old_pix[index].green = sat(old_pix[index].green + i * green_diff);
			old_pix[index].blue = sat(old_pix[index].blue + i * blue_diff);
		}
	}

	free(new_img->pixels);
	free(new_img);
			
}

