#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
	int i;
	
	srand(time(NULL));
	for (i=0;i<100;i++)
		printf("%08x\n", rand());
		

    uint64_t id;
    srand(time(NULL));

    id = rand();
    id = id | ((uint64_t)time(NULL) << 16);

printf("%08x\n", id);
	return 0;
}
