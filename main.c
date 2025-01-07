/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** main
*/

#include "includes/my.h"

int show_usage(void)
{
    write(1, "Air traffic simulation panel\nUSAGE\n", 35);
    write(1, "\t./my_radar [OPTIONS] path_to_script\n", 37);
    write(1, "\tpath_to_script\tThe path to the script file.\nOPTIONS\n", 54);
    write(1, "\t-h\tprint the usage and quit.\nUSER INTERACTIONS\n", 49);
    write(1, "\t'L' key\tenable/disable hitboxes and areas.\n", 45);
    write(1, "\t'S' key\tenable/disable sprites.\n", 34);
    return 0;
}

int program_end(sprite_t *sprite)
{
    int all_landed = 1;

    for (int i = 0; i < sprite->nb_plane; i++) {
        if (sprite->plane[i].is_arr == 0)
            all_landed = 0;
    }
    return all_landed;
}

void loop_func(sprite_t *sprite, sfRenderWindow *window,
    sfClock *clock_move, sfClock *clock_delay)
{
    while (sfRenderWindow_isOpen(window)) {
        manage_events(window, sprite);
        verify_collide(sprite);
        move_plane(sprite, clock_move, clock_delay);
        draw_sprites(sprite, window);
        if (program_end(sprite) == 1)
            break;
    }
}

int main(int ac, char **av)
{
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "My Radar",
    sfResize | sfClose, NULL);
    sprite_t sprite;
    sfClock *clock_move = sfClock_create();
    sfClock *clock_delay = sfClock_create();

    if (av[1][0] == '-' && av[1][1] == 'h')
        return show_usage();
    if (verify_error(av[1]) == 84 || ac > 2)
        return 84;
    init_sprites(&sprite, av[1]);
    if (!window)
        return 84;
    loop_func(&sprite, window, clock_move, clock_delay);
    destroy_all(&sprite, window, clock_move, clock_delay);
    return 0;
}
