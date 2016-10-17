/* menuUtil.c
 *
 * Aleck Zhao azhao9
 * Noah Halpern nhalper1
 * 14 October, 2016
 *
 * Program to display an interactive menu and read user choice.
 */

#include "menuUtil.h"

// displays the menu
void display() {
	printf("Main menu:\n \
			\t r <filename> - read image from <filename>\n\
			\t w <filename> - write image to <filename>\n\
			\t c <x1> <y1> <x2> <y2> - crop image to the box with the given corners\n\
			\t i - invert intensities\n\
			\t s - swap color chanels\n\
			\t g - convert to grayscale\n\
			\t bl <sigma> - Gaussian blur with the given radius (sigma)\n\
			\t sh <sigma> <amt> - sharpen by given amount (intensity), with radius (sigma)\n\
			\t br <amt> - change brightness (up or down) by the given amount\n\
			\t cn <amt> - change contrast (up or down) by the given amount\n\
			\t q - quit\n");
}

// reads first argument of user input and determines what to do
int readOption() {
	printf("Enter choice: ");

	char input[30];

	// reads first arg
	scanf("%s", input);

	if (!strcmp(input, "r")) {
		return 1;
	} else if (!strcmp(input, "w")) {
		return 2;
	} else if (!strcmp(input, "c")) {
		return 3;
	} else if (!strcmp(input, "i")) {
		return 4;
	} else if (!strcmp(input, "s")) {
		return 5;
	} else if (!strcmp(input, "g")) {
		return 6;
	} else if (!strcmp(input, "bl")) {
		return 7;
	} else if (!strcmp(input, "sh")) {
		return 8;
	} else if (!strcmp(input, "br")) {
		return 9;
	} else if (!strcmp(input, "cn")) {
		return 10;
	} else if (!strcmp(input, "q")) {
		return 0;
	} else {
		return -1;
	}
}
