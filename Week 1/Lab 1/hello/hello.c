#include <stdio.h>
// #include <cs50.h>

int main(void)
{
    // string name = get_string("What is your name? ");
    char name[100];
    printf("What is your name? ");
    gets(name);
    printf("Hello, %s\n", name);
}