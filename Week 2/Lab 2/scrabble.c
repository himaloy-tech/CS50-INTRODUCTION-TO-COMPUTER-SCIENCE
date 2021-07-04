#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Alphabets
char *alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Prototypes
// int compute_score(string word);
int compute_score(char word[]);

int main(void)
{
    // Initialize variables
    char word1[50];
    char word2[50];

    // Get input words from both players
    // string word1 = get_string("Player 1: ");
    printf("Player 1: ");
    gets(word1);

    // string word2 = get_string("Player 2: ");
    printf("Player 2: ");
    gets(word2);
    
    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2 && score1 != score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1 && score1 != score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// compute_score(string word);
int compute_score(char word[])
{
    int score = 0;
    int index;

    // Convert word to uppercase and assign points
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        index = toupper(word[i]);
        if (index > 0)
        {
            // Score
            score = score + POINTS[index - 65];
        }
    }
    // return score
    return score;
}