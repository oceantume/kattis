#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// support for msvc
#ifdef _MSC_VER
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif

#define putstring(str) do { for(unsigned i = 0; i < sizeof(str) - 1; i++) putchar_unlocked(str[i]); } while(0)


#define IS_BIN_PEOPLE(x) ((x) & (1<<(16)))
#define MAKE_BIN_OR_DEC_VALUE(ov, v) ((1 << (ov + 16)) + v)

int map[1000][1000];

void fill(int x, int y, int r, int c, int ov, int nv);

// https://stackoverflow.com/a/27999517/6520209
static int parseint(void)
{
	int c, n;
	
	n = getchar_unlocked() - '0';
	while ((c = getchar_unlocked()) >= '0')
		n = 10 * n + c - '0';

	return n;
}

int main()
{
	int r = parseint(), c = parseint();
	
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			map[i][j] = (getchar_unlocked() - '0');
		}
		getchar_unlocked();
	}

	int n = parseint();

	// don't work without queries
	if (n <= 0) {
		return 0;
	}

	// map regions
	for (int i = 0, v = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			int ov = map[i][j];

			if (ov < 2) {
				int nv = MAKE_BIN_OR_DEC_VALUE(ov, ++v);
				fill(i, j, r, c, ov, nv);
			}
		}
	}

	// queries
	for (int i = 0; i < n; i++) {
		int r1 = parseint(), c1 = parseint(), 
			r2 = parseint(), c2 = parseint();

		int first = map[r1-1][c1-1], second = map[r2-1][c2-1];
		
		if (first != second)
			putstring("neither\n");
		else if (IS_BIN_PEOPLE(first))
			putstring("binary\n");
		else
			putstring("decimal\n");
	}

    return 0;
}




//
// https://github.com/erich666/GraphicsGems/blob/master/gems/SeedFill.c

typedef struct { short y, xl, xr, dy; } Segment;
/*
* Filled horizontal segment of scanline y for xl<=x<=xr.
* Parent segment was on line y-dy.  dy=1 or -1
*/

#define MAX 10000		/* max depth of stack */

#define PUSH(Y, XL, XR, DY)	/* push new segment on stack */ \
    if (sp<stack+MAX && Y+(DY)>=0 && Y+(DY)<c) \
    {sp->y = Y; sp->xl = XL; sp->xr = XR; sp->dy = DY; sp++;}

#define POP(Y, XL, XR, DY)	/* pop segment off stack */ \
    {sp--; Y = sp->y+(DY = sp->dy); XL = sp->xl; XR = sp->xr;}

void fill(int x, int y, int r, int c, int ov, int nv) {
	int l, x1, x2, dy;

	Segment stack[MAX], *sp = stack;	/* stack of filled segments */

	PUSH(y, x, x, 1);			/* needed in some cases */
	PUSH(y + 1, x, x, -1);		/* seed segment (popped 1st) */

	while (sp > stack) {
		/* pop segment off stack and fill a neighboring scan line */
		POP(y, x1, x2, dy);

		/*
		* segment of scan line y-dy for x1<=x<=x2 was previously filled,
		* now explore adjacent pixels in scan line y
		*/
		for (x = x1; x >= 0 && map[x][y] == ov; x--)
			map[x][y] = nv;
		if (x >= x1) goto skip;
		l = x + 1;
		if (l<x1) PUSH(y, l, x1 - 1, -dy);		/* leak on left? */
		x = x1 + 1;
		do {
			for (; x < r && map[x][y] == ov; x++)
				map[x][y] = nv;
			PUSH(y, l, x - 1, dy);
			if (x>x2 + 1) PUSH(y, x2 + 1, x - 1, -dy);	/* leak on right? */
		skip:	    for (x++; x <= x2 && map[x][y] != ov; x++);
			l = x;
		} while (x <= x2);
	}
}