#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Initializing the function
string substitute(string key, string plaintext);

int main(int argc, string argv[])
{
    // If incorrect number of command line arguments are provided
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        // Get key from user input
        string key = argv[1];

        // Check if key is 26 letters long
        if (strlen(key) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

        // Run checks to see if the user input is valid
        else
        {
            int counter = 0;

            for (int i = 0; i < strlen(key); i++)
            {
                // Checking for duplicate letters
                int duplicate = 0;
                char lower_char = tolower(key[i]);
                // If character isnt another letter
                if (!isupper(key[i]) && !islower(key[i]))
                {
                    printf("Key must contain 26 characters.\n");
                    return 1;
                }
                for (int j = 0; j < strlen(key); j++)
                {
                    if (lower_char == tolower(key[j]))
                    {
                        duplicate++;
                        if (duplicate > 1)
                        {
                            printf("Duplicate letters present;\n");
                            return 1;
                        }
                    }
                }
            }
            // Get user input for plaintext
            string plaintext = get_string("plaintext:");


            // Output ciphertext
            printf("ciphertext: %s\n", substitute(key, plaintext));

        }


    }


}

// Function that converts plaintext to ciphertext
// Takes key and plaintext as input and gives ciphertext as output
string substitute(string key, string plaintext)
{

    // Creating a copy of the key but in all lowercase
    char lowerkey[strlen(key)];
    for (int i = 0; i < strlen(key); i++)
    {
        lowerkey[i] = tolower(key[i]);

    }
    // Creating a copy of key but all uppercase
    char upperkey[strlen(key)];
    for (int j = 0; j < strlen(key); j++)
    {
        upperkey[j] = toupper(key[j]);

    }
    //printf("%s\n",lowerkey);

    // Applying the cipher
    string ciphertext = plaintext;
    for (int k = 0; k < strlen(plaintext); k++)
    {
        // If the character is uppercase
        if (isupper(plaintext[k]))
        {
            int count = plaintext[k] - 65;
            ciphertext[k] = upperkey[count];
        }

        // If the character is lowercase
        if (islower(plaintext[k]))
        {
            // Counter to use for ascii
            int count1 = plaintext[k] - 97;
            ciphertext[k] = lowerkey[count1];
        }
        // If the character is neither upper nor lower
        // Just add the character as it is
        else
        {
            ciphertext[k] = plaintext[k];
        }

    }
    // Returning ciphertext, a string
    //printf("%s\n",ciphertext);
    return ciphertext;
}
