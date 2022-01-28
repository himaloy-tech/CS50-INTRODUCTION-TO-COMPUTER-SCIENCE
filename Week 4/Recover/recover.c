#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    int file_number = 0;
    char filename[8];
    FILE *image = NULL;

    // Check if argument is present
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Opening file
    FILE *file = fopen(argv[1], "r");
    // Exit program if unable to open file
    if (file == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    // Buffer to store byte
    BYTE buffer[512];
    while (fread(&buffer, sizeof(BYTE), 512, file) == 512)
    {
        // Check if the follwing data is a start of a new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (file_number == 0)
            {
                sprintf(filename, "%03i.jpg", file_number);
                image = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), 512, image);
                file_number++;
            }
            else if (file_number > 0)
            {
                fclose(image);
                sprintf(filename, "%03i.jpg", file_number);
                image = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), 512, image);
                file_number++;
            }
        }
        else if (file_number > 0)
        {
            fwrite(&buffer, sizeof(BYTE), 512, image);
        }
    }

    // CLose file
    fclose(image);
    fclose(file);
}