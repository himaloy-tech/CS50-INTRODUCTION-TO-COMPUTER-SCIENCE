#include "helpers.h"
#include <math.h>

// PROTOTYPE
int check(int value);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            // Calculating Average
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int red = 0;
    int green = 0;
    int blue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;
            // Calculating SepiaRed
            int sepiaRed = round((0.393 * red) + (0.769 * green) + (0.189 * blue));
            // Calcutating SepiaGreen
            int sepiaGreen = round(0.349 * red + 0.686 * green + 0.168 * blue);
            // Calculating SepiaBlue
            int sepiaBlue = round(0.272 * red + 0.534 * green + 0.131 * blue);
            // Check
            image[i][j].rgbtRed = check(sepiaRed);
            image[i][j].rgbtGreen = check(sepiaGreen);
            image[i][j].rgbtBlue = check(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int TEMP_VAR[3];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            TEMP_VAR[0] = image[i][j].rgbtBlue;
            TEMP_VAR[1] = image[i][j].rgbtGreen;
            TEMP_VAR[2] = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = TEMP_VAR[0];
            image[i][width - j - 1].rgbtGreen = TEMP_VAR[1];
            image[i][width - j - 1].rgbtRed = TEMP_VAR[2];

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

int check(int value)
{
    if (value >= 255)
    {
        return 255;
    }
    else
    {
        return value;
    }
}