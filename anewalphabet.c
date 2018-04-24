#include <stdio.h>

// support for msvc
#ifdef _MSC_VER
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif

#define putstring(str) do { for(unsigned i = 0; str[i] != 0; i++) putchar_unlocked(str[i]); } while(0)


char* g_map[] = {
	"@", "8", "(", "|)", "3", "#",
	"6", "[-]", "|", "_|", "|<", "1",
	"[]\\/[]", "[]\\[]", "0", "|D",
	"(,)", "|Z", "$", "']['", "|_|",
	"\\/", "\\/\\/", "}{", "`/", "2"
};

int main()
{
	char c;
	while ((c = getchar_unlocked()) != '\n') {
		if (c >= 'a' && c <= 'z') {
			putstring(g_map[c - 'a']);
		} else if (c >= 'A' && c <= 'Z') {
			putstring(g_map[c - 'A']);
		} else if ((c >= 32 && c <= 126) || c == '\t') {
			putchar_unlocked(c);
		} else {
			break;
		}
	}

	return 0;
}
