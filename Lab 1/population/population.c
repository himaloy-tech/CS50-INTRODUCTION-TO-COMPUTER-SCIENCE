#include <stdio.h>

int math(int population, int end);

int main(void)
{
    int start = 0, end = 0, years = 0;
    do
    {
        printf("Start size: ");
        scanf("%i", &start);
    } while (start < 9);
    do
    {
        printf("End size: ");
        scanf("%i", &end);
    } while (end < start);
    printf("Years: %i\n", math(start, end));
    return 0;
}

int math(int population, int end)
{
    int years = 0;
    for(; population < end; years++)
    {
        population = population + (population/3) - (population/4);
    }
    return years;
}