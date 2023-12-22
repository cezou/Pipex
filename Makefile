NAME = pipex
NAMEB = objs/pipex_bonus

CC = cc
CFLAGS = 

IDIR = include
LIBFT = $(IDIR)/QuoicouLibft/libft.a

DIR = srcs
SRCS = $(DIR)/pipex_utils.c $(DIR)/parse_and_exec.c $(DIR)/split_utils.c

MANDATORY = $(DIR)/pipex.c 
BONUS = $(DIR)/pipex_bonus.c


all : QuoicouLibft $(NAME)

bonus : QuoicouLibft $(NAMEB)

QuoicouLibft:
	@make --silent -C $(IDIR)/QuoicouLibft

$(NAME): $(SRCS) $(MANDATORY)
	@echo "\n     \033[1;32m🦑🦑🦑 Pipex créé 🦑🦑🦑\033[0m\n"
	@$(CC) $(CFLAGS) $(SRCS) $(MANDATORY) -o $(NAME) $(LIBFT)

$(NAMEB): $(SRCSBONUS) $(BONUS)
	@echo "\n \033[1;32m🦑🦑🦑 Pipex Bonus créé 🦑🦑🦑\033[0m\n"
	@$(CC) $(CFLAGS) $(SRCS) $(BONUS) -o $(NAMEB) $(LIBFT)
	@cp $(NAMEB) $(NAME)

clean:
	@make --silent fclean -C $(IDIR)/QuoicouLibft


fclean:
	@if [ -f $(NAME) ] || [ -f $(NAMEB) ]; then \
			make --silent fclean_no_check; \
	fi

fclean_no_check: clean
	@rm -f $(NAME) $(NAMEB)
	@echo "\n      \033[1;31m🦑🦑🦑 Pipex crampté 🦑🦑🦑\033[0m\n"

re : fclean all

.PHONY: QuoicouLibft clean fclean re all bonus