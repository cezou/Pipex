# inspire toi du makefile de gnl (/home/cviegas/Documents/adventofcode/libft/gnl/Makefile)

# Path: libft/minmax/Makefile

NAME = minmax.a

SRC = ft_min_max.c
OBJ = $(SRC:.c=.o)

CC = cc 
FLAGS = -Wall -Wextra -Werror

all: ccc $(NAME) echo clean

$(NAME): $(OBJ)
	@ar rc $@ $^

ccc:
	@$(CC) $(FLAGS) -c $(SRC)

echo:
	@echo "         \033[32mGreenlight minmax!\033[0m"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
