#include <stdio.h>
#include <string.h>

// support for msvc
#ifdef _MSC_VER
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif

#define putstring(str) do { for(unsigned i = 0; str[i] != '\0'; i++) putchar_unlocked(str[i]); } while(0)

// https://stackoverflow.com/a/27999517/6520209
static int getint(void)
{
	int c, n;

	n = getchar_unlocked() - '0';
	while ((c = getchar_unlocked()) >= '0')
		n = 10 * n + c - '0';

	return n;
}



int main()
{
	char c, map[26];
	int n = getint(), count = 0;

	while (n--) {
		count = 0;
		memset(map, 0, sizeof(map));
		while ((c = getchar_unlocked()) != '\n') {
			if ((c >= 'a' && c <= 'z') && !(map[c - 'a']++)) {
				count++;
			} else if ((c >= 'A' && c <= 'Z') && !(map[c - 'A']++)) {
				count++;
			}
		}

		if (count == 26) {
			putstring("pangram\n");
		} else {
			putstring("missing ");

			for (int i = 0; i < 26; i++) {
				if (!map[i]) putchar_unlocked('a' + i);
			}

			putchar_unlocked('\n');
		}
	}

	return 0;
}
