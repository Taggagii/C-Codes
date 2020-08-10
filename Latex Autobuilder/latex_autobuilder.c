#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int compare_files(const char *filenameone, const char* filenametwo)
{
    FILE *mainfile = fopen(filenameone, "r");
    FILE *checkerfile = fopen(filenametwo, "r");
    int value = 1;
    if (!mainfile || !checkerfile)
    {
        value = -1;
        goto END;
    }
    char letter, letter2;
    while ((letter = fgetc(mainfile)) != EOF && (letter2 = fgetc(checkerfile)) != EOF)
        if (letter != letter2)
        {
            value = 0;
            break;
        }
END:
    fclose(mainfile);
    fclose(checkerfile);
    return value;
}

void update_pdf()
{
    system(": | pdflatex -halt-on-error holder.tex | grep '^!.*' -A200 --color=always");
    system("open holder.pdf");
}


int main(int argc, char *argv[])
{
    char *filename;
    int templen = 0, len = 0;
    for (int i = 1; i < argc; i++)
    {
        templen = strlen(argv[i]);
        filename = realloc(filename, len + templen + 2);
        strcpy(filename + len, argv[i]);
        strcpy(filename + len + templen, " ");
        len += templen + 1;
    }
    if (!len)
    {
        printf("\033[0;31mYou must enter a filename\033[0m\n");
        return EXIT_FAILURE;
    }
    filename[len - 1] = 0;
    FILE *thefile = fopen(filename, "r");
    if (thefile == NULL)
    {
        thefile = fopen(strcat(filename, ".tex"), "r");
        if (thefile == NULL)
        {
            printf("\033[0;31mFile \"%s\" filename not found\033[0m\n", filename);
            return EXIT_FAILURE;
        }
    }
    fclose(thefile);
    printf("\nFilename : %s\n\n", filename);

    char *open_tex_command = (char*) malloc(strlen("open ") + strlen(filename) + 1);
    strcpy(open_tex_command, "open ");
    strcat(open_tex_command, filename);
    system(open_tex_command);
    char *command = (char*) malloc(strlen("cp -f  holder.tex") + strlen(filename));
    strcpy(command, "cp -f ");
    strcat(command, filename);
    strcat(command, " holder.tex");
    system(command);


    update_pdf();
    int value, previousvalue;
    while (1)
    {
        while(compare_files(filename, "holder.tex") == 1);
        previousvalue = value;
        system(command);
        update_pdf();
    }
    system("rm holder.tex");
    return 0;
}