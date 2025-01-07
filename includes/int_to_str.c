/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** int_to_str
*/

#include "my.h"

char *int_to_str(int i)
{
    char c;
    int len = my_countnb(i);
    char *res = malloc(sizeof(char) * len + 1);

    if (i <= 0)
        return "0";
    for (int j = 0; i != 0; j++){
        c = i % 10;
        i = i / 10;
        res[j] = c + 48;
    }
    res[len] = '\0';
    res = my_revstr(res);
    return res;
}
