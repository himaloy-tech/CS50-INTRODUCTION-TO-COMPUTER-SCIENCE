amount = -1
coins = 0

while (amount < 0):
    try:
        amount = float(input("Change owed: "))
    except ValueError:
        pass

# Dollars to cents
amount = round(amount * 100)

# Check number of quaters(25)
while (amount > 24):
    amount = amount - 25
    coins += 1

# Check number of dimes(10)
while (amount > 9):
    amount = amount - 10
    coins += 1


# Check number of nickels(5)
while (amount > 4):
    amount = amount - 5
    coins += 1

print(coins + amount)