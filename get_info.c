/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** get_info
*/

#include "includes/my.h"

void line_to_infos(char *line, int *infos)
{
    int index = 0;
    int value = 0;

    for (int i = 0; line[i] != '\n'; i++) {
        if (line[i] >= '0' && line[i] <= '9')
            value = (value * 10) + (line[i] - 48);
        if ((line[i] == ' ' && value != 0)) {
            infos[index] = value;
            value = 0;
            index++;
        }
    }
    infos[index] = value;
}

void get_info_plane(sprite_t *sprite, char *path)
{
    FILE *file = fopen(path, "r");
    int *infos = malloc(sizeof(int) * 6);
    char *line = NULL;
    size_t size = 0;
    int idx = 0;

    for (int i = 0; getline(&line, &size, file) != -1; i++) {
        if (line[0] == 'A') {
            line_to_infos(line, infos);
            sprite->plane[idx].dep_pos = (sfVector2f){infos[0], infos[1]};
            sprite->plane[idx].arr_pos = (sfVector2f){infos[2], infos[3]};
            sprite->plane[idx].speed = infos[4];
            sprite->plane[idx].delay = infos[5];
            idx++;
        }
    }
    free(infos);
    free(line);
    fclose(file);
}

void get_info_tower(sprite_t *sprite, char *path)
{
    FILE *file = fopen(path, "r");
    int *infos = malloc(sizeof(int) * 3);
    char *line = NULL;
    size_t size = 0;
    int idx = 0;

    for (int i = 0; getline(&line, &size, file) != -1; i++) {
        if (line[0] == 'T') {
            line_to_infos(line, infos);
            sprite->tower[idx].pos = (sfVector2f){infos[0], infos[1]};
            sprite->tower[idx].radius = infos[2];
            idx++;
        }
    }
    free(infos);
    free(line);
    fclose(file);
}

int get_nbelemt(char *path, int is_plane)
{
    FILE *file = fopen(path, "r");
    char type;
    int counter = 0;

    while (fscanf(file, "%c", &type) != -1) {
        if (type == 'A' && is_plane == 1)
            counter++;
        if (type == 'T' && is_plane == 0)
            counter++;
    }
    return counter;
}