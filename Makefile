NAME := philo
CC := cc
CFLAGS := -Wall -Wextra -Werror -g
SRCS := philo.c philo_allocs.c philo_frees.c libft.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
