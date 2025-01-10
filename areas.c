/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** areas
*/

#include "includes/my.h"

static void add_plane(area_t *area, plane_t *added_plane)
{
    added_plane->next_plane = area->planes;
    area->planes = added_plane;
}

static void remove_plane(area_t *area, plane_t *removed_plane)
{
    plane_t *current = area->planes;
    plane_t *previous = NULL;

    if (current == removed_plane) {
        area->planes = current->next_plane;
        return;
    }
    while (current != NULL) {
        if (current == removed_plane) {
            previous->next_plane = current->next_plane;
            return;
        }
        previous = current;
        current = current->next_plane;
    }
}

plane_t *is_plane_in_area(sprite_t *sprite, area_t *area,
    int id_area, plane_t *added_plane)
{
    sfVector2f position = sfRectangleShape_getPosition(added_plane->hitbox);
    sfVector2f size = sfRectangleShape_getSize(added_plane->hitbox);

    for (int i = 0; i < sprite->nb_area; i++) {
        if (position.x + size.x > area->area_rect.left &&
        position.x < area->area_rect.left + area->area_rect.width &&
        position.y + size.y > area->area_rect.top
        && position.y < area->area_rect.top + area->area_rect.height
        && id_area != i) {
            remove_plane(area, added_plane);
            add_plane(&sprite->areas[i], added_plane);
            return area->planes;
        } else {
            return added_plane->next_plane;
        }
    }
}

void verify_area_plane(sprite_t *sprite)
{
    plane_t *temp;

    for (int i = 0; i < sprite->nb_area; i++) {
        temp = sprite->areas[i].planes;
        while (temp != NULL)
            temp = is_plane_in_area(sprite, &sprite->areas[i], i, temp);
    }
}

void init_area_plane(sprite_t *sprite, plane_t *added_plane)
{
    sfVector2f position = sfRectangleShape_getPosition(added_plane->hitbox);
    sfVector2f size = sfRectangleShape_getSize(added_plane->hitbox);
    area_t *area;

    for (int j = 0; j < sprite->nb_area; j++) {
        area = &sprite->areas[j];
        if (position.x + size.x > area->area_rect.left &&
        position.x < area->area_rect.left + area->area_rect.width &&
        position.y + size.y > area->area_rect.top &&
        position.y < area->area_rect.top + area->area_rect.height) {
            add_plane(area, added_plane);
            return;
        }
    }
}

void init_areas(sprite_t *sprite, char *path)
{
    sprite->nb_area = 4;
    sprite->areas = malloc(sizeof(area_t) * sprite->nb_area);
    sprite->areas[0].area_rect = (sfIntRect){0, 0, 960, 540};
    sprite->areas[1].area_rect = (sfIntRect){960, 0, 960, 540};
    sprite->areas[2].area_rect = (sfIntRect){0, 540, 960, 540};
    sprite->areas[3].area_rect = (sfIntRect){960, 540, 960, 540};
    for (int i = 0; i < sprite->nb_area; i++)
        sprite->areas[i].planes = NULL;
    for (int i = 0; i < sprite->nb_plane; i++)
        init_area_plane(sprite, &sprite->plane[i]);
}
