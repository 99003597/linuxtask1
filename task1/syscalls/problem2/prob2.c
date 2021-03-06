#include <stdio.h>
#include <stdlib.h>

int main()
{
    f * f;
    int s;
    char p[100];
    char ch;
    int character, word, line;
    //printf("Enter source f p: ");
    //scanf("%s", p);
    f = fopen("nd.txt", "r");
   if (f == NULL)
    {
        printf("\nUnable to open file.\n");
        printf("Please check if file exists and you have read privilege.\n");

        exit(EXIT_FAILURE);
    }

    character = word = line = 0;
    while ((ch = fgetc(f)) != EOF)
    {
        character++;

        /* Check new line */
        if (ch == '\n' || ch == '\0')
            line++;

        /* Check words */
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
            word++;


        if(ch == ' ')
                s++;
    }
    
    printf("\n");
    printf("Total characters = %d\n", character);
    printf("Total lines      = %d\n", line);
 printf("Total space = %d\n", s);
   
    fclose(f);

    return 0;
}