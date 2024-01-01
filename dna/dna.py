import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Incorrect Usage")

    # TODO: Read database file into a variable
    file = open(sys.argv[1], "r")
    reader = csv.DictReader(file)
    # Create a list of dictionaries from csv file
    dna_list = []
    for row in reader:
        dna_list.append(row)

    # Close the files
    file.close()

    # Get list of all dna sequences
    str_dict = dna_list[0].copy()
    del str_dict["name"]

    # TODO: Read DNA sequence file into a variable
    file1 = open(sys.argv[2], "r")
    sequence = file1.read()
    file1.close()
    # TODO: Find longest match of each STR in DNA sequence
    seq_dict = {}
    for seq in str_dict:
        seq_dict[seq] = longest_match(sequence, seq)

    # TODO: Check database for matching profiles
    for person in dna_list:
        # Check for each person if number is equal
        flag = True
        for seq in seq_dict:
            test = person[seq]
            test1 = seq_dict[seq]
            flag = flag and (seq_dict[seq] == int(person[seq]))
        # Check if flag is up
        if flag:
            print(person["name"])
            return
    print("No match")
    return


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
