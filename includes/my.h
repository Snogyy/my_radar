/*
** EPITECH PROJECT, 2024
** bs_myradar
** File description:
** my
*/

#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#ifndef INCLUDED_MY_H
    #define INCLUDED_MY_H

typedef struct plane {
    sfSprite *plane;
    sfRectangleShape *hitbox;
    int is_dep;
    int is_arr;
    sfVector2f dep_pos;
    sfVector2f arr_pos;
    int speed;
    int delay;
} plane_t;

typedef struct tower {
    sfSprite *tower;
    sfCircleShape *hitbox;
    sfVector2f pos;
    int radius;
} tower_t;

typedef struct sprite {
    sfTexture *background_text;
    sfSprite *background;
    int nb_plane;
    sfTexture *plane_text;
    plane_t *plane;
    int nb_tower;
    sfTexture *tower_text;
    tower_t *tower;
} sprite_t;

void init_planes(sprite_t *sprite, char *path);
void init_towers(sprite_t *sprite, char *path);
int get_nbelemt(char *path, int is_plane);
void get_info_plane(sprite_t *sprite, char *path);
void get_info_tower(sprite_t *sprite, char *path);
char **my_str_to_word_array(char const *str);
int str_to_int(char *str);
int my_strlen(char const *str);
void move_plane(sprite_t *sprite, sfClock *clock_move, sfClock *clock_delay);
void verify_collide(sprite_t *sprite);

#endif
