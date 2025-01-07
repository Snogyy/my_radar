/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** events
*/

#include "includes/my.h"

void show_hitbox(sprite_t *sprite, sfEvent event)
{
    if (sprite->show_hitbox == 0)
        sprite->show_hitbox = 1;
    else if (sprite->show_hitbox == 1)
        sprite->show_hitbox = 0;
}

void manage_events(sfRenderWindow *window, sprite_t *sprite)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyL)
            show_hitbox(sprite, event);
    }
}
