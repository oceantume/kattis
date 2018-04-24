#include <stdio.h>
#include <string.h>

// support for msvc
#ifdef _MSC_VER
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif

// https://stackoverflow.com/a/27999517/6520209
static int getint(void)
{
	int c, n;

	n = getchar_unlocked() - '0';
	while ((c = getchar_unlocked()) >= '0')
		n = 10 * n + c - '0';

	return n;
}

#define SIMON_SAYS "Simon says "
#define SIMON_SAYS_SIZE (sizeof(SIMON_SAYS))
#define SIMON_SAYS_LEN (SIMON_SAYS_SIZE - 1)

int main()
{
	char command[102];
	int n = getint(), count = 0;

	while (n--) {
		count = 0;

		int index = 0;
		while ((command[index++] = getchar_unlocked()) != '\n');

		if (!strncmp(command, SIMON_SAYS, SIMON_SAYS_LEN)) {
			for (int i = SIMON_SAYS_LEN; i < index; i++) {
				putchar_unlocked(command[i]);
			};
		}
	}

	return 0;
}
