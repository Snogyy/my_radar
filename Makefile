##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## EPITECH
##

SRC 	=	main.c \
			plane.c \
			tower.c \
			get_info.c \
			collide.c \
			error.c \
			events.c \
			sprites.c \
			includes/my_strlen.c \
			includes/int_to_str.c \
			includes/my_revstr.c \
			includes/my_countnb.c \

OBJ		=	$(SRC:.c=.o)

NAME 	= 	my_radar

CFLAGS	+=	-g -lm -lcsfml-window -lcsfml-graphics -lcsfml-system -lcsfml-audio

all:	$(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all
