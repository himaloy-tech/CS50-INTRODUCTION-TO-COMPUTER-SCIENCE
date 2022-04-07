# Intialize
words = 1
sentences = 0
letters = 0

# Alphabets
alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# User input
text = input("Text: ")

# Text Length
n = len(text)

# Number of letters
for i in range(n):
    if (text[i].upper() in alphabets):
        letters += 1
    else:
        pass

# Number of words 
for i in range(n):
    if (text[i] == " "):
        words += 1
    else:
        pass

# Number of sentences 
for i in range(n):
    if (text[i] == '.' or text[i] == '?' or text[i] == '!'):
        sentences += 1
    else:
        pass

# Result
result = 0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8

# Print Result
if (result <= 0):

    print("Before Grade 1\n")

elif (result >= 16):

    print("Grade 16+\n")

else:
    print(f"Grade {round(result)}\n")
