/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** collision
*/

#include "includes/my.h"

void is_intersecting_hitbox(sprite_t *sprite, int i, int j)
{
    sfRectangleShape *rect1 = sprite->plane[i].hitbox;
    sfRectangleShape *rect2 = sprite->plane[j].hitbox;
    sfVector2f pos1 = sfRectangleShape_getPosition(rect1);
    sfVector2f pos2 = sfRectangleShape_getPosition(rect2);
    sfVector2f size1 = sfRectangleShape_getSize(rect1);
    sfVector2f size2 = sfRectangleShape_getSize(rect2);

    if (sprite->plane[i].is_arr == 0 && sprite->plane[j].is_arr == 0) {
        if ((pos2.x >= pos1.x + size1.x) || (pos2.x + size2.x <= pos1.x)
        || (pos2.y >= pos1.y + size1.y) || (pos2.y + size2.y <= pos1.y))
           return;
        else {
            sprite->plane[i].is_arr = 1;
            sprite->plane[j].is_arr = 1;
        }
    }
    printf("collide! %d and %d", i, j);
}

void verify_collide(sprite_t *sprite)
{
    for (int i = 0; i < (sprite->nb_plane - 1); i++) {
        for (int j = i + 1; j < sprite->nb_plane; j++) {
            is_intersecting_hitbox(sprite, i, j);
        }
    }
}
