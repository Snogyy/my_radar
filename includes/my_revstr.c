/*
** EPITECH PROJECT, 2024
** my_revstr
** File description:
** EPITECH
*/

#include "my.h"

char *my_revstr(char *str)
{
    int i = 0;
    int j = (my_strlen(str) - 1);
    char temp;

    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
    return str;
}
