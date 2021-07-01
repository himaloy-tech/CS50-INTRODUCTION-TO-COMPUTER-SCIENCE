#include <stdio.h>
// #include <cs50.h>
int main(void)
{
    // Initializing variables
    int height;
    
    // Get height
    do
    {
        // height = get_int("Height: ");
        printf("Height: ");
        scanf("%i", &height);
    }
    while (height < 1 || height > 8);

    // Calculation
    for (int n = 0; n < height; n++)
    {
        // Loop for number of spaces
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