#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    // Gets height until in range 1 to 8
    do
    {
        // Gets height
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);



    // To make pyramid
    int space = height;

    for (int i = 0; i < height; i++)
    {
        // Prints spaces
        for (int j = 1; j < space; j++)
        {
            printf(" ");
        }
        space--;

        int hashes = height - space;

        // Prints #s
        for (int k = 0; k < hashes; k++)
        {
            printf("#");
        }

        // Print the middle spaces
        printf("  ");

        // Print second half of hashes
        for (int k = 0; k < hashes; k++)
        {
            printf("#");
        }
        // Go to a new line
        printf("\n");



    }


}