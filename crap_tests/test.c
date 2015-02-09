#include <stdio.h>
#include <time.h>

int main()
{
	printf("%lu\n", (unsigned long)time(NULL));
	printf("%lu\n", (unsigned long)clock());
	return 0;
}
