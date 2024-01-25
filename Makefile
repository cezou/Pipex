NAME = pipex
NAMEB = objs/pipex_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

IDIR = include
LIBFT = $(IDIR)/QuoicouLibft/libft.a

DIR = srcs
SRCS = $(DIR)/utils.c $(DIR)/parse_and_exec.c $(DIR)/split_utils.c $(DIR)/heredoc_and_pipe_handling.c

MANDATORY = $(DIR)/main.c
BONUS =  $(DIR)/main_bonus.c

UP = \033[1A
ERASE = \033[0J

all : QuoicouLibft $(NAME)

bonus : QuoicouLibft $(NAMEB)

QuoicouLibft:
	@make --silent -C $(IDIR)/QuoicouLibft

$(NAME): $(SRCS) $(MANDATORY)
	@echo "\033[1;32m   ● Made Pipex\033[0m"
	@$(CC) $(CFLAGS) $(SRCS) $(MANDATORY) -o $(NAME) $(LIBFT)

$(NAMEB): $(SRCSBONUS) $(BONUS)
	@mkdir -p objs
	@echo "\033[1;32m   ● Made Bonus\033[0m"
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
	@rm -rf objs
	@echo "\033[1;31m   ● Pipex crampted\033[0m"

re : fclean all

.PHONY: QuoicouLibft clean fclean re all bonus