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
#include <string.h>

#ifndef INCLUDED_MY_H
    #define INCLUDED_MY_H
    #define M_PI 3.14159265358979323846

typedef struct plane {
    sfSprite *plane;
    sfRectangleShape *hitbox;
    int is_dep;
    int is_arr;
    int in_tower;
    int id_tower;
    sfVector2f dep_pos;
    sfVector2f arr_pos;
    int speed;
    int delay;
    struct plane *next_plane;
} plane_t;

typedef struct tower {
    sfSprite *tower;
    sfCircleShape *hitbox;
    sfVector2f pos;
    int radius;
} tower_t;

typedef struct area {
    sfIntRect area_rect;
    plane_t *planes;
} area_t;

typedef struct sprite {
    sfTexture *background_text;
    sfSprite *background;
    sfTexture *plane_text;
    plane_t *plane;
    int nb_plane;
    sfTexture *tower_text;
    tower_t *tower;
    int nb_tower;
    area_t *areas;
    int nb_area;
    int show_hitbox;
    int show_sprite;
    sfText *timer;
} sprite_t;

void init_planes(sprite_t *sprite, char *path);
void init_towers(sprite_t *sprite, char *path);
void get_info(sprite_t *sprite, char *path, int is_plane);
int get_nbelemt(char *path, int is_plane);
int my_strlen(char const *str);
void move_plane(sprite_t *sprite, sfClock *clock_move, sfClock *clock_delay);
void verify_collide(sprite_t *sprite);
int verify_error(char *path);
void manage_events(sfRenderWindow *window, sprite_t *sprite);
void init_sprites(sprite_t *sprite, char *path);
void draw_sprites(sprite_t *sprite, sfRenderWindow *window);
void destroy_all(sprite_t *sprite, sfRenderWindow *window,
    sfClock *clock_move, sfClock *clock_delay);
void init_areas(sprite_t *sprite, char *path);
void verify_area_plane(sprite_t *sprite);
char *int_to_str(int i);
char *my_revstr(char *str);
int my_countnb(long number);

#endif
