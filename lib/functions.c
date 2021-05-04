#include "../cpu/type.h"
#include "math.h"
#include "../drivers/screen.h"
#include "functions.h"

#include <string.h>
#include <stdio.h>

int int_table[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char hexes[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };


void int_to_ascii(int n, char str[])
{
    int i, sign;
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do
    {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

char int_to_ascii_char(int n){
    if( n < 0 || n > 15){
        return '\0';
    }
    return hexes[n];
}

void hex_to_ascii(int n, char str[])
{
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    s32 tmp;
    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0)
            continue;
        zeros = 1;
        if (tmp > 0xA)
            append(str, tmp - 0xA + 'a');
        else
            append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA)
        append(str, tmp - 0xA + 'a');
    else
        append(str, tmp + '0');
}

void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void append(char s[], char n)
{
    int len = strlen(s);
    s[len] = n;
    s[len + 1] = '\0';
}

void backspace(char s[])
{
    int len = strlen(s);
    s[len - 1] = '\0';
}


char *substring(char *destination, const char *source, int beg, int n)
{
    while (n > 0)
    {
        *destination = *(source + beg);

        destination++;
        source++;
        n--;
    }
    *destination = '\0';
    return destination;
}

int char_to_int(char in){
    if(in == '0'){
        return 0;
    }
    if(in == '1'){
        return 1;
    }
    if(in == '2'){
        return 2;
    }
    if(in == '3'){
        return 3;
    }
    if(in == '4'){
        return 4;
    }
    if(in == '5'){
        return 5;
    }
    if(in == '6'){
        return 6;
    }
    if(in == '7'){
        return 7;
    }
    if(in == '8'){
        return 8;
    }
    if(in == '9'){
        return 9;
    }

    if(in == 'A'){
        return 10;
    }
    if(in == 'B'){
        return 11;
    }
    if(in == 'C'){
        return 12;
    }
    if(in == 'D'){
        return 13;
    }
    if(in == 'E'){
        return 14;
    }
    if(in == 'F'){
        return 15;
    }
    return -1;
}
