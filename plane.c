/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** plane
*/

#include "includes/my.h"

void init_plane_hitbox(plane_t *plane)
{
    sfColor grey = sfColor_fromRGB(151, 149, 157);

    plane->hitbox = sfRectangleShape_create();
    sfRectangleShape_setSize(plane->hitbox, (sfVector2f){20, 20});
    sfRectangleShape_setPosition(plane->hitbox,
    sfSprite_getPosition(plane->plane));
    sfRectangleShape_setOutlineThickness(plane->hitbox, 1);
    sfRectangleShape_setFillColor(plane->hitbox, sfTransparent);
}

void init_planes(sprite_t *sprite, char *path)
{
    sfFloatRect bounds;

    sprite->nb_plane = get_nbelemt(path, 1);
    sprite->plane = malloc(sizeof(plane_t) * sprite->nb_plane);
    get_info(sprite, path, 1);
    sprite->plane_text = sfTexture_createFromFile("src/plane.png", sfFalse);
    for (int i = 0; i < sprite->nb_plane; i++) {
        sprite->plane[i].id_tower = -1;
        sprite->plane[i].is_dep = 0;
        sprite->plane[i].is_arr = 0;
        sprite->plane[i].plane = sfSprite_create();
        sfSprite_setTexture(sprite->plane[i].plane,
        sprite->plane_text, sfFalse);
        sfSprite_setScale(sprite->plane[i].plane, (sfVector2f){0.10, 0.105});
        bounds = sfSprite_getLocalBounds(sprite->plane[i].plane);
        sfSprite_setOrigin(sprite->plane[i].plane,
        (sfVector2f){bounds.width / 2, bounds.height / 2});
        sfSprite_setPosition(sprite->plane[i].plane, sprite->plane[i].dep_pos);
        init_plane_hitbox(&sprite->plane[i]);
    }
}

sfVector2f get_next_pos(plane_t *plane, float time, sfVector2f act_pos)
{
    sfVector2f direction;
    double norme;

    direction = (sfVector2f){(plane->arr_pos.x - act_pos.x),
    (plane->arr_pos.y - act_pos.y)};
    norme = sqrt((direction.x * direction.x) + (direction.y * direction.y));
    direction = (sfVector2f){direction.x / norme, direction.y / norme};
    act_pos.x = act_pos.x + direction.x * plane->speed * time;
    act_pos.y = act_pos.y + direction.y * plane->speed * time;
    return act_pos;
}

void verify_flying(sfClock *clock_delay, plane_t *plane, sfVector2f act_pos)
{
    float arrival_x = fabs(act_pos.x - plane->arr_pos.x);
    float arrival_y = fabs(act_pos.y - plane->arr_pos.y);

    if (sfTime_asSeconds(sfClock_getElapsedTime(clock_delay)) >= plane->delay)
        plane->is_dep = 1;
    if (arrival_x < 2 && arrival_y < 2)
        plane->is_arr = 1;
}

static void change_orientation(sfVector2f act_pos,
    sfVector2f next_pos, plane_t *plane)
{
    float angle = atan2((next_pos.y - act_pos.y), (next_pos.x - act_pos.x));

    angle = angle * (180 / M_PI);
    sfSprite_setRotation(plane->plane, angle);
}

void move_plane(sprite_t *sprite,
    sfClock *clock_move, sfClock *clock_delay)
{
    float time = sfTime_asSeconds(sfClock_getElapsedTime(clock_move));
    int timer = sfTime_asSeconds(sfClock_getElapsedTime(clock_delay));
    sfVector2f act_pos;
    sfVector2f next_pos;

    sfText_setString(sprite->timer, int_to_str(timer));
    for (int i = 0; i < sprite->nb_plane; i++) {
        act_pos = sfSprite_getPosition(sprite->plane[i].plane);
        verify_flying(clock_delay, &sprite->plane[i], act_pos);
        if (sprite->plane[i].is_dep == 1 && sprite->plane[i].is_arr == 0) {
            next_pos = get_next_pos(&sprite->plane[i], time, act_pos);
            change_orientation(act_pos, next_pos, &sprite->plane[i]);
            sfSprite_setPosition(sprite->plane[i].plane, next_pos);
            sfRectangleShape_setPosition(sprite->plane[i].hitbox,
            (sfVector2f){next_pos.x - 10, next_pos.y - 10});
        }
    }
    verify_area_plane(sprite);
    sfClock_restart(clock_move);
}
