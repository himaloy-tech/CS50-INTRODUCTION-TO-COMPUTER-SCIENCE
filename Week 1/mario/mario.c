#include <stdio.h>
// #include <cs50.h>
int main(void)
{
    // Get height
    int height;
    do
    {
        // height = get_int("Height: ");
        printf("Height: ");
        scanf("%i", &height);
    } while(height < 1 || height > 8);

    // Calculation
    for(int n = 0; n < height; n++)
    {
        for(int x = 1; x < (height - n); x++)
        {
            printf(" ");
        }
        for(int y = -1; y < n; y++)
        {
            printf("#");
        }
        printf("\n");
    }
}