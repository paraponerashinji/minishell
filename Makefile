NAME= minishell
CC= cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFTDIR) -ggdb
SRCS= main.c src/pipes.c src/parsing.c src/more_parsing.c src/parser.c src/second_split.c src/parsing_utilities.c gnl/get_next_line.c gnl/get_next_line_utils.c
OBJS= $(SRCS:.c=.o)
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline $(LIBFT)
$(LIBFT):
	@make -C $(LIBFTDIR) > /dev/null
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
	@make clean -C $(LIBFTDIR) > /dev/null
fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFTDIR) > /dev/null
all: $(NAME)
re: fclean all
.PHONY: clean fclean all re
