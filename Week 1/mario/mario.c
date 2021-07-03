#include <stdio.h>
#include "cs50.c"

int main(void)
{
    // Get height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Calculation
    for (int n = 0; n < height; n++)
    {
        // Loop for number of space
        for (int x = 1; x < (height - n); x++)
        {
            printf(" ");
        }
        // Loop for number of #
        for (int y = -1; y < n; y++)
        {
            printf("#");
        }
        // New line character
        printf("\n");
    }
}