NAME = libft.a

all: check_libft

check_libft:
	@if [ ! -f $(NAME) ]; then \
			make making; \
			make $(NAME); \
			make echo; \
			make oclean; \
	fi

$(NAME):
	@make --silent -C gnl
	@make --silent -C printfd
	@make --silent -C minmax
	@cp printfd/libftprintf.a $(NAME)
	@cp gnl/gnl.a .
	@cp minmax/minmax.a .
	@ar x gnl.a
	@ar x minmax.a
	@ar rc $(NAME) *.o
	@rm *.o
	@rm gnl.a
	@rm minmax.a

echo:
	@echo "\033[33m               ⚫⚫🟢\033[0m"
	@echo "\033[33m  Ouaaais, c'est ca qui m'fallait\033[0m"

making:
	@echo "\n\033[35m🦑🦑🦑 Making QuoicouLibft... 🦑🦑🦑\033[0m"

oclean:
	@make --silent fclean -C ./libft
	@make --silent fclean -C ./gnl
	@make --silent fclean -C ./printfd
	@make --silent fclean -C ./minmax

clean: clean_o clean_a 
	@echo "\n\033[35m🦑🦑🦑 Crampting QuoicouLibft... 🦑🦑🦑\033[0m"
	@make --silent fclean -C ./libft
	@echo "\033[31m          Redlight FIRST LIBFT!\033[0m"
	@make --silent fclean -C ./gnl
	@echo "\033[31m              Redlight GNL!\033[0m"
	@make --silent fclean -C ./printfd
	@echo "\033[31m            Redlight PRINTFD!\033[0m"
	@make --silent fclean -C ./minmax
	@echo "\033[31m            Redlight MINMAX!\033[0m"
	@echo "                 🔴⚫⚫"

fclean:
	@if [ -f $(NAME) ]; then \
			make --silent fclean_no_check; \
	fi

fclean_no_check: clean
	@rm -f $(NAME) 
	@echo "\033[33m  La QuoicouLibft s'est faite cramptée\033[0m"

re: fclean all

clean_o:
	@rm -f *.o

clean_a:
	@rm -f gnl.a libftprintf.a minmax.a