#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    char* input_file = argv[1];
    FILE* input_pointer = fopen(input_file, "r");
    if (input_file == NULL)
    {
        printf(" %s is not available!\n", input_file);
        return 1;
    }
    int block_size=512;
    unsigned char read[block_size];
    int image_counter = 0;
    FILE *output_pointer = NULL;

    int notfirst = 0;

    while (fread(&read, block_size, 1, input_pointer) == 1)
    {

        if (read[0] == 0xff && read[1] == 0xd8 && read[2] == 0xff && (read[3] & 0xf0) == 0xe0)
        {

            if (notfirst == 1)
            {

                fclose(output_pointer);
            }

            else
            {

                notfirst = 1;
            }
            char filename[8];
            sprintf(filename, "%03i.jpg", image_counter);
            output_pointer = fopen(filename, "w");
            image_counter++;
        }
        if (notfirst == 1)
        {

            fwrite(&buffer, block_size, 1, output_pointer);
        }
    }
    if (output_pointer == NULL)
    {
        fclose(output_pointer);
    }
    if (input_pointer == NULL)
    {
        fclose(input_pointer);
    }
    return 0;
}