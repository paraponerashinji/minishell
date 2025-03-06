NAME= minishell
CC= cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFTDIR) -ggdb
SRCS=		main.c\
		src/Parsing/parser.c\
		src/Parsing/parser_utilities.c\
		src/Parsing/first_split.c\
		src/Parsing/first_split_utilities.c\
		src/Parsing/listing.c\
		src/Parsing/listing_utilities.c\
		src/Parsing/second_split.c\
		src/Parsing/valid_line.c\
		src/Pipes/pipes.c\
		src/Pipes/replacing.c\
		src/Pipes/execute.c\
		src/Pipes/input.c\
		src/Pipes/output.c\
		src/Pipes/utils.c\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c
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
