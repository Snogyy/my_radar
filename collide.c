/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** collision
*/

#include "includes/my.h"

int check_circle_rect_collision(sfRectangleShape *rect, sfCircleShape *circ,
    int radius)
{
    sfVector2f rect_pos = sfRectangleShape_getPosition(rect);
    sfVector2f rect_size = sfRectangleShape_getSize(rect);
    sfVector2f circ_pos = sfCircleShape_getPosition(circ);
    sfVector2f circ_center = {circ_pos.x + radius, circ_pos.y + radius};
    float closest_x = fmax(rect_pos.x,
    fmin(circ_center.x, rect_pos.x + rect_size.x));
    float closest_y = fmax(rect_pos.y,
    fmin(circ_center.y, rect_pos.y + rect_size.y));
    float dx = circ_center.x - closest_x;
    float dy = circ_center.y - closest_y;

    if ((dx * dx + dy * dy) <= (radius * radius))
        return 1;
    else
        return 0;
}

void is_in_tower(plane_t *plane, tower_t *tower, int id_tower)
{
    sfRectangleShape *rect = plane->hitbox;
    sfCircleShape *circ = tower->hitbox;
    int radius = tower->radius;

    if (check_circle_rect_collision(rect, circ, radius) == 1) {
        plane->in_tower = 1;
        plane->id_tower = id_tower;
        sfRectangleShape_setOutlineColor(plane->hitbox, sfGreen);
    } else if (plane->id_tower == id_tower) {
        plane->in_tower = 0;
        plane->id_tower = -1;
        sfRectangleShape_setOutlineColor(plane->hitbox, sfRed);
    }
}

void is_intersecting_plane(sprite_t *sprite, int i, int j)
{
    sfRectangleShape *rect1 = sprite->plane[i].hitbox;
    sfRectangleShape *rect2 = sprite->plane[j].hitbox;
    sfVector2f pos1 = sfRectangleShape_getPosition(rect1);
    sfVector2f pos2 = sfRectangleShape_getPosition(rect2);
    sfVector2f size1 = sfRectangleShape_getSize(rect1);
    sfVector2f size2 = sfRectangleShape_getSize(rect2);

    if (sprite->plane[i].in_tower == 0 && sprite->plane[j].in_tower == 0
    && sprite->plane[i].is_arr == 0 && sprite->plane[j].is_arr == 0) {
        if ((pos2.x >= pos1.x + size1.x) || (pos2.x + size2.x <= pos1.x)
        || (pos2.y >= pos1.y + size1.y) || (pos2.y + size2.y <= pos1.y))
            return;
        else {
            sprite->plane[i].is_arr = 1;
            sprite->plane[j].is_arr = 1;
        }
    }
}

void verify_collide(sprite_t *sprite)
{
    for (int i = 0; i < sprite->nb_plane; i++) {
        for (int j = 0; j < sprite->nb_tower; j++)
            is_in_tower(&sprite->plane[i], &sprite->tower[j], j);
    }
    for (int i = 0; i < (sprite->nb_plane - 1); i++) {
        for (int j = (i + 1); j < (sprite->nb_plane); j++)
            is_intersecting_plane(sprite, i, j);
    }
}
