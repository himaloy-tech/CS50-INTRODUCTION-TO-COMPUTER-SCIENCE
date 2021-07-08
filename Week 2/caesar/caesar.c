#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "cs50.c"

// Constant variable aplhabets
const string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, string argv[])
{
    // Check "without command-line arguments or with more than one command-line argument"
    if (argc != 2)
    {
        printf("error command line argument!");
        // return exit status 1
        return 1;
    }
    // Check "command-line argument is a decimal digit"
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (argv[1][i] == '.' || atoi(argv[1]) == 0)
        {
            printf("Usage: %s key\n", argv[0]);
            // return exit status 1
            return 1;
        }
    }
    // User input
    string plain_text = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        if (isupper(plain_text[i]) && isalpha(plain_text[i]))
        {
            // Formula
            int formula = ((plain_text[i] - 65) + atoi(argv[1])) % 26;
            printf("%c", alphabets[formula]);
        }
        else if (islower(plain_text[i]) && isalpha(plain_text[i]))
        {
            // Formula
            int formula = ((plain_text[i] - 97) + atoi(argv[1])) % 26;
            printf("%c", tolower(alphabets[formula]));
        }
        else
        {
            printf("%c", plain_text[i]);
        }
    }
    // Print new line character
    printf("\n");
    // return exit status 0
    return 0;
}