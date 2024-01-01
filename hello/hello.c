#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Gets User's name
    string name = get_string("What's your name?:");
    // Prints users name
    printf("hello, %s \n", name);
}