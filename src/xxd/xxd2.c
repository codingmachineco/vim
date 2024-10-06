#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define COLS 16

// 7: offset
// 2: ": "
// 5: 2 hex digits + space
// 1: space
// COLS: COLS characters
#define LLEN (7 + 2 + 5 * (COLS / 2) + 1 + COLS)

char hexxa[] = "0123456789abcdef";
char *hexx = hexxa;

int main(int argc, char *argv[])
{
    FILE *fp = stdin;
    int c, n = 0, p = 0;
    char l[LLEN + 2]; // +2 for '\n' and '\0'

    if (argc > 1)
    {
        fp = fopen(argv[1], "rb");
    }

    while ((c = getc(fp)) != EOF)
    {
        if (p == 0)
        {
            sprintf(l, "%07x: ", n);
            for (int i = 7 + 2; i < LLEN; l[i++] = ' ')
                ;
            l[LLEN] = '\n';
            l[LLEN + 1] = '\0';
        }
        l[7 + 2 + p / 2 + p * 2] = hexx[(c >> 4) & 0xf];
        l[7 + 2 + p / 2 + p * 2 + 1] = hexx[c & 0xf];
        l[7 + 2 + 5 * (COLS / 2) + 1 + p] = (c > 31 && c < 127) ? c : '.';
        n++;
        if (++p == COLS)
        {
            fputs(l, stdout);
            p = 0;
        }
    }

    if (p) fputs(l, stdout);

    if (fp != stdin) fclose(fp);

    return 0;
}