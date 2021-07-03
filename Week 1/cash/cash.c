#include <stdio.h>
#include "cs50.c"
#include <math.h>

int main(void)
{
    // Initializing variables;
    float amount;
    int coins = 0;

    // User input
    do
    {
        amount = get_float("Change amount: ");
    }
    while (amount < 0);

    // Convert Dollars to cents
    amount = round(amount * 100);

    // Check number of quaters(25)
    while (amount > 24)
    {
        amount = amount - 25;
        coins++;
    }
    
    // Check number of dimes(10)
    while (amount > 9)
    {
        amount = amount - 10;
        coins++;
    }

    // Check number of nickels(5)
    while (amount > 4)
    {
        amount = amount - 5;
        coins++;
    }

    // Check number of pennies
    coins = amount + coins;

    printf("%i\n", coins);
}
