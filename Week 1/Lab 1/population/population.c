#include <stdio.h>
#include "cs50.c"

int math(int population, int end);

int main(void)
{
    // Intializing variables
    int start = 0, end = 0;

    // Asking start size
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // Asking end size
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // Displaying result
    printf("Years: %i\n", math(start, end));
}

// Calculation
int math(int population, int end)
{
    int years = 0;
    for (; population < end; years++)
    {
        population = population + (population / 3) - (population / 4);
    }
    return years;
}