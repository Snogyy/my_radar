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

void show_sprite(sprite_t *sprite, sfEvent event)
{
    if (sprite->show_sprite == 0)
        sprite->show_sprite = 1;
    else if (sprite->show_sprite == 1)
        sprite->show_sprite = 0;
}

void manage_key_events(sprite_t *sprite, sfEvent event)
{
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyL)
        show_hitbox(sprite, event);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyS)
        show_sprite(sprite, event);
}

void manage_events(sfRenderWindow *window, sprite_t *sprite)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        manage_key_events(sprite, event);
    }
}
