#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char *p;
    p = malloc(20);

    strcpy(p, "Hello World!");
    printf("%s\n", p);
    printf("0x%x\n", *(p-4));

    free(p);

    return 0;
}
