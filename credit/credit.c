#include <cs50.h>
#include <stdio.h>


// Initializes checksum
bool checksum(long);

// Initialize digitchecker
int digitnumber(long number);

int main(void)
{
    // Takes input from user
    long number = get_long("Enter Credit Card Number:");
    // Gets if number is valid or not
    bool x = checksum(number);
    // Gets number of digits in the number
    int digits = digitnumber(number);
    // Finds first or first two digits of the numbers
    int twodigamex = number / 10000000000000;
    int digvisa = number / 1000000000000000;
    int digvisa1 = number / 1000000000000;
    int digm = number / 100000000000000;
    if (x)
    {
        // Checks if 15 digits and starts with amex numbers
        if (digits == 15)
        {
            if (twodigamex == 34 || twodigamex == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }

        }
        // Checks if digits are 16 and then master or visa
        else if (digits == 16)
        {
            if (digvisa == 4)
            {
                printf("VISA\n");
            }
            // Checks if mastercard starting numbers
            else if (digm == 51 || digm == 52 || digm == 53 || digm == 54 || digm == 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }

        }
        // Checks if diigts are 13 and if starts with 4
        else if (digits == 13)
        {
            if (digvisa1 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // If sum is not divisible by 10
    else
    {
        printf("INVALID\n");
    }

}


// Checks if number is valid
bool checksum(long number)
{
    long n = number;
    int counter = 1;
    int sum = 0;
    while (n != 0)
    {
        // If the number is at even position from the end
        if ((counter % 2) == 0)
        {
            // If the number is two digits we separate them
            if ((2 * (n % 10)) > 9)
            {
                sum += ((2 * (n % 10)) % 10);
                sum += ((2 * (n % 10)) / 10);
                n /= 10;
                counter ++;

            }
            else
            {
                sum += (2 * (n % 10));
                n /= 10;
                counter ++;
            }
        }
        else
        {
            // If the number is even we just add without doubling
            sum += (n % 10);
            n /= 10;
            // Increment the counter to parse from the back
            counter ++;
        }

    }
    // Check and return if the sum is divisible by 10
    return ((sum % 10) == 0);

}

int digitnumber(long number)
{
    // Checks for how many digits the number has
    // returns digits as an integer
    long numb = number;
    int digits = 0;
    while (numb != 0)
    {
        numb /= 10;
        digits ++;
    }
    // returns digits
    return digits;
}


