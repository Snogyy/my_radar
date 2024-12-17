/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** str_to_int
*/

#include "my.h"

int str_to_int(char *str)
{
    int res = 0;

    for (int i = 0; i < my_strlen(str); i++)
        res = (res * 10) + str[i] - 48;
    return res;
}
