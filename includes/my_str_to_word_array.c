/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** EPITECH
*/

#include "my.h"

static int search_index0(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return i;
}

static int my_char_isalphanum(char const *str, int i)
{
    if ((str[i] >= 'a' && str[i] <= 'z') ||
        (str[i] >= 'A' && str[i] <= 'Z') ||
        (str[i] >= '0' && str[i] <= '9')) {
        return 1;
    } else {
        return 0;
    }
}

static int still_some_alphanums(char const *str)
{
    for (int i = 0; str[i]; i++) {
        if (my_char_isalphanum(str, i))
            return 1;
    }
    return 0;
}

char **find_malloc2(char const *str)
{
    int i = 0;
    int len = 0;
    char **result;
    int index0 = search_index0(str);

    while (i < index0) {
        if (still_some_alphanums(&str[i]) == 1)
            len++;
        while (my_char_isalphanum(str, i) == 0) {
            i++;
        }
        while (my_char_isalphanum(str, i) == 1) {
            i++;
        }
    }
    result = malloc(sizeof(char *) * (len + 1));
    return result;
}

char **find_malloc1(char const *str)
{
    char **result = find_malloc2(str);
    int i = 0;
    int j = 0;
    int len = 0;
    int index0 = search_index0(str);

    while (i < index0 && still_some_alphanums(&str[i]) == 1) {
        while (my_char_isalphanum(str, i) == 0) {
            i++;
        }
        while (my_char_isalphanum(str, i) == 1) {
            len++;
            i++;
        }
        result[j] = malloc(sizeof(char) * (len + 1));
        len = 0;
        j++;
    }
    return result;
}

int fill_cells2(char const *str, int i)
{
    while (my_char_isalphanum(str, i) == 0) {
            i++;
    }
    return i;
}

char **fill_cells(char const *str, char **result)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int index0 = search_index0(str);

    while (i < index0 && still_some_alphanums(&str[i]) == 1) {
        i = fill_cells2(str, i);
        while (my_char_isalphanum(str, i) == 1) {
            result[j][k] = str[i];
            k++;
            i++;
        }
        result[j][k] = '\0';
        j++;
        k = 0;
    }
    result[j] = NULL;
    return result;
}

char **my_str_to_word_array(char const *str)
{
    char **result;

    if (str == NULL || still_some_alphanums(&str[0]) == 0)
        return NULL;
    result = find_malloc1(str);
    result = fill_cells(str, result);
    return result;
}
