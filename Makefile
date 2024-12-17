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
			includes/my_str_to_word_array.c \
			includes/str_to_int.c \
			includes/my_strlen.c

OBJ		=	$(SRC:.c=.o)

NAME 	= 	myradar

CFLAGS	+=	-g

all:	$(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -lcsfml-window -lcsfml-graphics -lcsfml-system -lcsfml-audio -lm $(CFLAGS)

clean :
	rm -f $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all
