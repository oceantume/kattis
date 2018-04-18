#include <stdio.h>

char s_quadrants[4] = {
	'2',
	'3',
	'1',
	'4'
};

int main()
{
	int x, y;
	
	x = fgetc(stdin) == '-' ? -1 : 1;
	
	while (fgetc(stdin) != '\n');

	y = fgetc(stdin) == '-' ? -1 : 1;

	// see https://stackoverflow.com/a/4609795/6520209
	fputc(s_quadrants[2 + (0 < x) - (x < 0) - (0 < y)], stdout);

	return 0;
}
