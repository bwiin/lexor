#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6,  slashsym = 7, oddsym = 8,
    eqsym = 9, neqsym = 10, lessym = 11, leqsym = 12, gtrsym = 13, geqsym = 14,
    lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18, periodsym = 19,
    becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26,
    callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31, readsym = 32, elsesym = 33, colonsym = 34
    } token_type;


//function prototypes.
char* printSourceNoComment(char *code, int fileLength);
void printSourceWithComment(char *code, int fileLength);
void readTokens(char *code, int fileLength);

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");

    int c;
    char *code, *real;
    int i = 0, fileLength;

    code = malloc(20000 * sizeof(char));

    while(fscanf(fp, "%c", &c) != EOF)
    {
        code[i] = c;
        i++;
        fileLength++;
    }
    printSourceWithComment(code, fileLength);
    real = printSourceNoComment(code, fileLength);
    readTokens(real, fileLength);

    return 0;
}
void readTokens(char *code, int fileLength)
{

    int i;

    for (i=0; i<fileLength; i++)
    {
        if((code[i] == 'v') && (code[i+1] == 'a') && (code[i+2] == 'r'))
        {
            printf("var\t\t29\n");
            i=i+3;
        }
        if(isalpha(code[i]))
           printf("%c  \t\t2\n", code[i]);

        if(isdigit(code[i]))
        {

            if((isdigit(code[i+4])) && (isdigit(code[i+3])) && (isdigit(code[i+2])) && (isdigit(code[i+1])))
            {
               printf("%c%c%c%c%c \t3", code[i], code[i+1], code[i+2] ,code[i+3], code[i+4]);
               i=i+4;
            }
            else if((isdigit(code[i+3])) && (isdigit(code[i+2]))&& (isdigit(code[i+1])))
            {
               printf("%c%c%c%c   \t3", code[i], code[i+1], code[i+2], code[i+3]);
               i=i+3;
            }
            else if(isdigit(code[i+2]) && (isdigit(code[i+1])))
            {
               printf("%c%c%c \t\t3", code[i], code[i+1], code[i+2]);
               i=i+2;
            }
            else if(isdigit(code[i+1]))
            {
                printf("%c%c \t\t3\n", code[i], code[i+1]);
                i=i+1;
            }
            else
                printf("%c  \t\t3\n", code[i]);
        }

        if(code[i] == ',')
            printf("%c  \t\t17\n", code[i]);

        if(code[i] == ';')
            printf("%c  \t\t18\n", code[i]);

        if((code[i] == 'b') && (code[i+1] == 'e') && (code[i+2] == 'g') &&
           (code[i+3] == 'i') && (code[i+4] == 'n'))
        {
            printf("begin   \t21\n");
            i=i+5;
        }
        if(code[i] == ':' && code[i+1] == '=')
        {
            printf("%c%c \t\t20\n", code[i],code[i+1]);
            i=i+2;
        }
        if(code[i] == '+')
            printf("%c   \t\t4\n", code[i]);

        if((code[i] == 'e') && (code[i+1] == 'n') && (code[i+2] == 'd' ))
        {
            printf("end  \t\t22\n");
            i=i+3;
        }

        if(code[i] == '.')
            printf("%c   \t\t19\n", code[i]);

    }

}
char *printSourceNoComment(char *code, int fileLength)
{
    int i;
    char *real;

    real = malloc(20000 * sizeof(char));

    printf("source code without comments:\n-----------------------------\n");
    for(i=0; i < fileLength; i++)
    {
        if(code[i] == '/' && code[i+1] == '*')
        {
            //skip ahead 2 spaces.
            i=i+2;
            while(code[i] != '*' && code[i+1] != '/')
                i++;
        }

        if(code[i] != '*' && code[i] != '/')
        {
            printf("%c", code[i]);
            real[i]=code[i];
        }
    }
    printf("\n\ntokens\n-------\n");

    return real;

}
void printSourceWithComment(char *code, int fileLength)
{
    int i;
    printf("source code:\n------------\n");
    for(i=0; i < fileLength; i++)
        printf("%c", code[i]);

    printf("\n\n");
}
