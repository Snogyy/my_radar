/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** sprites
*/

#include "includes/my.h"

void init_sprites(sprite_t *sprite, char *path)
{
    sfFont *font = sfFont_createFromFile("src/digital-7.regular.ttf");

    sprite->background = sfSprite_create();
    sprite->background_text = sfTexture_createFromFile
    ("src/world.jpg", sfFalse);
    sprite->timer = sfText_create();
    sfText_setFont(sprite->timer, font);
    sfText_setCharacterSize(sprite->timer, 60);
    sfSprite_setTexture(sprite->background, sprite->background_text, sfFalse);
    sfText_setPosition(sprite->timer, (sfVector2f){1750, 10});
    sfText_setLetterSpacing(sprite->timer, 3);
    sprite->show_hitbox = 1;
    sprite->show_sprite = 1;
    init_planes(sprite, path);
    init_towers(sprite, path);
    init_areas(sprite, path);
}

void draw_plane(sprite_t *sprite, sfRenderWindow *window)
{
    for (int i = 0; i < sprite->nb_plane; i++) {
        if (sprite->plane[i].is_dep == 1 && sprite->plane[i].is_arr == 0
        && sprite->show_sprite == 1)
            sfRenderWindow_drawSprite(window, sprite->plane[i].plane, sfFalse);
        if (sprite->plane[i].is_dep == 1 && sprite->plane[i].is_arr == 0
        && sprite->show_hitbox == 1) {
            sfRenderWindow_drawRectangleShape(window,
            sprite->plane[i].hitbox, sfFalse);
        }
    }
}

void draw_tower(sprite_t *sprite, sfRenderWindow *window)
{
    for (int i = 0; i < sprite->nb_tower; i++) {
        if (sprite->show_sprite == 1)
            sfRenderWindow_drawSprite(window, sprite->tower[i].tower, sfFalse);
        if (sprite->show_hitbox == 1) {
            sfRenderWindow_drawCircleShape(window, sprite->tower[i].hitbox,
            sfFalse);
        }
    }
}

void draw_sprites(sprite_t *sprite, sfRenderWindow *window)
{
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, sprite->background, sfFalse);
    sfRenderWindow_drawText(window, sprite->timer, sfFalse);
    draw_plane(sprite, window);
    draw_tower(sprite, window);
    sfRenderWindow_display(window);
}

void destroy_all(sprite_t *sprite, sfRenderWindow *window,
    sfClock *clock_move, sfClock *clock_delay)
{
    sfSprite_destroy(sprite->background);
    sfTexture_destroy(sprite->background_text);
    sfTexture_destroy(sprite->plane_text);
    sfText_destroy(sprite->timer);
    for (int i = 0; i < sprite->nb_plane; i++) {
        sfSprite_destroy(sprite->plane[i].plane);
        sfRectangleShape_destroy(sprite->plane[i].hitbox);
    }
    for (int i = 0; i < sprite->nb_tower; i++) {
        sfSprite_destroy(sprite->tower[i].tower);
        sfCircleShape_destroy(sprite->tower[i].hitbox);
    }
    sfClock_destroy(clock_move);
    sfClock_destroy(clock_delay);
    sfRenderWindow_destroy(window);
}
