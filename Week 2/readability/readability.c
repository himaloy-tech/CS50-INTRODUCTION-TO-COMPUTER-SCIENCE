#include <stdio.h>
#include "cs50.c"
#include <string.h>
#include <math.h>
#include <ctype.h>

// Alphabets
char *alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(void)
{
    // Initialize variables
    int words = 1;
    int sentences = 0;
    int letters = 0;

    // Get string
    string text = get_string("Text: ");

    // length of the string
    int n = strlen(text);

    // Count the number of letters
    for (int i = 0; i < n; i++)
    {
        if (strchr(alphabets, toupper(text[i])) != NULL)
        {
            letters++;
        }
    }

    // Count the number of words
    for (int i = 0; i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }

    // Count the number of sentences
    for (int i = 0; i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }

    // Coleman Liau formula
    float result = 0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8;

    // Print result
    if (result <= 0)
    {
        printf("Before Grade 1\n");
    }
    else if (result >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", (int)round(result));
    }
}