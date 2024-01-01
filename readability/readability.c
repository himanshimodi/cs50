#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Initializing functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Gets text to determine grade of
    string text = get_string("Text:");
    // Prints the text inputted
    //printf("%s\n", text);
    printf("%i\n", count_letters(text));
    printf("%i\n", count_words(text));
    printf("%i\n", count_sentences(text));
    int word_number = count_words(text);
    // Average letters and sentences per 100 words
    float L = (count_letters(text) * 100.0 / word_number);
    printf("%f\n", L);
    float S = (count_sentences(text) * 100.0 / word_number);
    printf("%f\n", S);
    // Calculating index by formula
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    //printf("%i\n", index);

    // Possible outputs
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Function to count the number of letters, returns an integer
int count_letters(string text)
{
    int letters = 0;
    // Iterate over the string
    for (int i = 0; i < strlen(text); i++)
    {
        // Pick out and assign a character
        char let = text[i];
        if (islower(let) || isupper(let))
        {
            letters += 1;
        }
    }
    return letters;

}

// Function to count number of words
// Returns an Int

int count_words(string text)
{
    int counter = 1;

    // Iterate over the string
    for (int j = 0; j < strlen(text); j++)
    {
        char lett = text[j];
        // Check if character is a space
        if (lett == 32)
        {
            // Increment the counter
            counter++;
        }

    }
    // Return counter
    return counter;
}

// Function which counts the number of sentences
// Returns an int

int count_sentences(string text)
{
    int counter = 0;
    // Iterate through the string
    for (int k = 0; k < strlen(text); k++)
    {
        char lett = text[k];
        // If the character is a . ? or ! increase the counter
        if (lett == 46 || lett == 63 || lett == 33)
        {
            counter++;
        }
    }
    return counter;
}