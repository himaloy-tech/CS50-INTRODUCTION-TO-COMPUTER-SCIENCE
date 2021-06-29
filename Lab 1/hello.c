#include <stdio.h>

int main(void)
{
    char name[100];
    printf("What is your name? ");
    gets(name);
    printf("Hello, %s\n", name);
}