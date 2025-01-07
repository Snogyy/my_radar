/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** main
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
    init_planes(sprite, path);
    init_towers(sprite, path);
}

void draw_sprites(sprite_t *sprite, sfRenderWindow *window)
{
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, sprite->background, sfFalse);
    sfRenderWindow_drawText(window, sprite->timer, sfFalse);
    for (int i = 0; i < sprite->nb_plane; i++) {
        if (sprite->plane[i].is_dep == 1 && sprite->plane[i].is_arr == 0)
            sfRenderWindow_drawSprite(window, sprite->plane[i].plane, sfFalse);
        if (sprite->plane[i].is_dep == 1 && sprite->plane[i].is_arr == 0
        && sprite->show_hitbox == 1) {
            sfRenderWindow_drawRectangleShape(window,
            sprite->plane[i].hitbox, sfFalse);
        }
    }
    for (int i = 0; i < sprite->nb_tower; i++) {
        sfRenderWindow_drawSprite(window, sprite->tower[i].tower, sfFalse);
        if (sprite->show_hitbox == 1) {
            sfRenderWindow_drawCircleShape(window, sprite->tower[i].hitbox,
            sfFalse);
        }
    }
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

int main(int ac, char **av)
{
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "My Radar",
    sfResize | sfClose, NULL);
    sprite_t sprite;
    sfClock *clock_move = sfClock_create();
    sfClock *clock_delay = sfClock_create();

    if (verify_error(av[1]) == 84 || ac > 2)
        return 84;
    init_sprites(&sprite, av[1]);
    if (!window)
        return 84;
    while (sfRenderWindow_isOpen(window)) {
        manage_events(window, &sprite);
        verify_collide(&sprite);
        move_plane(&sprite, clock_move, clock_delay);
        draw_sprites(&sprite, window);
    }
    destroy_all(&sprite, window, clock_move, clock_delay);
    return 0;
}
