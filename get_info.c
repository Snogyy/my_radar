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

    for (int i = 0; i != my_strlen(line); i++) {
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

int get_info_plane(sprite_t *sprite, char *line, int index)
{
    int *infos = malloc(sizeof(int) * 6);

    line_to_infos(line, infos);
    sprite->plane[index].dep_pos = (sfVector2f){infos[0], infos[1]};
    sprite->plane[index].arr_pos = (sfVector2f){infos[2], infos[3]};
    sprite->plane[index].speed = infos[4];
    sprite->plane[index].delay = infos[5];
    index++;
    free(infos);
    return index;
}

int get_info_tower(sprite_t *sprite, char *line, int index)
{
    int *infos = malloc(sizeof(int) * 3);

    line_to_infos(line, infos);
    sprite->tower[index].pos = (sfVector2f){infos[0], infos[1]};
    sprite->tower[index].radius = infos[2];
    index++;
    free(infos);
    return index;
}

void get_info(sprite_t *sprite, char *path, int is_plane)
{
    FILE *file = fopen(path, "r");
    char *line = NULL;
    size_t size = 0;
    int idx_plane = 0;
    int idx_tower = 0;

    for (int i = 0; getline(&line, &size, file) != -1; i++) {
        if (line[0] == 'A' && is_plane == 1)
            idx_plane = get_info_plane(sprite, line, idx_plane);
        if (line[0] == 'T' && is_plane == 0)
            idx_tower = get_info_tower(sprite, line, idx_tower);
    }
    free(line);
    fclose(file);
}

int get_nbelemt(char *path, int is_plane)
{
    FILE *file = fopen(path, "r");
    char *line = NULL;
    size_t size = 0;
    int counter = 0;

    for (int i = 0; getline(&line, &size, file) != -1; i++) {
        if (line[0] == 'A' && is_plane == 1)
            counter++;
        if (line[0] == 'T' && is_plane == 0)
            counter++;
    }
    free(line);
    fclose(file);
    return counter;
}
