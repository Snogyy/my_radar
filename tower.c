/*
** EPITECH PROJECT, 2024
** my_radar
** File description:
** tower
*/

#include "includes/my.h"

void init_tower_hitbox(tower_t *tower)
{
    sfColor grey = sfColor_fromRGB(151, 149, 157);
    sfVector2f hitbox_pos = (sfVector2f){(tower->pos.x - tower->radius), (tower->pos.y - tower->radius)};

    tower->hitbox = sfCircleShape_create();
    sfCircleShape_setPosition(tower->hitbox, hitbox_pos);
    sfCircleShape_setRadius(tower->hitbox, tower->radius);
    sfCircleShape_setOutlineThickness(tower->hitbox, 1.5);
    sfCircleShape_setOutlineColor(tower->hitbox, grey);
    sfCircleShape_setFillColor(tower->hitbox, sfTransparent);
}

void init_towers(sprite_t *sprite, char *path)
{
    sfFloatRect bounds;

    sprite->nb_tower = get_nbelemt(path, 0);
    sprite->tower = malloc(sizeof(tower_t) * sprite->nb_tower);
    get_info_tower(sprite, path);
    sprite->tower_text = sfTexture_createFromFile("src/tower.png", sfFalse);
    for (int i = 0; i < sprite->nb_tower; i++) {
        sprite->tower[i].tower = sfSprite_create();
        sfSprite_setTexture(sprite->tower[i].tower, sprite->tower_text, sfFalse);
        sfSprite_setScale(sprite->tower[i].tower, (sfVector2f){0.05, 0.05});
        bounds = sfSprite_getLocalBounds(sprite->tower[i].tower);
        sfSprite_setOrigin(sprite->tower[i].tower, (sfVector2f){bounds.width / 2, bounds.height / 2});
        sfSprite_setPosition(sprite->tower[i].tower, sprite->tower[i].pos);
        init_tower_hitbox(&sprite->tower[i]);
    }
}