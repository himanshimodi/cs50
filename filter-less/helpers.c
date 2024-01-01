#include "helpers.h"
#include <math.h>
BYTE sepiachecker(float colour);
int getblur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int colno);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            BYTE originalBlue = image[i][j].rgbtBlue;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalRed = image[i][j].rgbtRed;
            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            image[i][j].rgbtBlue = sepiachecker(sepiaBlue);
            BYTE a = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = sepiachecker(sepiaRed);
            BYTE b = image[i][j].rgbtRed;
            image[i][j].rgbtGreen = sepiachecker(sepiaGreen);
            BYTE c = image[i][j].rgbtGreen;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];

        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = getblur(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = getblur(i, j, height, width, copy, 1);
            image[i][j].rgbtBlue = getblur(i, j, height, width, copy, 2);


        }
    }

}
BYTE sepiachecker(float colour)
{
    if (colour > 255)
    {
        return 255;
    }
    else if (colour < 0)
    {
        return 0;
    }
    else
    {
        return round(colour);
    }
}
// Helper function for blur
// Different inputs
// Colno means number of colour
// 0 red
// Green is 1
// Blue is 2
int getblur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int colno)
{
    int sum = 0;
    float counter = 0;

    for (int k = i - 1; k < (i + 2); k++)
    {

        for (int l = j - 1; l < (j + 2); l++)
        {
            // Check if valid
            if (k < 0 || l < 0 || k >= height || l >= width)
            {
                continue;
            }
            // Check colour
            if (colno == 0)
            {
                sum += image[k][l].rgbtRed;
            }
            else if (colno == 1)
            {
                sum += image[k][l].rgbtGreen;
            }
            else
            {
                sum += image[k][l].rgbtBlue;
            }
            counter++;


        }
    }
    return round(sum / counter);
}

// Comments