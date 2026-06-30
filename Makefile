NAME := philo
CC := cc
CFLAGS := -Wall -Wextra -Werror -g -pthread
SRCS := philo.c parsing.c utils.c dinner.c init.c safe_functions.c free.c get_set.c syncro_utils.c overview.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re