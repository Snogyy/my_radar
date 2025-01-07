/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** error
*/

#include "includes/my.h"

int verify_line(char *line)
{
    int count = 0;
    int len = my_strlen(line) - 1;

    if (line[0] != 'A' && line[0] != 'T')
        return 84;
    for (int i = 1; i < len; i++) {
        if ((line[i] < '0' || line[i] > '9') && line[i] != ' ')
            return 84;
        if (line[i] == ' ' && line[i + 1] >= '0' && line[i + 1] <= '9')
            count++;
    }
    if (line[0] == 'A' && count != 6)
        return 84;
    if (line[0] == 'T' && count != 3)
        return 84;
    return 0;
}

int verify_error(char *path)
{
    FILE *fd = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;

    if (fd == NULL) {
        write(1, "The script is not found\n", 24);
        return 84;
    }
    while (getline(&line, &len, fd) != -1) {
        if (verify_line(line) == 84) {
            write(1, "The script is incorrect\n", 24);
            return 84;
        }
    }
    return 0;
}
