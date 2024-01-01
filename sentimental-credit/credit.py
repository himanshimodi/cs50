# TODO

from cs50 import get_int


def main():
    numb = get_int("Number:")
    str_numb = str(numb)
    length = len(str_numb)
    first = int(str_numb[0])
    two = int(str_numb[0:2])
    mastercase = [51, 52, 53, 54, 55]

    # If numb length doesnt match
    if (length != 13 and length != 15 and length != 16):
        print("INVALID")
    elif (Luhn(numb)):
        if (length == 15):
            if (two == 34 or two == 37):
                print("AMEX")
            else:
                print("INVALID")
        elif (length == 13):
            if (first == 4):
                print("VISA")
            else:
                print("INVALID")
        else:
            if (two in mastercase):
                print("MASTERCARD")
            elif (first == 4):
                print("VISA")
            else:
                print("INVALID")
    else:
        print("INVALID")


def Luhn(numb):
    # Luhns algorithm
    # returns bool
    str_numb = str(numb)
    length = len(str_numb)
    count = 1
    sum = 0

    while (count < length + 1):
        digit = numb % 10
        numb = numb // 10

        # Check if double or not
        if (count % 2 == 0):
            digit *= 2
            if (digit >= 10):
                sum += digit // 10
                sum += digit % 10
            else:
                sum += digit
        else:
            sum += digit

        # Increment digit
        count += 1
        str_numb = str(numb)
    return (sum % 10) == 0

# CAll to main
# Comment
# Comment


if __name__ == '__main__':
    main()