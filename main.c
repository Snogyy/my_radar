/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** main
*/

#include "includes/my.h"

void init_sprites(sprite_t *sprite, char *path)
{
    sprite->background = sfSprite_create();
    sprite->background_text = sfTexture_createFromFile("src/world.jpg", sfFalse);
    sfSprite_setTexture(sprite->background, sprite->background_text, sfFalse);
    init_planes(sprite, path);
    init_towers(sprite, path);
}

void draw_sprites(sprite_t *sprite, sfRenderWindow *window)
{
    sfRenderWindow_drawSprite(window, sprite->background, sfFalse);
    for (int i = 0; i < sprite->nb_plane; i++) {
        if (sprite->plane[i].is_dep == 1 && sprite->plane[i].is_arr == 0) {
            sfRenderWindow_drawSprite(window, sprite->plane[i].plane, sfFalse);
            sfRenderWindow_drawRectangleShape(window, sprite->plane[i].hitbox, sfFalse);
        }
    }
    for (int i = 0; i < sprite->nb_tower; i++) {
        sfRenderWindow_drawSprite(window, sprite->tower[i].tower, sfFalse);
        sfRenderWindow_drawCircleShape(window, sprite->tower[i].hitbox, sfFalse);
    }
}

void destroy_all(sprite_t *sprite, sfRenderWindow *window, sfClock *clock_move, sfClock *clock_delay)
{
    sfSprite_destroy(sprite->background);
    sfTexture_destroy(sprite->background_text);
    sfTexture_destroy(sprite->plane_text);
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
    sfRenderWindow *window = sfRenderWindow_create(mode, "My Radar", sfResize | sfClose, NULL);
    sprite_t sprite;
    sfEvent event;
    sfClock *clock_move = sfClock_create();
    sfClock *clock_delay = sfClock_create();

    init_sprites(&sprite, av[1]);
    if (!window)
        return EXIT_FAILURE;
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        //verify_collide(&sprite);
        move_plane(&sprite, clock_move, clock_delay);
        draw_sprites(&sprite, window);
        sfRenderWindow_display(window);
    }
    destroy_all(&sprite, window, clock_move, clock_delay);
    return EXIT_SUCCESS;
}

//sfRectangleShape_setPosition(sprite->plane[i].hitbox, sfSprite_getPosition(sprite->plane[i].plane));
