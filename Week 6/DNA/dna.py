import csv
from datetime import date
import sys


def main():
    dna_list = []
    dna_keys = None
    dna_compare = {}

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python DNA.py database.csv sequence.csv")

    # TODO: Read database file into a variable
    with open(f"{sys.argv[1]}", "r") as file:
        database = csv.DictReader(file)
        for row in database:
            sample = row
            # sample.pop('name')
            dna_list.append(sample)
            dna_keys = (database.fieldnames)

    for i in range(1, len(dna_keys)):
        dna_compare[dna_keys[i]] = 0

    # TODO: Read DNA sequence file into a variable
    with open(f"{sys.argv[2]}", "r") as file:
        sequence = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    for i in range(1, len(dna_keys)):
        match = longest_match(sequence, dna_keys[i])
        dna_compare[dna_keys[i]] = match

    # TODO: Check database for matching profiles
    for i in range(len(dna_list)):
        condition = True
        for key, value in (dna_list[i]).items():
            if key != 'name':
                if int(value) != int(dna_compare[key]):
                    condition = False
                else:
                    pass
            else:
                pass
        if condition == True:
            print(dna_list[i]['name'])
            return
        else:
            pass
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
