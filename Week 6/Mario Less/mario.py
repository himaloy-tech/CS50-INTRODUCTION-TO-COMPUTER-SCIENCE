height = 0

# While loop for checking height
while (not height >= 1 or not height <= 8):
    try:
        height = int(input("Height: "))
    except ValueError:

        # Do Nothing
        pass

for i in range(1, height+1):

    # Printing blank space without new line character
    print(" "*(height-i), end="")

    # For loop for printing #
    for l in range(i):

        # Printing #
        print("#", end="")

    # Adding new line character
    print("\n", end="")