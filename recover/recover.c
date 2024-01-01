#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int BLOCK_SIZE = 512;
typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    // Check if there is one command line argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    else
    {
        // Open the file
        FILE *file = fopen(argv[1], "r");

        // Check if the file is successfully opened
        if (file == NULL)
        {
            printf("Could not open file\n");
            return 2;
        }
        else
        {
            BYTE buffer[BLOCK_SIZE];
            FILE *img = NULL;
            char filename[8];
            int count = 0;
            int fileopen = 0;
            // Read the file
            // Check if data read is 512 bytes long
            while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
            {

                // Check for header of jpeg file
                if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
                {
                    // Define pointer to output

                    // Check if first file opened
                    if (fileopen == 1)
                    {
                        fclose(img);

                    }
                    else if (fileopen == 0)
                    {
                        fileopen = 1;
                    }
                    sprintf(filename, "%03i.jpg", count);
                    img = fopen(filename, "w");
                    count++;


                }
                if (fileopen == 1)
                {
                    fwrite(buffer, 1, BLOCK_SIZE, img);
                }

            }
            fclose(img);
        }
        fclose(file);

    }


}