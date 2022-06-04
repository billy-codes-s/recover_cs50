#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./filetorecover - exit error 1\n");
        return 1;

    }

    FILE *recoverfile = fopen(argv[1], "r");

    if (recoverfile == NULL)
    {

        printf("Memory error, please try again\n");
        return 1;

    }
    FILE *newimage = fopen(argv[1], "r");
    BYTE singleblock[512];
    int passage = 0;

    while (fread(singleblock, sizeof(BYTE), 512, recoverfile) == 512)
    {
        if (singleblock[0] == 0xff && singleblock[1] == 0xd8 && singleblock[2] == 0xff && (singleblock[3] & 0xf0) == 0xe0)
        {
            printf("Success\n");
            char filename[250];
            sprintf(filename, "%03d.jpg", passage);
            fclose(newimage);
            newimage = fopen(filename, "w");
            fwrite(singleblock, sizeof(BYTE), 512, newimage);
            passage++;
            continue;
        }

        if( passage == 0)
        {
            continue;
        }

        else
        {
            fwrite(singleblock, sizeof(BYTE), 512, newimage);
        }



    }
    fclose(newimage);
    fclose(recoverfile);


}