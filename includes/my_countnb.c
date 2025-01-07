/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** my_countnb
*/

int my_countnb(long number)
{
    int count = 1;

    if (number < 0) {
        count++;
    }
    while (number / 10 > 0) {
        count++;
        number = number / 10;
    }
    return count;
}
