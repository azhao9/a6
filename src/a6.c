/* a6.c
 *
 * Aleck Zhao azhao9
 * Noah Halpern nhalper1
 * 24 October, 2016
 *
 * Main for image manipulation.
 */

#include "menuUtil.h"
#include "ppmIO.h"
#include "imageManip.h"
#include <math.h>

int main () {
	display();
	int option = readOption();

	Image *img = NULL;

	while (option != 0) {
		if (option == -1) {
			printf("Invalid input, please try again\n");
		}
		else if (option == 1) {
			// read
			char path[100];
			scanf("%s", path);
			FILE *toRead = fopen(path, "r");
			if (toRead != NULL) {
				printf("Reading from %s...\n", path);
				img = readImage(toRead);
				fclose(toRead);
			} else {
				printf("Couldn't open file %s...\n", path);
			}


		} else if (option == 2) {
			// write
			char path[100];
			scanf("%s", path);
			FILE *toWrite = fopen(path, "wb");

			if (img == NULL) {
				printf("Nothing read yet...\n");
			} else if (toWrite != NULL) {
				printf("Writing to %s...\n", path);
				writeImage(toWrite, img);
				fclose(toWrite);
			} else {
				printf("Couldn't open file %s...\n", path);
			}


		} else if (option == 3) {
			// crop

			if (img == NULL) {
				printf("Nothing read yet...\n");
			} else {
				Image *temp = crop(img);

				if (temp != NULL) {
					img = temp;
				} else {
					printf("Cropping failed :(\n");
				}
			}

		} else if (option == 4) {
			// invert
			if (img == NULL) {
				printf("Nothing read yet...\n");
			} else {
				invert(img);
			}
		} else if (option == 5) {
			// swap
			if (img == NULL) {
				printf("Nothing read yet...\n");
			} else {
				swap(img);
			}
		} else if (option == 6) {
			// grayscale
			if (img == NULL) {
				printf("Nothing read yet...\n");
			} else {
				grayscale(img);
			}
		} else if (option == 7) {
			// blur
			if (img == NULL) {
				printf("Nothing read yet...\n");
			} else {
				Image* temp = blur(img);

				if (temp) {
					free(img->pixels);
					free(img);

					img = temp;
				}
			}
		} else if (option == 8) {
			// sharpen
			if (img == NULL) {
				printf("Nothing read yet...\n");
			} else {
				sharpen(img);
			}
		} else if (option == 9) {
			// brighten 
			if (img == NULL) {
				printf("Nothing read yet...\n");
			} else {
				brightness(img);
			}
		} else if (option == 10) {
			// contrast
			if (img == NULL) {
				printf("Nothing read yet...\n");
			} else {
				contrast(img);
			}
		}

		display();
		option = readOption();
	}

	printf("Goodbye!\n");
	if (img) {
		// if not null pointer
		free((*img).pixels);
		free(img);
	}

	return 0;
	
}
