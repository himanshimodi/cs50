# TODO
from cs50 import get_int
# Get user input
height = 0
while (height < 1 or height > 8):
    height = get_int("Height:")

row = 1
# Iterate through rows
for i in range(height):
    # Print spaces then hashes
    for j in range(height - row):
        print(" ", end="")

    for k in range(row):
        print("#", end="")

    # Print middle space
    print("  ", end="")

    # Print end hashes
    for k in range(row):
        print("#", end="")
    # Go to the next line
    print("")
    row += 1